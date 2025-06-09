// DFT_Short.h: interface for the CDFT_Short class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DFT_Short_h__)
#define _DFT_Short_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DFTBase.h"

class CDFT_Short : public CDFTBase
{
public:
	static CDFT_Short* CreateDft();
	static CDFT_Short* CreateDft(double* pdSin, double* pdCos);
	static CDFT_Short* GetDft();
	static void ReleaseDFT();

public:
	BOOL DFTSINGL(BOOL bFirst,short *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);
	BOOL DFTCalByMap(BOOL bFirst,short* pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree);
	BOOL DFTCalByMap(short* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree);
	BOOL CalDFT(double dCoef,short* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue);

protected:
	CDFT_Short();
	virtual ~CDFT_Short();
	static CDFT_Short*g_pDft;
	static long m_nDftRef;

};

#endif // !defined(_DFT_Short_h__)
