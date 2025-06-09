
#include "CTime_QT.h"
#include "../../Log/LogPrint.h"
#ifdef USE_Custom_CDateTime
#include "../../API/MathApi.h"
#endif
//#include <ctime>

#ifdef USE_Custom_CDateTime
#include"CDateTime_QT.h"
#endif

// time_t tmToTimeT(struct tm& tm) {
// 	std::time_t time_since_epoch = std::mktime(&tm);
// 	// mktime returns -1 on failure, handle it appropriately
// 	if (time_since_epoch == -1) {
// 		throw std::runtime_error("mktime failed to convert tm to time_t");
// 	}
// 	return time_since_epoch;
// }

// 

// time_t convertToUnixTimestamp(int year, int month, int day, int hour, int minute, int second) {
// 	struct tm tm = {};
// 	tm.tm_year = year - 1900;  // tm_year is the number of years since 1900
// 	tm.tm_mon = month - 1;     // tm_mon is zero-based (0 = January, 11 = December)
// 	tm.tm_mday = day;
// 	tm.tm_hour = hour;
// 	tm.tm_min = minute;
// 	tm.tm_sec = second;
// 
// 	// Normalize the tm structure and convert it to time_t
// 	return tmToTimeT(tm);
// }


CTime::CTime()
{
#ifdef USE_Custom_CDateTime
	m_nSecond = 0;
	m_nMs = 0;
#endif
//	CLogPrint::LogString(XLOGLEVEL_RESULT,_T("CTime Create"));
}

CTime::CTime(qint64 n64Time)
{
#ifdef USE_Custom_CDateTime
	m_nSecond = n64Time/1000;
	m_nMs = n64Time%1000;
#else
	setMSecsSinceEpoch(n64Time);
#endif
}

//xupf
CTime::CTime(SYSTEMTIME tm)
{
#ifdef USE_Custom_CDateTime
	long nSecondNum = 0;
	short nYear = tm.wYear;
	short nMonth = tm.wMonth;
	short nDay = tm.wDay;
	short nHour = tm.wHour;
	short nMinute = tm.wMinute;
	short nSecond = tm.wSecond;
	TransTimer_To_LongTime(nSecondNum,nYear,nMonth,nDay,nHour,nMinute,nSecond);
	m_nSecond = nSecondNum;
	m_nMs = tm.wMilliseconds;
#else
	QDate qdt(tm.wYear, tm.wMonth, tm.wDay) ;
	QTime qtm(tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	QDateTime(qdt, qtm);
#endif
}

CTime& CTime::operator = (QDateTime &other)
{
#ifdef USE_Custom_CDateTime
	qint64 n64Value = other.toMSecsSinceEpoch();
	m_nSecond = n64Value/1000;
	m_nMs = n64Value%1000;
#else
	QDateTime::operator= ( (const QDateTime &)other);
#endif
	return *this;
}

CTime& CTime::operator = (CTime &other)
{
#ifdef USE_Custom_CDateTime
	m_nSecond = other.m_nSecond;
	m_nMs = other.m_nMs;
#else
	QDateTime::operator= ( (const CTime &)other);
#endif
	return *this;
}

void CTime::GetAsSystemTime(SYSTEMTIME &tm)
{
#ifdef USE_Custom_CDateTime
	short nYear = tm.wYear;
	short nMonth = tm.wMonth;
	short nDay = tm.wDay;
	short nHour = tm.wHour;
	short nMinute = tm.wMinute;
	short nSecond = tm.wSecond;
	TransTimer_LongTime(m_nSecond,nYear,nMonth,nDay,nHour,nMinute,nSecond);
	tm.wYear = nYear;
	tm.wMonth = nMonth;
	tm.wDay = nDay;
	tm.wHour = nHour;
	tm.wMinute = nMinute;
	tm.wSecond = nSecond;
	tm.wMilliseconds = m_nMs;
#else
 	QDate qdate = date();
 	QTime qtime = time();
 	tm.wYear = qdate.year();
 	tm.wMonth = qdate.month();
 	tm.wDay = qdate.day();
 	tm.wHour = qtime.hour();
 	tm.wMinute = qtime.minute();
 	tm.wSecond = qtime.second();
 	tm.wMilliseconds = qtime.msec();
#endif
}

void CTime::Format(const CString &strTime)
{
#ifdef USE_Custom_CDateTime
	SYSTEMTIME tm;
	CString_To_SystemTime(strTime,tm);
	CTime oTm(tm);
	*this = oTm;
#else
 	QDateTime tm = QDateTime::fromString(strTime);
 	((QDateTime&)*this) = tm;
#endif
}

double CTime::GetTime()
{
#ifdef USE_Custom_CDateTime
	double dTime = m_nSecond*1000.0f + m_nMs;
	return dTime;
#else
	return (double)toMSecsSinceEpoch();
#endif
}

unsigned short CTime::GetYear()
{
#ifdef USE_Custom_CDateTime
	short nYear = 1970;
	short nMonth = 1;
	short nDay = 1;
	short nHour = 0;
	short nMinute = 0;
	short nSecond = 0;
	TransTimer_LongTime(m_nSecond,nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return nYear;
#else
 	QDate qdate = date();
 	return qdate.year();
#endif
}
unsigned short CTime::GetMonth()
{
#ifdef USE_Custom_CDateTime
	short nYear = 1970;
	short nMonth = 1;
	short nDay = 1;
	short nHour = 0;
	short nMinute = 0;
	short nSecond = 0;
	TransTimer_LongTime(m_nSecond,nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return nMonth;
#else
	QDate qdate = date();
	return qdate.month();
#endif
}
unsigned short CTime::GetDay()
{
#ifdef USE_Custom_CDateTime
	short nYear = 1970;
	short nMonth = 1;
	short nDay = 1;
	short nHour = 0;
	short nMinute = 0;
	short nSecond = 0;
	TransTimer_LongTime(m_nSecond,nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return nDay;
#else
	QDate qdate = date();
	return qdate.day();
#endif
}

unsigned short CTime::GetHour()
{
#ifdef USE_Custom_CDateTime
	short nYear = 1970;
	short nMonth = 1;
	short nDay = 1;
	short nHour = 0;
	short nMinute = 0;
	short nSecond = 0;
	TransTimer_LongTime(m_nSecond,nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return nHour;
#else
	QTime qtime = time();
	return qtime.hour();
#endif
}
unsigned short CTime::GetMinute()
{
#ifdef USE_Custom_CDateTime
	short nYear = 1970;
	short nMonth = 1;
	short nDay = 1;
	short nHour = 0;
	short nMinute = 0;
	short nSecond = 0;
	TransTimer_LongTime(m_nSecond,nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return nMinute;
#else
	QTime qtime = time();
	return qtime.minute();
#endif
}
unsigned short CTime::GetSecond()
{
#ifdef USE_Custom_CDateTime
	short nYear = 1970;
	short nMonth = 1;
	short nDay = 1;
	short nHour = 0;
	short nMinute = 0;
	short nSecond = 0;
	TransTimer_LongTime(m_nSecond,nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return nSecond;
#else
	QTime qtime = time();
	return qtime.second();
#endif
}

#ifdef USE_Custom_CDateTime
CTime CTime::GetTime_FromString(const CString &strTime)
{
	SYSTEMTIME tm;
	CString_To_SystemTime(strTime,tm);
	CTime oTm(tm);
	return oTm;
}
#endif

#ifdef _PSX_QT_LINUX_
void GetLocalTime(SYSTEMTIME *tm)
{
//是否使用自定义的时间对象
#ifdef USE_Custom_CDateTime
    int nYear = 1970, nMon = 1, nDay = 1, nHour = 0, nMin = 0, nSec = 0,nMs = 0;
    CDateTime::GetTime(nYear,nMon,nDay,nHour,nMin,nSec,nMs);
    tm->wYear = nYear;
    tm->wMonth = nMon;
    tm->wDay = nDay;
    tm->wHour = nHour;
    tm->wMinute = nMin;
    tm->wSecond = nSec;
    tm->wMilliseconds = nMs;
//	CDateTime::GetTime(,tm->wMonth,tm->wDay,tm->wHour,tm->wMinute,tm->wSecond,tm->wMilliseconds);
#else
    QDateTime current_date_time =QDateTime::currentDateTime();
    QDate qdate = current_date_time.date();
    QTime qtime = current_date_time.time();

    tm->wYear = qdate.year();
    tm->wMonth = qdate.month();
    tm->wDay = qdate.day();
    tm->wHour = qtime.hour();
    tm->wMinute = qtime.minute();
    tm->wSecond = qtime.second();
    tm->wMilliseconds = qtime.msec();
#endif
}
#endif
