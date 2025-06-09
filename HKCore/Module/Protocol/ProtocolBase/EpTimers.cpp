// EpTimers.cpp: implementation of the CEpTimers class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpTimers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpTimers::CEpTimers()
{

}

CEpTimers::~CEpTimers()
{

}


void CEpTimers::BeginTimer()
{
	DWORD dwTick = ::GetTickCount();
	POS pos = GetHeadPosition();
	CEpTimer *pTimer = NULL;

	while (pos != NULL)
	{
		pTimer = (CEpTimer*)GetNext(pos);
		pTimer->BeginTimer(dwTick);
	}
}

void CEpTimers::ResetTimer()
{
	DWORD dwTick = ::GetTickCount();
	POS pos = GetHeadPosition();
	CEpTimer *pTimer = NULL;

	while (pos != NULL)
	{
		pTimer = (CEpTimer*)GetNext(pos);
		pTimer->ResetTimer(dwTick);
	}
}

void CEpTimers::KillTimer()
{
	POS pos = GetHeadPosition();
	CEpTimer *pTimer = NULL;

	while (pos != NULL)
	{
		pTimer = (CEpTimer*)GetNext(pos);
		pTimer->KillTimer();
	}
}

CEpNode* CEpTimers::RunTimer(DWORD dwCurrTick)
{
	CEpNode *pNodeToRun = NULL;
	POS pos = GetHeadPosition();
	CEpTimer *pTimer = NULL;

	while (pos != NULL)
	{
		pTimer = (CEpTimer*)GetNext(pos);

		if (pTimer->IsTimeOut(dwCurrTick) )
		{
			pNodeToRun = pTimer->m_pJumpToNode;
		}

		if (pNodeToRun != NULL)
		{
			break;
		}
	}

	return pNodeToRun;
}

