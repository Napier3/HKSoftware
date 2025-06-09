#include "stdafx.h"
#include "SttRemoteClientTestEngine.h"
#include "../SttAuthority/SttTestRemoteRegister.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttSocket/TestTerminal/VC/SttClientSocket.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"

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
		m_pSttClientSocket->XAttachCmdOverTimeMsgRcv(this);
	}

	return m_pSttClientSocket->XConnectServer(strIPServer, nPort);
}

void CSttRemoteClientTestEngine::OnSocketClose(CSttXcmdChInterface *pSocket, BOOL bDeleteSocket)
{
	CSttTestEngineRemoteClientData::OnSocketClose(pSocket, bDeleteSocket);
}

long CSttRemoteClientTestEngine::Process_Cmd_Test(CSttXcmdChInterface *pClientSocket, CSttTestCmd &oTestCmd)
{
	
	return 0;
}

long CSttRemoteClientTestEngine::Process_Cmd_Ats(CSttXcmdChInterface *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CSttRemoteClientTestEngine::Process_SysState_System(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	long nRet = 0;

	if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Login)
	{//如果是登录应答【本地、远程】
		nRet = Process_SysState_System_Login(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Logout)
	{//如果是退出登录应答【本地、远程】
		nRet = Process_SysState_System_Logout(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Request)
	{//如果是权限申请应答【本地、远程】
		nRet = Process_SysState_System_Request(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Authority)
	{//如果是Authority应答【远程】
		nRet = Process_SysState_System_Authority(oSysState);
	}
	else
	{//其他测试命令

	}
	
	long nCmdExecState = oSysState.Get_ExecStatus();
	CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nRet;
}

long CSttRemoteClientTestEngine::Process_SysState_Remote(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	long nRet = 0;

	if (oSysState.m_strID == STT_CMD_TYPE_REMOTE_Bind)
	{//如果是绑定应答【远程】
		nRet = Process_SysState_System_Bind(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_REMOTE_Query)
	{//如果是查询【远程】
		nRet = Process_SysState_System_Query(oSysState);
	}
	else
	{//其他测试命令

	}

	long nCmdExecState = oSysState.Get_ExecStatus();
	CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttClientSocket,oSysState,nCmdExecState);

	return nRet;
}

//////////////////////////////////////////////////////////////////////////
//
long CSttRemoteClientTestEngine::Process_SysState_Test(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	On_SysState_Test(oSysState);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
long CSttRemoteClientTestEngine::Process_SysState_Debug(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
{
	//CSttDebug：全局唯一对象

	On_SysState_Debug(oSysState);

	return 0;
}

long CSttRemoteClientTestEngine::Process_SysState_BroadcastUserMngr(CSttSysState &oSysState)
{
	return CSttTestEngineRemoteClientData::Process_SysState_BroadcastUserMngr(oSysState);
}

long CSttRemoteClientTestEngine::Process_SysState_Event(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Event(pClientSocket,oSysState);
}

long CSttRemoteClientTestEngine::Process_SysState_Exception(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Exception(pClientSocket,oSysState);
}

long CSttRemoteClientTestEngine::Process_SysState_Report(CSttXcmdChInterface *pClientSocket,CSttSysState &oSysState)
{
	return CSttTestEngineClientData::Process_SysState_Report(pClientSocket,oSysState);
}