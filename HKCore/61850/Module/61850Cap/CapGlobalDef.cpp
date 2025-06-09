#include "StdAfx.h"
#include "CapGlobalDef.h"

#include "..\CriticalSection\SynCriticalSection.h"

#define _use_CaptureIDCriticSection
volatile __int64 g_nCaptureID = 0;

#ifdef _use_CaptureIDCriticSection
CAutoCriticSection g_pCaptureIDCriticSection;
CAutoCriticSection g_oCapWriteCriticSection;
#endif

DWORD g_nEpCapBufferWriteState = 0;
DWORD g_nEpCapWriteCounter = 0;

volatile __int64 Ep_Cap_GenerateCaptureID()
{
#ifdef _use_CaptureIDCriticSection
	CAutoSimpleLock oLock(g_pCaptureIDCriticSection);
#endif

	g_nCaptureID++;
	return g_nCaptureID;	
}


void ep_cap_timeval_to_time(const struct timeval &ts, EP_ETHER_CAP_TIME &time)
{
	int i,year,month,day,hour,minute,second;
	long tmp;
	int dyr[12]={31,29,31,30,31,30,31,31,30,31,30,31}; //闰年月份
	int dyp[12]={31,28,31,30,31,30,31,31,30,31,30,31}; //平年
	bool flag=0;
	long t = ts.tv_sec;
	int *pdy = NULL;
	int days=0;

	for(year=1970; ;year++)
	{
		if((year%400==0)||(year%4==0 && year%100!=0)) //润年
		{
			days = 366;
			pdy = dyr;
		}
		else
		{
			days = 365;
			pdy = dyp;
		}

		tmp=days*24*60*60;

		if(t >= tmp)
		{
			t = t - tmp;
		}
		else
		{

			for(i=0;i<12;i++)
			{
				tmp=pdy[i]*24*60*60;

				if(t>=tmp)
				{
					t=t-tmp;
				}
				else
				{
					month=i+1;
					day=t/(24*60*60)+1;
					t=t-(day-1)*24*60*60;
					hour=t/(60*60);
					t=t-hour*60*60;
					minute=t/60;
					second=t%60;
					flag=1;
					break;
				}
			}
		}

		if(flag) 
		{
			break;
		}
	}


	SYSTEMTIME tmSys;
	tmSys.wYear = year;
	tmSys.wMonth = month;
	tmSys.wDay = day;
	tmSys.wHour = hour;
	tmSys.wMinute = minute;
	tmSys.wSecond = second;

	CTime ctime(tmSys);
	CTimeSpan tmSpan(0, 8, 0, 0);
	ctime += tmSpan;
	ctime.GetAsSystemTime(tmSys);

	time.year = tmSys.wYear;
	time.month = tmSys.wMonth;
	time.day = tmSys.wDay;
	time.hour = tmSys.wHour;
	time.minute = minute;
	time.second = second;
	time.usec = ts.tv_usec;
}

void ep_time_to_cap_timeval(const EP_ETHER_CAP_TIME &time, struct timeval &ts)
{
	ts.tv_usec = time.usec;
	ts.tv_sec = 0;

	int dyr[12]={31,29,31,30,31,30,31,31,30,31,30,31}; //闰年月份
	int dyp[12]={31,28,31,30,31,30,31,31,30,31,30,31}; //平年
	int *pdy = NULL;
	int year = 0;
	int i = 1;

	for(year=1970; year <time.year ;year++)
	{
		if((year%400==0)||(year%4==0 && year%100!=0)) //润年
		{
			ts.tv_sec += 366*24*60*60;
		}
		else
		{
			ts.tv_sec += 365*24*60*60;
		}
	}

	if((time.year%400==0)||(time.year%4==0 && time.year%100!=0)) //润年
	{
		pdy = dyr;
	}
	else
	{
		pdy = dyp;
	}

	for(i=1;i<time.month; i++)
	{
		ts.tv_sec += pdy[i]*24*60*60;
	}

	ts.tv_sec += (time.day-1)*24*60*60; //day
	ts.tv_sec += time.hour*60*60;
	ts.tv_sec += time.minute*60;
	ts.tv_sec += time.second;
}

void ep_curr_cap_timeval(struct timeval &ts)
{
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	EP_ETHER_CAP_TIME time;
	time.year = tm.wYear;
	time.month = tm.wMonth;
	time.day = tm.wDay;
	time.hour = tm.wHour;
	time.minute = tm.wMinute;
	time.second = tm.wSecond;
	time.usec = tm.wMilliseconds*1000;
	ep_time_to_cap_timeval(time, ts);
}

