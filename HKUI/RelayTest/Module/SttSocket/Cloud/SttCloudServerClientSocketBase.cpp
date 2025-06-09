#include "stdafx.h"

#include "SttCloudServerClientSocketBase.h"
#include "SttCloudServerSocketBase.h"
#include "../../SttGlobalDef.h"
#include "../../SttCmd/SttSysState.h"
#include "../../Cloud/SttRemoteRegMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttCloudServerClientSocketBase::CSttCloudServerClientSocketBase()
{
	m_pRefSttSckt = NULL;
	m_pszXmlBuffer = NULL;
	m_nXmlBufferLen = 0;
	SetXmlBufferLen(1048576); //1M
}

//2020-5-25  避免xml解析的时候，频繁分配内存，缺省为1M个wchar_t
void CSttCloudServerClientSocketBase::SetXmlBufferLen(long nLen)
{
	if (nLen <= m_nXmlBufferLen)
	{
		return;
	}

	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}

	m_pszXmlBuffer = new char [nLen+10];
	m_nXmlBufferLen = nLen;
	memset(m_pszXmlBuffer, 0, nLen);
}

CSttCloudServerClientSocketBase::~CSttCloudServerClientSocketBase()
{
	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}
}

//客户端断链
void CSttCloudServerClientSocketBase::OnSocketClose(int nErrorCode)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("CSttCloudServerClientSocketBase::OnSocketClose 【nErrorCode = %d】"), nErrorCode);
	if (m_nIDTester != 0)
	{
		if(IsSocketType_Remote())
		{//远程端且已绑定
			if(m_pRefSttSckt != NULL)
			{
				CStt_RemoteRegRT *pFind = g_oSttRemoteRegMngr.FindByRefSocket(m_pRefSttSckt);

				if (pFind != NULL)
				{
					CStt_RemoteUserRT *pFindUser = pFind->FindByIDTest(m_nIDTester);
					if (pFindUser != NULL)
					{//是否已登录
						//生成Logout命令转发给本地
						CSttSystemCmd oSystemCmd;
						oSystemCmd.m_strID = STT_CMD_TYPE_SYSTEM_Logout;
						oSystemCmd.AddNewParasData(ID_STT_USER_ATTR_ID_Terminal, STT_TERMINAL_TYPE_REMOTE);
						oSystemCmd.AddNewParasData(ID_STT_USER_ATTR_SN_TestApp, m_pRefSttSckt->m_strSN_TestApp);
						oSystemCmd.AddNewParasData(ID_STT_USER_ATTR_Code_Register, m_pRefSttSckt->m_strCode_Register);
						oSystemCmd.AddNewParasData(STT_CMD_PARA_IDTESTER, m_nIDTester);

						m_pRefSttSckt->SendCmdEx(&oSystemCmd,m_nIDTester);
					}
				}	
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnSocketClose【%d】error"),m_nIDTester);
			}

			((CSttCloudServerClientSocketBase *)m_pRefSttSckt)->DeleteBindSocket(this);
		}
		else
		{//测试仪或远程协助
			//本地端断链
			InitAfterUnRegister(TRUE);

			CSttSocketDataBase_File::OnSocketClose(nErrorCode);
		}
	}
	else
	{//无绑定、纯连接
		CSttSocketDataBase_File::OnSocketClose(nErrorCode);
	}
}

void CSttCloudServerClientSocketBase::AddBindSocket(CSttCloudServerClientSocketBase *p,DWORD nIDTester)
{
	CAutoSimpleLock oLock(m_oClientChildSocketMngrLock);
	p->m_pRefSttSckt = this;
	p->m_nSocketType = STT_SOCKET_TYPE_REMOTE;
	p->m_nIDTester = nIDTester;
	
	CSttCloudServerClientSocketBase *pFind = FindBindSocketByIDTest(nIDTester);
	if (pFind == NULL)
	{
		AddTail(p);
	}
	else
	{
		if (pFind != p)
		{//相同客户端重复绑定
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("AddBindSocket【%u】repeat 绑定"),nIDTester);
//			pFind->CloseSocket();
			Delete(pFind);
			AddTail(p);
		}	
	}
}

void CSttCloudServerClientSocketBase::DeleteBindSocket(CSttCloudServerClientSocketBase *p)
{
	CAutoSimpleLock oLock(m_oClientChildSocketMngrLock);
	Delete(p);
}

CSttCloudServerClientSocketBase* CSttCloudServerClientSocketBase::FindBindSocketByIDTest(DWORD nIDTester)
{
	POS pos = GetHeadPosition();
	CSttCloudServerClientSocketBase *p = NULL;

	while(pos != NULL)
	{
		p = (CSttCloudServerClientSocketBase *)GetNext(pos);

		if (p->GetIDTest() == nIDTester)
		{
			return p;
		}
	}

	return NULL;
}

void CSttCloudServerClientSocketBase::InitAfterUnRegister(BOOL bDisconnect)
{
	//更新数据链表、数据库
	g_oSttRemoteRegMngr.DeleteRegisterChild(this);
	m_nIDTester = 0;//未注册状态
	m_strCode_Register = _T("");
	m_strSN_TestApp = _T("");

	//更新Socket链表
	POS pos = GetHeadPosition();
	CSttCloudServerClientSocketBase *p = NULL;

	while (pos != NULL)
	{
		p = (CSttCloudServerClientSocketBase *)GetNext(pos);

		if (bDisconnect)
		{
			DeleteBindSocket(p);
		}
		else
		{
			p->CloseSocket();
		}	
	}
}

BOOL CSttCloudServerClientSocketBase::ProcessRecvPacket(BYTE *pBuf, long nLen)
{
	long nCmdType = 0;
	char pszCmdID[64] = {0}, pszTestor[64] = {0}, pszRetCmdType[64]={0};
	BOOL bRet = FALSE;

	bRet = stt_pkg_get_cmd_id((char*)pBuf,nLen,nCmdType, pszCmdID, pszTestor, pszRetCmdType);

	if (!bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("解析报文命令头错误!"));
		return FALSE;
	}

	//File
	if (stt_is_cmd_a_file_cmd(nCmdType))
	{
		return ProcessCmd_File(pBuf, nLen);
	}

	//Heartbeat
	if (nCmdType == STT_CMD_TYPE_HEARTBEAT)
	{
		return ProcessCmd_HeartBeat(pBuf, nLen);
	}

	//Remote
	if (strcmp(pszCmdID,STT_CMD_TYPE_REMOTE_Register) == 0)
	{
		return ProcessCmd_Register(pBuf, nLen);
	}

	if (strcmp(pszCmdID,STT_CMD_TYPE_REMOTE_UnRegister) == 0)
	{
		return ProcessCmd_UnRegister(pBuf, nLen);
	}
	
	if (strcmp(pszCmdID,STT_CMD_TYPE_REMOTE_Bind) == 0)
	{
		return ProcessCmd_Bind(pBuf, nLen);
	}

	if (strcmp(pszCmdID,STT_CMD_TYPE_REMOTE_Query) == 0)
	{
		return ProcessCmd_Query(pBuf, nLen);
	}
	
	//SysState
	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{
		return ProcessCmd_SysState(pBuf, nLen, pszCmdID, pszTestor);
	}

	//System
	if (nCmdType == STT_CMD_TYPE_SYSTEM)
	{
		return ProcessCmd_XCmd_System(pBuf, nLen, pszCmdID, pszTestor);
	}
	
	//ATS
	if (nCmdType == STT_CMD_TYPE_ATS)
	{
		return ProcessCmd_XCmd_Ats(pBuf, nLen, pszCmdID, pszTestor);
	}

	//TEST
	if (nCmdType == STT_CMD_TYPE_TEST)
	{
		return ProcessCmd_XCmd_Test(pBuf, nLen, pszCmdID, pszTestor);
	}
	
	//Assist
	if (nCmdType == STT_CMD_TYPE_ASSIST)
	{
		return ProcessCmd_XCmd_Assist(pBuf, nLen, pszCmdID, pszTestor);
	}
	
	//Debug
	if (nCmdType == STT_CMD_TYPE_DEBUG)
	{
		return ProcessCmd_XCmd_Debug(pBuf, nLen, pszCmdID, pszTestor);
	}

	return 0;
}

CSttSocketDataBase *CSttCloudServerClientSocketBase::FindDestSocket(int nDestID)
{
	CAutoSimpleLock oLock(m_oClientChildSocketMngrLock);

	CSttSocketDataBase *pParentSocket = m_pRefSttSckt;
	if (pParentSocket == NULL)
	{
		pParentSocket = this;
	}

	POS pos = pParentSocket->GetHeadPosition();
	CSttSocketDataBase *pFind = NULL;

	while(pos != NULL)
	{
		pFind = (CSttSocketDataBase *)pParentSocket->GetNext(pos);

		if (pFind->GetIDTest() == nDestID)
		{
			return pFind;
		}
	}

	return NULL;
}

CSttSocketDataBase *CSttCloudServerClientSocketBase::FindDestSocket(BYTE *pBuf,long nLen)
{
	BYTE *pTemp = (BYTE *)pBuf;
	int nID_Test = stt_pkg_get_idtester(pTemp);
	ASSERT(nID_Test != 0);

	if(nID_Test == NULL)
	{
		return 0;
	}

	return FindDestSocket(nID_Test);
}

long CSttCloudServerClientSocketBase::TransmitBufferToDest(BYTE *pBuf,long nLen)
{
	CSttSocketDataBase *pDestSocket = FindDestSocket(pBuf,nLen);

	if (pDestSocket != NULL)
	{
		return pDestSocket->SendBuffer(pBuf,nLen);
	}

	return 0;
}

//应用场景
BOOL CSttCloudServerClientSocketBase::SendCmdToChildren(CSttSocketDataBase *pExceptSocket
										   ,CSttCmdBase *pCmd,BOOL bCompress,BOOL bReset,BOOL bRetOwn)
{
	BYTE *pSendBuf = NULL;
	long nSendBufLen = 0;

	stt_InitSendBuf_Cmd(&pSendBuf,nSendBufLen,pCmd,bCompress, _PUGI_XML_TYPE_);

	BOOL bRet = SendBufferToChildren(pExceptSocket,pSendBuf,nSendBufLen,bRetOwn);
	delete pSendBuf;

	return bRet;
}

BOOL CSttCloudServerClientSocketBase::SendBufferToChildren(CSttSocketDataBase *pExceptSocket,BYTE *pBuf,long nLen,BOOL bRetOwn)
{
	CAutoSimpleLock oLock(m_oClientChildSocketMngrLock);

	if (bRetOwn)
	{
		SendBuffer(pBuf,nLen);
	}

	//转发给所有远程
	POS pos = GetHeadPosition();
	CSttSocketDataBase *p = NULL;

	while(pos != NULL)
	{
		p = (CSttSocketDataBase *)GetNext(pos);

		if(p == pExceptSocket)
		{
			continue;
		}

		p->SendBuffer(pBuf, nLen);
	}

	return TRUE;
}

BOOL CSttCloudServerClientSocketBase::SendSysStateToChildren(CSttSocketDataBase *pExceptSocket,CSttSysState *pSysState,BOOL bRetOwn)
{
	//转发应答命令给所有连接
	BYTE *pSendBuf = NULL;
	long nSendBufLen = 0;

	pSysState->m_nIDTester = GetIDTest();
	stt_InitRetSendBuf(&pSendBuf,nSendBufLen,pSysState, FALSE, _PUGI_XML_TYPE_);

	if (bRetOwn)
	{
		SendBuffer(pSendBuf,nSendBufLen);
	}
	BOOL bRet = SendBufferToChildren(pExceptSocket,pSendBuf,nSendBufLen);
	delete pSendBuf;

	return bRet;
}

long CSttCloudServerClientSocketBase::ProcessCmd_Register(BYTE *pBuf, long nLen)
{
	CSttRemoteCmd oRemoteCmd;

	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
	oRemoteCmd.ParsePkgXml(pBuf, nLen, m_pszXmlBuffer);

	CString strCode_Register,strSN_TestApp;
	oRemoteCmd.GetParasDataValueByID(ID_STT_USER_ATTR_SN_TestApp,strSN_TestApp);

	if(strSN_TestApp.IsEmpty())
	{
		Stt_GenerateSN_TestApp(strSN_TestApp);
	}

	//检查SN_TestApp是否存在
	BOOL bRet = g_pSttCloudSvrSocket->HasRegisteredByTestApp(strSN_TestApp);

	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oRemoteCmd);

	if (bRet)
	{//已经存在，则直接拒绝
		oSysState.Set_ExecStatus_Failure();
		oSysState.AddNewParasData(ID_STT_USER_ATTR_Code_Register, _T(""));
	}
	else
	{
		//生成注册码
		Stt_GenerateCode_Register(strSN_TestApp,strCode_Register);

		oSysState.Set_ExecStatus_Success();
		oSysState.AddNewParasData(ID_STT_USER_ATTR_Code_Register, strCode_Register);	
		oSysState.AddNewParasData(ID_STT_USER_ATTR_SN_TestApp, strSN_TestApp);

		//更新数据链表和数据库
		m_nIDTester = 0x8000;
		m_strCode_Register = strCode_Register;
		m_strSN_TestApp = strSN_TestApp;
		m_nSocketType = oRemoteCmd.GetRegisterMode();
	}

	BOOL bRet1 = SendSysState(&oSysState);

	if((!bRet) && bRet1)
	{
		oRemoteCmd.SetParasDataAttr(ID_STT_USER_ATTR_Code_Register,m_strCode_Register);
		oRemoteCmd.SetParasDataAttr(ID_STT_USER_ATTR_SN_TestApp,m_strSN_TestApp);
		g_oSttRemoteRegMngr.AddRegisterChild(oRemoteCmd,this);
	}

	return bRet1;
}

BOOL CSttCloudServerClientSocketBase::ProcessCmd_UnRegister(BYTE *pBuf, long nLen)
{
	CSttSysState oSysState;
	oSysState.m_strID = STT_CMD_TYPE_REMOTE_UnRegister;
	oSysState.Set_ExecStatus_Success();

	SendSysState(&oSysState);

	//注销后处理
	InitAfterUnRegister(FALSE);

	return TRUE;
}

BOOL CSttCloudServerClientSocketBase::ProcessCmd_Query(BYTE *pBuf, long nLen)
{
	CSttRemoteCmd oRemoteCmd;
	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
	oRemoteCmd.ParsePkgXml(pBuf, nLen, m_pszXmlBuffer);

	CString strCode_Register;
	oRemoteCmd.GetParasDataValueByID(ID_STT_USER_ATTR_Code_Register,strCode_Register);

	CStt_RemoteRegRTs oRemoteRegRTs;
	BOOL bRet = g_oSttRemoteRegMngr.QueryRegisterList(strCode_Register,oRemoteRegRTs);

	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oRemoteCmd);
	
	if (bRet)
	{
		oSysState.Set_ExecStatus_Success();
		oRemoteRegRTs.GenerateQuerySysState(oSysState);
		oRemoteRegRTs.RemoveAll();
	}
	else
	{
		oSysState.Set_ExecStatus_Failure();
	}

	return SendSysState(&oSysState);
}

long CSttCloudServerClientSocketBase::ProcessCmd_Bind(BYTE *pBuf, long nLen)
{
	CSttRemoteCmd oRemoteCmd;
	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
	oRemoteCmd.ParsePkgXml(pBuf, nLen, m_pszXmlBuffer);

	CString strCode_Register;
	DWORD nIDTester = 0;
	oRemoteCmd.GetParasDataValueByID(ID_STT_USER_ATTR_Code_Register,strCode_Register);
	oRemoteCmd.GetParasDataValueByID(STT_CMD_PARA_IDTESTER,nIDTester);

	BOOL bRet = g_pSttCloudSvrSocket->Bind(this,strCode_Register,nIDTester);

	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oRemoteCmd);

	if (bRet)
	{
		oSysState.Set_ExecStatus_Success();
	}
	else
	{
		oSysState.Set_ExecStatus_Failure();
	}
	
	oSysState.AddNewParasData(STT_CMD_PARA_IDTESTER, m_nIDTester);

	return SendSysState(&oSysState);
}

BOOL CSttCloudServerClientSocketBase::ProcessCmd_SysState(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttSysState oSysState;
	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
	oSysState.ParsePkgXml(pBuf, nLen, m_pszXmlBuffer);

	if (oSysState.m_strRetType == SYS_STATE_RETTYPE_USERMNGR)
	{
		g_oSttRemoteRegMngr.Update_UserList(&oSysState,this);
		return SendBufferToChildren(NULL,pBuf,nLen);
	}

	if ((oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Login)
		|| (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Logout)
		|| (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Request)
		|| (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Authority)
		|| (oSysState.m_strID == STT_CMD_TYPE_ATS_GetReportFile)
		|| (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_GetDirs)
		|| (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_DownFile)
		|| (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_DeleteFile)
		|| (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_DownFolder)
		|| (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_DeleteFolder)
		|| (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_CreateFolder)
		|| (oSysState.m_strID == STT_CMD_TYPE_DEBUG_GetProcessState)
		|| (oSysState.m_strID == STT_CMD_TYPE_DEBUG_GetMemState)
		|| (oSysState.m_strID == STT_CMD_TYPE_DEBUG_GetTestParas)
		|| (oSysState.m_strID == STT_CMD_TYPE_DEBUG_GetBasicTestParas)
		|| (oSysState.m_strID == STT_CMD_TYPE_DEBUG_GetFpgaData)
		|| (oSysState.m_strID == STT_CMD_TYPE_DEBUG_GetSocketConnect)
		|| (oSysState.m_strID == STT_CMD_TYPE_DEBUG_ConfigDebug))
	{//转发给发送端
		return TransmitBufferToDest(pBuf,nLen);
	}
	else
	{//转发给所有远程
		return SendBufferToChildren(NULL,pBuf,nLen);
	}
}

BOOL CSttCloudServerClientSocketBase::ProcessCmd_File(BYTE *pBuf, long nLen)
{//文件操作点对点
	if(IsSocketType_Remote())
	{//远程->云端
		//转发给本地
		return m_pRefSttSckt->SendBuffer(pBuf,nLen);
	}
	else
	{//本地->云端
		//转发给目标远程
		return TransmitBufferToDest(pBuf,nLen);
	}
}

long g_nLog_HeartBeat_Msg = 0;

long CSttCloudServerClientSocketBase::ProcessCmd_HeartBeat(BYTE *pBuf, long nLen)
{
	//ASSERT(m_pRefSttSckt != NULL);

	if (g_nLog_HeartBeat_Msg == 1)
	{	
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("收到心跳报文【%s,%d】"),m_strIPRemote,m_nPortRemote);
	}

	if(m_pRefSttSckt != NULL)
	{
		return m_pRefSttSckt->SendBuffer(pBuf,nLen);
	}

	return 1;
}

BOOL CSttCloudServerClientSocketBase::ProcessCmd_XCmd_Ats(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	BOOL bRet = FALSE;

	if(IsSocketType_Remote())
	{//远程->云端
		
		//转发给本地、其他远程
		bRet = m_pRefSttSckt->SendBuffer(pBuf,nLen);

		if (pszCmdID != STT_CMD_TYPE_ATS_GetReportFile)
		{
			bRet = m_pRefSttSckt->SendBufferToChildren(this, pBuf, nLen);
		}
	}
	else
	{//本地->云端
		//转发给所有远程
		bRet = SendBufferToChildren(NULL,pBuf,nLen);
	}

	return bRet;
}

BOOL CSttCloudServerClientSocketBase::ProcessCmd_XCmd_System(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{//远程->云端
	if(!IsSocketType_Remote())
	{//本地->云端
		return FALSE;
	}

//	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("ProcessCmd_XCmd_System: >>>>> 转发给本地"));
	//转发给本地
	return m_pRefSttSckt->SendBuffer(pBuf,nLen);
// 	long nRet = m_pRefSttSckt->SendBuffer(pBuf,nLen);
// 
// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ProcessCmd_XCmd_System: <<<<<[%d] 转发给本地"),nRet);
// 
// 	return nRet;
}

BOOL CSttCloudServerClientSocketBase::ProcessCmd_XCmd_Test(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	BOOL bRet = FALSE;

	if(IsSocketType_Remote())
	{//远程->云端
		
		//转发给本地、其他远程
		bRet = m_pRefSttSckt->SendBuffer(pBuf,nLen);

		//if (pszCmdID != STT_CMD_TYPE_TEST_GetSystemState)
		//{
		//	bRet = m_pRefSttSckt->SendBufferToChildren(this, pBuf, nLen);
		//}
	}
	else
	{//本地->云端
		//转发给所有远程
		bRet = SendBufferToChildren(NULL,pBuf,nLen);
	}

	return bRet;
}

BOOL CSttCloudServerClientSocketBase::ProcessCmd_XCmd_Assist(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	if(IsSocketType_Remote())
	{//远程->云端
		//转发给本地、其他远程
		m_pRefSttSckt->SendBuffer(pBuf,nLen);
		return m_pRefSttSckt->SendBufferToChildren(this, pBuf, nLen);
	}
	else
	{//本地->云端
		//转发给所有远程
		return SendBufferToChildren(NULL,pBuf,nLen);
	}
}

BOOL CSttCloudServerClientSocketBase::ProcessCmd_XCmd_Debug(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{//远程->云端
	if(!IsSocketType_Remote())
	{//本地->云端
		return FALSE;
	}

	//转发给本地
	return m_pRefSttSckt->SendBuffer(pBuf,nLen);
}

///////////////////////////////////////
void Stt_GenerateSN_TestApp(CString &strSN_TestApp)
{
	if (!strSN_TestApp.IsEmpty())
	{
		return;
	}

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	strSN_TestApp.Format(_T("%04d%02d%02d%02d%02d%02d")
		,tm.wYear,tm.wMonth,tm.wDay,tm.wHour,tm.wMinute,tm.wSecond);
}

void Stt_GenerateCode_Register(const CString &strSN_TestApp,CString &strCode_Register)
{
	CString strSN = strSN_TestApp;

	Stt_GenerateSN_TestApp(strSN);

	strCode_Register = strSN;
}