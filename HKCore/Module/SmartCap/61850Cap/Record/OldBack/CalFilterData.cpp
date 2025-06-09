// RtCalFilterData.cpp: implementation of the CRtCalFilterData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CalFilterData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtCalFilterData::CRtCalFilterData(PRTCALFUNCPARA pCalFuncPara, long *pCurrPos)
{
	m_bIsZeroPos = TRUE;
	m_bIsZeroPos2 = TRUE;
	m_pBuffer = pCalFuncPara->pnBuffer;
	m_nDataLength = pCalFuncPara->nDataLength;
	m_nBufferLength = pCalFuncPara->nBufferLength;
	m_pCurrPos = pCurrPos;

#ifndef _CAL_IN_ONLINE_RECORD_ANALYSE
	if (m_nDataLength < m_nBufferLength)
	{
		//if (m_pCurrPos - m_pBuffer < RT_FILTER_DATA_LEN_PREV)
		if (m_pCurrPos - m_pBuffer < RTATTRIBUTECAL_MIN_BUFFER_LEN)
		{
			return;
		}
	}
#endif

	m_ppFilterData[RT_FILTER_DATA_LEN_PREV] = pCurrPos;
	GetPrevData();
	
	m_bIsZeroPos = FALSE;
	m_bIsZeroPos2 = FALSE;

	GetNextData();
	Filter2();

	if (m_bIsZeroPos2)
	{
		Filter();
	}
}

CRtCalFilterData::~CRtCalFilterData()
{

}

void CRtCalFilterData::GetPrevData()
{
	long nIndex = 0;
	long *pTemp = NULL;

	if (m_pCurrPos - m_pBuffer > RT_FILTER_DATA_LEN_PREV)
	{
		pTemp = m_pCurrPos-RT_FILTER_DATA_LEN_PREV;

		for (nIndex=0; nIndex<RT_FILTER_DATA_LEN_PREV; nIndex++)
		{
			m_ppFilterData[nIndex] = pTemp + nIndex;
		}
	}
	else
	{
		long *pEnd = m_pBuffer + m_nBufferLength;
		long nLen1 = m_pCurrPos - m_pBuffer;
		long nLen2 = RT_FILTER_DATA_LEN_PREV - nLen1;

		pTemp = pEnd - nLen2;

		while (pTemp <pEnd)
		{
			m_ppFilterData[nIndex] = pTemp;
			pTemp++;
			nIndex++;
		}

		pTemp = m_pBuffer;

		while (pTemp < m_pCurrPos)
		{
			m_ppFilterData[nIndex] = pTemp;
			pTemp++;
			nIndex++;
		}
	}
}

void CRtCalFilterData::GetNextData()
{
	long nIndex = 0;
	long *pTemp = NULL;
	long *pNext = m_pCurrPos + 1;
	long *pEnd = m_pBuffer + m_nBufferLength;
	long **ppBegin = m_ppFilterData + RT_FILTER_DATA_LEN_PREV + 1;

	if (pNext + RT_FILTER_DATA_LEN_NEXT > pEnd)
	{
		pTemp = pNext;
		long nLen1 = pEnd - pNext;
		long nLen2 = RT_FILTER_DATA_LEN_NEXT - nLen1;

		for (nIndex=0; nIndex<nLen1; nIndex++)
		{
			*ppBegin = pTemp;
			pTemp++;
			ppBegin++;
		}
		
		pTemp = m_pBuffer;

		for (nIndex=0; nIndex<nLen2; nIndex++)
		{
			*ppBegin = pTemp;
			pTemp++;
			ppBegin++;
		}
	}
	else
	{
		pTemp = pNext;

		for (nIndex=0; nIndex<RT_FILTER_DATA_LEN_NEXT; nIndex++)
		{
			*ppBegin = pTemp;
			pTemp++;
			ppBegin++;
		}
	}
}

void CRtCalFilterData::Filter()
{
	m_bIsZeroPos = FALSE;
	long *pTemp = m_ppFilterData[0];
	long *pCurr = m_ppFilterData[RT_FILTER_DATA_LEN_PREV];

	long nIndex = 0;
	short nVal = (short)(**m_ppFilterData);
	short **ppFilterData = (short**)m_ppFilterData;

	for (nIndex=0; nIndex<RT_FILTER_BUFFER_LEN; nIndex++)
	{
		m_pFilterData[nIndex] = *ppFilterData[nIndex] - nVal;
	}
	
	long nSum = 0;

	for (nIndex = 0; nIndex<RT_FILTER_BUFFER_LEN; nIndex++)
	{
		nSum += m_pFilterData[nIndex];
	}

	if (nSum > 0)
	{//上升曲线
		short *pCurr = m_pFilterData;
		short *pEnd = m_pFilterData + RT_FILTER_BUFFER_LEN - 1;

// 		while (pCurr < pEnd)
// 		{
// 			if (*(pCurr+1) < *pCurr)
// 			{
// 				*(pCurr + 1) = *pCurr;
// 			}
// 
// 			pCurr++;
// 		}

		m_bIsZeroPos = TRUE;
	}
	else
	{//下降曲线
		short *pCurr = m_pFilterData;
		short *pEnd = m_pFilterData + RT_FILTER_BUFFER_LEN - 1;
		
// 		while (pCurr < pEnd)
// 		{
// 			if (*(pCurr) < *(pCurr+1))
// 			{
// 				*(pCurr + 1) = *pCurr;
// 			}
// 
// 			pCurr++;
// 		}
	}

// 	for (nIndex=0; nIndex<RT_FILTER_BUFFER_LEN; nIndex++)
// 	{
// 		*ppFilterData[nIndex] = nVal + m_pFilterData[nIndex];
// 	}
}


void CRtCalFilterData::Filter2()
{
	m_bIsZeroPos2 = FALSE;
	long *pTemp = m_ppFilterData[0];
	long *pCurr = m_ppFilterData[RT_FILTER_DATA_LEN_PREV];
	
	long nIndex = 0;
	short nVal = (short)(**m_ppFilterData);
	short **ppFilterData = (short**)m_ppFilterData;
	long nValPre = 0;
	long nValNext = 0;
	
	for (nIndex=0; nIndex<RT_FILTER_DATA_LEN_PREV; nIndex++)
	{
		nValPre += *ppFilterData[nIndex];
	}
	
	for (nIndex=0; nIndex<RT_FILTER_DATA_LEN_NEXT; nIndex++)
	{
		nValNext += *ppFilterData[nIndex+1+RT_FILTER_DATA_LEN_PREV];
	}
	
	if (nValNext > nValPre)
	{
		m_bIsZeroPos2 = TRUE;
	}
	else
	{
		m_bIsZeroPos2 = FALSE;
	}
}

