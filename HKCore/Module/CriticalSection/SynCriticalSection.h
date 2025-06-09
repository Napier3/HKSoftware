// SynCriticalSection.h: interface for the SynCriticalSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SYNCRITICALSECTION_H__)
#define _SYNCRITICALSECTION_H__

#ifdef _PSX_IDE_QT_

#include "QT/SynCriticalSection_QT.h"

#else

class CAutoCriticSection : public CRITICAL_SECTION
{
public:
	CAutoCriticSection( void )
	{
		::InitializeCriticalSection( this );
	}
	
	virtual ~CAutoCriticSection( void )
	{
		::DeleteCriticalSection( this );
	}
};

class CAutoSimpleLock
{
public:
	CAutoSimpleLock( CAutoCriticSection *pSection ) : m_pSection( pSection )
	{
		if( m_pSection != NULL )
		{
			EnterCriticalSection( m_pSection );
		}
	}
	CAutoSimpleLock(CAutoCriticSection &oSection )
	{
		m_pSection = &oSection;
		if( m_pSection != NULL )
		{
			EnterCriticalSection( m_pSection );
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
			EnterCriticalSection( m_pSection );
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
			EnterCriticalSection( m_pSection );
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
			LeaveCriticalSection( m_pSection );
		}
		
		m_pSection = NULL;
	}
	
private:
	CAutoCriticSection *m_pSection;
};
#endif


#endif // !defined(_SYNCRITICALSECTION_H__)
