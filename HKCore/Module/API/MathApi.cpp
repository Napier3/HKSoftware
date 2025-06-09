// MathApi.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MathApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//数据修约
double math_ValueRevised(double dValue, long nDots)
{
	double dInt = (long)dValue;
	double dTemp = dValue - dInt;
	double dCal = 0;
	long nDot = 0;
	double dIntTemp = 0;
	double dDiv = 1;
	long nIntTempPrev = 0;

	if (nDots <= 0)
	{
		nDots = 3;
	}

	for (nDot=0; nDot<nDots; nDot++)
	{
		dDiv *= 10;
		dTemp *= 10;
		dIntTemp = (long)dTemp;
		dCal = dCal * 10 + dIntTemp;
		nIntTempPrev = (long)dIntTemp;
		dTemp = dTemp - dIntTemp;
	}

	dTemp *= 10;
	dIntTemp = (long)dTemp;
	long nIntTemp = (long)dIntTemp;

	if (dIntTemp >= 6)
	{
		dCal += 1;
	}
	else
	{
		if (nIntTemp == 5)
		{
			if (dTemp - 5.0 > PRECISION_COMPARE)
			{
				dCal += 1;
			}
			else
			{
				if (nIntTempPrev % 2 == 1)
				{
					dCal += 1;
				}
			}
		}
	}

	dCal = dInt + dCal / dDiv;
	//dCal += 0.0000000001;

	return dCal;
}


double math_GetValueFromString(char *pString)
{
	char *p = pString;

	while (*p == VK_SPACE || *p==VK_TAB)
	{
		p++;
	}

	if (*p == '+' || *p == '-')
	{
		p++;
	}

	while (*p != '\0')
	{
		if (('0' <= *p && *p <= '9') || (*p == '.'))
		{
			p++;
		}
		else
		{
			break;
		}
	}

	double dValue = atof(pString);

	if (*p == 'k' || *p == 'K')
	{
		dValue *= 1000;
	}
	else if (*p == 'm' || *p == 'M')
	{
		dValue *= 1000000;
	}

	return dValue;
}

void math_GetStringFromValue(CString &strText, double dValue, const CString &strUnit, BOOL bUnitConversion)
{
	if (!bUnitConversion)
	{
		strText.Format(_T("%.3f%s"), dValue, strUnit.GetString());
		return;
	}

	if (dValue >= 1000000)
	{
		dValue /= 1000000;
		strText.Format(_T("%.3fM%s"), dValue, strUnit.GetString());
	}
	else if (dValue >= 1000)
	{
		dValue /= 1000;
		strText.Format(_T("%.3fk%s"), dValue, strUnit.GetString());
	}
	else
	{
		strText.Format(_T("%.3f%s"), dValue, strUnit.GetString());
	}
}

double math_GetValueFromString(const CString &strValue)
{
	char *pString = NULL;
	double dValue = 0;
	CString_to_char(strValue, &pString);
	dValue = math_GetValueFromString(pString);
	delete pString;
	return dValue;
}

void MakeAngleTo360(double &dAngle)
{
	while (dAngle < 0)
	{
		dAngle += 360;
	}

	while (dAngle >= 360)
	{
		dAngle -= 360;
	}
}

void MakeAngleTo360(float &fAngle)
{
	while (fAngle < 0)
	{
		fAngle += 360;
	}

	while (fAngle > 360)
	{
		fAngle -= 360;
	}
}


void MakeAngleTo180(double &dAngle)
{
	while (dAngle < -180)
	{
		dAngle += 360;
	}

	while (dAngle > 180)
	{
		dAngle -= 360;
	}
}

void MakeAngleTo180(float &fAngle)
{
	while (fAngle < -180)
	{
		fAngle += 360;
	}

	while (fAngle > 180)
	{
		fAngle -= 360;
	}
}


void MakeAngleTo_PI2(double &dAngle)
{
	while (dAngle < 0)
	{
		dAngle += _PI2;
	}

	while (dAngle >= _PI2)
	{
		dAngle -= _PI2;
	}
}

void MakeAngleTo_PI2(float &fAngle)
{
	while (fAngle < 0)
	{
		fAngle += (float)_PI2;
	}

	while (fAngle > _PI2)
	{
		fAngle -= (float)_PI2;
	}
}


void MakeAngleTo_PI(double &dAngle)
{
	while (dAngle < -_PI)
	{
		dAngle += _PI2;
	}

	while (dAngle > _PI)
	{
		dAngle -= _PI2;
	}
}

void MakeAngleTo_PI(float &fAngle)
{
	while (fAngle < -_PI)
	{
		fAngle += (float)_PI2;
	}

	while (fAngle > _PI)
	{
		fAngle -= (float)_PI2;
	}
}

void math_CalError(double dValue, double dRefValue, double &dAbsCal, double &dRelCal, BOOL bIsAngle)
{
	dAbsCal = dValue - dRefValue;

	if (bIsAngle)
	{
		dAbsCal = dAbsCal - ( ((long)(dAbsCal / 360))*360);
	}

	dRelCal = dAbsCal;//fabs(dAbsCal);

	if (!bIsAngle)
	{
		if (dRefValue > 0.0001)
		{
			dRelCal /= dRefValue;
		}
	}
}

void math_CalError(double dValue, double dRefValue, double dRelStdRefValue, double &dAbsCal, double &dRelCal, BOOL bIsAngle)
{
	dAbsCal = dValue - dRefValue;

	if (bIsAngle)
	{
		dAbsCal = dAbsCal - ( ((long)(dAbsCal / 360))*360);
	}

	dRelCal = dAbsCal;//fabs(dAbsCal);

	if (!bIsAngle)
	{
		if (dRefValue > 0.0001)
		{
			dRelCal /= dRelStdRefValue;
		}
	}
}

long math_CalIsInError(double dAbsCal, double dRelCal, double dAbsErr, double dRelErr)
{
	BOOL bAbsRsltJdg = TRUE;
	BOOL bRelRsltJdg = TRUE;
	long nRsltJdg = 0;
	BOOL bRsltJdg = FALSE;

	dAbsCal = fabs(dAbsCal);
	dRelCal = fabs(dRelCal);

	if (dAbsErr > 0)
	{
		if (dAbsCal > dAbsErr)
		{
			bAbsRsltJdg = FALSE;
		}
		else
		{
			bRsltJdg = TRUE;
		}
	}

	if (dRelErr > 0)
	{
		if (dRelCal > dRelErr)
		{
			bRelRsltJdg = FALSE;
		}
		else
		{
			bRsltJdg = TRUE;
		}
	}

	//if (bAbsRsltJdg && bRelRsltJdg)
	if (bRsltJdg)
	{
		nRsltJdg = 1;
	}
	else
	{
		nRsltJdg = 0;
	}

	return nRsltJdg;
}

BOOL mathAngle360_IsEqual(double dValue1, double dValue2, double dPrecision)
{
	MakeAngleTo360(dValue1);
	MakeAngleTo360(dValue2);
	double dValue = fabs(dValue2 - dValue1);
	MakeAngleTo360(dValue);//正常上述相减完值应该在0~360返回内,防止精度丢失导致的误差,此处再确认转换一次
	BOOL bRet = (dValue< dPrecision);

	if (!bRet)//如果差值在360附近,此处再减去360确认一次
	{
		bRet = (fabs(dValue - 360)< dPrecision);
	}

	return bRet;
}

static short Leap_year[2][12] =
{
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

void TransTimer_t(unsigned int ntime_t,
						 short &nYear, short &nMon, short &nDay, short &nHour, short &nMin, short &nSec)
{
	TransTimer_LongTime(ntime_t,nYear,nMon,nDay,nHour,nMin,nSec);
}

void TransTimer_LongTime(long ntime_t,
				  short &nYear, short &nMon, short &nDay, short &nHour, short &nMin, short &nSec)
{
	nYear = 1970;
	nMon = 1;
	nDay = 1;
	nHour = nMin = nSec = 0;

	while(TRUE)
	{
		int nIsLeap = 0;

		if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
		{
			nIsLeap = 1;
		}

		int nDiff = nIsLeap ? 366 : 365;

		if(ntime_t >= nDiff * 24 * 60 * 60)
		{
			nYear += 1;
			ntime_t -= nDiff * 24 * 60 * 60;
		}
		else
		{
			break;
		}
	}

	while(TRUE)
	{
		int nIsLeap = 0;

		if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
		{
			nIsLeap = 1;
		}

		int nLastDay = Leap_year[nIsLeap][nMon - 1];

		if(ntime_t >= nLastDay * 24 * 60 * 60)
		{
			nMon += 1;
			ntime_t -= nLastDay * 24 * 60 * 60;
		}
		else
		{
			break;
		}
	}

	while(TRUE)
	{
		if(ntime_t >= 24 * 60 * 60)
		{
			nDay += 1;
			ntime_t -= 24 * 60 * 60;
		}
		else
		{
			break;
		}
	}

	while(TRUE)
	{
		if(ntime_t >= 60 * 60)
		{
			nHour += 1;
			ntime_t -= 60 * 60;
		}
		else
		{
			break;
		}
	}

	while(TRUE)
	{
		if(ntime_t >= 60)
		{
			nMin += 1;
			ntime_t -= 60;
		}
		else
		{
			break;
		}
	}

	nSec = ntime_t;
}

//此函数为兼容之前老的接口
void TransTimer_To_t(unsigned int &ntime_t,
					 short nYear, short nMon, short nDay, short nHour, short nMin, short nSec)
{
	long nTime_Long = 0;
	TransTimer_To_LongTime(nTime_Long,nYear, nMon, nDay, nHour, nMin, nSec);
	ntime_t = nTime_Long;
}

void TransTimer_To_LongTime(long &ntime_t,
							short nYear, short nMon, short nDay, short nHour, short nMin, short nSec)
{
	ntime_t = 0;
	int nYearRef = 1970;

	while(TRUE)
	{
		int nDiffYear = nYear - nYearRef;

		if(nDiffYear == 0)
		{
			break;
		}

		int nIsLeap = 0;

		if((nYearRef % 4 == 0 && nYearRef % 100 != 0) || nYearRef % 400 == 0)
		{
			nIsLeap = 1;
		}

		int nDays = nIsLeap ? 366 : 365;
		ntime_t += nDays * 24 * 60 * 60;
		nYearRef++;
	}

	int nIsLeap = 0;

	if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
	{
		nIsLeap = 1;
	}

	int nMonRef = 1;

	while(TRUE)
	{
		int nDiffMon = nMon - nMonRef;

		if(nDiffMon == 0)
		{
			break;
		}

		int nLastDay = Leap_year[nIsLeap][nMonRef - 1];
		ntime_t += nLastDay * 24 * 60 * 60;
		nMonRef++;
	}

	ntime_t += (nDay - 1) * 24 * 60 * 60;
	ntime_t += nHour * 60 * 60;
	ntime_t += nMin * 60;
	ntime_t += nSec;
}

void TransTimer_To_LongTime_ms(unsigned long long &ntime_t,
							   short nYear, short nMon, short nDay, short nHour, short nMin, short nSec, short nMilliseconds)
{
	ntime_t = 0;
	long nTime = 0;
	TransTimer_To_LongTime(nTime, nYear, nMon, nDay, nHour, nMin, nSec);

	ntime_t = (unsigned long long)nTime * 1000 + nMilliseconds;
}