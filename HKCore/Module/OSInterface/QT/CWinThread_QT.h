#ifndef _CWinThread_QT_qt_h__
#define _CWinThread_QT_qt_h__

#include <QThread>

#include "XMsgCycleBuffer.h"

typedef unsigned int (WIN_THREAD_PROC)(void*);

class CWinThread : public QThread, public CXMsgCycleBuffer
{
public:
    CWinThread();
    CWinThread(WIN_THREAD_PROC *pfnThreadProc, void *pParam);
    virtual ~CWinThread()
    {
    }

	void WaitThreadExit();

    WIN_THREAD_PROC *m_pfnThreadProc;
    void *m_pParam;

    bool m_bAutoDelete;

    void PostThreadMessage(unsigned long nMsg, unsigned long wParam, unsigned long lParam);
    virtual void ResumeThread();
    virtual int ExitInstance();

public:
    //重载函数OnWndMsg，实现消息处理
    virtual void OnThreadMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);

protected:
    virtual void run();

};


#endif   //_CWinThread_QT_qt_h__
