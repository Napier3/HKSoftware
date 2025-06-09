// CmsEngineAppWnd.cpp
//

#include "stdafx.h"
#include "CmsEngineAppWnd_Win.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCmsEngineAppWnd_Win
IMPLEMENT_DYNAMIC(CCmsEngineAppWnd_Win, CWnd)

CCmsEngineAppWnd_Win::CCmsEngineAppWnd_Win()
{

}

CCmsEngineAppWnd_Win::~CCmsEngineAppWnd_Win()
{
	
}

BOOL CCmsEngineAppWnd_Win::CreateWnd()
{
	CreateEx(0, AfxRegisterWndClass(0), _T("_CmsEngineAppWnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
	
	return CCmsEngineAppWnd::CreateWnd();
}

BEGIN_MESSAGE_MAP(CCmsEngineAppWnd_Win, CWnd)
	ON_MESSAGE(WM_SAVE_ALL_DEVICES_RCD_FILES,&CCmsEngineAppWnd_Win::SaveAllMmsDevicesRcdFiles)
	ON_MESSAGE(WM_Notify_Msg, &CCmsEngineAppWnd_Win::OnMmsCmdFinish)
	ON_MESSAGE(WM_MMS_REPORT, &CCmsEngineAppWnd_Win::OnMmsReport)
	ON_MESSAGE(WM_PROCEDURE_RESET, &CCmsEngineAppWnd_Win::OnReset)
	ON_MESSAGE(WM_CONNECT_ALL_DEVICE, &CCmsEngineAppWnd_Win::OnConnectAllDevice)
END_MESSAGE_MAP()

