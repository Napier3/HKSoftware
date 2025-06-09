#include "stdafx.h"
#include "XTimer.h"

/*
CXTimerBase::CXTimerBase()
{

}

CXTimerBase::~CXTimerBase()
{

}

DWORD CXTimerBase::SetXTimer(DWORD dwTimerID,DWORD dwTimeLong)
{
	return SetTimer(dwTimerID, dwTimeLong, NULL);
}

void CXTimerBase::KillXTimer(DWORD dwTimerID)
{
	KillTimer(dwTimerID);
}

void CXTimerBase::OnTimer(unsigned int  nIDEvent)
{
	OnXTimer(nIDEvent);
}


*/


// CXTimer
#ifndef _PSX_IDE_QT_
IMPLEMENT_DYNAMIC(CXTimer, CWnd)
#endif

CXTimer::CXTimer()
{

}

CXTimer::~CXTimer()
{
}

void CXTimer::CreateXTimer()
{
#ifndef _PSX_IDE_QT_
	CreateEx(0, AfxRegisterWndClass(0), _T("_Test_Ctrl_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
#endif
}


#ifdef _PSX_IDE_QT_
void CXTimer::OnWndTimer(unsigned int nIDEvent)
{
	OnTimer(nIDEvent);
}

void CXTimer::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)//zhouhj 20211120 解决编译问题
{

}

#else
BEGIN_MESSAGE_MAP(CXTimer, CWnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()

#endif

DWORD CXTimer::SetXTimer(DWORD dwTimerID,DWORD dwTimeLong)
{
	return SetTimer(dwTimerID, dwTimeLong, NULL);
}

void CXTimer::KillXTimer(DWORD dwTimerID)
{
	KillTimer(dwTimerID);
}


void CXTimer::OnTimer(unsigned int  nIDEvent)
{
	OnXTimer(nIDEvent);
}