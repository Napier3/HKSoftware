// StMemBuffer.cpp: implementation of the CMemBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemBuffer::CMemBuffer()
{
	m_nBufferLength		= 0;	
	m_nDataLength		= 0;
	m_pBuffer			= NULL;
}

CMemBuffer::~CMemBuffer()
{
	FreeBuffer();
}

void CMemBuffer::SetBufferLength(long nBufferLen)
{
	FreeBuffer();
	m_nBufferLength = nBufferLen;
	m_pBuffer = new BYTE[nBufferLen+10];
	memset(m_pBuffer, 0, nBufferLen*sizeof(BYTE));
}

void CMemBuffer::SetBuffer(BYTE *pBuffer, long nLen)
{
	if (m_nBufferLength < nLen)
	{
		SetBufferLength(nLen);
	}

	m_nDataLength = nLen;
	memcpy(m_pBuffer, pBuffer, nLen);
}

void CMemBuffer::FreeBuffer(BOOL bOnlyDeleteBuffer)
{
	if (m_pBuffer!= NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
		m_nDataLength = 0;
		m_nBufferLength = 0;
	}
}


long CMemBuffer::CopyBuffer(BYTE *pBuffer, long nLen, long nBeginPos, long nGap)
{
	if (nBeginPos < 0)
	{
		nBeginPos = 0;
	}

	long nEnd = nBeginPos + nLen;

	if (nEnd > m_nBufferLength)
	{
		return -1;
	}

	memcpy(m_pBuffer + nBeginPos, pBuffer, nLen);
	m_nDataLength += nLen;

	return nLen;
}


void CMemBuffer::ClearBuffer()
{
	m_pBuffer = NULL;
	m_nDataLength = 0;
	m_nBufferLength = 0;
}

void CMemBuffer::Init()
{
	m_nDataLength		= 0;
}

BOOL CMemBuffer::GetBuffer(BYTE *pDestBuffer, long nBeginPos, long nLen)
{
	CYCLEMEMBUFFERPOS oBufPos;
	long nDataLen = m_nDataLength;

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

//nLen = -1, 从nBeginPos到m_nDataFillBeginPos
long CMemBuffer::GetBufferPos(long nBeginPos, long nLen, long &nPos1Begin , long &nPos1End, long &nPos2Begin, long &nPos2End)
{
	if (nBeginPos >= m_nBufferLength)
	{//如果缓冲区
		nBeginPos -= m_nBufferLength;
	}

	nPos1Begin = -1;
	nPos1End   = -1;
	nPos2Begin = -1;
	nPos2End   = -1;

	if (nBeginPos >= m_nDataLength)
	{
		return -1;
	}

	long nEnd = nBeginPos + nLen;

	if (nEnd > m_nDataLength)
	{
		nLen = m_nDataLength - nBeginPos;
		nPos1Begin = nBeginPos;
		nPos1End = m_nDataLength;
		return nLen;
	}
	else
	{
		nBeginPos = nBeginPos;
		nPos1End = nBeginPos + nLen;
		return nLen;
	}
}