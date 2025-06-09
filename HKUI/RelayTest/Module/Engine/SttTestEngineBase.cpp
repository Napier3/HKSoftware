#include "stdafx.h"
#include "SttTestEngineBase.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CSttTestMsgViewInterface::OnTestMsgEx(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType){}
void CSttTestMsgViewInterface::On_Process_Cmd_System(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd){}
void CSttTestMsgViewInterface::On_Process_Cmd_Test(CSttXcmdChInterface *pClientSocket,  CSttTestCmd &oTestCmd){}
void CSttTestMsgViewInterface::On_Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd){}
void CSttTestMsgViewInterface::On_Process_Cmd_Remote(CSttXcmdChInterface *pClientSocket, CSttRemoteCmd &oRemoteCmd){}
void CSttTestMsgViewInterface::On_Process_Cmd_Ats(CSttXcmdChInterface *pClientSocket, CSttAtsCmd &oAtsCmd){}
void CSttTestMsgViewInterface::On_Process_Cmd_Assist(CSttXcmdChInterface *pClientSocket, CSttAssistCmd &oAssistCmd){}
void CSttTestMsgViewInterface::On_Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd){}
void CSttTestMsgViewInterface::On_Process_SysState(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState){}

//////////////////////////////////////////////////////////////////////////
//CSttTestEngineBase
CSttTestEngineBase::CSttTestEngineBase()
{
	m_pSocketDataBase = NULL;
	m_pSttTestMsgViewInterface = NULL;
	m_pszXmlBuffer = NULL;
	m_nXmlBufferLen = 0;
	SetXmlBufferLen(1048576); //1M
}

CSttTestEngineBase::~CSttTestEngineBase()
{
	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}
}

void CSttTestEngineBase::OnSendCmdFailFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID){}
void CSttTestEngineBase::OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID){}
void CSttTestEngineBase::OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID){}


//2020-5-25  避免xml解析的时候，频繁分配内存，缺省为1M个wchar_t
void CSttTestEngineBase::SetXmlBufferLen(long nLen)
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
	memset(m_pszXmlBuffer, 0, nLen+10);
}


void CSttTestEngineBase::CloseSocket(CSttXcmdChInterface *pSocket)
{
	
}

void CSttTestEngineBase::OnSocketClose(CSttXcmdChInterface *pSocket, BOOL bDeleteSocket)
{

}

long CSttTestEngineBase::SendCmd(CSttCmdBase *pCmd,BOOL bCompress,BOOL bReset, long nSrcID_Test, long nTimeOut)
{//根据权限
	return 0;
}

long CSttTestEngineBase::ReturnSysState(CSttXcmdChInterface *pSocket, int nCmdType, char *pszCmdID, BOOL bIsSuccess)
{
	return 0;
}

long CSttTestEngineBase::ReturnSysState(CSttXcmdChInterface *pSocket,CSttSysState *pSysState, BOOL bSpyAllCmd)
{
	if (pSocket == NULL)
	{
		return 0;
	}

    //2020-11-29  lijunqing
    m_oClientUserMngr.SendSysState(pSocket, pSysState, bSpyAllCmd);
    return 0;
    //return pSocket->SendSysState(pSysState);
}

//lijunqing 2020-10-21
long CSttTestEngineBase::ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttXcmdChInterface *pSocket, CSttCmdData *pRetData)
{
	if (pSocket == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("SttCmd->m_pRefSocketDataBase == NULL"));
		return 0;
	}

	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pSttCmd);

	if (pRetData != NULL)
	{//返回结果数据
		//2020-10-27  lijunqing
		oSysState.AppendParas(*pRetData);
		//pRetData->RemoveAll();
	}

	oSysState.Set_ExecStatus(nCmdExecStatus);

	return pSocket->XSendSysState(&oSysState);
}


//lijunqing 2020-10-20
long CSttTestEngineBase::ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttCmdData *pRetData)
{
	CSttXcmdChInterface *pSocket = pSttCmd->GetRefSocketData();
	return ReturnSysState(pSttCmd, nCmdExecStatus, pSocket, pRetData);
}

CSttXcmdChInterface *CSttTestEngineBase::GetTestAuthoritySocket()
{
	CSttTestClientUser *pUser = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_Test);
	if (pUser == NULL)
	{
		return NULL;
	}
	return pUser->m_pRefSttSckt;
}

CSttXcmdChInterface *CSttTestEngineBase::GetAtsAuthoritySocket()
{
	CSttTestClientUser *pUser = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_Ats);
	if (pUser == NULL)
	{
		return NULL;
	}
	return pUser->m_pRefSttSckt;
}

//2020-11-29  lijunqing
//根据软件ID返回报文
void CSttTestEngineBase::SendToAllUser(const CString &strSoftID, BYTE *pBuf,long nLen)
{
    m_oClientUserMngr.SendToAllUser(strSoftID, pBuf, nLen);
}

void CSttTestEngineBase::LogPkgHeadError(BYTE *pBuf, long nLen)
{
	stt_LogPkgHeadError(pBuf, nLen);
}

long CSttTestEngineBase::OnTestMsg(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen)
{
	ASSERT(pClientSocket != NULL);

	long nCmdType = 0;
	char pszCmdID[64] = {0}, pszTestor[64] = {0}, pszRetCmdType[64]={0};
	BOOL bRet = FALSE;

    bRet = stt_pkg_get_cmd_id((char*)pBuf,nLen,nCmdType, pszCmdID, pszTestor, pszRetCmdType);

	if (!bRet)
	{
       LogPkgHeadError(pBuf, nLen);

		return FALSE;
	}

	bRet = FALSE;//zhouhj 2024.10.14
    m_oSttPkgDispatch.DispatchMsg(pBuf, nLen);


	return OnTestMsgEx(pClientSocket, pBuf, nLen, nCmdType, pszCmdID, pszTestor, pszRetCmdType, bRet);
}

BOOL CSttTestEngineBase::OnTestMsgEx(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet)
{
	//2020-11-29  lijunqing  监视所有命令报文
#ifdef _PSX_QT_LINUX_ 
	 if (g_nSttLogServerSpyAllCmd)
	 {
		 if (nCmdType != STT_CMD_TYPE_DEBUG)
		 {
			 SendToAllUser(STT_SOFT_ID_DEBUG, pBuf, nLen);
		 }
	 }
#endif

	//2020-3-24  lijq 发送消息给外部消息处理模块
	if (m_pSttTestMsgViewInterface != NULL)
	{
		m_pSttTestMsgViewInterface->OnTestMsgEx(pClientSocket, pBuf, nLen, nCmdType, pszCmdID, pszTestor, pszRetCmdType);
	}

	if (nCmdType == STT_CMD_TYPE_SYSTEM)
	{
		bRet = Process_Cmd_System(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
	}
	else if (nCmdType == STT_CMD_TYPE_TEST)
	{
		bRet = Process_Cmd_Test(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
	}
	else if (nCmdType == STT_CMD_TYPE_DEBUG)
	{
		bRet = Process_Cmd_Debug(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
	}
	else if (nCmdType == STT_CMD_TYPE_REMOTE)
	{
		bRet = Process_Cmd_Remote(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
	}
	else if (nCmdType == STT_CMD_TYPE_ATS)
	{
		bRet = Process_Cmd_Ats(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
	}
	else if (nCmdType == STT_CMD_TYPE_ASSIST)
	{
		bRet = Process_Cmd_Assist(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
	}
	else if (nCmdType == STT_CMD_TYPE_ADJUST)
	{
		bRet = Process_Cmd_Adjust(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
	}
	else if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{
		bRet = Process_SysState(pClientSocket,pBuf, nLen, pszCmdID, pszTestor, pszRetCmdType);
	}
	else if (nCmdType == STT_CMD_TYPE_HEARTBEAT)
	{
		bRet = Process_Heartbeat(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
	}
    else if (nCmdType == STT_CMD_TYPE_TRIGGER)
    {
        bRet = Process_Trigger(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
    }
	else if (nCmdType == STT_CMD_TYPE_COMTRADE)
	{
		bRet = Process_Cmd_Comtrade(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);
	}

	return bRet;
}

long CSttTestEngineBase::Process_Cmd_System(CSttXcmdChInterface *pClientSocket
								, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttSystemCmd oSysCmd;

	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
    oSysCmd.ParsePkgXml(pBuf, nLen, m_pszXmlBuffer);

	return Process_Cmd_System(pClientSocket, oSysCmd);
}

long CSttTestEngineBase::Process_Cmd_Test(CSttXcmdChInterface *pClientSocket
								, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttTestCmd oTestCmd;

	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
    oTestCmd.ParsePkgXml(pBuf,nLen, m_pszXmlBuffer);

	return Process_Cmd_Test(pClientSocket, oTestCmd);
}

long CSttTestEngineBase::Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket
								, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttDebugCmd oDebugCmd;

	oDebugCmd.SetRefSocketData(pClientSocket);
	SetXmlBufferLen(nLen * 2);
    oDebugCmd.ParsePkgXml(pBuf,nLen, m_pszXmlBuffer);

	ReturnSysState(&oDebugCmd, STT_CMD_ExecStatus_ACK, NULL);

	return Process_Cmd_Debug(pClientSocket, oDebugCmd);
}

long CSttTestEngineBase::Process_Cmd_Remote(CSttXcmdChInterface *pClientSocket
								, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttRemoteCmd oRemoteCmd;

	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
    oRemoteCmd.ParsePkgXml(pBuf,nLen, m_pszXmlBuffer);

	return Process_Cmd_Remote(pClientSocket, oRemoteCmd);
}

long CSttTestEngineBase::Process_Cmd_Ats(CSttXcmdChInterface *pClientSocket
								, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttAtsCmd *pAtsCmd = new CSttAtsCmd();
	pAtsCmd->AddRef();
	long nRet = 0;

	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
    pAtsCmd->ParsePkgXml(pBuf,nLen, m_pszXmlBuffer);

	//xxy测试命令应答
// 	CSttSysState oSysState;
// 	oSysState.UpdateSysStateHead(&oAtsCmd);
// 	oSysState.Set_IsSuccess(TRUE);
// 	oSysState.SetReply();
// 	pClientSocket->SendSysState(&oSysState);
#ifdef _SttTestServer_For_Debug_
	if (pAtsCmd->m_strID == STT_CMD_TYPE_ATS_InputData)
	{
		nRet = Process_Cmd_Ats(pClientSocket, *pAtsCmd);
	}

#else
	nRet = Process_Cmd_Ats(pClientSocket, *pAtsCmd);
#endif

	pAtsCmd->Release();
	return nRet;

}

long CSttTestEngineBase::Process_Cmd_Assist(CSttXcmdChInterface *pClientSocket
								, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttAssistCmd oAssistCmd;

	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
    oAssistCmd.ParsePkgXml(pBuf,nLen, m_pszXmlBuffer);

	return Process_Cmd_Assist(pClientSocket, oAssistCmd);
}

long CSttTestEngineBase::Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket
											, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	CSttAdjustCmd oAdjustCmd;

	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
	oAdjustCmd.ParsePkgXml(pBuf,nLen, m_pszXmlBuffer);

	return Process_Cmd_Adjust(pClientSocket, oAdjustCmd);
}

long CSttTestEngineBase::Process_SysState(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor, char *pszRetCmdType)
{
	CSttSysState oSysState;

	//2020-5-25 lijq
	SetXmlBufferLen(nLen * 2);
	oSysState.ParsePkgXml(pBuf, nLen, m_pszXmlBuffer);

// 	if (m_pSttTestMsgViewInterface != NULL)
// 	{
// 		m_pSttTestMsgViewInterface->On_Process_SysState(pClientSocket, oSysState);
// 	}

	//SYSTEMTIME tm;
	//::GetLocalTime(&tm);
	//CString strTmpPath = _P_GetLibraryPath();
	//strTmpPath.AppendFormat(_T("SysState%d-%d-%d %d-%d-%d.%d.xml"), tm.wYear, tm.wMonth, tm.wDay
	//	, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);
	//oSysState.SaveXmlFile(strTmpPath,CDataMngrXmlRWKeys::g_pXmlKeys);

	return Process_SysState(pClientSocket, oSysState);
}

long CSttTestEngineBase::Process_Heartbeat(CSttXcmdChInterface *pClientSocket
								, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	return 0;
}

long CSttTestEngineBase::Process_Trigger(CSttXcmdChInterface *pClientSocket
                                , BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
    return 0;
}

long CSttTestEngineBase::Process_Cmd_Comtrade(CSttXcmdChInterface *pClientSocket
										 , BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	return 0;
}

long CSttTestEngineBase::Process_Cmd(CSttXcmdChInterface *pClientSocket, CSttCmdBase *pCmd)
{
    UINT nClassID = pCmd->GetClassID();

    switch (nClassID)
    {
    case STTCMDCLASSID_CSTTSYSTEMCMD:
        return Process_Cmd_System(pClientSocket, *((CSttSystemCmd*)pCmd));
        break;

    case STTCMDCLASSID_CSTTTESTCMD:
        return Process_Cmd_Test(pClientSocket, *((CSttTestCmd*)pCmd));
        break;

    case STTCMDCLASSID_CSTTDEBUGCMD:
        return Process_Cmd_Debug(pClientSocket, *((CSttDebugCmd*)pCmd));
        break;

    case STTCMDCLASSID_CSTTATSCMD:
        return Process_Cmd_Ats(pClientSocket, *((CSttAtsCmd*)pCmd));
        break;

    case STTCMDCLASSID_CSTTASSISTCMD:
        return Process_Cmd_Assist(pClientSocket, *((CSttAssistCmd*)pCmd));
        break;

    case STTCMDCLASSID_CSTTADJUSTCMD:
        return Process_Cmd_Adjust(pClientSocket, *((CSttAdjustCmd*)pCmd));
        break;

	default:
		return -1;
    }
}

long CSttTestEngineBase::Process_Cmd_System(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd)
{
	return 0;
}

long CSttTestEngineBase::Process_Cmd_Test(CSttXcmdChInterface *pClientSocket,  CSttTestCmd &oTestCmd)
{
	return 0;
}

long CSttTestEngineBase::Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	return 0;
}

long CSttTestEngineBase::Process_Cmd_Remote(CSttXcmdChInterface *pClientSocket, CSttRemoteCmd &oRemoteCmd)
{
	return 0;
}

long CSttTestEngineBase::Process_Cmd_Ats(CSttXcmdChInterface *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CSttTestEngineBase::Process_Cmd_Assist(CSttXcmdChInterface *pClientSocket, CSttAssistCmd &oAssistCmd)
{
	return 0;
}

long CSttTestEngineBase::Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd)
{
	return 0;
}

long CSttTestEngineBase::Process_SysState(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	if(oSysState.m_strRetType == SYS_STATE_RETTYPE_USERMNGR)
	{
		return Process_SysState_BroadcastUserMngr(oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_EXCEPTION)
	{
		return Process_SysState_Exception(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_STATE)
	{
		return Process_SysState_State(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_REPORT)
	{
		return Process_SysState_Report(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_SEARCH_REPORT)
	{
		return Process_SysState_SearchPointReport(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_LOG)
	{
		return Process_SysState_Log(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_EVENT)
	{
		return Process_SysState_Event(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_PACKAGE)
	{
		return Process_SysState_Packet(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_UPDATE)
	{
		return Process_SysState_Update(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_REPLY)
	{
		return Process_SysState_Reply(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_RTDATA)
	{
		return Process_SysState_RtData(pClientSocket,oSysState);
	}
	else if(oSysState.m_strRetType == SYS_STATE_RETTYPE_MEAS)
	{
		return Process_SysState_Meas(pClientSocket,oSysState);
	}
	else if (oSysState.m_strRetType == SYS_STATE_RETTYPE_STOP_AUTOTEST)
	{
		return Process_SysState_Ats_Stop(pClientSocket,oSysState);
	}

	return 0;
}

long CSttTestEngineBase::Process_SysState_BroadcastUserMngr(CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_Exception(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_State(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_Report(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_SearchPointReport(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_Log(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_Event(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_Packet(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_Update(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_RtData(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_Meas(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState){	return 0;}
long CSttTestEngineBase::Process_SysState_Ats_Stop(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)	{	return 0;	}


long CSttTestEngineBase::Process_SysState_Reply(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{

	if (oSysState.m_strRetSttCmd == CSttCmdDefineXmlRWKeys::CSttSystemCmdKey())
	{
		return  Process_SysState_System(pClientSocket,oSysState);
	}
	else if (oSysState.m_strRetSttCmd ==  CSttCmdDefineXmlRWKeys::CSttTestCmdKey())
	{
		return  Process_SysState_Test(pClientSocket,oSysState);
	}
	else if (oSysState.m_strRetSttCmd ==  CSttCmdDefineXmlRWKeys::CSttDebugCmdKey())
	{
		return  Process_SysState_Debug(pClientSocket,oSysState);
	}
	else if (oSysState.m_strRetSttCmd ==  CSttCmdDefineXmlRWKeys::CSttRemoteCmdKey())
	{
		return  Process_SysState_Remote(pClientSocket,oSysState);
	}
	else if (oSysState.m_strRetSttCmd ==  CSttCmdDefineXmlRWKeys::CSttAtsCmdKey())
	{
		return  Process_SysState_Ats(pClientSocket,oSysState);
	}
	else if (oSysState.m_strRetSttCmd ==  CSttCmdDefineXmlRWKeys::CSttAssistCmdKey())
	{
		return  Process_SysState_Assist(pClientSocket,oSysState);
	}
	else if (oSysState.m_strRetSttCmd ==  CSttCmdDefineXmlRWKeys::CSttAdjustCmdKey())
	{
		return  Process_SysState_Adjust(pClientSocket,oSysState);
	}
	else if (oSysState.m_strRetSttCmd ==  CSttCmdDefineXmlRWKeys::CSttIotCmdKey())
	{//2022-10-08  lijunqing
		return  Process_SysState_IOT(pClientSocket,oSysState);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
long CSttTestEngineBase::Process_SysState_System(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	return 0;
}

long CSttTestEngineBase::Process_SysState_Test(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	return 0;
}

long CSttTestEngineBase::Process_SysState_Debug(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	return 0;
}

long CSttTestEngineBase::Process_SysState_Remote(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	return 0;
}

long CSttTestEngineBase::Process_SysState_Ats(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	return 0;
}

long CSttTestEngineBase::Process_SysState_Assist(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	return 0;
}

long CSttTestEngineBase::Process_SysState_Adjust(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	return 0;
}

long CSttTestEngineBase::Process_SysState_IOT(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	return 0;
}
