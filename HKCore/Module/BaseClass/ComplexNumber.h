// ComplexNumber.h: interface for the CComplexNumber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLEXNUMBER_H__31CB2902_876D_4A6C_AD3A_5A72D33F7F14__INCLUDED_)
#define AFX_COMPLEXNUMBER_H__31CB2902_876D_4A6C_AD3A_5A72D33F7F14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define COMPLEX_MODE_RADIAN  0
#define COMPLEX_MODE_DEGREE 1

class CComplexNumber  
{
public:
	
public:
	double	m_fReal;
	double	m_fImaginary;

public:
	CComplexNumber(double fModulus,double fAngle,long nMode);
	CComplexNumber(double fReal,double fImaginary);
	CComplexNumber();
	virtual ~CComplexNumber();

	void Set(double fReal,double fImaginary,long nMode=COMPLEX_MODE_DEGREE);
	double GetRadianAngle();
	double GetAngle();
	double GetAngle_180_180();
	double GetAngle_0_360();
	double GetModulus ();
	void GetValueAngle(double &fModulus,double &fAngle,long nMode=COMPLEX_MODE_DEGREE);
	void SetValueAngle(double fModulus,double fAngle,long nMode=COMPLEX_MODE_DEGREE);
	void GetValue(double &fReal,double &fImaginary);
	void SetValue(double fReal,double fImaginary);
	static double	GetTheAngleRange_180_180(double fAngle);
	static double	GetTheAngleRange_0_360(double fAngle);
	void Rotate(double fAngle,long nMode=COMPLEX_MODE_DEGREE);
	void Zoom(double fCoef);
	
public:
	CComplexNumber& operator=(const CComplexNumber &val);
	BOOL operator==(const CComplexNumber &val);
	CComplexNumber& operator+=(const CComplexNumber &val);
	CComplexNumber& operator-=(const CComplexNumber &val);
	CComplexNumber& operator*=(const CComplexNumber &val);
	CComplexNumber& operator/=(const CComplexNumber &val);

	CComplexNumber operator+(const CComplexNumber &val);
	CComplexNumber operator-(const CComplexNumber &val);
	CComplexNumber operator*(const CComplexNumber &val);
	CComplexNumber operator/(const CComplexNumber &val);

	CComplexNumber& Add(const CComplexNumber &lhs,const CComplexNumber &rhs);
	CComplexNumber& Minus(const CComplexNumber &lhs,const CComplexNumber &rhs);
	CComplexNumber& Multiply(const CComplexNumber &lhs,const CComplexNumber &rhs);
	CComplexNumber& Divide(const CComplexNumber &lhs,const CComplexNumber &rhs);
};


#endif // !defined(AFX_COMPLEXNUMBER_H__31CB2902_876D_4A6C_AD3A_5A72D33F7F14__INCLUDED_)
