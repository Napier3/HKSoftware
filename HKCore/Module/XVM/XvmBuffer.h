
#if !defined __XvmBuffer_H_
#define __XvmBuffer_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../MemBuffer/BufferBase.h"

class CXvmBuffer : public CBufferBase
{
public:
	CXvmBuffer();
	CXvmBuffer(const CString &strBuff);
	CXvmBuffer(const BSTR &bstrBuff);
	CXvmBuffer(const char *pszBuff);
	CXvmBuffer(const CXvmBuffer *pBuffer);
	CXvmBuffer(const char *pBuffBegin,const char *pBuffEnd);
	virtual ~CXvmBuffer();

public:
	//³õÊ¼»¯»º³åÇø
	virtual void InitBuffer(long nBufferLength);
};


#endif
