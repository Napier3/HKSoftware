// GpsPcTime.h: interface for the CGpsPcTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GPSPCTIME_H__)
#define _GPSPCTIME_H__

#include "../MemBuffer/BufferBase.h"

#define TIME_INIT_MODE_LOCAL  0
#define TIME_INIT_MODE_ZERO   1

typedef struct structGpsTime
{
	LONG nYear;
	LONG nMonth;
	LONG nDay;
	LONG nHour;
	LONG nMinute;
	LONG nSecond;
	LONG nMilliseconds;
	LONG nMicroseconds;
}*PGPSTIME, GPSTIME;

typedef struct structPcTime
{
	LONG nYear;
	LONG nMonth;
	LONG nDay;
	LONG nHour;
	LONG nMinute;
	LONG nSecond;
	LONG nMilliseconds;
	LONG nTickCount;
}*PPCTIME, PCTIME;

typedef struct structGpsPcTimeMap
{
	GPSTIME tmGps;
	PCTIME tmPc;
}*PGPSPCTIMEMAP, GPSPCTIMEMAP;

inline PGPSTIME tm_CreateGpsTime()
{
	PGPSTIME pTm = (PGPSTIME)malloc(sizeof(GPSTIME));
	memset(pTm, 0, sizeof(GPSTIME));
	return pTm;
}


inline PGPSTIME tm_CreateGpsTime(long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs)
{
	PGPSTIME pTm = (PGPSTIME)malloc(sizeof(GPSTIME));
	memset(pTm, 0, sizeof(GPSTIME));
	pTm->nYear = nYear;
	pTm->nMonth = nMonth;
	pTm->nDay = nDay;
	pTm->nHour = nHour;
	pTm->nMinute = nMinute;
	pTm->nSecond = nS;
	pTm->nMilliseconds = nMs;
	pTm->nMicroseconds = nUs;
	return pTm;
}

inline PPCTIME tm_CreatePcTime()
{
	PPCTIME pTm = (PPCTIME)malloc(sizeof(PCTIME));
	memset(pTm, 0, sizeof(PCTIME));
	return pTm;
}

inline PGPSPCTIMEMAP tm_CreateGpsPcTimeMap()
{
	PGPSPCTIMEMAP pTmMap = (PGPSPCTIMEMAP)malloc(sizeof(GPSPCTIMEMAP));
	memset(pTmMap, 0, sizeof(GPSPCTIMEMAP));
	return pTmMap;
}

inline void tm_InitPcTime(PPCTIME pTm, SYSTEMTIME tmSys)
{
	pTm->nYear = tmSys.wYear;
	pTm->nMonth = tmSys.wMonth;
	pTm->nDay = tmSys.wDay;
	pTm->nHour = tmSys.wHour;
	pTm->nMinute = tmSys.wMinute;
	pTm->nSecond = tmSys.wSecond;
	pTm->nMilliseconds = tmSys.wMilliseconds;
}

inline void tm_InitGpsTime(PGPSTIME pTm, SYSTEMTIME tmSys)
{
	pTm->nYear = tmSys.wYear;
	pTm->nMonth = tmSys.wMonth;
	pTm->nDay = tmSys.wDay;
	pTm->nHour = tmSys.wHour;
	pTm->nMinute = tmSys.wMinute;
	pTm->nSecond = tmSys.wSecond;
	pTm->nMilliseconds = tmSys.wMilliseconds;
	pTm->nMicroseconds = 0;
}

inline long CompareSysTime(const SYSTEMTIME &tm1, const SYSTEMTIME &tm2)
{
	if (tm1.wYear > tm2.wYear)
	{
		return 1;
	}
	else if (tm1.wYear < tm2.wYear)
	{
		return -1;
	}

	if (tm1.wMonth > tm2.wMonth)
	{
		return 1;
	}
	else if (tm1.wMonth < tm2.wMonth)
	{
		return -1;
	}

	if (tm1.wDay > tm2.wDay)
	{
		return 1;
	}
	else if (tm1.wDay < tm2.wDay)
	{
		return -1;
	}

	if (tm1.wHour > tm2.wHour)
	{
		return 1;
	}
	else if (tm1.wHour < tm2.wHour)
	{
		return -1;
	}

	if (tm1.wMinute > tm2.wMinute)
	{
		return 1;
	}
	else if (tm1.wMinute < tm2.wMinute)
	{
		return -1;
	}

	if (tm1.wSecond > tm2.wSecond)
	{
		return 1;
	}
	else if (tm1.wSecond < tm2.wSecond)
	{
		return -1;
	}

	if (tm1.wMilliseconds > tm2.wMilliseconds)
	{
		return 1;
	}
	else if (tm1.wMilliseconds < tm2.wMilliseconds)
	{
		return -1;
	}

	return 0;
}

inline BOOL IsSysTimeEqual(SYSTEMTIME tm1, SYSTEMTIME tm2)
{
	if (tm1.wYear != tm2.wYear)
	{
		return FALSE;
	}

	if (tm1.wMonth != tm2.wMonth)
	{
		return FALSE;
	}

	if (tm1.wDayOfWeek != tm2.wDayOfWeek)
	{
		return FALSE;
	}

	if (tm1.wDay != tm2.wDay )
	{
		return FALSE;
	}

	if (tm1.wHour != tm2.wHour)
	{
		return FALSE;
	}

	if (tm1.wMinute != tm2.wMinute)
	{
		return FALSE;
	}

	if (tm1.wSecond != tm2.wSecond)
	{
		return FALSE;
	}

	if (tm1.wMilliseconds != tm2.wMilliseconds)
	{
		return FALSE;
	}
	return TRUE;
}

inline BOOL IsSysTimeEqual_Short(SYSTEMTIME tm1, SYSTEMTIME tm2)
{
	if (tm1.wYear != tm2.wYear)
	{
		return FALSE;
	}

	if (tm1.wMonth != tm2.wMonth)
	{
		return FALSE;
	}

	if (tm1.wDay != tm2.wDay )
	{
		return FALSE;
	}

	return TRUE;
}

class CGpsPcTimeSpan
{
public:
	CGpsPcTimeSpan();
	CGpsPcTimeSpan(WORD wDay, WORD wHour, WORD wMinute, WORD wSecond, WORD wMilliseconds, WORD wMicroseconds);
	virtual ~CGpsPcTimeSpan();
	void InitByMilliseconds( long nMs);

	WORD m_wDay; 
	WORD m_wHour; 
	WORD m_wMinute; 
	WORD m_wSecond; 
	WORD m_wMilliseconds; 
	WORD m_wMicroseconds;	
	
public:
	CGpsPcTimeSpan& operator= (const CGpsPcTimeSpan &ts);
	DWORD GetTotalSecond();
	DWORD GetTotalMilliseconds();
	DWORD GetTotalMicroseconds();
	CString FormatString();
	void Validate();

private:
	void Init();
};

class CGpsPcTime 
{
public:
	CGpsPcTime();
	CGpsPcTime(const GPSTIME &tm);
	CGpsPcTime(const PCTIME &tm);
	CGpsPcTime(const SYSTEMTIME &tm);
	CGpsPcTime(WORD wYear, WORD wMonth, WORD wDay, WORD wHour, WORD wMinute, WORD wSecond, WORD wMilliseconds, WORD wMicroseconds);
	virtual ~CGpsPcTime();
    BOOL FromString(const CString &strTime, long nInitMode=TIME_INIT_MODE_LOCAL);
    BOOL FromStringEx(const CString &strTime, long nInitMode=TIME_INIT_MODE_LOCAL);
	void ToString(CString &strTime);
	void GetSysTime(SYSTEMTIME &tm);
    void Clear(long nInitMode=TIME_INIT_MODE_LOCAL);

public:
	short m_wYear; 
    short m_wMonth; 
    short m_wDay; 
    short m_wHour; 
    short m_wMinute; 
    short m_wSecond; 
    short m_wMilliseconds; 
	short m_wMicroseconds;

public:
	CGpsPcTime& operator= (const CGpsPcTime &tm);

	CGpsPcTime& operator-= (CGpsPcTimeSpan &ts);
	CGpsPcTime& operator+= (CGpsPcTimeSpan &ts);
	CGpsPcTimeSpan operator- (const CGpsPcTime &tm);

	BOOL operator> (const CGpsPcTime &tm);
	BOOL operator>= (const CGpsPcTime &tm);
	BOOL operator< (const CGpsPcTime &tm);
	BOOL operator<= (const CGpsPcTime &tm);
	BOOL operator== (const CGpsPcTime &tm);

	void GetGpsPcTime(GPSTIME &oGpsPcTime);
	void GetGpsPcTime(PCTIME &oGpsPcTime);

	DWORD GetTotalSecond();
	DWORD GetTotalMilliseconds();
	__time64_t GetTime_Int64();
	double GetTime_double();

private:
	void AdjustSub(BOOL bUseDayZero = FALSE);
	void AdjustAdd();
	long GetLongValue(CBufferBase &oBuffer, short &nValue);//char *pCurr, short &nValue, char *pEnd);
	long GetTime(CBufferBase &oBuffer);//char *pCurr, char *pEnd);
	long GetYyMmDd(CBufferBase &oBuffer);//char *pCurr, char *pEnd);

};

class CGpsPcTimeTickCount
{
public:
	CGpsPcTimeTickCount();
	virtual ~CGpsPcTimeTickCount();

	void Enter();
	long GetTickCountLong(BOOL bUdate=TRUE);

protected:
	CGpsPcTime m_oGpsPcTime;
	void InitByLocalTime(CGpsPcTime &tmGps);
};

inline CGpsPcTime operator+ (const CGpsPcTime& tm, CGpsPcTimeSpan& ts)
{
	CGpsPcTime t = tm;
	t += ts;
	return t;
}

inline CGpsPcTime operator- (const CGpsPcTime& tm, CGpsPcTimeSpan& ts)
{
	CGpsPcTime t = tm;
	t -= ts;
	return t;
}

/*
由于地球绕太阳运行周期为365天5小时48分46秒（合365.24219天）即一回归年，
公历把一年定为365天。所余下的时间约为四年累计一天，加在二月里，所以平常
年份每年365天，二月为28天，闰年为366天，二月为29天。因此，每400年中有97
个闰年，闰年在2月末增加一天，闰年366天。 闰年的计算方法：公元纪年的年数
可以被4整除，即为闰年；被100整除为平年；被100整除也可被400整除的为闰年。
公历每月有月大、月小和月平的说法，月大为31天，月小为30天，月平只有2月，
为28天（闰年29天）。 公历一年中每月天数:

月份 	1月 	2月 	3月		4月 	5月 	6月 	7月	 	8月 	9月 	10月	11月 	12月 
天数 	31 		28 		31 		30 		31 		30 		31 		31 		30 		31 		30 		31
　　				闰年29
 */

inline BOOL Mr_IsLeapYear(WORD wYear)
{
	if (wYear % 4 != 0)
	{
		return FALSE;
	}
	else
	{
		if (wYear % 100 == 0)
		{
			if (wYear % 400 == 0)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return TRUE;
		}
	}
}

inline WORD Mr_GetDaysOfMonth(WORD wYear, WORD wMonth)
{
	//ASSERT (1 <= wMonth && wMonth <= 12);

	if (!(1 <= wMonth && wMonth <= 12))
	{
		wMonth = 1;
	}

	WORD wDays = 0;

	static WORD g_wDaysOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (wMonth == 2)
	{
		if (Mr_IsLeapYear(wYear))
		{
			wDays = 29;
		}
		else
		{
			wDays = 28;
		}
	}
	else
	{
		wDays = g_wDaysOfMonth[wMonth-1];
	}

	return wDays;
}

inline void InitPcTime(const SYSTEMTIME &tmSys, PCTIME &tmPc)
{
	tmPc.nYear = tmSys.wYear;
	tmPc.nMonth = tmSys.wMonth;
	tmPc.nDay = tmSys.wDay;
	tmPc.nHour = tmSys.wHour;
	tmPc.nMinute = tmSys.wMinute;
	tmPc.nSecond = tmSys.wSecond;
	tmPc.nMilliseconds = tmSys.wMilliseconds;
}

inline void InitGpsTime(const SYSTEMTIME &tmSys, PCTIME &tmPc)
{
	tmPc.nYear = tmSys.wYear;
	tmPc.nMonth = tmSys.wMonth;
	tmPc.nDay = tmSys.wDay;
	tmPc.nHour = tmSys.wHour;
	tmPc.nMinute = tmSys.wMinute;
	tmPc.nSecond = tmSys.wSecond;
	tmPc.nMilliseconds = tmSys.wMilliseconds;
}

inline PCTIME operator+ (const PCTIME& tm, const long nMs)
{
	CGpsPcTime t1(tm);
	CGpsPcTimeSpan ts;
	ts.InitByMilliseconds(nMs);
	t1 += ts;
	PCTIME tmPc;
	t1.GetGpsPcTime(tmPc);
	return tmPc;
}

inline PCTIME operator- (const PCTIME& tm, const long nMs)
{
	CGpsPcTime t1(tm);
	CGpsPcTimeSpan ts;
	ts.InitByMilliseconds(nMs);
	t1 -= ts;
	PCTIME tmPc;
	t1.GetGpsPcTime(tmPc);
	return tmPc;
}


inline GPSTIME operator+ (const GPSTIME& tm, const long nMs)
{
	CGpsPcTime t1(tm);
	CGpsPcTimeSpan ts;
	ts.InitByMilliseconds(nMs);
	t1 += ts;
	GPSTIME tmPc;
	t1.GetGpsPcTime(tmPc);
	return tmPc;
}

inline GPSTIME operator- (const GPSTIME& tm, const long nMs)
{
	CGpsPcTime t1(tm);
	CGpsPcTimeSpan ts;
	ts.InitByMilliseconds(nMs);
	t1 -= ts;
	GPSTIME tmPc;
	t1.GetGpsPcTime(tmPc);
	return tmPc;
}

inline long GetSpanMSeconds(SYSTEMTIME &tmBegin,SYSTEMTIME &tmEnd)
{
	CGpsPcTime oBegin(tmBegin);
	CGpsPcTime oEnd(tmEnd);

	CGpsPcTimeSpan oSpan;
	oSpan = oEnd - oBegin;

	return oSpan.GetTotalMilliseconds();
}

#endif // !defined(_GPSPCTIME_H__)
//shaolei 2022-1-11 从别处挪到此处
void ep_cap_timeval_to_systime(const struct timeval &ts, SYSTEMTIME &tmSys);