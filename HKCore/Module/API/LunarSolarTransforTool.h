#pragma once

typedef CArray <SYSTEMTIME> CArraySystemTime;

//某年所有公休日期数组
extern CArraySystemTime g_ArrHoldayDates;

//在日期数组中查找指定日期是否存在
int FindTimeArr(CArraySystemTime &tmArr,SYSTEMTIME &tm);

//判断是否是闰年
BOOL IsLeapYear(WORD nYear);

WORD GetWeekDay(SYSTEMTIME &tm);

//返回阴历nLunarYear年的闰月月份，如没有返回0
long GetLeapMonth(WORD nLunarYear);

//返回阴历nLunarYear年nLunarMonth月的天数
long GetLunarMonthDays(WORD nLunarYear, WORD nLunarMonth);

//返回阴历nLunarYear年第二个闰月的天数，没有闰月返回0
long GetLunarLeapMonthDays(WORD nLunarYear);

//获取阴历nLunarYear年春节公历日期
BOOL GetLunarSpringDate(WORD nLunarYear, WORD &nSolarMonth, WORD &nSolarDay);

//检查阴历日期是否正确
BOOL CheckLunarDate(WORD nLunarYear, WORD nLunarMonth, WORD nLunarDay);

//检查阳历日期是否正确
BOOL CheckSolarDate(WORD nSolarYear, WORD nSolarMonth, WORD nSolarDay);

//阴历转阳历日期
BOOL LunarToSolarDate(WORD nLunarYear, WORD nLunarMonth, WORD nLunarDay
					  ,WORD &nSolarYear, WORD &nSolarMonth, WORD &nSolarDay);
//阴历转阳历日期
BOOL LunarToSolarDate(WORD nLunarYear, WORD nLunarMonth, WORD nLunarDay
					  ,SYSTEMTIME &tm);

//阳历转阴历日期
BOOL SolarToLunarDate(WORD nSolarYear, WORD nSolarMonth, WORD nSolarDay
					  ,WORD &nLunarYear, WORD &nLunarMonth, WORD &nLunarDay);

//获取指定日期
void GetFixedDate(SYSTEMTIME &tmCurr,long nDays=1);

void InitPublicHoldayDate(WORD nYear,CArraySystemTime &tmArr);

BOOL GetHoldayArrBetweenDates(CArraySystemTime &tmArrHolday
							  ,SYSTEMTIME tmBegin,SYSTEMTIME tmEnd);