// EpTimer.cpp: implementation of the CEpTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpTimer.h"
#include "EpNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpTimer::CEpTimer()
{

}

CEpTimer::~CEpTimer()
{

}


void CEpTimer::BeginTimer(DWORD dwCurrTick)
{
	m_bTimerBegin = TRUE;
	m_dwTimerBegin = dwCurrTick;
}

void CEpTimer::ResetTimer(DWORD dwCurrTick)
{
	m_dwTimerBegin = dwCurrTick;
}

void CEpTimer::KillTimer()
{
	m_bTimerBegin = FALSE;
	m_dwTimerBegin = 0;
}

BOOL CEpTimer::IsTimeOut(DWORD dwCurrTick)
{
	long nTimer = dwCurrTick - m_dwTimerBegin;

	if (nTimer > m_nTimeLong)
	{
		return TRUE;
	}
	else
	{
		if (nTimer < 0)
		{
			m_dwTimerBegin = 0;
			return ((long)dwCurrTick > m_nTimeLong);
		}
		else
		{
			return FALSE;
		}
	}
}
