#include "stdafx.h"
#include "LunarSolarTransforTool.h"
#include "..\GpsPcTime\GpsPcTime.h"

//某年所有公休日期数组
CArraySystemTime g_ArrHoldayDates;

int FindTimeArr(CArraySystemTime &tmArr,SYSTEMTIME &tm)
{
	SYSTEMTIME tmTemp;
	int nCount = tmArr.GetSize();
	int nFind = -1;

	for (int i=0; i < nCount; i++)
	{
		tmTemp = tmArr[i];

		if ((tmTemp.wYear == tm.wYear)
			&& (tmTemp.wMonth = tm.wMonth)
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
void GetFixedDate(SYSTEMTIME &tmCurr,SYSTEMTIME &tmFixed,long nDays)
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

	//清明
	LunarToSolarDate(nYear, 4, 5,tm);
	tmArr.Add(tm);

	//端午
	LunarToSolarDate(nYear, 5, 5,tm);
	tmArr.Add(tm);

	//中秋
	LunarToSolarDate(nYear, 8, 15,tm);
	tmArr.Add(tm);

	memset(&tm,0,sizeof(SYSTEMTIME));
	tm.wYear = nYear;

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
}

BOOL GetHoldayArrBetweenDates(CArraySystemTime &tmArrHolday
							  ,SYSTEMTIME tmBegin,SYSTEMTIME tmEnd)
{
//	FindTimeArr
	SYSTEMTIME tm = tmBegin;
	while(1)
	{

	}
	return TRUE;
}