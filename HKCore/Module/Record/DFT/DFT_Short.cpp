// DFT_Short.cpp: implementation of the CDFT_Short class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DFT_Short.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDFT_Short* CDFT_Short::g_pDft = NULL;
long CDFT_Short::m_nDftRef = 0;

CDFT_Short::CDFT_Short()
{
	m_pCos=NULL;
	m_pSin=NULL;
	m_nCalPos = 0;
	m_nMaxDegree = 100;	
	m_nDataLength = 0;

	m_pdSin = NULL;
	m_pdCos = NULL;
	m_nDftCalGap = 1;
}

CDFT_Short::~CDFT_Short()
{
	TermTriangle();
	ClearSinCos();
}

//�õ�����ģ��ͨ�������ֵ nDegree��ʾ����nDegree+1��г��
BOOL CDFT_Short::DFTSINGL(BOOL bFirst,short *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
{
	if (nDegree >= m_nMaxDegree)
	{
		m_nCalPos = 0;
		dRealValue = dImValue = 0.0;
		return FALSE;
	}

	if (nEnd <= nBegin)
	{
		m_nCalPos = 0;
		dRealValue = dImValue = 0.0;
		return FALSE;
	}

	if (bFirst)
	{
		dRealValue = dImValue = 0.0;
		m_nCalPos = 0;
	}
	
	double* pCurrentCos = m_pCos[nDegree] + m_nCalPos;
	double* pCurrentSin = m_pSin[nDegree] + m_nCalPos;
	short* pBegin = pBuffer + nBegin;
	short* pEnd =pBuffer + nEnd;
	short* pTemp = pBegin  + m_nDataLength;

	if (pEnd >pTemp)
	{
		pEnd = pTemp;
	}
	
	while(pBegin < pEnd)
	{
		dRealValue += (*pCurrentCos) * (*pBegin);
		dImValue   += (*pCurrentSin) * (*pBegin);
		m_nCalPos ++;
		pCurrentSin ++;
		pCurrentCos ++;
		pBegin++;
	}

	return TRUE;
}

//����һ��
CDFT_Short* CDFT_Short::CreateDft()
{
	m_nDftRef++;

	if (m_nDftRef == 1)
	{
		ASSERT (g_pDft == NULL);
		g_pDft = new CDFT_Short();
		g_pDft->InitSinCos();
	}

	return g_pDft;
}
CDFT_Short* CDFT_Short::CreateDft(double* pdSin, double* pdCos)
{
	m_nDftRef++;

	if (m_nDftRef == 1)
	{
		ASSERT (g_pDft == NULL);
		g_pDft = new CDFT_Short();
		g_pDft->AttatchSinCos(pdSin, pdCos);
	}

	return g_pDft;
}

CDFT_Short* CDFT_Short::GetDft()
{
	//ASSERT( g_pDft != NULL );
	return g_pDft;
}

//ֻ�ڳ����˳�ʱ����
void CDFT_Short::ReleaseDFT()
{
	m_nDftRef--;

	if (m_nDftRef != 0)
	{
		return;
	}

	if (g_pDft != NULL)
	{
		g_pDft->TermTriangle();
		g_pDft->ClearSinCos();
		delete g_pDft;
		g_pDft = NULL;
	}
}

BOOL CDFT_Short::DFTCalByMap(BOOL bFirst,short *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
{
	if (nDegree >= m_nMaxDegree)
	{
		m_nCalPos = 0;
		dRealValue = dImValue = 0.0;
		return FALSE;
	}
	
	if (nEnd <= nBegin)
	{
		m_nCalPos = 0;
		dRealValue = dImValue = 0.0;
		return FALSE;
	}
	
	if (bFirst)
	{
		dRealValue = dImValue = 0.0;
		m_nCalPos = 0;
	}
	
	long nHar = (nDegree + 1);
	short* pBegin = pBuffer + nBegin;
	short* pEnd =pBuffer + nEnd;
	short* pTemp = pBegin  + m_nDataLength;
	
	if (pEnd >pTemp)
	{
		pEnd = pTemp;
	}
	
	if (m_nDataLength < 1)
	{
		dRealValue = 0;
		dImValue   = 0;
		return FALSE;
	}

	double dTemp = DFT_LENGTH * nHar;
	dTemp /= m_nDataLength;
	
	while(pBegin < pEnd)
	{
		long nPos = (long)(m_nCalPos * dTemp);

		if (nPos >= DFT_LENGTH) 
		{
			nPos = nPos % DFT_LENGTH;
		}

		if (nPos < 0)
		{
			dRealValue = 0;
			dImValue   = 0;
			return FALSE;
		}

		
		dRealValue += (m_pdCos[nPos]) * (*pBegin);
		dImValue   += (m_pdSin[nPos]) * (*pBegin);
		m_nCalPos++;
		pBegin++;
	}
	
	return TRUE;
}


BOOL CDFT_Short::DFTCalByMap(short* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree)
{
	dImValue = dRealValue = 0;
	BOOL bCal = FALSE;
	if (nDegree >= m_nMaxDegree)
	{
		m_nCalPos = 0;
		dRealValue = dImValue = 0.0;
		return FALSE;
	}

	long nHar = (nDegree + 1);
	double dTemp = DFT_LENGTH * nHar;
	dTemp /= m_nDataLength;
	dTemp *= m_nDftCalGap;

	if ((nLen1 > 0) && (nBegin1 >= 0))
	{
		bCal = CalDFT(dTemp,pBuffer,nBegin1,nLen1,dRealValue,dImValue);
	}

	if ((nLen2 > 0 )&& (nBegin2 >= 0) )
	{
		long nRemain = nLen1 % m_nDftCalGap;

		long nBegin = nBegin2 ;
		long nLen = nLen2;

		if (nRemain == 0)
		{
		}
		else
		{
			nBegin += (m_nDftCalGap - nRemain);
			nLen -= nRemain;
		}	

		bCal = CalDFT(dTemp,pBuffer,nBegin,nLen,dRealValue,dImValue);
	}

	m_nCalPos = 0;
	return bCal;
}

BOOL CDFT_Short::CalDFT(double dCoef,short* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue)
{
	short* pBegin = pBuffer + nBegin;
	short* pEnd   = pBegin + nLen;
	
	while(pBegin < pEnd)
	{
		long nPos = (long)(m_nCalPos * dCoef);
		
		if (nPos >= DFT_LENGTH) 
		{
			nPos = nPos % DFT_LENGTH;
		}
		
		if (nPos < 0)
		{
			dRealValue = 0;
			dImValue   = 0;
			return FALSE;
		}
			
		dRealValue += (m_pdCos[nPos]) * (*pBegin);
		dImValue   += (m_pdSin[nPos]) * (*pBegin);
		m_nCalPos++;
		pBegin += m_nDftCalGap;
	}

	return TRUE;
}

