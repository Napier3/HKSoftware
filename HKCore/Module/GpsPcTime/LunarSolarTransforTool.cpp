#include "stdafx.h"
#include "LunarSolarTransforTool.h"
#include "GpsPcTime.h"
#include "..\BaseClass\XDbSQLFieldObject.h"

//某年所有公休日期数组
//CArraySystemTime g_ArrHoldayDates;

void TraceDateInfo(CArraySystemTime &tmArr,const WORD &nBeginYear,const WORD &nEndYear
				   ,const CString &strInfo)
{
	return;
#ifdef _DEBUG
	CString strTime,str;
	GenrerateDateString(tmArr,strTime,TRUE);
	str.Format(_T("%04d-%04d年法定公休日【%d天】：%s")
		,nBeginYear,nEndYear,tmArr.GetSize(),strTime);
	CLogPrint::LogString(XLOGLEVEL_TRACE, str);
#endif
}

void TraceDateInfo(CArraySystemTime &tmArr,const SYSTEMTIME &tmBegin,const SYSTEMTIME &tmEnd
				   ,const CString &strInfo)
{
	return;
#ifdef _DEBUG
	CString strTime,str;
	GenrerateDateString(tmArr,strTime,TRUE);
	str.Format(_T("%04d年%02d月%02d日-%04d年%02d月%02d日%s【%d天】：%s")
		,tmBegin.wYear,tmBegin.wMonth,tmBegin.wDay
		,tmEnd.wYear,tmEnd.wMonth,tmEnd.wDay
		,strInfo,tmArr.GetSize(),strTime);
	CLogPrint::LogString(XLOGLEVEL_TRACE, str);
#endif
}


BOOL IsTimeIntervalCorrect(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd)
{
	CTime oT_Start(tmStart);
	CTime oT_End(tmEnd);

	if (oT_Start <= oT_End)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL IsDateIntervalCorrect(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd)
{
	CTime oT_Start(tmStart.wYear,tmStart.wMonth,tmStart.wDay,0,0,0);
	CTime oT_End(tmEnd.wYear,tmEnd.wMonth,tmEnd.wDay,0,0,0);

	if (oT_Start > oT_End)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL IsDuring_TimeInterval(const SYSTEMTIME &tmStart,const SYSTEMTIME &tmEnd 
						   ,const SYSTEMTIME &tmCurTime)
{
	CTime oT_Start(tmStart);
	CTime oT_End(tmEnd);
	CTime oT_Cur(tmCurTime);

	if (oT_Cur>=oT_Start && oT_Cur<=oT_End)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL IsDuring_DateInterval(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd 
						   ,const SYSTEMTIME &tmCurTime)
{
	CTime oT_Start(tmStart.wYear,tmStart.wMonth,tmStart.wDay,0,0,0);
	CTime oT_End(tmEnd.wYear,tmEnd.wMonth,tmEnd.wDay,0,0,0);
	CTime oT_Cur(tmCurTime.wYear,tmCurTime.wMonth,tmCurTime.wDay,0,0,0);

	if (oT_Cur>=oT_Start && oT_Cur<=oT_End)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL IsDuring_DateInterval(const SYSTEMTIME &tmStart, const SYSTEMTIME &tmEnd 
						   ,const CTime &tmCurTime)
{
	CTime oT_Start(tmStart.wYear,tmStart.wMonth,tmStart.wDay,0,0,0);
	CTime oT_End(tmEnd.wYear,tmEnd.wMonth,tmEnd.wDay,0,0,0);
	CTime oT_Cur(tmCurTime.GetYear(),tmCurTime.GetMonth(),tmCurTime.GetDay(),0,0,0);

	if (oT_Cur>=oT_Start && oT_Cur<=oT_End)
	{
		return TRUE;
	}

	return FALSE;
}

void GetDateString(SYSTEMTIME &tm,CString &strTime,BOOL bDayOfWeek)
{
	SystemTime_To_ShortString(tm,strTime);

	if (!bDayOfWeek)
	{
		return;
	}

	WORD nDayOfWeek = tm.wDayOfWeek;

	switch(nDayOfWeek)
	{
	case 0:strTime.AppendFormat(_T("(星期日)"));break;
	case 1:strTime.AppendFormat(_T("(星期一)"));break;
	case 2:strTime.AppendFormat(_T("(星期二)"));break;
	case 3:strTime.AppendFormat(_T("(星期三)"));break;
	case 4:strTime.AppendFormat(_T("(星期四)"));break;
	case 5:strTime.AppendFormat(_T("(星期五)"));break;
	case 6:strTime.AppendFormat(_T("(星期六)"));break;
	default:break;
	}
}

void GenrerateDateString(CArraySystemTime &tmArr,CString &strTime,BOOL bDayOfWeek)
{
	SYSTEMTIME tm;
	CString str;
	int nCount = tmArr.GetSize();
	strTime = _T("");

	for (int i=0; i < nCount; i++)
	{
		tm = tmArr[i];

		GetDateString(tm,str,bDayOfWeek);
		strTime.AppendFormat(_T("%s; "),str);

		if ((i+1) % 3 == 0)
		{
			strTime = strTime + _T("\r\n");
		}
	}
}

int FindTimeArr(CArraySystemTime &tmArr,SYSTEMTIME &tm)
{
	SYSTEMTIME tmTemp;
	int nCount = tmArr.GetSize();
	int nFind = -1;

	for (int i=0; i < nCount; i++)
	{
		tmTemp = tmArr[i];

		if ((tmTemp.wYear == tm.wYear)
			&& (tmTemp.wMonth == tm.wMonth)
			&& (tmTemp.wDay == tm.wDay) )
		{
			nFind = i;
			break;
		}
	}
	return nFind;
}


/*
  bit23 bit22 bit21 bit20:表示当年闰月月份，值为0 为则表示当年无闰月

  bit19 bit18 bit17 bit16 bit15 bit14 bit13 bit12 bit11 bit10 bit9 bit8 bit7
    1     2     3     4     5     6     7     8     9     10    11   12   13
  农历1-13 月大小 。月份对应位为1，农历月大(30 天),为0 表示小(29 天)

  bit6 bit5 bit4 bit3 bit2 bit1 bit0
  春节的公历月份      春节的公历日期
*/
unsigned long lunar200y[199] = {
    0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A,/*1901-1910*/
    0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754,/*1911-1920*/
    0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E,/*1921-1930*/
    0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48,/*1931-1940*/
    0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51,/*1941-1950*/
    0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x6AD53C,/*1951-1960*/
    0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46,/*1961-1970*/
    0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50,/*1971-1980*/
    0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB,/*1981-1990*/
    0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645,/*1991-2000*/
    0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E,/*2001-2010*/
    0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9,/*2011-2020*/
    0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43,/*2021-2030*/
    0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C,/*2031-2040*/
    0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37,/*2041-2050*/
    0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42,/*2051-2060*/
    0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B,/*2061-2070*/
    0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6,/*2071-2080*/
    0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E,/*2081-2090*/
    0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5          /*2091-2099*/
};

int g_nArrMonthSumDays[13] = {0,31,59,90,120,151,181,212,243,273,304,334,365};

BOOL IsLeapYear(WORD nYear)
{
	return !(nYear%4)&&(nYear%100) || (!(nYear%400));
}

#define MIN_YEAR 1901
#define MAX_YEAR 2099

//计算公历时间对应是星期几
WORD GetWeekDay(SYSTEMTIME &tm)
{
	//数组元素nMonthDay[i]表示第i个月以前的总天数除以7的余数
	WORD nArrMonthDay[]={0,3,3,6,1,4,6,2,5,0,3,5};

	WORD nDays = (tm.wYear-1)%7 + (tm.wYear-1)/4
					- (tm.wYear-1)/100 +(tm.wYear-1)/400;
	nDays += (nArrMonthDay[tm.wMonth-1] +tm.wDay) ;
	//如果iYear是闰年
	if(IsLeapYear(tm.wYear) && tm.wMonth>2)
		nDays++;

	tm.wDayOfWeek = nDays%7;
	//返回:0,1,2,3,4,5,6表日、一、二、三、四、五、六
	return tm.wDayOfWeek;
}

//0x04AE53
//
//0000 0100 1010 1110 0  101 0011
//返回阴历nLunarYear年的闰月月份，如没有返回0
long GetLeapMonth(WORD nLunarYear)
{
	return((lunar200y[nLunarYear-MIN_YEAR] & 0xf00000) >> 20);
}

//返回阴历nLunarYear年nLunarMonth月的天数
long GetLunarMonthDays(WORD nLunarYear, WORD nLunarMonth)
{
	return( (lunar200y[nLunarYear-MIN_YEAR] & (0x80000 >> (nLunarMonth-1))) ?  30:29 );
}

//返回阴历nLunarYear年第二个闰月的天数，没有闰月返回0
long GetLunarLeapMonthDays(WORD nLunarYear)
{
	long nLeapMonth = GetLeapMonth(nLunarYear);

	if(nLeapMonth != 0)
	{//有闰月，将第二个闰月的天数返回
		return( (lunar200y[nLunarYear-MIN_YEAR] & (0x80000 >> (nLeapMonth-1))) ?  30:29 );
	}
	else
	{
		return 0;
	}
}

//获取阴历nLunarYear年春节公历日期
BOOL GetLunarSpringDate(WORD nLunarYear, WORD &nSolarMonth, WORD &nSolarDay)
{
	nSolarMonth = (lunar200y[nLunarYear-MIN_YEAR] & 0x0060) >> 5;
	nSolarDay = lunar200y[nLunarYear-MIN_YEAR] & 0x1f;

	return TRUE;
}

//检查阴历日期是否正确
BOOL CheckLunarDate(WORD nLunarYear, WORD nLunarMonth, WORD nLunarDay)
{
	if ((nLunarYear < MIN_YEAR) || (nLunarYear > MAX_YEAR))
	{
	    return FALSE;
	}

	if ((nLunarMonth < 1) || (nLunarMonth > 12))
	{
	    return FALSE;
	}
	
	if ((nLunarDay < 1) || (nLunarDay > 30)) //中国的月最多30天
	{
	   return FALSE;
	}

	//获取阴历月天数
	if(GetLunarMonthDays(nLunarYear,nLunarMonth) < nLunarDay)
	{
		long nLeapMonth = GetLeapMonth(nLunarYear);
		if(nLeapMonth == nLunarMonth)
		{//如果刚好是闰月
			if(GetLunarLeapMonthDays(nLunarYear) < nLunarDay)
			{
				return FALSE;
			}	
		}	
	}

	return TRUE;
}

//检查阳历日期是否正确
BOOL CheckSolarDate(WORD nSolarYear, WORD nSolarMonth, WORD nSolarDay)
{
	if ((nSolarYear < MIN_YEAR) || (nSolarYear > MAX_YEAR))
	{
	    return FALSE;
	}
	
	if ((nSolarMonth < 1) || (nSolarMonth > 12))
	{
	    return FALSE;
	}
	if ((nSolarDay < 1) || (nSolarDay > 31))
	{
	   return FALSE;
	}

	if(nSolarMonth == 2)
	{
		if(IsLeapYear(nSolarYear))// 是闰年
		{
			if(nSolarDay > 29)
			{
				return FALSE;
			}
		}
		else
		{
			if(nSolarDay > 28)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

//阴历转阳历日期
BOOL LunarToSolarDate(WORD nLunarYear, WORD nLunarMonth, WORD nLunarDay
					  ,WORD &nSolarYear, WORD &nSolarMonth, WORD &nSolarDay)
{
    int byNow, i;
	WORD nSpringSolarMonth,nSpringSolarDay;
	WORD nLeapMonth = 0;

	if(!CheckLunarDate(nLunarYear,nLunarMonth,nLunarDay))
	{
		return FALSE;
	}
    
	//获取阴历nLunarYear年春节公历日期
	GetLunarSpringDate(nLunarYear, nSpringSolarMonth, nSpringSolarDay);

    byNow = nSpringSolarDay - 1;
    if( nSpringSolarMonth == 2)
	{
		byNow += 31;
	}
        
    for(i = 1; i < nLunarMonth; i++)
	{
		byNow += GetLunarMonthDays(nLunarYear,i);
    }

    byNow += nLunarDay;
    nLeapMonth =GetLeapMonth(nLunarYear);
    if(nLeapMonth != 0)	
	{
        if(nLunarMonth >= nLeapMonth)	
		{
			byNow += GetLunarLeapMonthDays(nLunarYear);
        }
    }

    if(byNow > 366 || (nLunarYear%4 != 0 && byNow == 365))
	{
        nLunarYear += 1;
        if(nLunarYear%4 == 0)
		{
            byNow -= 366;
		}
        else
		{
            byNow -= 365;
		}
    }

    for(i=1; i <= 13; i ++)
	{
        if(g_nArrMonthSumDays[i] >= byNow)
		{
            nLunarMonth = i;
            break;
        }
    }

    nSolarDay = byNow - g_nArrMonthSumDays[nLunarMonth-1];
    nSolarMonth = nLunarMonth;
    nSolarYear = nLunarYear;
    
    return TRUE;
}

//阴历转阳历日期
BOOL LunarToSolarDate(WORD nLunarYear, WORD nLunarMonth, WORD nLunarDay
					  ,SYSTEMTIME &tm)
{
	BOOL bRet = LunarToSolarDate(nLunarYear,nLunarMonth,nLunarDay
										,tm.wYear,tm.wMonth,tm.wDay);
	GetWeekDay(tm);
	return bRet;
}

//阳历转阴历日期
BOOL SolarToLunarDate(WORD nSolarYear, WORD nSolarMonth, WORD nSolarDay
					  ,WORD &nLunarYear, WORD &nLunarMonth, WORD &nLunarDay)
{
    int bySpring,bySolar,daysPerMonth;
    int index,flag;
	WORD nSpringSolarMonth,nSpringSolarDay;

	if(!CheckSolarDate(nSolarYear,nSolarMonth,nSolarDay))
	{
		return FALSE;
	}
    
    //bySpring 记录春节离当年元旦的天数。
    //bySolar 记录阳历日离当年元旦的天数。

	//获取阴历nSolarYear年春节公历日期
	GetLunarSpringDate(nSolarYear, nSpringSolarMonth, nSpringSolarDay);

    if( nSpringSolarMonth == 1)
	{
        bySpring = nSpringSolarDay - 1;
	}
    else
	{
        bySpring = nSpringSolarDay - 1 + 31;
	}
	
    bySolar = g_nArrMonthSumDays[nSolarMonth-1] + nSolarDay - 1;
    if( (!(nSolarYear % 4)) && (nSolarMonth > 2))
	{
        bySolar++;
	}

    //daysPerMonth记录大小月的天数 29 或30
    //index 记录从哪个月开始来计算。
    //flag 是用来对闰月的特殊处理。
    
    //判断阳历日在春节前还是春节后
	if (bySolar >= bySpring) /*/阳历日在春节后（含春节那天）*/
	{
		index = 1;
		bySolar -= bySpring;
		nSolarMonth = 1;
		flag = 0;

		daysPerMonth =GetLunarMonthDays(nSolarYear,nSolarMonth);

		while(bySolar >= daysPerMonth) 
		{
			bySolar -= daysPerMonth;
			if(nSolarMonth == GetLeapMonth(nSolarYear) ) 
			{
				flag = ~flag;
				if(flag == 0)
				{
					nSolarMonth++;
				}
			}
			else
			{
				nSolarMonth++;
			}

			index ++; 
			daysPerMonth =GetLunarMonthDays(nSolarYear,index);
		}
		nSolarDay = bySolar + 1;
	}
	else 
	{                                                      //阳历日在春节前 
		bySpring -= bySolar;      
		nSolarYear--;          
		nSolarMonth = 12;   
		if ( GetLeapMonth(nSolarYear) == 0)  
		{
			index = 12;     
		}
		else 
		{
			index = 13; 
		}
		flag = 0;      

		daysPerMonth = GetLunarMonthDays(nSolarYear, index );

		while(bySpring > daysPerMonth)
		{         
			bySpring -= daysPerMonth;    
			index--;   

			if(flag == 0) 
			{
				nSolarMonth--; 
			}
			if(nSolarMonth == GetLeapMonth(nSolarYear)) 
			{
				flag = !flag;
			}
			daysPerMonth = GetLunarMonthDays(nSolarYear, index );
		}
		nSolarDay = daysPerMonth - bySpring + 1;
	}

	nLunarDay = nSolarDay;
	nLunarMonth = nSolarMonth;
	nLunarYear = nSolarYear;
	
	return TRUE;
}

//获取指定日期
void GetFixedDate(const SYSTEMTIME &tmCurr,SYSTEMTIME &tmFixed,long nDays)
{
	GPSTIME otmFixed = {tmCurr.wYear,tmCurr.wMonth,tmCurr.wDay,0};
	CGpsPcTime oT_Fixed(otmFixed);

	if(nDays < 0)
	{
		CGpsPcTimeSpan oSpan(-nDays,0,0,0,0,0);
		oT_Fixed -= oSpan;
	}
	else
	{
		CGpsPcTimeSpan oSpan(nDays,0,0,0,0,0);
		oT_Fixed += oSpan;
	}
	
	oT_Fixed.GetSysTime(tmFixed);
	GetWeekDay(tmFixed);
}

void InitPublicHoldayDate(WORD nYear,CArraySystemTime &tmArr)
{
	tmArr.RemoveAll();
	SYSTEMTIME tm;
	memset(&tm,0,sizeof(SYSTEMTIME));

	//春节
	LunarToSolarDate(nYear, 1, 1,tm);
	tmArr.Add(tm);
	LunarToSolarDate(nYear, 1, 2,tm);
	tmArr.Add(tm);
	LunarToSolarDate(nYear, 1, 3,tm);
	tmArr.Add(tm);
	LunarToSolarDate(nYear, 1, 4,tm);
	tmArr.Add(tm);
	LunarToSolarDate(nYear, 1, 5,tm);
	tmArr.Add(tm);
	LunarToSolarDate(nYear, 1, 6,tm);
	tmArr.Add(tm);

	//端午
	LunarToSolarDate(nYear, 5, 5,tm);
	tmArr.Add(tm);

	//中秋
	LunarToSolarDate(nYear, 8, 15,tm);
	tmArr.Add(tm);

	memset(&tm,0,sizeof(SYSTEMTIME));
	tm.wYear = nYear;

	//清明
	tm.wMonth = 4;
	tm.wDay = 5;
	GetWeekDay(tm);
	tmArr.Add(tm);

	//元旦
	tm.wMonth = 1;
	tm.wDay = 1;
	GetWeekDay(tm);
	tmArr.Add(tm);

	//五一
	tm.wMonth = 5;
	tm.wDay = 1;
	GetWeekDay(tm);
	tmArr.Add(tm);
	tm.wDay = 2;
	GetWeekDay(tm);
	tmArr.Add(tm);
	tm.wDay = 3;
	GetWeekDay(tm);
	tmArr.Add(tm);

	//国庆
	tm.wMonth = 10;
	tm.wDay = 1;
	GetWeekDay(tm);
	tmArr.Add(tm);
	tm.wDay = 2;
	GetWeekDay(tm);
	tmArr.Add(tm);
	tm.wDay = 3;
	GetWeekDay(tm);
	tmArr.Add(tm);
	tm.wDay = 4;
	GetWeekDay(tm);
	tmArr.Add(tm);
	tm.wDay = 5;
	GetWeekDay(tm);
	tmArr.Add(tm);
	tm.wDay = 6;
	GetWeekDay(tm);
	tmArr.Add(tm);
	tm.wDay = 7;
	GetWeekDay(tm);
	tmArr.Add(tm);

	TraceDateInfo(tmArr,nYear,nYear,_T("法定公休日"));
}

void InitPublicHoldayDate(WORD nBeginYear,WORD nEndYear,CArraySystemTime &tmArrHoliday)
{
	ASSERT(nBeginYear <= nEndYear);

	WORD nBegin = nBeginYear;
	CArraySystemTime tmArr;
	while( nBeginYear <= nEndYear )
	{
		InitPublicHoldayDate(nBeginYear,tmArr);
		tmArrHoliday.Append(tmArr);

		nBeginYear++;
	}

	TraceDateInfo(tmArrHoliday,nBegin,nEndYear,_T("法定公休日"));
}

//返回开始时间、结束时间之间共多少天，期间休息日数组
long GetHoldayArrBetweenDates(CArraySystemTime &tmArrHolday
							  ,const SYSTEMTIME &tmBegin
							  ,const SYSTEMTIME &tmEnd)
{	
	//检查开始时间、结束时间是否正确
	if(!IsDateIntervalCorrect(tmBegin,tmEnd))
	{
		return 0;
	}

	CArraySystemTime tmArrPublicHoliday;
	//初始化法定节假日数组
	InitPublicHoldayDate(tmBegin.wYear,tmEnd.wYear,tmArrPublicHoliday);

	int nFind = 0;
	int nDaysCount = 0;
	SYSTEMTIME tm = tmBegin;
	tmArrHolday.RemoveAll();

	while(1)
	{
		if(!IsDuring_DateInterval(tmBegin,tmEnd,tm))
		{
			break;
		}

		if(tm.wDayOfWeek == 0 || tm.wDayOfWeek == 6)
		{//如果是星期六或日
			tmArrHolday.Add(tm);
		}
		else
		{
			nFind = FindTimeArr(tmArrPublicHoliday,tm);
			if(nFind >= 0)
			{//如果是法定公休日
				tmArrHolday.Add(tm);
			}
		}
		
		nDaysCount++;
		GetFixedDate(tmBegin,tm,nDaysCount);
	}

	TraceDateInfo(tmArrHolday,tmBegin,tmEnd,_T("休息日"));

	return nDaysCount;
}

//开始时间、结束时间之间总天数,不存在日期tmArrUnExistDate，bFilterHoliday是否过滤休息日
BOOL FilterUnExistDateArrBetweenDates(CArraySystemTime &tmArrExistDate,CArraySystemTime &tmArrUnExistDate
		,CArraySystemTime &tmArrHolidayDate,const SYSTEMTIME &tmBegin,const SYSTEMTIME &tmEnd,BOOL bFilterHoliday)
{
	int nFind = 0;
	int nDaysCount = 0;
	SYSTEMTIME tm;
	tmArrUnExistDate.RemoveAll();

	while(1)
	{
		GetFixedDate(tmBegin,tm,nDaysCount++);

		if(!IsDuring_DateInterval(tmBegin,tmEnd,tm))
		{
			break;
		}

		if (bFilterHoliday)
		{
			nFind = FindTimeArr(tmArrHolidayDate,tm);
			if(nFind >= 0)
			{//如果是休息日
				continue;
			}
		}
		
		nFind = FindTimeArr(tmArrExistDate,tm);
		if(nFind >= 0)
		{//如果已经存在日期
			continue;
		}

		tmArrUnExistDate.Add(tm);
	}

	TraceDateInfo(tmArrExistDate,tmBegin,tmEnd,_T("存在日期"));
	TraceDateInfo(tmArrUnExistDate,tmBegin,tmEnd,_T("不存在日期"));

	return TRUE;
}

///////////////////////////////////////////////////

void OA_GetTime(CDateTimeCtrl *pDateTimeCtrl, SYSTEMTIME &tmOA, BOOL bShortTime)
{
	pDateTimeCtrl->GetTime(&tmOA);

	if (bShortTime)
	{
		tmOA.wHour = 0;
		tmOA.wMinute = 0;
		tmOA.wSecond = 0;
		tmOA.wMilliseconds = 0;
	}
}

void InitQueryBeginTime(CDateTimeCtrl &m_dtcStart,CDateTimeCtrl &m_dtcEnd,int nDays)
{
	ASSERT(nDays >= 0);

	SYSTEMTIME tmStart,tmFixed;
	GetLocalTime(&tmStart);

	GetFixedDate(tmStart,tmFixed,-nDays);

	m_dtcEnd.SetTime(tmStart);
	m_dtcStart.SetTime(tmFixed);
}

BOOL CheckTimeIsRight(SYSTEMTIME &tmStart,SYSTEMTIME &tmEnd
					  ,const CString &strTmPK,CString &strFilter_Date)
{
	ASSERT( !strTmPK.IsEmpty() );

	if (!IsDateIntervalCorrect(tmStart,tmEnd))
	{
		AfxMessageBox(_T("选择的时间错误。"));
		return FALSE;
	}

	GetDuringDateString(tmStart,tmEnd,strTmPK,strFilter_Date);

	return TRUE;
}

BOOL CheckTimeIsRight(CDateTimeCtrl &m_dtcStart,CDateTimeCtrl &m_dtcEnd
					  ,const CString &strTmPK,CString &strFilter_Date)
{
	//日期
	SYSTEMTIME tmStart,tmEnd;
	m_dtcStart.GetTime(&tmStart);
	m_dtcEnd.GetTime(&tmEnd);

	return CheckTimeIsRight(tmStart,tmEnd,strTmPK,strFilter_Date);
}

BOOL CheckTimeIsRight(CDateTimeCtrl &m_dtcStart,CDateTimeCtrl &m_dtcEnd)
{
	//日期
	SYSTEMTIME tmStart,tmEnd;
	m_dtcStart.GetTime(&tmStart);
	m_dtcEnd.GetTime(&tmEnd);

	if (!IsDateIntervalCorrect(tmStart,tmEnd))
	{
		AfxMessageBox(_T("选择的时间错误。"));
		return FALSE;
	}

	return TRUE;
}

void ModifyQueryEndTime(SYSTEMTIME& tmEnd)
{
	int wYear = tmEnd.wYear;
	int wMonth = tmEnd.wMonth;
	int wDay = tmEnd.wDay;
	BOOL bLeap = IsLeapYear(wYear);

	if ((wMonth==1 || wMonth==3 || wMonth==5 || wMonth==7 || wMonth == 8 || wMonth==10) && wDay==31
		|| (wMonth==4 || wMonth==6 || wMonth==9 || wMonth==11) && wDay==30
		|| wMonth==2 && (bLeap && wDay==29 || !bLeap && wDay==28))
	{
		tmEnd.wMonth += 1;
		tmEnd.wDay = 1;
	}
	else if (wMonth==12 && wDay==31)
	{
		tmEnd.wYear += 1;
		tmEnd.wMonth = 1;
		tmEnd.wDay = 1;
	}
	else
	{
		tmEnd.wDay += 1;
	}

	tmEnd.wHour = 0;
	tmEnd.wMinute = 0;
	tmEnd.wSecond = 0;
	tmEnd.wMilliseconds = 0;
}