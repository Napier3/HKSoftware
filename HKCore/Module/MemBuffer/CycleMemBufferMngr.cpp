#include "StdAfx.h"
#include "CycleMemBufferMngr.h"


CCycleMemBufferMngr::CCycleMemBufferMngr(void)
{
}

CCycleMemBufferMngr::~CCycleMemBufferMngr(void)
{
}

CCycleMemBuffer* CCycleMemBufferMngr::AddBuffer(const BYTE *pBuffer, long nLen, BOOL bAddToTail)
{
	CCycleMemBuffer *pNewBuffer = NewCycleMemBuffer();
	pNewBuffer->SetBufferLength(nLen+BUFFER_LENGTH_ADD);
	pNewBuffer->CopyBuffer((BYTE*)pBuffer, nLen, 0);

	if (bAddToTail)
	{
		AddTail(pNewBuffer);
	}

	return pNewBuffer;
}

CCycleMemBuffer* CCycleMemBufferMngr::AddBuffer(const unsigned short *pBuffer, long nLen, BOOL bAddToTail)
{
	CCycleMemBuffer *pNewBuffer = NewCycleMemBuffer();
	nLen *= sizeof(unsigned short);
	pNewBuffer->SetBufferLength(nLen+BUFFER_LENGTH_ADD);
	pNewBuffer->CopyBuffer((BYTE*)pBuffer, nLen, 0);
	
	if (bAddToTail)
	{
		AddTail(pNewBuffer);
	}

	return pNewBuffer;
}

CCycleMemBuffer* CCycleMemBufferMngr::AddBuffer(const unsigned long *pBuffer, long nLen, BOOL bAddToTail)
{
	CCycleMemBuffer *pNewBuffer = NewCycleMemBuffer();
	nLen *= sizeof(unsigned long);
	pNewBuffer->SetBufferLength(nLen+BUFFER_LENGTH_ADD);
	pNewBuffer->CopyBuffer((BYTE*)pBuffer, nLen, 0);

	if (bAddToTail)
	{
		AddTail(pNewBuffer);
	}

	return pNewBuffer;
}

long CCycleMemBufferMngr::CombineBuffer(long nIndex1, long nBeginPos1, long nLen1, long nIndex2, long nBeginPos2, long nLen2, BYTE *pDestBuffer)
{
	CCycleMemBuffer *pBuffer1 = GetAtIndex(nIndex1);
	CCycleMemBuffer *pBuffer2 = GetAtIndex(nIndex2);

	if (pBuffer1 == NULL || pBuffer2 == NULL)
	{
		return 0;
	}

	return CombineBuffer(pBuffer1, nBeginPos1, nLen1, pBuffer2, nBeginPos2, nLen2, pDestBuffer);
}

long CCycleMemBufferMngr::CombineBuffer(CCycleMemBuffer *pBuffer1, long nBeginPos1, long nLen1, CCycleMemBuffer *pBuffer2, long nBeginPos2, long nLen2, BYTE *pDestBuffer)
{
	if (pBuffer1 == NULL || pBuffer2 == NULL)
	{
		return 0;
	}
	
	MakeBufferPosTrue(pBuffer1, nBeginPos1, nLen1);
	MakeBufferPosTrue(pBuffer2, nBeginPos2, nLen2);

	return CombineBuffer(pBuffer1->GetBuffer(), nBeginPos1, nLen1, pBuffer2->GetBuffer(), nBeginPos2, nLen2, pDestBuffer);
}

long CCycleMemBufferMngr::CombineBuffer(BYTE *pBuffer1, long nBeginPos1, long nLen1, BYTE *pBuffer2, long nBeginPos2, long nLen2, BYTE *pDestBuffer)
{
	if (pBuffer1 == NULL || pBuffer2 == NULL)
	{
		return 0;
	}

	if (nLen1 > 0)
	{
		memcpy(pDestBuffer, (pBuffer1+nBeginPos1), nLen1);
		pDestBuffer += nLen1;
	}

	if (nLen2 > 0)
	{
		memcpy(pDestBuffer, (pBuffer2+nBeginPos2), nLen2);
	}

	return nLen1 + nLen2;
}

void CCycleMemBufferMngr::MakeBufferPosTrue(CCycleMemBuffer *pBuffer, long &nBeginPos, long &nLen)
{
	if (nBeginPos < 0)
	{
		nBeginPos = 0;
	}

	if (nLen < 0)
	{
		nLen = pBuffer->GetDataLength() - nBeginPos;
	}

	if (nLen < 0)
	{
		nLen = 0;
	}
}