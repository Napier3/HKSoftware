// DFT.h: interface for the CDFT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DFT_H__EBA2E7A5_ED06_4841_AA5C_648DC84CA83F__INCLUDED_)
#define AFX_DFT_H__EBA2E7A5_ED06_4841_AA5C_648DC84CA83F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DFTBase.h"
#include "DFT_Long.h"
#include "DFT_Short.h"

class CDFT : public CDFTBase
{
public:
	static CDFT* CreateDft();
	static CDFT* GetDft();
	static void ReleaseDFT();

public:
	//Short
	BOOL DFTSINGL(BOOL bFirst,short *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
	{
		ASSERT (m_pDftShort != NULL);
		return m_pDftShort->DFTSINGL(bFirst, pBuffer, nBegin, nEnd, dRealValue, dImValue, nDegree);
	}
	BOOL DFTCalByMap(BOOL bFirst,short* pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
	{
		ASSERT (m_pDftShort != NULL);
		return m_pDftShort->DFTCalByMap(bFirst, pBuffer, nBegin, nEnd, dRealValue, dImValue, nDegree);
	}
	BOOL DFTCalByMap(short* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree)
	{
		ASSERT (m_pDftShort != NULL);
		return m_pDftShort->DFTCalByMap(pBuffer, nBegin1, nLen1, nBegin2, nLen2, dRealValue, dImValue, nDegree);
	}
	BOOL CalDFT(double dCoef,short* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue)
	{
		ASSERT (m_pDftShort != NULL);
		return m_pDftShort->CalDFT(dCoef, pBuffer, nBegin, nLen, dRealValue, dImValue);
	}

	//long
	BOOL DFTSINGL(BOOL bFirst,long *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
	{
		ASSERT (m_pDftLong != NULL);
		m_pDftLong->DFTSINGL(bFirst, pBuffer, nBegin, nEnd, dRealValue, dImValue, nDegree);
	}
	BOOL DFTCalByMap(BOOL bFirst,long* pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
	{
		ASSERT (m_pDftLong != NULL);
		return m_pDftLong->DFTCalByMap(bFirst, pBuffer, nBegin, nEnd, dRealValue, dImValue, nDegree);
	}
	BOOL DFTCalByMap(long* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree)
	{
		ASSERT (m_pDftLong != NULL);
		return m_pDftLong->DFTCalByMap(pBuffer, nBegin1, nLen1, nBegin2, nLen2, dRealValue, dImValue, nDegree);
	}
	BOOL CalDFT(double dCoef,long* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue)
	{
		ASSERT (m_pDftLong != NULL);
		return m_pDftLong->CalDFT(dCoef, pBuffer, nBegin, nLen, dRealValue, dImValue);
	}

public:
	virtual void SetDftCalGap(long nGap = 1)
	{
		ASSERT (m_pDftShort != NULL);
		ASSERT (m_pDftLong != NULL);
		m_nDftCalGap = nGap;
		m_pDftShort->SetDftCalGap(nGap);
		m_pDftLong->SetDftCalGap(nGap);
	}
	virtual void SetCurrentDataLength(long nDataLen)
	{
		ASSERT (m_pDftShort != NULL);
		ASSERT (m_pDftLong != NULL);
		m_nDataLength = nDataLen;
		m_pDftShort->SetCurrentDataLength(nDataLen);
		m_pDftLong->SetCurrentDataLength(nDataLen);
	}

protected:
	CDFT();
	virtual ~CDFT();
	static CDFT*g_pDft;
	static long m_nDftRef;

	CDFT_Short *m_pDftShort;
	CDFT_Long *m_pDftLong;
};

#endif // !defined(AFX_DFT_H__EBA2E7A5_ED06_4841_AA5C_648DC84CA83F__INCLUDED_)
