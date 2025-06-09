#pragma once

/*
	功能描述：自动测试的接口App
*/
#include "AtsRpc\AtsRpcServerGlobalApi.h"

#include "SmartTestInterface.h"
#include "AutoTestGlobalDefine.h"

//////////////////////////////////////////////////////////////////////////
//CSmartTestInterfaceApp

class CSmartTestInterfaceApp : public CWinAppEx
{
public:
	CSmartTestInterfaceApp();
	virtual ~CSmartTestInterfaceApp();

public:
	BOOL InitSmartTestAp();
	void ExitSmartTestApp();

	SmartTest::CTestAppMngr GetTestAppMngr();
	CAtsRpcTestDefine* GetAtsRpcTestDefine()		{	return &m_oAtsRpcTestDefine;	}

protected:
	SmartTest::CTestAppMngr m_oTestAppMngr;
	CAtsRpcTestDefine m_oAtsRpcTestDefine;

public:
	//以下返回值为long的函数，返回值为0，标识执行成功，否则返回非零值。 //shaolei  20210512
	long CreateTest(const CString &strTestID);
	long BeginTest(const CString &strTestID);
	long StopTest(const CString &strTestID);
	long Retest(const CString &strTestID, const CString &strCommConfig);
	long ExportRpt(const CString &strTestID);
	long CloseTest(const CString &strTestID);
	long ViewItemRpt(const CString &strTestID, long nDeviceIndex, long nItemIndex);
	long TestAllInlegibleItems(const CString &strTestID);
	long TestPoint(const CString &strTestID, long nDeviceIndex);
	long TestBelow(const CString &strTestID, long nDeviceIndex);
	long OpenGbrptFile(const CString &strFilePath, long nDeviceIndex=-1);  //默认参数 -1 表示测两台装置
	CString GetAllTestItems(const CString &strTestID);
	CString GetTestItemReports(const CString &strTestID);
	long SetAppVisible(long nVisible);
};

extern CSmartTestInterfaceApp *g_theSmartTestInterfaceApp;

//////////////////////////////////////////////////////////////////////////
//
class CSmartTestEventMsg
{
public:
	CSmartTestEventMsg(const CString &strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, const CString &strItemID, const CString &strState)
	{
		m_strTestID = strTestID;
		m_nDeviceIndex = nDeviceIndex;
		m_nReportIndex = nReportIndex;
		m_nItemIndex = nItemIndex;
		m_strItemID = strItemID;
		m_strState = strState;
	}
	virtual ~CSmartTestEventMsg(){}

public:
	CString m_strTestID;
	LONG   m_nDeviceIndex;
	LONG   m_nReportIndex;
	LONG   m_nItemIndex;
	CString m_strItemID;
	CString m_strState;
};

#define  WM_SMARTTEST_EVENT_SINK   (WM_USER + 1527)

#define SMARTTEST_EVENT_OnOpenGbrptFileFailed   8
#define SMARTTEST_EVENT_OnTestCreated			7
#define SMARTTEST_EVENT_OnEngineEvent			6
#define SMARTTEST_EVENT_OnTestAppEvent			5
#define SMARTTEST_EVENT_OnExportRptFinished	4
#define SMARTTEST_EVENT_OnTestStoped				3
#define SMARTTEST_EVENT_OnTestFinished			2
#define SMARTTEST_EVENT_OnItemStateChanged	1

LONG TES_OnItemStateChanged(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState);
LONG TES_OnTestFinished(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG TES_OnTestStoped(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG TES_OnExportRptFinished(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG TES_OnTestAppEvent(CWnd *pWnd, LPCTSTR strTestID, LPCTSTR strEvent);
LONG TES_OnEngineEvent(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent);
LONG TES_OnTestCreated(CWnd *pWnd, LPCTSTR strTestID);
LONG TES_OnOpenGbrptFileFailed(CWnd *pWnd, LPCTSTR strTestID);

//shaolei  20210511  为防止不同线程中调用相同COM接口失败，增加以下函数
LONG TES_OnItemStateChanged(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState);
LONG TES_OnTestFinished(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG TES_OnTestStoped(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG TES_OnExportRptFinished(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG TES_OnTestAppEvent(CWinThread *pThread, LPCTSTR strTestID, LPCTSTR strEvent);
LONG TES_OnEngineEvent(CWinThread *pThread, LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent);
LONG TES_OnTestCreated(CWinThread *pThread, LPCTSTR strTestID);
LONG TES_OnOpenGbrptFileFailed(CWinThread *pThread, LPCTSTR strTestID);