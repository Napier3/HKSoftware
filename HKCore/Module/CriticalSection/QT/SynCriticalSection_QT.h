#ifndef _SynCriticalSection_QT_h_
#define _SynCriticalSection_QT_h_

#ifdef _PSX_QT_LINUX_
//#define USE_pthread_mutex_lock//zhouhj 2025.1.11
#endif

/*
330硬件平台+Qt4.8下， QMutex::lock()函数禁止使用。以API函数"pthread_mutex_lock()"代替。
原因是由于QMutex::lock()函数中调用了pthread_mutex_lock->pthread_con_wait->pthread_mutx_unlock，使用到了系统时钟。
由于系统时钟的偶发不确定性导致pthread_con_wait不能正常结束，逻辑无法完成pthread_mutx_unlock。
*/
#ifdef USE_pthread_mutex_lock
#include <pthread.h>
class CAutoCriticSection_Thread
{
public:
	CAutoCriticSection_Thread( void )
	{
		pthread_mutex_init(&m_oMutex, NULL);
	}
	virtual ~CAutoCriticSection_Thread( void )
	{
		pthread_mutex_destroy(&m_oMutex);
	}
	void lock() {
		pthread_mutex_lock(&m_oMutex);
	}
	void unlock() {
		pthread_mutex_unlock(&m_oMutex);
	}
	// 假设你想提供一个带有超时参数的 lock 函数
	bool try_lock_for(int milliseconds) {
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		ts.tv_sec += milliseconds / 1000;
		ts.tv_nsec += (milliseconds % 1000) * 1000000;
		if (ts.tv_nsec >= 1000000000) {
			ts.tv_sec += 1;
			ts.tv_nsec -= 1000000000;
		}

		int ret = pthread_mutex_timedlock(&m_oMutex, &ts);
		return ret == 0;
	}
private:
	pthread_mutex_t m_oMutex;
};
#else
#include <QMutex>
#include <QMutexLocker>

class CAutoCriticSection_QMutex: public QMutex
{
public:
	CAutoCriticSection_QMutex( void )
	{
	}
	virtual ~CAutoCriticSection_QMutex( void )
	{
	}
};

#endif


#ifdef USE_pthread_mutex_lock
typedef CAutoCriticSection_Thread CAutoCriticSection;
#else
typedef CAutoCriticSection_QMutex CAutoCriticSection;
#endif

class CAutoSimpleLock
{
public:
    CAutoSimpleLock( CAutoCriticSection *pSection ) : m_pSection( pSection )
    {
        if( m_pSection != NULL )
        {
            m_pSection->lock();
        }
    }
    CAutoSimpleLock(CAutoCriticSection &oSection )
    {
        m_pSection = &oSection;
        if( m_pSection != NULL )
        {
              m_pSection->lock();
        }
    }

    void Enter(CAutoCriticSection *pSection)
    {
        if( m_pSection != NULL )
        {
            Free();
        }

        m_pSection = pSection;

        if( m_pSection != NULL )
        {
            m_pSection->lock();
        }
    }

    void Enter(CAutoCriticSection &oSection)
    {
        if( m_pSection != NULL )
        {
            Free();
        }

        m_pSection = &oSection;

        if( m_pSection != NULL )
        {
            m_pSection->lock();
        }
    }

    virtual ~CAutoSimpleLock()
    {
        Free();
    }

    void Free()
    {
        if( m_pSection != NULL )
        {
            m_pSection->unlock();
        }

        m_pSection = NULL;
    }

private:
    CAutoCriticSection *m_pSection;
};

#endif
