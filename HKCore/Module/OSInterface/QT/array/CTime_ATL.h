
#ifndef _CTime_QT_h__
#define _CTime_QT_h__

#include "CString_QT.h"
#include "XGlobalDefine_QT.h"

class CTimeSpan
{
public:
	CTimeSpan() throw();
	CTimeSpan( __time64_t time ) throw();
	CTimeSpan( LONG lDays, int nHours, int nMins, int nSecs ) throw();

	LONGLONG GetDays() const throw();
	LONGLONG GetTotalHours() const throw();
	LONG GetHours() const throw();
	LONGLONG GetTotalMinutes() const throw();
	LONG GetMinutes() const throw();
	LONGLONG GetTotalSeconds() const throw();
	LONG GetSeconds() const throw();

	__time64_t GetTimeSpan() const throw();

	CTimeSpan operator+( CTimeSpan span ) const throw();
	CTimeSpan operator-( CTimeSpan span ) const throw();
	CTimeSpan& operator+=( CTimeSpan span ) throw();
	CTimeSpan& operator-=( CTimeSpan span ) throw();
	bool operator==( CTimeSpan span ) const throw();
	bool operator!=( CTimeSpan span ) const throw();
	bool operator<( CTimeSpan span ) const throw();
	bool operator>( CTimeSpan span ) const throw();
	bool operator<=( CTimeSpan span ) const throw();
	bool operator>=( CTimeSpan span ) const throw();

public:
	CString Format( LPCTSTR pszFormat ) const;

private:
	__time64_t m_timeSpan;
};

class CTime
{
public:
	static CTime  GetCurrentTime() throw();
	static BOOL  IsValidFILETIME(const FILETIME& ft) throw();

	CTime() throw();
	CTime( __time64_t time ) throw();
	CTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
		int nDST = -1 );
	CTime( WORD wDosDate, WORD wDosTime, int nDST = -1 );
	CTime( const SYSTEMTIME& st, int nDST = -1 );
	CTime( const FILETIME& ft, int nDST = -1 );

	CTime& operator=( __time64_t time ) throw();

	CTime& operator+=( CTimeSpan span ) throw();
	CTime& operator-=( CTimeSpan span ) throw();

	CTimeSpan operator-( CTime time ) const throw();
	CTime operator-( CTimeSpan span ) const throw();
	CTime operator+( CTimeSpan span ) const throw();

	bool operator==( CTime time ) const throw();
	bool operator!=( CTime time ) const throw();
	bool operator<( CTime time ) const throw();
	bool operator>( CTime time ) const throw();
	bool operator<=( CTime time ) const throw();
	bool operator>=( CTime time ) const throw();

	struct tm* GetGmtTm( struct tm* ptm ) const;
	struct tm* GetLocalTm( struct tm* ptm ) const;

	bool GetAsSystemTime( SYSTEMTIME& st ) const throw();
	bool GetAsDBTIMESTAMP( DBTIMESTAMP& dbts ) const throw();

	__time64_t GetTime() const throw();

	int GetYear() const throw();
	int GetMonth() const throw();
	int GetDay() const throw();
	int GetHour() const throw();
	int GetMinute() const throw();
	int GetSecond() const throw();
	int GetDayOfWeek() const throw();

	// formatting using "C" strftime
	CString Format( LPCTSTR pszFormat ) const;
	CString FormatGmt( LPCTSTR pszFormat ) const;
	CString Format( UINT nFormatID ) const;
	CString FormatGmt( UINT nFormatID ) const;

	CString Format(LPCSTR pFormat) const;
	CString FormatGmt(LPCSTR pFormat) const;

private:
	__time64_t m_time;
};

#endif  // _CTime_QT_h__
