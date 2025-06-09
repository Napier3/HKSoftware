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
���ڵ�����̫����������Ϊ365��5Сʱ48��46�루��365.24219�죩��һ�ع��꣬
������һ�궨Ϊ365�졣�����µ�ʱ��ԼΪ�����ۼ�һ�죬���ڶ��������ƽ��
���ÿ��365�죬����Ϊ28�죬����Ϊ366�죬����Ϊ29�졣��ˣ�ÿ400������97
�����꣬������2��ĩ����һ�죬����366�졣 ����ļ��㷽������Ԫ���������
���Ա�4��������Ϊ���ꣻ��100����Ϊƽ�ꣻ��100����Ҳ�ɱ�400������Ϊ���ꡣ
����ÿ�����´���С����ƽ��˵�����´�Ϊ31�죬��СΪ30�죬��ƽֻ��2�£�
Ϊ28�죨����29�죩�� ����һ����ÿ������:

�·� 	1�� 	2�� 	3��		4�� 	5�� 	6�� 	7��	 	8�� 	9�� 	10��	11�� 	12�� 
���� 	31 		28 		31 		30 		31 		30 		31 		31 		30 		31 		30 		31
����				����29
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
