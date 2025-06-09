// D:\WorkPM\Source\PMTest\Module\SttSmartTestWnd_Linux.cpp : 实现文件
//

#include "stdafx.h"
#include "SttSmartTestWnd_Linux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSttSmartTestWnd_Linux

CSttSmartTestWnd_Linux::CSttSmartTestWnd_Linux()
{

}

CSttSmartTestWnd_Linux::~CSttSmartTestWnd_Linux()
{
}

BOOL CSttSmartTestWnd_Linux::CreateSttSmartTestWnd()
{
    return CSttSmartTestWnd::CreateSttSmartTestWnd();
}

void CSttSmartTestWnd_Linux::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
    switch (nMsgID )
    {
    case WM_STT_BEGINETEST:
        OnSttBegineTest(wParam, lParam);
        break;

    case WM_STT_CREATETEST:
        OnSttCreateTest(wParam, lParam);
        break;

    case WM_STT_CREATETEST_EX:
       OnSttCreateTestEx(wParam, lParam);
        break;

    case WM_STT_CREATETEST_BY_CMD:
        OnSttCreateTestByCmd(wParam, lParam);
        break;

    case WM_STT_CLOSETEST:
        OnSttCloseTest(wParam, lParam);
        break;

    case WM_STT_STOPTEST:
        OnSttStopTest(wParam, lParam);
        break;

    case WM_STT_OPENGBRPTFILE:
        OnSttOpenGbrptFile(wParam, lParam);
        break;

    case WM_STT_FREETESTCONTROL:
        OnSttFreeTestControl(wParam, lParam);
        break;

    case WM_STT_TESTPOINT:
        OnSttTestPoint(wParam, lParam);
        break;

    case WM_STT_TESTBELOW:
        OnSttTestBelow(wParam, lParam);
        break;

    case WM_STT_TESTALLINLEGIBLEITEMS:
        OnSttTestAllInlegibleItems(wParam, lParam);
        break;

    case WM_STT_CREATEDEVICEREFS:
        OnSttCreateDeviceRefs(wParam, lParam);
        break;

    case WM_STT_SENDTESTCMD:
        OnSttSendTestCmd(wParam, lParam);
        break;

    case WM_STT_CLEARREPORTSRSLTS:
        OnSttClearReportsRslts(wParam, lParam);
        break;

    case WM_STT_RELEASEPPENGINE:
        OnSttReleasePpEngine(wParam, lParam);
        break;

    case WM_STT_CONNECTSTTSERVER_19814:
        OnConnectSttServer_19814(wParam, lParam);
        break;
    }
}

void CSttSmartTestWnd_Linux::OnWndTimer(unsigned int nIDEvent)
{
    //OnTimer(nIDEvent);
}


