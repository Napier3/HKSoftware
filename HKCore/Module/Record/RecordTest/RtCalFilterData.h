// RtCalFilterData.h: interface for the CRtCalFilterData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCALFILTERDATA_H__EB2409BE_D8E1_43D0_92BA_995012F62EF0__INCLUDED_)
#define AFX_RTCALFILTERDATA_H__EB2409BE_D8E1_43D0_92BA_995012F62EF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "../RecordTest/RecordTestClassDef.h"
template <class T, class T2>
class CRtCalFilterData  
{
public:
	CRtCalFilterData(PRTCALFUNCPARA pCalFuncPara, T *pnBuffer, T *pCurrPos)
	{
		m_bIsZeroPos = TRUE;
		m_bIsZeroPos2 = TRUE;
		m_pBuffer = pnBuffer;
		m_nDataLength = pCalFuncPara->nDataLength;
		m_nBufferLength = pCalFuncPara->nBufferLength;
		m_pCurrPos = pCurrPos;

#ifndef _CAL_IN_ONLINE_RECORD_ANALYSE
		if (m_nDataLength < m_nBufferLength)
		{
			//if (m_pCurrPos - m_pBuffer < RT_FILTER_DATA_LEN_PREV)
			if (m_pCurrPos - m_pBuffer < pCalFuncPara->pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN)
			{
				return;
			}
		}
#endif

		m_ppFilterData[pCalFuncPara->pCalLenPara->RT_FILTER_DATA_LEN_PREV] = pCurrPos;
		GetPrevData(pCalFuncPara->pCalLenPara);

		m_bIsZeroPos = FALSE;
		m_bIsZeroPos2 = FALSE;

		GetNextData(pCalFuncPara->pCalLenPara);
		Filter2(pCalFuncPara->pCalLenPara);

		if (m_bIsZeroPos2)
		{
			Filter(pCalFuncPara->pCalLenPara);
		}
	}
	virtual ~CRtCalFilterData(){}

	T *m_ppFilterData[RT_FILTER_BUFFER_LEN];
	T2 m_pFilterData[RT_FILTER_BUFFER_LEN];
	T *m_pBuffer;
	long m_nDataLength;
	long m_nBufferLength;
	T *m_pCurrPos;

	BOOL IsZeroPos()   {    return (m_bIsZeroPos && m_bIsZeroPos);    }
private:
	CRtCalFilterData(){}
	BOOL m_bIsZeroPos;
	BOOL m_bIsZeroPos2;

	void GetPrevData(PRECORD_CAL_LEN_PARA pCalLenPara)
	{
		long nIndex = 0;
		T *pTemp = NULL;

		if (m_pCurrPos - m_pBuffer > pCalLenPara->RT_FILTER_DATA_LEN_PREV)
		{
			pTemp = m_pCurrPos-pCalLenPara->RT_FILTER_DATA_LEN_PREV;

			for (nIndex=0; nIndex<pCalLenPara->RT_FILTER_DATA_LEN_PREV; nIndex++)
			{
				m_ppFilterData[nIndex] = pTemp + nIndex;
			}
		}
		else
		{
			T *pEnd = m_pBuffer + m_nBufferLength;
			long nLen1 = m_pCurrPos - m_pBuffer;
			long nLen2 = pCalLenPara->RT_FILTER_DATA_LEN_PREV - nLen1;

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
	void GetNextData(PRECORD_CAL_LEN_PARA pCalLenPara)
	{
		long nIndex = 0;
		T *pTemp = NULL;
		T *pNext = m_pCurrPos + 1;
		T *pEnd = m_pBuffer + m_nBufferLength;
		T **ppBegin = m_ppFilterData + pCalLenPara->RT_FILTER_DATA_LEN_PREV + 1;

		if (pNext + pCalLenPara->RT_FILTER_DATA_LEN_NEXT > pEnd)
		{
			pTemp = pNext;
			long nLen1 = pEnd - pNext;
			long nLen2 = pCalLenPara->RT_FILTER_DATA_LEN_NEXT - nLen1;

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

			for (nIndex=0; nIndex<pCalLenPara->RT_FILTER_DATA_LEN_NEXT; nIndex++)
			{
				*ppBegin = pTemp;
				pTemp++;
				ppBegin++;
			}
		}
	}

	void Filter(PRECORD_CAL_LEN_PARA pCalLenPara)
	{
		m_bIsZeroPos = FALSE;
		T *pTemp = m_ppFilterData[0];
		T *pCurr = m_ppFilterData[pCalLenPara->RT_FILTER_DATA_LEN_PREV];

		long nIndex = 0;
		T2 nVal = (T2)(**m_ppFilterData);
		T2 **ppFilterData = (T2**)m_ppFilterData;

		for (nIndex=0; nIndex<pCalLenPara->USE_RT_FILTER_BUFFER_LEN; nIndex++)
		{
			m_pFilterData[nIndex] = *ppFilterData[nIndex] - nVal;
		}

		long nSum = 0;

		for (nIndex = 0; nIndex<pCalLenPara->USE_RT_FILTER_BUFFER_LEN; nIndex++)
		{
			nSum += m_pFilterData[nIndex];
		}

		if (nSum > 0)
		{//上升曲线
			T2 *pCurr = m_pFilterData;
			T2 *pEnd = m_pFilterData + pCalLenPara->USE_RT_FILTER_BUFFER_LEN - 1;
			m_bIsZeroPos = TRUE;
		}
		else
		{//下降曲线
			T2 *pCurr = m_pFilterData;
			T2 *pEnd = m_pFilterData + pCalLenPara->USE_RT_FILTER_BUFFER_LEN - 1;
		}
	}

	void Filter2(PRECORD_CAL_LEN_PARA pCalLenPara)
	{
		m_bIsZeroPos2 = FALSE;
		T *pTemp = m_ppFilterData[0];
		T *pCurr = m_ppFilterData[pCalLenPara->RT_FILTER_DATA_LEN_PREV];

		long nIndex = 0;
		T2 nVal = (T2)(**m_ppFilterData);
		T2 **ppFilterData = (T2**)m_ppFilterData;
		long nValPre = 0;
		long nValNext = 0;

		for (nIndex=0; nIndex<pCalLenPara->RT_FILTER_DATA_LEN_PREV; nIndex++)
		{
			nValPre += *ppFilterData[nIndex];
		}

		for (nIndex=0; nIndex<pCalLenPara->RT_FILTER_DATA_LEN_NEXT; nIndex++)
		{
			nValNext += *ppFilterData[nIndex+1+pCalLenPara->RT_FILTER_DATA_LEN_PREV];
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
};

#endif // !defined(AFX_RTCALFILTERDATA_H__EB2409BE_D8E1_43D0_92BA_995012F62EF0__INCLUDED_)
