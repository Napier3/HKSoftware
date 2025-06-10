#include "stdafx.h"
#include "SttTestServerEngine.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>	//SIGIO
#include <sys/syscall.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int g_nOnTimerMs=1000;//��ʱ��ʱ��������λ����
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#include "QDebug"
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
		//CSttTestServerBase����������Ϊprotected���ڴ�ֱ��ɾ�����﷨����
		//���Խ�����ָ��ǿ��ת��ΪCSttTestServerEngine��Ȼ����ɾ��
		//delete g_pSttTestServerEngine;
		CSttTestServerEngine *pTestServer = (CSttTestServerEngine*)g_pSttTestServerEngine;
		delete pTestServer;

		g_pSttTestServerEngine = NULL;
	}
}


CSttTestServerEngine::CSttTestServerEngine()
{
	//g_pSttTestEngine = this;
#ifdef _PSX_QT_LINUX_
	g_nOnTimerMs=CSttDeviceBase::g_pSttDeviceBase->m_nOnTimerMs;
#endif
}

CSttTestServerEngine::~CSttTestServerEngine()
{
	m_bRunTimer = FALSE;
}

void CSttTestServerEngine::OnSendCmdFinish(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{

}

void CSttTestServerEngine::OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID)
{

}

volatile long nTestFinishTick = 0;
void SigCallBack(int sig)
{
	BOOL bIsTestFinish=CSttServerTestCtrlCntr::EventProcess();
	if(bIsTestFinish)
	{
		nTestFinishTick++;
	}
}

void CSttTestServerEngine::OnCallBackTimer()
{
	if(nTestFinishTick)
	{
		nTestFinishTick = 0;
	CSttServerTestCtrlCntr::ProcessTestFinish();
	}
}

void CSttTestServerEngine::Init(int fd)
{
#ifdef _PSX_QT_LINUX_
	signal(SIGIO,SigCallBack);
	fcntl(fd,F_SETOWN,getpid());
	int oflags=0;
	oflags=fcntl(fd,F_GETFL);
	fcntl(fd,F_SETFL,oflags|FASYNC);
#endif

    //ignor SIGPIPE (send error after socket disconnect)
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGPIPE);
    sigprocmask(SIG_BLOCK,&set,NULL);

	// m_pServerTimer=new QTimer;
	// connect(m_pServerTimer,SIGNAL(timeout()),this,SLOT(OnServerTimer()));
	// m_pServerTimer->start(g_nOnTimerMs);

	m_bRunTimer = TRUE;
	pthread_t nthreadid;
	int nRet = pthread_create(&nthreadid, NULL, TimerThread, (LPVOID)this);
	if(nRet == 0)
	{
		qDebug() << ">>>>>>Create TestServerEngine_TimerThread";
	}
}

void *TimerThread(LPVOID pParam)
{
	CSttTestServerEngine *pTestServerEngine = (CSttTestServerEngine*)pParam;
	while(pTestServerEngine->m_bRunTimer)
	{
		for(int i = 0;i < g_nOnTimerMs;i++)
		{
			usleep(1000);
		}

		pTestServerEngine->OnTimer();
	}

	pthread_exit(0);
}

// void CSttTestServerEngine::OnServerTimer()
// {
// 	//2021-05-21  zhoulei
// 	//CSttTestServerBase::OnTimer()ִ�й����в�������ʱ�ж�,��ֹ�ж϶ѻ�
// 	m_pServerTimer->stop();

// 	CSttTestServerBase::OnTimer();
// 	m_pServerTimer->start(g_nOnTimerMs);
// }
