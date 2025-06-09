//#ifndef MUTC_LOCAL_H
//#define MUTC_LOCAL_H
#pragma once

#include <time.h>

#define uint32	unsigned int

typedef struct
{
	uint32 sec;
	uint32 fsec;	//秒的小数，最小单位纳秒
}MUTC;

typedef struct
{
	uint32 year;
	uint32 mon;
	uint32 day;
	uint32 hour;
	uint32 min;
	uint32 sec;
	uint32 msec;
	uint32 usec;
	uint32 nsec;
}LOCALTIME;

inline BOOL MUTC2Std(MUTC *mTime, LOCALTIME *sTime,unsigned nCode)
{
	time_t st;
//	if((nCode&0x01)||(nCode&0x04))
//	{
//		mTime->sec+=946684799;//946771199;//;
//		mTime->fsec+=3435173036;
//	}
	if(nCode&0x01)mTime->sec+=28800;
	TIME_ZONE_INFORMATION tzi;
	GetTimeZoneInformation(&tzi);
	if(((nCode&0x01)>0||(nCode&0x04)>0)&&(time_t)mTime->sec>=-tzi.Bias*60-1)
		st= (time_t)mTime->sec + tzi.Bias*60+1  ; // B码为当地时间,需要转为格林威治时间.GPS为格林威治时间
	else st= (time_t)mTime->sec;
	if(st>0)
	{
	struct tm *p = localtime(&st);
		uint32 mSec = mTime->fsec / 1000000;
		uint32 unt = mTime->fsec % 1000000;

		uint32 uSes = unt / 1000;
		uint32 nSec = unt % 1000;

//		if(bCode)sTime->year = 1900 + p->tm_year+30;
//		else 
		sTime->year = 1900 + p->tm_year;
		sTime->mon = 1 + p->tm_mon;
		sTime->day = p->tm_mday;
		sTime->hour = p->tm_hour;
		sTime->min = p->tm_min;
		sTime->sec = p->tm_sec;
		sTime->msec = mSec;
		sTime->usec = uSes;
		sTime->nsec = nSec;
		return TRUE;
	}
	else return FALSE;
}

inline void Std2MUTC(LOCALTIME *sTime, MUTC *mTime)
{
	struct tm t = {0};
	t.tm_year = sTime->year - 1900;
	t.tm_mon = sTime->mon - 1;
	t.tm_mday = sTime->day; 
	t.tm_hour = sTime->hour;
	t.tm_min = sTime->min;
	t.tm_sec = sTime->sec;

	time_t st = mktime(&t);

	mTime->sec = (UINT)st;//+28799;  //转为北京时间，以便和FPGA秒数比较
	
	mTime->fsec = sTime->msec * 1000000
		+ sTime->usec * 1000
		+ sTime->nsec;
}

//#endif