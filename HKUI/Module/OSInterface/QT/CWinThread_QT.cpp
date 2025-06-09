#include "stdafx.h"
#include "CWinThread_QT.h"
#include "../../API/StringApi.h"

#include "CString_QT.h"

CWinThread::CWinThread()
{
    m_pfnThreadProc = NULL;
    m_pParam = NULL;
    m_bAutoDelete = TRUE;
    //connect(&m_oXMsgTimer_Post,SIGNAL(timeout()),this,SLOT(On_XMsgTimer_Post()));
}

CWinThread::CWinThread(WIN_THREAD_PROC *pfnThreadProc, void *pParam)
{
    m_pfnThreadProc = pfnThreadProc;
    m_pParam = pParam;
    m_bAutoDelete = TRUE;
}

void CWinThread::WaitThreadExit()
{
	PostThreadMessage(WM_QUIT, 0, 0);
	wait();
}

void CWinThread::PostThreadMessage(unsigned long nMsg, unsigned long wParam, unsigned long lParam)
{
    AddMsg(nMsg, wParam, lParam);
    //m_oXMsgTimer_Post.start(50);
}

void CWinThread::OnThreadMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{

}

void CWinThread::ResumeThread()
{
    start();
}

int CWinThread::ExitInstance()
{
    return 0;
}


void CWinThread::run()
{
    unsigned long nMsg, wParam,  lParam;

    while (true)
    {
        if (isFinished())
        {//判断是否结束
            break;
        }

        if (m_pfnThreadProc != NULL)
        {//如果是函数线程，则执行函数，函数执行结束，结束线程
            (m_pfnThreadProc)(m_pParam);
            break;
        }

        if (PeekMsg(nMsg, wParam, lParam))
        {//获取消息
            if (WM_QUIT == nMsg)
            {//如果是线程结束消息，则结束线程
                break;
            }

            //分发线程消息
            OnThreadMsg(nMsg, wParam, lParam);
        }
        else
        {//如果没有消息，则延时5ms
            usleep(5000);
        }
    }

    if (m_pfnThreadProc != NULL)
    {//函数模式：删除自身
        if (m_bAutoDelete)
        {
            delete this;
        }
    }
    else
    {//线程模式，调用ExitInstance函数
        ExitInstance();
    }
}


