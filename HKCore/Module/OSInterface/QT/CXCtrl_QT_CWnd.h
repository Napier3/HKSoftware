#pragma once

#include <QObject>
#include "CString_QT.h"

#ifndef _USE_NO_GUI_

#include "CXDraw_QT.h"
#include <QWidget>

#else

#include "XGlobalDefine_QT.h"
#include "CXDrawTypes_QT.h"

#endif

#include <QTimerEvent>
#include <QTimer>
#include <QThread>
#include <QMap>

#include "XMsgCycleBuffer.h"
#include "../XWndInterface.h"

// #ifndef _USE_NO_GUI_
// #ifndef QT_Wnd_USE_QWIDGET
// #define QT_Wnd_USE_QWIDGET
// #endif
// #endif

//lijunqing 2020-11-6 message
#ifdef QT_Wnd_USE_QWIDGET
class CWnd : public QWidget, public CXWndInterface
#else
class CWnd : public QObject, public CXMsgCycleBuffer, public CXWndInterface
#endif
{
    Q_OBJECT
public:
	virtual unsigned int XSetTimer(unsigned int nIDEvent, unsigned int nElapse, void* pFunc)
	{
		return SetTimer(nIDEvent, nElapse, pFunc);
	}
	virtual BOOL XKillTimer(unsigned int nIDEvent)
	{
		return KillTimer(nIDEvent);
	}
	virtual void XPostMessage(unsigned int nMsgID, unsigned long wParam=0, unsigned long  lParam=0)
	{
		PostMessage(nMsgID, wParam, lParam);
	}

public:
#ifdef QT_Wnd_USE_QWIDGET
	CWnd(QWidget *parent = NULL);
#else
    CWnd();
#endif

//#ifdef QT_Wnd_USE_QWIDGET
private:
    // 存储定时器ID的列表：key=nIDEvent；value=startTimer的返回值
        QMap<int, int> timerIds;
//#endif

public:
     virtual ~CWnd();

	 CWnd *m_hWnd;

public:

    static CWnd* FromHandle(HWND hWnd);
    static CWnd* GetDesktopWindow();

#ifndef _USE_NO_GUI_
    virtual CDC* GetDC();
    virtual void ReleaseDC(CDC *pDC);

    QWidget *m_pWidgetRef;
    virtual void InvalidateRect(CRect *pRect, BOOL b);
    virtual void InvalidateRect(CRect &rect, BOOL b);
    virtual void Invalidate(BOOL b);
    virtual void GetClientRect(CRect &rc);
    virtual void GetClientRect(CRect *pRect);
#endif

    virtual void SetCapture();
    virtual void ReleaseCapture();
    virtual void ClientToScreen(CRect *pRect);
    virtual void SetWindowText(const CString &strText);
    virtual unsigned int SetTimer(unsigned int nIDEvent, UINT nElapse, LPVOID pFunc);
    virtual BOOL KillTimer(unsigned int nIDEvent);
    virtual void KillAllTimers();
    virtual BOOL IsTimerExist(unsigned int nIDEvent);   //通过key判断
    virtual BOOL IsTimerExist2(int nTimer);  //通过value判断
    virtual int GetTimerID(int nTimer);//通过value，返回Key
    virtual BOOL DestroyWindow();
    virtual unsigned long GetSafeHwnd();

    virtual void PostMessage(unsigned int nMsgID, unsigned long wParam=0, unsigned long  lParam=0);

	//message
protected:
    bool m_bClose;

public:
    //重载函数OnWndMsg，实现消息处理
    virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam) = 0;
    virtual void OnWndTimer(unsigned int nIDEvent) = 0;

protected:
//#ifndef QT_Wnd_USE_QWIDGET
    //virtual void run();
//#endif


//#ifdef QT_Wnd_USE_QWIDGET
signals:
	void sig_AddMessage(unsigned long nMsgID, unsigned long wParam, unsigned long lParam);

public slots:
	void slot_ExecMessage(unsigned long nMsgID, unsigned long wParam, unsigned long lParam);

public:
    virtual void timerEvent( QTimerEvent * );
//#endif
};



