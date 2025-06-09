#include "stdafx.h"
#include "SttTestServerEngine.h"
#include "../../Module/OSInterface/OSInterface.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include <sys/syscall.h>
#include "../../SttSocket/SttCmdOverTimeMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#include "../../SttDevice/Module/FpgaUart/FpgaUart.h"
#include "QDebug"
#include "pthread.h"
#endif

CSttTestServerEngine* CSttTestServerEngine::Create(int fd, char *pszIP, int nTestPort,int nReplayPort)
{
	m_nSttTestServerEngineRef++;

	if (m_nSttTestServerEngineRef == 1)
	{
		CSttTestServerEngine *pSttTestServerEngine = new CSttTestServerEngine();
		g_pSttTestServerEngine = pSttTestServerEngine;
		pSttTestServerEngine->Init(fd);
        pSttTestServerEngine->InitSttServerEngine(pszIP, nTestPort,nReplayPort);
	}

	return (CSttTestServerEngine*)g_pSttTestServerEngine;
}

void CSttTestServerEngine::Release()
{
	m_nSttTestServerEngineRef--;

	if (m_nSttTestServerEngineRef == 0)
	{
		//CSttTestServerBase的析构函数为protected，在此直接删除有语法错误
		//所以将基类指针强制转换为CSttTestServerEngine，然后再删除
		//delete g_pSttTestServerEngine;
		CSttTestServerEngine *pTestServer = (CSttTestServerEngine*)g_pSttTestServerEngine;
		delete pTestServer;

		g_pSttTestServerEngine = NULL;
	}
}


CSttTestServerEngine::CSttTestServerEngine()
{

}

CSttTestServerEngine::~CSttTestServerEngine()
{
	m_bRunThread = FALSE;
}

void CSttTestServerEngine::OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{

}

void CSttTestServerEngine::OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{

}

void SigCallBack(int nSigNum)
{
	CSttServerTestCtrlCntr::EventProcessEx();
}

void CSttTestServerEngine::Init(int fd)
{
#ifdef _PSX_QT_LINUX_
	fcntl(fd,F_SETOWN,getpid());
	int oflags=0;
	oflags=fcntl(fd,F_GETFL);
	fcntl(fd,F_SETFL,oflags|FASYNC);
#endif
	signal(SIGIO,SigCallBack);

    //ignor SIGPIPE (send error after socket disconnect)
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGPIPE);
    sigprocmask(SIG_BLOCK,&set,NULL);

	m_bRunThread = TRUE;
	pthread_t nthreadid;
	int nRet = pthread_create(&nthreadid, NULL, ProTimerThread, (LPVOID)this);
	if(nRet == 0)
	{
		qDebug() << ">>>>>>Create TestServerEngine_ProTimerThread";
	}
}

void *ProTimerThread(LPVOID pParam)
{
	pthread_setname_np(pthread_self(),"TimerThread");
	CSttTestServerEngine *pTestServerEngine = (CSttTestServerEngine*)pParam;
	long nCount =0;
	while(pTestServerEngine->m_bRunThread)
	{
		Sleep(50);
		pTestServerEngine->OnTimer();
		pTestServerEngine->OnTimer_RtDataEvent();
		CSttCmdOverTimeTool::ProcessTimeOutProc_Attach();
		nCount++;
		if(nCount > 20)
		{
			nCount = 0;
			pTestServerEngine->OnTimer_CheckHeartbeat();
		}
	}

	pthread_exit(0);
}
