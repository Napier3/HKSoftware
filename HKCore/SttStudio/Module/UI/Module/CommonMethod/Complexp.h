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
	Complex aoperator(double u);
	Complex polar(double mag,double ang);
	double arg(const Complex&)const;
	double arg()const;
	double norm(const Complex&)const;
	double norm()const;
	Complex pnom(const Complex&u)const;
	Complex pnom()const;
	void SetParameter(double dreal,double dimag);
	double real;
	double imag;
	double Mag;
	double Ang;
	double Fre;
	double bDC;
//	double pi;
};

#endif // !defined(AFX_Complex_H__25F906BC_5946_4F49_A982_C9998A20DB40__INCLUDED_)
