#include "XGlobalDefine_QT.h"

#include "CXCtrl_QT_CWnd.h"
#include "CWinThread_QT.h"

void ThrowInvalidArgException()
{

}

#ifdef _PSX_QT_LINUX_

#include "qfile.h"
#include "qdatetime.h"
//#include <unistd.h>

//是否使用自定义的时间对象
#ifdef USE_Custom_CDateTime
#include"CDateTime_QT.h"

long g_nTickCountSecond_First = 0;
long g_nTickCountNS_First = 0;
long GetTickCount()
{
	unsigned long nTickCount = 0;

	if ((g_nTickCountSecond_First != 0) || (g_nTickCountNS_First != 0))
	{
		long nSecond = 0,nNs = 0;
        CDateTime::GetDateTime_Zone0/*GetDateTime*/(nSecond,nNs);
		nTickCount = nSecond - g_nTickCountSecond_First;
		nTickCount *= 1000;
		nTickCount += (nNs - g_nTickCountNS_First)/1000000;
	} 
	else
	{
        CDateTime::GetDateTime_Zone0/*GetDateTime*/(g_nTickCountSecond_First,g_nTickCountNS_First);
	}

	return nTickCount;
}
#else
QDateTime g_oTickCountStartTime;
long GetTickCount()
{
    static int nFirst = 0;
    unsigned long nTickCount = 0;
    if(nFirst == 0)
    {
        nFirst++;
        g_oTickCountStartTime = QDateTime::currentDateTime();

        nTickCount = 0;
    }
    else
    {
        QDateTime oCurrTime = QDateTime::currentDateTime();
        nTickCount = g_oTickCountStartTime.msecsTo(oCurrTime);
    }

    return nTickCount;
}
#endif

#ifdef _PSX_OS_CENTOS_
#include<unistd.h>
#endif

#include <QThread>
void Sleep(long nmSecond)
{
    QThread::usleep(nmSecond * 1000);
}


char* itoa(int val, char* buf,unsigned int radix)
{
    char* p;
    unsigned int a;        //every digit
    int len;
    char* b;            //start of the digit char
    char temp;
    unsigned int u;

    p = buf;

    if (val < 0)
    {
        *p++ = '-';
        val = 0 - val;
    }

    u = (unsigned int)val;

    b = p;

    do
    {
        a = u % radix;
        u /= radix;

        *p++ = a + '0';

    } while (u > 0);

    len = (int)(p - buf);

    *p-- = 0;

    //swap
    do
    {
        temp = *p;
        *p = *b;
        *b = temp;
        --p;
        ++b;

    } while (b < p);

    return buf;
}

//
CWinThread* AfxBeginThread(CWinThread *pThread, unsigned int nPRIORITY, unsigned int nParam, unsigned int nCREATE)
{
    return pThread;
}

CWinThread* AfxBeginThread(WIN_THREAD_PROC *pfnThreadProc, LPVOID pData)
{
     CWinThread *pThread = new CWinThread(pfnThreadProc, pData);

     return pThread;
}

bool IsWindow(HWND hWnd)
{
    return hWnd != 0;
}

bool IsWindow(CWnd* hWnd)
{
	return hWnd != NULL;
}

unsigned long PostMessage(HWND hWnd, unsigned long nMsg, unsigned long wPara, unsigned long lPara)
{
    CWnd *pWnd = (CWnd*)hWnd;
    pWnd->PostMessage(nMsg, wPara, lPara);
    return 0;
}

unsigned long PostThreadMessage(unsigned long hThreadID, unsigned long nMsg, unsigned long wPara, unsigned long lPara)
{
    if (hThreadID == 0)
    {
        return 0;
    }

    CWinThread *pThread = (CWinThread*)hThreadID;
    pThread->PostThreadMessage(nMsg, wPara, lPara);

    return 0;
}

#endif
