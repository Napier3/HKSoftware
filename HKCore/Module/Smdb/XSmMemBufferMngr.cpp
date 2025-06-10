#include "stdafx.h"
#include "XSmMemBufferMngr.h"


CXSmMemBufferMngr::CXSmMemBufferMngr(void)
{
	m_bWriteFinished = FALSE;
	m_pdwXSmMemBuffer = NULL;
	m_nMaxCount = 0;
	m_nCurrIndex = 0;
	m_nCurrCount = 0;
	m_n64CapIndex = 0;
	
	m_oBeginTime.nType = EP_TIME_EX_TYPE_DOUBLE;
	m_oBeginTime.dTime = 0;

	m_nCurrParseIndex = 0;  //当前解析的位置
	m_nCurrWriteIndex = 0;  //当前写入数据库的位置
	m_nCurrFreeIndex = 0;  //当前释放缓存的位置

	m_nLastParseIndex = 0;

	m_nAllocPos = 0;
}

void CXSmMemBufferMngr::ResetMngr()
{
	m_nCurrIndex = 0;
	m_nCurrCount = 0;
	m_nCurrParseIndex = 0;  //当前解析的位置
	m_nCurrWriteIndex = 0;  //当前写入数据库的位置
	m_nCurrFreeIndex = 0;  //当前释放缓存的位置

	m_nLastParseIndex = 0;

	m_nAllocPos = 0;
}

CXSmMemBufferMngr::~CXSmMemBufferMngr(void)
{
	Free();
}

void CXSmMemBufferMngr::Free()
{
	if (m_pdwXSmMemBuffer != NULL)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex<m_nMaxCount; nIndex++)
		{
			CXSmMemBuffer *pBuffer = (CXSmMemBuffer*)m_pdwXSmMemBuffer[nIndex];
			delete pBuffer;
		}

		delete m_pdwXSmMemBuffer;
		m_pdwXSmMemBuffer = NULL;
	}
}

void CXSmMemBufferMngr::SetState(long nIndexFrom, UINT nState)
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

void CXSmMemBufferMngr::FreeBuffer(long nIndexFrom)
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

void CXSmMemBufferMngr::FreeBuffer()
{
	long nBegin1 = -1, nEnd1 = -1, nBegin2 = -1, nEnd2 = -1;
	GetFreeIndexRange(nBegin1, nEnd1, nBegin2, nEnd2);

	if (nEnd1 > nBegin1)
	{
		if (!FreeBuffer(nBegin1, nEnd1))
		{
			return;
		}
	}

	if (nBegin2 >= 0)
	{
		FreeBuffer(nBegin2, nEnd2);
	}
}

void CXSmMemBufferMngr::SetState(long nBeginIndex, long nEndIndex, UINT nState)
{
	long nIndex = 0;

	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
	{
		CXSmMemBuffer *pCapBuffer = (CXSmMemBuffer*)GetFrameBuffer(nIndex);
		pCapBuffer->SetState(nState);
		m_nCurrFreeIndex = nIndex+1;
	}
}

BOOL CXSmMemBufferMngr::FreeBuffer(long nBeginIndex, long nEndIndex)
{
	if (m_pBuffer != NULL)
	{
		m_nCurrFreeIndex = nEndIndex + 1;
		return TRUE;
	}

	long nIndex = 0;

	for (nIndex=nBeginIndex; nIndex<= nEndIndex; nIndex++)
	{
		CXSmMemBuffer *pCapBuffer = (CXSmMemBuffer*)GetFrameBuffer(nIndex);

		if (!pCapBuffer->CanFreeBuffer())
		{
			return FALSE;
		}

		pCapBuffer->FreeBuffer(TRUE);
		m_nCurrFreeIndex = nIndex+1; //下一次free的位置
	}

	return TRUE;
}

void CXSmMemBufferMngr::SetMaxCount(long nMaxCount)
{
	if (m_nMaxCount == nMaxCount)
	{
		return;
	}

	m_nMaxCount = nMaxCount;
	long nLen = m_nMaxCount + 10;
	m_pdwXSmMemBuffer = new DWORD[nLen];
	ZeroMemory(m_pdwXSmMemBuffer, m_nMaxCount * sizeof(DWORD));

	long nIndex = 0;
	CXSmMemBuffer *pFrmMemBuffer = NULL;

	for (nIndex=0; nIndex<nMaxCount; nIndex++)
	{
		pFrmMemBuffer = NewMemBuffer();
		m_pdwXSmMemBuffer[nIndex] = (DWORD)pFrmMemBuffer;
	}
}

long CXSmMemBufferMngr::GetCount(long nIndexFrom)
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

void CXSmMemBufferMngr::InitXSmMemBufferMngr ()
{
	SetMaxCount(20000);//FRAME_MEM_BUFFER_COUNT);
}

CXSmMemBuffer* CXSmMemBufferMngr::AddFrameBuffer(const BYTE *pBuffer, long nLen, __int64 dTimeSnamp)
{
	if (m_oBeginTime.dTime == 0)
	{
		m_oBeginTime.n64Time = dTimeSnamp;
	}

	m_n64CapIndex++;
	CXSmMemBuffer *pFrameBuffer = GetFrameBuffer(m_nCurrIndex);
	
	if (pFrameBuffer == NULL)
	{
		pFrameBuffer = NewMemBuffer();
		m_pdwXSmMemBuffer[m_nCurrIndex] = (DWORD)pFrameBuffer;
	}

	//lijunqing 2020-6-17  一次性分配一块大的缓存，避免频繁分配
	if (m_pBuffer != NULL)
	{
		BYTE *p = AllocBuffer(nLen);
		pFrameBuffer->AttachBuffer(p, nLen);
	}
	else
	{
		pFrameBuffer->SetBufferLength(nLen);//+4);
	}

	pFrameBuffer->CopyBuffer((BYTE*)pBuffer, nLen, 0);
	//pFrameBuffer->SetDataLength(nLen);
	pFrameBuffer->m_n64TimeSnamp = dTimeSnamp;
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


void CXSmMemBufferMngr::GetParseIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
	long nCurrCount = m_nCurrCount;
	long nCurrIndex = m_nCurrIndex;

	xmem_get_cycle_range_index(m_nMaxCount, nCurrCount, nCurrIndex
		, m_nCurrParseIndex
		, nBegin1, nEnd1, nBegin2, nEnd2);
}

void CXSmMemBufferMngr::GetWriteIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
	long nCurrCount = m_nCurrCount;
	long nCurrIndex = m_nCurrIndex;

	xmem_get_cycle_range_index(m_nMaxCount, nCurrCount, nCurrIndex
		, m_nCurrWriteIndex
		, nBegin1, nEnd1, nBegin2, nEnd2);
}

void CXSmMemBufferMngr::GetFreeIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
	long nCurrCount = m_nCurrCount;
	long nCurrIndex = m_nCurrIndex;

	xmem_get_cycle_range_index(m_nMaxCount, nCurrCount, nCurrIndex
		, m_nCurrFreeIndex
		, nBegin1, nEnd1, nBegin2, nEnd2);
}

void CXSmMemBufferMngr::GetLastParseIndexRange(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
	long nCurrCount = m_nCurrCount;
	long nCurrIndex = m_nCurrIndex;

	xmem_get_cycle_range_index(m_nMaxCount, nCurrCount, nCurrIndex
		, m_nLastParseIndex
		, nBegin1, nEnd1, nBegin2, nEnd2);
}

// 
// void CXSmMemBufferMngr::SetAllBufferPased()
// {
// 	CXSmMemBuffer *pFrameBuffer = NULL;
// // 	POS pos = GetHeadPosition();
// // 
// // 	while (pos != NULL)
// // 	{
// // 		pFrameBuffer = (CXSmMemBuffer *)GetNext(pos);
// // 		pFrameBuffer->SetState(EBS_BEPARSED);
// // 		Ep_SetProtocol_ProtoType(pFrameBuffer->m_nProtocol, 0x0FF);
// // 		Ep_SetProtocol_FrameType(pFrameBuffer->m_nProtocol, 0x0FF);
// // 	}
// }
void CXSmMemBufferMngr::DeleteAll(BOOL bClear)
{
	CXSmMemBuffer *pFrameBuffer = NULL;
	long nIndex = 0;
	m_nCurrIndex = 0;

	for (nIndex=0; nIndex<m_nMaxCount; nIndex++)
	{
		CXSmMemBuffer *pBuffer = (CXSmMemBuffer*)m_pdwXSmMemBuffer[nIndex];

		if(!bClear)
		{
			pBuffer->FreeBuffer();
		}
		else
		{
			if(pBuffer->GetBuffer() != NULL && pBuffer->GetBufferLength() > 0)
			{
				ZeroMemory(pBuffer->GetBuffer(), pBuffer->GetBufferLength());

				m_nCurrParseIndex = 0;
				m_nLastParseIndex = 0;
			}
		}
	}

	m_nCurrIndex = 0;
	m_nCurrCount = 0;
}


//////////////////////////////////////////////////////////////////////////
//
BYTE* CXSmMemBufferMngr::AllocBuffer(long nLen)
{
	BYTE *pBuffer = NULL;
	
	if (m_nAllocPos + nLen >= m_nBufferLength)
	{//剩余的缓存不够分配，则回到缓冲区的首位置
		pBuffer = m_pBuffer;
		m_nAllocPos = nLen;//下一次分配的位置
	}
	else
	{
		pBuffer = m_pBuffer + m_nAllocPos;
		m_nAllocPos += nLen;//下一次分配的位置
	}

	return pBuffer;
}
