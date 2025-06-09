#pragma once

#include "../../../AutoTest/Module/TCtrlCntrDefine.h"
#include "../../../AutoTest/Module/SmartTestDefineInterface.h"
#include "SttSmartTest.h"

#ifndef _PSX_IDE_QT_
#include "../../Module/System/TimeTrigger.h"
#endif

class CSttSmartTestMsgInterface
{
public:
	virtual void X_OnSttCreateTest(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttCloseTest(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttBegineTest(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttStopTest(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttOpenGbrptFile(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttAdjustMainWnd(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttExportReport(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttFreeTestControl(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttTestPoint(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttTestBelow(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttTestAllInlegibleItems(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttAdjustReport(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttCreateDeviceRefs(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttSendTestCmd(CTestControlBase *pTestControl, CSttTestCmd *pTestCmd) = 0;
	virtual void X_OnSttGenWordReport(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
	virtual void X_OnSttClearReportsRslts(CTestControlBase *pTestControl, CSttSmartTest *pSmartTest) = 0;
};

class CSttSmartTestWnd : public CWnd
{
public:
	CSttSmartTestWnd();
	virtual ~CSttSmartTestWnd();
	CSttSmartTestMsgInterface *m_pSmartTestMsgInterface;
	CTestControlBase *m_pMainTestControl;
	
	virtual BOOL CreateSttSmartTestWnd();
	virtual void SetTestControl(CExBaseObject *pTestControl);

public:
	LRESULT OnSttCreateTest(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttCreateTestEx(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttCreateTestByCmd(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttCloseTest(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttBegineTest(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttStopTest(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttFinishInputData(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttOpenGbrptFile(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttAdjustMainWnd(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttExportReport(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttFreeTestControl(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttTestPoint(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttTestBelow(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttTestAllInlegibleItems(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttAdjustReport(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttCreateDeviceRefs(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttSendTestCmd(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttGenWordReport(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttClearReportsRslts(WPARAM wParam, LPARAM lParam);
	LRESULT OnExportReport(WPARAM wParam, LPARAM lParam);
	LRESULT OnCreateTest(WPARAM wParam, LPARAM lParam);
	LRESULT OnSttReleasePpEngine(WPARAM wParam, LPARAM lParam);
    LRESULT OnConnectSttServer_19814(WPARAM wParam, LPARAM lParam);


public:
	virtual long X_OnSttCreateTest(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttCreateTestEx(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttCreateTestByCmd(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttCloseTest(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttBegineTest(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttStopTest(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttFinishInputData(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttOpenGbrptFile(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttAdjustMainWnd(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttExportReport(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttFreeTestControl(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttTestPoint(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttTestBelow(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttTestAllInlegibleItems(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttAdjustReport(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttCreateDeviceRefs(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttSendTestCmd(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttGenWordReport(WPARAM wParam, LPARAM lParam);
	virtual long X_OnSttClearReportsRslts(WPARAM wParam, LPARAM lParam);
	virtual long X_OnExportReport(WPARAM wParam, LPARAM lParam);

};

//shaolei 2024-3-14 改为配置文件
// #define  MARCO_ID_MACRO_MUAccuracyTest             "MUAccuracyTest"
// //#define  MARCO_ID_MACRO_MUZeroDriftTest            "MUZeroDriftTest"
// #define  MARCO_ID_MACRO_MUTimingAccurTest          "MUTimingAccurTest"
// #define  MARCO_ID_MACRO_MUPunctAccurTest           "MUPunctAccurTest"
// #define  MARCO_ID_MACRO_MUFirstCycleTest           "MUFirstCycleTest"
// #define  MARCO_ID_MACRO_MUMaxPeakErrorTest         "MUMaxPeakErrorTest"
// #define  MARCO_ID_MACRO_MUAttenConstantTest        "MUAttenConstantTest"
// #define  MARCO_ID_MACRO_MUAccurAutoTest             "MUAccurAutoTest"
// #define  MARCO_ID_MACRO_MUAutoTest                   "MUAutoTest" //2023-10-24 lcq
// #define  MARCO_ID_MACRO_SoeTest                      "SoeTest"
// #define  MARCO_ID_MACRO_ShortTimeOverTest           "ShortTimeOverTest"
// #define  MARCO_ID_MACRO_LineDiffCurr6ITest          "LineDiffCurr6ITest"
// #define  MARCO_ID_MACRO_BusDiffCurr6ITest           "BusDiffCurr6ITest"

// BOOL IsMuTest();
BOOL IsMacroTest_CanUseAutoTest();
