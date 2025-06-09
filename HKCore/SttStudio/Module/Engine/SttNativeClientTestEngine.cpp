#include "stdafx.h"
#include "SttNativeClientTestEngine.h"
#include "../SttCmd/SttTestCmd.h"

#ifdef _PSX_QT_LINUX_
#include "../SttSocket/TestTerminal/QT/SttClientSocket.h"
#else
#include "../SttSocket/TestTerminal/VC/SttClientSocket.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttNativeClientTestEngine::CSttNativeClientTestEngine()
{//�����ͻ���socket,���ù���ָ��
	m_pExternEngineRef = NULL;
}

CSttNativeClientTestEngine::~CSttNativeClientTestEngine()
{
	
}

/*************************
1���յ�TestServer GetScktConnect��������û�Ȩ�޹�������Ӧ��ֱ�Ӵ�����
2���յ�NativeEngineת������Զ�̵������Զ˻�TestControlģ�����ɡ��ĵ������������Debug���
ͨ��SendBufferֱ��͸����TestServer
3���յ�TestServer�������������Debug����Ӧ��ֱ��ת����NativeEngine
**************************/
BOOL CSttNativeClientTestEngine::OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet)
{
	if (m_pSttTestMsgViewInterface != NULL)
	{
		m_pSttTestMsgViewInterface->OnTestMsgEx(pClientSocket, pBuf, nLen, nCmdType, pszCmdID, pszTestor, pszRetCmdType);
	}

	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{
		DWORD nIDTester = stt_pkg_get_idtester(pBuf);
		if (m_oCurrUser.GetIDTest() == nIDTester)
		{//NativeClient���������Ӧ��
			return Process_SysState(pClientSocket,pBuf, nLen, pszCmdID, pszTestor, pszRetCmdType);
		}

// 		if ((strcmp(pszCmdID,STT_CMD_TYPE_SYSTEM_Login) == 0)
// 			|| (strcmp(pszCmdID,STT_CMD_TYPE_SYSTEM_Logout) == 0)
// 			|| (strcmp(pszCmdID,STT_CMD_TYPE_SYSTEM_Request) == 0)
// 			|| (strcmp(pszCmdID,STT_CMD_TYPE_SYSTEM_Authority) == 0))
// 		{
// 			return Process_SysState(pClientSocket,pBuf, nLen, pszCmdID, pszTestor, pszRetCmdType);
// 		}
// 		else
// 		{
			char pszRetType[64] = {0};

			char *pCmdData = NULL;
			long nCmdLen = 0;

			BOOL bRet = stt_pkg_get_cmddata((char *)pBuf, nLen,pCmdData,nCmdLen);
			if (!bRet)
			{
				return FALSE;
			}

			stt_cmd_get_key_value(pCmdData, nCmdLen, STT_SYSSTATE_RET_TYPE, pszRetType);

			if (strcmp(pszRetType,SYS_STATE_RETTYPE_USERMNGR) == 0)
			{
				return Process_SysState(pClientSocket,pBuf, nLen, pszCmdID, pszTestor, pszRetCmdType);
			}
// 		}

		//����ת����NativeEngine
		//�����⣺��Ҫ����CSttClientTestEngine���������˷��͵�sys-cmd
		return m_pExternEngineRef->OnTestMsgEx(pClientSocket, pBuf, nLen, nCmdType, pszCmdID, pszTestor, pszRetCmdType, bRet);
	}
	else
	{
		//����TestServer ��������GetScktConnect����
		return CSttTestEngineBase::Process_Cmd_Debug(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);

//		return CSttTestEngineBase::OnTestMsgEx(pClientSocket, pBuf, nLen, nCmdType, pszCmdID, pszTestor, nRetCmdType, bRet);
	}

	return TRUE;
}

long CSttNativeClientTestEngine::Process_SysState_System(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
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

long CSttNativeClientTestEngine::Process_Cmd_Debug(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	//TODO�������������
	long bRet = 0;

	CString strDebugCmd = oDebugCmd.m_strID; //��ȡDebug��������

	if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetSocketConnect)
	{
		bRet = Process_Debug_GetSocketConnect(pClientSocket,oDebugCmd);
	}

	return bRet;
}

long CSttNativeClientTestEngine::Process_Debug_GetSocketConnect(CSttSocketDataBase *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oDebugCmd);

	m_pExternEngineRef->m_oClientUserMngr.GenerateSysState(oSysState);

	return pClientSocket->SendSysState(&oSysState);
}


void CSttNativeClientTestEngine::OnSendHeartbeatTimer()
{
	//xxy 20210522 ��Ҫ���ȡ��ע���NativeClientռ��TestȨ��
	//���û��ClientEngineȨ�ޣ����ͷ�NativeClient��TestȨ��
	CSttTestClientUser *pFind = m_pExternEngineRef->m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_ClientEngine);
	if (pFind == NULL)
	{
		if (m_oCurrUser.HasAuthority(KEY_AUTHORITY_MODULE_Test))
		{
			System_Request(KEY_AUTHORITY_MODULE_Test,0);
			return;
		}
	}
	
	CSttTestEngineClientData::OnSendHeartbeatTimer();
}