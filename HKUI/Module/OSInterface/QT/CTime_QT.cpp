
#include "CTime_QT.h"
#include "../../Log/LogPrint.h"

#ifdef USE_Custom_CDateTime
#include"CDateTime_QT.h"
#endif

CTime::CTime()
{
//	CLogPrint::LogString(XLOGLEVEL_RESULT,_T("CTime Create"));
}

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
