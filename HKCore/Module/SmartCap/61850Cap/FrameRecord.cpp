// FrameRecord.cpp: implementation of the CFrameRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FrameRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrameRecord::CFrameRecord()
{
	m_nProtocol = _CAP_CHTYPE_UDP;  //规约类型:_CAP_CHTYPE_UDP/TCP/SERIAL
	memset(&m_tm, 0, sizeof(TIME64)); //cap的时间
	memset(&m_ipGroup, 0, sizeof(_ETHER_CAP_IP_GROUP)); //cap的时间
	m_n64CapID = 0;   //cap id
//	memset(&m_oDataHead, 0, sizeof(DEVICEDATAHEAD)); //cap的时间
	m_nDeviceDataType = _DEVICE_DATA_EMPTY;
	m_nDataCount = 0;
 	m_oBuffer.SetBufferLength(FRAME_RECORD_BUFFER_LEN);
// 	m_pFrmBuffer = NULL;
// 	m_pFrmBuffer = new CCycleMemBuffer();
// 	m_pFrmBuffer->SetBufferLength(FRAME_RECORD_BUFFER_LEN);
//	m_nFrmBuffer = 0;
//	memset(m_pFrmBuffer, 0, FRAME_RECORD_BUFFER_LEN);
}

CFrameRecord::~CFrameRecord()
{
	//m_oBuffer.FreeBuffer();
	//delete m_pFrmBuffer;
}

void CFrameRecord::SetBuffer(CCycleMemBuffer *pBuffer)
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

void CFrameRecord::SetBuffer(BYTE *pBuffer, long nLength)
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
CFrameRecordMngr::CFrameRecordMngr()
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

CFrameRecordMngr::~CFrameRecordMngr()
{
#ifdef FRAMERECORD_USE_DWORD
	long nIndex = 0;

	for (nIndex=0; nIndex<m_nLimit; nIndex++)
	{
		CFrameRecord *p = (CFrameRecord*)m_pRecordMngr[nIndex];
		delete p;
	}

	delete m_pRecordMngr;
#endif
}

void CFrameRecordMngr::SetLimit(long nLimit)
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

void CFrameRecordMngr::CreateRecord(long nBeginIndex)
{
	for (; nBeginIndex<m_nLimit; nBeginIndex++)
	{
		CFrameRecord *pNew = new CFrameRecord();
		ASSERT (pNew != NULL);

#ifdef FRAMERECORD_USE_DWORD
		m_pRecordMngr[nBeginIndex] = (DWORD)pNew;
#else
		AddTail(pNew);
#endif
	}
}

CFrameRecord* CFrameRecordMngr::AddRecord(long &nCurrIndex)
{
	CFrameRecord *pRecord = NULL;

#ifdef FRAMERECORD_USE_DWORD
	pRecord = (CFrameRecord*)m_pRecordMngr[m_nCurrIndex];
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

CFrameRecord* CFrameRecordMngr::GetRecord(long nIndex)
{
#ifdef FRAMERECORD_USE_DWORD
	if (nIndex >= m_nCount || nIndex >= m_nLimit || nIndex < 0)
	{
		return NULL;
	}

	return (CFrameRecord*)m_pRecordMngr[nIndex];
#else
	POS pos = FindIndex(nIndex);

	if (pos != NULL)
	{
		return (CFrameRecord*)GetAt(pos);
	}
	else
	{
		return NULL;
	}
#endif
}

