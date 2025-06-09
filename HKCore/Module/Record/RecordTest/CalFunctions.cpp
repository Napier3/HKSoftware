#include "stdafx.h"
#include "CalFunctions.h"
#include "../MR1200BaseApp.h"

BOOL g_bInAdjustingZeroCalState = FALSE; //�Ƿ���У׼״̬�����������ϵ��ʹ��

BOOL g_bRecordApp_IsAdStart = FALSE;
BOOL g_bRecordApp_IsInRecordHoldState = FALSE;

//zhouhj 2024.9.12 ȥ��ԭnot_use_FreqCalFix50Hz��,��ֵС��1ʱ,����ʵʱ��ȡƵ�ʵķ�ʽ,�����ô˷�ʽ,�������з�ֵ����ʱ,�ᶪʧ���־���,���ù̶�Ƶ�ʼ���ķ�ʽ,����㾫�ȸ���
//��ֵȱʡΪ50Hz�����ݲ�ͬ��Ӧ�ó���,�ɸ��������Զ����øù̶�Ƶ�ʼ���ʱ��Ƶ��ֵ
//double g_dFixFreqCalValue = 50.0f;

#define _CalFrequency_use_cal_

long g_nRtFrequencyCalMode = FREQUENCY_CAL_MODE_DFT;

//SingleVariable
template <class T, class T2>
void T_RT_CalFrequency(PRTCALFUNCPARA pCalFuncPara, T* pnBuffer, BOOL bCalFreq)
{
	long RT_FILTER_DATA_LEN_NEXT = pCalFuncPara->pCalLenPara->RT_FILTER_DATA_LEN_NEXT;
//lblCalAgain:
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
// #ifndef not_use_FreqCalFix50Hz//2023.7.14 zhouhj Ĭ�ϲ��ù̶�50Hz��ʽ���޸ļ��ݷ�50Hz�����
// 	pRtChAttrVal->dFrequency = 50;
// #endif

	//zhouhj 2024.9.12 ȥ��ԭnot_use_FreqCalFix50Hz��,��ֵС��1ʱ,����ʵʱ��ȡƵ�ʵķ�ʽ
	if (g_dFixFreqCalValue>1.0f)
	{
		pRtChAttrVal->dFrequency = g_dFixFreqCalValue;
	} 

	DWORD *pdwFreqZeroPosition    = pCalFuncPara->pdwFreqZeroPosition;     //��ͨ���Ĺ����λ��
	UINT  *pnFreqZeroPosCount     = pCalFuncPara->pnFreqZeroPosCount;
	DWORD *pdwRefFreqZeroPosition = pCalFuncPara->pdwRefFreqZeroPosition;  //�ο�ͨ���Ĺ����λ��
	UINT  *pnRefFreqZeroPosCount  = pCalFuncPara->pnRefFreqZeroPosCount;

	//unsigned short *pnBuffer  = pCalFuncPara->pnBuffer;       //������
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
	long nCount = 0;

	nEndPos = nBuffer1Pos;
	T *pBegin = NULL;
	T *pEnd = NULL;
	T *pTemp = NULL;
	DWORD *pLastZeroPos = NULL;

	//��ȡ�����λ��
	pBegin = pnBuffer + nBuffer1Pos;
	pTemp = pBegin;
	pEnd = pBegin + nBuffer1Len -1 ;//������-1����Ȼ���ڴ�Խ��
	*pnFreqZeroPosCount = 0;
	long nJumpOffset = 0;

#ifdef _CalFrequency_use_cal_
	double fCurrValue = 0, fNextValue=0;
	double dCoef = pCalFuncPara->dCeofValue;
	double dZeroVal = pCalFuncPara->dZeroValue;
	double nAverage = 0;
#else
	T2 nAverage = 0;
#endif
	
	if (nBuffer1Len > 0)
	{
#ifdef _CalFrequency_use_cal_
		fCurrValue = (T2)(*pTemp) * dCoef + dZeroVal;
#endif

		while (pTemp < pEnd)//=
		{
#ifdef _CalFrequency_use_cal_
			fNextValue = (T2)(*(pTemp+1)) * dCoef + dZeroVal;
			
			if ( (fCurrValue <= 0) && (fNextValue > nAverage))
#else
			if ( ((T2)(*pTemp) <= nAverage) && ((T2)(*(pTemp+1)) > nAverage))
#endif
			{
				CRtCalFilterData<T, T2> oFilter(pCalFuncPara, pnBuffer, pTemp);
				
				if (oFilter.IsZeroPos())
				{
					*pnFreqZeroPosCount = *pnFreqZeroPosCount + 1;
					
					if (*pnFreqZeroPosCount >= MAX_FREQ_ZERO_POS_COUNT)
					{
						goto ErrorCalFreq;
					}
					
					*pdwFreqZeroPosition = nBuffer1Pos + pTemp - pBegin;
					pdwFreqZeroPosition++;

					//�����һ������㣬��������������������жϵ����ݳ���
					pTemp += RT_FILTER_DATA_LEN_NEXT;
					fCurrValue = (T2)(*pTemp) * dCoef + dZeroVal;

					if (pTemp > pEnd)
					{
						nJumpOffset = pTemp - pEnd;
						break;
					}

					continue;
				}
			}
			
			pTemp++;

#ifdef _CalFrequency_use_cal_
			fCurrValue = fNextValue;
#endif
		}
	}
	
	if (nBuffer2Pos >= 0 && nBuffer2Len > 0)
	{
		pBegin = pnBuffer + nBuffer2Pos;
		//fdp add 2009.11.13,�ж����һ�����Ƿ��������

		if (nBuffer1Len > 0)
		{
			if (nJumpOffset == 0)
			{//����Ҫ��λ
				if ( ( (T2)(*pTemp) <= nAverage ) && ( (T2)(*pBegin)  > nAverage) )
				{
					CRtCalFilterData<T, T2> oFilter(pCalFuncPara, pnBuffer, pTemp);
					
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

		//������λ
		pTemp = pBegin + nJumpOffset;
		pEnd = pBegin + nBuffer2Len;
		
		while (pTemp < pEnd)//fdp add 2009.11.13
		{
			if ( ((T2)(*pTemp) <= nAverage) && ((T2)(*(pTemp+1)) > nAverage) )//if
			{
				CRtCalFilterData<T, T2> oFilter(pCalFuncPara, pnBuffer, pTemp);

				if (oFilter.IsZeroPos())
				{
					*pnFreqZeroPosCount = *pnFreqZeroPosCount + 1;
					
					if (*pnFreqZeroPosCount >= MAX_FREQ_ZERO_POS_COUNT)
					{
						goto ErrorCalFreq;
					}
					
					*pdwFreqZeroPosition = nBuffer2Pos + pTemp - pBegin;
					pdwFreqZeroPosition++;
					
					//�����һ������㣬��������������������жϵ����ݳ���
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
	
	//////////////////////////////����Ƶ��ǰ���Ƚ��Թ���������ϲ���fdp add 2010.4.15
	pdwFreqZeroPosition    = pCalFuncPara->pdwFreqZeroPosition;     //��ͨ���Ĺ����λ��

	//////////////////////////////////////////////////////////////////////////
	//����Ƶ��
	//���һ��������λ��
	pLastZeroPos = pCalFuncPara->pdwFreqZeroPosition + *pnFreqZeroPosCount - 1;
	pdwFreqZeroPosition = pCalFuncPara->pdwFreqZeroPosition;
	
	if (*pLastZeroPos > *pdwFreqZeroPosition)
	{
		nCount = *pLastZeroPos;
		nCount -= *pdwFreqZeroPosition;
	}
	else
	{
		//��������ĩβ�ĳ���
		nCount = pCalFuncPara->nBufferLength - (long)(*pdwFreqZeroPosition);
		nCount += *pLastZeroPos;
	}

	dFrequency = (nFreqZeroPosCount-1);
	dFrequency *= pCalFuncPara->dwSampleRate;
	dFrequency /= nCount;

	if (bCalFreq)
	{
	pRtChAttrVal->dFrequency = dFrequency;
	}

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
		
		CDebugDataCal *pDebugData = g_theRecordApp.CreateCalDebugData(DEBUG_SPY_CALVALUE, 3);
		
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
		g_theRecordApp.AddDebugData(pDebugData);
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


double g_dRtFrequencyCal_Fft[10000];
#include "../FFT/FFT.h"


void RT_CalFundValue_To_double(long *pLong, double dCoef, long &nFftDataIndex, long nBegin, long nEnd)
{
	long nIndex = 0;

	for (nIndex=nBegin; nIndex<= nEnd; nIndex++)
	{
		g_dRtFrequencyCal_Fft[nFftDataIndex] = dCoef * pLong[nIndex];
		nFftDataIndex++;
	}
}

long RT_CalFundValue_To_double(PRTCALFUNCPARA pCalFuncPara)
{
	long nCount = 0;
	long nIndex = 0;
	long nBegin = pCalFuncPara->nBufFillIndex - RT_FREQUENCY_CAL_LEN - RT_FREQUENCY_CAL_LEN_ADD;
	//long nEnd = 0, nBegin2 = 0, nEnd2 = 0;

	if (nBegin >= 0)
	{
		RT_CalFundValue_To_double(pCalFuncPara->pnBuffer_long, pCalFuncPara->dCeofValue
			, nIndex, nBegin, nBegin + RT_FREQUENCY_CAL_LEN);
	}
	else
	{////zhouhj 2024.9.12 ?????����Ĵ˴��޸Ĵ�������,�������޸�
// 		nBegin2 = 0;
// 		nEnd2 = pCalFuncPara->nBufFillIndex - 1;
// 		nBegin = pCalFuncPara->nDataLength  - nEnd2 - RT_FREQUENCY_CAL_LEN_ADD;
// 		nEnd = pCalFuncPara->nDataLength - 1;

		long nBegin2 = 0;
		long nEnd2 = pCalFuncPara->nBufFillIndex - 1;
		long nEnd = pCalFuncPara->nDataLength - 1;
		nBegin = nEnd - (RT_FREQUENCY_CAL_LEN + RT_FREQUENCY_CAL_LEN_ADD - 1);

		RT_CalFundValue_To_double(pCalFuncPara->pnBuffer_long, pCalFuncPara->dCeofValue
			, nIndex, nBegin, nEnd);
		RT_CalFundValue_To_double(pCalFuncPara->pnBuffer_long, pCalFuncPara->dCeofValue
			, nIndex, nBegin2, nEnd2);
	}

	return nIndex;
}

BOOL RT_CalFrequency_dft(PRTCALFUNCPARA pCalFuncPara, BOOL bCalFreq)
{
	if (pCalFuncPara->pnBuffer != NULL)
	{
		T_RT_CalFrequency<unsigned short, short>(pCalFuncPara, pCalFuncPara->pnBuffer, bCalFreq);
	}
	else if (pCalFuncPara->pnBuffer_long != NULL)
	{
		T_RT_CalFrequency<long, long>(pCalFuncPara, pCalFuncPara->pnBuffer_long, bCalFreq);
	}

	return TRUE;
}

BOOL RT_CalFrequency_fft(PRTCALFUNCPARA pCalFuncPara)
{
	if (pCalFuncPara->nDataLength > RT_FREQUENCY_CAL_LEN + RT_FREQUENCY_CAL_LEN_ADD)
	{
		//FFT
		double dFreq = 0;
		long nPoints = RT_FREQUENCY_CAL_LEN;
		double dSampleRate = pCalFuncPara->dwSampleRate;
		PRTCHANNELATTRVALUE pRtCalValue = pCalFuncPara->pRefRtChAttrVal;
		RT_CalFundValue_To_double(pCalFuncPara);
		AfxCalcFFT(g_dRtFrequencyCal_Fft, nPoints, dSampleRate, pRtCalValue->dFundValue ,pRtCalValue->dFundPhase, pRtCalValue->dFrequency);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void RT_CalFrequency(PRTCALFUNCPARA pCalFuncPara)
{
	if (rt_is_frequency_cal_mode_fft())
	{
		RT_CalFrequency_fft(pCalFuncPara);
	}
	else if (rt_is_frequency_cal_mode_dft())
	{
		RT_CalFrequency_dft(pCalFuncPara, TRUE);
	}
	else if (rt_is_frequency_cal_mode_fft_dft())
	{
		if (pCalFuncPara->nDataLength > RT_FREQUENCY_CAL_LEN + RT_FREQUENCY_CAL_LEN_ADD)
		{
			PRTCHANNELATTRVALUE pRtCalValue = pCalFuncPara->pRefRtChAttrVal;
			RT_CalFrequency_fft(pCalFuncPara);
	
			if (pRtCalValue->dFrequency < 25)
			{
				RT_CalFrequency_dft(pCalFuncPara, TRUE);
			}
		}
	}
}

double RT_Cal_Phase(double dFrequency, long nPh, long dwSampleRate, long nVal1, long nVal2)
{
	if (nVal2 < 0)
	{
		return 0;
	}

	if (nVal1 < 0)
	{
		nVal1 = -nVal1;
	}

	double dAngPer = 360 * dFrequency / dwSampleRate; // ÿ�������ĽǶ�
	double dAdd = nVal1;
	dAdd /= (nVal1 + nVal2);
	double dPhasic = dAdd + nPh;
	dPhasic *= dAngPer;

	//nPh��ʾ��һ�����һ�����ľ��룺ʵ�ʼ����������λӦ�����ͺ�
	dPhasic = -dPhasic;

	long nCircles = (long)(dPhasic / 360);
	dPhasic -= nCircles * 360;

	if (dPhasic >= 180)
	{
		return dPhasic - 360;
	}
	else if (dPhasic <= -180)
	{
		return dPhasic + 360;
	}
	else
	{
		return dPhasic;
	}
}

//2020-4-22 lijq
template <class T1, class T2> 
void T_RT_CalEffecValue(PRTCALFUNCPARA pCalFuncPara, T1 *pnBuffer)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	
	DWORD *pdwFreqZeroPosition    = pCalFuncPara->pdwFreqZeroPosition;     //��ͨ���Ĺ����λ��
	UINT  *pnFreqZeroPosCount     = pCalFuncPara->pnFreqZeroPosCount;
	UINT  *pnRefFreqZeroPosCount  = pCalFuncPara->pnRefFreqZeroPosCount;
	DWORD *pLastZeroPos = pdwFreqZeroPosition  + *pnFreqZeroPosCount - 1;
	DWORD *pdwRefFreqZeroPosition = pCalFuncPara->pdwRefFreqZeroPosition;  //�ο�ͨ���Ĺ����λ��

	if (*pnFreqZeroPosCount == 0)
	{
		RT_CalFrequency_dft(pCalFuncPara, FALSE);
	}

	//unsigned short *pnBuffer  = pCalFuncPara->pnBuffer;       //������
	float          *pfBuffer  = pCalFuncPara->pfBuffer;

	//2022-5-4  lijunqing
	long nCalIndex = 0;
// #ifdef not_use_FreqCalFix50Hz//2023.7.14 zhouhj Ĭ�ϲ��ù̶�50Hz��ʽ���޸ļ��ݷ�50Hz�����
// 	long nCalCount = pCalFuncPara->dwSampleRate/50;
// 
// 	if (pCalFuncPara->pRefFrequency != NULL)//��������Ƶ��,����Ƶ��ֵ����1ʱ,���ö�̬�������Ƶ��ֵ
// 	{
// 		if ((*pCalFuncPara->pRefFrequency)>1.0f)
// 		{
// 			nCalCount = pCalFuncPara->dwSampleRate/(*pCalFuncPara->pRefFrequency);
// 		}
// 	}
// #else
// 	long nCalCount = pCalFuncPara->dwSampleRate / 50;
// #endif

	long nCalCount = pCalFuncPara->dwSampleRate / g_dFixFreqCalValue;
	//zhouhj 2024.9.12 ȥ��ԭnot_use_FreqCalFix50Hz��,��ֵС��1ʱ,����ʵʱ��ȡƵ�ʵķ�ʽ
	if (g_dFixFreqCalValue <= 1.0f)
	{
		nCalCount = pCalFuncPara->dwSampleRate/50;

		if (pCalFuncPara->pRefFrequency != NULL)//��������Ƶ��,����Ƶ��ֵ����1ʱ,���ö�̬�������Ƶ��ֵ
		{
			if ((*pCalFuncPara->pRefFrequency)>1.0f)
			{
				nCalCount = pCalFuncPara->dwSampleRate/(*pCalFuncPara->pRefFrequency);
			}
		}
	} 

// 	if (*pnFreqZeroPosCount >= MAX_FREQ_ZERO_POS_COUNT) //���������������޶�ֵ����Ϊֱ��
// 	{
// 		pRtChAttrVal->dEffecValue = pRtChAttrVal->dAverageValue ;//ֱ��
// 		pRtChAttrVal->dEffecPhase = 0;//ֱ��
// 		return ;
// 	}
	

	
	long nBuffer1Pos = pCalFuncPara->nDftBuffer1Pos;
	long nBuffer2Pos = pCalFuncPara->nDftBuffer2Pos;
	long nBuffer1Len = pCalFuncPara->nDftBuffer1Len;
	long nBuffer2Len = pCalFuncPara->nDftBuffer2Len;
	long nBufferLength = pCalFuncPara->nBufferLength;
	long nChIndex = pCalFuncPara->nChIndex;
	double dSum = 0;
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
		
		pTemp = pfBuffer + nBuffer1Pos;
		pEnd = pfBuffer + nBuffer1Pos + nBuffer1Len;
		
		while (pTemp < pEnd)//=
		{
			if (nCalIndex >= nCalCount)
			{
				break;
			}

			nCalIndex++;
			dSum += (*pTemp) * (*pTemp);
			pTemp++;
		}
		
		if (nBuffer2Len > 0 && nBuffer2Pos >= 0)
		{
			pTemp = pfBuffer + nBuffer2Pos;
			pEnd = pTemp + nBuffer2Len;
			
			while (pTemp < pEnd)
			{
				if (nCalIndex >= nCalCount)
				{
					break;
				}

				nCalIndex++;
				dSum += (*pTemp) * (*pTemp);
				pTemp++;
			}
		}
		
		pRtChAttrVal->dEffecValue = sqrt(dSum/(nLength -1 ));
		return ;
	}
	
	
	T1 *pBegin = NULL;
	T1 *pEnd = NULL;
	T1 *pTemp = NULL;
	double dCeofValue = pCalFuncPara->dCeofValue;
	
	////////////////////////////������Чֵ ʹ�òο�ͨ���������յ����
	pTemp = pnBuffer + nBuffer1Pos;
	pEnd = pnBuffer + nBuffer1Pos + nBuffer1Len;
	dSum = 0.0f;

	if (g_bInAdjustingZeroCalState)// 20220530 zhouhj  ��ϵ��������ǰ
	{
		dCeofValue = 5.0 / 32768.0;
	}

	double dCeofValue_Square = dCeofValue * dCeofValue;

	while (pTemp < pEnd)//=
	{
		if (nCalIndex >= nCalCount)
		{
			break;
		}

		nCalIndex++;
		dSum += ((T2)*pTemp)* dCeofValue_Square * ((T2)*pTemp) ;// 20220530 zhouhj  ��ƽ����ʱ,����ϵ����ƽ��,��ֹ9-2����ԭʼ����ֵ̫��,����ƽ����Խ��
		pTemp++;
	}

	if (nBuffer2Len > 0 && nBuffer2Pos >= 0)
	{
		pTemp = pnBuffer + nBuffer2Pos;
		pEnd = pTemp + nBuffer2Len;

		while (pTemp < pEnd)
		{
			if (nCalIndex >= nCalCount)
			{
				break;
			}

			nCalIndex++;
			dSum += ((T2)*pTemp)  * dCeofValue_Square * ((T2)*pTemp);// 20220530 zhouhj  ��ƽ����ʱ,����ϵ����ƽ��,��ֹ9-2����ԭʼ����ֵ̫��,����ƽ����Խ��
			pTemp++;
		}
	}

	double dZeroValue = pCalFuncPara->dZeroValue;


	if (dSum>0)//sqrt����ֻ֧�ֶ�����������,��ƽ���ͼ������������,����ָ���,Ϊ���������ֵΪnan�����,�˴���������
	{
		pRtChAttrVal->dEffecValue = sqrt(dSum/(nCalCount ))/* * dCeofValue*/;// 20220530 zhouhj  ��ƽ����ʱ,����ϵ����ƽ��,�˴����ٳ���ϵ��
	} 
	else
	{
		pRtChAttrVal->dEffecValue = -sqrt((-dSum)/(nCalCount ))/* * dCeofValue*/;// 20220530 zhouhj  ��ƽ����ʱ,����ϵ����ƽ��,�˴����ٳ���ϵ��
	}

	//if (!g_bInAdjustingZeroCalState)
	{
		pRtChAttrVal->dEffecValue -= dZeroValue;
	}

	//2022-5-4  lijunqing can angle
	//�ж��Ƿ��������,fdp add 2010.6.13
	if (*pnFreqZeroPosCount > MAX_FREQ_ZERO_POS_COUNT || *pnFreqZeroPosCount == 0)
	{
		pRtChAttrVal->dEffecPhase = 0;
		return;
	}

	if (pCalFuncPara->nDataLength <= RT_FREQUENCY_CAL_LEN * 4)
	{
		pRtChAttrVal->dEffecPhase = 0;
		return;
	}

	long nPh = 0;

	if (nBuffer1Pos >= *pdwFreqZeroPosition && nBuffer1Pos >= (long)(*pdwRefFreqZeroPosition)) //����ѭ��
	{
		nPh = nBufferLength - nBuffer1Pos + *pdwFreqZeroPosition;
	}
	else
	{
		nPh = (long)(*pdwFreqZeroPosition) - nBuffer1Pos;
	}

	long nZeroPos = *pdwFreqZeroPosition;
	if (nZeroPos == nBufferLength-1)
	{
		pRtChAttrVal->dEffecPhase = RT_Cal_Phase(pRtChAttrVal->dFrequency, nPh, pCalFuncPara->dwSampleRate, pnBuffer[nZeroPos], pnBuffer[0]);
	}
	else
	{
		pRtChAttrVal->dEffecPhase = RT_Cal_Phase(pRtChAttrVal->dFrequency, nPh, pCalFuncPara->dwSampleRate, pnBuffer[nZeroPos], pnBuffer[nZeroPos+1]);
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("pRtChAttrVal->dEffecPhase=%lf."),pRtChAttrVal->dEffecPhase);

	return;

	//������λ��
	if (*pnRefFreqZeroPosCount > 0 && *pnFreqZeroPosCount > 0)
	{
		if (pdwRefFreqZeroPosition == pdwFreqZeroPosition)//�ο���
		{
			pRtChAttrVal->dEffecPhase = 0;
		}
		else
		{
			//�ж��Ƿ��������,fdp add 2010.6.13
			if (*pnRefFreqZeroPosCount > MAX_FREQ_ZERO_POS_COUNT && *pnFreqZeroPosCount > MAX_FREQ_ZERO_POS_COUNT)
			{
				pRtChAttrVal->dEffecPhase = 0;
				return;
			}

			double dPhasic = 0;
			DWORD* pCurrentChanPos = pdwFreqZeroPosition;
			BOOL bFind = FALSE;
			long nPh = 0;

			if (g_bRecordApp_IsAdStart && !g_bRecordApp_IsInRecordHoldState)
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

				if (*pCurrentChanPos >= *pdwFreqZeroPosition && nBuffer1Pos >= (long)(*pdwRefFreqZeroPosition)) //����ѭ��
				{
					nPh = (long)(*pCurrentChanPos) - nBuffer1Pos;
				}
				else if (*pCurrentChanPos >= *pdwFreqZeroPosition && nBuffer1Pos < (long)(*pdwRefFreqZeroPosition)) //�ο�ͨ��ѭ������ͨ����ѭ��
				{
					nPh = (long)(*pCurrentChanPos) - nBufferLength - nBuffer1Pos;//nDataLength
				}
				else if (*pCurrentChanPos < *pdwFreqZeroPosition && nBuffer1Pos >= (long)(*pdwRefFreqZeroPosition)) //��ͨ��ѭ�����ο�ͨ����ѭ��
				{
					nPh = (long)(*pCurrentChanPos) + nBufferLength - nBuffer1Pos;//nDataLength
				}
				else //��ѭ��������
				{
					nPh = (long)(*pCurrentChanPos) - nBuffer1Pos;
				}
			} 
			else
			{
				if ((long)(*pdwRefFreqZeroPosition)>=nBuffer1Pos && (long)(*pdwRefFreqZeroPosition)<(nBuffer1Pos + nBuffer1Len))
				{//�ο�ͨ���ھɵ�һ��
					if ((long)(*pCurrentChanPos)>=nBuffer1Pos && (long)(*pCurrentChanPos)<(nBuffer1Pos + nBuffer1Len)) 
					{//����һ��
						nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition);
					}
					else
					{//��ͨ�����µ�һ��
						nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition) + nBufferLength;
					}
				} 
				else
				{//�ο�ͨ�������µ�һ��
					if ((long)(*pCurrentChanPos)>=nBuffer1Pos && (long)(*pCurrentChanPos)<(nBuffer1Pos + nBuffer1Len)) 
					{//��ͨ���ھɵ�һ��
						nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition) - nDataLength;
					}
					else
					{//��ͨ�����µ�һ��
						nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition);
					}
				}
			}
			

			nPh = 0 - nPh;//��Ϊ�Ƿ���Ŵ�����������180
#ifdef _USE_RECORD_BUFFER_TO_CAL
			dPhasic = (*pCalFuncPara->pRefFrequency + pRtChAttrVal->dFrequency) * nPh * 360 / ( 2 * g_dwSampleRate) ;
#else
			dPhasic = (*pCalFuncPara->pRefFrequency + pRtChAttrVal->dFrequency) * nPh * 360 / ( 2 * pCalFuncPara->dwSampleRate) ;
#endif
			
//			dPhasic += 180; //��Ϊ�Ƿ���Ŵ�����������180
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

void RT_CalEffecValue(PRTCALFUNCPARA pCalFuncPara)
{
	if (pCalFuncPara->pnBuffer != NULL)
	{
		return T_RT_CalEffecValue<unsigned short, short>(pCalFuncPara, pCalFuncPara->pnBuffer);
	}

	if (pCalFuncPara->pnBuffer_long != NULL)
	{
		return T_RT_CalEffecValue<long, long>(pCalFuncPara, pCalFuncPara->pnBuffer_long);
	}
}

void RT_CalFundValue(PRTCALFUNCPARA pCalFuncPara)
{	
	if (rt_is_frequency_cal_mode_fft())
	{
		return;
	}
	else if (rt_is_frequency_cal_mode_fft_dft())
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;

	//DFT
	CalHar(0,pCalFuncPara, pRtChAttrVal->dFundValue ,pRtChAttrVal->dFundPhase);	
}

void RT_CalFundPhase(PRTCALFUNCPARA pCalFuncPara)
{

}

template<class T1, class T2>
void T_RT_CalPeakValue(PRTCALFUNCPARA pCalFuncPara, T1* pnBuffer)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	
	double dCeofValue = pCalFuncPara->dCeofValue ;
	double dZeroValue = pCalFuncPara->dZeroValue ;
	//unsigned short *pnBuffer  = pCalFuncPara->pnBuffer;       //������
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
	T2 nMaxValue = -32768;
	UINT nIndex = 0;
	UINT nEndPos = 0;
	double dAverage = 0;
	long nCount = 0;
	
	nEndPos = nBuffer1Pos;
	T1 *pBegin = NULL;
	T1 *pEnd = NULL;
	T1 *pTemp = NULL;
	DWORD *pLastZeroPos = NULL;
	
	//��ȡƽ��ֵ
	pBegin = pnBuffer + nBuffer1Pos;
	pTemp = pBegin;
	pEnd = pBegin + nBuffer1Len;
	
	if (nBuffer1Len > 0)
	{
		while (pTemp < pEnd)//= ���ﲻ���� = ���ڴ�Խ��
		{
			T2 nValue = (T2)(*pTemp);		
			nMaxValue = max(nMaxValue, nValue);
			pTemp++;
		}
	}
	
	if (nBuffer2Len > 0 && nBuffer2Pos >= 0) //����Ҫ�� = ��ΪnBuffer2Len �ڻ��ʱ-1��,���ڲ���Ҫ=�ˣ���Ϊ-1û����
	{
		pBegin = pnBuffer + nBuffer2Pos;
		pTemp = pBegin;
		pEnd = pBegin + nBuffer2Len;
		
		while (pTemp < pEnd)// =
		{
			T2 nValue = (T2)(*pTemp);		
			nMaxValue = max(nMaxValue, nValue);
			pTemp++;
		}
	}
	
	pRtChAttrVal->dPeakValue = (dCeofValue * nMaxValue - dZeroValue);
}

void RT_CalPeakValue(PRTCALFUNCPARA pCalFuncPara)
{
	if (pCalFuncPara->pnBuffer != NULL)
	{
		return T_RT_CalPeakValue<unsigned short, short>(pCalFuncPara, pCalFuncPara->pnBuffer);
	}

	if (pCalFuncPara->pnBuffer_long != NULL)
	{
		return T_RT_CalPeakValue<long, long>(pCalFuncPara, pCalFuncPara->pnBuffer_long);
	}
}

template<class T1, class T2>
void T_RT_CalVellayValue(PRTCALFUNCPARA pCalFuncPara, T1* pnBuffer)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	
	double dCeofValue = pCalFuncPara->dCeofValue ;
	double dZeroValue = pCalFuncPara->dZeroValue ;
	//unsigned short *pnBuffer  = pCalFuncPara->pnBuffer;       //������
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
	T2 nMinValue = 32767;
	UINT nIndex = 0;
	UINT nEndPos = 0;
	double dAverage = 0;
	long nCount = 0;
	
	nEndPos = nBuffer1Pos;
	T1 *pBegin = NULL;
	T1 *pEnd = NULL;
	T1 *pTemp = NULL;
	DWORD *pLastZeroPos = NULL;
	
	//��ȡƽ��ֵ
	pBegin = pnBuffer + nBuffer1Pos;
	pTemp = pBegin;
	pEnd = pBegin + nBuffer1Len;
	
	if (nBuffer1Len > 0)
	{
		while (pTemp < pEnd)//= ���ﲻ���� = ���ڴ�Խ��
		{
			T2 nValue = (T2)(*pTemp);		
			nMinValue = min(nMinValue, nValue);
			pTemp++;
		}
	}
	
	if (nBuffer2Len > 0 && nBuffer2Pos >= 0) //����Ҫ�� = ��ΪnBuffer2Len �ڻ��ʱ-1��,���ڲ���Ҫ=�ˣ���Ϊ-1û����
	{
		pBegin = pnBuffer + nBuffer2Pos;
		pTemp = pBegin;
		pEnd = pBegin + nBuffer2Len;
		
		while (pTemp < pEnd)// =
		{
			T2 nValue = (T2)(*pTemp);		
			nMinValue = min(nMinValue, nValue);
			pTemp++;
		}
	}
	
	pRtChAttrVal->dVellayValue =  dCeofValue * nMinValue - dZeroValue;
}

void RT_CalVellayValue(PRTCALFUNCPARA pCalFuncPara)
{
	if (pCalFuncPara->pnBuffer != NULL)
	{
		return T_RT_CalVellayValue<unsigned short, short>(pCalFuncPara, pCalFuncPara->pnBuffer);
	}

	if (pCalFuncPara->pnBuffer_long != NULL)
	{
		return T_RT_CalVellayValue<long, long>(pCalFuncPara, pCalFuncPara->pnBuffer_long);
	}
}

template < class T1, class T2>
void T_RT_CalInstValue(PRTCALFUNCPARA pCalFuncPara, T1* pnBuffer)
{
	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	
	double dCeofValue = pCalFuncPara->dCeofValue;
	double dZeroValue = pCalFuncPara->dZeroValue;
	//unsigned short *pnBuffer  = pCalFuncPara->pnBuffer;       //������
	float          *pfBuffer  = pCalFuncPara->pfBuffer;
	
	if (pnBuffer == NULL)
	{
		return;
	}
	
	long nBuffer1Pos = pCalFuncPara->nBuffer1Pos;

	double dValue = (T2)(*(pnBuffer + nBuffer1Pos));
	dValue *= dCeofValue;
	dValue -= dZeroValue;

	pRtChAttrVal->dInstValue =  dValue;
}


void RT_CalInstValue(PRTCALFUNCPARA pCalFuncPara)
{
	if (pCalFuncPara->pnBuffer != NULL)
	{
		return T_RT_CalInstValue<unsigned short, short>(pCalFuncPara, pCalFuncPara->pnBuffer);
	}

	if (pCalFuncPara->pnBuffer_long != NULL)
	{
		return T_RT_CalInstValue<long, long>(pCalFuncPara, pCalFuncPara->pnBuffer_long);
	}
}

template < class T1, class T2>
void T_RT_CalAverageValue(PRTCALFUNCPARA pCalFuncPara, T1* pnBuffer)
{
	if (pCalFuncPara == NULL)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	DWORD *pdwFreqZeroPosition		 = pCalFuncPara->pdwFreqZeroPosition;     //��ͨ���Ĺ����λ��
	UINT  *pnFreqZeroPosCount		 = pCalFuncPara->pnFreqZeroPosCount;
	DWORD *pdwRefFreqZeroPosition	 = pCalFuncPara->pdwRefFreqZeroPosition;  //�ο�ͨ���Ĺ����λ��
	UINT  *pnRefFreqZeroPosCount	 = pCalFuncPara->pnRefFreqZeroPosCount;
	
	double dCeofValue = pCalFuncPara->dCeofValue ;
	double dZeroValue = pCalFuncPara->dZeroValue ;
	//unsigned short *pnBuffer  = pCalFuncPara->pnBuffer;       //������
	float          *pfBuffer  = pCalFuncPara->pfBuffer;
	
// 	if (g_bInAdjustingZeroCalState)
// 	{
// 		dCeofValue = 5.0 / 32768.0;
// 	}

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
	T1 *pBegin = NULL;
	T1 *pEnd = NULL;
	T1 *pTemp = NULL;
	DWORD *pLastZeroPos = NULL;

	long nTotalLen = nBuffer1Len;

	if (nBuffer2Len < 0)
	{
		nTotalLen += nBuffer2Len;
	}

// #ifdef not_use_FreqCalFix50Hz//2023.7.14 zhouhj Ĭ�ϲ��ù̶�50Hz��ʽ���޸ļ��ݷ�50Hz�����
// 	long nCyclePoints = pCalFuncPara->dwSampleRate / 50;
// 
// 	if (pCalFuncPara->pRefFrequency != NULL)//��������Ƶ��,����Ƶ��ֵ����1ʱ,���ö�̬�������Ƶ��ֵ
// 	{
// 		if ((*pCalFuncPara->pRefFrequency)>1.0f)
// 		{
// 			nCyclePoints = pCalFuncPara->dwSampleRate/(*pCalFuncPara->pRefFrequency);
// 		}
// 	}
// #else
// 	long nCyclePoints = pCalFuncPara->dwSampleRate / 50;
// #endif

	long nCyclePoints = pCalFuncPara->dwSampleRate / g_dFixFreqCalValue;
	//zhouhj 2024.9.12 ȥ��ԭnot_use_FreqCalFix50Hz��,��ֵС��1ʱ,����ʵʱ��ȡƵ�ʵķ�ʽ
	if (g_dFixFreqCalValue <= 1.0f)
	{
		nCyclePoints = pCalFuncPara->dwSampleRate / 50;

		if (pCalFuncPara->pRefFrequency != NULL)//��������Ƶ��,����Ƶ��ֵ����1ʱ,���ö�̬�������Ƶ��ֵ
		{
			if ((*pCalFuncPara->pRefFrequency)>1.0f)
			{
				nCyclePoints = pCalFuncPara->dwSampleRate/(*pCalFuncPara->pRefFrequency);
			}
		}
	}

	long nTotalPoints = nTotalLen / nCyclePoints;
	nTotalPoints *= nCyclePoints;
	long nPointsCal = 0;

	//��ȡƽ��ֵ
	pBegin = pnBuffer + nBuffer1Pos;
	pTemp = pBegin;
	pEnd = pBegin + nBuffer1Len;
	
	if (nBuffer1Len > 0)
	{
		while (pTemp < pEnd)//= ���ﲻ���� = ���ڴ�Խ��
		{
			vSum += (T2)(*pTemp);
			pTemp++;
			nPointsCal++;

			if (nPointsCal >= nTotalPoints)
				break;
		}
	}
	
	if (nBuffer2Len > 0 && nBuffer2Pos >= 0) //����Ҫ�� = ��ΪnBuffer2Len �ڻ��ʱ-1��,���ڲ���Ҫ=�ˣ���Ϊ-1û����
	{
		pBegin = pnBuffer + nBuffer2Pos;
		pTemp = pBegin;
		pEnd = pBegin + nBuffer2Len;
		
		while (pTemp < pEnd)// =
		{
			if (nPointsCal >= nTotalPoints)
				break;

			nPointsCal++;
			vSum += (T2)(*pTemp);
			pTemp++;
		}
	}
	
	pRtChAttrVal->dAverageValue = dCeofValue * vSum / nTotalPoints - dZeroValue;
}


void RT_CalAverageValue(PRTCALFUNCPARA pCalFuncPara)
{
	if (pCalFuncPara->pnBuffer != NULL)
	{
		return T_RT_CalAverageValue<unsigned short, short>(pCalFuncPara, pCalFuncPara->pnBuffer);
	}

	if (pCalFuncPara->pnBuffer_long != NULL)
	{
		return T_RT_CalAverageValue<long, long>(pCalFuncPara, pCalFuncPara->pnBuffer_long);
	}
}


void RT_CalHarm02Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm02Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(1,pCalFuncPara, pRtChAttrVal->dHarmValue[0] ,pRtChAttrVal->dHarmPhase[0]);	
}

void RT_CalHarm03Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm03Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(2,pCalFuncPara, pRtChAttrVal->dHarmValue[1] ,pRtChAttrVal->dHarmPhase[1]);
}

void RT_CalHarm04Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm04Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(3,pCalFuncPara, pRtChAttrVal->dHarmValue[2] ,pRtChAttrVal->dHarmPhase[2]);
}

void RT_CalHarm05Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm05Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(4,pCalFuncPara, pRtChAttrVal->dHarmValue[3] ,pRtChAttrVal->dHarmPhase[3]);
}

void RT_CalHarm06Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm06Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(5,pCalFuncPara, pRtChAttrVal->dHarmValue[4] ,pRtChAttrVal->dHarmPhase[4]);
}

void RT_CalHarm07Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm07Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(6,pCalFuncPara, pRtChAttrVal->dHarmValue[5] ,pRtChAttrVal->dHarmPhase[5]);
}

void RT_CalHarm08Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm08Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(7,pCalFuncPara, pRtChAttrVal->dHarmValue[6] ,pRtChAttrVal->dHarmPhase[6]);
}

void RT_CalHarm09Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm09Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(8,pCalFuncPara, pRtChAttrVal->dHarmValue[7] ,pRtChAttrVal->dHarmPhase[7]);
}

void RT_CalHarm10Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm10Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(9,pCalFuncPara, pRtChAttrVal->dHarmValue[8] ,pRtChAttrVal->dHarmPhase[8]);
}

void RT_CalHarm11Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm11Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(10,pCalFuncPara, pRtChAttrVal->dHarmValue[9] ,pRtChAttrVal->dHarmPhase[9]);
}

void RT_CalHarm12Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm12Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(11,pCalFuncPara, pRtChAttrVal->dHarmValue[10] ,pRtChAttrVal->dHarmPhase[10]);
}

void RT_CalHarm13Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm13Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(12,pCalFuncPara, pRtChAttrVal->dHarmValue[11] ,pRtChAttrVal->dHarmPhase[11]);
}

void RT_CalHarm14Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm14Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(13,pCalFuncPara, pRtChAttrVal->dHarmValue[12] ,pRtChAttrVal->dHarmPhase[12]);
}

void RT_CalHarm15Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm15Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(14,pCalFuncPara, pRtChAttrVal->dHarmValue[13] ,pRtChAttrVal->dHarmPhase[13]);
}

void RT_CalHarm16Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm16Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(15,pCalFuncPara, pRtChAttrVal->dHarmValue[14] ,pRtChAttrVal->dHarmPhase[14]);
}

void RT_CalHarm17Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm17Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(16,pCalFuncPara, pRtChAttrVal->dHarmValue[15] ,pRtChAttrVal->dHarmPhase[15]);
}

void RT_CalHarm18Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm18Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(17,pCalFuncPara, pRtChAttrVal->dHarmValue[16] ,pRtChAttrVal->dHarmPhase[16]);
}

void RT_CalHarm19Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm19Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(18,pCalFuncPara, pRtChAttrVal->dHarmValue[17] ,pRtChAttrVal->dHarmPhase[17]);
}

void RT_CalHarm20Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm20Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(19,pCalFuncPara, pRtChAttrVal->dHarmValue[18] ,pRtChAttrVal->dHarmPhase[18]);
}

void RT_CalHarm21Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm21Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(20,pCalFuncPara, pRtChAttrVal->dHarmValue[19] ,pRtChAttrVal->dHarmPhase[19]);
}

void RT_CalHarm22Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm22Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(21,pCalFuncPara, pRtChAttrVal->dHarmValue[20] ,pRtChAttrVal->dHarmPhase[20]);
}

void RT_CalHarm23Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm23Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(22,pCalFuncPara, pRtChAttrVal->dHarmValue[21] ,pRtChAttrVal->dHarmPhase[21]);
}

void RT_CalHarm24Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm24Value == 0)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	CalHar(23,pCalFuncPara, pRtChAttrVal->dHarmValue[22] ,pRtChAttrVal->dHarmPhase[22]);
}

void RT_CalHarm25Value(PRTCALFUNCPARA pCalFuncPara)
{
	if (g_nEnableCal_Harm25Value == 0)
	{
		return;
	}

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

//���㶼��ʹ�õĻ�������Чֵ����λ
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

void CalHar_Cal(long nHar,PRTCALFUNCPARA pCalFuncPara, double& dHarValue ,double& dHarPhasic)
{
#ifdef _USE_SPYDLL
	
	CString str(">>CalHar");
	g_theRecordApp.m_pGetInfor(str);
#endif
	
	CDFT* pDft = CDFT::GetDft();

	if (pDft == NULL)
	{
		return;
	}

	PRTCHANNELATTRVALUE pRtChAttrVal = pCalFuncPara->pRtChAttrVal;
	short* pnBuffer  = (short*)pCalFuncPara->pnBuffer;       //������
	long* pnBuffer_long  = (long*)pCalFuncPara->pnBuffer_long;       //������
	float* pfBuffer  = pCalFuncPara->pfBuffer;
	long nBuffer1Pos = pCalFuncPara->nDftBuffer1Pos;
	long nBuffer2Pos = pCalFuncPara->nDftBuffer2Pos;
	long nBuffer1Len = pCalFuncPara->nDftBuffer1Len;
	long nBuffer2Len = pCalFuncPara->nDftBuffer2Len;
	long nEnd1 = nBuffer1Pos + nBuffer1Len;
	double dRealValue,dImValue;
	long nChIndex  = pCalFuncPara->nChIndex;
	long nDataLen = nBuffer1Len;

	if (pnBuffer == NULL && pnBuffer_long == NULL)
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

		pDft->CDFTBase::DFTCalByMap(pfBuffer,nBuffer1Pos,nBuffer1Len,nBuffer2Pos,nBuffer2Len,dRealValue,dImValue,nHar);
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

		if (pnBuffer != NULL)
		{
			pDft->DFTCalByMap(pnBuffer,nBuffer1Pos,nBuffer1Len,nBuffer2Pos,nBuffer2Len,dRealValue,dImValue,nHar);
		}
		else if (pnBuffer_long != NULL)
		{
			pDft->DFTCalByMap(pnBuffer_long,nBuffer1Pos,nBuffer1Len,nBuffer2Pos,nBuffer2Len,dRealValue,dImValue,nHar);
		}

		double dCeofValue = pCalFuncPara->dCeofValue;
		double dZeroValue = pCalFuncPara->dZeroValue;
		
		double dTemp = 2 * dCeofValue / nDataLen;
		dRealValue *= dTemp;
		dImValue   *= dTemp;
		dHarValue = sqrt((dRealValue * dRealValue + dImValue * dImValue) / 2) - dZeroValue;
	}
	
	dHarPhasic = atan2(dRealValue, dImValue) * 180 / PI;
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
	g_theRecordApp.m_pGetInfor(str);
#endif
}

void CalHar(long nHar,PRTCALFUNCPARA pCalFuncPara, double& dHarValue ,double& dHarPhasic)
{
	if (rt_is_frequency_cal_mode_fft_dft() || rt_is_frequency_cal_mode_fft())
	{
		if (pCalFuncPara->nDataLength < RT_FREQUENCY_CAL_LEN + RT_FREQUENCY_CAL_LEN_ADD)
		{
			return;
		}
	}

	CalHar_Cal(nHar, pCalFuncPara, dHarValue, dHarPhasic);
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

//2022-5-3  lijunqing enable harm cal  functions
long g_nEnableCal_Root  = 1 ;

long g_nEnableCal_Harm02Value = 1 ;
long g_nEnableCal_Harm03Value = 1 ;
long g_nEnableCal_Harm04Value = 1 ;
long g_nEnableCal_Harm05Value = 1 ;
long g_nEnableCal_Harm06Value = 1 ;
long g_nEnableCal_Harm07Value = 1 ;
long g_nEnableCal_Harm08Value = 1 ;
long g_nEnableCal_Harm09Value = 1 ;
long g_nEnableCal_Harm10Value = 1 ;
long g_nEnableCal_Harm11Value = 1 ;
long g_nEnableCal_Harm12Value = 1 ;
long g_nEnableCal_Harm13Value = 1 ;
long g_nEnableCal_Harm14Value = 1 ;
long g_nEnableCal_Harm15Value = 1 ;
long g_nEnableCal_Harm16Value = 1 ;
long g_nEnableCal_Harm17Value = 1 ;
long g_nEnableCal_Harm18Value = 1 ;
long g_nEnableCal_Harm19Value = 1 ;
long g_nEnableCal_Harm20Value = 1 ;
long g_nEnableCal_Harm21Value = 1 ;
long g_nEnableCal_Harm22Value = 1 ;
long g_nEnableCal_Harm23Value = 1 ;
long g_nEnableCal_Harm24Value = 1 ;
long g_nEnableCal_Harm25Value = 1 ;

