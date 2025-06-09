#pragma once

typedef CArray <SYSTEMTIME> CArraySystemTime;

//某年所有公休日期数组
//extern CArraySystemTime g_ArrHoldayDates;

//debug模式下打印日期信息
void TraceDateInfo(CArraySystemTime &tmArr,const WORD &nBeginYear,const WORD &nEndYear
				   ,const CString &strInfo);
void TraceDateInfo(CArraySystemTime &tmArr,const SYSTEMTIME &tmBegin,const SYSTEMTIME &tmEnd
				   ,const CString &strInfo);

//在日期数组中查找指定日期是否存在
int FindTimeArr(CArraySystemTime &tmArr,SYSTEMTIME &tm);

BOOL IsTimeIntervalCorrect(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd);
BOOL IsDateIntervalCorrect(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd);
BOOL IsDuring_TimeInterval(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd ,const SYSTEMTIME &tmCurTime);
BOOL IsDuring_DateInterval(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd ,const SYSTEMTIME &tmCurTime);
BOOL IsDuring_DateInterval(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd ,const CTime &tmCurTime);

void GetDateString(SYSTEMTIME &tm,CString &strTime,BOOL bDayOfWeek=FALSE);
void GenrerateDateString(CArraySystemTime &tmArr,CString &strTime,BOOL bDayOfWeek=FALSE);

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
void GetFixedDate(const SYSTEMTIME &tmCurr,SYSTEMTIME &tmFixed,long nDays=1);

void InitPublicHoldayDate(WORD nYear,CArraySystemTime &tmArr);
void InitPublicHoldayDate(WORD nBeginYear,WORD nEndYear,CArraySystemTime &tmArrHoliday);

//返回开始时间、结束时间之间共多少天
long GetHoldayArrBetweenDates(CArraySystemTime &tmArrHolday,const SYSTEMTIME &tmBegin
								,const SYSTEMTIME &tmEnd);

//开始时间、结束时间之间总天数,不存在日期tmArrUnExistDate，bFilterHoliday是否过滤休息日
BOOL FilterUnExistDateArrBetweenDates(CArraySystemTime &tmArrExistDate
								,CArraySystemTime &tmArrUnExistDate
								,CArraySystemTime &tmArrHolidayDate
								,const SYSTEMTIME &tmBegin ,const SYSTEMTIME &tmEnd
								,BOOL bFilterHoliday=TRUE);

///////////////////////////////////////////////////////

void OA_GetTime(CDateTimeCtrl *pDateTimeCtrl, SYSTEMTIME &tmOA, BOOL bShortTime=TRUE);

//初始化日期控件
void InitQueryBeginTime(CDateTimeCtrl &m_dtcStart,CDateTimeCtrl &m_dtcEnd,int nDays);
//检查时间控件是否正确，生成mysql过滤字符串
BOOL CheckTimeIsRight(SYSTEMTIME &tmStart,SYSTEMTIME &tmEnd
					  ,const CString &strTmPK,CString &strFilter_Date);
BOOL CheckTimeIsRight(CDateTimeCtrl &m_dtcStart,CDateTimeCtrl &m_dtcEnd
					  ,const CString &strTmPK,CString &strFilter_Date);
BOOL CheckTimeIsRight(CDateTimeCtrl &m_dtcStart,CDateTimeCtrl &m_dtcEnd);
void ModifyQueryEndTime(SYSTEMTIME& tmEnd);