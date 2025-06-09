#pragma once

#include "../SttAuthority/SttTestRemoteRegister.h"
#include "../SttSocket/TestTerminal/SttClientSocketBase.h"
#include "../SttSocket/TestServer/SttTestServerSocketBase.h"
#include "../SttSocket/TestServer/VC/SttNativeRemoteClientSocket.h"

#include "SttTestEngineServerBase.h"
#include "SttNativeClientTestEngine.h"

class CSttNativeRemoteTestEngine : public CSttTestEngineServerBase
{
private:
	CSttNativeRemoteTestEngine();
	virtual ~CSttNativeRemoteTestEngine();

	static CSttNativeRemoteTestEngine* g_pNativeTestEngine;
	static long g_nNativeTestEngineRef;

public:
	static CSttNativeRemoteTestEngine* Create(const char *pszIP, int nPort);
	static void Release();
	static CSttNativeRemoteTestEngine* GetNativeTestEngine();

public:
	//2020-4-6  lijq
	virtual void InitSttServerEngine(const char *pszIP, int nPort);
	virtual void ExitSttServerEngine();

	virtual void OnSocketClose(CSttSocketDataBase *pSocket);
	virtual long SendSysState(CSttSysState *pSysState);
	virtual BOOL OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet);

	virtual BOOL SendBufferToChildren(CSttSocketDataBase *pExceptSocket,BYTE *pBuf,long nLen);	
	virtual long Process_Cmd_System_Request(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Authority(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Register(CSttSysState &oSysState);
	virtual long Process_SysState_UnRegister(CSttSysState &oSysState);
	virtual long Process_SysState_InputData(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState);

	//收到测试命令，先检查是否有权限，无权限则返回失败
	BOOL CheckBeforeProcessCmdTest(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	//本地Ats和远程登录
	virtual long Process_Cmd_System_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Logout(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	//退出登录或断链，检查是否停止测试
	virtual void CheckStopTestAfterReleaseUser();
	//只检测具有单机测试权限的测试端心跳超时
	virtual void CheckHeartbeatOverTime();

public:
	CSttTestRemoteRegister m_oRemoteRegister;
	CSttNativeRemoteClientSocket *m_pSttCloudClientSocket;//云端socket

	//本机测试端引擎
    CSttNativeClientTestEngine  *m_pNativeClientTestEngine;

    //SmartTest  目前只处理但装置的测试
    CSttSmartTest *m_pSmartTest;
	
public:
	virtual long ConnectCloudServer(const CString &strIPServer,long nPort);
	void DisConnectCloudServer();
	virtual long Register(CSttCmdData *pRetData=NULL);
	virtual long UnRegister(CSttCmdData *pRetData=NULL);
	
	//用于超时处理逻辑
	virtual long SendCmd(CSttCmdBase *pCmd,long nTimeOut=3000,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	//用于超时处理逻辑
	virtual long SendCmdSync(CSttCmdBase *pCmd,long nTimeOut=-1,CSttCmdData *pRetData=NULL,BOOL bDoEvents=TRUE);
	

public:
	void InitClientUserMngr();
	void AttachSttAtsInterface(CSttAtsInterface *pSttAtsInterface){	m_pSttAtsInterface = pSttAtsInterface;	}
	void AttachRefAtsUser(CSttTestClientUser *pRefAtsUser);

	BOOL AuthorityToAtsUser(CSttSystemCmd &oSysCmd,CSttTestClientUser *pUser);
	BOOL AuthorityToTestUser(CSttSystemCmd &oSysCmd,CSttTestClientUser *pUser);
	virtual long AuthorityToUser(CSttSystemCmd &oSysCmd,BOOL bRequest,BOOL bBroadcastWhenSuccess=TRUE);
	virtual long AuthorityToRefAtsUser(long nAtsAuthority,BOOL bRequest);
	BOOL IsCanAuthorityToRefAtsUser(long nAtsAuthority,BOOL bRequest);

	CSttTestClientUser* User_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);

	//如果没有ClientEngine权限，则释放NativeClient的Test权限
	long CheckCancelNativeClientAuthority();

	//如果没有Ats权限，则释放TestControl的ClientEngine权限
	long CheckUpdateTestControlAuthority();

private:
	//自动测试权限用户，与远程单机测试竞争ClientEngine权限
	CSttTestClientUser m_oTestControlUser;

	//TestMain界面测试用户，无界面时为NULL
	//ID_Terminal=STT_TERMINAL_TYPE_NATIVE_ATS为自动测试界面用户，
	//否则为STT_TERMINAL_TYPE_NATIVE_TEST为单机测试界面用户
	CSttTestClientUser *m_pRefAtsUser;

//2020-11-25  lijunqing
public:
    void OnTimer();

};

extern CSttNativeRemoteTestEngine *g_theNativeTestEngine;
