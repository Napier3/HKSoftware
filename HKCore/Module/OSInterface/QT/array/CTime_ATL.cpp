
#include "CTime_QT.h"

/////////////////////////////////////////////////////////////////////////////
// CTimeSpan
/////////////////////////////////////////////////////////////////////////////

CTimeSpan::CTimeSpan() throw() :
	m_timeSpan(0)
{
}

CTimeSpan::CTimeSpan( __time64_t time ) throw() :
	m_timeSpan( time )
{
}

CTimeSpan::CTimeSpan(LONG lDays, int nHours, int nMins, int nSecs) throw()
{
 	m_timeSpan = nSecs + 60* (nMins + 60* (nHours + __int64(24) * lDays));
}

LONGLONG CTimeSpan::GetDays() const throw()
{
	return( m_timeSpan/(24*3600) );
}

LONGLONG CTimeSpan::GetTotalHours() const throw()
{
	return( m_timeSpan/3600 );
}

LONG CTimeSpan::GetHours() const throw()
{
	return( LONG( GetTotalHours()-(GetDays()*24) ) );
}

LONGLONG CTimeSpan::GetTotalMinutes() const throw()
{
	return( m_timeSpan/60 );
}

LONG CTimeSpan::GetMinutes() const throw()
{
	return( LONG( GetTotalMinutes()-(GetTotalHours()*60) ) );
}

LONGLONG CTimeSpan::GetTotalSeconds() const throw()
{
	return( m_timeSpan );
}

LONG CTimeSpan::GetSeconds() const throw()
{
	return( LONG( GetTotalSeconds()-(GetTotalMinutes()*60) ) );
}

__time64_t CTimeSpan::GetTimeSpan() const throw()
{
	return( m_timeSpan );
}

CTimeSpan CTimeSpan::operator+( CTimeSpan span ) const throw()
{
	return( CTimeSpan( m_timeSpan+span.m_timeSpan ) );
}

CTimeSpan CTimeSpan::operator-( CTimeSpan span ) const throw()
{
	return( CTimeSpan( m_timeSpan-span.m_timeSpan ) );
}

CTimeSpan& CTimeSpan::operator+=( CTimeSpan span ) throw()
{
	m_timeSpan += span.m_timeSpan;
	return( *this );
}

CTimeSpan& CTimeSpan::operator-=( CTimeSpan span ) throw()
{
	m_timeSpan -= span.m_timeSpan;
	return( *this );
}

bool CTimeSpan::operator==( CTimeSpan span ) const throw()
{
	return( m_timeSpan == span.m_timeSpan );
}

bool CTimeSpan::operator!=( CTimeSpan span ) const throw()
{
	return( m_timeSpan != span.m_timeSpan );
}

bool CTimeSpan::operator<( CTimeSpan span ) const throw()
{
	return( m_timeSpan < span.m_timeSpan );
}

bool CTimeSpan::operator>( CTimeSpan span ) const throw()
{
	return( m_timeSpan > span.m_timeSpan );
}

bool CTimeSpan::operator<=( CTimeSpan span ) const throw()
{
	return( m_timeSpan <= span.m_timeSpan );
}

bool CTimeSpan::operator>=( CTimeSpan span ) const throw()
{
	return( m_timeSpan >= span.m_timeSpan );
}

/////////////////////////////////////////////////////////////////////////////
// CTime
/////////////////////////////////////////////////////////////////////////////

CTime  CTime::GetCurrentTime() throw()
{
	return( CTime( ::_time64( NULL ) ) );
}

BOOL  CTime::IsValidFILETIME(const FILETIME& fileTime) throw()
{
	FILETIME localTime;
	if (!FileTimeToLocalFileTime(&fileTime, &localTime))
	{
		return FALSE;
	}

	// then convert that time to system time
	SYSTEMTIME sysTime;
	if (!FileTimeToSystemTime(&localTime, &sysTime))
	{
		return FALSE;
	}

	return TRUE;
}

CTime::CTime() throw() :
	m_time(0)
{
}

CTime::CTime( __time64_t time )  throw():
	m_time( time )
{
}

CTime::CTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
	int nDST)
{
#pragma warning (push)
#pragma warning (disable: 4127)  // conditional expression constant

	ATLENSURE( nYear >= 1900 );
	ATLENSURE( nMonth >= 1 && nMonth <= 12 );
	ATLENSURE( nDay >= 1 && nDay <= 31 );
	ATLENSURE( nHour >= 0 && nHour <= 23 );
	ATLENSURE( nMin >= 0 && nMin <= 59 );
	ATLENSURE( nSec >= 0 && nSec <= 59 );

#pragma warning (pop)

	struct tm atm;

	atm.tm_sec = nSec;
	atm.tm_min = nMin;
	atm.tm_hour = nHour;
	atm.tm_mday = nDay;
	atm.tm_mon = nMonth - 1;        // tm_mon is 0 based
	atm.tm_year = nYear - 1900;     // tm_year is 1900 based
	atm.tm_isdst = nDST;

	m_time = _mktime64(&atm);
	ATLASSUME(m_time != -1);       // indicates an illegal input time
	if(m_time == -1)
	{
		AtlThrow(E_INVALIDARG);
	}
}

CTime::CTime(WORD wDosDate, WORD wDosTime, int nDST)
{
	struct tm atm;
	atm.tm_sec = (wDosTime & ~0xFFE0) << 1;
	atm.tm_min = (wDosTime & ~0xF800) >> 5;
	atm.tm_hour = wDosTime >> 11;

	atm.tm_mday = wDosDate & ~0xFFE0;
	atm.tm_mon = ((wDosDate & ~0xFE00) >> 5) - 1;
	atm.tm_year = (wDosDate >> 9) + 80;
	atm.tm_isdst = nDST;
	m_time = _mktime64(&atm);
	ATLASSUME(m_time != -1);       // indicates an illegal input time

	if(m_time == -1)
		AtlThrow(E_INVALIDARG);

}

CTime::CTime(const SYSTEMTIME& sysTime, int nDST)
{
	if (sysTime.wYear < 1900)
	{
		__time64_t time0 = 0L;
		CTime timeT(time0);
		*this = timeT;
	}
	else
	{
		CTime timeT(
			(int)sysTime.wYear, (int)sysTime.wMonth, (int)sysTime.wDay,
			(int)sysTime.wHour, (int)sysTime.wMinute, (int)sysTime.wSecond,
			nDST);
		*this = timeT;
	}
}

CTime::CTime(const FILETIME& fileTime, int nDST)
{
	// first convert file time (UTC time) to local time
	FILETIME localTime;
	if (!FileTimeToLocalFileTime(&fileTime, &localTime))
	{
		m_time = 0;
		AtlThrow(E_INVALIDARG);
		return;
	}

	// then convert that time to system time
	SYSTEMTIME sysTime;
	if (!FileTimeToSystemTime(&localTime, &sysTime))
	{
		m_time = 0;
		AtlThrow(E_INVALIDARG);		
		return;
	}

	// then convert the system time to a time_t (C-runtime local time)
	CTime timeT(sysTime, nDST);
	*this = timeT;
}

CTime& CTime::operator=( __time64_t time ) throw()
{
	m_time = time;

	return( *this );
}

CTime& CTime::operator+=( CTimeSpan span ) throw()
{
	m_time += span.GetTimeSpan();

	return( *this );
}

CTime& CTime::operator-=( CTimeSpan span ) throw()
{
	m_time -= span.GetTimeSpan();

	return( *this );
}

CTimeSpan CTime::operator-( CTime time ) const throw()
{
	return( CTimeSpan( m_time-time.m_time ) );
}

CTime CTime::operator-( CTimeSpan span ) const throw()
{
	return( CTime( m_time-span.GetTimeSpan() ) );
}

CTime CTime::operator+( CTimeSpan span ) const throw()
{
	return( CTime( m_time+span.GetTimeSpan() ) );
}

bool CTime::operator==( CTime time ) const throw()
{
	return( m_time == time.m_time );
}

bool CTime::operator!=( CTime time ) const throw()
{
	return( m_time != time.m_time );
}

bool CTime::operator<( CTime time ) const throw()
{
	return( m_time < time.m_time );
}

bool CTime::operator>( CTime time ) const throw()
{
	return( m_time > time.m_time );
}

bool CTime::operator<=( CTime time ) const throw()
{
	return( m_time <= time.m_time );
}

bool CTime::operator>=( CTime time ) const throw()
{
	return( m_time >= time.m_time );
}

struct tm* CTime::GetGmtTm(struct tm* ptm) const
{
	// Ensure ptm is valid
	ATLENSURE( ptm != NULL );

	if (ptm != NULL)
	{
		struct tm ptmTemp;
		errno_t err = _gmtime64_s(&ptmTemp, &m_time);

		// Be sure the call succeeded
		if(err != 0) { return NULL; }

		*ptm = ptmTemp;
		return ptm;
	}

	return NULL;
}

struct tm* CTime::GetLocalTm(struct tm* ptm) const
{
	// Ensure ptm is valid
	ATLENSURE( ptm != NULL );

	if (ptm != NULL)
	{
		struct tm ptmTemp;
		errno_t err = _localtime64_s(&ptmTemp, &m_time);

		if (err != 0)
		{
			return NULL;    // indicates that m_time was not initialized!
		}

		*ptm = ptmTemp;
		return ptm;
	}

	return NULL;
}

bool CTime::GetAsSystemTime(SYSTEMTIME& timeDest) const throw()
{
	struct tm ttm;
	struct tm* ptm;

	ptm = GetLocalTm(&ttm);

	if(!ptm) { return false; }

	timeDest.wYear = (WORD) (1900 + ptm->tm_year);
	timeDest.wMonth = (WORD) (1 + ptm->tm_mon);
	timeDest.wDayOfWeek = (WORD) ptm->tm_wday;
	timeDest.wDay = (WORD) ptm->tm_mday;
	timeDest.wHour = (WORD) ptm->tm_hour;
	timeDest.wMinute = (WORD) ptm->tm_min;
	timeDest.wSecond = (WORD) ptm->tm_sec;
	timeDest.wMilliseconds = 0;

	return true;
}

__time64_t CTime::GetTime() const throw()
{
	return( m_time );
}

int CTime::GetYear() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? (ptm->tm_year) + 1900 : 0 ; 
}

int CTime::GetMonth() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_mon + 1 : 0;
}

int CTime::GetDay() const
{
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_mday : 0 ; 
}

int CTime::GetHour() const
{
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_hour : -1 ; 
}

int CTime::GetMinute() const
{
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_min : -1 ; 
}

int CTime::GetSecond() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_sec : -1 ;
}

int CTime::GetDayOfWeek() const
{ 
	struct tm ttm;
	struct tm * ptm;

	ptm = GetLocalTm(&ttm);
	return ptm ? ptm->tm_wday + 1 : 0 ;
}


CString CTimeSpan::Format(LPCTSTR pFormat) const
// formatting timespans is a little trickier than formatting CTimes
//  * we are only interested in relative time formats, ie. it is illegal
//      to format anything dealing with absolute time (i.e. years, months,
//         day of week, day of year, timezones, ...)
//  * the only valid formats:
//      %D - # of days
//      %H - hour in 24 hour format
//      %M - minute (0-59)
//      %S - seconds (0-59)
//      %% - percent sign
//	%#<any_of_mods> - skip leading zeros
{
	ATLASSERT( pFormat != NULL );
	if( pFormat == NULL )
		AtlThrow( E_INVALIDARG );

	CString strBuffer;
	CString hmsFormats [_CTIMESPANFORMATS] = {_T("%c"),_T("%02ld"),_T("%d")};
	CString dayFormats [_CTIMESPANFORMATS] = {_T("%c"),_T("%I64d"),_T("%I64d")};
	strBuffer.Preallocate(maxTimeBufferSize);
	TCHAR ch;

	while ((ch = *pFormat++) != _T('\0'))
	{
		enum _CTIMESPANFORMATSTEP formatstep = _CTFS_NONE;
		if(ch == _T('%'))
		{
			formatstep = _CTFS_FORMAT;
			ch = *pFormat++;
			if(ch == _T('#'))
			{
					formatstep = _CTFS_NZ;
					ch = *pFormat++;
			}
		}
		switch (ch)
		{
			case '%':
				strBuffer += ch;
				break;
			case 'D':
				strBuffer.AppendFormat(dayFormats[formatstep], formatstep ? GetDays()    : ch);
				break;
			case 'H':
				strBuffer.AppendFormat(hmsFormats[formatstep], formatstep ? GetHours()   : ch);
				break;
			case 'M':
				strBuffer.AppendFormat(hmsFormats[formatstep], formatstep ? GetMinutes() : ch);
				break;
			case 'S':
				strBuffer.AppendFormat(hmsFormats[formatstep], formatstep ? GetSeconds() : ch);
				break;
			default:
				if(formatstep)
				{
#pragma warning (push)
#pragma warning (disable: 4127)  // conditional expression constant
					ATLENSURE(FALSE);      // probably a bad format character
#pragma warning (pop)
				}
				else
				{
					strBuffer += ch;
#ifdef _MBCS
					if (_istlead(ch))
					{
						strBuffer += *pFormat++;
					}
#endif
				}
				break;
			}
	}

	return strBuffer;
}

CString CTimeSpan::Format(UINT nFormatID) const
{
	CString strFormat;
	ATLENSURE(strFormat.LoadString(nFormatID));
	return Format(strFormat);
}

#if defined(_AFX) && defined(_UNICODE)
CString CTimeSpan::Format(LPCSTR pFormat) const
{
	return Format(CString(pFormat));
}
#endif

#ifdef __oledb_h__
CTime::CTime( const DBTIMESTAMP& dbts, int nDST ) throw()
{
	struct tm atm;
	atm.tm_sec = dbts.second;
	atm.tm_min = dbts.minute;
	atm.tm_hour = dbts.hour;
	atm.tm_mday = dbts.day;
	atm.tm_mon = dbts.month - 1;        // tm_mon is 0 based
	ATLASSERT(dbts.year >= 1900);
	atm.tm_year = dbts.year - 1900;     // tm_year is 1900 based
	atm.tm_isdst = nDST;
	m_time = _mktime64(&atm);
	ATLASSUME(m_time != -1);       // indicates an illegal input time
}
#endif

CString CTime::Format(LPCTSTR pFormat) const
{
	if(pFormat == NULL)
	{
		return pFormat;
	}

	TCHAR szBuffer[maxTimeBufferSize];

	struct tm ptmTemp;
	errno_t err = _localtime64_s(&ptmTemp, &m_time);
	if (err != 0 || !_tcsftime(szBuffer, maxTimeBufferSize, pFormat, &ptmTemp))
	{
		szBuffer[0] = '\0';
	}

	return szBuffer;
}

CString CTime::FormatGmt(LPCTSTR pFormat) const
{
	if(pFormat == NULL)
	{
		return pFormat;
	}

	TCHAR szBuffer[maxTimeBufferSize];

	struct tm ptmTemp;
	errno_t err = _gmtime64_s(&ptmTemp, &m_time);
	if (err != 0 || !_tcsftime(szBuffer, maxTimeBufferSize, pFormat, &ptmTemp))
	{
		szBuffer[0] = '\0';
	}

	return szBuffer;
}

CString CTime::Format(UINT nFormatID) const
{
	CString strFormat;
	ATLENSURE(strFormat.LoadString(nFormatID));
	return Format(strFormat);
}

CString CTime::Format(LPCSTR pFormat) const
{
	return Format(CString(pFormat));
}

CString CTime::FormatGmt(LPCSTR pFormat) const
{
	return FormatGmt(CString(pFormat));
}
