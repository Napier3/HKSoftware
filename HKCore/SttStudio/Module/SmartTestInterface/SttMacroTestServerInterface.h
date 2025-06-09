#pragma once

#include "MacroTestInterface.h"
#include "../SttCmd/SttTestCmd.h"

#define STT_MACROTEST_MSG_CONNECT       (WM_USER + 2110)
#define STT_MACROTEST_MSG_BEGIN         (WM_USER + 2111)
#define STT_MACROTEST_MSG_FINISH        (WM_USER + 2112)
#define STT_MACROTEST_MSG_STOP          (WM_USER + 2113)
#define STT_MACROTEST_MSG_EXCEPTION     (WM_USER + 2114)
#define STT_MACROTEST_MSG_EVENT         (WM_USER + 2115)
#define STT_MACROTEST_MSG_RTDATA        (WM_USER + 2116)

#define STT_VMSERVER_MSG_RCVCMD         (WM_USER + 2117)
#define STT_MACROTEST_MSG_CONFIGDEVICE  (WM_USER + 2118)
#define STT_MACROTEST_TIMER_ID_READMEAS   (WM_USER + 2119)
#define STT_MACROTEST_TIMER_ID_JUDGEERR   (WM_USER + 2120)

class CSttMacroTestServerInterface
{
public:
	CSttMacroTestServerInterface()	{		};
	virtual ~CSttMacroTestServerInterface(void){};

	CString m_strCurrTestMacroID;

public:
	virtual void PostVmServerRcvCmd(CSttCmmOptrInterface *pCmmOptrInterface, CSttTestCmd *pTestCmd) = 0;
	virtual long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID) = 0;

	virtual long TestCmd_ConfigDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas) = 0;
	virtual long TestCmd_ConnectDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas) = 0;
	virtual long TestCmd_CloseDevice(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas) = 0;
	virtual long TestCmd_SetParameter(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro) = 0;
	virtual long TestCmd_UpdateParameter(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro) = 0;
	virtual long TestCmd_StartTest(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro) = 0;
	virtual long TestCmd_StopTest(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas) = 0;
	virtual long TestCmd_GetReport(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttMacro *pSttMacro) = 0;
	virtual long TestCmd_GetSystemState(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas) = 0;
	virtual long TestCmd_TriggerTest(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas) = 0;
	virtual long TestCmd_FinishInputData(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pSttParas) = 0;

	virtual BOOL IsTestFinished(DWORD dwPara) = 0;
	virtual BOOL IsConnectSuccess() = 0;

	virtual long GetEvents(CDataGroup *pSttParas) = 0;
	virtual long GetRtDatas(CDataGroup *pSttParas) = 0;
	virtual long GetExceptions(CDataGroup *pSttParas) = 0;

};

/*
测试完成	TestFinished	上传测试报告数据
测试开始	TestStarted	测试开始
测试停止	TestStoped	测试停止
搜索点测试报告	SearchPointReport	上送搜索线的测试中间事件
联机成功	ConnectSuccess	
联机失败	ConnectFailed	
*/
//测试功能事件接口
class CSttMacroTestEventServerInterface
{
public:
	CSttMacroTestEventServerInterface(){}
	virtual ~CSttMacroTestEventServerInterface(){}

public:
	virtual void OnTestState_Reply(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttCmdData *pParas, long nExecStaus, char *pszEventID, char *pszRetCmdType){ }
	virtual void OnTestState_Reply(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;
	virtual void OnTestState_Report(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;
	virtual void OnTestState_Exception(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;
	
	virtual void OnTestEvent_ExecCmd(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;
	virtual void OnTestEvent_ConnectSuccess(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;
	virtual void OnTestEvent_ConnectFailed(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;
	virtual void OnTestEvent_TestStarted(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;
	virtual void OnTestEvent_TestFinished(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;
	virtual void OnTestEvent_TestStoped(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;
	virtual void OnTestEvent_SearchPointReport(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas) = 0;

};

