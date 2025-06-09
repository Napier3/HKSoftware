// DFT.h: interface for the CDFT_Long class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DFT_LONG_H__)
#define _DFT_LONG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DFTBase.h"

class CDFT_Long : public CDFTBase
{
public:
	static CDFT_Long* CreateDft();
	static CDFT_Long* CreateDft(double* pdSin, double* pdCos);
	static CDFT_Long* GetDft();
	static void ReleaseDFT();

public:
	BOOL DFTSINGL(BOOL bFirst,long *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);
	BOOL DFTCalByMap(BOOL bFirst,long* pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);
	BOOL DFTCalByMap(long* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree);
	BOOL CalDFT(double dCoef,long* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue);

protected:
	CDFT_Long();
	virtual ~CDFT_Long();
	static CDFT_Long*g_pDft;
	static long m_nDftRef;

};

#endif // !defined(_DFT_LONG_H__)
