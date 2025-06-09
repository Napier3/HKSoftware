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

//���ڼ���ǰ��Ĳ������ĵ���
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
		m_nSampleRate = 50000; //ȱʡΪÿ�ܲ�1000��
		m_nPrevPoints = 20;
		m_nNextPoints = 20;
		m_nCurrPos = 0;
		m_vPrevSum = 0;
		m_vNextSum = 0;
		m_nPeakVallyOffsetPoints = 0;

		memset(m_vaPrevDelta, 0, sizeof(Tdata)*RCD_CAL_FILTER_MAX_POINTS);
		memset(m_vaNextDelta, 0, sizeof(Tdata)*RCD_CAL_FILTER_MAX_POINTS);
	}
	
	Tbuf *m_pBuffer;  //�������ݻ�����
	Tbuf *m_pCurrPos; //���˼����λ��
	PRT_MEM_BUFFER_DATA_POS m_pDataPos;

	long m_nPrevPoints;   //���ε�ǰλ�ÿ�ʼ��ǰ���������ݲ������ĸ���
	long m_nNextPoints;   //���ε�ǰλ�ÿ�ʼ���󲿲������ݲ������ĸ���
	long m_nSampleRate;   //������
	long m_nCurrPos;
	Tsum m_vPrevSum, m_vNextSum;
	Tsum m_vDeltaDoor;    //��ֵ�ż���ֵ
	long m_nPeakVallyOffsetPoints;  //

	long m_nFilterType;    //����õ�������
	
	//����ж�ģʽ�£����ڼ�¼������ʱ���ݣ��ƶ�����һ����м���ʱ
	//�ܹ������ϴεĲ������ݣ���߼����Ч��  ��ʱ��ʵ��
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
			m_nNextPoints = m_nSampleRate / RCD_CAL_FILTER_RATIO_SAMP_RATE;//��ʮ��֮һ�ܲ�
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
	{//��ʱ��ʵ��

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
		{//��һ��������㹻��Ŀǰֻ���ǵ�����
			CalDelta(m_pBuffer + m_nCurrPos - m_nPrevPoints, m_nPrevPoints, pDelta);
		}
		else
		{
			//���´������Ŀǰֻ���ǵ�����
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
		{//��ǰλ���ڵ�һ������
			long nNext1Len = m_pDataPos->nBuffer1Len + m_pDataPos->nBuffer1Pos - m_nCurrPos;
			nNext1Len = nNext1Len - 1;

			if (m_nNextPoints <= nNext1Len)
			{//��һ�������㹻
				CalDelta(m_pCurrPos+1, m_nPrevPoints, pDelta);
			}
			else
			{
			//���´������Ŀǰֻ���ǵ�����
				CalDelta(m_pCurrPos+1, nNext1Len, pDelta);//��һ������
				CalDelta(m_pBuffer + m_pDataPos->nBuffer2Pos, m_nNextPoints - nNext1Len, pDelta);//�ڶ�������
			}
		}
		else
		{//��ǰλ���ڵڶ�������
			CalDelta(m_pCurrPos+1, m_nNextPoints, pDelta);//�ڶ�������
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

		//��ֵ�����ݲ�ֵ���ż�ֵ�����ж�
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
	//�����
	//�� ת �� �����   Positive to Negative
	//bUsePrev = TRUE bUseNext=TRUE  �������Ҳ�
	//bUsePrev = TRUE bUseNext=FALSE  �������ͻ�䵽0
	//bUsePrev = FALSE bUseNext=TRUE  0ͻ�䵽�������
	BOOL Is_Zero_P_to_N(Tbuf *pPos, BOOL bUsePrev, BOOL bUseNext)
	{
		if (m_vCurrData < 0)
		{//��ǰ��Ϊ ��  ������FALSE
			return FALSE;
		}

		ASSERT((!bUsePrev) && (!bUseNext) );

		Tdata *p = NULL;

		if (bUsePrev)
		{//ǰ�������ݣ�����ȫ������0
			p = GetEndForZeroCal_Prev(pPos);

			while (p < pPos)
			{
				if (*p <= 0)
				{//ǰ�������ݣ�����ȫ������0
					return FALSE;
				}

				p++;
			}
		}

		if (bUseNext)
		{
			//�󲿵����ݣ�����ȫ��С��0
			p = GetEndForZeroCal_Next(pPos);

			while (p > pPos)
			{
				if (*p >= 0)
				{//�󲿵����ݣ�����ȫ��С��0
					return FALSE;
				}

				p--;
			}
		}

		//������ȫ��Ϊ��������TRUE
		return TRUE;
	}

	//�� ת �� �����  Negative  to Positive
	//bUsePrev = TRUE bUseNext=TRUE  �������Ҳ�
	//bUsePrev = TRUE bUseNext=FALSE  �������ͻ�䵽0
	//bUsePrev = FALSE bUseNext=TRUE  0ͻ�䵽�������
	BOOL Is_Zero_N_to_P(Tbuf *pPos, BOOL bUsePrev, BOOL bUseNext)
	{
		if (m_vCurrData > 0)
		{//��ǰ��Ϊ ��  ������FALSE
			return FALSE;
		}

		ASSERT((!bUsePrev) && (!bUseNext) );

		Tdata *p = NULL;

		if (bUsePrev)
		{
			//ǰ�������ݣ�����ȫ��С��0
			p = GetEndForZeroCal_Prev(pPos);

			while (p < pPos)
			{
				if (*p >= 0)
				{//ǰ�������ݣ�����ȫ��С��0
					return FALSE;
				}

				p++;
			}
		}

		if (bUseNext)
		{
			//�󲿵����ݣ�����ȫ������0
			p = GetEndForZeroCal_Next(pPos);

			while (p > pPos)
			{
				if (*p >= 0)
				{//�󲿵����ݣ�����ȫ������0
					return FALSE;
				}

				p--;
			}
		}

		//������ȫ��Ϊ��������TRUE
		return TRUE;
	}

	//////////////////////////////////////////////////////////////////////////
	//�Ե�ǰ��Ϊ�����㣬�ж��������ܲ����Ǹ����ܲ�
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

//�������ֵλ��
	BOOL FindPeak_Next(Tbuf *pPos, long &nPos, Tdata &vPeakValue)
	{//�򻯰汾���������һ�����ֵλ�ã��ҵ�һ����ʼ�½���λ��
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
			{//�����޸ģ���������IsPeak�ж�
				vPeakValue = *p;
				nPos = p - (Tdata*)m_pBuffer;
			}

			p++;
		}

		return nPos > 0;
	}
	BOOL FindPeak_Prev(Tbuf *pPos, long &nPos, Tdata &vPeakValue)
	{//�򻯰汾���������һ�����ֵλ�ã��ҵ�һ����ʼ�½���λ��
		Tdata *p = (Tdata*)pPos;

		Tdata *pEnd = GetEndForZeroCal_Prev(pPos, m_nPeakVallyOffsetPoints);
		vPeakValue = *p;
		p--;

		while (p > pEnd)
		{
			if (*p >= vPeakValue)
			{//�����޸ģ���������IsPeak�ж�
				vPeakValue = *p;
				nPos = p - (Tdata*)m_pBuffer;
			}

			p--;
		}

		return nPos > 0;
	}
	BOOL FindValley_Next(Tbuf *pPos, long &nPos, Tdata &vValleyValue)
	{//�򻯰汾���������һ�����ֵλ�ã��ҵ�һ����ʼ�½���λ��
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
			{//�����޸ģ���������IsValley�ж�
				vValleyValue = *p;
				nPos = p - (Tdata*)m_pBuffer;
			}

			p++;
		}

		return nPos > 0;
	}
	BOOL FindValley_Prev(Tbuf *pPos, long &nPos, Tdata &vValleyValue)
	{//�򻯰汾���������һ�����ֵλ�ã��ҵ�һ����ʼ�½���λ��
		Tdata *p = (Tdata*)pPos;
		Tdata *pEnd = GetEndForZeroCal_Prev(pPos, m_nPeakVallyOffsetPoints);
		vValleyValue = *p;
		p--;

		while (p > pEnd)
		{
			if (*p <= vValleyValue)
			{//�����޸ģ���������IsValley�ж�
				vValleyValue = *p;
				nPos = p - (Tdata*)m_pBuffer;
			}

			p--;
		}

		return nPos > 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//���ҹ����  
	BOOL FindZero_Next(Tbuf *pPos, Tbuf*pEnd, Tdata vDelta, long &nRetPos)
	{//�򻯰汾���������һ�����ֵλ�ã��ҵ�һ����ʼ�½���λ��
		Tdata *p = (Tdata*)pPos;
		Tdata *pEnd2 = (Tdata*)pEnd;

		//�ҹ����
		if (*p > 0)
		{
			while (p < pEnd2)
			{
				if (*p <= 0)
				{//�����޸ģ���������IsValley�ж�
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
				{//�����޸ģ���������IsValley�ж�
					nRetPos = p - (Tdata*)m_pBuffer;
					return TRUE;
				}

				p++;
			}
		}

		//��Delta��
		p = (Tdata*)pPos;
		while (p < pEnd2)
		{
			if ((abs(*(p+1) - *p) < vDelta) && (abs(*p) < vDelta))
			{//������Ĳ�ֵ����Delta��ͬʱ��ǰֵ����ҪС��Delta
				nRetPos = p - (Tdata*)m_pBuffer + 1;
				return TRUE;
			}

			p++;
		}

		return FALSE;
	}
	BOOL FindZero_Prev(Tbuf *pPos, Tbuf*pEnd, Tdata vDelta, long &nRetPos)
	{//�򻯰汾���������һ�����ֵλ�ã��ҵ�һ����ʼ�½���λ��
		Tdata *p = (Tdata*)pPos;
		Tdata *pEnd2 = (Tdata*)pEnd;

		//�ҹ����
		if (*p > 0)
		{
			while (p > pEnd2)
			{
				if (*p <= 0)
				{//�����޸ģ���������IsValley�ж�
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
				{//�����޸ģ���������IsValley�ж�
					nRetPos = p - (Tdata*)m_pBuffer;
					return TRUE;
				}

				p--;
			}
		}

		//��Delta��
		p = (Tdata*)pPos;

		while (p > pEnd2)
		{
			if ((abs(*(p-1) - *p) < vDelta) && (abs(*p) < vDelta))
			{//������Ĳ�ֵ����Delta��ͬʱ��ǰֵ����ҪС��Delta
				nRetPos = p - (Tdata*)m_pBuffer - 1;
				return TRUE;
			}

			p--;
		}

		return FALSE;
	}
};

#endif // !defined(_XRcdCalFilter_H__)
