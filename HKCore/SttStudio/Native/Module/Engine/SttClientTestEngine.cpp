#include "stdafx.h"
#include "SttClientTestEngine.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttSocket/TestTerminal/VC/SttClientSocket.h"

#include "../../../Module/Socket/XPing.h"

#ifndef NOT_USE_XLANGUAGE

#include "../../../Module/XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttClientTestEngine::CSttClientTestEngine()
{

}

CSttClientTestEngine::~CSttClientTestEngine()
{
	
}

BOOL CSttClientTestEngine::ConnectServer(const CString &strIPServer, long nPort)
{
	if (m_pSttClientSocket == NULL)
	{
		m_pSttClientSocket = new CSttClientSocket();

		m_oCurrUser.SetRefSttSckt(m_pSttClientSocket);
		m_pSttClientSocket->SetTestEngine(this);
		SetRefSocket(m_pSttClientSocket);
		SetSttSvrUserMngrRef(&m_oClientUserMngr);
		m_pSttClientSocket->AttachCmdOverTimeMsgRcv(this);
	}

	//û����������½��е��ԣ����õȺܳ�ʱ��
	BOOL bRet = FALSE;
#ifndef _PSX_QT_LINUX_
	bRet = xping(strIPServer.GetString());
	#ifdef NOT_USE_XLANGUAGE
		if (!bRet)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("���ӷ�����[%s][%d]�ɹ�"), strIPServer.GetString(), nPort);
			return bRet;
		}
	#else
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ConServerSucc.GetString(), strIPServer.GetString(), nPort);
		return bRet;
	}
#endif
#endif


	bRet = m_pSttClientSocket->ConnectServer(strIPServer, nPort);

	if (!bRet)
	{
		delete m_pSttClientSocket;
		m_pSttClientSocket = NULL;
	}

	return bRet;
}

//xxy 20200927:ClientEngineData::Disconnect�Ѿ�����
// void CSttClientTestEngine::CloseSocket(CSttSocketDataBase *pSocket)
// {
// 	if (m_pSttClientSocket == NULL)
// 	{
// 		return;
// 	}
// 
// 	m_pSttClientSocket->WaitForThreadExit();
// 	delete m_pSttClientSocket;
// 	m_pSttClientSocket = NULL;
// }

void CSttClientTestEngine::OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket)
{
	CSttTestEngineClientData::OnSocketClose(pSocket, bDeleteSocket);
}

long CSttClientTestEngine::OnTestMsg(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen)
{
	if (m_pTestEventRcv != NULL)
	{
		m_pTestEventRcv->OnTestMsg(pBuf, nLen);
	}

	return CSttTestEngineBase::OnTestMsg(pClientSocket, pBuf, nLen);
}

long CSttClientTestEngine::Process_Cmd_Test(CSttSocketDataBase *pClientSocket, CSttTestCmd &oTestCmd)
{
	return 0;
}

long CSttClientTestEngine::Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_InputData)
	{//����¼������
		return Process_Cmd_Ats_InputData(pClientSocket, oAtsCmd);
	}
	return 0;
}

long CSttClientTestEngine::Process_SysState_System(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	long nValue = 0;
	BOOL bPreLogin = FALSE;
	long nRet = 0;

	if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Login)
	{//����ǵ�¼Ӧ�𡾱��ء�Զ�̡�
		nRet = Process_SysState_System_Login(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Logout)
	{//������˳���¼Ӧ�𡾱��ء�Զ�̡�
		nRet = Process_SysState_System_Logout(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Request)
	{//�����Ȩ������Ӧ�𡾱��ء�Զ�̡�
		nRet = Process_SysState_System_Request(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Authority)
	{//�����AuthorityӦ��Զ�̡�
		nRet = Process_SysState_System_Authority(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_LiveUpdate)
	{
		nRet = Process_SysState_System_LiveUpdate(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_SetSysConfig)
	{
		nRet = Process_SysState_System_SetSysConfig(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_GetSysConfig)
	{
		nRet = Process_SysState_System_GetSysConfig(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_ReadMeas)
	{//2021-10-2  lijunqing
		nRet = Process_SysState_System_ReadMeas(oSysState);
	}
	else
	{//������������
		
	}
	
	long nCmdExecState = oSysState.Get_ExecStatus();
	CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nRet;
}

//////////////////////////////////////////////////////////////////////////
//
long CSttClientTestEngine::Process_SysState_Test(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	On_SysState_Test(oSysState);

	return 0;
}

long CSttClientTestEngine::Process_SysState_Ats(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	On_SysState_Ats(oSysState);

	return 0;
}

long CSttClientTestEngine::Process_SysState_Adjust(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	On_SysState_Adjust(oSysState);

	return 0;
}

long CSttClientTestEngine::Process_SysState_IOT(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	On_SysState_IOT(oSysState);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
long CSttClientTestEngine::Process_SysState_Debug(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	//CSttDebug��ȫ��Ψһ����

	On_SysState_Debug(oSysState);

	return 0;
}

long CSttClientTestEngine::Process_SysState_BroadcastUserMngr(CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_BroadcastUserMngr(oSysState);
}

long CSttClientTestEngine::Process_SysState_Exception(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Exception(pClientSocket,oSysState);
}

long CSttClientTestEngine::Process_SysState_Report(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Report(pClientSocket,oSysState);
}

long CSttClientTestEngine::Process_SysState_Packet(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Packet(pClientSocket,oSysState);
}

long CSttClientTestEngine::Process_SysState_Update(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Update(pClientSocket,oSysState);
}

long CSttClientTestEngine::Process_SysState_State(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return 1;
}

long CSttClientTestEngine::Process_SysState_SearchPointReport(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return 1;
}

long CSttClientTestEngine::Process_SysState_Log(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Log(pClientSocket,oSysState);
}

long CSttClientTestEngine::Process_SysState_Event(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Event(pClientSocket,oSysState);
}

long CSttClientTestEngine::Process_SysState_RtData(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_RtData(pClientSocket,oSysState);
}

long CSttClientTestEngine::Process_SysState_Meas(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
    return CSttTestEngineClientData::Process_SysState_Meas(pClientSocket,oSysState);
}

long CSttClientTestEngine::Process_SysState_Ats_Stop(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Ats_Stop(pClientSocket,oSysState);
}

long CSttClientTestEngine::Process_SysState_System_LiveUpdate(CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_System_LiveUpdate(oSysState);
}

long CSttClientTestEngine::Process_Comtrade_RequestData(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{//�յ�����Comtrade��������
	int *pTemp = (int *)(&pBuf[STT_PKG_HEAD_LEN+1]);
	int nRequestIndex = pTemp[0];

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�յ��ط���������index=%d"),nRequestIndex);

	if (m_pTestEventRcv != NULL)
	{
		m_pTestEventRcv->Event_OnProcessComtradeRequstData(nRequestIndex);
	}

	return 1;
}

long CSttClientTestEngine::Process_Comtrade_SendDataStartAck(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	int *pTemp = (int *)(&pBuf[STT_PKG_HEAD_LEN+1]);
	int nSendIndex = pTemp[0];

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�յ��������ݿ�ʼӦ��index=%d"),nSendIndex);

	if (m_pTestEventRcv != NULL)
	{
		m_pTestEventRcv->Event_OnProcessComtradeSendDataStartAck(nSendIndex);
	}

	return 1;
}

long CSttClientTestEngine::Process_Cmd_Comtrade(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	int nType = pBuf[STT_PKG_HEAD_LEN];

	switch (nType)
	{
	case STT_CMD_TYPE_COMTRADE_REQUESTDATA:
		return Process_Comtrade_RequestData(pClientSocket,pBuf,nLen,pszCmdID,pszTestor);
	case STT_CMD_TYPE_COMTRADE_SENDDATASTART_ACK:
		return Process_Comtrade_SendDataStartAck(pClientSocket,pBuf,nLen,pszCmdID,pszTestor);
	}

	return 0;
}


long CSttClientTestEngine::Process_SysState(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor, char *pszRetCmdType)
{
	//ΪDebug������Ĵ������磺��ʾ���Բ�����ֱ��ʹ�ñ��ĵĲ����ı����ɣ�û�б�Ҫ�ٽ�����һ��
	if (m_pTestEventRcv != NULL)
	{
		if(strcmp(pszRetCmdType,  STT_CMD_SYSSTATE_DEBUG) == 0)
		{
			if (m_pTestEventRcv->OnRecvSttDebugData(pBuf, nLen, pszCmdID, pszTestor, pszRetCmdType))
			{
				return 0;
			}
		}
	}

	return CSttTestEngineBase::Process_SysState(pClientSocket, pBuf, nLen, pszCmdID, pszTestor, pszRetCmdType);
}

void CSttClientTestEngine::AddPkgDispatch(CSttPkgDispatchInterface *pPkgDispatch)
{
    Add(pPkgDispatch);
}

void CSttClientTestEngine::RemovePkgDispatch(CSttPkgDispatchInterface *pPkgDispatch)
{
	Remove(pPkgDispatch);
}
