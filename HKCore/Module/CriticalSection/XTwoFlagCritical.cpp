// CXTwoFlagCritical.cpp: implementation of the CXTwoFlagCritical class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "XTwoFlagCritical.h"
#include "..\System\TickCount32.h"

//////////////////////////////////////////////////////////////////////
CXTwoFlagCritical::CXTwoFlagCritical()
{
	m_bXValidate = TRUE;  //是否有效的标志
	m_nXOccupyRefCount = 0;	//占用计数器

}

CXTwoFlagCritical::~CXTwoFlagCritical()
{
	
}

BOOL CXTwoFlagCritical::XWaitForNoOccupy(long nWiteTimeLong)
{
	long nCount = nWiteTimeLong / 50;
	CTickCount32 oTick;

	while (m_nXOccupyRefCount != 0)
	{
		oTick.DoEvents(50);

		if (nCount == 0)
		{
			break;
		}

		nCount--;
	}

	return (m_nXOccupyRefCount == 0);
}


BOOL CXTwoFlagCritical::XWaitForValidate(long nWiteTimeLong)
{
	long nCount = nWiteTimeLong / 50;
	CTickCount32 oTick;

	while (!m_bXValidate)
	{
		oTick.DoEvents(50);

		if (nCount == 0)
		{
			break;
		}

		nCount--;
	}

	return m_bXValidate;
}

