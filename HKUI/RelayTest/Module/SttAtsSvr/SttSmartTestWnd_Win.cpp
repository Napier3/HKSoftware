// D:\WorkPM\Source\PMTest\Module\SttSmartTestWnd_Win.cpp : 实现文件
//

#include "stdafx.h"
#include "SttSmartTestWnd_Win.h"
#include "../../../AutoTest/Module/GuideBook/ReportMap/WordRptExportBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSttSmartTestWnd_Win
IMPLEMENT_DYNAMIC(CSttSmartTestWnd_Win, CWnd)

CSttSmartTestWnd_Win::CSttSmartTestWnd_Win()
{

}

CSttSmartTestWnd_Win::~CSttSmartTestWnd_Win()
{
}

BOOL CSttSmartTestWnd_Win::CreateSttSmartTestWnd()
{
	CreateEx(0, AfxRegisterWndClass(0), _T("_SttSmartTest_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);

	return CSttSmartTestWnd::CreateSttSmartTestWnd();
}

BEGIN_MESSAGE_MAP(CSttSmartTestWnd_Win, CWnd)
	ON_MESSAGE(WM_STT_CREATETEST,&CSttSmartTestWnd::OnSttCreateTest)
	ON_MESSAGE(WM_STT_CREATETEST_EX,&CSttSmartTestWnd::OnSttCreateTestEx)
	ON_MESSAGE(WM_STT_CREATETEST_BY_CMD,&CSttSmartTestWnd::OnSttCreateTestByCmd)
	ON_MESSAGE(WM_STT_CLOSETEST,&CSttSmartTestWnd::OnSttCloseTest)
	ON_MESSAGE(WM_STT_BEGINETEST,&CSttSmartTestWnd::OnSttBegineTest)
	ON_MESSAGE(WM_STT_STOPTEST,&CSttSmartTestWnd::OnSttStopTest)
	ON_MESSAGE(WM_STT_FINISHINPUTDATA,&CSttSmartTestWnd::OnSttFinishInputData)
	ON_MESSAGE(WM_STT_OPENGBRPTFILE,&CSttSmartTestWnd::OnSttOpenGbrptFile)
	ON_MESSAGE(WM_STT_ADJUSTMAINWND,&CSttSmartTestWnd::OnSttAdjustMainWnd)
	ON_MESSAGE(WM_STT_EXPORTREPORT,&CSttSmartTestWnd::OnSttExportReport)
	ON_MESSAGE(WM_STT_FREETESTCONTROL,&CSttSmartTestWnd::OnSttFreeTestControl)
	ON_MESSAGE(WM_STT_TESTPOINT,&CSttSmartTestWnd::OnSttTestPoint)
	ON_MESSAGE(WM_STT_TESTBELOW,&CSttSmartTestWnd::OnSttTestBelow)
	ON_MESSAGE(WM_STT_TESTALLINLEGIBLEITEMS,&CSttSmartTestWnd::OnSttTestAllInlegibleItems)
	ON_MESSAGE(WM_STT_ADJUSTREPORT,&CSttSmartTestWnd::OnSttAdjustReport)
	ON_MESSAGE(WM_STT_CREATEDEVICEREFS,&CSttSmartTestWnd::OnSttCreateDeviceRefs)
	ON_MESSAGE(WM_STT_SENDTESTCMD,&CSttSmartTestWnd::OnSttSendTestCmd)
	ON_MESSAGE(WM_STT_GENWORDRPT_BYTOOL,&CSttSmartTestWnd::OnSttGenWordReport)
	ON_MESSAGE(WM_STT_CLEARREPORTSRSLTS,&CSttSmartTestWnd::OnSttClearReportsRslts)
	ON_MESSAGE(WM_EXPORT_REPORT_WORD,&CSttSmartTestWnd::OnExportReport)
	ON_MESSAGE(WM_ATS_CREATETEST,&CSttSmartTestWnd::OnCreateTest)
	ON_MESSAGE(WM_STT_RELEASEPPENGINE,&CSttSmartTestWnd::OnSttReleasePpEngine)
	ON_MESSAGE(WM_STT_CONNECTSTTSERVER_19814,&CSttSmartTestWnd::OnConnectSttServer_19814)
END_MESSAGE_MAP()

