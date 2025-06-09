// IniFileBuffer.h: interface for the CIniFileBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILEBUFFER_H__5F4B1F9E_5743_4ED7_9F86_30F0B2592CD3__INCLUDED_)
#define AFX_INIFILEBUFFER_H__5F4B1F9E_5743_4ED7_9F86_30F0B2592CD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\MemBuffer\EquationBuffer.h"

class CIniFileBuffer : public CEquationBuffer  
{
public:
	CIniFileBuffer();
	CIniFileBuffer(const CString &strBuff);
	CIniFileBuffer(const char *pszBuff);
	CIniFileBuffer(const CBufferBase *pBuffer);
	CIniFileBuffer(const char *pBuffBegin,const char *pBuffEnd);
	virtual ~CIniFileBuffer();

public:
	//初始化缓冲区
	virtual void InitBuffer(const CString &strBuff);
	virtual void InitBuffer(const CBufferBase *pBuffer);
	virtual void InitBuffer(const char *pBuffBegin,const char *pBuffEnd);
	
	//初始化缓冲区，缓冲区的大小比实际的大
	virtual void FormatBufferEx();

	virtual BOOL ReadFromFile(const char *pszFile);
	virtual BOOL ReadFromFile(const CString &strFile);
	virtual BOOL WriteToFile(const CString &strFile);
	
protected:
	virtual BOOL IsIgnoreChar(char ch);
	virtual bool IsASeparateChar(char ch);
	
public:
	BOOL IsCurrStringASection();
	BOOL IsCurrStringAKey();
	BOOL GetIniSection(char *pszSectionName);
	BOOL GetIniSection(CString &strSectionName);
	BOOL GetIniKey(char *pszKeyName,char *pszKeyValue);
	BOOL GetIniKey(CString &strKeyName,CString &strKeyValue);
};

#endif // !defined(AFX_INIFILEBUFFER_H__5F4B1F9E_5743_4ED7_9F86_30F0B2592CD3__INCLUDED_)
