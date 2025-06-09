//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestClientSingleTimer.cpp

#include "../SttTestClientSingleTimer.h"
#include "../SttTestClientBase.h"

long g_nSttTestClientSingleTimerLong = 1000;
#define QT_STT_TEST_CLIENT_SIGLE_TIMER_ID  10001

#include <QObject>  
#include <QTimer>

class CSttTestClientSingleTimer : public CWnd
{  
	//Q_OBJECT

public:  
        CSttTestClientSingleTimer();


	~CSttTestClientSingleTimer()
	{
                //delete m_pTimer;
	}

//	void StopSttTimer()
//	{
//                //m_pTimer->stop();
//	}

        void KillTestTimer(unsigned int  nTimerID)
            {
                    ASSERT (nTimerID == QT_STT_TEST_CLIENT_SIGLE_TIMER_ID);
                    KillTimer(nTimerID);
        }
         virtual  void OnWndTimer(unsigned int nIDEvent)
        {
            if(nIDEvent == QT_STT_TEST_CLIENT_SIGLE_TIMER_ID)
            {
                //下发心跳
                if(m_pClient != NULL)
                {
                    m_pClient->Test_SendHeartbeat();
                }
            }
        }
        virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam) {}

public:
        CSttTestClientBase *m_pClient;
//	public slots:
//		void handleTimeout()//超时处理函数
//		{
//			stt_test_singleclient_timer(QT_STT_TEST_CLIENT_SIGLE_TIMER_ID, 0);
//		}

//private:
        //QTimer *m_pTimer;
};  

CSttTestClientSingleTimer::CSttTestClientSingleTimer()
{
//	m_pTimer = new QTimer(this);
//	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
//	m_pTimer->start(g_nSttTestClientSingleTimerLong);
    m_pClient = NULL;
}

CSttTestClientSingleTimer *g_theSttTestClientSingleTimer = NULL;

long stt_test_singleclient_timer_create(long nTimerLong)
{
	g_nSttTestClientSingleTimerLong = nTimerLong;

	if (g_theSttTestClientSingleTimer == NULL)
	{
            g_theSttTestClientSingleTimer = new CSttTestClientSingleTimer();
	}

         g_theSttTestClientSingleTimer->SetTimer(QT_STT_TEST_CLIENT_SIGLE_TIMER_ID, nTimerLong, NULL);

	return QT_STT_TEST_CLIENT_SIGLE_TIMER_ID;
}

void stt_test_singleclient_timer_free(long nTimerID)
{
	if (nTimerID == QT_STT_TEST_CLIENT_SIGLE_TIMER_ID)
	{

	}

	if (g_theSttTestClientSingleTimer != NULL)
	{
                g_theSttTestClientSingleTimer->KillTestTimer(nTimerID);
                g_theSttTestClientSingleTimer->DestroyWindow();

		delete g_theSttTestClientSingleTimer;
		g_theSttTestClientSingleTimer = NULL;
	}
}

void stt_test_singleclient_timer_attactclient(CSttTestClientBase *pClient)
{
    if(g_theSttTestClientSingleTimer == NULL)
        return;

    g_theSttTestClientSingleTimer->m_pClient = pClient;
}
