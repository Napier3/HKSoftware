// RtTime.h: interface for the CRtTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTTIME_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)
#define AFX_RTTIME_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecordGlobalDefine.h"

class CRtTimeSpan
{
public:
	CRtTimeSpan();
	CRtTimeSpan(__int64 n64Val, DWORD dwSampleRate);
	CRtTimeSpan(WORD wDay, WORD wHour, WORD wMinute, WORD wSecond, WORD wMilliseconds, WORD wMicroseconds);
	virtual ~CRtTimeSpan();

	//WORD m_wYear; 
	//WORD m_wMonth; 
	WORD m_wDay; 
	WORD m_wHour; 
	WORD m_wMinute; 
	WORD m_wSecond; 
	WORD m_wMilliseconds; 
	WORD m_wMicroseconds;	
	
public:
	CRtTimeSpan& operator= (const CRtTimeSpan &ts);
	CRtTimeSpan& operator= (__int64 n64Val);
	__int64 GetInt64(DWORD dwSampleRate);
	DWORD GetTotalSecond();
	CString FormatString();
	
private:
	void Init(__int64 n64Val, DWORD dwSampleRate);
};

class CRtTime 
{
public:
	CRtTime(RTTIME &tm);
	CRtTime(WORD wYear, WORD wMonth, WORD wDay, WORD wHour, WORD wMinute, WORD wSecond, WORD wMilliseconds, WORD wMicroseconds);
	virtual ~CRtTime();
	
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
	CRtTime& operator= (const CRtTime &tm);

	CRtTime& operator-= (const CRtTimeSpan &ts);
	CRtTime& operator+= (const CRtTimeSpan &ts);
	CRtTimeSpan operator- (const CRtTime &tm);

	BOOL operator> (const CRtTime &tm);
	BOOL operator>= (const CRtTime &tm);
	BOOL operator< (const CRtTime &tm);
	BOOL operator<= (const CRtTime &tm);
	BOOL operator== (const CRtTime &tm);

	void GetRtTime(RTTIME &oRtTime);

private:
	void AdjustSub(BOOL bUseDayZero = FALSE);
	void AdjustAdd();

	CRtTime(){}
};

inline CRtTime operator+ (const CRtTime& tm, const CRtTimeSpan& ts)
{
	CRtTime t = tm;
	t += ts;
	return t;
}

inline CRtTime operator- (const CRtTime& tm, const CRtTimeSpan& ts)
{
	CRtTime t = tm;
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

#endif // !defined(AFX_RTTIME_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)
