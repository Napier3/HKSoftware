// RecordCmpBuffer.cpp: implementation of the CRecordCmpBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordCmpBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CRecordCmpBuffer::CRecordCmpBuffer()
{
	m_pDeltaBuffer1 = NULL;
	m_pDeltaBuffer2 = NULL;
	m_pBuffer1 = NULL;
	m_pBuffer2 = NULL;

	ZeroMemory(&m_oRcdCmpBuffers1, sizeof(RCD_CMP_FETURES));
	ZeroMemory(&m_oRcdCmpBuffers2, sizeof(RCD_CMP_FETURES));

	m_pRcdCmpFeture1 = NULL;
	m_pRcdCmpFeture2 = NULL;

	m_nSampleRate1 = 10000;
	m_nSampleRate2 = 10000;

	m_fSetValForFind = 0.5;
	m_fSetValForCmp = 10;

	m_nAllignPosition1 = -1;
	m_nAllignPosition2 = -1;
}

CRecordCmpBuffer::~CRecordCmpBuffer()
{

}

void CRecordCmpBuffer::SetBuffer(CMemBuffer_Float *pBuff1, CMemBuffer_Float *pBuff2)
{
	m_pBuffer1 = pBuff1;
	m_pBuffer2 = pBuff2;	
}

void CRecordCmpBuffer::RcdCmp(CMemBuffer_Float *pBuff1, CMemBuffer_Float *pBuff2
								  , long nSampleRate1, long nSampleRate2
								  , float fSetValForFind, float fSetValForCmp)
{
	m_nSampleRate1 = nSampleRate1;
	m_nSampleRate2 = nSampleRate2;
	m_fSetValForFind = fSetValForFind;
	m_fSetValForCmp = fSetValForCmp;
	m_pDeltaBuffer1 = pBuff1;
	m_pDeltaBuffer2 = pBuff2;

	long nCyclePoints1 = rcd_CalCyclePoints(m_nSampleRate1, 50.0);
	long nCyclePoints2 = rcd_CalCyclePoints(m_nSampleRate2, 50.0);
	
	InitRcdCmpFetures(m_pDeltaBuffer1, m_pBuffer1, &m_oRcdCmpBuffers1, nCyclePoints1);
	InitRcdCmpFetures(m_pDeltaBuffer2, m_pBuffer2, &m_oRcdCmpBuffers2, nCyclePoints2);

	RcdFetureAllign();

	if (m_pRcdCmpFeture1 != NULL && m_pRcdCmpFeture2 != NULL)
	{	//最大值下面一个周波
		m_nAllignPosition1 = m_pRcdCmpFeture1->nMaxPos + nCyclePoints1;
		m_nAllignPosition2 = m_pRcdCmpFeture2->nMaxPos + nCyclePoints2;
	}
	else
	{
		m_nAllignPosition1 = -1;
		m_nAllignPosition2 = -1;
	}

}

void CRecordCmpBuffer::LogRcdCmp(const CString &strVariableID)
{
	if (m_pRcdCmpFeture1 == NULL || m_pRcdCmpFeture2 == NULL)
	{
		return;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s: [%d:%d-%d-%d]   [%d:%d-%d-%d]"), strVariableID
		, m_nAllignPosition1, m_pRcdCmpFeture1->nBeginPos, m_pRcdCmpFeture1->nMaxPos, m_pRcdCmpFeture1->nEndPos
		, m_nAllignPosition2, m_pRcdCmpFeture2->nBeginPos, m_pRcdCmpFeture2->nMaxPos, m_pRcdCmpFeture2->nEndPos);

}

void CRecordCmpBuffer::RcdFetureAllign()
{
	//默认：故指只有一个波形特征
	long nCount1 = m_oRcdCmpBuffers1.nFetureCount;
	long nIndex1 = nCount1;
	long nCount2 = m_oRcdCmpBuffers2.nFetureCount;
	long nIndex2 = nCount2;

// 	if (m_oRcdCmpBuffers2.nFetureCount != 1)
// 	{
// 		return;
// 	}

	PRCD_CMP_FETURE pFeture2 = &m_oRcdCmpBuffers2.fetures[0];

	for (nIndex2=nCount2-1; nIndex2>=0; nIndex2--)
	{
		pFeture2 = &m_oRcdCmpBuffers2.fetures[nIndex2];
	
		for (nIndex1=nCount1-1; nIndex1>= 0; nIndex1--)
		{
			if (RcdFetureCmp(&m_oRcdCmpBuffers1.fetures[nIndex1], pFeture2))
			{
				m_pRcdCmpFeture1 = &m_oRcdCmpBuffers1.fetures[nIndex1];
				m_pRcdCmpFeture2 = pFeture2;
				break;
			}
		}

		if (m_pRcdCmpFeture1 != NULL)
		{
			break;
		}
	}
}

BOOL CRecordCmpBuffer::RcdFetureCmp(PRCD_CMP_FETURE pFeture1, PRCD_CMP_FETURE pFeture2)
{
	float fDeltaMax = abs(pFeture1->fMaxValueDelta - pFeture2->fMaxValueDelta);
	float fDeltaBegin = abs(pFeture1->fBeginDelta - pFeture2->fBeginDelta);
	float fDeltaEnd = abs(pFeture1->fEndDelta - pFeture2->fEndDelta);

	float fMax = abs(pFeture1->fMaxValue - pFeture2->fMaxValue);
	float fBegin = abs(pFeture1->fBegin - pFeture2->fBegin);
	float fEnd = abs(pFeture1->fEnd - pFeture2->fEnd);

	if (fDeltaMax < m_fSetValForCmp && fDeltaBegin < m_fSetValForCmp && fDeltaEnd < m_fSetValForCmp)
	{
		if (fMax < m_fSetValForCmp && fBegin < m_fSetValForCmp && fEnd < m_fSetValForCmp)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

void CRecordCmpBuffer::InitRcdCmpFetures(CMemBuffer_Float *pBuffDelta, CMemBuffer_Float *pBuff, PRCD_CMP_FETURES pFetures, long nCyclePoints)
{
	//float fMax = CalMaxValue(pBuff);
	float *pfBufBegin = pBuffDelta->GetBuffer_float();
	float *pfCurr = pfBufBegin;
	float *pfEnd = pfBufBegin + pBuffDelta->GetBufferLength();
	float fGapMax = 0;
	long nTotalCount = 0;
	long nMaxPos = 0;
	long nCalPoints = (long)(0.8 * nCyclePoints);
	long nBeginPos = 0;
	float *pfBufValue = pBuff->GetBuffer_float();

	float *pfFetureBegin = NULL, *pfFetureEnd = NULL, *pfFetureMax = NULL;

	while (pfCurr < pfEnd)
	{
		pfFetureBegin = NULL;
		pfFetureEnd = NULL;
		pfFetureMax = NULL;

		CalFetureAvg_FindPos(pfCurr, pfEnd, nCyclePoints, &pfFetureBegin, &pfFetureEnd, &pfFetureMax);

		if (pfFetureMax == NULL)
		{
			break;
		}

		nTotalCount = pfFetureEnd - pfFetureBegin;

		if (nTotalCount > nCalPoints && pfFetureMax - pfBufBegin > nCalPoints/3)
		{
			nBeginPos = pfFetureBegin - pfBufBegin;
			AddFeture(pFetures
				,  pfFetureBegin - pfBufBegin,  pfFetureMax - pfBufBegin,  pfFetureEnd - pfBufBegin
				, *pfFetureBegin, *pfFetureMax, *pfFetureEnd
				, pfBufValue);
			pfCurr = pfFetureEnd + 1;
		}
		else
		{
			pfCurr++;
		}
	}
}
// 
// void CRecordCmpBuffer::CalFeture(float *pfBegin, float *pfEnd, float &fGapMax, long &nTotalCount, long &nMaxPos)
// {
// 	float *pfTemp = pfBegin + 1;
// 	float fCal = 0;
// 
// 	if (*pfBegin < *pfTemp)
// 	{
// 		while (pfTemp < pfEnd)
// 		{
// 			if (*pfBegin <= *pfTemp)
// 			{
// 				fCal = *pfTemp - *pfBegin;
// 
// 				if (fGapMax <= fCal)
// 				{
// 					fGapMax = fCal;
// 					nMaxPos = pfTemp - pfBegin;
// 				}
// 
// 				pfTemp++;
// 			}
// 			else
// 			{
// 				break;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		while (pfTemp < pfEnd)
// 		{
// 			if (*pfBegin >= *pfTemp)
// 			{
// 				fCal = *pfBegin - *pfTemp;
// 
// 				if (fGapMax <= fCal)
// 				{
// 					fGapMax = fCal;
// 					nMaxPos = pfTemp - pfBegin;
// 				}
// 
// 				pfTemp++;
// 			}
// 			else
// 			{
// 				break;
// 			}
// 		}
// 	}
// 
// 	nTotalCount = pfTemp - pfBegin;
// }

void CRecordCmpBuffer::CalFetureAvg_FindPos_PeakValley(float fAvgVal, long nCyclePoints, float *pfBegin, float *pfEnd
									  ,float **ppfBegin, float **ppfEnd, float **ppfGapMax)
{
	//查找差值大于m_fSetValForCmp的起点
	float fVal = 0;
	float *pfCurr = pfBegin;
	float *pfCurrEnd = pfEnd - nCyclePoints;

	while (pfCurr <pfEnd)
	{
		fVal = abs(*pfCurr - *(pfCurr+nCyclePoints));

		if (fVal > m_fSetValForCmp)
		{
			break;
		}

		pfCurr++;
	}
	
	pfCurr += nCyclePoints / 2;
	pfCurrEnd = pfCurr + nCyclePoints * 3;

	if (pfCurrEnd > pfEnd)
	{
		pfCurrEnd = pfEnd;
	}

	float fMax = -100000000;//*pfCurr;

	if (*pfCurr < *(pfCurr + nCyclePoints))
	{//峰
		fMax = -100000000;//*pfCurr;

		while (pfCurr < pfCurrEnd)
		{
			if (fMax < *pfCurr)
			{
				fMax = *pfCurr;
				*ppfGapMax = pfCurr;
			}

			pfCurr++;
		}
	}
	else
	{
		fMax = 100000000;//*pfCurr;

		while (pfCurr < pfCurrEnd)
		{
			if (fMax > *pfCurr)
			{
				fMax = *pfCurr;
				*ppfGapMax = pfCurr;
			}

			pfCurr++;
		}
	}

	if (*ppfGapMax == NULL)
	{
		*ppfBegin = NULL;
		*ppfEnd = pfCurrEnd;
	}
	else
	{

		if (*ppfGapMax >= pfEnd)
		{
			*ppfBegin = NULL;
			*ppfEnd = pfCurrEnd;
			*ppfGapMax = NULL;
			return;
		}

		*ppfBegin = *ppfGapMax - nCyclePoints;
		*ppfEnd = *ppfGapMax + nCyclePoints;

		if (*ppfEnd >= pfEnd)
		{
			*ppfBegin = NULL;
			*ppfEnd = pfCurrEnd;
			*ppfGapMax = NULL;
			return;
		}

		fVal = **ppfGapMax - **ppfBegin;
		fVal = abs(fVal);

		if (fVal < m_fSetValForCmp)
		{
			*ppfBegin = NULL;
			*ppfEnd = pfCurrEnd;
			*ppfGapMax = NULL;
		}
	}

}

// void CRecordCmpBuffer::CalFetureAvg_FindPos_PeakValley(float fAvgVal, long nCyclePoints, float *pfBegin, float *pfEnd
// 									  ,float **ppfBegin, float **ppfEnd, float **ppfGapMax)
// {
// 	long nOffset = nCyclePoints / 2;
// 
// 	if (fAvgVal > *(pfBegin + nOffset) )
// 	{//谷
// 		CalFetureAvg_FindPos_PeakValley1(fAvgVal, nCyclePoints, pfBegin, pfEnd, ppfBegin, ppfEnd, ppfGapMax);
// 	}
// 	else
// 	{//峰
// 		CalFetureAvg_FindPos_PeakValley2(fAvgVal, nCyclePoints, pfBegin, pfEnd, ppfBegin, ppfEnd, ppfGapMax);
// 	}
// }

void CRecordCmpBuffer::CalFetureAvg_FindPos_PeakValley1(float fAvgVal, long nCyclePoints, float *pfBegin, float *pfEnd
													   ,float **ppfBegin, float **ppfEnd, float **ppfGapMax)
{
	float *pfCurr = pfBegin;
	float fGapMax = *pfCurr;

	while (fAvgVal < *pfCurr)
	{
		pfCurr++;
	}

	while (fAvgVal >= *pfCurr)
	{
		if (fGapMax > *pfCurr)
		{
			fGapMax = *pfCurr;
			*ppfGapMax = pfCurr;
		}

		pfCurr++;
	}

	*ppfBegin = pfCurr;
	*ppfEnd = pfCurr;
}


void CRecordCmpBuffer::CalFetureAvg_FindPos_PeakValley2(float fAvgVal, long nCyclePoints, float *pfBegin, float *pfEnd
													   ,float **ppfBegin, float **ppfEnd, float **ppfGapMax)
{
	float *pfCurr = pfBegin;
	float fGapMax = *pfCurr;

	while (fAvgVal <= *pfCurr)
	{
		if (fGapMax < *pfCurr)
		{
			fGapMax = *pfCurr;
			*ppfGapMax = pfCurr;
		}

		pfCurr++;
	}

	*ppfBegin = pfCurr;
	*ppfEnd = pfCurr;
}
// 
// void CRecordCmpBuffer::CalFetureAvg_FindPos_PeakValley(float fAvgVal, long nCyclePoints, float *pfBegin, float *pfEnd
// 									  ,float **ppfBegin, float **ppfEnd, float **ppfGapMax)
// {
// 	long nOffset = nCyclePoints / 2;
// 	float *pfCurr = pfBegin;
// 	float fGapMax;
// 
// 	if (fAvgVal > *(pfBegin + nOffset) )
// 	{//谷
// 		while (fAvgVal < *pfCurr)
// 		{
// 			pfCurr++;
// 		}
// 
// 		*ppfBegin = pfCurr;
// 		fGapMax = *pfCurr;
// 
// 		while (fAvgVal >= *pfCurr)
// 		{
// 			if (fGapMax > *pfCurr)
// 			{
// 				fGapMax = *pfCurr;
// 				*ppfGapMax = pfCurr;
// 			}
// 
// 			pfCurr++;
// 		}
// 
// 		*ppfEnd = pfCurr;
// 	}
// 	else
// 	{//峰
// 		while (fAvgVal > *pfCurr)
// 		{
// 			pfCurr++;
// 		}
// 
// 		*ppfBegin = pfCurr;
// 		fGapMax = *pfCurr;
// 
// 		while (fAvgVal <= *pfCurr)
// 		{
// 			if (fGapMax < *pfCurr)
// 			{
// 				fGapMax = *pfCurr;
// 				*ppfGapMax = pfCurr;
// 			}
// 
// 			pfCurr++;
// 		}
// 
// 		*ppfEnd = pfCurr;
// 	}
// }

void CRecordCmpBuffer::CalFetureAvg_FindPos(float *pfBegin, float *pfEnd, long nCyclePoints
									 ,float **ppfBegin, float **ppfEnd, float **ppfGapMax)
{
	float *pfTemp = pfBegin;
	double dAvg = 0;
/*
	float fCal = 0;
	double dSum = 0;
	pfEnd = pfEnd - 1;

	while (pfTemp < pfEnd)
	{
		fCal = *(pfTemp+1) - *pfTemp;
		fCal = abs(fCal);

		if (fCal < m_fSetValForFind)
		{
			dSum += *pfTemp;
		}
		else
		{
			break;
		}

		pfTemp++;
	}

	//是否需要考虑异常：点数nCalCount <= 1?2
	long nCalCount = pfTemp - pfBegin;
	dAvg = dSum / nCalCount;
*/

	CalFetureAvg_FindPos_PeakValley(dAvg, nCyclePoints, pfTemp, pfEnd, ppfBegin, ppfEnd, ppfGapMax);
}

void CRecordCmpBuffer::AddFeture(PRCD_CMP_FETURES pFetures, long nBeginPos, long nMaxPos, long nEndPos
								 , float fBegin, float fMax, float fEnd, float *pfBufValue)
{
	if (pFetures->nFetureCount >= RCD_CMP_FETURE_TYPE_MAX_COUNT)
	{
		return;
	}

	PRCD_CMP_FETURE pFeture = &pFetures->fetures[pFetures->nFetureCount];
	pFeture->fMaxValueDelta = fMax;
	pFeture->nBeginPos = nBeginPos;
	pFeture->nEndPos = nEndPos;
	pFeture->nMaxPos = nMaxPos;
	pFeture->fBeginDelta = fBegin;
	pFeture->fEndDelta = fEnd;
	pFetures->nFetureCount++;

	pFeture->fBegin = pfBufValue[nBeginPos];
	pFeture->fMaxValue = pfBufValue[nMaxPos];
	pFeture->fEnd = pfBufValue[nEndPos];
}
// 
// float CRecordCmpBuffer::CalMaxValue(CMemBuffer_Float *pBuff)
// {
// 	float *pfBuf = pBuff->GetBuffer();
// 	float *pfEnd = pfBuf + pBuff->GetBufferLength();
// 	float fMax = 0;
// 	float fCurr = 0;
// 
// 	while (pfBuf < pfEnd)
// 	{
// 		fCurr = abs(*pfBuf);
// 
// 		if (fMax < fCurr)
// 		{
// 			fMax = fCurr;
// 		}
// 	}
// 
// 	return fMax;
// }
// 
// void CRecordCmpBuffer::RemoveLittleFetures(PRCD_CMP_FETURES pFetures)
// {
// 	
// }
// 
// void CRecordCmpBuffer::RcdCmp()
// {
// 
// }
BOOL CRecordCmpBuffer::GetAlignPosVariable2(long &nAlignPos)
{
	if (m_pRcdCmpFeture1 == NULL || m_pRcdCmpFeture2 == NULL)
	{
		return FALSE;
	}

	if (nAlignPos > m_pRcdCmpFeture2->nEndPos)
	{
		nAlignPos = m_pRcdCmpFeture2->nEndPos;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
