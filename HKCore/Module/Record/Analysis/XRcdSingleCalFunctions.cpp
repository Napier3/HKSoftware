// RtCalFilterData.cpp: implementation of the CRtCalFilterData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XRcdSingleCalFunctions.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//2020-4-22 lijq
//T1=unsinged short, shor, ungigned long , long ,     float
//T2=        short     , short,     long        , long ,     double
//T3=      __int64    ,  __int64, __int64,    ,__int64,  double
template <class T1, class T2, class Tsum> 
void T_RT_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, T1 *pDataBuffer
							   , double dEffecValue, double &dEffecPhase
							   , DWORD *pdwFreqZeroPosition, UINT  *pnFreqZeroPosCount
							   , DWORD *pdwRefFreqZeroPosition, UINT  *pnRefFreqZeroPosCount
							   , double dRefFrequency, double dFrequency, long dwSampleRate)
{
	long nBuffer1Pos = pDataPos->nBuffer1Pos;
	long nBuffer2Pos = pDataPos->nBuffer2Pos;
	long nBuffer1Len = pDataPos->nBuffer1Len;
	long nBuffer2Len = pDataPos->nBuffer2Len;
	long nBufferLength = pDataPos->nBufferLength;
	Tsum vSum = 0;
	UINT nIndex = 0;
	long nDataLength = pDataPos->nDataLength;
	long nLength = nBuffer1Len;

	if (nBuffer2Pos>= 0 && nBuffer2Len > 0)
	{
		nLength += nBuffer2Len;
	}

	dEffecValue = 0;
	dEffecPhase = 0;

	if (pDataBuffer == NULL)
	{
		return;
	}

	T1 *pBegin = NULL;
	T1 *pEnd = NULL;
	T1 *pTemp = NULL;

	////////////////////////////计算有效值 使用参考通道的起点和终点计算
	pTemp = pDataBuffer + nBuffer1Pos;
	pEnd = pDataBuffer + nBuffer1Pos + nBuffer1Len;
	vSum = 0;

	while (pTemp < pEnd)//=
	{
		vSum += ((T2)*pTemp) * ((T2)*pTemp);
		pTemp++;
	}

	if (nBuffer2Len > 0 && nBuffer2Pos >= 0)
	{
		pTemp = pDataBuffer + nBuffer2Pos;
		pEnd = pTemp + nBuffer2Len;

		while (pTemp < pEnd)
		{
			vSum += ((T2)*pTemp) * ((T2)*pTemp);
			pTemp++;
		}
	}

	dEffecValue = (double)vSum;
	dEffecValue /= nLength ;
	dEffecValue = sqrt(dEffecValue);

	if (pdwFreqZeroPosition == NULL || pnFreqZeroPosCount == NULL
		|| pdwRefFreqZeroPosition == NULL || pnRefFreqZeroPosCount == NULL)
	{
		dEffecPhase = 0;
		return;
	}

	DWORD *pLastZeroPos = pdwFreqZeroPosition  + *pnFreqZeroPosCount - 1;

	//计算相位差
	if (*pnRefFreqZeroPosCount <= 0|| *pnFreqZeroPosCount <= 0)
	{
		return;
	}

	if (pdwRefFreqZeroPosition == pdwFreqZeroPosition)//参考相
	{
		return;
	}

	//判断是否过零点过多,fdp add 2010.6.13
	if (*pnRefFreqZeroPosCount > MAX_FREQ_ZERO_POS_COUNT && *pnFreqZeroPosCount > MAX_FREQ_ZERO_POS_COUNT)
	{
		return;
	}

	double dPhasic = 0;
	DWORD* pCurrentChanPos = pdwFreqZeroPosition;
	BOOL bFind = FALSE;
	long nPh = 0;

	if ((long)(*pdwRefFreqZeroPosition)>=nBuffer1Pos && (long)(*pdwRefFreqZeroPosition)<(nBuffer1Pos + nBuffer1Len))
	{//参考通道在旧的一侧
		if ((long)(*pCurrentChanPos)>=nBuffer1Pos && (long)(*pCurrentChanPos)<(nBuffer1Pos + nBuffer1Len)) 
		{//都在一侧
			nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition);
		}
		else
		{//本通道在新的一侧
			nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition) + nBufferLength;
		}
	} 
	else
	{//参考通道的在新的一侧
		if ((long)(*pCurrentChanPos)>=nBuffer1Pos && (long)(*pCurrentChanPos)<(nBuffer1Pos + nBuffer1Len)) 
		{//本通道在旧的一侧
			nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition) - nDataLength;
		}
		else
		{//本通道在新的一侧
			nPh = (long)(*pCurrentChanPos) - (long)(*pdwRefFreqZeroPosition);
		}
	}

	dPhasic = (dRefFrequency + dFrequency) * nPh * 360 / ( 2 * dwSampleRate) ;

	long nCircles = (long)(dPhasic / 360);
	dPhasic -= nCircles * 360;

	if (dPhasic >= 180)
	{
		dEffecPhase = dPhasic - 360;
	}
	else if (dPhasic <= -180)
	{
		dEffecPhase = dPhasic + 360;
	}
	else
	{
		dEffecPhase = dPhasic;
	}
}

void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, unsigned short *pDataBuffer
							 , double dEffecValue, double &dEffecPhase
							 , DWORD *pdwFreqZeroPosition, UINT  *pnFreqZeroPosCount
							 , DWORD *pdwRefFreqZeroPosition, UINT  *pnRefFreqZeroPosCount
							 , double dRefFrequency, double dFrequency, long dwSampleRate)
{
	T_RT_CalEffecValue_Single<unsigned short, short, __int64>(pDataPos, pDataBuffer, dEffecValue, dEffecPhase
		, pdwFreqZeroPosition, pnFreqZeroPosCount, pdwRefFreqZeroPosition, pnRefFreqZeroPosCount
		, dRefFrequency, dFrequency, dwSampleRate);
}

void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, short *pDataBuffer
							 , double dEffecValue, double &dEffecPhase
							 , DWORD *pdwFreqZeroPosition, UINT  *pnFreqZeroPosCount
							 , DWORD *pdwRefFreqZeroPosition, UINT  *pnRefFreqZeroPosCount
							 , double dRefFrequency, double dFrequency, long dwSampleRate)
{
	T_RT_CalEffecValue_Single<short, short, __int64>(pDataPos, pDataBuffer, dEffecValue, dEffecPhase
		, pdwFreqZeroPosition, pnFreqZeroPosCount, pdwRefFreqZeroPosition, pnRefFreqZeroPosCount
		, dRefFrequency, dFrequency, dwSampleRate);
}


void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, long *pDataBuffer
							 , double dEffecValue, double &dEffecPhase
							 , DWORD *pdwFreqZeroPosition, UINT  *pnFreqZeroPosCount
							 , DWORD *pdwRefFreqZeroPosition, UINT  *pnRefFreqZeroPosCount
							 , double dRefFrequency, double dFrequency, long dwSampleRate)
{
	T_RT_CalEffecValue_Single<long, long, __int64>(pDataPos, pDataBuffer, dEffecValue, dEffecPhase
		, pdwFreqZeroPosition, pnFreqZeroPosCount, pdwRefFreqZeroPosition, pnRefFreqZeroPosCount
		, dRefFrequency, dFrequency, dwSampleRate);
}

void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, float *pDataBuffer
							 , double dEffecValue, double &dEffecPhase
							 , DWORD *pdwFreqZeroPosition, UINT  *pnFreqZeroPosCount
							 , DWORD *pdwRefFreqZeroPosition, UINT  *pnRefFreqZeroPosCount
							 , double dRefFrequency, double dFrequency, long dwSampleRate)
{
	T_RT_CalEffecValue_Single<float, float, double>(pDataPos, pDataBuffer, dEffecValue, dEffecPhase
		, pdwFreqZeroPosition, pnFreqZeroPosCount, pdwRefFreqZeroPosition, pnRefFreqZeroPosCount
		, dRefFrequency, dFrequency, dwSampleRate);
}

void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, double *pDataBuffer
							 , double dEffecValue, double &dEffecPhase
							 , DWORD *pdwFreqZeroPosition, UINT  *pnFreqZeroPosCount
							 , DWORD *pdwRefFreqZeroPosition, UINT  *pnRefFreqZeroPosCount
							 , double dRefFrequency, double dFrequency, long dwSampleRate)
{
	T_RT_CalEffecValue_Single<double, double, double>(pDataPos, pDataBuffer, dEffecValue, dEffecPhase
		, pdwFreqZeroPosition, pnFreqZeroPosCount, pdwRefFreqZeroPosition, pnRefFreqZeroPosCount
		, dRefFrequency, dFrequency, dwSampleRate);
}

//////////////////////////////////////////////////////////////////////////
//CalEffecValue_Quick
template <class T1, class T2, class Tsum> 
void T_RT_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, T1 *pDataBuffer, double dEffecValue)
{
	long nBuffer1Pos = pDataPos->nBuffer1Pos;
	long nBuffer2Pos = pDataPos->nBuffer2Pos;
	long nBuffer1Len = pDataPos->nBuffer1Len;
	long nBuffer2Len = pDataPos->nBuffer2Len;
	long nBufferLength = pDataPos->nBufferLength;
	Tsum vSum = 0;
	UINT nIndex = 0;
	long nDataLength = pDataPos->nDataLength;

	long nLength = nBuffer1Len;

	if (nBuffer2Pos>= 0 && nBuffer2Len > 0)
	{
		nLength += nBuffer2Len;
	}

	if (pDataBuffer == NULL)
	{
		dEffecValue = 0;
		return;
	}

	T1 *pBegin = NULL;
	T1 *pEnd = NULL;
	T1 *pTemp = NULL;

	////////////////////////////计算有效值 使用参考通道的起点和终点计算
	pTemp = pDataBuffer + nBuffer1Pos;
	pEnd = pDataBuffer + nBuffer1Pos + nBuffer1Len;

	while (pTemp < pEnd)//=
	{
		vSum += abs((T2)*pTemp);
		pTemp++;
	}

	if (nBuffer2Len > 0 && nBuffer2Pos >= 0)
	{
		pTemp = pDataBuffer + nBuffer2Pos;
		pEnd = pTemp + nBuffer2Len;

		while (pTemp < pEnd)
		{
			vSum += abs((T2)*pTemp);
			pTemp++;
		}
	}

	dEffecValue = (double)vSum;
	dEffecValue /= nLength;
	dEffecValue = sqrt(dEffecValue);
}

void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, unsigned short *pDataBuffer, double dEffecValue)
{
	T_RT_CalEffecValue_Quick<unsigned short, short, __int64>(pDataPos, pDataBuffer, dEffecValue);
}

void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, short *pDataBuffer, double dEffecValue)
{
	T_RT_CalEffecValue_Quick<short, short, __int64>(pDataPos, pDataBuffer, dEffecValue);
}

void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, long *pDataBuffer, double dEffecValue)
{
	T_RT_CalEffecValue_Quick<long, long, __int64>(pDataPos, pDataBuffer, dEffecValue);
}

void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, float *pDataBuffer, double dEffecValue)
{
	T_RT_CalEffecValue_Quick<float, float, double>(pDataPos, pDataBuffer, dEffecValue);
}

void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, double *pDataBuffer, double dEffecValue)
{
	T_RT_CalEffecValue_Quick<double, double, double>(pDataPos, pDataBuffer, dEffecValue);
}

