// D:\WorkPM\Source\PMTest\Module\TestControlWnd_Linux.cpp : 实现文件
//

#include "stdafx.h"
#include "TestControlWnd_Linux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestControlWnd_Linux

CTestControlWnd_Linux::CTestControlWnd_Linux()
{

}

CTestControlWnd_Linux::~CTestControlWnd_Linux()
{
}

BOOL CTestControlWnd_Linux::CreateTestControlWnd()
{
    return CTestControlWnd::CreateTestControlWnd();
}

void CTestControlWnd_Linux::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
    switch (nMsgID )
    {
    case WM_ELECTRIC_TEST:
        OnElectricTestMsg(wParam, lParam);
        break;

    case WM_COMM_COMMAND:
        OnCommCommandMsg(wParam, lParam);
        break;

    case WM_SAFETY_TEST_FINISHED:
        OnSafetyTestFinished(wParam, lParam);
        break;

    case WM_SYSPARAEDIT_TEST_FINISHED:
        OnSysParaEditTestFinished(wParam, lParam);
        break;

    case WM_COMMCMD_TEST_FINISHED:
        OnCommCmdMamualTestFinished(wParam, lParam);
        break;

    case WM_MANUAL_TEST:
        OnManualTestMsg(wParam, lParam);
        break;

    case WM_ENGINE_SYSTEM_MSG:
        OnEngineSystemMessage(wParam, lParam);
        break;

    case WM_TIMER_TRIGGER:
        OnTimerTrigger(wParam, lParam);
        break;
    }
}

void CTestControlWnd_Linux::OnWndTimer(unsigned int nIDEvent)
{
    OnTimer(nIDEvent);
}


