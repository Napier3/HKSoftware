// MemBuffer_UnsignedShort.cpp: implementation of the CMemBuffer_UnsignedShort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemBuffer_UnsignedShort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemBuffer_UnsignedShort::CMemBuffer_UnsignedShort()
{
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
	m_pBuffer			= NULL;
	m_strBufferID		= "";
	memset(m_dwFreqZeroPosition, 0, MAX_FREQ_ZERO_POS_BUFFER*sizeof(DWORD));
	m_nFreqZeroPosCount = 0;
	m_nChIndex = -1;
	m_dCoefValue = 0;
	m_n64BeginPos = 0;
	m_n64EndPos  = 0;
	m_bBufferAttach = FALSE;
}

CMemBuffer_UnsignedShort::~CMemBuffer_UnsignedShort()
{
	FreeBuffer();
}

long CMemBuffer_UnsignedShort::CopyBuffer(CMemBufferInterface *pBuffer, long &lCopyBeginPos, long lGap)
{
	ASSERT (FALSE);
	return 0;
}

void CMemBuffer_UnsignedShort::SetBufferLength(long lBufferLen)
{
	FreeBuffer();
	m_nBufferLength = lBufferLen;
	m_pBuffer = new unsigned short[lBufferLen+MEMBUFFER_LENGTH_EX];
	memset(m_pBuffer, 0, lBufferLen*sizeof(unsigned short));
}

void CMemBuffer_UnsignedShort::AttachBuffer(unsigned short *pBuffer, long lLen)
{	
	FreeBuffer();	
	m_bBufferAttach = TRUE;
	m_pBuffer = pBuffer;
	m_nBufferLength = lLen;
	m_nDataLength = lLen;
	m_nDataFillBeginPos = lLen;
}

void CMemBuffer_UnsignedShort::AttachBuffer(CMemBuffer_UnsignedShort *pBuffer)
{
	FreeBuffer();
	m_bBufferAttach = TRUE;
	m_pBuffer = pBuffer->GetBuffer();
	m_nBufferLength = pBuffer->GetBufferLength();
}

void CMemBuffer_UnsignedShort::DettachBuffer()
{
	m_bBufferAttach = TRUE;
	m_pBuffer = NULL;
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
	m_n64BeginPos = 0; 
	m_n64EndPos   = 0;
}

long CMemBuffer_UnsignedShort::CopyBuffer(unsigned short *pBuffer, long lLen, long lGap)
{
	long lPos1Begin = -1;
	long lPos1End = -1;
	long lPos2Begin = -1;
	long lPos2End = -1;

	long lLenCopy = CalCopyBuffer(lLen, lGap, FALSE, lPos1Begin, lPos1End, lPos2Begin, lPos2End);

	if (lPos1Begin >= 0)
	{
		CopyBufferByPos(pBuffer, lPos1Begin, lPos1End, lGap);
	}

	if (lPos2Begin >= 0)
	{
		CopyBufferByPos(pBuffer+lPos1End-lPos1Begin, lPos2Begin, lPos2End, lGap);
	}

	lLenCopy = CalCopyBuffer(lLen, lGap, TRUE, lPos1Begin, lPos1End, lPos2Begin, lPos2End);
	
	return lLenCopy;
}

//pBuffer：源缓冲区
//lCopyBeginPos：源缓冲开始拷贝的位置
long CMemBuffer_UnsignedShort::CopyBuffer(CMemBuffer_UnsignedShort *pBuffer, long &lCopyBeginPos, long lGap)
{
/*
	{
		unsigned short *pTemp = pBuffer->GetBuffer();
		if (pTemp[pBuffer->GetBufferLength()-1] == 0x0087)
		{
			int i = 0;
		}
	}*/

	//确保源缓冲区的长度小于等于目标缓冲区的长度
	ASSERT(pBuffer->m_nBufferLength <= m_nBufferLength);
	if(pBuffer->m_nBufferLength > m_nBufferLength)
	{
		return -1;
	}
	
	//
	if (pBuffer->m_nDataLength == 0)
	{
		return -1;
	}
	
	long lOffset = 0;
	long lLen = 0;
	long lCopyLen = 0;
	long lCopyLenRet = 0;
	unsigned short *pTemp = NULL;

	//当前填充的位置大于开始拷贝的位置，只需要拷贝源数据的一个区域
	//即从lCopyBeginPos到pBuffer->m_nDataFillBeginPos位置
	if (pBuffer->m_nDataFillBeginPos > lCopyBeginPos)
	{
		pTemp = pBuffer->GetBuffer() + lCopyBeginPos;
		lLen = pBuffer->GetDataFillBeginPosition() - lCopyBeginPos;
		lCopyLenRet = CopyBuffer(pTemp, lLen, lGap);

		lOffset = lLen - lCopyLenRet;

//		if (lCopyLenRet == 0)
//		{
//			lCopyBeginPos = lCopyBeginPos + lCopyLenRet;//下一次拷贝的位置=当前位置+实际拷贝的长度
//		}
//		else if (lCopyBeginPos > 0)
//		{
//			lCopyBeginPos = lCopyBeginPos + lCopyLenRet - lOffset + lGap;
//		}
//		else //(lCopyBeginPos < 0)
//		{
//			lCopyBeginPos = lCopyBeginPos + lCopyLenRet - lOffset;
//		}
		
		lCopyBeginPos = lCopyBeginPos + lCopyLenRet;//下一次拷贝的位置=当前位置+实际拷贝的长度
	}
	else
	{
		//总的长度
		long nTotalLen = pBuffer->GetDataLength() - lCopyBeginPos + pBuffer->GetDataFillBeginPosition();

		//第一次拷贝，拷贝到缓冲区结束位置
		pTemp = pBuffer->GetBuffer() + lCopyBeginPos;
		lLen = pBuffer->GetDataLength() - lCopyBeginPos;
		lCopyLen = CopyBuffer(pTemp, lLen, lGap);
		lOffset = lLen - lCopyLen;  //间隔拷贝过程中到缓冲区末尾剩下的长度
		lCopyLenRet = lCopyLen;

		//第二次拷贝
		lLen = nTotalLen - lCopyLen;

		//第二次开始拷贝的起始位置
		if(lOffset > 0)
		{
			pTemp = pBuffer->GetBuffer() - lOffset + lGap;
		}
		else if (lOffset == 0)
		{
			pTemp = pBuffer->GetBuffer();
		}
		else //lOffset < 0
		{
			pTemp = pBuffer->GetBuffer() - lOffset;
		}

		//下一次拷贝的位置=第二次实际拷贝的长度
		lCopyLen = CopyBuffer(pTemp, lLen, lGap);
		lCopyBeginPos = lCopyLen - lOffset; 
		lCopyLenRet += lCopyLen;
	}

	return lCopyLenRet*lGap;
}

//第三个参数的作用是TRUE修改索引地址，FALSE时获得地址
// long CMemBuffer_UnsignedShort::CopyBuffer(long lLen, long lGap, BOOL bOffsetBuffer, long &lPos1Begin, long &lPos1End, long &lPos2Begin, long &lPos2End)
// {
// 	long lLenCopy = lLen / lGap;
// 	long nOffset = lLen - lLenCopy * lGap;
// 
// 	if (nOffset > 0)
// 	{
// 		lLenCopy++;
// 	}
// 
// 	long lEndPos = m_nDataFillBeginPos + lLenCopy; //目标缓冲区期望末位置
// 	long lLenCopy1 = 0, lLenCopy2 = 0;
// 	
// 	lPos1Begin = -1;
// 	lPos1End   = -1;
// 	lPos2Begin = -1;
// 	lPos2End   = -1;
// 	
// 	if (lEndPos < m_nBufferLength)
// 	{
// 		lPos1Begin = m_nDataFillBeginPos;
// 		lPos1End   = lEndPos;
// 		
// 		if (bOffsetBuffer)
// 		{
// 				m_nDataFillBeginPos = lEndPos;
// 		}
// 	}
// 	else 
// 	{
// 		//第一次拷贝,从m_nDataFillBeginPos到缓冲区末尾
// 		lLenCopy1 = m_nBufferLength - m_nDataFillBeginPos;
// 		lPos1Begin = m_nDataFillBeginPos;
// 		lPos1End   = m_nBufferLength;
// 		
// 		//第一次拷贝,从缓冲区开始到......
// 		lLenCopy2 = lLenCopy - lLenCopy1;
// 		lPos2Begin = 0;
// 		lPos2End   = lLenCopy2;
// 		
// 		if (bOffsetBuffer)
// 		{
// 			m_nDataFillBeginPos = lLenCopy2;
// 		}
// 		
// 	}
// 	
// 	if (bOffsetBuffer)
// 	{
// 		m_nDataLength += lLenCopy;
// 		
// 		if (m_nDataLength >= m_nBufferLength)
// 		{
// 			m_nDataLength = m_nBufferLength;
// 		}
// 	}
// 	
// 	return lLenCopy*lGap;
// }

long CMemBuffer_UnsignedShort::CopyBufferByPos(unsigned short *pBuffer, long lBeginPos, long lEndPos, long lGap)
{
	ASSERT (lBeginPos >= 0 && lEndPos >= 0 && lEndPos >= lBeginPos);
	if (!(lBeginPos >= 0 && lEndPos >= 0 && lEndPos >= lBeginPos))
	{
		return 0;
	}

	unsigned short *pDest = NULL;
	unsigned short *pDestEnd = NULL;
	unsigned short *pSrc = NULL;
	unsigned short *pSrcEnd = NULL;	

	pDest = m_pBuffer + lBeginPos;
	
	if (lGap == 1)
	{
		memcpy(pDest, pBuffer, (lEndPos - lBeginPos)*sizeof(unsigned short));
	}
	else
	{
		pDestEnd = m_pBuffer + lEndPos;
		pSrc = pBuffer;
		
		while (pDest < pDestEnd)
		{
			*pDest = *pSrc;
			pDest++;
			pSrc += lGap;
		}
	}

	m_n64BeginPos += (lEndPos - lBeginPos);//增加放入缓存的数量计数值
	return lGap * (lEndPos - lBeginPos);
}

long CMemBuffer_UnsignedShort::AddValue(unsigned short *pValue)
{
	m_pBuffer[m_nDataFillBeginPos] = *pValue;
	
	if (m_nDataFillBeginPos + 1 < m_nBufferLength)
	{
		m_nDataFillBeginPos++;
		m_nDataLength++;
	}
	else 
	{
		m_nDataFillBeginPos = 0;
		m_nDataLength = m_nBufferLength;
	}
	
	return 1;
}

long CMemBuffer_UnsignedShort::AddValue(unsigned short nValue)
{
	m_pBuffer[m_nDataFillBeginPos] = nValue;
	
	if (m_nDataFillBeginPos + 1 < m_nBufferLength)
	{
		m_nDataFillBeginPos++;
		m_n64EndPos += nValue;
	}
	else 
	{
		m_nDataFillBeginPos = 0;
		m_n64EndPos += nValue;
	}
	
	if (m_nDataLength >= m_nBufferLength)
	{
		m_nDataLength = m_nBufferLength;
	}
	else
	{
		m_nDataLength++;
	}
	
	return 1;
}

void CMemBuffer_UnsignedShort::FreeBuffer()
{	
	if (!m_bBufferAttach)
	{
		if (m_pBuffer!= NULL)
		{
			delete m_pBuffer;
		}
	}
	
	m_pBuffer = NULL;
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
	m_n64BeginPos		= 0;
	m_n64EndPos			= 0;
	m_bBufferAttach     = FALSE;
}

void CMemBuffer_UnsignedShort::Init()
{
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
	m_n64BeginPos		= 0;
	m_n64EndPos			= 0;
}

void CMemBuffer_UnsignedShort::OffsetDataFillBeginPosition(long nLen)
{
	m_nDataFillBeginPos += nLen;
	m_nDataLength += nLen;

	if (m_nDataFillBeginPos >= m_nBufferLength)
	{
		m_nDataFillBeginPos -= m_nBufferLength;
	}

	if (m_nDataLength >= m_nBufferLength)
	{
		m_nDataLength = m_nBufferLength;
	}
	
}

void CMemBuffer_UnsignedShort::ModifyLastValue(short nOffSet)
{
	long nLast = m_nDataFillBeginPos - 1;
	
	if (nLast < 0)
	{
		nLast += m_nBufferLength;
	}
	
	short nValue = m_pBuffer[nLast];
	nValue += nOffSet;
	m_pBuffer[nLast] = nValue;	
	m_n64EndPos		 += nOffSet;

}

/*
#ifdef _use_global_log_
void CMemBuffer_UnsignedShort::LOG_ShowBuffer(BOOL bShowTitle)
{
	long nIndex = 0;
	CString strTemp;
	CString strData;

	if (bShowTitle)
	{
		strTemp.Format("BufferLen=%d  DataLen=%d  DataFill=%d", m_nBufferLength, m_nDataLength, m_nDataFillBeginPos);
		LOG_WriteLawString(strTemp);
	}

	for (nIndex=0; nIndex<m_nBufferLength; nIndex++)
	{
		strTemp.Format("%04d ", m_pBuffer[nIndex]);
		strData += strTemp;
	}

	LOG_WriteLawString(strData);
}

void CMemBuffer_UnsignedShort::LOG_ShowBufferInfor()
{
	long nIndex = 0;
	CString strTemp;
	CString strData;
	
	strTemp.Format("BufferLen=%d  DataLen=%d  DataFill=%d", m_nBufferLength, m_nDataLength, m_nDataFillBeginPos);
	LOG_WriteLawString(strTemp);
}

#endif
*/

