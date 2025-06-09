#include "stdafx.h"
#include "IotPxEngineDeviceWnd_Linux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIotPxEngineDeviceWnd_Linux

CIotPxEngineDeviceWnd_Linux::CIotPxEngineDeviceWnd_Linux()
{

}

CIotPxEngineDeviceWnd_Linux::~CIotPxEngineDeviceWnd_Linux()
{
}

BOOL CIotPxEngineDeviceWnd_Linux::CreateIotPxEngineDeviceWnd()
{
    return CIotPxEngineDeviceWnd::CreateIotPxEngineDeviceWnd();
}

void CIotPxEngineDeviceWnd_Linux::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
    switch (nMsgID )
    {
	case WM_PROCEDURE_END_MSG:
        OnProcedureEndMsg(wParam, lParam);
        break;

    case WM_SYSTEM_MSG:
        OnEngineSystemMessage(wParam, lParam);
        break;

    case WM_MMS_REPORT_MSG:
        OnMmsReportMessage(wParam, lParam);
        break;
    }
}

void CIotPxEngineDeviceWnd_Linux::OnWndTimer(unsigned int nIDEvent)
{
    OnTimer(nIDEvent);
}


