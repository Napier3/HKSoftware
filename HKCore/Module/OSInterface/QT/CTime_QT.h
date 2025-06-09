
#ifndef _CTime_QT_h__
#define _CTime_QT_h__

#include "CString_QT.h"
#include "XGlobalDefine_QT.h"
#include "qdatetime.h"

#ifdef USE_Custom_CDateTime
class CTime
#else
class CTime : public QDateTime
#endif
{
public:
    CTime();

    CTime(qint64 n64Time);
//     {
//         setMSecsSinceEpoch(n64Time);
//     }

    //xupf
    CTime(SYSTEMTIME tm);
//     {
//         QDate qdt(tm.wYear, tm.wMonth, tm.wDay) ;
//         QTime qtm(tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
//         QDateTime(qdt, qtm);
//     }

    virtual ~CTime()
    {
    }

    /*inline*/ CTime &operator = (QDateTime &other);
//     {
//         QDateTime::operator= ( (const QDateTime &)other);
//         return *this;
//     }

    /*inline*/ CTime &operator = (CTime &other);
//     {
//         QDateTime::operator= ( (const CTime &)other);
//         return *this;
//     }

    /*inline*/ void GetAsSystemTime(SYSTEMTIME &tm);
//     {
//         QDate qdate = date();
//         QTime qtime = time();
//         tm.wYear = qdate.year();
//         tm.wMonth = qdate.month();
//         tm.wDay = qdate.day();
//         tm.wHour = qtime.hour();
//         tm.wMinute = qtime.minute();
//         tm.wSecond = qtime.second();
//         tm.wMilliseconds = qtime.msec();
//     }

    /*inline*/ void Format(const CString &strTime);
//     {
//         QDateTime tm = QDateTime::fromString(strTime);
//         ((QDateTime&)*this) = tm;
//     }

    inline CString Format(char *pszFormat)
    {
		pszFormat = 0;
        return GetTimeString();
    }

/*    inline __int64 GetTime()
    {
        toMSecsSinceEpoch();
    }
*/
    /*inline*/ double GetTime();
//     {
//         return (double)toMSecsSinceEpoch();
//     }

    //xupf
    static CTime GetCurrentTime()
    {
       return CTime(0);
    }

    unsigned short GetYear();
//     {
//         QDate qdate = date();
//         return qdate.year();
//     }
    unsigned short GetMonth();
//     {
//         QDate qdate = date();
//         return qdate.month();
//     }
    unsigned short GetDay();
//     {
//          QDate qdate = date();
//         return qdate.day();
//     }

    unsigned short GetHour();
//     {
//        QTime qtime = time();
//         return qtime.hour();
//     }
    unsigned short GetMinute();
//     {
//        QTime qtime = time();
//         return qtime.minute();
//     }
    unsigned short GetSecond();
//     {
//        QTime qtime = time();
//         return qtime.second();
//     }
    inline CString GetTimeString()
    {
        CString strTime;
        strTime.Format("%d%02d%02d%02d%02d%02d", GetYear(), GetMonth(), GetDay(), GetHour(), GetMinute(), GetSecond());
        return strTime;
    }
#ifdef USE_Custom_CDateTime
	static CTime GetTime_FromString(const CString &strTime);
private:
	long m_nSecond;
	long m_nMs;
#endif
};

#ifdef _PSX_QT_LINUX_
void GetLocalTime(SYSTEMTIME *tm);
#endif

#endif  // _CTime_QT_h__
