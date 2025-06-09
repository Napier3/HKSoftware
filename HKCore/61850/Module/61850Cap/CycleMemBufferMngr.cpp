#include "StdAfx.h"
#include "CycleMemBufferMngr.h"
#include "CycleMemBuffer.h"


CCycleMemBufferMngr::CCycleMemBufferMngr(void)
{
	m_posCurr = NULL;
	m_dwMaxBufferLength = 1048576;//1M
	m_dwCurrBufferLength = 0;
	m_dwBufferNeedParse = 0;
	m_nBufferParseLength = 0;
	m_bParsedFlag = FALSE;
}

CCycleMemBufferMngr::~CCycleMemBufferMngr(void)
{
}

CCycleMemBuffer* CCycleMemBufferMngr::AddBuffer(const BYTE *pBuffer, long nLen, BOOL bAddToTail)
{
	if (nLen > 1024)
	{
		nLen = 1024;
	}

	CCycleMemBuffer *pCapBuffer = (CCycleMemBuffer*)CCycleMemBufferMngr::AddBuffer(pBuffer, nLen, bAddToTail);
	m_dwCurrBufferLength += nLen;
	m_dwBufferNeedParse += nLen;

	if (m_bParsedFlag)
	{
		m_dwBufferNeedParse -= m_nBufferParseLength;
		m_bParsedFlag = FALSE;
	}

	return pCapBuffer;
}

BOOL CCycleMemBufferMngr::HasBufferNeedParse()
{
	if (m_dwBufferNeedParse > 1048576)
	{//如果未解析的数据超过1M,跳过未解析的部分

	}

	return (m_dwBufferNeedParse > 0);
}

CCycleMemBuffer* CCycleMemBufferMngr::GetBufferNeedParse()
{
	if (m_posCurr == NULL)
	{
		m_posCurr = GetHeadPosition();
	}

	if (m_posCurr == NULL)
	{
		return NULL;
	}

	CCycleMemBuffer *pCurr = (CCycleMemBuffer*)GetAt(m_posCurr);
	POS posTail = GetTailPosition();

	if (pCurr->Ebs_Barsed())
	{
		if (posTail != m_posCurr)
		{
			GetNext(m_posCurr);
			pCurr = (CCycleMemBuffer*)GetAt(m_posCurr);
		}
		else
		{
			pCurr = NULL;
		}
	}
	else if (pCurr->Ebs_Somarsed())
	{
		if (posTail != m_posCurr)
		{
			GetNext(m_posCurr);
			CCycleMemBuffer *pNext = (CCycleMemBuffer*)GetAt(m_posCurr);
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

void CCycleMemBufferMngr::FrearsedBuffer()
{
	POS pos = GetHeadPosition();
	DWORD dwLength = 0;
	POS posCurr = m_posCurr;
	POS posNext = NULL;

	while (pos != posCurr)
	{
		CCycleMemBuffer *pCurr = (CCycleMemBuffer*)GetAt(pos);

		if (! (pCurr->Ebs_Barsed() && pCurr->Ebs_BeWrited() ) )
		{//被完整解析并且写入到数据库
			pCurr = (CCycleMemBuffer*)GetNext(pos);
			continue;
		}

		posNext = pos;
		GetNext(posNext);
		RemoveAt(pos);
		dwLength += pCurr->GetDataLength();
		delete pCurr;
		pos = posNext;
	}

	m_dwCurrBufferLength -= dwLength;
}

void CCycleMemBufferMngr::OffsetBufferPos(long nOffset)
{
	ASSERT (m_posCurr != NULL);
	CCycleMemBuffer *pCurr = (CCycleMemBuffer*)GetAt(m_posCurr);
	m_dwBufferNeedParse -= nOffset;
	pCurr->OffsetCurrPos(nOffset);
}

long CCycleMemBufferMngr::GetUnparseBufferLen()
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
// 		CCycleMemBuffer *p = (CCycleMemBuffer*)GetAt(pos);
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

void CCycleMemBufferMngr::SetParsedLength(long nLen)
{
	m_nBufferParseLength = nLen;
	m_bParsedFlag = TRUE;
}

void CCycleMemBufferMngr::FreeBuffer(POS posFrom, POS posTo)
{
	CCycleMemBuffer *pCapBuffer = NULL;
	POS pos = posFrom;

	while (TRUE)
	{
		pCapBuffer = (CCycleMemBuffer *)GetAt(pos);
		pCapBuffer->FreeBuffer(TRUE);

		if (pos == posTo)
		{
			break;
		}

		GetNext(pos);
	}
}

