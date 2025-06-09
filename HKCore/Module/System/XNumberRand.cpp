// XNumberRand.cpp: implementation of the CXNumberRand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XNumberRand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXNumberRand::CXNumberRand()
{
		srand(time(0));
		m_nMaxForFloatRandRateCal = 20000;
}

CXNumberRand::~CXNumberRand()
{
	
}

long CXNumberRand::long_Rand()
{
	long nRet = rand();
	return nRet > 0 ? nRet : -nRet;
}

long CXNumberRand::long_RandInRange(long nMinVal, long nMaxVal)
{
	if (nMaxVal == nMinVal)
	{
		return nMinVal;
	}

	long nLength = nMaxVal - nMinVal;
	
	long nRet = 0;
	nRet = rand() % nLength;
	nRet += nMinVal;
	
	return nRet;
}


//范围内的随机数
float CXNumberRand::float_RandInRange(float fMinVal, float fMaxVal)
{
	float fRange = fMaxVal - fMinVal;

	long nRand = rand();
	nRand = nRand % m_nMaxForFloatRandRateCal;
	float fRate = nRand;
	fRate /= m_nMaxForFloatRandRateCal;

	float fValue = fMinVal + fRange * fRate;;
	return fValue;
}


double CXNumberRand::double_RandInRange(double fMinVal, double fMaxVal)
{
	double fRange = fMaxVal - fMinVal;

	long nRand = rand();
	nRand = nRand % m_nMaxForFloatRandRateCal;
	double fRate = nRand;
	fRate /= m_nMaxForFloatRandRateCal;

	double fValue = fMinVal + fRange * fRate;;
	return fValue;
}
