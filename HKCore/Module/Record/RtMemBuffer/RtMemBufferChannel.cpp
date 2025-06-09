// RtMemBufferChannel.cpp: implementation of the CRtMemBufferChannel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "RtMemBufferChannel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtMemBufferChannel::CRtMemBufferChannel()
{
	m_pRecordMemBuffer			= NULL;
	m_pSpyMemBuffer				= NULL;
	m_pLRecordMemBuffer			= NULL;
	m_pLSpyMemBuffer			= NULL;
	m_nSpyMemBufferCopyBeginPos = 0;
	m_nID                       = 0;
	m_nChannelType				= 0;
	m_bUseRecordBuffer			= TRUE;
	m_bUseSpyBuffer				= TRUE;
	SetRtChTypeNormal();
}

CRtMemBufferChannel::~CRtMemBufferChannel()
{
	if (m_pRecordMemBuffer != NULL)
	{
		delete m_pRecordMemBuffer;
	}

	if (m_pSpyMemBuffer != NULL)
	{
		delete m_pSpyMemBuffer;
	}
	
	if (m_pLRecordMemBuffer != NULL)
	{
		delete m_pLRecordMemBuffer;
	}
	
	if (m_pLSpyMemBuffer != NULL)
	{
		delete m_pLSpyMemBuffer;
	}
	
	m_pRecordMemBuffer			= NULL;
	m_pSpyMemBuffer				= NULL;
	m_pLRecordMemBuffer			= NULL;
	m_pLSpyMemBuffer			= NULL;
}

void CRtMemBufferChannel::SetRecordMemBufferLength(long nBufferLen)
{
	FreeRecordBuffer();
	
	if (nBufferLen>0 && m_bUseRecordBuffer)
	{
		if (IsRtChTypeNormal())
		{
			ASSERT (m_pRecordMemBuffer != NULL);
			
			//m_pRecordMemBuffer = new CMemBuffer_UShort();
			m_pRecordMemBuffer->SetBufferLength(nBufferLen);
		}
		else
		{
			ASSERT (m_pLRecordMemBuffer != NULL);
			
			//m_pLRecordMemBuffer = new CMemBuffer_Long();
			m_pLRecordMemBuffer->SetBufferLength(nBufferLen);
		}
	}
}

void CRtMemBufferChannel::SetSpyMemBufferLength(long nBufferLen)
{
	FreeSpyBuffer();
	
	if (nBufferLen>0 && m_bUseSpyBuffer)
	{
		if (IsRtChTypeNormal() || IsRtChTypeGPS())
		{
			ASSERT (m_pSpyMemBuffer != NULL);

			//m_pSpyMemBuffer = new CMemBuffer_UShort();
			m_pSpyMemBuffer->SetBufferLength(nBufferLen);
		}
		else
		{
			ASSERT (m_pLSpyMemBuffer != NULL);
			
			//m_pLSpyMemBuffer = new CComplexBuffer_Long();
			m_pLSpyMemBuffer->SetBufferLength(nBufferLen);
		}
	}
}

void CRtMemBufferChannel::SetMemBufferLength(long nRecordBufferLen, long nSpyMemBufferLen)
{
	SetRecordMemBufferLength(nRecordBufferLen);
	SetSpyMemBufferLength(nSpyMemBufferLen);
}

void CRtMemBufferChannel::AttachRecordMemBuffer(CMemBuffer_UShort *pMemBuffer)
{
	m_pRecordMemBuffer = pMemBuffer;
}

void CRtMemBufferChannel::AttachSpyMemBuffer(CMemBuffer_UShort *pMemBuffer)
{
	m_pSpyMemBuffer = pMemBuffer;
}

unsigned short* CRtMemBufferChannel::GetSpyMemBuffer2() 
{
	return m_pSpyMemBuffer == NULL  ? NULL : m_pSpyMemBuffer->GetBuffer(); 
}

long* CRtMemBufferChannel::GetSpyMemBuffer2_long() 
{
	return m_pSpyMemBuffer == NULL  ? NULL : m_pSpyMemBuffer->GetBuffer_long(); 
}

CMemBufferInterface* CRtMemBufferChannel::GetSpyMemBuffer()  
{ 
	return m_pSpyMemBuffer;  
}

unsigned short* CRtMemBufferChannel::GetRecordMemBuffer2() 
{  
	return m_pRecordMemBuffer == NULL   ? NULL : m_pRecordMemBuffer->GetBuffer();  
}

long* CRtMemBufferChannel::GetRecordMemBuffer2_long() 
{  
	return m_pRecordMemBuffer == NULL   ? NULL : m_pRecordMemBuffer->GetBuffer_long();  
}

CMemBufferInterface* CRtMemBufferChannel::GetRecordMemBuffer()  
{
	return m_pRecordMemBuffer; 
}


void CRtMemBufferChannel::FreeSpyBuffer()
{
	if (m_pSpyMemBuffer)
	{
		m_pSpyMemBuffer->FreeBuffer();
	}

	if (m_pLSpyMemBuffer)
	{
		m_pLSpyMemBuffer->FreeBuffer();
	}
}

void CRtMemBufferChannel::FreeRecordBuffer()
{
	if (m_pRecordMemBuffer) 
	{	
		m_pRecordMemBuffer->FreeBuffer();
	}

	if (m_pLRecordMemBuffer) 
	{	
		m_pLRecordMemBuffer->FreeBuffer();
	}
	
	m_nSpyMemBufferCopyBeginPos = 0;
}

long CRtMemBufferChannel::CopySpyMemBufferToRecordBuffer(long nGap)
{
	if (m_pRecordMemBuffer != NULL)
	{
		return m_pRecordMemBuffer->CopyBuffer(m_pSpyMemBuffer, m_nSpyMemBufferCopyBeginPos, nGap);
	}

	if (m_pLRecordMemBuffer != NULL)
	{
		return m_pLRecordMemBuffer->CopyBuffer(m_pLSpyMemBuffer, m_nSpyMemBufferCopyBeginPos, nGap);
	}

	return 0;
}


void CRtMemBufferChannel::Init(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID)
{
	m_strID = strChannelID;
	SetUseRecordBuffer(bUseRecordBuf);
	SetUseSpyBuffer(bUseSpyBuf);
	
	Init();

	if (m_pRecordMemBuffer != NULL)
	{
		m_pRecordMemBuffer->m_strBufferID = strRecordBufID;
		m_pRecordMemBuffer->m_nMemBufferTypeID = CreateMemBufferTypeIDRecordUShort();
	}

	if (m_pSpyMemBuffer != NULL)
	{
		m_pSpyMemBuffer->m_strBufferID = strSpyBufID;
		m_pSpyMemBuffer->m_nMemBufferTypeID = MEMBUFFER_TYPE_ID_NONE;
	}
	
	if (m_pLRecordMemBuffer != NULL)
	{
		m_pLRecordMemBuffer->m_strBufferID = strRecordBufID;
		m_pLRecordMemBuffer->m_nMemBufferTypeID = CreateMemBufferTypeIDRecordFloat();
	}
	
	if (m_pLSpyMemBuffer != NULL)
	{
		m_pLSpyMemBuffer->m_strBufferID = strSpyBufID;
		m_pLSpyMemBuffer->m_nMemBufferTypeID = MEMBUFFER_TYPE_ID_NONE;
	}
}

void CRtMemBufferChannel::Init()
{
	m_nSpyMemBufferCopyBeginPos = 0;

	if (IsRtChTypeNormal() || IsRtChTypeGPS())
	{
		if (m_pRecordMemBuffer != NULL)
		{
			m_pRecordMemBuffer->FreeBuffer();
		}

		if (m_pSpyMemBuffer != NULL)
		{
			m_pSpyMemBuffer->FreeBuffer();
		}
		
		if (m_bUseRecordBuffer && m_pRecordMemBuffer == NULL)
		{
			m_pRecordMemBuffer = new CMemBuffer_UShort();
		}
		
		if (m_bUseSpyBuffer && m_pSpyMemBuffer == NULL)
		{
			m_pSpyMemBuffer = new CMemBuffer_UShort();
		}

	}
	else
	{
		if (m_pRecordMemBuffer != NULL)
		{
			m_pRecordMemBuffer->FreeBuffer();
		}

		if (m_pSpyMemBuffer != NULL)
		{
			m_pSpyMemBuffer->FreeBuffer();
		}
		
		if (m_bUseSpyBuffer && m_pLSpyMemBuffer == NULL)
		{
#ifdef COMPLEXVARIABLE_USE_FLOAT
			m_pLSpyMemBuffer = new CComplexBuffer_Float();
#else 
			m_pLSpyMemBuffer = new CComplexBuffer_Long();
#endif
		}
		
		if (m_bUseRecordBuffer && m_pLRecordMemBuffer == NULL)
		{
#ifdef COMPLEXVARIABLE_USE_FLOAT
			m_pLRecordMemBuffer = new CMemBuffer_Float();
#else 
			m_pLRecordMemBuffer = new CMemBuffer_Long();
#endif
		}
	}
}

void CRtMemBufferChannel::SetChIndex(UINT &nChIndex)
{
	BOOL bInc = FALSE;

	if (m_bUseSpyBuffer && m_pSpyMemBuffer != NULL)
	{
		m_pSpyMemBuffer->m_nChIndex = nChIndex;
		bInc = TRUE;
	}

	if (m_bUseRecordBuffer && m_pRecordMemBuffer != NULL)
	{
		m_pRecordMemBuffer->m_nChIndex = nChIndex;
		bInc = TRUE;
	}

	if (bInc)
	{
		nChIndex++;
	}
}

void CRtMemBufferChannel::InitDataPos()
{
	m_nSpyMemBufferCopyBeginPos = 0;

	if (m_pSpyMemBuffer != NULL)
	{
		m_pSpyMemBuffer->Init();
	}

	if (m_pRecordMemBuffer != NULL)
	{
		m_pRecordMemBuffer->Init();
	}

	if (m_pLRecordMemBuffer != NULL)
	{
		m_pLRecordMemBuffer->Init();
	}
	
	if (m_pLSpyMemBuffer)
	{
		m_pLSpyMemBuffer->Init();
	}
}
