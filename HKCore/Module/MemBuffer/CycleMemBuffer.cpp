// CycleMemBuffer.cpp: implementation of the CCycleMemBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CycleMemBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCycleMemBuffer::CCycleMemBuffer()
{
	m_nBufferLength		= 0;	
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
	m_pBuffer			= NULL;
	m_bAttach           = FALSE;
}

CCycleMemBuffer::~CCycleMemBuffer()
{
	FreeBuffer();
}

void CCycleMemBuffer::SetBufferLength(long nBufferLen, BOOL bAllocAlways)
{
	if (nBufferLen < 0)
	{
		nBufferLen = 1;
	}

	if (bAllocAlways)
	{
		FreeBuffer();
		m_nBufferLength = nBufferLen;
		m_pBuffer = new BYTE[nBufferLen+10];
	}
	else
	{
		if (nBufferLen > m_nBufferLength)
		{
			FreeBuffer();
			m_nBufferLength = nBufferLen;
			m_pBuffer = new BYTE[nBufferLen+10];
		}
	}

    memset(m_pBuffer, 0, nBufferLen*sizeof(BYTE));
}

void CCycleMemBuffer::SetBuffer(BYTE *pBuffer, long nLen)
{
	if (m_nBufferLength < nLen)
	{
		SetBufferLength(nLen);
	}

	m_nDataLength = nLen;
	memcpy(m_pBuffer, pBuffer, nLen);
}


void CCycleMemBuffer::ResetOffsetDataFillBeginPosition(long nDataFillBeginPos, long nDataLength)
{
	m_nDataFillBeginPos = nDataFillBeginPos;
	m_nDataLength = nDataLength;
}

void CCycleMemBuffer::AttachBuffer(BYTE *pBuffer, long nLen)
{
	FreeBuffer();
	m_pBuffer = pBuffer;
	m_nBufferLength = nLen;
	m_bAttach = TRUE;
}

void CCycleMemBuffer::AttachBuffer(CCycleMemBuffer *pBuffer, BOOL bClearScr)
{
	FreeBuffer();
	m_pBuffer = pBuffer->GetBuffer();
	m_nBufferLength = pBuffer->GetBufferLength();
	m_bAttach = TRUE;
	m_nDataLength = pBuffer->GetDataLength();

	if (bClearScr)
	{
		pBuffer->ClearBuffer();
	}
}

long CCycleMemBuffer::AppendBuffer(BYTE *pBuffer, long nLen, long nGap)
{
	long nPos1Begin = -1;
	long nPos1End = -1;
	long nPos2Begin = -1;
	long nPos2End = -1;

	long nLenCopy = AppendBuffer(nLen, nGap, FALSE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);

	if (nPos1Begin >= 0)
	{
		AppendBufferByPos(pBuffer, nPos1Begin, nPos1End, nGap);
	}

	if (nPos2Begin >= 0)
	{
		AppendBufferByPos(pBuffer+nPos1End-nPos1Begin, nPos2Begin, nPos2End, nGap);
	}

	nLenCopy = AppendBuffer(nLen, nGap, TRUE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);
	
	return nLenCopy;
}

long CCycleMemBuffer::CopyBuffer(BYTE *pBuffer, long nLen, long nBeginPos, long nGap)
{
	long nPos1Begin = -1;
	long nPos1End = -1;
	long nPos2Begin = -1;
	long nPos2End = -1;
	GetBufferAppendPos(nBeginPos, nLen, nGap, FALSE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);

	if (nPos1Begin >= 0)
	{
		AppendBufferByPos(pBuffer, nPos1Begin, nPos1End, nGap);
	}
	
	if (nPos2Begin >= 0)
	{
		AppendBufferByPos(pBuffer+nPos1End-nPos1Begin, nPos2Begin, nPos2End, nGap);
	}

	GetBufferAppendPos(nBeginPos, nLen, nGap, TRUE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);

	return 0;
}

//pBuffer：源缓冲区
//nCopyBeginPos：源缓冲开始拷贝的位置
long CCycleMemBuffer::AppendBuffer(CCycleMemBuffer *pBuffer, long &nCopyBeginPos, long nGap)
{
	//确保源缓冲区的长度小于等于目标缓冲区的长度
	ASSERT(pBuffer->m_nBufferLength <= m_nBufferLength);

	if(pBuffer->m_nBufferLength > m_nBufferLength)
	{
		return -1;
	}
	
	if (pBuffer->m_nDataLength == 0)
	{
		return -1;
	}
	
	long nOffset = 0;
	long nLen = 0;
	long nCopyLen = 0;
	long nCopyLenRet = 0;
	BYTE *pTemp = NULL;

	//当前填充的位置大于开始拷贝的位置，只需要拷贝源数据的一个区域
	//即从nCopyBeginPos到pBuffer->m_nDataFillBeginPos位置
	if (pBuffer->m_nDataFillBeginPos > nCopyBeginPos)
	{
		pTemp = pBuffer->GetBuffer() + nCopyBeginPos;
		nLen = pBuffer->GetDataFillBeginPosition() - nCopyBeginPos;
		nCopyLenRet = AppendBuffer(pTemp, nLen, nGap);
		nOffset = nLen - nCopyLenRet;
		nCopyBeginPos = nCopyBeginPos + nCopyLenRet;//下一次拷贝的位置=当前位置+实际拷贝的长度
	}
	else
	{
		//总的长度
		long nTotanLen = pBuffer->GetDataLength() - nCopyBeginPos + pBuffer->GetDataFillBeginPosition();

		//第一次拷贝，拷贝到缓冲区结束位置
		pTemp = pBuffer->GetBuffer() + nCopyBeginPos;
		nLen = pBuffer->GetDataLength() - nCopyBeginPos;
		nCopyLen = AppendBuffer(pTemp, nLen, nGap);
		nOffset = nLen - nCopyLen;  //间隔拷贝过程中到缓冲区末尾剩下的长度
		nCopyLenRet = nCopyLen;

		//第二次拷贝
		nLen = nTotanLen - nCopyLen;

		//第二次开始拷贝的起始位置
		if(nOffset > 0)
		{
			pTemp = pBuffer->GetBuffer() - nOffset + nGap;
		}
		else if (nOffset == 0)
		{
			pTemp = pBuffer->GetBuffer();
		}
		else //nOffset < 0
		{
			pTemp = pBuffer->GetBuffer() - nOffset;
		}

		//下一次拷贝的位置=第二次实际拷贝的长度
		nCopyLen = AppendBuffer(pTemp, nLen, nGap);
		nCopyBeginPos = nCopyLen - nOffset; 
		nCopyLenRet += nCopyLen;
	}

	return nCopyLenRet*nGap;
}

//第三个参数的作用是TRUE修改索引地址，FALSE时获得地址
long CCycleMemBuffer::GetBufferAppendPos(long nBeginPos,long nLen, long nGap, BOOL bOffsetBuffer, long &nPos1Begin, long &nPos1End, long &nPos2Begin, long &nPos2End)
{
	long nLenCopy = nLen / nGap;
	long nOffset = nLen - nLenCopy * nGap;

	if (nOffset > 0)
	{
		nLenCopy++;
	}

	long nEndPos = nBeginPos + nLenCopy; //目标缓冲区期望末位置
	long nLenCopy1 = 0, nLenCopy2 = 0;
	
	nPos1Begin = -1;
	nPos1End   = -1;
	nPos2Begin = -1;
	nPos2End   = -1;
	
	if (nEndPos < m_nBufferLength)
	{
		nPos1Begin = nBeginPos;
		nPos1End   = nEndPos;
		
		if (bOffsetBuffer)
		{
				m_nDataFillBeginPos = nEndPos;
		}
	}
	else 
	{
		//第一次拷贝,从nBeginPos到缓冲区末尾
		nLenCopy1 = m_nBufferLength - nBeginPos;
		nPos1Begin = nBeginPos;
		nPos1End   = m_nBufferLength;
		
		//第一次拷贝,从缓冲区开始到......
		nLenCopy2 = nLenCopy - nLenCopy1;
		nPos2Begin = 0;
		nPos2End   = nLenCopy2;
		
		if (bOffsetBuffer)
		{
			m_nDataFillBeginPos = nLenCopy2;
		}
		
	}
	
	if (bOffsetBuffer)
	{
		m_nDataLength += nLenCopy;
		
		if (m_nDataLength >= m_nBufferLength)
		{
			m_nDataLength = m_nBufferLength;
		}
	}
	
	return nLenCopy*nGap;
}


//第三个参数的作用是TRUE修改索引地址，FALSE时获得地址
long CCycleMemBuffer::AppendBuffer(long nLen, long nGap, BOOL bOffsetBuffer, long &nPos1Begin, long &nPos1End, long &nPos2Begin, long &nPos2End)
{
	long nLenCopy = nLen / nGap;
	long nOffset = nLen - nLenCopy * nGap;

	if (nOffset > 0)
	{
		nLenCopy++;
	}

	long nEndPos = m_nDataFillBeginPos + nLenCopy; //目标缓冲区期望末位置
	long nLenCopy1 = 0, nLenCopy2 = 0;
	
	nPos1Begin = -1;
	nPos1End   = -1;
	nPos2Begin = -1;
	nPos2End   = -1;
	
	if (nEndPos < m_nBufferLength)
	{
		nPos1Begin = m_nDataFillBeginPos;
		nPos1End   = nEndPos;
		
		if (bOffsetBuffer)
		{
				m_nDataFillBeginPos = nEndPos;
		}
	}
	else 
	{
		//第一次拷贝,从m_nDataFillBeginPos到缓冲区末尾
		nLenCopy1 = m_nBufferLength - m_nDataFillBeginPos;
		nPos1Begin = m_nDataFillBeginPos;
		nPos1End   = m_nBufferLength;
		
		//第一次拷贝,从缓冲区开始到......
		nLenCopy2 = nLenCopy - nLenCopy1;
		nPos2Begin = 0;
		nPos2End   = nLenCopy2;
		
		if (bOffsetBuffer)
		{
			m_nDataFillBeginPos = nLenCopy2;
		}
		
	}
	
	if (bOffsetBuffer)
	{
		m_nDataLength += nLenCopy;
		
		if (m_nDataLength >= m_nBufferLength)
		{
			m_nDataLength = m_nBufferLength;
		}
	}
	
	return nLenCopy*nGap;
}

long CCycleMemBuffer::AppendBufferByPos(BYTE *pBuffer, long nBeginPos, long nEndPos, long nGap)
{
	ASSERT (nBeginPos >= 0 && nEndPos >= 0 && nEndPos >= nBeginPos);
	if (!(nBeginPos >= 0 && nEndPos >= 0 && nEndPos >= nBeginPos))
	{
		return 0;
	}

	BYTE *pDest = NULL;
	BYTE *pDestEnd = NULL;
	BYTE *pSrc = NULL;
	BYTE *pSrcEnd = NULL;	

	pDest = m_pBuffer + nBeginPos;
	
	if (nGap == 1)
	{
		memcpy(pDest, pBuffer, (nEndPos - nBeginPos)*sizeof(BYTE));
	}
	else
	{
		pDestEnd = m_pBuffer + nEndPos;
		pSrc = pBuffer;
		
		while (pDest < pDestEnd)
		{
			*pDest = *pSrc;
			pDest++;
			pSrc += nGap;
		}
	}

	return nGap * (nEndPos - nBeginPos);
}

/*
long CCycleMemBuffer::AddValue(BYTE *pValue)
{
	m_pBuffer[m_nDataFillBeginPos] = *pValue;
	
	if (m_nDataFillBeginPos + 1 < m_nBufferLength)
	{
		m_nDataFillBeginPos++;
	}
	else 
	{
		m_nDataFillBeginPos = 0;
	}
	
	return 1;
}

long CCycleMemBuffer::AddValue(BYTE nValue)
{
	m_pBuffer[m_nDataFillBeginPos] = nValue;
	
	if (m_nDataFillBeginPos + 1 < m_nBufferLength)
	{
		m_nDataFillBeginPos++;
	}
	else 
	{
		m_nDataFillBeginPos = 0;
	}
	
	return 1;
}
*/

void CCycleMemBuffer::FreeBuffer(BOOL bOnlyDeleteBuffer)
{
	if (!m_bAttach)
	{
		if (m_pBuffer!= NULL)
		{
			delete m_pBuffer;
			m_pBuffer = NULL;
		}
	}
	
	if (!bOnlyDeleteBuffer)
	{
		m_nBufferLength	= 0;	
		m_nDataFillBeginPos = 0;
		m_nDataLength		= 0;
	}
}

void CCycleMemBuffer::ClearBuffer()
{
	m_pBuffer = NULL;
	m_nDataLength = 0;
	m_nBufferLength = 0;
	m_nDataFillBeginPos = 0;
}

void CCycleMemBuffer::Init()
{
	m_nDataFillBeginPos = 0;
	m_nDataLength		= 0;
}

void CCycleMemBuffer::Init(BYTE *pBuffer, long nLength)
{
	FreeBuffer(FALSE);

	SetBufferLength(nLength);
	memcpy(m_pBuffer, pBuffer, nLength);
	SetDataLength(nLength);
}

void CCycleMemBuffer::OffsetDataFillBeginPosition(long nLen)
{
	if (nLen < 0)
	{
		m_nDataFillBeginPos = 0;
		m_nDataLength = 0;
	}
	else
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
}

long CCycleMemBuffer::GetDataLength(long nBeginPos)
{
	if (nBeginPos < 0)
	{
		return m_nDataLength;
	}

	if (nBeginPos >= m_nBufferLength)
	{
		nBeginPos -= m_nBufferLength;
	}
	
	long nLen = 0;

	if (m_nDataLength == m_nBufferLength)
	{
		if(m_nDataFillBeginPos >= nBeginPos)
		{
			nLen = m_nDataFillBeginPos - nBeginPos;
		}
		else
		{
			nLen = m_nDataFillBeginPos + m_nBufferLength - nBeginPos;
		}
	}
	else 
	{
		if(m_nDataFillBeginPos >= nBeginPos)
		{
			nLen = m_nDataFillBeginPos - nBeginPos;
		}
		else
		{
			nLen = 0;
		}
	}
	
	return nLen;
}

//nLen = -1, 从nBeginPos到m_nDataFillBeginPos
long CCycleMemBuffer::GetLenFromCurrToFillBeginPos(long nBeginPos)
{
	ASSERT(nBeginPos < m_nBufferLength);

	if (nBeginPos <= m_nDataFillBeginPos)
	{
		return m_nDataFillBeginPos - nBeginPos;
	}
	else
	{
		return m_nBufferLength - nBeginPos + m_nDataFillBeginPos;
	}
}

//nLen = -1, 从nBeginPos到m_nDataFillBeginPos
long CCycleMemBuffer::GetBufferPos(long nBeginPos, long nLen, long &nPos1Begin , long &nPos1End, long &nPos2Begin, long &nPos2End)
{
	if (nBeginPos >= m_nBufferLength)
	{//如果缓冲区
		nBeginPos -= m_nBufferLength;
	}

	nPos1Begin = -1;
	nPos1End   = -1;
	nPos2Begin = -1;
	nPos2End   = -1;

	if (nLen <= 0)
	{
		if (m_nDataLength == m_nBufferLength)
		{
			if(m_nDataFillBeginPos > nBeginPos)
			{
				nPos1Begin = nBeginPos;
				nPos1End = m_nDataFillBeginPos;
			}
			else if (m_nDataFillBeginPos < nBeginPos)
			{
				nPos1Begin = nBeginPos;
				nPos1End = m_nBufferLength;
				nPos2Begin = 0;
				nPos2End = m_nDataFillBeginPos;
			}
		}
		else
		{
			if (nBeginPos < m_nDataFillBeginPos)
			{
				nPos1Begin = nBeginPos;
				nPos1End = m_nDataFillBeginPos;
			}
			else
			{
				nPos1Begin = -1;
				nPos1End = 0;
			}
		}
	}
	else
	{
		if (m_nDataLength == m_nBufferLength)
		{
			nPos1Begin = nBeginPos;
			nPos1End = nBeginPos + nLen;
			
			if(m_nDataFillBeginPos > nBeginPos)
			{
				if (nPos1End >= m_nDataFillBeginPos)
				{
					nPos1End = m_nDataFillBeginPos;
				}
				else
				{
				}
			}
			else
			{
				if (nPos1End >= m_nBufferLength)
				{
					nPos1End = m_nBufferLength;
					nPos2Begin = 0;
					nPos2End = nLen - nPos1End + nPos1Begin;
					
					if (nPos2End >= m_nDataFillBeginPos)
					{
						nPos2End = m_nDataFillBeginPos;
					}
					else
					{
					}
				}
				else
				{
				}
			}
		}
		else 
		{
			if (nBeginPos < m_nDataFillBeginPos)
			{
				nPos1Begin = nBeginPos;
				nPos1End = nBeginPos + nLen;
				
				if (nPos1End >= m_nDataFillBeginPos)
				{
					nPos1End = m_nDataFillBeginPos;
				}
				else
				{
				}
			}
			else
			{
				nPos1Begin = -1;
				nPos1End = 0;
			}
		}		
	}
	
	return 0;
}

BOOL CCycleMemBuffer::GetBuffer(BYTE *pDestBuffer, long nBeginPos, long nLen)
{
	CYCLEMEMBUFFERPOS oBufPos;
	long nDataLen = GetDataLength(nBeginPos);

	GetBufferPos(nBeginPos, nDataLen, oBufPos);
	
	if (nDataLen < nLen)
	{
		return FALSE;
	}

	if (oBufPos.nBuf1EndPos - oBufPos.nBuf1BeginPos + 1 >= nLen)
	{
		memcpy(pDestBuffer, m_pBuffer+oBufPos.nBuf1BeginPos, nLen);
	}
	else
	{
		long nLen1 = oBufPos.nBuf1EndPos - oBufPos.nBuf1BeginPos+1;
		ASSERT (nLen1 > 0);

		memcpy(pDestBuffer, m_pBuffer+oBufPos.nBuf1BeginPos, nLen1);
		memcpy(pDestBuffer+nLen1, m_pBuffer, nLen - nLen1);
	}

	return TRUE;
}

