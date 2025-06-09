// EpFrameRecord.cpp: implementation of the CEpFrameRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpFrameRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpFrameRecord::CEpFrameRecord()
{
	m_nProtocol = EP_CAP_CHTYPE_UDP;  //规约类型:EP_CAP_CHTYPE_UDP/TCP/SERIAL
	memset(&m_tm, 0, sizeof(EPTIME64)); //cap的时间
	memset(&m_ipGroup, 0, sizeof(EP_ETHER_CAP_IP_GROUP)); //cap的时间
	m_n64CapID = 0;   //cap id
//	memset(&m_oDataHead, 0, sizeof(EPDEVICEDATAHEAD)); //cap的时间
	m_nDeviceDataType = EP_DEVICE_DATA_EMPTY;
	m_nDataCount = 0;
 	m_oBuffer.SetBufferLength(FRAME_RECORD_BUFFER_LEN);
// 	m_pFrmBuffer = NULL;
// 	m_pFrmBuffer = new CCycleMemBuffer();
// 	m_pFrmBuffer->SetBufferLength(FRAME_RECORD_BUFFER_LEN);
//	m_nFrmBuffer = 0;
//	memset(m_pFrmBuffer, 0, FRAME_RECORD_BUFFER_LEN);
}

CEpFrameRecord::~CEpFrameRecord()
{
	//m_oBuffer.FreeBuffer();
	//delete m_pFrmBuffer;
}

void CEpFrameRecord::SetBuffer(CCycleMemBuffer *pBuffer)
{
	if (pBuffer == NULL)
	{
		return;
	}

	SetBuffer(pBuffer->GetBuffer(), pBuffer->GetDataLength());
	long nLen = pBuffer->GetDataLength();
	m_oBuffer.SetBufferLength(nLen);
	BYTE *pDest = m_oBuffer.GetBuffer();
	BYTE *pSrc = pBuffer->GetBuffer();
	memcpy(pDest, pSrc, nLen);
}

void CEpFrameRecord::SetBuffer(BYTE *pBuffer, long nLength)
{
	m_oBuffer.SetBufferLength(nLength, TRUE);
	BYTE *pDest = m_oBuffer.GetBuffer();
	memcpy(pDest, pBuffer, nLength);
	m_oBuffer.SetDataLength(nLength);

	//m_oBuffer.FreeBuffer();
	//m_oBuffer.SetBufferLength(nLength);
	//m_oBuffer.CopyBuffer(pBuffer, nLength, 0);
// 	long nLen = min(nLength, FRAME_RECORD_BUFFER_LEN);
// 	BYTE *pDest = m_oBuffer.GetBuffer();
// 
// 	if (pDest != NULL)
// 	{
// 		memcpy(pDest, pBuffer, nLen);
// 		m_oBuffer.SetDataLength(nLen);
// 	}
// 	m_nFrmBuffer = min(nLength, FRAME_RECORD_BUFFER_LEN);
// 	memcpy(m_pFrmBuffer, pBuffer, m_nFrmBuffer);
// 
// 	BYTE *pDest =m_pFrmBuffer->GetBuffer();
// 
// 	if (pDest != NULL)
// 	{
// 		memcpy(pDest, pBuffer, nLen);
// 		m_pFrmBuffer->SetDataLength(nLen);
// 	}
}

//////////////////////////////////////////////////////////////////////////
CEpFrameRecordMngr::CEpFrameRecordMngr()
{
#ifdef FRAMERECORD_USE_DWORD
	m_pRecordMngr = NULL;
#endif

	m_nCurrIndex = 0;
	m_nLimit = 0;
	SetLimit(FRAME_RECORD_LIMIT);
	m_nCount = 0;
	m_nCurrIndex = 0;
}

CEpFrameRecordMngr::~CEpFrameRecordMngr()
{
#ifdef FRAMERECORD_USE_DWORD
	long nIndex = 0;

	for (nIndex=0; nIndex<m_nLimit; nIndex++)
	{
		CEpFrameRecord *p = (CEpFrameRecord*)m_pRecordMngr[nIndex];
		delete p;
	}

	delete m_pRecordMngr;
#endif
}

void CEpFrameRecordMngr::SetLimit(long nLimit)
{
	if (nLimit < m_nLimit)
	{
		return;
	}

#ifdef FRAMERECORD_USE_DWORD

	DWORD *pBuffer = new DWORD[nLimit];

	if (m_pRecordMngr == NULL)
	{
		m_pRecordMngr = pBuffer;
		ZeroMemory(m_pRecordMngr, nLimit*sizeof(DWORD));
		m_nLimit = nLimit;
		CreateRecord(0);
	}
	else
	{
		memcpy(pBuffer, m_pRecordMngr, m_nLimit);
		DWORD *pTemp = m_pRecordMngr;
		m_pRecordMngr = pBuffer;
		long nPos = m_nLimit;
		m_nLimit = nLimit;
		delete pTemp;
		CreateRecord(nPos);
	}

#else
	long nPos = m_nLimit;
	m_nLimit = nLimit;
	CreateRecord(nPos);
#endif
}

void CEpFrameRecordMngr::CreateRecord(long nBeginIndex)
{
	for (; nBeginIndex<m_nLimit; nBeginIndex++)
	{
		CEpFrameRecord *pNew = new CEpFrameRecord();
		ASSERT (pNew != NULL);

#ifdef FRAMERECORD_USE_DWORD
		m_pRecordMngr[nBeginIndex] = (DWORD)pNew;
#else
		AddTail(pNew);
#endif
	}
}

CEpFrameRecord* CEpFrameRecordMngr::AddRecord(long &nCurrIndex)
{
	CEpFrameRecord *pRecord = NULL;

#ifdef FRAMERECORD_USE_DWORD
	pRecord = (CEpFrameRecord*)m_pRecordMngr[m_nCurrIndex];
#else
	pRecord = GetRecord(m_nCurrIndex);
#endif

	nCurrIndex = m_nCurrIndex;
	m_nCurrIndex++;

	if (m_nCount == m_nLimit)
	{
	}
	else
	{
		m_nCount++;

		if (m_nCount > m_nLimit)
		{
			m_nCount = m_nLimit;
		}
	}

	if (m_nCurrIndex >= m_nLimit)
	{
		m_nCurrIndex = 0;
	}

	return pRecord;
}

CEpFrameRecord* CEpFrameRecordMngr::GetRecord(long nIndex)
{
#ifdef FRAMERECORD_USE_DWORD
	if (nIndex >= m_nCount || nIndex >= m_nLimit || nIndex < 0)
	{
		return NULL;
	}

	return (CEpFrameRecord*)m_pRecordMngr[nIndex];
#else
	POS pos = FindIndex(nIndex);

	if (pos != NULL)
	{
		return (CEpFrameRecord*)GetAt(pos);
	}
	else
	{
		return NULL;
	}
#endif
}

