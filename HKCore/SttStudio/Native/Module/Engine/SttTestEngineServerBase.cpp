#include "stdafx.h"
#include "SttTestEngineServerBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttTestEngineServerBase::CSttTestEngineServerBase()
{
    m_pServerSocket = NULL;
	m_pReplaySocket = NULL;
	SetTestClientUserMngr(&m_oClientUserMngr);
}

CSttTestEngineServerBase::~CSttTestEngineServerBase()
{

}

void CSttTestEngineServerBase::OnSocketClose(CSttSocketDataBase *pSocket, BOOL bDeleteSocket)
{
	CSttTestEngineServerData::OnSocketClose(pSocket, bDeleteSocket);
}

long CSttTestEngineServerBase::Process_Cmd_System(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
	long nRet = 0;

    if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_Login)
    {
        nRet = Process_Cmd_System_Login(pClientSocket,oSysCmd);
    }
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_Logout)
    {
        nRet = Process_Cmd_System_Logout(pClientSocket,oSysCmd);
    }
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_Request)
    {
        nRet = Process_Cmd_System_Request(pClientSocket,oSysCmd);
    }
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_Authority)
    {
        nRet = Process_Cmd_System_Authority(pClientSocket,oSysCmd);
    }
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_GetDirs)
    {
        nRet = Process_Cmd_System_GetDirs(pClientSocket,oSysCmd);
    }
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_DownFile)
    {
        nRet = Process_Cmd_System_DownFile(pClientSocket,oSysCmd);
    }
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_SetSysConfig)
	{
		nRet = ProcessCmd_SetSysConfig(pClientSocket,oSysCmd);
	}
	else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_GetSysConfig)
	{
		nRet = ProcessCmd_GetSysConfig(pClientSocket,oSysCmd);
	}
    else if (oSysCmd.m_strID == STT_CMD_TYPE_SYSTEM_CloudTest)
    {
        nRet = ProcessCmd_CloudTest(pClientSocket,oSysCmd);
    }
    else
    {//������������

    }

	//2020-3-24  lijq ������Ϣ���ⲿ��Ϣ����ģ��
	if (m_pSttTestMsgViewInterface != NULL)
	{
		m_pSttTestMsgViewInterface->On_Process_Cmd_System(pClientSocket, oSysCmd);
	}

    return nRet;
}
