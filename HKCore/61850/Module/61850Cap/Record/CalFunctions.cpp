#include "stdafx.h"
#include "CalFunctions.h"
#include <math.h>

//SingleVariable
void RT_CalFrequency(PRTCALFUNCPARA pCalFuncPara)
{
//lblCalAgain:
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	pRtChAttrVal->dFrequency = 50;

	DWORD *pdwFreqZeroPosition    = pCalFuncPara->pdwFreqZeroPosition;     //本通道的过零点位置
	UINT  *pnFreqZeroPosCount     = pCalFuncPara->pnFreqZeroPosCount;
	DWORD *pdwRefFreqZeroPosition = pCalFuncPara->pdwRefFreqZeroPosition;  //参考通道的过零点位置
	UINT  *pnRefFreqZeroPosCount  = pCalFuncPara->pnRefFreqZeroPosCount;

	long *pnBuffer  = pCalFuncPara->pnBuffer;       //缓冲区
	float          *pfBuffer  = pCalFuncPara->pfBuffer;
	
	if (pnBuffer == NULL)
	{
		return;
	}
	
	long nBuffer1Pos = pCalFuncPara->nBuffer1Pos;
	long nBuffer2Pos = pCalFuncPara->nBuffer2Pos;
	long nBuffer1Len = pCalFuncPara->nBuffer1Len;
	long nBuffer2Len = pCalFuncPara->nBuffer2Len;
	long nChIndex = pCalFuncPara->nChIndex;
	long nFreqZeroPosCount = 0;
	double dFrequency = 0;
	
	__int64 vSum = 0;
	UINT nIndex = 0;
	UINT nEndPos = 0;
	short nAverage = 0;
	long nCount = 0;

	nEndPos = nBuffer1Pos;
	long *pBegin = NULL;
	long *pEnd = NULL;
	long *pTemp = NULL;
	DWORD *pLastZeroPos = NULL;

	//求取过零点位置
	pBegin = pnBuffer + nBuffer1Pos;
	pTemp = pBegin;
	pEnd = pBegin + nBuffer1Len -1 ;//必须是-1，不然会内存越界
	*pnFreqZeroPosCount = 0;
	long nJumpOffset = 0;
	
	if (nBuffer1Len > 0)
	{
		while (pTemp < pEnd)//=
		{
			if ( ((short)(*pTemp) <= nAverage) && ((short)(*(pTemp+1)) > nAverage))
			{
				CRtCalFilterData oFilter(pCalFuncPara, pTemp);
				
				if (oFilter.IsZeroPos())
				{
					*pnFreqZeroPosCount = *pnFreqZeroPosCount + 1;
					
					if (*pnFreqZeroPosCount >= MAX_FREQ_ZERO_POS_COUNT)
					{
						goto ErrorCalFreq;
					}
					
					*pdwFreqZeroPosition = nBuffer1Pos + pTemp - pBegin;
					pdwFreqZeroPosition++;

					//如果是一个过零点，则跳过过零点后面的用于判断的数据长度
					pTemp += RT_FILTER_DATA_LEN_NEXT;

					if (pTemp > pEnd)
					{
						nJumpOffset = pTemp - pEnd;
						break;
					}

					continue;
				}
			}
			
			pTemp++;
		}
	}
	
	if (nBuffer2Pos >= 0 && nBuffer2Len > 0)
	{
		pBegin = pnBuffer + nBuffer2Pos;
		//fdp add 2009.11.13,判断最后一个点是否满足情况

		if (nBuffer1Len > 0)
		{
			if (nJumpOffset == 0)
			{//不需要移位
				if ( ( (short)(*pTemp) <= nAverage ) && ( (short)(*pBegin)  > nAverage) )
				{
					CRtCalFilterData oFilter(pCalFuncPara, pTemp);
					
					if (oFilter.IsZeroPos())
					{
						*pnFreqZeroPosCount = *pnFreqZeroPosCount + 1;
						
						if (*pnFreqZeroPosCount >= MAX_FREQ_ZERO_POS_COUNT)
						{
							goto ErrorCalFreq;
						}
						
						*pdwFreqZeroPosition = pTemp - pBegin;
						pdwFreqZeroPosition++;
					}
				}
			}
			else
			{
				nJumpOffset--;
			}
		}

		//进行移位
		pTemp = pBegin + nJumpOffset;
		pEnd = pBegin + nBuffer2Len;
		
		while (pTemp < pEnd)//fdp add 2009.11.13
		{
			if ( ((short)(*pTemp) <= nAverage) && ((short)(*(pTemp+1)) > nAverage) )//if
			{
				CRtCalFilterData oFilter(pCalFuncPara, pTemp);

				if (oFilter.IsZeroPos())
				{
					*pnFreqZeroPosCount = *pnFreqZeroPosCount + 1;
					
					if (*pnFreqZeroPosCount >= MAX_FREQ_ZERO_POS_COUNT)
					{
						goto ErrorCalFreq;
					}
					
					*pdwFreqZeroPosition = nBuffer2Pos + pTemp - pBegin;
					pdwFreqZeroPosition++;
					
					//如果是一个过零点，则跳过过零点后面的用于判断的数据长度
					pTemp += RT_FILTER_DATA_LEN_NEXT;
					
					if (pTemp > pEnd)
					{
						nJumpOffset = pTemp - pEnd;
						break;
					}
					
					continue;
				}
			}
			
			pTemp++;
		}
	}
	
	nFreqZeroPosCount = *pnFreqZeroPosCount;

	if (nFreqZeroPosCount <= 1)
	{
		goto ErrorCalFreq;
	}
	
	//////////////////////////////计算频率前，先进性过零点过滤与合并，fdp add 2010.4.15
	pdwFreqZeroPosition    = pCalFuncPara->pdwFreqZeroPosition;     //本通道的过零点位置

	//////////////////////////////////////////////////////////////////////////
	//计算频率
	//最后一个过零点的位置
	pLastZeroPos = pCalFuncPara->pdwFreqZeroPosition + *pnFreqZeroPosCount - 1;
	pdwFreqZeroPosition = pCalFuncPara->pdwFreqZeroPosition;
	
	if (*pLastZeroPos > *pdwFreqZeroPosition)
	{
		nCount = *pLastZeroPos;
		nCount -= *pdwFreqZeroPosition;
	}
	else
	{
		//到缓冲区末尾的长度
		nCount = pCalFuncPara->nBufferLength - (long)(*pdwFreqZeroPosition);
		nCount += *pLastZeroPos;
	}

	dFrequency = (nFreqZeroPosCount-1);
	dFrequency *= g_dwSampleRate;
	dFrequency /= nCount;
	pRtChAttrVal->dFrequency = dFrequency;

#ifdef _DEBUG
	if (pRtChAttrVal->dFrequency < 45)
	{
		int i = 0;
		//goto lblCalAgain;
	}

	if (pRtChAttrVal->dFrequency > 55)
	{
		int i = 0;
	}

#endif

#ifdef _USE_DEBUG_SPY_

	if (pRtChAttrVal->dFrequency < 40)
	{
		CSTRECORDBaseApp *theApp = (CSTRECORDBaseApp *)AfxGetApp();
		CDebugDataCal *pDebugData = theApp->CreateCalDebugData(DEBUG_SPY_CALVALUE, 3);
		
		pDebugData->m_nRefBufLen = pCalFuncPara->nBufferLength;
		pDebugData->m_nRefDataLen = pCalFuncPara->nDataLength;
		pDebugData->m_nRefFillBeginPos = (long)(pRtChAttrVal->dFrequency*1000);
		pDebugData->m_nBufPos1 = nBuffer1Pos;
		pDebugData->m_nBufLen1 = nBuffer1Len;
		pDebugData->m_nBufPos2 = nBuffer2Pos;
		pDebugData->m_nBufLen2 = nBuffer2Len;

		pDebugData->m_nZeroCount = *pnFreqZeroPosCount;
		pDebugData->m_nFirst = *pdwFreqZeroPosition;
		pDebugData->m_nLast = *pLastZeroPos;
		pDebugData->GetEndTime();
		pDebugData->m_nPos = 9;
		theApp->AddDebugData(pDebugData);
	}

#endif

	return;
ErrorCalFreq:
	//fdp add 2009.12.27
	double dCeofValue = pCalFuncPara->dCeofValue;
	double dZeroValue = pCalFuncPara->dZeroValue;
	pRtChAttrVal->dFrequency = 0;
// 	pRtChAttrVal->dAverageValue = nAverage * dCeofValue - dZeroValue;
// 	pRtChAttrVal->dFundPhase = 0;
// 	pRtChAttrVal->dFundValue = 0;
}
// 
// void Rt_FilterData(PRTCALFUNCPARA pCalFuncPara, long *pFilterBuffer, long *pPos, long nPos)
// {
// 	long nOffset = RT_FILTER_BUUFFER_LEN / 2;
// 	long nDataLength = pCalFuncPara->nDataLength;
// 	long nBufferLength = pCalFuncPara->nBufferLength;
// 
// 	if (nDataLength == nBufferLength)
// 	{
// 		if (nPos )
// 	}
// 	else
// 	{
// 
// 	}
// }

void RT_CalEffecValue(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	
	DWORD *pdwFreqZeroPosition    = pCalFuncPara->pdwFreqZeroPosition;     //本通道的过零点位置
	UINT  *pnFreqZeroPosCount     = pCalFuncPara->pnFreqZeroPosCount;
	UINT  *pnRefFreqZeroPosCount  = pCalFuncPara->pnRefFreqZeroPosCount;
	DWORD *pLastZeroPos = pdwFreqZeroPosition  + *pnFreqZeroPosCount - 1;
	DWORD *pdwRefFreqZeroPosition = pCalFuncPara->pdwRefFreqZeroPosition;  //参考通道的过零点位置
	long *pnBuffer  = pCalFuncPara->pnBuffer;       //缓冲区
	float          *pfBuffer  = pCalFuncPara->pfBuffer;

// 	if (*pnFreqZeroPosCount >= MAX_FREQ_ZERO_POS_COUNT) //如果过零点数超过限定值，视为直流
// 	{
// 		pRtChAttrVal->dEffecValue = pRtChAttrVal->dAverageValue ;//直流
// 		pRtChAttrVal->dEffecPhase = 0;//直流
// 		return ;
// 	}
	
	
	long nBuffer1Pos = pCalFuncPara->nBuffer1Pos;
	long nBuffer2Pos = pCalFuncPara->nBuffer2Pos;
	long nBuffer1Len = pCalFuncPara->nBuffer1Len;
	long nBuffer2Len = pCalFuncPara->nBuffer2Len;
	long nBufferLength = pCalFuncPara->nBufferLength;
	long nChIndex = pCalFuncPara->nChIndex;
	__int64 vSum = 0;
	UINT nIndex = 0;
	long nDataLength = pCalFuncPara->nDataLength;

	long nLength = nBuffer1Len;
	
	if (nBuffer2Pos>= 0 && nBuffer2Len > 0)
	{
		nLength += nBuffer2Len;
	}

//	if (nBuffer1Len <= 0)
//	{
//		return;	
//	}
	
	if (pnBuffer == NULL)
	{
		float *pBegin = NULL;
		float *pEnd = NULL;
		float *pTemp = NULL;
		double dSum = 0;
		
		pTemp = pfBuffer + nBuffer1Pos;
		pEnd = pfBuffer + nBuffer1Pos + nBuffer1Len;
		vSum = 0;
		
		while (pTemp < pEnd)//=
		{
			dSum += (*pTemp) * (*pTemp);
			pTemp++;
		}
		
		if (nBuffer2Len > 0 && nBuffer2Pos >= 0)
		{
			pTemp = pfBuffer + nBuffer2Pos;
			pEnd = pTemp + nBuffer2Len;
			
			while (pTemp < pEnd)
			{
				dSum += (*pTemp) * (*pTemp);
				pTemp++;
			}
		}
		
		pRtChAttrVal->dEffecValue = sqrt(dSum/(nLength -1 ));
		return ;
	}
	
	
	long *pBegin = NULL;
	long *pEnd = NULL;
	long *pTemp = NULL;
	
	////////////////////////////计算有效值 使用参考通道的起点和终点计算
	pTemp = pnBuffer + nBuffer1Pos;
	pEnd = pnBuffer + nBuffer1Pos + nBuffer1Len;
	vSum = 0;

	while (pTemp < pEnd)//=
	{
		vSum += ((short)*pTemp) * ((short)*pTemp);
		pTemp++;
	}

	if (nBuffer2Len > 0 && nBuffer2Pos >= 0)
	{
		pTemp = pnBuffer + nBuffer2Pos;
		pEnd = pTemp + nBuffer2Len;

		while (pTemp < pEnd)
		{
			vSum += ((short)*pTemp) * ((short)*pTemp);
			pTemp++;
		}
	}


	double dCeofValue = pCalFuncPara->dCeofValue;
	double dZeroValue = pCalFuncPara->dZeroValue;


	pRtChAttrVal->dEffecValue = sqrt((double)vSum/(nLength -1 )) * dCeofValue;

	{
		pRtChAttrVal->dEffecValue -= dZeroValue;
	}

	//计算相位差
	if (*pnRefFreqZeroPosCount > 0 && *pnFreqZeroPosCount > 0)
	{
		if (pdwRefFreqZeroPosition == pdwFreqZeroPosition)//参考相
		{
			pRtChAttrVal->dEffecPhase = 0;
		}
		else
		{
			//判断是否过零点过多,fdp add 2010.6.13
			if (*pnRefFreqZeroPosCount > MAX_FREQ_ZERO_POS_COUNT && *pnFreqZeroPosCount > MAX_FREQ_ZERO_POS_COUNT)
			{
				pRtChAttrVal->dEffecPhase = 0;
				return;
			}

			double dPhasic = 0;
			DWORD* pCurrentChanPos = pdwFreqZeroPosition;
			BOOL bFind = FALSE;
			long nPh = 0;

			//if (pApp->IsAdStart() && !pApp->IsInRecordHoldState())
			{	
				while (pCurrentChanPos < pLastZeroPos)
				{
					if (long(*pCurrentChanPos) >= (long)(*pdwRefFreqZeroPosition))
					{
						if ((long)(*pCurrentChanPos)>=nBuffer1Pos && (long)(*pCurrentChanPos)<(nBuffer1Pos + nBuffer1Len)) 
						{
							break;
						}
					}
					else
					{
						if ((long)(*pCurrentChanPos)>=nBuffer2Pos && (long)(*pCurrentChanPos)<(nBuffer2Pos + nBuffer2Len)) 
						{
							break;
						}
					}
					
					pCurrentChanPos++;
				}

				if (*pCurrentChanPos >= *pdwFreqZeroPosition && nBuffer1Pos >= (long)(*pdwRefFreqZeroPosition)) //都不循环
				{
					nPh = (long)(*pCurrentChanPos) - nBuffer1Pos;
				}
				else if (*pCurrentChanPos >= *pdwFreqZeroPosition && nBuffer1Pos < (long)(*pdwRefFreqZeroPosition)) //参考通道循环，本通道不循环
				{
					nPh = (long)(*pCurrentChanPos) - nBufferLength - nBuffer1Pos;//nDataLength
				}
				else if (*pCurrentChanPos < *pdwFreqZeroPosition && nBuffer1Pos >= (long)(*pdwRefFreqZeroPosition)) //本通道循环，参考通道不循环
				{
					nPh = (long)(*pCurrentChanPos) + nBufferLength - nBuffer1Pos;//nDataLength
				}
				else //都循环到缓存
				{
					nPh = (long)(*pCurrentChanPos) - nBuffer1Pos;
				}
			} 
// 			else
// 			{
// 				if ((long)(*pdwRefFreqZeroPosition)>=nBuffer1Pos && (long)(*pdwRefFreqZeroPosition)<(nBuffer1Pos + nBuffer1Len))
// 				{//参考通道在旧的一侧
// 					if ((long)(*pCurrentChanPos)>=nBuffer1Pos && (long)(*pCurrentChanPos)<(nBuffer1Pos + nBuffer1Len)) 
// 					{//都在一侧
// 						nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition);
// 					}
// 					else
// 					{//本通道在新的一侧
// 						nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition) + nBufferLength;
// 					}
// 				} 
// 				else
// 				{//参考通道的在新的一侧
// 					if ((long)(*pCurrentChanPos)>=nBuffer1Pos && (long)(*pCurrentChanPos)<(nBuffer1Pos + nBuffer1Len)) 
// 					{//本通道在旧的一侧
// 						nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition) - nDataLength;
// 					}
// 					else
// 					{//本通道在新的一侧
// 						nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition);
// 					}
// 				}
// 			}
			

			//nPh = 0 - nPh;//因为是反向放大器，相角相差180
#ifdef _USE_RECORD_BUFFER_TO_CAL
			dPhasic = (*pCalFuncPara->pRefFrequency + pRtChAttrVal->dFrequency) * nPh * 360 / ( 2 * g_dwSampleRate) ;
#else
			dPhasic = (*pCalFuncPara->pRefFrequency + pRtChAttrVal->dFrequency) * nPh * 360 / ( 2 * STRECORD_SAMPLE_RATE) ;
#endif
			
//			dPhasic += 180; //因为是反向放大器，相角相差180
			long nCircles = (long)(dPhasic / 360);
			dPhasic -= nCircles * 360;

			if (dPhasic >= 180)
			{
				pRtChAttrVal->dEffecPhase = dPhasic - 360;
			}
			else if (dPhasic <= -180)
			{
				pRtChAttrVal->dEffecPhase = dPhasic + 360;
			}
			else
			{
				pRtChAttrVal->dEffecPhase = dPhasic;
			}
		}
	}
	else
	{
		pRtChAttrVal->dEffecPhase = 0;
	}
}

void RT_CalFundValue(PRTCALFUNCPARA pCalFuncPara)
{	
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(0,pCalFuncPara, pRtChAttrVal->dFundValue ,pRtChAttrVal->dFundPhase);	

// 	if (pRtChAttrVal->dFundValue < 1)
// 	{
// 		int i = 0;
// 	}
// 
// 	if (pRtChAttrVal->dFundValue > 70)
// 	{
// 		int i = 0;
// 	}
	
}

void RT_CalFundPhase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalPeakValue(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	
	double dCeofValue = pCalFuncPara->dCeofValue ;
	double dZeroValue = pCalFuncPara->dZeroValue ;
	long *pnBuffer  = pCalFuncPara->pnBuffer;       //缓冲区
	float          *pfBuffer  = pCalFuncPara->pfBuffer;
	
	if (pnBuffer == NULL)
	{
		return;
	}
	
	long nBuffer1Pos = pCalFuncPara->nBuffer1Pos;
	long nBuffer2Pos = pCalFuncPara->nBuffer2Pos;
	long nBuffer1Len = pCalFuncPara->nBuffer1Len;
	long nBuffer2Len = pCalFuncPara->nBuffer2Len;
	long nChIndex = pCalFuncPara->nChIndex;
	short nMaxValue = -32768;
	UINT nIndex = 0;
	UINT nEndPos = 0;
	double dAverage = 0;
	long nCount = 0;
	
	nEndPos = nBuffer1Pos;
	long *pBegin = NULL;
	long *pEnd = NULL;
	long *pTemp = NULL;
	DWORD *pLastZeroPos = NULL;
	
	//求取平均值
	pBegin = pnBuffer + nBuffer1Pos;
	pTemp = pBegin;
	pEnd = pBegin + nBuffer1Len;
	
	if (nBuffer1Len > 0)
	{
		while (pTemp < pEnd)//= 这里不能有 = 会内存越界
		{
			short nValue = (short)(*pTemp);		
			nMaxValue = max(nMaxValue, nValue);
			pTemp++;
		}
	}
	
	if (nBuffer2Len > 0 && nBuffer2Pos >= 0) //这里要有 = 因为nBuffer2Len 在获得时-1了,现在不需要=了，因为-1没有了
	{
		pBegin = pnBuffer + nBuffer2Pos;
		pTemp = pBegin;
		pEnd = pBegin + nBuffer2Len;
		
		while (pTemp < pEnd)// =
		{
			short nValue = (short)(*pTemp);		
			nMaxValue = max(nMaxValue, nValue);
			pTemp++;
		}
	}
	
	pRtChAttrVal->dPeakValue = (dCeofValue * nMaxValue - dZeroValue);
}

void RT_CalVellayValue(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	
	double dCeofValue = pCalFuncPara->dCeofValue ;
	double dZeroValue = pCalFuncPara->dZeroValue ;
	long *pnBuffer  = pCalFuncPara->pnBuffer;       //缓冲区
	float          *pfBuffer  = pCalFuncPara->pfBuffer;
	
	if (pnBuffer == NULL)
	{
		return;
	}
	
	long nBuffer1Pos = pCalFuncPara->nBuffer1Pos;
	long nBuffer2Pos = pCalFuncPara->nBuffer2Pos;
	long nBuffer1Len = pCalFuncPara->nBuffer1Len;
	long nBuffer2Len = pCalFuncPara->nBuffer2Len;
	long nChIndex = pCalFuncPara->nChIndex;
	short nMinValue = 32767;
	UINT nIndex = 0;
	UINT nEndPos = 0;
	double dAverage = 0;
	long nCount = 0;
	
	nEndPos = nBuffer1Pos;
	long *pBegin = NULL;
	long *pEnd = NULL;
	long *pTemp = NULL;
	DWORD *pLastZeroPos = NULL;
	
	//求取平均值
	pBegin = pnBuffer + nBuffer1Pos;
	pTemp = pBegin;
	pEnd = pBegin + nBuffer1Len;
	
	if (nBuffer1Len > 0)
	{
		while (pTemp < pEnd)//= 这里不能有 = 会内存越界
		{
			short nValue = (short)(*pTemp);		
			nMinValue = min(nMinValue, nValue);
			pTemp++;
		}
	}
	
	if (nBuffer2Len > 0 && nBuffer2Pos >= 0) //这里要有 = 因为nBuffer2Len 在获得时-1了,现在不需要=了，因为-1没有了
	{
		pBegin = pnBuffer + nBuffer2Pos;
		pTemp = pBegin;
		pEnd = pBegin + nBuffer2Len;
		
		while (pTemp < pEnd)// =
		{
			short nValue = (short)(*pTemp);		
			nMinValue = min(nMinValue, nValue);
			pTemp++;
		}
	}
	
	pRtChAttrVal->dVellayValue =  dCeofValue * nMinValue - dZeroValue;
}

void RT_CalInstValue(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	
	double dCeofValue = pCalFuncPara->dCeofValue;
	double dZeroValue = pCalFuncPara->dZeroValue;
	long *pnBuffer  = pCalFuncPara->pnBuffer;       //缓冲区
	float          *pfBuffer  = pCalFuncPara->pfBuffer;
	
	if (pnBuffer == NULL)
	{
		return;
	}
	
	long nBuffer1Pos = pCalFuncPara->nBuffer1Pos;

	double dValue = (short)(*(pnBuffer + nBuffer1Pos));
	dValue *= dCeofValue;
	dValue -= dZeroValue;

	pRtChAttrVal->dInstValue =  dValue;
}

void RT_CalAverageValue(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	DWORD *pdwFreqZeroPosition		 = pCalFuncPara->pdwFreqZeroPosition;     //本通道的过零点位置
	UINT  *pnFreqZeroPosCount		 = pCalFuncPara->pnFreqZeroPosCount;
	DWORD *pdwRefFreqZeroPosition	 = pCalFuncPara->pdwRefFreqZeroPosition;  //参考通道的过零点位置
	UINT  *pnRefFreqZeroPosCount	 = pCalFuncPara->pnRefFreqZeroPosCount;
	
	double dCeofValue = pCalFuncPara->dCeofValue ;
	double dZeroValue = pCalFuncPara->dZeroValue ;
	long *pnBuffer  = pCalFuncPara->pnBuffer;       //缓冲区
	float          *pfBuffer  = pCalFuncPara->pfBuffer;
	
	if (pnBuffer == NULL)
	{
		return;
	}
	
	long nBuffer1Pos = pCalFuncPara->nBuffer1Pos;
	long nBuffer2Pos = pCalFuncPara->nBuffer2Pos;
	long nBuffer1Len = pCalFuncPara->nBuffer1Len;
	long nBuffer2Len = pCalFuncPara->nBuffer2Len;
	long nChIndex = pCalFuncPara->nChIndex;
	__int64 vSum = 0;
	UINT nIndex = 0;
	UINT nEndPos = 0;
	double dAverage = 0;
	long nCount = 0;
	
	nEndPos = nBuffer1Pos;
	long *pBegin = NULL;
	long *pEnd = NULL;
	long *pTemp = NULL;
	DWORD *pLastZeroPos = NULL;
	
	//求取平均值
	pBegin = pnBuffer + nBuffer1Pos;
	pTemp = pBegin;
	pEnd = pBegin + nBuffer1Len;
	
	if (nBuffer1Len > 0)
	{
		while (pTemp < pEnd)//= 这里不能有 = 会内存越界
		{
			vSum += (short)(*pTemp);
			pTemp++;
		}
	}
	
	if (nBuffer2Len > 0 && nBuffer2Pos >= 0) //这里要有 = 因为nBuffer2Len 在获得时-1了,现在不需要=了，因为-1没有了
	{
		pBegin = pnBuffer + nBuffer2Pos;
		pTemp = pBegin;
		pEnd = pBegin + nBuffer2Len;
		
		while (pTemp < pEnd)// =
		{
			vSum += (short)(*pTemp);
			pTemp++;
		}
	}
	
	if (nBuffer2Len > 0  && nBuffer2Pos >= 0)
	{
		pRtChAttrVal->dAverageValue = dCeofValue * vSum / (nBuffer1Len + nBuffer2Len + 1) - dZeroValue;
	}
	else
	{
		pRtChAttrVal->dAverageValue = dCeofValue * vSum / nBuffer1Len - dZeroValue;
	}

	if (pRtChAttrVal->dAverageValue < 0.00001)
	{
// #ifdef _debug_write_spy_file
// 	CString strMsg;
// 	strMsg.Format("nChIndex=%d Buffer(%d, %d,%d,%d)  Coef=%f  Zero=%f\r\n", pCalFuncPara->nChIndex,
// 		nBuffer1Pos, nBuffer1Len, nBuffer2Pos, nBuffer2Len, dCeofValue, dZeroValue);
// 	_debug_write_file(strMsg);
// #endif
	}
	
//	pRtChAttrVal->dAverageValue = -pRtChAttrVal->dAverageValue;
}

void RT_CalHarm02Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(1,pCalFuncPara, pRtChAttrVal->dHarmValue[0] ,pRtChAttrVal->dHarmPhase[0]);	
}

void RT_CalHarm03Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(2,pCalFuncPara, pRtChAttrVal->dHarmValue[1] ,pRtChAttrVal->dHarmPhase[1]);
}

void RT_CalHarm04Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(3,pCalFuncPara, pRtChAttrVal->dHarmValue[2] ,pRtChAttrVal->dHarmPhase[2]);
}

void RT_CalHarm05Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(4,pCalFuncPara, pRtChAttrVal->dHarmValue[3] ,pRtChAttrVal->dHarmPhase[3]);
}

void RT_CalHarm06Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(5,pCalFuncPara, pRtChAttrVal->dHarmValue[4] ,pRtChAttrVal->dHarmPhase[4]);
}

void RT_CalHarm07Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(6,pCalFuncPara, pRtChAttrVal->dHarmValue[5] ,pRtChAttrVal->dHarmPhase[5]);
}

void RT_CalHarm08Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(7,pCalFuncPara, pRtChAttrVal->dHarmValue[6] ,pRtChAttrVal->dHarmPhase[6]);
}

void RT_CalHarm09Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(8,pCalFuncPara, pRtChAttrVal->dHarmValue[7] ,pRtChAttrVal->dHarmPhase[7]);
}

void RT_CalHarm10Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(9,pCalFuncPara, pRtChAttrVal->dHarmValue[8] ,pRtChAttrVal->dHarmPhase[8]);
}

void RT_CalHarm11Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(10,pCalFuncPara, pRtChAttrVal->dHarmValue[9] ,pRtChAttrVal->dHarmPhase[9]);
}

void RT_CalHarm12Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(11,pCalFuncPara, pRtChAttrVal->dHarmValue[10] ,pRtChAttrVal->dHarmPhase[10]);
}

void RT_CalHarm13Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(12,pCalFuncPara, pRtChAttrVal->dHarmValue[11] ,pRtChAttrVal->dHarmPhase[11]);
}

void RT_CalHarm14Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(13,pCalFuncPara, pRtChAttrVal->dHarmValue[12] ,pRtChAttrVal->dHarmPhase[12]);
}

void RT_CalHarm15Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(14,pCalFuncPara, pRtChAttrVal->dHarmValue[13] ,pRtChAttrVal->dHarmPhase[13]);
}

void RT_CalHarm16Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(15,pCalFuncPara, pRtChAttrVal->dHarmValue[14] ,pRtChAttrVal->dHarmPhase[14]);
}

void RT_CalHarm17Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(16,pCalFuncPara, pRtChAttrVal->dHarmValue[15] ,pRtChAttrVal->dHarmPhase[15]);
}

void RT_CalHarm18Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(17,pCalFuncPara, pRtChAttrVal->dHarmValue[16] ,pRtChAttrVal->dHarmPhase[16]);
}

void RT_CalHarm19Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(18,pCalFuncPara, pRtChAttrVal->dHarmValue[17] ,pRtChAttrVal->dHarmPhase[17]);
}

void RT_CalHarm20Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(19,pCalFuncPara, pRtChAttrVal->dHarmValue[18] ,pRtChAttrVal->dHarmPhase[18]);
}

void RT_CalHarm21Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(20,pCalFuncPara, pRtChAttrVal->dHarmValue[19] ,pRtChAttrVal->dHarmPhase[19]);
}

void RT_CalHarm22Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(21,pCalFuncPara, pRtChAttrVal->dHarmValue[20] ,pRtChAttrVal->dHarmPhase[20]);
}

void RT_CalHarm23Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(22,pCalFuncPara, pRtChAttrVal->dHarmValue[21] ,pRtChAttrVal->dHarmPhase[21]);
}

void RT_CalHarm24Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(23,pCalFuncPara, pRtChAttrVal->dHarmValue[22] ,pRtChAttrVal->dHarmPhase[22]);
}

void RT_CalHarm25Value(PRTCALFUNCPARA pCalFuncPara)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(24,pCalFuncPara, pRtChAttrVal->dHarmValue[23] ,pRtChAttrVal->dHarmPhase[23]);
}

void RT_CalHarm02Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm03Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm04Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm05Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm06Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm07Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm08Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm09Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm10Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm11Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm12Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm13Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm14Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm15Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm16Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm17Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm18Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm19Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm20Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm21Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm22Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm23Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm24Phase(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalHarm25Phase(PRTCALFUNCPARA pCalFuncPara)
{

}


//MultiVariable
void RT_CalImpedance(PRTCALFUNCPARA pCalFuncPara)
{
	double dValue1 = pCalFuncPara->pRtChanAttr[0]->dEffecValue;
	double dValue2 = pCalFuncPara->pRtChanAttr[1]->dEffecValue;

	pCalFuncPara->pRtChAttrVal->dImpedance = dValue1 / dValue2;
}

void RT_CalPositiveSequence(PRTCALFUNCPARA pCalFuncPara)
{
	double dReal1,dReal2,dReal3,dIm1,dIm2,dIm3,dReal,dIm;
	GetRealandImValue(pCalFuncPara,dReal1,dReal2,dReal3,dIm1,dIm2,dIm3);
	
	dReal = dReal1 - 0.5 * (dReal2 + dReal3) - 0.8660254 * (dIm2 -dIm3);
	dIm   = dIm1   - 0.5 * (dIm2   + dIm3  ) + 0.8660254 * (dReal2 - dReal3);
	pCalFuncPara->pRtChAttrVal->dPositiveSequence = (sqrt(dReal * dReal + dIm * dIm)) / 3;
	pCalFuncPara->pRtChAttrVal->dPositiveSequencePhase = atan2(dReal, dIm) * 180 / PI;
}

void RT_CalNegativeSequence(PRTCALFUNCPARA pCalFuncPara)
{
	double dReal1,dReal2,dReal3,dIm1,dIm2,dIm3,dReal,dIm;
	GetRealandImValue(pCalFuncPara,dReal1,dReal2,dReal3,dIm1,dIm2,dIm3);
	
	dReal = dReal1 - 0.5 * (dReal2 + dReal3) + 0.8660254 * (dIm2 -dIm3);
	dIm   = dIm1   - 0.5 * (dIm2   + dIm3  ) - 0.8660254 * (dReal2 - dReal3);
	pCalFuncPara->pRtChAttrVal->dNegativeSequence = (sqrt(dReal * dReal + dIm * dIm)) / 3;
	pCalFuncPara->pRtChAttrVal->dNegativeSequencePhase = atan2(dReal, dIm) * 180 / PI;
}

void RT_CalZeroSequence(PRTCALFUNCPARA pCalFuncPara)
{
	double dReal1,dReal2,dReal3,dIm1,dIm2,dIm3,dReal,dIm;
	GetRealandImValue(pCalFuncPara,dReal1,dReal2,dReal3,dIm1,dIm2,dIm3);

	dReal = dReal1 + dReal2 + dReal3;
	dIm   = dIm1   + dIm2	+ dIm3;
	pCalFuncPara->pRtChAttrVal->dZeroSequence = (sqrt(dReal * dReal + dIm * dIm)) / 3;
	pCalFuncPara->pRtChAttrVal->dZeroSequencePhase = atan2(dReal, dIm) * 180 / PI;

}

//计算都是使用的基波的有效值和相位
void RT_CalActivePower(PRTCALFUNCPARA pCalFuncPara)
{
	double dFundValue1  = pCalFuncPara->pRtChanAttr[0]->dFundValue;
	double dFundValue2  = pCalFuncPara->pRtChanAttr[1]->dFundValue;
	double dFundPhasic1 = pCalFuncPara->pRtChanAttr[0]->dFundPhase ;
	double dFundPhasic2 = pCalFuncPara->pRtChanAttr[1]->dFundPhase ;
	pCalFuncPara->pRtChAttrVal->dActivePower = dFundValue1 * dFundValue2 * cos((dFundPhasic1 - dFundPhasic2) * PI_RADIAN_PER_DEG);
}

void RT_CalReactivePower(PRTCALFUNCPARA pCalFuncPara)
{
	double dFundValue1  = pCalFuncPara->pRtChanAttr[0]->dFundValue;
	double dFundValue2  = pCalFuncPara->pRtChanAttr[1]->dFundValue;
	double dFundPhasic1 = pCalFuncPara->pRtChanAttr[0]->dFundPhase;
	double dFundPhasic2 = pCalFuncPara->pRtChanAttr[1]->dFundPhase;
	pCalFuncPara->pRtChAttrVal->dReactivePower = dFundValue1 * dFundValue2 * sin((dFundPhasic1 - dFundPhasic2) * PI_RADIAN_PER_DEG);
}

void RT_CalApparentPower(PRTCALFUNCPARA pCalFuncPara)
{
	double dValue1 = pCalFuncPara->pRtChanAttr[0]->dFundValue;
	double dValue2 = pCalFuncPara->pRtChanAttr[1]->dFundValue;
	pCalFuncPara->pRtChAttrVal->dApparentPower = dValue1 * dValue2;
}

void RT_CalReserve01Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalReserve02Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalReserve03Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalReserve04Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalReserve05Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalReserve06Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalReserve07Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalReserve08Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalReserve09Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void RT_CalReserve10Value(PRTCALFUNCPARA pCalFuncPara)
{

}

void CalHar(long nHar,PRTCALFUNCPARA pCalFuncPara, double& dHarValue ,double& dHarPhasic)
{
#ifdef _USE_SPYDLL
	CSTRECORDBaseApp *pApp = (CSTRECORDBaseApp *)AfxGetApp();
	CString str(">>CalHar");
	pApp->m_pGetInfor(str);
#endif
	
	CDFT* pDft = CDFT::CreateDft();
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	short* pnBuffer  = (short*)pCalFuncPara->pnBuffer;       //缓冲区
	float* pfBuffer  = pCalFuncPara->pfBuffer;
	long nBuffer1Pos = pCalFuncPara->nDftBuffer1Pos;
	long nBuffer2Pos = pCalFuncPara->nDftBuffer2Pos;
	long nBuffer1Len = pCalFuncPara->nDftBuffer1Len;
	long nBuffer2Len = pCalFuncPara->nDftBuffer2Len;
	long nEnd1 = nBuffer1Pos + nBuffer1Len;
	double dRealValue,dImValue;
	long nChIndex  = pCalFuncPara->nChIndex;
	long nDataLen = nBuffer1Len;

	if (pnBuffer == NULL)
	{
		if (nBuffer2Len > 0  && nBuffer2Pos >= 0) 
		{
			//////////fdp add 2010.4.15
			nDataLen = nBuffer1Len + nBuffer2Len;
// 			pDft->SetCurrentDataLength(nDataLen);
// 			pDft->DFTCalByMap(TRUE,pfBuffer,nBuffer1Pos,nEnd1,dRealValue,dImValue,nHar);
// 			long nEnd2 = nBuffer2Pos + nBuffer2Len;
// 			pDft->DFTCalByMap(FALSE,pfBuffer,nBuffer2Pos,nEnd2,dRealValue,dImValue,nHar);		
		}
		else
		{
// 			pDft->SetCurrentDataLength(nDataLen);
// 			pDft->DFTCalByMap(TRUE,pfBuffer,nBuffer1Pos,nEnd1,dRealValue,dImValue,nHar);
		}

		pDft->SetCurrentDataLength(nDataLen);
		pDft->DFTCalByMap(pfBuffer,nBuffer1Pos,nBuffer1Len,nBuffer2Pos,nBuffer2Len,dRealValue,dImValue,nHar);
		double dCeofValue = pCalFuncPara->dCeofValue;
		double dZeroValue = pCalFuncPara->dZeroValue;
		
		double dTemp = 2.0 / nDataLen;
		dRealValue *= dTemp;
		dImValue   *= dTemp;
		dHarValue = sqrt((dRealValue * dRealValue + dImValue * dImValue) / 2);
	}
	else
	{
		if (nBuffer2Len > 0  && nBuffer2Pos >= 0)  
		{
			//////////fdp add 2010.4.15
			nDataLen = nBuffer1Len + nBuffer2Len;
// 			pDft->SetCurrentDataLength(nDataLen);
// 			pDft->DFTCalByMap(TRUE,pnBuffer,nBuffer1Pos,nEnd1,dRealValue,dImValue,nHar);
// 			long nEnd2 = nBuffer2Pos + nBuffer2Len;
// 			pDft->DFTCalByMap(FALSE, pnBuffer, nBuffer2Pos, nEnd2, dRealValue, dImValue, nHar);
		}
		else
		{
// 			pDft->SetCurrentDataLength(nDataLen);
// 			pDft->DFTCalByMap(TRUE, pnBuffer, nBuffer1Pos, nEnd1, dRealValue, dImValue, nHar);
		}

		pDft->SetCurrentDataLength(nDataLen);
		pDft->DFTCalByMap(pnBuffer,nBuffer1Pos,nBuffer1Len,nBuffer2Pos,nBuffer2Len,dRealValue,dImValue,nHar);
		double dCeofValue = pCalFuncPara->dCeofValue;
		double dZeroValue = pCalFuncPara->dZeroValue;
		
		double dTemp = 2 * dCeofValue / nDataLen;
		dRealValue *= dTemp;
		dImValue   *= dTemp;
		dHarValue = sqrt((dRealValue * dRealValue + dImValue * dImValue) / 2) - dZeroValue;
	}
	
	dHarPhasic = atan2(dRealValue,dImValue) * 180 / PI;
	if (dHarValue < ZERO_VALUE)
	{
		dHarValue = 0;
	}
	
	if (dHarPhasic < ZERO_VALUE)
	{
		//dHarPhasic += 0;
	}
	
#ifdef _USE_SPYDLL
	str = "CalHar>>";
	pApp->m_pGetInfor(str);
#endif
}

void GetRealandImValue(PRTCALFUNCPARA pCalFuncPara,double& dReal1,double& dReal2,double& dReal3,double& dIm1,double& dIm2,double& dIm3)
{
	double dValue1 = pCalFuncPara->pRtChanAttr[0]->dFundValue;
	double dValue2 = pCalFuncPara->pRtChanAttr[1]->dFundValue; 
	double dValue3 = pCalFuncPara->pRtChanAttr[2]->dFundValue; 
	double dPasic1 = pCalFuncPara->pRtChanAttr[0]->dFundPhase * PI_RADIAN_PER_DEG;
	double dPasic2 = pCalFuncPara->pRtChanAttr[1]->dFundPhase * PI_RADIAN_PER_DEG;
	double dPasic3 = pCalFuncPara->pRtChanAttr[2]->dFundPhase * PI_RADIAN_PER_DEG;
	
	dReal1 = dValue1 * cos(dPasic1);
	dIm1   = dValue1 * sin(dPasic1);
	dReal2 = dValue2 * cos(dPasic2);
	dIm2   = dValue2 * sin(dPasic2);
	dReal3 = dValue3 * cos(dPasic3);
	dIm3   = dValue3 * sin(dPasic3);
}
