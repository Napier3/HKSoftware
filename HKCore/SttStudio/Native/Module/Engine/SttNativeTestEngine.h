#pragma once

#include "../SttAuthority/SttTestRemoteRegister.h"
#include "../SttSocket/TestTerminal/SttClientSocketBase.h"
#include "../SttSocket/TestServer/SttTestServerSocketBase.h"
#include "../SttSocket/TestServer/VC/SttNativeRemoteClientSocket.h"

#include "SttTestEngineServerBase.h"
#include "SttNativeClientTestEngine.h"

#include "SttNativeTestEngineInterface.h"


class CSttNativeTestEngine : public CSttTestEngineServerBase, public CSttNativeTestEngineInterface
{
public:
    virtual void OnCommCmdMessage(WPARAM wParam, LPARAM lParam);
    virtual void OnSysMessage(WPARAM wParam, LPARAM lParam);
    //2020-11-24  lijunqing LINUX  post msg to ats
    virtual void OnEngineDataDeleted(const CString &strDeviceID);

public:	//CSttPkgDispatchInterface
	//2022-2-12  lijunqing
	virtual void DispatchMsg(unsigned char *pBuf, long nLen);

public: //CSttNativeTestEngineInterface
	virtual long X_ReturnSysStateToChildren(void *pCommInterface, CSttSysState *pSysState) ;
	virtual long X_Ats_InputData(void *pCommInterface, CDataGroup *pDatas,CExBaseList *pMsgs) ;

private:
	CSttNativeTestEngine();
	virtual ~CSttNativeTestEngine();

	static CSttNativeTestEngine* g_pNativeTestEngine;
	static long g_nNativeTestEngineRef;

public:
	static CSttNativeTestEngine* Create(const CString &strConfigFile, CSttSmartTest *pSttSmartTest);
	static CSttNativeTestEngine* Create(const char *pszIP, int nPort, CSttSmartTest *pSttSmartTest);
	static void Release();
	static CSttNativeTestEngine* GetNativeTestEngine();

public:
	//2020-4-6  lijq
	virtual void InitSttServerEngine(const char *pszIP, int nPort,int nReplayPort=0);
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
	BOOL CheckBeforeProcessCmdAts(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

    // 2020-05-27  shaolei  add    设置云测试
    virtual long ProcessCmd_CloudTest(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	//本地Ats和远程登录
	virtual long Process_Cmd_System_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Logout(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd);
	//退出登录或断链，检查是否停止测试
	virtual void CheckStopTestAfterReleaseUser();
	//只检测具有单机测试权限的测试端心跳超时
	virtual void CheckHeartbeatOverTime();
	
public:
    //2020-5-18  lijunqing
	virtual long Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
    virtual long Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);

	//2022-4-20 shaolei lijunq 
	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	//当前自动测试命令
	CSttAtsCmd m_oSttAtsCmd;
	long ReturnExecReply(CSttCmdBase *pCmd, long nCmdExecStatus,CSttCmdData *pRetData=NULL);

protected:
    CDvmDataset* Ats_GetDataset(CSttAtsCmd &oAtsCmd);
     long Ats_SetDataset(CSttAtsCmd &oAtsCmd);
     long Ats_ConfigDevice(CSttAtsCmd &oAtsCmd);

    long Process_Cmd_Ats_CreateTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_StartTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_StopTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_CloseTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_TestItem(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_TestFrom(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_TestAllFailedItems(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetItemReport(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetReportFile(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetSystemState(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_CreateDevice(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ConnectDevice(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_ConfigDevice(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetDataset(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_SetDataset(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_RunProcedure(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_CloseDevice(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_ConfigEngine(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);

	long Process_Cmd_Ats_FinishInputData(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_QueryAtsFile(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_SetItemState(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GenerateTemplate(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_GenerateItems(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_GenerateMacroTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_SetItemPara(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Procss_Cmd_Ats_SetItemPara_SystemConfig(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_ManualTrigger(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_SaveTemplate(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_SaveTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ExportWordRpt(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_OpenTemplate(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_OpenGbrptFile(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_AdjustMainWnd(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ExportReport(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_QueryItem(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_UpdateItem(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_AdjustReport(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ClearReportsRslts(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);


    void Return_Ats_Success(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd, unsigned int nState=STT_CMD_ExecStatus_SUCCESS, CDvmDataset *pDatas=NULL, CExBaseObject *pGuideBook = NULL);
    void Return_NoDevice(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
    void Return_Ats_Event(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
    long ValidateSmartTest(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	//shaolei 20220326 
	void Return_DeviceParameter_AfterLogin(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

public:
	CSttTestRemoteRegister m_oRemoteRegister;
	CSttNativeRemoteClientSocket *m_pSttCloudClientSocket;//云端socket

	//本机测试端引擎
    CSttNativeClientTestEngine  *m_pNativeClientTestEngine;

    //SmartTest  目前只处理但装置的测试
    CSttSmartTest *m_pSmartTest;
	void SetSttSmartTest(CSttSmartTest *pSmartTest)	{	m_pSmartTest = pSmartTest;	}
	
public:
	virtual long ConnectCloudServer(const CString &strIPServer,long nPort);
	void DisConnectCloudServer();
    BOOL IsConnectColudServerSuccess();
	virtual long Register(CSttCmdData *pRetData=NULL);
	virtual long UnRegister(CSttCmdData *pRetData=NULL);
	virtual long Ats_InputData(CSttSocketDataBase *pClientSocket,CDataGroup *pDatas,CExBaseList *pMsgs);
	
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
	//测试控制管理接口，对于有界面的TestMain，由界面启动，对于没有界面的TestMain,由TestMainCore启动
	CSttAtsInterface *m_pSttAtsInterface;

	//自动测试权限用户，与远程单机测试竞争ClientEngine权限
	CSttTestClientUser m_oTestControlUser;

	//TestMain界面测试用户，无界面时为NULL
	//ID_Terminal=STT_TERMINAL_TYPE_NATIVE_ATS为自动测试界面用户，
	//否则为STT_TERMINAL_TYPE_NATIVE_TEST为单机测试界面用户
	CSttTestClientUser *m_pRefAtsUser;

//2020-11-25  lijunqing
public:
    virtual void OnTimer();

};

extern CSttNativeTestEngineInterfaces *g_theNativeTestEngine;
extern CSttTestAppCfg *g_pTheSttTestAppCfg ;
