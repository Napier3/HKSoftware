#pragma once

#include "..\MemBuffer\CycleMemBufferMngr.h"
#include "CycleMemBuffer.h"

class CCycleMemBufferMngr :	public CCycleMemBufferMngr
{
public:
	CCycleMemBufferMngr(void);
	virtual ~CCycleMemBufferMngr(void);
	
	long m_dwMaxBufferLength;  //��󻺳�����С
	long m_dwCurrBufferLength; //��ǰ��������С
	long m_dwBufferNeedParse;  //��Ҫ�����Ļ�������С

public:
	POS m_posCurr;           //��ǰ���ʵĻ���������λ��

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
