// XMemBufferBse.cpp: implementation of the CXMemBufferBse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XMemBufferBse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXMemBufferBse::CXMemBufferBse()
{
	m_nBufferLength		= 0;	
	m_pBuffer			= NULL;
	m_bAttach           = FALSE;
}

CXMemBufferBse::~CXMemBufferBse()
{
	FreeBuffer();
}

void CXMemBufferBse::SetBufferLength(long nBufferLen, BOOL bAllocAlways)
{
	if (nBufferLen < 0)
	{
		nBufferLen = 1;
	}

	if (bAllocAlways)
	{
		FreeBuffer();
		m_nBufferLength = nBufferLen;
		m_pBuffer = new BYTE[nBufferLen+XMEMBUF_ALLOC_SIZE_EX];
	}
	else
	{
		if (nBufferLen > m_nBufferLength)
		{
			FreeBuffer();
			m_nBufferLength = nBufferLen;
			m_pBuffer = new BYTE[nBufferLen+XMEMBUF_ALLOC_SIZE_EX];
		}
	}
}

void CXMemBufferBse::SetBuffer(BYTE *pBuffer, long nLen)
{
	if (m_nBufferLength < nLen)
	{
		SetBufferLength(nLen);
	}

	memcpy(m_pBuffer, pBuffer, nLen);
}

void CXMemBufferBse::AttachBuffer(BYTE *pBuffer, long nLen)
{
	FreeBuffer();
	m_pBuffer = pBuffer;
	m_nBufferLength = nLen;
	m_bAttach = TRUE;
}

void CXMemBufferBse::AttachBuffer(CXMemBufferBse *pBuffer, BOOL bClearScr)
{
	FreeBuffer();
	m_pBuffer = pBuffer->GetBuffer();
	m_nBufferLength = pBuffer->GetBufferLength();
	m_bAttach = TRUE;

	if (bClearScr)
	{
		pBuffer->ClearBuffer();
	}
}

void CXMemBufferBse::FreeBuffer(BOOL bOnlyDeleteBuffer)
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
	}
}


long CXMemBufferBse::CopyBuffer(BYTE *pBuffer, long nLen, long nBeginPos, long nGap)
{
	if (nGap <= 1)
	{
		ASSERT (m_nBufferLength >= nLen);
		memcpy(m_pBuffer, pBuffer, nLen);
	}
	else
	{
		ASSERT(FALSE);
	}

	return 0;
}

void CXMemBufferBse::ClearBuffer()
{
	m_pBuffer = NULL;
	m_nBufferLength = 0;
}

void CXMemBufferBse::Init()
{
	m_pBuffer = NULL;
	m_nBufferLength = 0;
	m_bAttach = FALSE;
}

void CXMemBufferBse::Init(BYTE *pBuffer, long nLength)
{
	FreeBuffer(FALSE);

	SetBufferLength(nLength);
	memcpy(m_pBuffer, pBuffer, nLength);
}
