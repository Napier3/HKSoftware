#pragma once

#include "..\MemBuffer\CycleMemBufferMngr.h"
#include "EpCycleMemBuffer.h"

class CEpCycleMemBufferMngr :	public CCycleMemBufferMngr
{
public:
	CEpCycleMemBufferMngr(void);
	virtual ~CEpCycleMemBufferMngr(void);
	
	long m_dwMaxBufferLength;  //��󻺳�����С
	long m_dwCurrBufferLength; //��ǰ��������С
	long m_dwBufferNeedParse;  //��Ҫ�����Ļ�������С

public:
	POS m_posCurr;           //��ǰ���ʵĻ���������λ��

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
