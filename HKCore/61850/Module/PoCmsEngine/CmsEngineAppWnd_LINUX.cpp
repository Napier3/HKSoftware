// CmsEngineAppWnd.cpp
//

#include "stdafx.h"
#include "CmsEngineAppWnd_Linux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCmsEngineAppWnd_Linux

CCmsEngineAppWnd_Linux::CCmsEngineAppWnd_Linux()
{

}

CCmsEngineAppWnd_Linux::~CCmsEngineAppWnd_Linux()
{
	
}

BOOL CCmsEngineAppWnd_Linux::CreateWnd()
{	
	return CCmsEngineAppWnd::CreateWnd();
}

void CCmsEngineAppWnd_Linux::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	switch (nMsgID )
	{
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

void CCmsEngineAppWnd_Linux::OnWndTimer(unsigned int nIDEvent)
{

}


