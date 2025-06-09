#include "stdafx.h"
#include "SttNativeClientTestEngine.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"
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
{//创建客户端socket,设置关联指针
	m_pExternEngineRef = NULL;
}

CSttNativeClientTestEngine::~CSttNativeClientTestEngine()
{
	
}

/*************************
1、收到TestServer GetScktConnect、自身的用户权限管理命令应答，直接处理返回
2、收到NativeEngine转过来【远程单机测试端或TestControl模块生成】的单机测试命令和Debug命令，
通过SendBuffer直接透传给TestServer
3、收到TestServer单机测试命令或Debug命令应答，直接转发给NativeEngine
**************************/
BOOL CSttNativeClientTestEngine::OnTestMsgEx(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet)
{
	if (m_pSttTestMsgViewInterface != NULL)
	{
		m_pSttTestMsgViewInterface->OnTestMsgEx(pClientSocket, pBuf, nLen, nCmdType, pszCmdID, pszTestor, pszRetCmdType);
	}

	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{
		DWORD nIDTester = stt_pkg_get_idtester(pBuf);
		if (m_oCurrUser.GetIDTest() == nIDTester)
		{//NativeClient自身的命令应答
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

		//否则转发给NativeEngine
		//有问题：需要处理CSttClientTestEngine自身向服务端发送的sys-cmd
		return m_pExternEngineRef->OnTestMsgEx(pClientSocket, pBuf, nLen, nCmdType, pszCmdID, pszTestor, pszRetCmdType, bRet);
	}
	else
	{
		//处理TestServer 发过来的GetScktConnect命令
		return CSttTestEngineBase::Process_Cmd_Debug(pClientSocket,pBuf, nLen, pszCmdID, pszTestor);

//		return CSttTestEngineBase::OnTestMsgEx(pClientSocket, pBuf, nLen, nCmdType, pszCmdID, pszTestor, nRetCmdType, bRet);
	}

	return TRUE;
}

long CSttNativeClientTestEngine::Process_SysState_System(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState)
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

long CSttNativeClientTestEngine::Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	//TODO：处理调试命令
	long bRet = 0;

	CString strDebugCmd = oDebugCmd.m_strID; //获取Debug命令类型

	if(strDebugCmd == STT_CMD_TYPE_DEBUG_GetSocketConnect)
	{
		bRet = Process_Debug_GetSocketConnect(pClientSocket,oDebugCmd);
	}

	return bRet;
}

long CSttNativeClientTestEngine::Process_Debug_GetSocketConnect(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oDebugCmd);

	m_pExternEngineRef->m_oClientUserMngr.GenerateSysState(oSysState);

    return pClientSocket->XSendSysState(&oSysState);
}


void CSttNativeClientTestEngine::OnSendHeartbeatTimer()
{
	//xxy 20210522 主要解决取消注册后，NativeClient占用Test权限
	//如果没有ClientEngine权限，则释放NativeClient的Test权限
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
