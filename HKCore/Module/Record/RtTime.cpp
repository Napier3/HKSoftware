// RtTime.cpp: implementation of the CRtTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtTime.h"
// #include "LanguageMngrMR1200.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtTimeSpan::CRtTimeSpan(WORD wDay, WORD wHour, WORD wMinute, WORD wSecond, WORD wMilliseconds, WORD wMicroseconds)
{
	m_wDay    = 0; 
	m_wHour   = 0; 
	m_wMinute = 0; 
	m_wSecond = 0; 
	m_wMilliseconds = 0; 
	m_wMicroseconds = 0;		
	
	if (wMicroseconds >= 1000)
	{
		m_wMilliseconds = wMicroseconds / 1000;
		m_wMicroseconds = wMicroseconds % 1000;
	}
	else
	{
		m_wMicroseconds = wMicroseconds;
	}
	
	if (wMilliseconds >= 1000)
	{
		m_wMilliseconds += wMilliseconds % 1000;
		m_wSecond = wMilliseconds / 1000;
	}
	else
	{
		m_wMilliseconds += wMilliseconds;
	}

	if (wSecond >= 60)
	{
		m_wMinute = wSecond / 60;
		m_wSecond += wSecond % 60;
	}
	else
	{
		m_wSecond += wSecond;
	}
	
	if (wMinute >= 60)
	{
		m_wHour = wMinute / 60;
		m_wMinute += wMinute % 60;
	}
	else
	{
		m_wMinute += wMinute;
	}

	if (wHour >= 24)
	{
		m_wDay = wHour / 24;
		m_wHour = wHour % 24;
	}
	else
	{
		m_wHour += wHour;
	}

	m_wDay += wDay; 
	
}

CRtTimeSpan::CRtTimeSpan()
{
	m_wDay    = 0; 
	m_wHour   = 0; 
	m_wMinute = 0; 
	m_wSecond = 0; 
	m_wMilliseconds = 0; 
	m_wMicroseconds = 0;		
}

CRtTimeSpan::CRtTimeSpan(__int64 n64Val, DWORD dwSampleRate)
{
	Init(n64Val, dwSampleRate);		
}

CRtTimeSpan::~CRtTimeSpan()
{
	
}

CRtTimeSpan& CRtTimeSpan::operator= (const CRtTimeSpan &ts)
{
	//m_wYear   = ts.m_wYear;
	//m_wMonth  = ts.m_wMonth; 
	m_wDay    = ts.m_wDay; 
	m_wHour   = ts.m_wHour; 
	m_wMinute = ts.m_wMinute; 
	m_wSecond = ts.m_wSecond; 
	m_wMilliseconds = ts.m_wMilliseconds; 
	m_wMicroseconds = ts.m_wMicroseconds;	

	return *this;
}

CRtTimeSpan& CRtTimeSpan::operator= (__int64 n64Val)
{
	Init(n64Val, 100000);

	return *this;
}


__int64 CRtTimeSpan::GetInt64(DWORD dwSampleRate)
{
	__int64 n64Val = 0;
	double dValue = 0;
	double dGap = 1000;
	dGap /= dwSampleRate;  //每个点的毫秒数
	dGap *= 1000;
	double dTemp = 0;
	
	dValue = m_wDay * 24 + m_wHour;
	dValue *= 60;
	dValue /= dGap;

	dTemp = m_wMinute;
	dTemp /= dGap;
	dValue += dTemp;
	dValue *= 60;

	dTemp = m_wSecond;
	dTemp /= dGap;
	dValue += dTemp;
	dValue *= 1000;

	dTemp = m_wMilliseconds;
	dTemp /= dGap;
	dValue += dTemp;
	dValue *= 1000;

	dTemp = m_wMicroseconds;
	dTemp /= dGap;
	dValue += dTemp;

	n64Val = (__int64)dValue;

	return n64Val;
}

DWORD CRtTimeSpan::GetTotalSecond()
{
	DWORD dwSecond = m_wDay * 24;
	dwSecond += (dwSecond + m_wHour) * 60;
	dwSecond += (dwSecond + m_wMinute) * 60;
	dwSecond += m_wSecond;
	
	return dwSecond;
}

void CRtTimeSpan::Init(__int64 n64Val, DWORD dwSampleRate)
{
	double dGap = 1000;
	dGap /= dwSampleRate;  //每个点的毫秒数
	double dTemp = (double)n64Val;
	dTemp *= dGap;  //dTemp = ms
	
	//us
	__int64 n64Temp = (__int64)dTemp;
	m_wMicroseconds = (WORD)((WORD)(dTemp * 1000) - (n64Temp * 1000));

	//ms
	n64Temp = (__int64)dTemp;
	m_wMilliseconds = (WORD)(n64Temp % 1000);

	//s
	dTemp = (double)n64Temp;
	dTemp /= 1000;
	n64Temp = (__int64)dTemp;
	m_wSecond = (WORD)(n64Temp % 60);

	dTemp = (double)n64Temp;
	dTemp /= 60;
	n64Temp = (__int64)dTemp;
	m_wMinute = (WORD)(n64Temp % 60);

	dTemp = (double)n64Temp;
	dTemp /= 60;
	n64Temp = (__int64)dTemp;
	m_wHour = (WORD)(n64Temp % 24);
	m_wDay = (WORD)(n64Temp / 24);

	if (m_wDay > 28)
	{
		m_wDay = 28;
	}
}

CString CRtTimeSpan::FormatString()
{
	CString strDay, strHour, strMinute, strSecond, strRecordTime;	
	
	if (m_wDay > 0)
	{
		strDay.Format("%d ", m_wDay);
		//strDay.Format("%d%s", m_wDay, GetLanguageStringByID(gs_strLanguage_msDay));
	}
	
	if (m_wHour > 0)
	{
		strHour.Format("%d:", m_wHour);
		//strHour.Format("%d%s", m_wHour, GetLanguageStringByID(gs_strLanguage_msHour));
	}
	
	if (m_wMinute > 0)
	{
		strMinute.Format("%d:", m_wMinute);
		//strMinute.Format("%d%s", m_wMinute, GetLanguageStringByID(gs_strLanguage_msMinute));
	}
	
	strSecond.Format("%d ", m_wSecond);
	//strSecond.Format("%d%s", m_wSecond, GetLanguageStringByID(gs_strLanguage_msSecond));
	
    strRecordTime= strDay+strHour+strMinute+strSecond;
	
	return strRecordTime;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtTime::CRtTime(RTTIME &tm)
{
	m_wYear   = tm.wYear; 
	m_wMonth  = tm.wMonth; 
	m_wDay    = tm.wDay; 
	m_wHour   = tm.wHour; 
	m_wMinute = tm.wMinute; 
	m_wSecond = tm.wSecond; 
	m_wMilliseconds = tm.wMilliseconds; 
	m_wMicroseconds = tm.wMicroseconds;	
}

void CRtTime::GetRtTime(RTTIME &oRtTime)
{
	oRtTime.wYear= m_wYear;
	oRtTime.wMonth= m_wMonth; 
	oRtTime.wDay= m_wDay; 
	oRtTime.wHour= m_wHour; 
	oRtTime.wMinute= m_wMinute; 
	oRtTime.wSecond= m_wSecond; 
	oRtTime.wMilliseconds= m_wMilliseconds; 
	oRtTime.wMicroseconds= m_wMicroseconds;	
}

CRtTime::CRtTime(WORD wYear, WORD wMonth, WORD wDay, WORD wHour, WORD wMinute, WORD wSecond, WORD wMilliseconds, WORD wMicroseconds)
{
	m_wYear   = wYear; 
	m_wMonth  = wMonth; 
	m_wDay    = wDay; 
	m_wHour   = wHour; 
	m_wMinute = wMinute; 
	m_wSecond = wSecond; 
	m_wMilliseconds = wMilliseconds; 
	m_wMicroseconds = wMicroseconds;	
}

CRtTime::~CRtTime()
{

}

CRtTime& CRtTime::operator= (const CRtTime &tm)
{
	m_wYear   = tm.m_wYear; 
	m_wMonth  = tm.m_wMonth; 
	m_wDay    = tm.m_wDay; 
	m_wHour   = tm.m_wHour; 
	m_wMinute = tm.m_wMinute; 
	m_wSecond = tm.m_wSecond; 
	m_wMilliseconds = tm.m_wMilliseconds; 
	m_wMicroseconds = tm.m_wMicroseconds;	

	return *this;
}

//CRtTimeSpan CRtTime::operator-= (const CRtTime &tm)
//{
//	CRtTimeSpan ts;
//	return ts;
//}

void CRtTime::AdjustSub(BOOL bUseDayZero)
{
	if (m_wMilliseconds < 0)
	{
		m_wMilliseconds = 1000 + m_wMilliseconds;
		m_wSecond--;
	}

	if (m_wSecond < 0)
	{
		m_wSecond = 60 + m_wSecond;
		m_wMinute--;
	}
	
	if (m_wMinute < 0)
	{
		m_wMinute = 60 + m_wMinute;
		m_wHour--;
	}
	
	if (m_wHour < 0)
	{
		m_wHour = 24 + m_wHour;
		m_wDay--;
	}
	
	if (bUseDayZero)
	{
		if (m_wDay < 0)
		{
			m_wMonth--;
			
			if (m_wMonth > 0)
			{
				m_wDay = Mr_GetDaysOfMonth(m_wYear, m_wMonth);
			}
			else
			{
				m_wDay = 31; //前一年的12月
			}
		}
	}
	else
	{
		if (m_wDay <= 0)
		{
			m_wMonth--;

			if (m_wMonth > 0)
			{
				m_wDay = Mr_GetDaysOfMonth(m_wYear, m_wMonth);
			}
			else
			{
				m_wDay = 31; //前一年的12月
			}
		}
	}
	
	
	if (m_wMonth <= 0)
	{
		m_wMonth = 12;
		m_wYear--;
	}
}


void CRtTime::AdjustAdd()
{
	if (m_wMilliseconds >= 1000)
	{
		m_wMilliseconds -= 1000;
		m_wSecond++;
	}

	if (m_wSecond >= 60)
	{
		m_wSecond -= 60;
		m_wMinute++;
	}
	
	if (m_wMinute >= 60)
	{
		m_wMinute -= 60;
		m_wHour++;
	}
	
	if (m_wHour >= 24)
	{
		m_wHour -= 24;
		m_wDay++;
	}
	
	WORD dDay = 0;
	
	if (m_wMonth > 0) 
	{
		dDay = Mr_GetDaysOfMonth(m_wYear, m_wMonth);
	}

	if (m_wDay > dDay)
	{
		m_wDay = 1;
		m_wMonth++;
	}
	
	if (m_wMonth > 12)
	{
		m_wMonth = 1;
		m_wYear++;
	}
}

CRtTime& CRtTime::operator-= (const CRtTimeSpan &ts)
{
	if (m_wMicroseconds < ts.m_wMicroseconds)
	{
		m_wMicroseconds = 1000 + m_wMicroseconds - ts.m_wMicroseconds;
		m_wMilliseconds--;
		AdjustSub();
	}
	else
	{
		m_wMicroseconds -= ts.m_wMicroseconds;
	}

	if (m_wMilliseconds < ts.m_wMilliseconds)
	{
		m_wMilliseconds = 1000 + m_wMilliseconds - ts.m_wMilliseconds;
		m_wSecond--;
		AdjustSub();
	}
	else
	{
		m_wMilliseconds -= ts.m_wMilliseconds;
	}

	if (m_wSecond < ts.m_wSecond)
	{
		m_wSecond = 60 + m_wSecond - ts.m_wSecond;
		m_wMinute--;
		AdjustSub();
	}
	else
	{
		m_wSecond -= ts.m_wSecond;
	}

	if (m_wMinute < ts.m_wMinute)
	{
		m_wMinute = 60 + m_wMinute - ts.m_wMinute;
		m_wHour--;
		AdjustSub();
	}
	else
	{
		m_wMinute -= ts.m_wMinute;
	}

	if (m_wHour < ts.m_wHour)
	{
		m_wHour = 24 + m_wHour - ts.m_wHour;
		m_wDay--;
		AdjustSub();
	}
	else
	{
		m_wHour -= ts.m_wHour;
	}

	if (m_wDay < ts.m_wDay)
	{
		m_wMonth--;

		if (m_wMonth < 1)
		{
			m_wYear--;
		}
		
		m_wDay = Mr_GetDaysOfMonth(m_wYear, m_wMonth) + m_wDay - ts.m_wDay;
	}
	else
	{
		m_wDay -= ts.m_wDay;
	}

	return *this;
}

CRtTime& CRtTime::operator+= (const CRtTimeSpan &ts)
{
	m_wMicroseconds += ts.m_wMicroseconds;

	if (m_wMicroseconds >= 1000)
	{
		m_wMicroseconds -= 1000;
		m_wMilliseconds++;
		AdjustAdd();
	}
	
	m_wMilliseconds += ts.m_wMilliseconds;
	
	if (m_wMilliseconds >= 1000 )
	{
		m_wMilliseconds -= 1000;
		m_wSecond++;
		AdjustAdd();
	}
	
	m_wSecond += ts.m_wSecond;
	if (m_wSecond >= 60 )
	{
		m_wSecond -= 60;
		m_wMinute++;
		AdjustAdd();
	}

	m_wMinute += ts.m_wMinute;
	
	if (m_wMinute >= 60)
	{
		m_wMinute -= 60;
		m_wHour++;
		AdjustAdd();
	}

	m_wHour += ts.m_wHour;

	if (m_wHour >= 24)
	{
		m_wHour -= 24;
		m_wDay++;
		AdjustAdd();
	}
	
	m_wDay += ts.m_wDay;
	
	WORD dDay = Mr_GetDaysOfMonth(m_wYear, m_wMonth);
	
	if (m_wDay > dDay)
	{
		m_wDay = m_wDay - dDay;
		m_wMonth++;

		if (m_wMonth > 12)
		{
			m_wMonth -= 12;
			m_wYear++;
		}
	}
	
//	m_wMonth += ts.m_wMonth;
//
//	if (m_wMonth > 12)
//	{
//		m_wMonth -= 12;
//		m_wYear++;
//	}
	
	return *this;
}

CRtTimeSpan CRtTime::operator- (const CRtTime &tm)
{
	CRtTimeSpan ts;
	ts.m_wDay = tm.m_wDay;
	ts.m_wHour = tm.m_wHour;
	ts.m_wMinute = tm.m_wMinute;
	ts.m_wSecond = tm.m_wSecond;
	ts.m_wMilliseconds = tm.m_wMilliseconds;
	ts.m_wMicroseconds = tm.m_wMicroseconds;
	
	CRtTime tmSrc = *this;
	tmSrc -= ts;
	tmSrc.AdjustSub(TRUE);
	
	ts.m_wDay = tmSrc.m_wDay;
	ts.m_wHour = tmSrc.m_wHour;
	ts.m_wMinute = tmSrc.m_wMinute;
	ts.m_wSecond = tmSrc.m_wSecond;
	ts.m_wMilliseconds = tmSrc.m_wMilliseconds;
	ts.m_wMicroseconds = tmSrc.m_wMicroseconds;
	
	return ts;
}


BOOL CRtTime::operator> (const CRtTime &tm)
{
	if (m_wYear > tm.m_wYear)
	{
		return TRUE;
	}
	else if (m_wYear < tm.m_wYear)
	{
		return FALSE;
	}

	if (m_wMonth > tm.m_wMonth)
	{
		return TRUE;
	}
	else if (m_wMonth < tm.m_wMonth)
	{
		return FALSE;
	}

	if (m_wDay > tm.m_wDay)
	{
		return TRUE;
	}
	else if (m_wDay < tm.m_wDay)
	{
		return FALSE;
	}

	if (m_wHour > tm.m_wHour)
	{
		return TRUE;
	}
	else if (m_wHour < tm.m_wHour)
	{
		return FALSE;
	}

	if (m_wMinute > tm.m_wMinute)
	{
		return TRUE;
	}
	else if (m_wMinute < tm.m_wMinute)
	{
		return FALSE;
	}

	if (m_wSecond > tm.m_wSecond)
	{
		return TRUE;
	}
	else if (m_wSecond < tm.m_wSecond)
	{
		return FALSE;
	}

	if (m_wMilliseconds > tm.m_wMilliseconds)
	{
		return TRUE;
	}
	else if (m_wMilliseconds < tm.m_wMilliseconds)
	{
		return FALSE;
	}

	if (m_wMicroseconds > tm.m_wMicroseconds)
	{
		return TRUE;
	}
	
	return FALSE;
}

BOOL CRtTime::operator>= (const CRtTime &tm)
{
	return ! (*this < tm);
}

BOOL CRtTime::operator< (const CRtTime &tm)
{
	if (m_wYear < tm.m_wYear)
	{
		return TRUE;
	}
	else if (m_wYear > tm.m_wYear)
	{
		return FALSE;
	}
	
	if (m_wMonth < tm.m_wMonth)
	{
		return TRUE;
	}
	else if (m_wMonth > tm.m_wMonth)
	{
		return FALSE;
	}
	
	if (m_wDay < tm.m_wDay)
	{
		return TRUE;
	}
	else if (m_wDay > tm.m_wDay)
	{
		return FALSE;
	}
	
	if (m_wHour < tm.m_wHour)
	{
		return TRUE;
	}
	else if (m_wHour > tm.m_wHour)
	{
		return FALSE;
	} 
	
	if (m_wMinute < tm.m_wMinute)
	{
		return TRUE;
	}
	else if (m_wMinute > tm.m_wMinute)
	{
		return FALSE;
	}
	
	if (m_wSecond < tm.m_wSecond)
	{
		return TRUE;
	}
	else if (m_wSecond > tm.m_wSecond)
	{
		return FALSE;
	}
	
	if (m_wMilliseconds < tm.m_wMilliseconds)
	{
		return TRUE;
	}
	else if (m_wMilliseconds > tm.m_wMilliseconds)
	{
		return FALSE;
	}
	
	if (m_wMicroseconds < tm.m_wMicroseconds)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CRtTime::operator<= (const CRtTime &tm)
{
	return ! (*this > tm);
}

BOOL CRtTime::operator== (const CRtTime &tm)
{
	if (m_wYear != tm.m_wYear)
	{
		return FALSE;
	}
	
	if (m_wMonth != tm.m_wMonth)
	{
		return FALSE;
	}
	
	if (m_wDay != tm.m_wDay)
	{
		return FALSE;
	}
	
	if (m_wHour != tm.m_wHour)
	{
		return FALSE;
	}
	
	if (m_wMinute != tm.m_wMinute)
	{
		return FALSE;
	}
	
	if (m_wSecond != tm.m_wSecond)
	{
		return FALSE;
	}
	
	if (m_wMilliseconds != tm.m_wMilliseconds)
	{
		return FALSE;
	}
	
	if (m_wMicroseconds != tm.m_wMicroseconds)
	{
		return FALSE;
	}
	
	return TRUE;
}

