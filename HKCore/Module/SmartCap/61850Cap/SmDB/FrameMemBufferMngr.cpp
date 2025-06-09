#include "StdAfx.h"
#include "FrameMemBufferMngr.h"


CFrameMemBufferMngr::CFrameMemBufferMngr(void)
{
	m_bWriteFinished = FALSE;
	m_pdwFrameMemBuffer = NULL;
	m_nMaxCount = 0;
	SetMaxCount(FRAME_MEM_BUFFER_COUNT);
	m_nCurrIndex = 0;
	m_nCurrCount = 0;
	m_n64CapIndex = 0;
	m_dBeginTime = 0;
}

CFrameMemBufferMngr::~CFrameMemBufferMngr(void)
{
	Free();
}

void CFrameMemBufferMngr::SetState(long nIndexFrom, UINT nState)
{
	if (m_nCurrCount == m_nMaxCount)
	{
		if (nIndexFrom < m_nCurrIndex)
		{
			SetState(nIndexFrom, m_nCurrIndex-1, nState);
		}
		else
		{
			SetState(nIndexFrom, m_nCurrCount-1, nState);
			SetState(0, m_nCurrIndex-1, nState);
		}
	}
	else
	{
		SetState(nIndexFrom, m_nCurrIndex-1, nState);
	}
}

void CFrameMemBufferMngr::FreeBuffer(long nIndexFrom)
{
	if (m_nCurrCount == m_nMaxCount)
	{
		if (nIndexFrom < m_nCurrIndex)
		{
			FreeBuffer(nIndexFrom, m_nCurrIndex-1);
		}
		else
		{
			FreeBuffer(nIndexFrom, m_nCurrCount-1);
			FreeBuffer(0, m_nCurrIndex-1);
		}
	}
	else
	{
		FreeBuffer(nIndexFrom, m_nCurrIndex-1);
	}
}

void CFrameMemBufferMngr::SetState(long nBeginIndex, long nEndIndex, UINT nState)
{
	long nIndex = 0;

	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
	{
		CFrameMemBuffer *pCapBuffer = (CFrameMemBuffer*)GetFrameBuffer(nIndex);
		pCapBuffer->SetState(nState);
	}
}

void CFrameMemBufferMngr::FreeBuffer(long nBeginIndex, long nEndIndex)
{
	long nIndex = 0;

	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
	{
		CFrameMemBuffer *pCapBuffer = (CFrameMemBuffer*)GetFrameBuffer(nIndex);
		pCapBuffer->FreeBuffer(TRUE);
	}
}

void CFrameMemBufferMngr::SetMaxCount(long nMaxCount)
{
	if (m_nMaxCount == nMaxCount)
	{
		return;
	}

	m_nMaxCount = nMaxCount;
	long nLen = m_nMaxCount + 10;
	m_pdwFrameMemBuffer = new DWORD[nLen];
	ZeroMemory(m_pdwFrameMemBuffer, m_nMaxCount * sizeof(DWORD));

	long nIndex = 0;
	CFrameMemBuffer *pFrmMemBuffer = NULL;

	for (nIndex=0; nIndex<nMaxCount; nIndex++)
	{
		pFrmMemBuffer = new CFrameMemBuffer();
		m_pdwFrameMemBuffer[nIndex] = (DWORD)pFrmMemBuffer;
	}
}

long CFrameMemBufferMngr::GetCount(long nIndexFrom)
{
	if (m_nCurrCount == m_nMaxCount)
	{
		if (m_nCurrIndex >= nIndexFrom)
		{
			return m_nCurrIndex - nIndexFrom;
		}
		else
		{
			return m_nCurrCount - nIndexFrom + m_nCurrIndex;
		}
	}
	else
	{
		return m_nCurrIndex - nIndexFrom;
	}
}

CFrameMemBuffer* CFrameMemBufferMngr::AddFrameBuffer(const struct pcap_pkthdr *header, const BYTE *pBuffer)
{
	double dTimeSnamp = header->ts.tv_sec + 1E-6 * header->ts.tv_usec;

	if (m_dBeginTime == 0)
	{
		m_dBeginTime = dTimeSnamp;
	}

	m_n64CapIndex++;
	CFrameMemBuffer *pFrameBuffer = GetFrameBuffer(m_nCurrIndex);
	
	if (pFrameBuffer == NULL)
	{
		pFrameBuffer = new CFrameMemBuffer();
		m_pdwFrameMemBuffer[m_nCurrIndex] = (DWORD)pFrameBuffer;
	}

#ifdef FrameMemBuffer_use_pkthdr
	pFrameBuffer->m_oPcapHeader = *header;
#endif

	long nLen = header->caplen;

#ifdef FrameMemBuffer_use_FrameID
	pFrameBuffer->m_n64FrameID = m_n64CapIndex;
#endif
	pFrameBuffer->SetBufferLength(nLen);//+4);
	pFrameBuffer->CopyBuffer((BYTE*)pBuffer, nLen, 0);
	//pFrameBuffer->SetDataLength(nLen);
	pFrameBuffer->m_oCapBufferItem.Time = dTimeSnamp;
	m_nCurrIndex++;

	if (m_nCurrIndex >= m_nMaxCount)
	{
		m_nCurrIndex = 0;
	}

	m_nCurrCount++;
	if (m_nCurrCount >= m_nMaxCount)
	{
		m_nCurrCount = m_nMaxCount;
	}

	return pFrameBuffer;
}
// 
// void CFrameMemBufferMngr::SetAllBufferPased()
// {
// 	CFrameMemBuffer *pFrameBuffer = NULL;
// // 	POS pos = GetHeadPosition();
// // 
// // 	while (pos != NULL)
// // 	{
// // 		pFrameBuffer = (CFrameMemBuffer *)GetNext(pos);
// // 		pFrameBuffer->SetState(EBS_BEPARSED);
// // 		Ep_SetProtocol_ProtoType(pFrameBuffer->m_nProtocol, 0x0FF);
// // 		Ep_SetProtocol_FrameType(pFrameBuffer->m_nProtocol, 0x0FF);
// // 	}
// }
void CFrameMemBufferMngr::DeleteAll()
{
	CFrameMemBuffer *pFrameBuffer = NULL;
	long nIndex = 0;
	m_nCurrIndex = 0;

	for (nIndex=0; nIndex<m_nMaxCount; nIndex++)
	{
		CFrameMemBuffer *pBuffer = (CFrameMemBuffer*)m_pdwFrameMemBuffer[nIndex];
		pBuffer->FreeBuffer();
	}

	m_nCurrIndex = 0;
	m_nCurrCount = 0;
}
