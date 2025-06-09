// ComplexNumber.cpp: implementation of the CComplexNumber class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComplexNumber.h"
#include <math.h>
#include "../API/MathApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComplexNumber::CComplexNumber(double fModulus,double fAngle,long nMode)
{
	SetValueAngle(fModulus, fAngle, nMode);
}

CComplexNumber::CComplexNumber(double fReal,double fImaginary)
{
	SetValue(fReal, fImaginary);
}

CComplexNumber::CComplexNumber()
{
	m_fReal = 0;
	m_fImaginary = 0;
}

CComplexNumber::~CComplexNumber()
{

}


double CComplexNumber::GetRadianAngle()
{
	double fVal = 0;
	double fAnble = 0;
	GetValueAngle(fVal,fAnble);

	fAnble = (fAnble * RadianPerDegree);

	return fAnble;
}

double CComplexNumber::GetAngle()
{
	double fVal = 0;
	double fAnble = 0;
	GetValueAngle(fVal,fAnble);

	return fAnble;
}

double CComplexNumber::GetAngle_180_180()
{
	return GetTheAngleRange_180_180(GetAngle());
}

double CComplexNumber::GetAngle_0_360()
{
	return GetTheAngleRange_0_360(GetAngle());
}

double CComplexNumber::GetModulus()
{
	return sqrt(m_fReal * m_fReal + m_fImaginary * m_fImaginary);
}

void CComplexNumber::GetValueAngle(double &fModulus,double &fAngle,long nMode)
{
	fModulus = m_fReal * m_fReal + m_fImaginary * m_fImaginary;

	fModulus = (sqrt(fModulus));

	if (fabs(fModulus) <= PRECISION_COMPARE)
	{
		fAngle = 0;
	}
	else
	{
		fAngle = (acos(m_fReal/fModulus));

		if (nMode == COMPLEX_MODE_DEGREE)
		{
			fAngle = fAngle * DegreePerRadian;
			if (m_fImaginary < 0)
			{
				fAngle = 360 - fAngle;
			}
		}
	}
}

void CComplexNumber::SetValueAngle(double fModulus,double fAngle, long nMode)
{
	if (nMode == COMPLEX_MODE_DEGREE)
	{
		fAngle = fAngle * RadianPerDegree;
	}

	m_fReal = fModulus * cos(fAngle);
	m_fImaginary = fModulus * sin(fAngle);
}

void CComplexNumber::GetValue(double &fReal,double &fImaginary)
{
	fReal = m_fReal;
	fImaginary = m_fImaginary;	
}

void CComplexNumber::SetValue(double fReal,double fImaginary)
{
	m_fReal = fReal;
	m_fImaginary = fImaginary;
}

double CComplexNumber::GetTheAngleRange_180_180(double fAngle)
{
	while(fAngle < -180)
		fAngle += 360;

	while(fAngle > 180)
		fAngle -= 360;

	return fAngle;
}

double CComplexNumber::GetTheAngleRange_0_360(double fAngle)
{
	while(fAngle < 0)
		fAngle += 360;
	while(fAngle > 360)
		fAngle -= 360;
	
	return fAngle;
}

void CComplexNumber::Rotate(double fAngle,long nMode)
{
	double fValue = 0;
	double fAngleLast = 0;

	GetValueAngle(fValue,fAngleLast, nMode);
	fAngleLast += fAngle;

	SetValueAngle(fValue,fAngleLast, nMode);
}

void CComplexNumber::Zoom(double fCoef)
{
	m_fReal *= fCoef;
	m_fImaginary *= fCoef;
}


CComplexNumber& CComplexNumber::operator=(const CComplexNumber &val)
{
	m_fReal = val.m_fReal;
	m_fImaginary = val.m_fImaginary;

	return *this;
}

BOOL CComplexNumber::operator==(const CComplexNumber &val)
{
	return (fabs(m_fReal-val.m_fReal) <= PRECISION_COMPARE
		&& fabs(m_fImaginary-val.m_fImaginary) <= PRECISION_COMPARE);
}

CComplexNumber& CComplexNumber::operator+=(const CComplexNumber &val)
{
	m_fReal += val.m_fReal;
	m_fImaginary += val.m_fImaginary;
	
	return *this;
}

CComplexNumber& CComplexNumber::operator-=(const CComplexNumber &val)
{
	m_fReal -= val.m_fReal;
	m_fImaginary -= val.m_fImaginary;
	
	return *this;
}

CComplexNumber& CComplexNumber::operator*=(const CComplexNumber &val)
{
	double fReal = m_fReal * val.m_fReal - m_fImaginary * val.m_fImaginary;
	double fImaginary = m_fImaginary * val.m_fReal + m_fReal * val.m_fImaginary;

	m_fReal = fReal;
	m_fImaginary = fImaginary;
	
	return *this;
}

CComplexNumber& CComplexNumber::operator/=(const CComplexNumber &val)
{
	double fTemp = val.m_fReal * val.m_fReal + val.m_fImaginary * val.m_fImaginary;
	double fReal = (m_fReal * val.m_fReal + m_fImaginary * val.m_fImaginary) / fTemp;
	double fImaginary = (m_fImaginary * val.m_fReal - m_fReal * val.m_fImaginary) / fTemp;

	m_fReal = fReal;
	m_fImaginary = fImaginary;
	
	return *this;
}


CComplexNumber CComplexNumber::operator+(const CComplexNumber &val)
{
	CComplexNumber c = *this;
	c.m_fReal += val.m_fReal;
	c.m_fImaginary += val.m_fImaginary;

	return c;
}

CComplexNumber CComplexNumber::operator-(const CComplexNumber &val)
{
	CComplexNumber c = *this;
	c.m_fReal -= val.m_fReal;
	c.m_fImaginary -= val.m_fImaginary;

	return c;
}

CComplexNumber CComplexNumber::operator*(const CComplexNumber &val)
{
	double fReal = m_fReal * val.m_fReal - m_fImaginary * val.m_fImaginary;
	double fImaginary = m_fImaginary * val.m_fReal + m_fReal * val.m_fImaginary;

	CComplexNumber c;
	c.m_fReal = fReal;
	c.m_fImaginary = fImaginary;

	return c;
}

CComplexNumber CComplexNumber::operator/(const CComplexNumber &val)
{
	double fTemp = val.m_fReal * val.m_fReal + val.m_fImaginary * val.m_fImaginary;
	double fReal = (m_fReal * val.m_fReal + m_fImaginary * val.m_fImaginary) / fTemp;
	double fImaginary = (m_fImaginary * val.m_fReal - m_fReal * val.m_fImaginary) / fTemp;

	CComplexNumber c;
	c.m_fReal = fReal;
	c.m_fImaginary = fImaginary;

	return c;
}

CComplexNumber& CComplexNumber::Add(const CComplexNumber &lhs,const CComplexNumber &rhs)
{
	m_fReal = lhs.m_fReal + rhs.m_fReal;
	m_fImaginary = lhs.m_fImaginary + rhs.m_fImaginary;

	return *this;
}

CComplexNumber& CComplexNumber::Minus(const CComplexNumber &lhs,const CComplexNumber &rhs)
{
	m_fReal = lhs.m_fReal + rhs.m_fReal;
	m_fImaginary = lhs.m_fImaginary - rhs.m_fImaginary;
	
	return *this;
}

CComplexNumber& CComplexNumber::Multiply(const CComplexNumber &lhs,const CComplexNumber &rhs)
{
	m_fReal = lhs.m_fReal * rhs.m_fReal - lhs.m_fImaginary * rhs.m_fImaginary;
	m_fImaginary = lhs.m_fImaginary * rhs.m_fReal + lhs.m_fReal * rhs.m_fImaginary;
	
	return *this;
}

CComplexNumber& CComplexNumber::Divide(const CComplexNumber &lhs,const CComplexNumber &rhs)
{
	double fTemp = rhs.m_fReal * rhs.m_fReal + rhs.m_fImaginary * rhs.m_fImaginary;
	m_fReal = (lhs.m_fReal * rhs.m_fReal + lhs.m_fImaginary * rhs.m_fImaginary) / fTemp;
	m_fImaginary = (lhs.m_fImaginary * rhs.m_fReal - lhs.m_fReal * rhs.m_fImaginary) / fTemp;

	return *this;
}
