#include "stdafx.h"
#include "CXCtrl_QT_CWnd.h"
#include "../../API/StringApi.h"

#ifdef QT_Wnd_USE_QWIDGET
CWnd::CWnd(QWidget *parent): QWidget(parent)
{
	connect(this, SIGNAL(sig_AddMessage(unsigned long, unsigned long, unsigned long)),this, SLOT(slot_ExecMessage(unsigned long, unsigned long, unsigned long)),Qt::QueuedConnection);
}
#else
CWnd::CWnd()
{
#ifndef _USE_NO_GUI_
	m_pWidgetRef = NULL;
#endif
    connect(this, SIGNAL(sig_AddMessage(unsigned long, unsigned long, unsigned long)),this, SLOT(slot_ExecMessage(unsigned long, unsigned long, unsigned long)),Qt::QueuedConnection);
	m_hWnd = this;
    m_bClose = false;
    //start();
}
#endif


CWnd::~CWnd()
{
	//等待线程退出后，再析构
	//shaolei 2022-12-05
//#ifndef QT_Wnd_USE_QWIDGET
//	while (true)
//	{
//		if (isFinished())
//		{
//			break;
//		}

//		usleep(5000);
//	}
//#else
    KillAllTimers();
//#endif
}

#ifndef _USE_NO_GUI_
CDC* CWnd::GetDC()
{
	if (m_pWidgetRef == NULL)
	{
		return NULL;
	}

	CDC *pNewDC = new CDC(m_pWidgetRef);
	pNewDC->begin(m_pWidgetRef);

    return pNewDC;
}

void CWnd::ReleaseDC(CDC *pDC)
{
	if (pDC == NULL)
	{
		return;
	}

	pDC->end();
	delete pDC;
}
#endif

void CWnd::SetCapture()
{

}
void CWnd::ReleaseCapture()
{

}

void CWnd::ClientToScreen(CRect *pRect)
{

}

void CWnd::SetWindowText(const CString &strText)
{
// 	if (m_pWidgetRef != NULL)
// 	{
// 		m_pWidgetRef->setText(strText);
// 	}
}

CWnd* CWnd::FromHandle(HWND hWnd)
{
    return (CWnd*)hWnd;
}

CWnd* CWnd::GetDesktopWindow()
{
    return NULL;
}

unsigned int CWnd::SetTimer(unsigned int nIDEvent, UINT nElapse, LPVOID pFunc)
{
//#ifdef QT_Wnd_USE_QWIDGET
    //emit sig_AddMessage(WM_TIMER, nIDEvent, nElapse);
    if(IsTimerExist(nIDEvent))
    {
        return nIDEvent;
    }

    int nID = startTimer(nElapse);
    timerIds.insert(nIDEvent, nID);
// #else
//    AddMsg(WM_TIMER, nIDEvent, nElapse);
// #endif
    return nIDEvent;
}

BOOL CWnd::KillTimer(unsigned int nIDEvent)
{
//#ifndef QT_Wnd_USE_QWIDGET
//    RemoveMsg(WM_TIMER, nIDEvent);
//#else
    if(IsTimerExist(nIDEvent))
    {
        timerIds.remove(nIDEvent);
        killTimer(nIDEvent);
        //QWidget::killTimer(nIDEvent);
    }
//#endif
    return 0;
}

void CWnd::KillAllTimers()
{
    int nTimerID = -1;

    for (QMap<int, int>::const_iterator it = timerIds.constBegin(); it != timerIds.constEnd(); ++it) {
        nTimerID = it.key();
        killTimer(nTimerID);
       // QWidget::killTimer(nTimerID);
    }

    timerIds.clear();
}

BOOL CWnd::IsTimerExist(unsigned int nIDEvent)
{
    if(timerIds.size() == 0)
        return FALSE;

    return timerIds.contains(nIDEvent);
}

BOOL CWnd::IsTimerExist2(int nTimer)
{
    if(timerIds.size() == 0)
        return FALSE;

    for (QMap<int, int>::const_iterator it = timerIds.constBegin(); it != timerIds.constEnd(); ++it)
    {
        if(nTimer == it.value())
        {
            return TRUE;
        }
    }

    return FALSE;
}

 int CWnd::GetTimerID(int nTimer)
 {
     if(!IsTimerExist2(nTimer))
         return -1;

     for (QMap<int, int>::const_iterator it = timerIds.constBegin(); it != timerIds.constEnd(); ++it)
     {
         if(nTimer == it.value())
         {
             return it.key();
         }
     }

     return -1;
 }

BOOL CWnd::DestroyWindow()
{
    //2020-11-22 lijunqing
    PostMessage(WM_CLOSE, 0, 0);
    m_bClose = true;
 /*
    long nCount = 0;
    stop();

    while (nCount <= 4000)
    {
        if (isFinished())
        {
            break;
        }
        else
        {
            usleep(5000);
        }

        nCount++;
    }
*/
    return TRUE;
}

unsigned long CWnd::GetSafeHwnd()
{
    return (unsigned long)this;
}

#ifndef _USE_NO_GUI_
void CWnd::InvalidateRect(CRect *pRect, BOOL b)
{
	if (m_pWidgetRef != NULL)
	{
		m_pWidgetRef->updateGeometry();
	}
}

void CWnd::InvalidateRect(CRect &rect, BOOL b)
{
	InvalidateRect(&rect, b);
}

void CWnd::Invalidate(BOOL b)
{
	if (m_pWidgetRef != NULL)
	{
		m_pWidgetRef->updateGeometry();
	}
}

void CWnd::GetClientRect(CRect &rc)
{
	rc.left = 0;
	rc.top = 0;

	if (m_pWidgetRef == NULL)
	{
		rc.bottom = 600;
		rc.right = 800;
	}
	else
	{
		//QRect frameGeometry() const;
		//const QRect &geometry() const;
		//QRect normalGeometry() const;
		QRect rc1 = m_pWidgetRef->geometry();
		rc.bottom = rc1.height();
		rc.right = rc1.width();
	}
}

void CWnd::GetClientRect(CRect *pRect)
{
	GetClientRect(*pRect);
}
#endif

void CWnd::PostMessage(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
//#ifdef QT_Wnd_USE_QWIDGET
	 emit sig_AddMessage(nMsgID, wParam, lParam);
//#else
//    AddMsg(nMsgID, wParam, lParam);
//#endif
}

//#ifndef QT_Wnd_USE_QWIDGET
//void CWnd::run()
//{
//    unsigned long nMsg, wParam,  lParam;

//    while (true)
//    {
//        if (isFinished())
//        {
//            break;
//        }

//        if (m_bClose)
//        {
//            break;
//        }

//        if (PeekMsg(nMsg, wParam, lParam))
//        {
//            if (WM_CLOSE == nMsg)
//            {
//                break;
//            }

//            if (WM_TIMER == nMsg)
//            {//nMsgID==WM_TIMER; wParam=nIDEvent
//                OnWndTimer(wParam);
//                continue;
//            }

//            OnWndMsg(nMsg, wParam, lParam);
//        }
//        else
//        {
//            usleep(5000);
//        }
//    }

//    //2020-11-22 lijunqing debug for breakpoint
//    int i=10;
//    i = 100;
//}
//#endif

//#ifdef QT_Wnd_USE_QWIDGET
void CWnd::slot_ExecMessage( unsigned long nMsgID, unsigned long wParam, unsigned long lParam )
{
	if (WM_CLOSE == nMsgID)
	{
        //this->close();
		return;
	}

	if (WM_TIMER == nMsgID)
	{
		OnWndTimer(wParam);
		return;
	}

	OnWndMsg(nMsgID, wParam, lParam);
}

void CWnd::timerEvent( QTimerEvent *event )
{
    int nID = GetTimerID(event->timerId());

    if(nID == -1)
        return;

    OnWndTimer(nID);
     //QWidget::timerEvent(event);
}

//#endif




