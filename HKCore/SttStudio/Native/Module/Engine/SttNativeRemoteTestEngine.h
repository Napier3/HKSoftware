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

	//�յ���������ȼ���Ƿ���Ȩ�ޣ���Ȩ���򷵻�ʧ��
	BOOL CheckBeforeProcessCmdTest(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	//����Ats��Զ�̵�¼
	virtual long Process_Cmd_System_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Logout(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	//�˳���¼�����������Ƿ�ֹͣ����
	virtual void CheckStopTestAfterReleaseUser();
	//ֻ�����е�������Ȩ�޵Ĳ��Զ�������ʱ
	virtual void CheckHeartbeatOverTime();

public:
	CSttTestRemoteRegister m_oRemoteRegister;
	CSttNativeRemoteClientSocket *m_pSttCloudClientSocket;//�ƶ�socket

	//�������Զ�����
    CSttNativeClientTestEngine  *m_pNativeClientTestEngine;

    //SmartTest  Ŀǰֻ����װ�õĲ���
    CSttSmartTest *m_pSmartTest;
	
public:
	virtual long ConnectCloudServer(const CString &strIPServer,long nPort);
	void DisConnectCloudServer();
	virtual long Register(CSttCmdData *pRetData=NULL);
	virtual long UnRegister(CSttCmdData *pRetData=NULL);
	
	//���ڳ�ʱ�����߼�
	virtual long SendCmd(CSttCmdBase *pCmd,long nTimeOut=3000,BOOL bCompress=FALSE,BOOL bReset=TRUE);
	//���ڳ�ʱ�����߼�
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

	//���û��ClientEngineȨ�ޣ����ͷ�NativeClient��TestȨ��
	long CheckCancelNativeClientAuthority();

	//���û��AtsȨ�ޣ����ͷ�TestControl��ClientEngineȨ��
	long CheckUpdateTestControlAuthority();

private:
	//�Զ�����Ȩ���û�����Զ�̵������Ծ���ClientEngineȨ��
	CSttTestClientUser m_oTestControlUser;

	//TestMain��������û����޽���ʱΪNULL
	//ID_Terminal=STT_TERMINAL_TYPE_NATIVE_ATSΪ�Զ����Խ����û���
	//����ΪSTT_TERMINAL_TYPE_NATIVE_TESTΪ�������Խ����û�
	CSttTestClientUser *m_pRefAtsUser;

//2020-11-25  lijunqing
public:
    void OnTimer();

};

extern CSttNativeRemoteTestEngine *g_theNativeTestEngine;
