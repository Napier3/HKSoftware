#pragma once

#include "..\MemBuffer\CycleMemBufferMngr.h"
#include "EpCycleMemBuffer.h"

class CEpCycleMemBufferMngr :	public CCycleMemBufferMngr
{
public:
	CEpCycleMemBufferMngr(void);
	virtual ~CEpCycleMemBufferMngr(void);
	
	long m_dwMaxBufferLength;  //最大缓冲区大小
	long m_dwCurrBufferLength; //当前缓冲区大小
	long m_dwBufferNeedParse;  //需要解析的缓冲区大小

public:
	POS m_posCurr;           //当前访问的缓冲区对象位置

public:

	virtual CCycleMemBuffer* NewCycleMemBuffer()
	{
		return new CEpCycleMemBuffer();
	}

	CEpCycleMemBuffer* AddBuffer(const BYTE *pBuffer, long nLen, BOOL bAddToTail);
	BOOL HasBufferNeedParse();
	CEpCycleMemBuffer* GetBufferNeedParse();
	void FreeParsedBuffer();
	void OffsetBufferPos(long nOffset);
	CEpCycleMemBuffer* GetCurrBuffer()	{	return (CEpCycleMemBuffer*)GetAt(m_posCurr);	}
	long GetUnparseBufferLen();
	void SetMaxBufferLength(long nLen)		{	m_dwMaxBufferLength = nLen;	}
	void SetParsedLength(long nLen);

	void FreeBuffer(POS posFrom, POS posTo);
private:
	long m_nBufferParseLength;
	BOOL m_bParsedFlag;
};
