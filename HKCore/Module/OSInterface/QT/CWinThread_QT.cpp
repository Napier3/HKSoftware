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

#ifdef _PSX_QT_LINUX_
#include<unistd.h>
#endif

void CWinThread::run()
{
    unsigned long nMsg, wParam,  lParam;

    while (true)
    {
        if (isFinished())
        {//�ж��Ƿ����
            break;
        }

        if (m_pfnThreadProc != NULL)
        {//����Ǻ����̣߳���ִ�к���������ִ�н����������߳�
            (m_pfnThreadProc)(m_pParam);
            break;
        }

        if (PeekMsg(nMsg, wParam, lParam))
        {//��ȡ��Ϣ
            if (WM_QUIT == nMsg)
            {//������߳̽�����Ϣ��������߳�
                break;
            }

            //�ַ��߳���Ϣ
            OnThreadMsg(nMsg, wParam, lParam);
        }
        else
        {//���û����Ϣ������ʱ5ms
            //usleep(5000);
#ifdef _PSX_QT_LINUX_

#ifdef _PSX_OS_CENTOS_
            usleep(5000);
#else
            ::usleep(5000);//zhouhj ��LINUX��ʹ��::usleep�������gettimeofdayϵͳ����
#endif

#else
            usleep(5000);
#endif
        }
    }

    if (m_pfnThreadProc != NULL)
    {//����ģʽ��ɾ������
        if (m_bAutoDelete)
        {
            delete this;
        }
    }
    else
    {//�߳�ģʽ������ExitInstance����
        ExitInstance();
    }
}


