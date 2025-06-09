﻿#ifndef _math_api_h__
#define _math_api_h__

#include <math.h>
#include "StringApi.h"

//PI
#define _PI_HALF   1.57079633
#define _PI           3.14159265
#define _PI2          6.28318531
#define _PI_D_180  0.0174532925  //pi / 180
#define _180_D_PI  57.295779579  //180 / pi

#define SQRT2  1.41421356
#define SQRT3  1.73205081
#define PRECISION_COMPARE  0.00001

#define RadianPerDegree _PI_D_180
#define DegreePerRadian _180_D_PI

inline BOOL math_IsEqual(double dValue1, double dValue2)
{
	return (fabs(dValue2 - dValue1) < PRECISION_COMPARE);
}

inline BOOL math_IsEqual(float fValue1, float fValue2)
{
	return (fabs(fValue2 - fValue1) < PRECISION_COMPARE);
}

inline BOOL math_IsEqual(double dValue1, double dValue2, double dPrecision)
{
	return (fabs(dValue2 - dValue1) < dPrecision);
}

inline BOOL math_IsEqual(float fValue1, float fValue2, float fPrecision)
{
	return (fabs(fValue2 - fValue1) < fPrecision);
}

BOOL mathAngle360_IsEqual(double dValue1, double dValue2, double dPrecision);//2023.4.8  zhouhj


inline int math_CompareF(float fValue1, float fValue2, float fPrecision=0.001)
{
	if (fValue1 < fValue2)
	{
		if (fValue2 - fValue1 > fPrecision)
		{
			return -1;
		}
	}
	else if (fValue1 > fValue2)
	{
		if (fValue1 - fValue2 > fPrecision)
		{
			return 1;
		}
	}
	return 0;
}

inline int math_CompareF(double fValue1, double fValue2, double fPrecision=0.001)
{
	if (fValue1 < fValue2)
	{
		if (fValue2 - fValue1 > fPrecision)
		{
			return -1;
		}
	}
	else if (fValue1 > fValue2)
	{
		if (fValue1 - fValue2 > fPrecision)
		{
			return 1;
		}
	}
	return 0;
}

double math_GetValueFromString(char *pString);
void math_GetStringFromValue(CString &strText, double dValue, const CString &strUnit, BOOL bUnitConversion=TRUE);
double math_GetValueFromString(const CString &strValue);
void MakeAngleTo360(double &dAngle);
void MakeAngleTo360(float &fAngle);
void MakeAngleTo180(double &dAngle);
void MakeAngleTo180(float &fAngle);
void MakeAngleTo_PI2(double &dAngle);
void MakeAngleTo_PI2(float &fAngle);
void MakeAngleTo_PI(double &dAngle);
void MakeAngleTo_PI(float &fAngle);
void math_CalError(double dValue, double dRefValue, double &dAbsCal, double &dRelCal, BOOL bIsAngle);
void math_CalError(double dValue, double dRefValue, double dRelStdRefValue, double &dAbsCal, double &dRelCal, BOOL bIsAngle);
long math_CalIsInError(double dAbsCal, double dRelCal, double dAbsErr, double dRelErr);

//数据修约
double math_ValueRevised(double dValue, long nDots);


#endif
