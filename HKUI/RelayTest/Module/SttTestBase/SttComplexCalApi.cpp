#include "stdafx.h"
#include "SttComplexCalApi.h"


void Complex_Add(double dMag1, double dAng1, double dMag2, double dAng2, double &dMag3, double &dAng3, long nMode)
{
	CComplexNumber c1(dMag1,dAng1,nMode);
	CComplexNumber c2(dMag2,dAng2,nMode);

	c1 += c2;
	c1.GetValueAngle(dMag3, dAng3, nMode);
}

void Complex_Sub(double dMag1, double dAng1, double dMag2, double dAng2, double &dMag3, double &dAng3, long nMode)
{
	CComplexNumber c1(dMag1,dAng1,nMode);
	CComplexNumber c2(dMag2,dAng2,nMode);

	c1 -= c2;
	c1.GetValueAngle(dMag3, dAng3, nMode);
}

void Complex_Mul(double dMag1, double dAng1, double dMag2, double dAng2, double &dMag3, double &dAng3, long nMode)
{
	CComplexNumber c1(dMag1,dAng1,nMode);
	CComplexNumber c2(dMag2,dAng2,nMode);

	c1 *= c2;
	c1.GetValueAngle(dMag3, dAng3, nMode);
}

void Complex_Div(double dMag1, double dAng1, double dMag2, double dAng2, double &dMag3, double &dAng3, long nMode)
{
	CComplexNumber c1(dMag1,dAng1,nMode);
	CComplexNumber c2(dMag2,dAng2,nMode);

	c1 /= c2;
	c1.GetValueAngle(dMag3, dAng3, nMode);
}

double Complex_Len(double dMag1, double dAng1, double dMag2, double dAng2, long nMode)
{
	CComplexNumber c1(dMag1,dAng1,nMode);
	CComplexNumber c2(dMag2,dAng2,nMode);

	c1 -= c2;
	return c1.GetModulus();
}

