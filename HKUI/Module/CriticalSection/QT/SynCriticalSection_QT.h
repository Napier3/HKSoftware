#ifndef _SynCriticalSection_QT_h_
#define _SynCriticalSection_QT_h_

#include <QMutex>
#include <QMutexLocker>

class CAutoCriticSection : public QMutex
{
public:
    CAutoCriticSection( void ){}
    virtual ~CAutoCriticSection( void ){}
};

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
