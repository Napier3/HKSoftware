// DFT.cpp: implementation of the CDFT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DFT.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDFT* CDFT::g_pDft = NULL;

CDFT::CDFT()
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

CDFT::~CDFT()
{
	TermTriangle();
	ClearBuffer();
}

//nDegree表示的是nDegree+1次谐波
BOOL CDFT::DFTSINGL(BOOL bFirst,double *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
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
	double* pBegin = pBuffer + nBegin;
	double* pEnd =pBuffer + nEnd;
	double* pTemp = pBegin  + m_nDataLength;
	
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

//nMaxDegree最大谐波次数
//nDataLength 计算的数据长度
//nCircleAmount 数据是几个周期的
void CDFT::InitTriangle(long nMaxDegree,long nDataLength ,long nCircleAmount)
{
	if (m_nMaxDegree >0)
	{
		TermTriangle();
	}
	
	m_nMaxDegree = nMaxDegree;
	m_nDataLength = nDataLength;
	double k = PI * 2 /nDataLength,q;
	m_pCos=new double*[nMaxDegree];
	m_pSin=new double*[nMaxDegree];
	long i,j;

	for(j = 0 ; j < nMaxDegree ; j++)
	{
		m_pCos[j] = new double[nDataLength];
		m_pSin[j] = new double[nDataLength];
	}
	
	for(i = 0 ; i< nMaxDegree ; i++)
	{
		q=(i+1) * nCircleAmount * k;
		double* pCos = m_pCos[i];
		double* pSin = m_pSin[i];

		for(j = 0 ; j < nDataLength ; j++)
		{
			*pCos = cos(q*j);
			pCos++;
			*pSin = sin(q*j);
			pSin++;
		}
	}
}

void CDFT::TermTriangle()
{
	if(m_pSin!=NULL)
	{
		for(int i=0;i<m_nMaxDegree;i++)
		{
			delete m_pSin[i];
		}
		
		delete m_pSin;
		m_pSin=NULL;
	}
	
	if(m_pCos!=NULL)
	{
		for(int j=0;j<m_nMaxDegree;j++)
		{
			delete m_pCos[j];
		}
		
		delete m_pCos;
		m_pCos=NULL;
	}
	
	m_nMaxDegree = 0;
}

//得到根据模拟通道计算的值 nDegree表示的是nDegree+1次谐波
BOOL CDFT::DFTSINGL(BOOL bFirst,short *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
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

//调用一次
CDFT* CDFT::CreateDft()
{
	if (g_pDft == NULL)
	{
		g_pDft = new CDFT();
	}

	return g_pDft;
}

//只在程序退出时调用
void CDFT::ReleaseDFT()
{
	TermTriangle();

	ClearBuffer();
	
	if (g_pDft != NULL)
	{
		delete g_pDft;
	}
}

//////////////////fdp add 2010.3.23
void CDFT::InitBuffer()
{
	if (m_pdSin == NULL)
	{
		m_pdSin = new double[DFT_LENGTH];
	}
	
	if (m_pdCos == NULL)
	{
		m_pdCos = new double[DFT_LENGTH];
	}

	double dTemp = PI * 2 / DFT_LENGTH;
	
	for(int nIndex = 0; nIndex < DFT_LENGTH; nIndex++)
	{
		m_pdCos[nIndex] = cos(nIndex * dTemp );
		m_pdSin[nIndex] = sin(nIndex * dTemp );
	}
}
void CDFT::ClearBuffer()
{
	if (m_pdSin != NULL)
	{
		delete m_pdSin;
		m_pdSin = NULL;
	}
	
	if (m_pdCos != NULL)
	{
		delete m_pdCos;
		m_pdCos = NULL;	
	}
}

BOOL CDFT::DFTCalByMap(BOOL bFirst,short *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
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


BOOL CDFT::DFTCalByMap(BOOL bFirst,float *pBuffer, long nBegin, long nEnd, double &dRealValue, double &dImValue, long nDegree)
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
	float* pBegin = pBuffer + nBegin;
	float* pEnd =pBuffer + nEnd;
	float* pTemp = pBegin  + m_nDataLength;
	
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
		
		/**/
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

BOOL CDFT::DFTCalByMap(short* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree)
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

BOOL CDFT::CalDFT(double dCoef,short* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue)
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


BOOL CDFT::DFTCalByMap(float* pBuffer, long nBegin1, long nLen1,long nBegin2,long nLen2, double &dRealValue, double &dImValue, long nDegree)
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

BOOL CDFT::CalDFT(double dCoef,float* pBuffer,long& nBegin,long& nLen,double &dRealValue, double &dImValue)
{
	float* pBegin = pBuffer + nBegin;
	float* pEnd   = pBegin + nLen;
	
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