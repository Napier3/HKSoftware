#include "StdAfx.h"
#include "EpCycleMemBufferMngr.h"
#include "EpCycleMemBuffer.h"


CEpCycleMemBufferMngr::CEpCycleMemBufferMngr(void)
{
	m_posCurr = NULL;
	m_dwMaxBufferLength = 1048576;//1M
	m_dwCurrBufferLength = 0;
	m_dwBufferNeedParse = 0;
	m_nBufferParseLength = 0;
	m_bParsedFlag = FALSE;
}

CEpCycleMemBufferMngr::~CEpCycleMemBufferMngr(void)
{
}

CEpCycleMemBuffer* CEpCycleMemBufferMngr::AddBuffer(const BYTE *pBuffer, long nLen, BOOL bAddToTail)
{
	if (nLen > 1024)
	{
		nLen = 1024;
	}

	CEpCycleMemBuffer *pCapBuffer = (CEpCycleMemBuffer*)CCycleMemBufferMngr::AddBuffer(pBuffer, nLen, bAddToTail);
	m_dwCurrBufferLength += nLen;
	m_dwBufferNeedParse += nLen;

	if (m_bParsedFlag)
	{
		m_dwBufferNeedParse -= m_nBufferParseLength;
		m_bParsedFlag = FALSE;
	}

	return pCapBuffer;
}

BOOL CEpCycleMemBufferMngr::HasBufferNeedParse()
{
	if (m_dwBufferNeedParse > 1048576)
	{//如果未解析的数据超过1M,跳过未解析的部分

	}

	return (m_dwBufferNeedParse > 0);
}

CEpCycleMemBuffer* CEpCycleMemBufferMngr::GetBufferNeedParse()
{
	if (m_posCurr == NULL)
	{
		m_posCurr = GetHeadPosition();
	}

	if (m_posCurr == NULL)
	{
		return NULL;
	}

	CEpCycleMemBuffer *pCurr = (CEpCycleMemBuffer*)GetAt(m_posCurr);
	POS posTail = GetTailPosition();

	if (pCurr->Ebs_BeParsed())
	{
		if (posTail != m_posCurr)
		{
			GetNext(m_posCurr);
			pCurr = (CEpCycleMemBuffer*)GetAt(m_posCurr);
		}
		else
		{
			pCurr = NULL;
		}
	}
	else if (pCurr->Ebs_SomeParsed())
	{
		if (posTail != m_posCurr)
		{
			GetNext(m_posCurr);
			CEpCycleMemBuffer *pNext = (CEpCycleMemBuffer*)GetAt(m_posCurr);
			pNext->CombineBuffer(pCurr);
			pCurr = pNext;
		}
		else
		{
			pCurr = NULL;
		}
	}

	return pCurr;
}

void CEpCycleMemBufferMngr::FreeParsedBuffer()
{
	POS pos = GetHeadPosition();
	DWORD dwLength = 0;
	POS posCurr = m_posCurr;
	POS posNext = NULL;
// 	long nCount = 0;
// 	long nTemp = m_nCount;

	while (pos != posCurr)
	{
		CEpCycleMemBuffer *pCurr = (CEpCycleMemBuffer*)GetAt(pos);

		if (! (/*pCurr->Ebs_BeParsed() &&*/ pCurr->Ebs_BeWrited() ) )
		{//被完整解析并且写入到数据库
			pCurr = (CEpCycleMemBuffer*)GetNext(pos);
			continue;
		}

		posNext = pos;
		GetNext(posNext);
		RemoveAt(pos);
		dwLength += pCurr->GetDataLength();
		delete pCurr;
		pos = posNext;
//		nCount++;
	}

//	CLogPrint::LogFormatString(LOGLEVEL_TRACE,_T("释放缓存个数【%d】-【%d】  当前缓存个数【%d】"), nCount, nTemp, m_nCount);

	m_dwCurrBufferLength -= dwLength;
}

void CEpCycleMemBufferMngr::OffsetBufferPos(long nOffset)
{
	ASSERT (m_posCurr != NULL);
	CEpCycleMemBuffer *pCurr = (CEpCycleMemBuffer*)GetAt(m_posCurr);
	m_dwBufferNeedParse -= nOffset;
	pCurr->OffsetCurrPos(nOffset);
}

long CEpCycleMemBufferMngr::GetUnparseBufferLen()
{
	if (m_bParsedFlag)
	{
		return m_dwBufferNeedParse - m_nBufferParseLength;
	}
	else
	{
		return m_dwBufferNeedParse;
	}
// 	long nLen = 0;
// 	POS pos = m_posCurr;
// 	POS posTail = GetTailPosition();
// 
// 	while (TRUE)
// 	{
// 		CEpCycleMemBuffer *p = (CEpCycleMemBuffer*)GetAt(pos);
// 		nLen += p->GetUnparseBufferLength();
// 
// 		if (pos == posTail)
// 		{
// 			break;
// 		}
// 
// 		GetNext(pos);
// 	}
// 
// 	return nLen;
}

void CEpCycleMemBufferMngr::SetParsedLength(long nLen)
{
	m_nBufferParseLength = nLen;
	m_bParsedFlag = TRUE;
}

void CEpCycleMemBufferMngr::FreeBuffer(POS posFrom, POS posTo)
{
	CEpCycleMemBuffer *pCapBuffer = NULL;
	POS pos = posFrom;

	while (TRUE)
	{
		pCapBuffer = (CEpCycleMemBuffer *)GetAt(pos);
		pCapBuffer->FreeBuffer(TRUE);

		if (pos == posTo)
		{
			break;
		}

		GetNext(pos);
	}
}

