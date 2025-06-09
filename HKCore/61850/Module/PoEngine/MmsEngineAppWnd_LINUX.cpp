// MmsEngineAppWnd.cpp
//

#include "stdafx.h"
#include "MmsEngineAppWnd_Linux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMmsEngineAppWnd_Linux

CMmsEngineAppWnd_Linux::CMmsEngineAppWnd_Linux()
{

}

CMmsEngineAppWnd_Linux::~CMmsEngineAppWnd_Linux()
{
	
}

BOOL CMmsEngineAppWnd_Linux::CreateWnd()
{	
	return CMmsEngineAppWnd::CreateWnd();
}

void CMmsEngineAppWnd_Linux::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
   switch (nMsgID )
    {
    case WM_OPER_ALL_DEVS_REPORT:
        OnOperAllDevsRpt(wParam, lParam);
        break;

	case WM_DISCONNECT_ALL_DEVICE:
		OnDisConnAllDev(wParam, lParam);
		break;

	case WM_READ_RCDFILE_ALL:
		OnReadRcdAllDev(wParam, lParam);
		break;

	case WM_SAVE_ALL_DEVICES_RCD_FILES:
		SaveAllMmsDevicesRcdFiles(wParam, lParam);
		break;

	case WM_Notify_Msg:
		OnMmsCmdFinish(wParam, lParam);
		break;

	case WM_MMS_REPORT:
		OnMmsReport(wParam, lParam);
		break;

	case WM_PROCEDURE_RESET:
		OnReset(wParam, lParam);
		break;

	case WM_CONNECT_ALL_DEVICE:
		OnConnectAllDevice(wParam, lParam);
		break;
   }
}

void CMmsEngineAppWnd_Linux::OnWndTimer(unsigned int nIDEvent)
{

}


