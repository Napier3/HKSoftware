#pragma once

#include "..\MemBuffer\CycleMemBufferMngr.h"
#include "CycleMemBuffer.h"

class CCycleMemBufferMngr :	public CCycleMemBufferMngr
{
public:
	CCycleMemBufferMngr(void);
	virtual ~CCycleMemBufferMngr(void);
	
	long m_dwMaxBufferLength;  //最大缓冲区大小
	long m_dwCurrBufferLength; //当前缓冲区大小
	long m_dwBufferNeedParse;  //需要解析的缓冲区大小

public:
	POS m_posCurr;           //当前访问的缓冲区对象位置

public:

	virtual CCycleMemBuffer* NewCycleMemBuffer()
	{
		return new CCycleMemBuffer();
	}

	CCycleMemBuffer* AddBuffer(const BYTE *pBuffer, long nLen, BOOL bAddToTail);
	BOOL HasBufferNeedParse();
	CCycleMemBuffer* GetBufferNeedParse();
	void FrearsedBuffer();
	void OffsetBufferPos(long nOffset);
	CCycleMemBuffer* GetCurrBuffer()	{	return (CCycleMemBuffer*)GetAt(m_posCurr);	}
	long GetUnparseBufferLen();
	void SetMaxBufferLength(long nLen)		{	m_dwMaxBufferLength = nLen;	}
	void SetParsedLength(long nLen);

	void FreeBuffer(POS posFrom, POS posTo);
private:
	long m_nBufferParseLength;
	BOOL m_bParsedFlag;
};
