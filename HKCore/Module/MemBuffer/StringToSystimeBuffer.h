
#if !defined _CCStringToSystimeBuffer_h__
#define _CCStringToSystimeBuffer_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BufferBase.h"

class CStringToSystimeBuffer : public CBufferBase
{
public:
	CStringToSystimeBuffer();
	CStringToSystimeBuffer(const CString &strBuff);
	CStringToSystimeBuffer(const BSTR &bstrBuff);
	CStringToSystimeBuffer(const char *pszBuff);
	CStringToSystimeBuffer(const char *pBuffBegin,const char *pBuffEnd);

	virtual ~CStringToSystimeBuffer();
	
	SYSTEMTIME m_tmSystem;
	
public:
	//³õÊ¼»¯»º³åÇø
	virtual void InitBuffer(const CString &strBuff);
	virtual void InitBuffer(const BSTR &bstrBuff);
	virtual void InitBuffer(const char* pszBuff);
	virtual void InitBuffer(const char *pBuffBegin,const char *pBuffEnd);

	void CString_To_SystemTime(const CString &strText, SYSTEMTIME &tm);
protected:
	void CString_To_SystemTime(SYSTEMTIME &time);
};

#endif