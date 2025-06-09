#include "stdafx.h"
#include "SttRemoteClientTestEngine.h"
#include "../SttAuthority/SttTestRemoteRegister.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttSocket/TestTerminal/VC/SttClientSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttRemoteClientTestEngine::CSttRemoteClientTestEngine()
{

}

CSttRemoteClientTestEngine::~CSttRemoteClientTestEngine()
{

}

BOOL CSttRemoteClientTestEngine::ConnectServer(const CString &strIPServer, long nPort)
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

	return m_pSttClientSocket->ConnectServer(strIPServer, nPort);
}

void CSttRemoteClientTestEngine::OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket)
{
	CSttTestEngineRemoteClientData::OnSocketClose(pSocket, bDeleteSocket);
}

long CSttRemoteClientTestEngine::Process_Cmd_Test(CSttSocketDataBase *pClientSocket, CSttTestCmd &oTestCmd)
{
	
	return 0;
}

long CSttRemoteClientTestEngine::Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CSttRemoteClientTestEngine::Process_SysState_System(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
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
	else
	{//������������

	}
	
	long nCmdExecState = oSysState.Get_ExecStatus();
	CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nRet;
}

long CSttRemoteClientTestEngine::Process_SysState_Remote(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	long nRet = 0;

	if (oSysState.m_strID == STT_CMD_TYPE_REMOTE_Bind)
	{//����ǰ�Ӧ��Զ�̡�
		nRet = Process_SysState_System_Bind(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_REMOTE_Query)
	{//����ǲ�ѯ��Զ�̡�
		nRet = Process_SysState_System_Query(oSysState);
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
long CSttRemoteClientTestEngine::Process_SysState_Test(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	On_SysState_Test(oSysState);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
long CSttRemoteClientTestEngine::Process_SysState_Debug(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	//CSttDebug��ȫ��Ψһ����

	On_SysState_Debug(oSysState);

	return 0;
}

long CSttRemoteClientTestEngine::Process_SysState_BroadcastUserMngr(CSttSysState &oSysState)
{
	return CSttTestEngineRemoteClientData::Process_SysState_BroadcastUserMngr(oSysState);
}

long CSttRemoteClientTestEngine::Process_SysState_Event(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Event(pClientSocket,oSysState);
}

long CSttRemoteClientTestEngine::Process_SysState_Exception(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Exception(pClientSocket,oSysState);
}

long CSttRemoteClientTestEngine::Process_SysState_Report(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Report(pClientSocket,oSysState);
}