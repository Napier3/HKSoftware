// Complexp.cpp: implementation of the Complexp class.
//
//////////////////////////////////////////////////////////////////////

#include "Complexp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
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
	Mag=Ang=real=imag = 0.0;
//	pi=3.1415926;
}
Complex::~Complex()
{

}


Complex::Complex(double re,double im)
{
	/*Mag = */real = re;
	/*Ang = */imag = im;
}
Complex Complex::operator+(const Complex&u)const
{
	Complex v(real+u.real,imag+u.imag);
	return v;
}
Complex Complex::operator+(const double&u)const
{
	Complex v(real+u,imag);
	return v;
}
Complex Complex::operator-(const Complex&u)const
{
	Complex v(real-u.real,imag-u.imag);
	return v;
}
Complex Complex::operator-(const double&u)const
{
	Complex v(real-u,imag);
	return v;
}
Complex Complex::operator*(const Complex&u)const
{
	Complex v(real*u.real-imag*u.imag,imag*u.real+real*u.imag);
	return v;
}
Complex Complex::operator*(const double&u)const
{
	Complex v(real*u,imag*u);
	return v;
}
Complex Complex::operator/(const Complex&u)const
{
	Complex v((real*u.real+imag*u.imag)/(u.real*u.real+u.imag*u.imag),(imag*u.real-real*u.imag)/(u.real*u.real+u.imag*u.imag));
	return v;
}
Complex Complex::aoperator(double u)
{
	Complex v(cos(u*3.1415926/180.0),sin(u*3.1415926/180.0));
	return v;
}
Complex Complex::polar(double mag,double ang)
{
	if(fabs(mag)<0.0000001)mag=0.0000001;
	double dm = cos(ang*3.1415926/180.0);
	double da = sin(ang*3.1415926/180.0);
	Complex v(mag*dm,mag*da);
	v.Mag = mag;
	v.Ang = ang;
	return v;
}
double Complex::norm(const Complex&u)const
{
	double v=_hypot(u.real,u.imag);
	return v;
}
double Complex::norm()const
{
	double v=_hypot(real,imag);
	return v;
}
Complex Complex::pnom(const Complex&u)const
{
	Complex v(u.real,-u.imag);
	return v;
}
Complex Complex::pnom()const
{
	Complex v(real,-imag);
	return v;
}
double Complex::arg(const Complex&u)const
{
	double v;
	if(fabs(u.real)>0.0000000001)v=(float)atan2(u.imag,u.real)*180.0/3.1415926;
	else
	{
		if(fabs(u.imag)<0.0000000001&&fabs(u.real)<0.00000001)v=0;
		else
		{
			if(u.imag>=0.0000000001f)v=90.0f;
			else v=270.0f;
		}
    }
	return v;
}
double Complex::arg()const
{
	double v;
	if(fabs(real)>0.0000000001)
		v=(float)atan2(imag,real)*180.0/3.1415926;
	else
	{
		if(fabs(imag)<0.0000000001&&fabs(real)<0.00000001)v=0;
		else
		{
			if(imag>=0.0000000001f)v=90.0f;
			else v=270.0f;
		}
	}
	return v;
}
void Complex::SetParameter(double dreal,double dimag)
{	
	real=Mag=dreal;
	imag=Ang=dimag;
}