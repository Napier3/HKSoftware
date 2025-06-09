#include "stdafx.h"
#include "CXCtrl_QT_CWnd_T.h"
#include "../../API/StringApi.h"

CWindows::CWindows(QObject *parent) //: QObject(pParent)
{
    QObject::connect(this,     SIGNAL(WndMsg(unsigned int, unsigned long, unsigned long ))
                     ,this,     SLOT(WndMsgReceiver(unsigned int, unsigned long, unsigned long)));
    //QObject::connect(this, &CWindows::WndMsg, this, &CWindows::WndMsgReceiver);
}

CWindows::~CWindows()
{

}

#ifndef _USE_NO_GUI_
CDC* CWindows::GetDC()
{
    return NULL;
}

void CWindows::ReleaseDC(CDC *pDC)
{

}
#endif

void CWindows::SetCapture()
{

}
void CWindows::ReleaseCapture()
{

}

void CWindows::ClientToScreen(CRect *pRect)
{

}

void CWindows::SetWindowText(const CString &strText)
{

}

CWindows* CWindows::FromHandle(HWND hWnd)
{
    return (CWindows*)hWnd;
}

CWindows* CWindows::GetDesktopWindow()
{
    return NULL;
}

unsigned int CWindows::SetTimer(unsigned int nIDEvent, UINT nElapse, LPVOID pFunc)
{
    return 0;
}

BOOL CWindows::KillTimer(unsigned int nIDEvent)
{
    return 0;
}

BOOL CWindows::DestroyWindow()
{
    return TRUE;
}

unsigned long CWindows::GetSafeHwnd()
{
    return (unsigned long)this;
}

BOOL CWindows::PostMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    emit WndMsg(message, wParam, lParam);
    return TRUE;
}

void CWindows::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{

}

void CWindows::WndMsgReceiver(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
    OnWndMsg(nMsgID, wParam, lParam);
}


CWindowsEx g_otheWindows;

CWindowsEx::CWindowsEx()
{

}

CWindowsEx::~CWindowsEx()
{

}

//重载函数OnWndMsg，实现消息处理
void CWindowsEx::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{

}
