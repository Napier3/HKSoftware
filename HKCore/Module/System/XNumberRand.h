// XNumberRand.h: interface for the CXNumberRand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(XNumberRand_H__)
#define XNumberRand_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXNumberRand  
{
public:
	CXNumberRand();
	virtual ~CXNumberRand();

	long long_Rand();
	long long_RandInRange(long nMinVal, long nMaxVal);
	float float_RandInRange(float fMinVal, float fMaxVal);
	double double_RandInRange(double fMinVal, double fMaxVal);

protected:
	long m_nMaxForFloatRandRateCal;
	
public:
	void SetMaxForFloatRandRateCal(long nVal)	{	m_nMaxForFloatRandRateCal = nVal;	}
};

#endif // !defined(XNumberRand_H__)
