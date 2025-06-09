#pragma once

#include "SttTestEngineServerBase.h"
#include "../SttSocket/SttServerSocketDataBase.h"
#include "../SttTestBase/SttXmlSerialize.h"
#include "SttServerTestCtrlCntr.h"

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_IDE_QT_
#include "QT/SttMqttEngine.h"
#include "QMutex"
#else
#endif
#endif

extern BOOL g_bRtDataLock;

class CSttTestServerBase : public  CSttTestEngineServerBase
{
public:
	static CSttTestServerBase* GetServerEngine()  {   return g_pSttTestServerEngine;  }

protected:
    static long m_nSttTestServerEngineRef;
    static CSttTestServerBase *g_pSttTestServerEngine;

protected:
    CSttTestServerBase();
    virtual ~CSttTestServerBase();

	void Ret_SysState(CSttSysState &oSysState, CSttXcmdChInterface *pSttSocketDataBase, CSttXmlSerializeTool &oSttXmlSerializeTool);
	void Ret_Cmd_SysState(CSttCmdBase &oCmd, CSttXcmdChInterface *pSttSocketDataBase, CSttXmlSerializeTool &oSttXmlSerializeTool);

public:
    virtual long XSendSysState(CSttSysState *pSysState);

	virtual long Process_Heartbeat(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Trigger(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Test(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_System(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	virtual long Process_Cmd_Comtrade(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_SendDataFinish(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Comtrade_SendDataStart(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	virtual long Process_Cmd_Adjust(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_System(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Debug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
	virtual long Process_SysState_Debug(CSttXcmdChInterface *pClientSocket, CSttSysState &oSysState);

    //收到测试命令，先检查是否有权限，无权限则返回失败
	BOOL CheckBeforeProcessCmdTest(CSttXcmdChInterface *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

    //退出登录或断链，检查是否停止测试
	virtual void CheckStopTestAfterRelease(CSttXcmdChInterface *pClientSocket);
public:
    CSttTestCmd m_oSttTestCmd;

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_IDE_QT_
	CSttMqttEngine m_oMqttEngine;
#else
#endif
#endif

public:
    CSttTestClientUser *GetNativeClientUser();
	CSttXcmdChInterface *GetNativeClientSocket();
    virtual void InitSttServerEngine(const char *pszIP, int nTestPort,int nReplayPort = 0);
    virtual void ExitSttServerEngine();
	virtual void OnTimer();
	virtual void OnTimer_RtDataEvent();
	virtual void OnTimer_CheckHeartbeat();
    //只检测具有单机测试权限的测试端心跳超时
    virtual void CheckHeartbeatOverTime();

    void ReturnTestStateEvent(long nEventType, PSTT_TIME pTime, bool bWithEvent);
    void ReturnTestEvents();
    void ReturnSysStatesToChildren(int nDataType);

protected:
    //2020-04-6  lijq
	void Ret_Test_SysState(CSttSysState &oSysState, CSttXcmdChInterface *pSttSocketDataBase
                           , BOOL bBasic, BOOL bParas, BOOL bReport, BOOL bSearchResult
                           , PSTT_TIME pTime, bool bWithEvent);//zhouhj 20210925 增加搜索点
	void Ret_Test_SysState(CSttSysState &oSysState, CSttXcmdChInterface *pSttSocketDataBase
                           , BOOL bBasic, BOOL bParas, BOOL bReport, BOOL bSearchResult
                           , char *strRetType, PSTT_TIME pTime, bool bWithEvent);
	void Ret_Test_SysState(CSttSysState &oSysState, CSttXcmdChInterface *pSttSocketDataBase
						   , BOOL bBasic, BOOL bParas, BOOL bReport , BOOL bSearchResult
                           , const CString &strRetType, PSTT_TIME pTime, bool bWithEvent);
	long ReturnSysState(long nCmdExecStatus,CSttCmdData *pRetData=NULL);

    //2021-03-12 zhoulei
    void ReturnTestParaCheckFail();
protected:
    virtual long Process_Cmd_Test_SetParameter(CSttXmlSerializeTool &oSttXmlSerializeTool);
    virtual long Process_Cmd_Test_UpdateParameter(CSttXmlSerializeTool &oSttXmlSerializeTool);
    virtual long Process_Cmd_Test_StartTest(CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Test_StopTest(BOOL bReturnAsk=TRUE);
    virtual long Process_Cmd_Test_CloseDevice();

public:
	virtual long Process_Cmd_Test_GetReport(BOOL bParas=TRUE);
    virtual long Process_Debug_GetProcessState(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_GetMemState(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_GetTestParas(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_GetTestReports(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_GetBasicTestParas(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_GetBasicReportData(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_GetDrvTestData(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_GetDrvReportData(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_GetFpgaData(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_GetSocketConnect(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);
    virtual long Process_Debug_ConfigDebug(CSttXcmdChInterface *pClientSocket, CSttDebugCmd &oDebugCmd);

    virtual long Process_Cmd_System_ReadMeas(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_GetSystemState(CSttXcmdChInterface *pClientSocket, CSttSystemCmd &oSysCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
    //校准命令处理
	virtual long Process_Cmd_Adjust_Adjust(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Ajust_ReadDeviceParameter(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
    virtual long Process_Cmd_Ajust_WriteFile(CSttXcmdChInterface *pClientSocket, CSttAdjustCmd &oAdjustCmd);
    //测试仪主动请求故障回放数据
    long Comtrade_SendRequestData(long nIndex);

    //测试仪应答发送数据开始
    long Comtrade_SendDataStartAck(long nIndex);
    //接收线程接收完数据后，主动搬移数据后SttReplayTest处理逻辑
	void OnAfterMoveToComtradeBuf(int nIndex,int nDataLen);

    void StopAutoTestEvent();  //返回停止自动测试事件
};


//extern CSttServerTestCtrlCntr  *g_pTestCtrlEngine;
