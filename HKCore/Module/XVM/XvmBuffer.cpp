#include "stdafx.h"
#include "XvmBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define XVM_MENBUFFERLENEX  1024

CXvmBuffer::CXvmBuffer() 
{

}

CXvmBuffer::CXvmBuffer(const CString &strBuff)
	: CBufferBase(strBuff)
{
	
}

CXvmBuffer::CXvmBuffer(const BSTR &bstrBuff)
	: CBufferBase(bstrBuff)
{
	
}

CXvmBuffer::CXvmBuffer(const char *pszBuff)
	: CBufferBase(pszBuff)
{

}

CXvmBuffer::CXvmBuffer(const CXvmBuffer *pBuffer)
	: CBufferBase(pBuffer)
{
	
}

CXvmBuffer::CXvmBuffer(const char *pBuffBegin,const char *pBuffEnd)
	: CBufferBase(pBuffBegin, pBuffEnd)
{

}

CXvmBuffer::~CXvmBuffer()
{
	
}

void CXvmBuffer::InitBuffer(long nBufferLength)
{
	if (m_nCurrBuffLen < nBufferLength || nBufferLength == 0)
	{
		Release();
		m_nCurrBuffLen = nBufferLength + XVM_MENBUFFERLENEX;
		m_pBuffer = new char [m_nCurrBuffLen];
	}

	m_nLength = nBufferLength;
	ZeroMemory(m_pBuffer,(m_nCurrBuffLen)*sizeof(char));
	ResetPointer();
}
