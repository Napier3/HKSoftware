// XRcdCalFilter.h: interface for the CXRcdCalFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XRcdCalFilter_H__)
#define _XRcdCalFilter_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../RtMemBuffer/MemBufferDef.h"

#define ERR_PREV_DATA_NOT_ENOUGH   -1
#define ERR_NEXT_DATA_NOT_ENOUGH  -2
#define ERR_NEXT_DATA_NO_DATA         0

#define FILTER_TYPE_RISING         1
#define FILTER_TYPE_FALLING       2
#define FILTER_TYPE_FLAT            3
#define FILTER_TYPE_PEAK            4
#define FILTER_TYPE_VALLEY         5

//用于计算前后的参与计算的点数
#define RCD_CAL_FILTER_DEFAULT_POINTS  20
#define RCD_CAL_FILTER_RATIO_SAMP_RATE  20
#define RCD_CAL_FILTER_MAX_POINTS  100

template <class Tbuf, class Tdata, class Tsum>
class CXRcdCalFilter  
{
public:
	CXRcdCalFilter()
	{
		m_nFilterType = ERR_NEXT_DATA_NO_DATA;
		m_pBuffer = NULL;
		m_pCurrPos = NULL;
		m_nSampleRate = 50000; //缺省为每周波1000点
		m_nPrevPoints = 20;
		m_nNextPoints = 20;
		m_nCurrPos = 0;
		m_vPrevSum = 0;
		m_vNextSum = 0;
		m_nPeakVallyOffsetPoints = 0;

		memset(m_vaPrevDelta, 0, sizeof(Tdata)*RCD_CAL_FILTER_MAX_POINTS);
		memset(m_vaNextDelta, 0, sizeof(Tdata)*RCD_CAL_FILTER_MAX_POINTS);
	}
	
	Tbuf *m_pBuffer;  //波形数据缓冲区
	Tbuf *m_pCurrPos; //过滤计算的位置
	PRT_MEM_BUFFER_DATA_POS m_pDataPos;

	long m_nPrevPoints;   //波形当前位置开始，前部波形数据参与计算的个数
	long m_nNextPoints;   //波形当前位置开始，后部波形数据参与计算的个数
	long m_nSampleRate;   //采样率
	long m_nCurrPos;
	Tsum m_vPrevSum, m_vNextSum;
	Tsum m_vDeltaDoor;    //差值门槛定值
	long m_nPeakVallyOffsetPoints;  //

	long m_nFilterType;    //计算得到的类型
	
	//逐点判断模式下，用于记录计算临时数据，移动到下一点进行计算时
	//能够利用上次的部分数据，提高计算的效率  暂时不实现
	Tdata m_t2PrevDataSum, m_t2NextDataSum;
	Tbuf m_tPrevData;
	Tdata m_vCurrData;
	Tdata m_vaPrevDelta[RCD_CAL_FILTER_MAX_POINTS];
	Tdata m_vaNextDelta[RCD_CAL_FILTER_MAX_POINTS];

public:
	void SetDeltaDoor(Tsum vDeltaDoor)
	{
		m_vDeltaDoor = vDeltaDoor;
	}
	void SetPeakVallyOffsetPoints(long nPoints)
	{
		m_nPeakVallyOffsetPoints = nPoints;
	}
	void ConfigRcdCal(long nSampleRate, long nPrevDataCount, long nNextPoints)
	{
		m_nSampleRate = nSampleRate;
		m_nPrevPoints = nPrevDataCount;
		m_nNextPoints = nNextPoints;

		if (nPrevDataCount < 0)
		{
			m_nPrevPoints = m_nSampleRate / RCD_CAL_FILTER_RATIO_SAMP_RATE;
			m_nPrevPoints = min(RCD_CAL_FILTER_DEFAULT_POINTS, m_nPrevPoints); 
		}

		if (nNextPoints < 0)
		{
			m_nNextPoints = m_nSampleRate / RCD_CAL_FILTER_RATIO_SAMP_RATE;//二十分之一周波
			m_nNextPoints = min(RCD_CAL_FILTER_DEFAULT_POINTS, m_nNextPoints); 
		}
	}
	void ConfigRcdCal(Tbuf *pBuffer, PRT_MEM_BUFFER_DATA_POS pBufDataPos)
	{
		m_pBuffer = pBuffer;
		m_pDataPos = pBufDataPos;
	}
	void RcdCal(Tbuf *pCurrPos)
	{
		m_pCurrPos = pCurrPos;
		m_nCurrPos = pCurrPos - m_pBuffer;
		m_vCurrData = (Tdata)(*pCurrPos);

		RcdCal();
	}
	void RcdCal(Tbuf *pBuffer, Tbuf *pCurrPos, PRT_MEM_BUFFER_DATA_POS pBufDataPos)
	{
		ConfigRcdCal(pBuffer, pBufDataPos);
		RcdCal(pCurrPos);
	}

	void RcdCalNext(Tbuf *pCurrPos)
	{//暂时不实现

	}
	BOOL IsPeak(Tbuf *pCurrPos)
	{
		Tdata *p = GetEndForZeroCal_Prev(pCurrPos);
		Tdata vCurr = *((Tdata*)pCurrPos);

		while (p < pCurrPos)
		{
			if (*p > vCurr)
			{
				return FALSE;
			}

			p++;
		}

		p = GetEndForZeroCal_Next(pCurrPos);

		while (p > pCurrPos)
		{
			if (*p > vCurr)
			{
				return FALSE;
			}

			p--;
		}

		return TRUE;
	}

	BOOL IsValley(Tbuf *pCurrPos)
	{
		Tdata *p = GetEndForZeroCal_Prev(pCurrPos);
		Tdata vCurr = *((Tdata*)pCurrPos);

		while (p < pCurrPos)
		{
			if (*p < vCurr)
			{
				return FALSE;
			}

			p++;
		}

		p = GetEndForZeroCal_Next(pCurrPos);

		while (p > pCurrPos)
		{
			if (*p < vCurr)
			{
				return FALSE;
			}

			p--;
		}

		return TRUE;
	}

	BOOL IsPeak()
	{
		if (m_nFilterType <= 0)
		{
			return FALSE;
		}

		long k = 0;

		for (k=0; k< m_nPrevPoints; k++)
		{
			if (m_vaPrevDelta[k] > 0)
			{
				return FALSE;
			}
		}

		for (k=0; k< m_nNextPoints; k++)
		{
			if (m_vaNextDelta[k] > 0)
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	BOOL IsValley()
	{
		if (m_nFilterType <= 0)
		{
			return FALSE;
		}

		long k = 0;

		for (k=0; k< m_nPrevPoints; k++)
		{
			if (m_vaPrevDelta[k] < 0)
			{
				return FALSE;
			}
		}

		for (k=0; k< m_nNextPoints; k++)
		{
			if (m_vaNextDelta[k] < 0)
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	BOOL IsRising()	{		return m_nFilterType == FILTER_TYPE_RISING;	}
	BOOL IsFalling()	{		return m_nFilterType == FILTER_TYPE_FALLING;	}
	BOOL IsFlat()		{		return m_nFilterType == FILTER_TYPE_FLAT;		}


	
private:
	void CalDelta(Tbuf *pPos, long nCount, Tdata* &pDelta)
	{
		Tbuf *pEnd = pPos + nCount;

		while (pPos < pEnd)
		{
			*pDelta = *((Tdata*)pPos) - m_vCurrData;
			pPos++;
			pDelta++;
		}
	}

	void CalSum(Tdata *pDelta, long nCount, Tsum &vSum)
	{
		vSum = 0;
		Tdata *pEnd = pDelta + nCount;

		while (pDelta < pEnd)
		{
			vSum += *pDelta;
			pDelta++;
		}
	}


	void GetPrevData()
	{
		long nCount = rt_get_points_prev(m_pDataPos, m_nCurrPos);

		if (nCount < m_nPrevPoints)
		{
			return;
		}

		m_nFilterType = FILTER_TYPE_FLAT;
		m_vPrevSum = 0;
		Tdata *pDelta = m_vaPrevDelta;

		if (m_nCurrPos == 1018)
		{
			int i = 0;
		}

		if (nCount <= m_pDataPos->nBuffer1Len)
		{//第一段区域就足够，目前只考虑单缓冲
			CalDelta(m_pBuffer + m_nCurrPos - m_nPrevPoints, m_nPrevPoints, pDelta);
		}
		else
		{
			//以下代码错误，目前只考虑单缓冲
			CalDelta(m_pBuffer + m_nCurrPos, m_pDataPos->nBuffer1Len, pDelta);
			CalDelta(m_pBuffer + m_pDataPos->nBuffer2Pos, nCount - m_pDataPos->nBuffer1Len, pDelta);
		}

		CalSum(m_vaPrevDelta, m_nPrevPoints, m_vPrevSum);
	}

	void GetNextData()
	{
		long nCount = rt_get_points_next(m_pDataPos, m_nCurrPos);

		if (nCount < m_nNextPoints)
		{
			m_nFilterType = ERR_NEXT_DATA_NOT_ENOUGH;
			return;
		}

		m_vNextSum = 0;
		Tdata *pDelta = m_vaNextDelta;

		if ((m_pDataPos->nBuffer1Pos < m_nCurrPos) && (m_nCurrPos < m_pDataPos->nBuffer1Len + m_pDataPos->nBuffer1Pos))
		{//当前位置在第一段区域
			long nNext1Len = m_pDataPos->nBuffer1Len + m_pDataPos->nBuffer1Pos - m_nCurrPos;
			nNext1Len = nNext1Len - 1;

			if (m_nNextPoints <= nNext1Len)
			{//第一段区域足够
				CalDelta(m_pCurrPos+1, m_nPrevPoints, pDelta);
			}
			else
			{
			//以下代码错误，目前只考虑单缓冲
				CalDelta(m_pCurrPos+1, nNext1Len, pDelta);//第一段区域
				CalDelta(m_pBuffer + m_pDataPos->nBuffer2Pos, m_nNextPoints - nNext1Len, pDelta);//第二段区域
			}
		}
		else
		{//当前位置在第二段区域
			CalDelta(m_pCurrPos+1, m_nNextPoints, pDelta);//第二段区域
		}

		CalSum(m_vaNextDelta, m_nNextPoints, m_vNextSum);
	}

	void RcdCal()
	{
		m_nFilterType = ERR_PREV_DATA_NOT_ENOUGH;

		GetPrevData();

		if (m_nFilterType <= 0)
		{
			return;
		}

		GetNextData();

		if (m_nFilterType <= 0)
		{
			return;
		}

		//差值，根据差值的门槛值进行判断
		Tsum vDelta = m_vNextSum - m_vPrevSum;

		if (vDelta >= m_vDeltaDoor)
		{
			m_nFilterType = FILTER_TYPE_RISING;
		}
		else if (vDelta <= -m_vDeltaDoor)
		{
			m_nFilterType = FILTER_TYPE_FALLING;
		}
		else
		{
			m_nFilterType = FILTER_TYPE_FLAT;
		}
	}

protected:
	Tdata* GetEndForZeroCal_Next(Tbuf *pPos, long nOffsetPoints)
	{
		Tdata *pEnd = (Tdata*)pPos + nOffsetPoints;
		Tdata *pEnd2 = (Tdata*)m_pBuffer + m_pDataPos->nBuffer1Len - nOffsetPoints - 1;

		if (pEnd > pEnd2)
		{
			return pEnd2;
		}
		else
		{
			return pEnd;
		}
	}
	Tdata* GetEndForZeroCal_Prev(Tbuf *pPos, long nOffsetPoints)
	{
		Tdata *pEnd = (Tdata*)pPos - nOffsetPoints;

		if (pEnd < (Tdata*)m_pBuffer)
		{
			return (Tdata*)m_pBuffer;
		}
		else
		{
			return pEnd;
		}
	}
	Tdata* GetEndForZeroCal_Next(Tbuf *pPos)
	{
		return GetEndForZeroCal_Next(pPos, m_nNextPoints);
	}
	Tdata* GetEndForZeroCal_Prev(Tbuf *pPos)
	{
		return GetEndForZeroCal_Prev(m_nNextPoints);
	}

public: 
	//////////////////////////////////////////////////////////////////////////
	//过零点
	//正 转 负 过零点   Positive to Negative
	//bUsePrev = TRUE bUseNext=TRUE  正常正弦波
	//bUsePrev = TRUE bUseNext=FALSE  正向最大突变到0
	//bUsePrev = FALSE bUseNext=TRUE  0突变到正向最大
	BOOL Is_Zero_P_to_N(Tbuf *pPos, BOOL bUsePrev, BOOL bUseNext)
	{
		if (m_vCurrData < 0)
		{//当前点为 负  ，返回FALSE
			return FALSE;
		}

		ASSERT((!bUsePrev) && (!bUseNext) );

		Tdata *p = NULL;

		if (bUsePrev)
		{//前部的数据，必须全部大于0
			p = GetEndForZeroCal_Prev(pPos);

			while (p < pPos)
			{
				if (*p <= 0)
				{//前部的数据，必须全部大于0
					return FALSE;
				}

				p++;
			}
		}

		if (bUseNext)
		{
			//后部的数据，必须全部小于0
			p = GetEndForZeroCal_Next(pPos);

			while (p > pPos)
			{
				if (*p >= 0)
				{//后部的数据，必须全部小于0
					return FALSE;
				}

				p--;
			}
		}

		//后续点全部为负，返回TRUE
		return TRUE;
	}

	//负 转 正 过零点  Negative  to Positive
	//bUsePrev = TRUE bUseNext=TRUE  正常正弦波
	//bUsePrev = TRUE bUseNext=FALSE  负向最大突变到0
	//bUsePrev = FALSE bUseNext=TRUE  0突变到负向最大
	BOOL Is_Zero_N_to_P(Tbuf *pPos, BOOL bUsePrev, BOOL bUseNext)
	{
		if (m_vCurrData > 0)
		{//当前点为 负  ，返回FALSE
			return FALSE;
		}

		ASSERT((!bUsePrev) && (!bUseNext) );

		Tdata *p = NULL;

		if (bUsePrev)
		{
			//前部的数据，必须全部小于0
			p = GetEndForZeroCal_Prev(pPos);

			while (p < pPos)
			{
				if (*p >= 0)
				{//前部的数据，必须全部小于0
					return FALSE;
				}

				p++;
			}
		}

		if (bUseNext)
		{
			//后部的数据，必须全部大于0
			p = GetEndForZeroCal_Next(pPos);

			while (p > pPos)
			{
				if (*p >= 0)
				{//后部的数据，必须全部大于0
					return FALSE;
				}

				p--;
			}
		}

		//后续点全部为负，返回TRUE
		return TRUE;
	}

	//////////////////////////////////////////////////////////////////////////
	//以当前点为出发点，判断是正半周波还是负半周波
	BOOL IsNextPositive(Tbuf *pPos)
	{
		Tdata *p = NULL;
		p = GetEndForZeroCal_Next(pPos);

/*
		while(p > (Tdata*)pPos)
		{
			if (*p < 0)
			{
				return FALSE;
			}

			p--;
		}
*/

		return (*p > 0);
	}
	BOOL IsNextNegative(Tbuf *pPos)
	{
		Tdata *p = NULL;
		p = GetEndForZeroCal_Next(pPos);

/*
		while(p > (Tdata*)pPos)
		{
			if (*p > 0)
			{
				return FALSE;
			}

			p--;
		}
*/

		return (*p < 0);
	}
	BOOL IsPrevPositive(Tbuf *pPos)
	{
		Tdata *p = NULL;
		p = GetEndForZeroCal_Prev(pPos);

// 		while(p < (Tdata*)pPos)
// 		{
// 			if (*p < 0)
// 			{
// 				return FALSE;
// 			}
// 
// 			p++;
// 		}

		return (*p > 0);
	}
	BOOL IsPrevNegative(Tbuf *pPos)
	{
		Tdata *p = NULL;
		p = GetEndForZeroCal_Prev(pPos);

/*
		while(p < (Tdata*)pPos)
		{
			if (*p > 0)
			{
				return FALSE;
			}

			p++;
		}
*/

		return (*p < 0);
	}

//检索峰谷值位置
	BOOL FindPeak_Next(Tbuf *pPos, long &nPos, Tdata &vPeakValue)
	{//简化版本，往后查找一个最大值位置：找到一个开始下降的位置
		Tdata *p = (Tdata*)pPos;

		if (p < (Tdata*)m_pBuffer)
		{
			p = (Tdata*)m_pBuffer;
		}

		Tdata *pEnd = GetEndForZeroCal_Next(pPos, m_nPeakVallyOffsetPoints);
		vPeakValue = *p;
		p++;

		while (p < pEnd)
		{
			if (*p >= vPeakValue)
			{//后续修改，可以增加IsPeak判断
				vPeakValue = *p;
				nPos = p - (Tdata*)m_pBuffer;
			}

			p++;
		}

		return nPos > 0;
	}
	BOOL FindPeak_Prev(Tbuf *pPos, long &nPos, Tdata &vPeakValue)
	{//简化版本，往后查找一个最大值位置：找到一个开始下降的位置
		Tdata *p = (Tdata*)pPos;

		Tdata *pEnd = GetEndForZeroCal_Prev(pPos, m_nPeakVallyOffsetPoints);
		vPeakValue = *p;
		p--;

		while (p > pEnd)
		{
			if (*p >= vPeakValue)
			{//后续修改，可以增加IsPeak判断
				vPeakValue = *p;
				nPos = p - (Tdata*)m_pBuffer;
			}

			p--;
		}

		return nPos > 0;
	}
	BOOL FindValley_Next(Tbuf *pPos, long &nPos, Tdata &vValleyValue)
	{//简化版本，往后查找一个最大值位置：找到一个开始下降的位置
		Tdata *p = (Tdata*)pPos;

		if (p < (Tdata*)m_pBuffer)
		{
			p = (Tdata*)m_pBuffer;
		}

		Tdata *pEnd = GetEndForZeroCal_Next(pPos, m_nPeakVallyOffsetPoints);
		vValleyValue = *p;

		while (p < pEnd)
		{
			if (*p <= vValleyValue)
			{//后续修改，可以增加IsValley判断
				vValleyValue = *p;
				nPos = p - (Tdata*)m_pBuffer;
			}

			p++;
		}

		return nPos > 0;
	}
	BOOL FindValley_Prev(Tbuf *pPos, long &nPos, Tdata &vValleyValue)
	{//简化版本，往后查找一个最大值位置：找到一个开始下降的位置
		Tdata *p = (Tdata*)pPos;
		Tdata *pEnd = GetEndForZeroCal_Prev(pPos, m_nPeakVallyOffsetPoints);
		vValleyValue = *p;
		p--;

		while (p > pEnd)
		{
			if (*p <= vValleyValue)
			{//后续修改，可以增加IsValley判断
				vValleyValue = *p;
				nPos = p - (Tdata*)m_pBuffer;
			}

			p--;
		}

		return nPos > 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//查找过零点  
	BOOL FindZero_Next(Tbuf *pPos, Tbuf*pEnd, Tdata vDelta, long &nRetPos)
	{//简化版本，往后查找一个最大值位置：找到一个开始下降的位置
		Tdata *p = (Tdata*)pPos;
		Tdata *pEnd2 = (Tdata*)pEnd;

		//找过零点
		if (*p > 0)
		{
			while (p < pEnd2)
			{
				if (*p <= 0)
				{//后续修改，可以增加IsValley判断
					nRetPos = p - (Tdata*)m_pBuffer;
					return TRUE;
				}

				p++;
			}
		}
		else
		{
			while (p < pEnd2)
			{
				if (*p >= 0)
				{//后续修改，可以增加IsValley判断
					nRetPos = p - (Tdata*)m_pBuffer;
					return TRUE;
				}

				p++;
			}
		}

		//找Delta点
		p = (Tdata*)pPos;
		while (p < pEnd2)
		{
			if ((abs(*(p+1) - *p) < vDelta) && (abs(*p) < vDelta))
			{//两个点的差值满足Delta，同时当前值本身要小于Delta
				nRetPos = p - (Tdata*)m_pBuffer + 1;
				return TRUE;
			}

			p++;
		}

		return FALSE;
	}
	BOOL FindZero_Prev(Tbuf *pPos, Tbuf*pEnd, Tdata vDelta, long &nRetPos)
	{//简化版本，往后查找一个最大值位置：找到一个开始下降的位置
		Tdata *p = (Tdata*)pPos;
		Tdata *pEnd2 = (Tdata*)pEnd;

		//找过零点
		if (*p > 0)
		{
			while (p > pEnd2)
			{
				if (*p <= 0)
				{//后续修改，可以增加IsValley判断
					nRetPos = p - (Tdata*)m_pBuffer;
					return TRUE;
				}

				p--;
			}
		}
		else
		{
			while (p > pEnd2)
			{
				if (*p >= 0)
				{//后续修改，可以增加IsValley判断
					nRetPos = p - (Tdata*)m_pBuffer;
					return TRUE;
				}

				p--;
			}
		}

		//找Delta点
		p = (Tdata*)pPos;

		while (p > pEnd2)
		{
			if ((abs(*(p-1) - *p) < vDelta) && (abs(*p) < vDelta))
			{//两个点的差值满足Delta，同时当前值本身要小于Delta
				nRetPos = p - (Tdata*)m_pBuffer - 1;
				return TRUE;
			}

			p--;
		}

		return FALSE;
	}
};

#endif // !defined(_XRcdCalFilter_H__)
