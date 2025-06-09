#include "stdafx.h"
#include "ExpandMemBuf.h"

CExpandMemBuf::CExpandMemBuf()
{
	Init();
}

CExpandMemBuf::~CExpandMemBuf()
{
	FreeBuffer();
}

void CExpandMemBuf::Init()
{
	CXMemBufferBse::Init();
	m_pCurrPos = NULL;
}

void CExpandMemBuf::FreeBuffer(BOOL bOnlyDeleteBuffer)
{
	CXMemBufferBse::FreeBuffer(bOnlyDeleteBuffer);

	m_pCurrPos = NULL;
}

BOOL CExpandMemBuf::AllocBuffer(long nBufLen,long nExpendPercent)
{
	if (nBufLen == 0)
	{
		nBufLen = 4096000;
	}

	long nCapacity = nBufLen + nBufLen * nExpendPercent / 100;

	SetBufferLength(nCapacity);
	m_pCurrPos = m_pBuffer;
	
	return TRUE;
}

BOOL CExpandMemBuf::AddBufferDataLen(long nAddLen)
{
	if (nAddLen == 0)
	{
		return TRUE;
	}

	long nPos = m_pCurrPos - m_pBuffer;
	long nCapacity = m_nBufferLength + nAddLen;
	BYTE *pNew = new BYTE[nCapacity];
	memcpy(pNew, m_pBuffer, m_nBufferLength);
	FreeBuffer();
	m_pBuffer = pNew;
	m_pCurrPos = pNew + nPos;
	m_nBufferLength = nCapacity;
	
	return TRUE;
}

BOOL CExpandMemBuf::AppendBuffer(BYTE *pBuf,long nLen)
{
	long nCapacity = GetLeftDataLength();

	if (nCapacity > nLen)
	{
		memcpy(m_pCurrPos,pBuf,nLen);
		m_pCurrPos = m_pCurrPos + nLen;
		return TRUE;
	}

	AddBufferDataLen(nLen);
	memcpy(m_pCurrPos,pBuf,nLen);
	m_pCurrPos = m_pCurrPos + nLen;

	return TRUE;
}

BOOL CExpandMemBuf::AppendString(const char *pBuf)
{
	return AppendBuffer((BYTE*)pBuf, strlen(pBuf));
}

void CExpandMemBuf::PosMoveByUsedLen(long nLenUsed)
{
	long nDataLen = GetDataLength();
	long nLeftLen = nDataLen - nLenUsed;
	ASSERT (nLeftLen >= 0);

	if (nLeftLen > 0)
	{
		//将剩余数据移到缓存开头
		memcpy(m_pBuffer, m_pBuffer + nLenUsed, nLeftLen);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("PosMoveByUsedLen:%d"),nLeftLen);
	}
	else
	{
		//避免出现代码错误导致小于0
		nLeftLen = 0;
	}
	
	m_pCurrPos = m_pBuffer + nLeftLen;
}

void CExpandMemBuf::ZeroBuffer()
{
	m_pCurrPos = m_pBuffer;
	memset(m_pBuffer, 0, m_nBufferLength);
}

void CExpandMemBuf::AddData(double &val, char ch)
{
	AddBufferDataLen(30);
	sprintf((char*)m_pCurrPos, "%f%c", val, ch);
	m_pCurrPos += strlen((char*)m_pCurrPos);
}

void CExpandMemBuf::AddData(float &val, char ch)
{
	AddBufferDataLen(30);
	sprintf((char*)m_pCurrPos, "%f%c", val, ch);
	m_pCurrPos += strlen((char*)m_pCurrPos);
}

void CExpandMemBuf::AddData(int &val, char ch)
{
	AddBufferDataLen(30);
	sprintf((char*)m_pCurrPos, "%d%c", val, ch);
	m_pCurrPos += strlen((char*)m_pCurrPos);
}


