// Complex.h: interface for the Complex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Complex_H__25F906BC_5946_4F49_A982_C9998A20DB40__INCLUDED_)
#define AFX_Complex_H__25F906BC_5946_4F49_A982_C9998A20DB40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "math.h"


class Complex  
{
public:
	Complex();
	virtual ~Complex();
	Complex(double,double);
	Complex operator+(const Complex&)const;
	Complex operator+(const double&)const;
	Complex operator-(const Complex&)const;
	Complex operator-(const double&)const;
	Complex operator*(const Complex&)const;
	Complex operator*(const double&)const;
	Complex operator/(const Complex&)const;
	Complex operator/(const double&)const;
	Complex aoperator(double u);
	Complex polar(double mag,double ang);
	double arg(const Complex&)const;
	double arg()const;
	double norm(const Complex&)const;
	double norm()const;
	Complex pnom(const Complex&u)const;
	Complex pnom()const;
	void SetParameter(double dreal,double dimag);
	void SetParameter_ByAmpAng(double mag,double ang);//zhouhj 20230210 
	void SetMag(double dMag);//zhouhj 改变矢量的幅值
	double real;
	double imag;
	double Mag;
	double Ang;
	double Fre;
	double bDC;
	//	double pi;
};

void CalABCValues_BySequenceValues_Double(double &dA_mag,double &dA_ang,double &dB_mag,double &dB_ang,double &dC_mag,double &dC_ang,
										  double dPos_mag,double dPos_ang,double dNeg_mag,double dNeg_ang,double dZero_mag,double dZero_ang);
void CalABCValues_BySequenceValues_Float(float &dA_mag,float &dA_ang,float &dB_mag,float &dB_ang,float &dC_mag,float &dC_ang,
										 double dPos_mag,double dPos_ang,double dNeg_mag,double dNeg_ang,double dZero_mag,double dZero_ang);
double SetFactor_ByAng(double dU_ang,double dI_ang);
double SetActive_Power_ByAng(double dU_mag,double dU_ang,double dI_mag,double dI_ang);
double SetReactive_Power_ByAng(double dU_mag,double dU_ang,double dI_mag,double dI_ang);
double SetApparent_Power_ByAng(double dU_mag,double dI_mag);

void CalABCValues_ByPowerValues_Double(double dUA_mag,double dUA_ang,double dIA_mag,double dIA_ang
									   ,double dUB_mag,double dUB_ang,double dIB_mag,double dIB_ang
									   ,double dUC_mag,double dUC_ang,double dIC_mag,double dIC_ang);

#endif // !defined(AFX_Complex_H__25F906BC_5946_4F49_A982_C9998A20DB40__INCLUDED_)
