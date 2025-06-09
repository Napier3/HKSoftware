#pragma once

#include <QObject>
#include "CString_QT.h"

#ifndef _USE_NO_GUI_

#include "CXDraw_QT.h"

#else

#include "XGlobalDefine_QT.h"
#include "CXDrawTypes_QT.h"

#endif

//lijunqing 2020-11-6 message
class CWindows : public QObject
{
   Q_OBJECT

public:
    //CWindows();
    explicit CWindows(QObject *parent=0);
     ~CWindows();

public:

    static CWindows* FromHandle(HWND hWnd);
    static CWindows* GetDesktopWindow();

#ifndef _USE_NO_GUI_
    virtual CDC* GetDC();
    virtual void ReleaseDC(CDC *pDC);
#endif

    virtual void SetCapture();
    virtual void ReleaseCapture();
    virtual void ClientToScreen(CRect *pRect);
    virtual void SetWindowText(const CString &strText);
    virtual unsigned int SetTimer(unsigned int nIDEvent, UINT nElapse, LPVOID pFunc);
    virtual BOOL KillTimer(unsigned int nIDEvent);
    virtual BOOL DestroyWindow();
    virtual unsigned long GetSafeHwnd();

    BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);

    //message
public:
    //重载函数OnWndMsg，实现消息处理
    virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);

public slots:
    void WndMsgReceiver(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);

signals:
    void WndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);

private:


signals:

public slots:

};


class CWindowsEx : public CWindows
{
public:
    CWindowsEx();
    ~CWindowsEx();

public:
    //重载函数OnWndMsg，实现消息处理
    virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);

};
