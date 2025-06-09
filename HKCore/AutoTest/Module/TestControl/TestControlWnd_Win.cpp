// D:\WorkPM\Source\PMTest\Module\TestControlWnd_Win.cpp : 实现文件
//

#include "stdafx.h"
#include "TestControlWnd_Win.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestControlWnd_Win
IMPLEMENT_DYNAMIC(CTestControlWnd_Win, CWnd)

CTestControlWnd_Win::CTestControlWnd_Win()
{

}

CTestControlWnd_Win::~CTestControlWnd_Win()
{
}

BOOL CTestControlWnd_Win::CreateTestControlWnd()
{
#ifndef _PSX_QT_LINUX_
	CreateEx(0, AfxRegisterWndClass(0), _T("_Test_Ctrl_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
#endif

	return CTestControlWnd::CreateTestControlWnd();
}

BEGIN_MESSAGE_MAP(CTestControlWnd_Win, CWnd)
	ON_MESSAGE(WM_ELECTRIC_TEST, &CTestControlWnd::OnElectricTestMsg)
	ON_MESSAGE(WM_COMM_COMMAND, &CTestControlWnd::OnCommCommandMsg)
	ON_MESSAGE(WM_SAFETY_TEST_FINISHED, &CTestControlWnd::OnSafetyTestFinished)
	ON_MESSAGE(WM_SYSPARAEDIT_TEST_FINISHED, &CTestControlWnd::OnSysParaEditTestFinished)
	ON_MESSAGE(WM_COMMCMD_TEST_FINISHED, &CTestControlWnd::OnCommCmdMamualTestFinished)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MANUAL_TEST, &CTestControlWnd::OnManualTestMsg)
	ON_MESSAGE(WM_ENGINE_SYSTEM_MSG, &CTestControlWnd::OnEngineSystemMessage)
	ON_MESSAGE(WM_TIMER_TRIGGER, &CTestControlWnd::OnTimerTrigger)
	ON_MESSAGE(WM_ENGINE_EVENT_MSG, &CTestControlWnd::OnEngineEventMessage)
END_MESSAGE_MAP()
