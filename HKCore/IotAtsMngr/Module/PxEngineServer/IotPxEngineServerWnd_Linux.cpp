#include "stdafx.h"
#include "IotPxEngineServerWnd_Linux.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIotPxEngineServerWnd_Linux

CIotPxEngineServerWnd_Linux::CIotPxEngineServerWnd_Linux()
{

}

CIotPxEngineServerWnd_Linux::~CIotPxEngineServerWnd_Linux()
{
}

BOOL CIotPxEngineServerWnd_Linux::CreateIotPxEngineServerWnd()
{
    return CIotPxEngineServerWnd::CreateIotPxEngineServerWnd();
}

void CIotPxEngineServerWnd_Linux::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
    switch (nMsgID )
    {
	case WM_IOT_CMD_MSG:
        OnIotCmd(wParam, lParam);
        break;
    }
}

void CIotPxEngineServerWnd_Linux::OnWndTimer(unsigned int nIDEvent)
{

}


