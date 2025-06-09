// CThreadProgressInterface.cpp: implementation of the CCThreadProgressInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadProgressInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CThreadProgressInterface::CThreadProgressInterface()
{
	m_nMaxRange = 100;
	m_nOneStepCount = 10;
	m_nOneStepIndex = 0;
}

CThreadProgressInterface::~CThreadProgressInterface()
{
	
}

void CThreadProgressInterface::InitThreadProgress(long nMaxRange, long nOneStepCount)
{
	m_nMaxRange = nMaxRange;
	m_nOneStepCount = nOneStepCount;
	SetMaxRange(nMaxRange);
}

void CThreadProgressInterface::Step()
{
	m_nOneStepIndex++;

	if (m_nOneStepIndex >= m_nOneStepCount)
	{
		m_nOneStepIndex = 0;
		StepIt();
	}
}

