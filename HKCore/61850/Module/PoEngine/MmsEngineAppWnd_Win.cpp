// MmsEngineAppWnd.cpp
//

#include "stdafx.h"
#include "MmsEngineAppWnd_Win.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMmsEngineAppWnd_Win
IMPLEMENT_DYNAMIC(CMmsEngineAppWnd_Win, CWnd)

CMmsEngineAppWnd_Win::CMmsEngineAppWnd_Win()
{

}

CMmsEngineAppWnd_Win::~CMmsEngineAppWnd_Win()
{
	
}

BOOL CMmsEngineAppWnd_Win::CreateWnd()
{
	CreateEx(0, AfxRegisterWndClass(0), _T("_MmsEngineAppWnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
	
	return CMmsEngineAppWnd::CreateWnd();
}

BEGIN_MESSAGE_MAP(CMmsEngineAppWnd_Win, CWnd)
	ON_MESSAGE(WM_OPER_ALL_DEVS_REPORT, &CMmsEngineAppWnd_Win::OnOperAllDevsRpt)
	ON_MESSAGE(WM_DISCONNECT_ALL_DEVICE, &CMmsEngineAppWnd_Win::OnDisConnAllDev)
	ON_MESSAGE(WM_READ_RCDFILE_ALL,&CMmsEngineAppWnd_Win::OnReadRcdAllDev)
	ON_MESSAGE(WM_SAVE_ALL_DEVICES_RCD_FILES,&CMmsEngineAppWnd_Win::SaveAllMmsDevicesRcdFiles)
	ON_MESSAGE(WM_Notify_Msg, &CMmsEngineAppWnd_Win::OnMmsCmdFinish)
	ON_MESSAGE(WM_MMS_REPORT, &CMmsEngineAppWnd_Win::OnMmsReport)
	ON_MESSAGE(WM_PROCEDURE_RESET, &CMmsEngineAppWnd_Win::OnReset)
	ON_MESSAGE(WM_CONNECT_ALL_DEVICE, &CMmsEngineAppWnd_Win::OnConnectAllDevice)
END_MESSAGE_MAP()

