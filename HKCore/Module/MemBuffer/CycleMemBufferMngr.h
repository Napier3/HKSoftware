#pragma once

#include "CycleMemBuffer.h"
#include "../BaseClass/TLinkList.h"

class CCycleMemBufferMngr :	public CTLinkList<CCycleMemBuffer>
{
public:
	CCycleMemBufferMngr(void);
	virtual ~CCycleMemBufferMngr(void);

#define  BUFFER_LENGTH_ADD  4
public:
	virtual CCycleMemBuffer* AddBuffer(const BYTE *pBuffer, long nLen, BOOL bAddToTail);
	virtual CCycleMemBuffer* AddBuffer(const unsigned short *pBuffer, long nLen, BOOL bAddToTail);
	virtual CCycleMemBuffer* AddBuffer(const unsigned long *pBuffer, long nLen, BOOL bAddToTail);
	
	long CombineBuffer(long nIndex1, long nBeginPos1, long nLen1, long nIndex2, long nBeginPos2, long nLen2, BYTE *pDestBuffer);
	long CombineBuffer(CCycleMemBuffer *pBuffer1, long nBeginPos1, long nLen1, CCycleMemBuffer *pBuffer2, long nBeginPos2, long nLen2, BYTE *pDestBuffer);
	long CombineBuffer(BYTE *pBuffer1, long nBeginPos1, long nLen1, BYTE *pBuffer2, long nBeginPos2, long nLen2, BYTE *pDestBuffer);

	virtual CCycleMemBuffer* NewCycleMemBuffer()
	{
		return new CCycleMemBuffer();
	}

private:
	void MakeBufferPosTrue(CCycleMemBuffer *pBuffer, long &nBeginPos, long &nLen);
};
