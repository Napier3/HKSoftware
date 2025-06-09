// D:\WorkPM\Source\PMTest\Module\IotPxEngineServerWnd_Win.cpp : 实现文件
//

#include "stdafx.h"
#include "IotPxEngineServerWnd_Win.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIotPxEngineServerWnd_Win
IMPLEMENT_DYNAMIC(CIotPxEngineServerWnd_Win, CWnd)

CIotPxEngineServerWnd_Win::CIotPxEngineServerWnd_Win()
{

}

CIotPxEngineServerWnd_Win::~CIotPxEngineServerWnd_Win()
{
}

BOOL CIotPxEngineServerWnd_Win::CreateIotPxEngineServerWnd()
{
	CreateEx(0, AfxRegisterWndClass(0), _T("IotPxEngineServerWnd_Win"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);

	return CIotPxEngineServerWnd::CreateIotPxEngineServerWnd();
}

BEGIN_MESSAGE_MAP(CIotPxEngineServerWnd_Win, CWnd)
	ON_MESSAGE(WM_IOT_CMD_MSG, &CIotPxEngineServerWnd_Win::XOnIotCmd)
END_MESSAGE_MAP()

LRESULT CIotPxEngineServerWnd_Win::XOnIotCmd(WPARAM wParam, LPARAM lParam)
{
	return OnIotCmd(wParam, lParam);
}

