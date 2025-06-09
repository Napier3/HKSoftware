#pragma once

#include "XMemBufferBse.h"

#define DEFAULT_BUFF_EXPANDLEN	1024

#define OFFSET_FROM_BEGIN	0
#define OFFSET_FROM_CUR		1
#define OFFSET_FROM_END		2


class CExpandMemBuf : public CXMemBufferBse
{
public:
	CExpandMemBuf();
	virtual ~CExpandMemBuf();

private:
	BYTE *m_pCurrPos;

public:
	virtual void Init();
	virtual void FreeBuffer(BOOL bOnlyDeleteBuffer=FALSE);

public:
	virtual BOOL AllocBuffer(long nBufLen=0,long nExpendPercent=0);
	virtual BOOL AddBufferDataLen(long nAddLen);
	virtual BOOL AppendBuffer(BYTE *pBuf,long nLen);
	virtual BOOL AppendString(const char *pBuf);

	virtual long GetDataLength()	{	return (m_pCurrPos - m_pBuffer);	}
	virtual long GetLeftDataLength()	{	return (m_pBuffer + m_nBufferLength - m_pCurrPos);	}

	virtual void PosMoveByUsedLen(long nLenUsed);
	virtual BYTE* GetDataBuffer()	{	return m_pBuffer;	}
	virtual BYTE* GetCurBuffer()	{	return m_pCurrPos;	}

	//2022-9-23  lijunqing
	void ZeroBuffer();
	
	void AddData(double &val, char ch);
	void AddData(float &val, char ch);
	void AddData(int &val, char ch);
};
