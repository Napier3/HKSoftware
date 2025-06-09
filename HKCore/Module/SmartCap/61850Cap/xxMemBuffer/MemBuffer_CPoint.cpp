// MemBuffer_CPoint.cpp: implementation of the CMemBuffer_CPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MemBuffer_CPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemBuffer_CPoint::CMemBuffer_CPoint()
{
	m_nBufferLength = 0;
	m_pBuffer       = NULL;
	m_pBufferX      = NULL;
	m_pBufferY		= NULL;
	m_nCurrUseLength  = 0;
	m_dCoefY	      = 0;
	m_dOffSetY		  = 0;
	m_dCoefX	      = 0;
	m_dOffSetX		  = 0;
}

CMemBuffer_CPoint::~CMemBuffer_CPoint()
{
	DettachBuffer();
	FreeBuffer();
}

void CMemBuffer_CPoint::GetBeginAndEndPosition(CMemBuffer_Long *pBuffer, long nSrcBeginPos, long nSrcLength
													, long &nSrcBeginPos1, long &nSrcEndPos1
													, long &nSrcBeginPos2, long &nSrcEndPos2)
{
	long nBufferLength = pBuffer->GetBufferLength();
	long nDataLength   = pBuffer->GetDataLength();
	long nDataFillBeginPos = pBuffer->GetDataFillBeginPosition();
	long nEndTemp = 0;

	if (nBufferLength == nDataLength)
	{//缓冲区被填满
		if (nSrcBeginPos < 0)
		{//从最早的数据开始，往前推nSpace的数据
			nSrcBeginPos = pBuffer->GetDataFillBeginPosition();
		}
		else
		{
		}
	}
	else
	{
		if (nSrcBeginPos < 0)
		{
			nSrcBeginPos = 0;
		}
	}
	
	if (nSrcLength < 0)
	{
		nSrcLength = pBuffer->GetDataLength();
	}
	
	//初始化为异常数据
	nSrcBeginPos1 = -1;
	nSrcEndPos1   = -1;
	nSrcBeginPos2 = -1;
	nSrcEndPos2   = -1;
	
	if (nSrcLength <= 0)
	{//空数据
	}
	else
	{//有数据
		if (nDataLength < nBufferLength)
		{//数据没有填满缓冲区
			nSrcBeginPos1 = nSrcBeginPos;
			nSrcEndPos1 = nSrcBeginPos1 + nSrcLength;

			if (nSrcEndPos1 > nDataFillBeginPos)
			{
				nSrcEndPos1 = nDataFillBeginPos;
			}
		}
		else
		{//数据填满缓冲区
			if (nSrcBeginPos > nDataFillBeginPos)
			{//绘图的起始位置大于填充位置
				nSrcBeginPos1 = nSrcBeginPos;
				nEndTemp = nSrcBeginPos1 + nSrcLength;
				
				if (nEndTemp >= nDataLength)
				{
					nSrcEndPos1	  = nDataLength - 1;
					nSrcBeginPos2 = 0;
					nSrcEndPos2   = nEndTemp - nDataLength;
				}
				else
				{
					nSrcEndPos1 = nEndTemp;
				}
			}
			else
			{//起始位置小于填充位置
				nSrcBeginPos1 = nSrcBeginPos;
				nEndTemp = nSrcBeginPos1 + nSrcLength;
				
				if (nEndTemp >= nDataFillBeginPos)
				{
					nSrcEndPos1 = nDataFillBeginPos - 1;
				}
				else
				{
				}

				nSrcEndPos1 = nSrcBeginPos1 + nSrcLength;
				
				if (nSrcEndPos1 > nDataFillBeginPos)
				{
					nSrcEndPos1 = nDataFillBeginPos;
				}
			}
		}
	}
}


void CMemBuffer_CPoint::GetBeginAndEndPosition(CMemBuffer_Float *pBuffer, long nSrcBeginPos, long nSrcLength
													, long &nSrcBeginPos1, long &nSrcEndPos1
													, long &nSrcBeginPos2, long &nSrcEndPos2)
{
	if (pBuffer == NULL)
	{
		nSrcBeginPos1 = -1;
		nSrcEndPos1   = -1;
		nSrcBeginPos2 = -1;
		nSrcEndPos2   = -1;
		return;
	}

	long nBufferLength = pBuffer->GetBufferLength();
	long nDataLength   = pBuffer->GetDataLength();
	long nDataFillBeginPos = pBuffer->GetDataFillBeginPosition();
	long nEndTemp = 0;

	if (nBufferLength == nDataLength)
	{//缓冲区被填满
		if (nSrcBeginPos < 0)
		{//从最早的数据开始，往前推nSpace的数据
			nSrcBeginPos = pBuffer->GetDataFillBeginPosition();
		}
		else
		{
		}
	}
	else
	{
		if (nSrcBeginPos < 0)
		{
			nSrcBeginPos = 0;
		}
	}
	
	if (nSrcLength < 0)
	{
		nSrcLength = pBuffer->GetDataLength();
	}
	
	//初始化为异常数据
	nSrcBeginPos1 = -1;
	nSrcEndPos1   = -1;
	nSrcBeginPos2 = -1;
	nSrcEndPos2   = -1;
	
	if (nSrcLength <= 0)
	{//空数据
	}
	else
	{//有数据
		if (nDataLength < nBufferLength)
		{//数据没有填满缓冲区
			nSrcBeginPos1 = nSrcBeginPos;
			nSrcEndPos1 = nSrcBeginPos1 + nSrcLength;

			if (nSrcEndPos1 > nDataFillBeginPos)
			{
				nSrcEndPos1 = nDataFillBeginPos;
			}
		}
		else
		{//数据填满缓冲区
			if (nSrcBeginPos > nDataFillBeginPos)
			{//绘图的起始位置大于填充位置
				nSrcBeginPos1 = nSrcBeginPos;
				nEndTemp = nSrcBeginPos1 + nSrcLength;
				
				if (nEndTemp >= nDataLength)
				{
					nSrcEndPos1	  = nDataLength - 1;
					nSrcEndPos2   = nEndTemp - nDataLength;

					if (nSrcEndPos2 > 0)
					{
						nSrcBeginPos2 = 0;
					}
				}
				else
				{
					nSrcEndPos1 = nEndTemp;
				}
			}
			else
			{//起始位置小于填充位置
				nSrcBeginPos1 = nSrcBeginPos;
				nEndTemp = nSrcBeginPos1 + nSrcLength;
				
				if (nEndTemp >= nDataFillBeginPos)
				{
					nSrcEndPos1 = nDataFillBeginPos - 1;
				}
				else
				{
				}
			}
		}
	}
}


void CMemBuffer_CPoint::SetBufferLength(long nBufferLen)
{
	FreeBuffer();
	ASSERT (nBufferLen > 0);

	m_nBufferLength = nBufferLen;
	m_pBuffer = new CPoint[nBufferLen+MEMBUFFER_LENGTH_EX];
	memset(m_pBuffer, 0, sizeof(POINT) * m_nBufferLength);
}

void CMemBuffer_CPoint::AttachBufferX(CMemBuffer_Long *pBufferX)
{
	m_pBufferX = pBufferX;
}

void CMemBuffer_CPoint::AttachBufferY(CMemBuffer_Long *pBufferY)
{
	m_pBufferY = pBufferY;
}

void CMemBuffer_CPoint::AttachBuffer(CMemBuffer_Long *pBufferX, CMemBuffer_Long *pBufferY)
{
	m_pBufferX = pBufferX;
	m_pBufferY = pBufferY;
}

void CMemBuffer_CPoint::DettachBufferX()
{
	m_pBufferX = NULL;
}

void CMemBuffer_CPoint::DettachBufferY()
{
	m_pBufferY = NULL;
}

void CMemBuffer_CPoint::DettachBuffer()
{
	m_pBufferX = NULL;
	m_pBufferY = NULL;
}

void CMemBuffer_CPoint::InitValueX(double fCoef, double fOffset, CMemBuffer_Long *pBufferX, long nSrcBeginPos , long nSrcLength , long nGap)
{
	m_dCoefX = fCoef;
	m_dOffSetX = fOffset;

	long nBuffer1Begin = -1;
	long nBuffer1End = -1;
	long nBuffer2Begin = -1;
	long nBuffer2End = -1;
	
	GetBeginAndEndPosition(pBufferX, nSrcBeginPos, nSrcLength, nBuffer1Begin, nBuffer1End, nBuffer2Begin, nBuffer2End);
	
	if (nSrcLength > m_nBufferLength)
	{//确保缓冲区不要超过CPoint缓冲区大小
		nSrcLength = m_nBufferLength;
		GetBeginAndEndPosition(pBufferX, nSrcBeginPos, nSrcLength, nBuffer1Begin, nBuffer1End, nBuffer2Begin, nBuffer2End);
	}
	else
	{
	}
	
	if (nBuffer1Begin < 0)
	{//没有需要转换的缓冲区
		return;
	}
	
	CPoint *pPoint = m_pBuffer ;
	long *pSrcBufferX = pBufferX->GetBuffer();
	long *pSrcTemp = NULL;
	long *pSrcTempEnd = NULL;
	long nIndex = 0;
	long nOffset = 0;
	
	if (nBuffer1Begin >= 0)
	{
		pSrcTemp = pSrcBufferX + nBuffer1Begin;
		pSrcTempEnd = pSrcBufferX + nBuffer1End;
		
		while (pSrcTemp <= pSrcTempEnd)
		{
			long d = *pSrcTemp;
			pPoint->x = (long)(d * fCoef + fOffset);
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	if (nBuffer2Begin >= 0)
	{//=====
		//nOffset = nGap - (nBuffer1End - nBuffer1Begin + 1) % nGap - 1;
		if (nGap == 1)
		{
			nOffset = 0;
		}
		else
		{
			nOffset = nGap - (nBuffer1End - nBuffer1Begin + 1) % nGap ; 
		}

		pSrcTemp = pSrcBufferX + nBuffer2Begin + nOffset;
		pSrcTempEnd = pSrcBufferX + nBuffer2End;
		
		while (pSrcTemp <= pSrcTempEnd)
		{
			long d = *pSrcTemp;
			pPoint->x = (long)(d * fCoef + fOffset);
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	//当前使用的长度
	m_nCurrUseLength = pPoint - m_pBuffer - 1;
}

void CMemBuffer_CPoint::InitValueY(double fCoef, double fOffset, CMemBuffer_Long *pBufferY, long nSrcBeginPos, long nSrcLength, long nGap)
{
	m_dCoefY = fCoef;
	m_dOffSetY = fOffset;

	long nBuffer1Begin = -1;
	long nBuffer1End = -1;
	long nBuffer2Begin = -1;
	long nBuffer2End = -1;
	
	GetBeginAndEndPosition(pBufferY, nSrcBeginPos, nSrcLength, nBuffer1Begin, nBuffer1End, nBuffer2Begin, nBuffer2End);
	
	if (nSrcLength > m_nBufferLength)
	{//确保缓冲区不要超过CPoint缓冲区大小
		nSrcLength = m_nBufferLength;
		GetBeginAndEndPosition(pBufferY, nSrcBeginPos, nSrcLength, nBuffer1Begin, nBuffer1End, nBuffer2Begin, nBuffer2End);
	}
	else
	{
	}
	
	CalValueY(fCoef,fOffset,pBufferY,nBuffer1Begin,nBuffer1End,nBuffer2Begin,nBuffer2End,nGap);
}

void CMemBuffer_CPoint::InitValueY(double fCoef, double fOffset, CMemBuffer_Float *pBufferY, long nSrcBeginPos, long nSrcLength, long nGap)
{
	m_dCoefY = fCoef;
	m_dOffSetY = fOffset;

	long nBuffer1Begin = -1;
	long nBuffer1End = -1;
	long nBuffer2Begin = -1;
	long nBuffer2End = -1;
	
	GetBeginAndEndPosition(pBufferY, nSrcBeginPos, nSrcLength, nBuffer1Begin, nBuffer1End, nBuffer2Begin, nBuffer2End);
	
	if (nSrcLength > m_nBufferLength)
	{//确保缓冲区不要超过CPoint缓冲区大小
		nSrcLength = m_nBufferLength;
		GetBeginAndEndPosition(pBufferY, nSrcBeginPos, nSrcLength, nBuffer1Begin, nBuffer1End, nBuffer2Begin, nBuffer2End);
	}
	else
	{
	}
	
	CPoint *pPoint = m_pBuffer;
	float *pSrcBufferY = pBufferY->GetBuffer();
	float *pSrcTemp = NULL;
	float *pSrcTempEnd = NULL;
	long nIndex = 0;
	long nOffset = 0;

	
	if (nBuffer1Begin >= 0)
	{
		pSrcTemp = pSrcBufferY + nBuffer1Begin;
		pSrcTempEnd = pSrcBufferY + nBuffer1End;
		
		while (pSrcTemp </*=*/ pSrcTempEnd)//modify by qhy 2010-7-27
		{
			nIndex++;
			pPoint->y = (long)( *pSrcTemp * fCoef + fOffset);
			
			if (pPoint->y < 100)
			{
				int ii = 0;
			}
			
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	if (nBuffer2Begin >= 0)
	{//=====
	//	nOffset = nGap - (nBuffer1End - nBuffer1Begin + 1) % nGap - 1;
		if (nGap == 1)
		{
			nOffset = 0;
		}
		else
		{
			nOffset = nGap - (nBuffer1End - nBuffer1Begin + 1) % nGap ; 
		}

		pSrcTemp = pSrcBufferY + nBuffer2Begin + nOffset;
		pSrcTempEnd = pSrcBufferY + nBuffer2End;
		
		while (pSrcTemp <= pSrcTempEnd)
		{
			pPoint->y = (long)(*pSrcTemp * fCoef + fOffset);
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	//当前使用的长度
	m_nCurrUseLength = pPoint - m_pBuffer - 1;
}

void CMemBuffer_CPoint::InitValueX(double fCoef, double fOffset, CMemBuffer_Float *pBufferX, long nSrcBeginPos, long nSrcLength, long nGap)
{
	m_dCoefX = fCoef;
	m_dOffSetX = fOffset;

	long nBuffer1Begin = -1;
	long nBuffer1End = -1;
	long nBuffer2Begin = -1;
	long nBuffer2End = -1;
	
	GetBeginAndEndPosition(pBufferX, nSrcBeginPos, nSrcLength, nBuffer1Begin, nBuffer1End, nBuffer2Begin, nBuffer2End);
	
	if (nSrcLength > m_nBufferLength)
	{//确保缓冲区不要超过CPoint缓冲区大小
		nSrcLength = m_nBufferLength;
		GetBeginAndEndPosition(pBufferX, nSrcBeginPos, nSrcLength, nBuffer1Begin, nBuffer1End, nBuffer2Begin, nBuffer2End);
	}
	else
	{
	}
	
	CPoint *pPoint = m_pBuffer;
	float *pSrcBufferX = pBufferX->GetBuffer();
	float *pSrcTemp = NULL;
	float *pSrcTempEnd = NULL;
	long nIndex = 0;
	long nOffset = 0;
	
	if (nBuffer1Begin >= 0)
	{
		pSrcTemp = pSrcBufferX + nBuffer1Begin;
		pSrcTempEnd = pSrcBufferX + nBuffer1End;
		
		while (pSrcTemp <= pSrcTempEnd)
		{
			pPoint->x = (long)( *pSrcTemp * fCoef + fOffset);
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	if (nBuffer2Begin >= 0)
	{//=====
		if (nGap == 1)
		{
			nOffset = 0;
		}
		else
		{
			nOffset = nGap - (nBuffer1End - nBuffer1Begin + 1) % nGap ; 
		}

		pSrcTemp = pSrcBufferX + nBuffer2Begin + nOffset;
		pSrcTempEnd = pSrcBufferX + nBuffer2End;
		
		while (pSrcTemp <= pSrcTempEnd)
		{
			pPoint->x = (long)(*pSrcTemp * fCoef + fOffset);
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	//当前使用的长度
	m_nCurrUseLength = pPoint - m_pBuffer - 1;
}

void CMemBuffer_CPoint::InitValueXY(double fCoefX, double fOffsetX, CMemBuffer_Long *pBufferX, double fCoefY, double fOffsetY, CMemBuffer_Long *pBufferY, long nSrcBeginPos, long nSrcLength, long nGap)
{
	InitValueX(fCoefX,fOffsetX,pBufferX,nSrcBeginPos,nSrcLength,nGap);
	InitValueY(fCoefY,fOffsetY,pBufferY,nSrcBeginPos,nSrcLength,nGap);
}

void CMemBuffer_CPoint::InitValueXY(double fCoefX, double fOffsetX, double fCoefY, double fOffsetY, long nSrcBeginPos, long nSrcLength, long nGap)
{
	InitValueX(fCoefX,fOffsetX,nSrcBeginPos,nSrcLength,nGap);
	InitValueY(fCoefY,fOffsetY,nSrcBeginPos,nSrcLength,nGap);
}

void CMemBuffer_CPoint::InitValueX(double fCoef, double fOffset, long nSrcBeginPos, long nSrcLength, long nGap)
{
	InitValueX(fCoef,fOffset,m_pBufferX,nSrcBeginPos,nSrcLength,nGap);	
}

void CMemBuffer_CPoint::InitValueY(double fCoef, double fOffset, long nSrcBeginPos, long nSrcLength, long nGap)
{
	InitValueY(fCoef,fOffset,m_pBufferY,nSrcBeginPos,nSrcLength,nGap);	
}

void CMemBuffer_CPoint::FreeBuffer()
{
	if (m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}

	m_nBufferLength = 0;
	m_dCoefY	      = 0;
	m_dOffSetY		  = 0;
	m_dCoefX	      = 0;
	m_dOffSetX		  = 0;
}

void CMemBuffer_CPoint::CalValueY(double fCoef, double fOffset,CMemBuffer_Long *pSrc,long nBuffer1Begin,long nBuffer1End,long nBuffer2Begin ,long nBuffer2End , long nGap)
{
	ASSERT (nGap > 0);
	if (nBuffer1Begin < 0)
	{//没有需要转换的缓冲区
		return;
	}
	
	CPoint *pPoint = m_pBuffer;
	long *pSrcBufferY = pSrc->GetBuffer();
	long *pSrcTemp = NULL;
	long *pSrcTempEnd = NULL;
	long nIndex = 0;
	long nOffset = 0;
	
	if (nBuffer1Begin >= 0)
	{
		pSrcTemp = pSrcBufferY + nBuffer1Begin;
		pSrcTempEnd = pSrcBufferY + nBuffer1End;
		
		while (pSrcTemp <= pSrcTempEnd)
		{
			//short nVal = *pSrcTemp;
			pPoint->y = (long)( ( fCoef * (*pSrcTemp) )+ fOffset);
			//pPoint->y = (long)( nVal * fCoef + fOffset);
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	if (nBuffer2Begin >= 0)
	{//=====
	//	nOffset = nGap - (nBuffer1End - nBuffer1Begin + 1) % nGap - 1;
		if (nGap == 1)
		{
			nOffset = 0;
		}
		else
		{
			nOffset = nGap - (nBuffer1End - nBuffer1Begin + 1) % nGap ; 
		}

		pSrcTemp = pSrcBufferY + nBuffer2Begin + nOffset;
		pSrcTempEnd = pSrcBufferY + nBuffer2End;
		
		while (pSrcTemp <= pSrcTempEnd)
		{
			//short d = *pSrcTemp;
			pPoint->y = (long)( ( fCoef * (*pSrcTemp))+ fOffset);
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	//当前使用的长度
	m_nCurrUseLength = pPoint - m_pBuffer - 1;
	
}

void CMemBuffer_CPoint::CalValueY(double fCoef, double fOffset,CMemBuffer_Float *pSrc,long nBuffer1Begin,long nBuffer1End,long nBuffer2Begin ,long nBuffer2End , long nGap)
{
	ASSERT (nGap > 0);

	if (nBuffer1Begin < 0)
	{//没有需要转换的缓冲区
		return;
	}
	
	CPoint *pPoint = m_pBuffer;
	float *pSrcBufferY = pSrc->GetBuffer();
	float *pSrcTemp = NULL;
	float *pSrcTempEnd = NULL;
	long nIndex = 0;
	long nOffset = 0;
	
	if (nBuffer1Begin >= 0)
	{
		pSrcTemp = pSrcBufferY + nBuffer1Begin;
		pSrcTempEnd = pSrcBufferY + nBuffer1End;
		
		while (pSrcTemp <= pSrcTempEnd)
		{
			pPoint->y = (long)( ( fCoef * (*pSrcTemp))+ fOffset);
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	if (nBuffer2Begin >= 0)
	{//=====
		nOffset = nGap - (nBuffer1End - nBuffer1Begin + 1) % nGap - 1;
		pSrcTemp = pSrcBufferY + nBuffer2Begin + nOffset;
		pSrcTempEnd = pSrcBufferY + nBuffer2End;
		
		while (pSrcTemp <= pSrcTempEnd)
		{
			pPoint->y = (long)( ( fCoef * (*pSrcTemp) )+ fOffset);
			pSrcTemp += nGap;
			pPoint++;
		}
	}
	
	//当前使用的长度
	m_nCurrUseLength = pPoint - m_pBuffer - 1;
	
}
