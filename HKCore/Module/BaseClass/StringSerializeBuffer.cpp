// StringSerializeBuffer.cpp: implementation of the CStringSerializeBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringSerializeBuffer.h"
//#include "..\AtlBaseClass\AtlFile.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const long CStringSerializeBuffer::DEFAULT_BUFF_LENGTH = 512;
	
CStringSerializeBuffer::CStringSerializeBuffer()
{
	Init();
}

CStringSerializeBuffer::~CStringSerializeBuffer()
{
	FreeBuff();
}

void CStringSerializeBuffer::Init()
{
	m_pchData = NULL;
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
	m_nBufferLength = 0;
}

int  CStringSerializeBuffer::GetBufferLength()
{
	return 	m_nBufferLength;
}

void CStringSerializeBuffer::ResetBufferPointer()
{
	m_lpBufCur = m_pchData;
}

long CStringSerializeBuffer::Append_ASCII(const CString &strData)
{
#ifdef _UNICODE
	int nLen = strData.GetLength();
#else
	int nLen = strData.GetLength();
#endif

	if (m_lpBufCur + nLen <= m_lpBufMax) 
	{
#ifdef _UNICODE
		nLen = CString_to_char(strData, m_lpBufCur);
#else
        strcpy((char*)m_lpBufCur, strData.GetString());
#endif
		m_lpBufCur += nLen;
	}
	else
	{
		throw(-1);
	}

	return nLen;
}

 void CStringSerializeBuffer::StringEnd()
 {
	 if (m_lpBufCur <= m_lpBufMax) 
	 {
		*m_lpBufCur = 0;
	 }
	 else
	 {
		 *(m_lpBufMax-1) = 0;
	 }
 }

//»º³åÇø·½·¨

long CStringSerializeBuffer::String(const CString &strData)
{
	*this << strData;
	return (m_lpBufCur - m_pchData);
}

long CStringSerializeBuffer::String(BSTR strData)
{
	*this << strData;
	return (m_lpBufCur - m_pchData);
}

long CStringSerializeBuffer::String(CString *pstrData)
{
	*this >> *pstrData;
	return 0;
}

long CStringSerializeBuffer::String(BSTR *strData)
{
	*this >> strData;
	return 0;
}

BOOL CStringSerializeBuffer::SetBufferLength(int nLen)	
{	
	m_nBufferLength = nLen;	
	return TRUE;
}

void CStringSerializeBuffer::FreeBuff()
{
	if (m_pchData != NULL)
	{
		delete m_pchData;
		m_pchData = NULL;
	}

	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
}

BOOL CStringSerializeBuffer::AllocBuffer(long lExpandPercent)
{
	m_nBufferLength = m_nBufferLength + m_nBufferLength * lExpandPercent / 100;

	FreeBuff();
	m_pchData = new char[m_nBufferLength];
	m_lpBufMax = m_pchData + m_nBufferLength;
	m_lpBufCur = m_pchData;

	if (m_pchData != NULL)
	{
		memset(m_pchData,0,m_nBufferLength);
		m_lpBufCur = m_pchData;
	}

	return (m_pchData != NULL);
}
