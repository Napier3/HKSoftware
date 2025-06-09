// Complexp.cpp: implementation of the Complexp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SttComplexp.h"
#include"../../../Module/API/MathApi.h"

#ifdef _DEBUG
#undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
Complexp::Complexp()
{

}
*/
Complex::Complex()
{
    Mag = Ang = real = imag = 0.0;
//	XPI=3.1415926;
}
Complex::~Complex()
{
}


Complex::Complex(double re, double im)
{
	/*Mag = */real = re;
	/*Ang = */imag = im;
}
Complex Complex::operator+(const Complex &u)const
{
    Complex v(real + u.real, imag + u.imag);
	return v;
}
Complex Complex::operator+(const double &u)const
{
    Complex v(real + u, imag);
	return v;
}
Complex Complex::operator-(const Complex &u)const
{
    Complex v(real - u.real, imag - u.imag);
	return v;
}
Complex Complex::operator-(const double &u)const
{
    Complex v(real - u, imag);
	return v;
}
Complex Complex::operator*(const Complex &u)const
{
    Complex v(real * u.real - imag * u.imag, imag * u.real + real * u.imag);
	return v;
}
Complex Complex::operator*(const double &u)const
{
    Complex v(real * u, imag * u);
	return v;
}
Complex Complex::operator/(const Complex &u)const
{
    Complex v((real * u.real + imag * u.imag) / (u.real * u.real + u.imag * u.imag), (imag * u.real - real * u.imag) / (u.real * u.real + u.imag * u.imag));
	return v;
}
Complex Complex::operator/(const double &u)const
{
    Complex v(real / u, imag / u);
	return v;
}

Complex Complex::aoperator(double u)
{
    Complex v(cos(u * 3.1415926 / 180.0), sin(u * 3.1415926 / 180.0));
	return v;
}
Complex Complex::polar(double mag, double ang)
{
    if(fabs(mag) < 0.0000001)
    {
        mag = 0.0000001;
    }

    double dm = cos(ang * 3.1415926 / 180.0);
    double da = sin(ang * 3.1415926 / 180.0);
    Complex v(mag * dm, mag * da);
	v.Mag = mag;
	v.Ang = ang;
	return v;
}

#ifdef _PSX_QT_LINUX_
double Complex::norm(const Complex &u)const
{
    double v = hypot(u.real, u.imag);
	return v;
}

double Complex::norm()const
{
    double v = hypot(real, imag);
	return v;
}
#else
double Complex::norm(const Complex &u)const
{
    double v = _hypot(u.real, u.imag);
	return v;
}

double Complex::norm()const
{
    double v = _hypot(real, imag);
	return v;
}
#endif

Complex Complex::pnom(const Complex &u)const
{
    Complex v(u.real, -u.imag);
	return v;
}
Complex Complex::pnom()const
{
    Complex v(real, -imag);
	return v;
}
double Complex::arg(const Complex &u)const
{
	double v;

    if(fabs(u.real) > 0.0000000001)
    {
        v = (float)atan2(u.imag, u.real) * 180.0 / 3.1415926;
    }
	else
	{
        if(fabs(u.imag) < 0.0000000001 && fabs(u.real) < 0.00000001)
        {
            v = 0;
        }
		else
		{
            if(u.imag >= 0.0000000001f)
            {
                v = 90.0f;
            }
            else
            {
                v = 270.0f;
		}
    }
    }

	return v;
}
double Complex::arg()const
{
	double v;

    if(fabs(real) > 0.0000000001)
    {
        v = (float)atan2(imag, real) * 180.0 / 3.1415926;
    }
	else
	{
        if(fabs(imag) < 0.0000000001 && fabs(real) < 0.00000001)
        {
            v = 0;
        }
		else
		{
            if(imag >= 0.0000000001f)
            {
                v = 90.0f;
            }
            else
            {
                v = 270.0f;
            }
		}
	}

	return v;
}
void Complex::SetParameter(double dreal, double dimag)
{	
    real = Mag = dreal;
    imag = Ang = dimag;
}

void Complex::SetParameter_ByAmpAng(double mag, double ang)
{
    if(fabs(mag) < 0.0000001)
    {
        mag = 0.0000001;
    }

    double dm = cos(ang * 3.1415926 / 180.0);
    double da = sin(ang * 3.1415926 / 180.0);
    real = mag * dm;
    imag = mag * da;
	Mag = mag;
	Ang = ang;
}

void Complex::SetMag(double dMag)
{
	Complex oComp1;
    *this = oComp1.polar(dMag, arg());
}

void CalABCValues_BySequenceValues_Double(double &dA_mag, double &dA_ang, double &dB_mag, double &dB_ang, double &dC_mag, double &dC_ang,
        double dPos_mag, double dPos_ang, double dNeg_mag, double dNeg_ang, double dZero_mag, double dZero_ang)
{
    Complex oComplexA, oComplexB, oComplexC, oComplex1, oComplex2, oComplex0;
    oComplex1.SetParameter_ByAmpAng(dPos_mag, dPos_ang);
    oComplex2.SetParameter_ByAmpAng(dNeg_mag, dNeg_ang);
    oComplex0.SetParameter_ByAmpAng(dZero_mag, dZero_ang);
    oComplexA = oComplex1 + oComplex2 + oComplex0;
	dA_mag = oComplexA.norm();
	dA_ang = oComplexA.arg();
    oComplex1.SetParameter_ByAmpAng(dPos_mag, dPos_ang - 120);
    oComplex2.SetParameter_ByAmpAng(dNeg_mag, dNeg_ang + 120);
//	oComplex0.SetParameter_ByAmpAng(dZero_mag,dZero_ang);
    oComplexB = oComplex1 + oComplex2 + oComplex0;
	dB_mag = oComplexB.norm();
	dB_ang = oComplexB.arg();
    oComplex1.SetParameter_ByAmpAng(dPos_mag, dPos_ang + 120);
    oComplex2.SetParameter_ByAmpAng(dNeg_mag, dNeg_ang - 120);
//	oComplex0.SetParameter_ByAmpAng(dZero_mag,dZero_ang);
    oComplexC = oComplex1 + oComplex2 + oComplex0;
	dC_mag = oComplexC.norm();
	dC_ang = oComplexC.arg();
}

void CalABCValues_BySequenceValues_Float(float &dA_mag, float &dA_ang, float &dB_mag, float &dB_ang, float &dC_mag, float &dC_ang,
        double dPos_mag, double dPos_ang, double dNeg_mag, double dNeg_ang, double dZero_mag, double dZero_ang)
{
    Complex oComplexA, oComplexB, oComplexC, oComplex1, oComplex2, oComplex0;
    oComplex1.SetParameter_ByAmpAng(dPos_mag, dPos_ang);
    oComplex2.SetParameter_ByAmpAng(dNeg_mag, dNeg_ang);
    oComplex0.SetParameter_ByAmpAng(dZero_mag, dZero_ang);
    oComplexA = oComplex1 + oComplex2 + oComplex0;
	dA_mag = oComplexA.norm();
	dA_ang = oComplexA.arg();
    oComplex1.SetParameter_ByAmpAng(dPos_mag, dPos_ang - 120);
    oComplex2.SetParameter_ByAmpAng(dNeg_mag, dNeg_ang + 120);
    oComplexB = oComplex1 + oComplex2 + oComplex0;
	dB_mag = oComplexB.norm();
	dB_ang = oComplexB.arg();
    oComplex1.SetParameter_ByAmpAng(dPos_mag, dPos_ang + 120);
    oComplex2.SetParameter_ByAmpAng(dNeg_mag, dNeg_ang - 120);
    oComplexC = oComplex1 + oComplex2 + oComplex0;
	dC_mag = oComplexC.norm();
	dC_ang = oComplexC.arg();
}

void CalABCValues_Bylinevolt_Float(float &dA_mag, float &dA_ang, float &dB_mag, float &dB_ang, float &dC_mag, float &dC_ang,
                                   double dline_mag, double dline_ang, double dzero_mag, double dzero_ang)
{
	CalABCValues_BySequenceValues_Float(dA_mag,dA_ang,dB_mag,dB_ang,dC_mag,dC_ang,
		dline_mag/1.7320508, dline_ang-30,0.0f, 0.0f,dzero_mag/3, dzero_ang);
}

//功率因数
double SetFactor_ByAng(double dU_ang, double dI_ang)
{
    return cos((dU_ang - dI_ang) * _PI / 180);
}
//有功功率
double SetActive_Power_ByAng(double dU_mag, double dU_ang, double dI_mag, double dI_ang)
{
    return dU_mag * dI_mag * cos((dU_ang - dI_ang) * _PI / 180);
}

//无功功率
double SetReactive_Power_ByAng(double dU_mag, double dU_ang, double dI_mag, double dI_ang)
{
    return dU_mag * dI_mag * sin((dU_ang - dI_ang) * _PI / 180);
}

//视在功率
double SetApparent_Power_ByAng(double dU_mag, double dI_mag)
{
    return dU_mag * dI_mag;
}


void CalABCValues_ByPowerValues_Double(double dUA_mag, double dUA_ang, double dIA_mag, double dIA_ang,
                                       double dUB_mag, double dUB_ang, double dIB_mag, double dIB_ang,
                                       double dUC_mag, double dUC_ang, double dIC_mag, double dIC_ang)
{
    double Total_Active_Power, Total_Reactive_Power, Total_Apparent_Power;
    double FactorA, Active_PowerA, Reactive_PowerA, Apparent_PowerA;
    double FactorB, Active_PowerB, Reactive_PowerB, Apparent_PowerB;
    double FactorC, Active_PowerC, Reactive_PowerC, Apparent_PowerC;
    FactorA = SetFactor_ByAng(dUA_ang, dIA_ang);
    FactorB = SetFactor_ByAng(dUB_ang, dIB_ang);
    FactorC = SetFactor_ByAng(dUC_ang, dIC_ang);
    Active_PowerA = SetActive_Power_ByAng(dUA_mag, dUA_ang, dIA_mag, dIA_ang);
    Active_PowerB = SetActive_Power_ByAng(dUB_mag, dUB_ang, dIB_mag, dIB_ang);
    Active_PowerC = SetActive_Power_ByAng(dUC_mag, dUC_ang, dIC_mag, dIC_ang);
    Total_Active_Power = Active_PowerA + Active_PowerB + Active_PowerC;
    Reactive_PowerA = SetReactive_Power_ByAng(dUA_mag, dUA_ang, dIA_mag, dIA_ang);
    Reactive_PowerB = SetReactive_Power_ByAng(dUB_mag, dUB_ang, dIB_mag, dIB_ang);
    Reactive_PowerC = SetReactive_Power_ByAng(dUC_mag, dUC_ang, dIC_mag, dIC_ang);
    Total_Reactive_Power = Reactive_PowerA + Reactive_PowerB + Reactive_PowerC;
    Apparent_PowerA = SetApparent_Power_ByAng(dUA_mag, dIA_mag);
    Apparent_PowerB = SetApparent_Power_ByAng(dUB_mag, dIB_mag);
    Apparent_PowerC = SetApparent_Power_ByAng(dUC_mag, dIC_mag);
    Total_Apparent_Power = Apparent_PowerA + Apparent_PowerB + Apparent_PowerC;
}
void CalABCValues_ByPowerValues_Float(float &dA_mag, float &dA_ang, float &dB_mag, float &dB_ang, float &dC_mag, float &dC_ang,
									  float fPpower_dA, float fQpower_dA, float fAmp_dA, float fAngle_dA,
									  float fPpower_dB, float fQpower_dB, float fAmp_dB, float fAngle_dB,
									  float fPpower_dC, float fQpower_dC, float fAmp_dC, float fAngle_dC)
{
	 dA_mag = sqrtf((fPpower_dA*fPpower_dA)+(fQpower_dA*fQpower_dA))/fAmp_dA;
	 dA_ang = fAngle_dA - atan2(fQpower_dA,fPpower_dA)* 180 / _PI;

	 dB_mag = sqrtf((fPpower_dB*fPpower_dB)+(fQpower_dB*fQpower_dB))/fAmp_dB;
	 dB_ang = fAngle_dB - atan2(fQpower_dB,fPpower_dB)* 180 / _PI;

	 dC_mag = sqrtf((fPpower_dC*fPpower_dC)+(fQpower_dC*fQpower_dC))/fAmp_dC;
	 dC_ang = fAngle_dC - atan2(fQpower_dC,fPpower_dC)* 180 / _PI;

	 if(abs(fAmp_dA) < 1e-7)
	 {
        dA_mag = 0;
	 }
	 if(abs(fAmp_dB) < 1e-7)
	 {
		 dB_mag = 0;
	 }
	 if(abs(fAmp_dC) < 1e-7)
	 {
		 dC_mag = 0;
	 }
}
