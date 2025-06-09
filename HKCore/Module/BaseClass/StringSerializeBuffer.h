// StringSerializeBuffer.h: interface for the CStringSerializeBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_StringSerializeBuffer_H__)
#define _StringSerializeBuffer_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../API/StringApi.h"
#ifndef _PSX_QT_LINUX_
#include "oleauto.h"
#endif

class CStringSerializeBuffer
{
protected:
	char *m_pchData;
	char *m_lpBufCur;
	char *m_lpBufMax;
	
	void Init();
	void FreeBuff();

	//WRITE/READ operations flags
	long    m_nBufferLength;

public:
	long Tell()	{	return m_lpBufCur - m_pchData;	}
	const char* GetBuffer()	{	return m_pchData;	}
	CStringSerializeBuffer();
	virtual ~CStringSerializeBuffer();
	void Offset(long nOffset)
	{
		m_lpBufCur += nOffset;
	}
	
	//缓冲区的长度管理
	virtual BOOL SetBufferLength(int nLen);
	virtual int  GetBufferLength();
	virtual void ResetBufferPointer();
	virtual BOOL AllocBuffer(long lExpandPercent);	

	//缓冲方法
	virtual long String(const CString &strData);
	virtual long String(BSTR strData);
	virtual long String(CString *pstrData);
	virtual long String(BSTR *strData);
	virtual long Append_ASCII(const CString &strData);
	virtual void StringEnd();

public:
	// Serialize member function 
	// WRITE operations

	void WriteBuffer(LPVOID pBuffer, DWORD dwLen)
	{
		if (m_lpBufCur + dwLen <= m_lpBufMax) 
		{
			memcpy(m_lpBufCur, pBuffer, dwLen);
			m_lpBufCur += dwLen;
		}
		else
		{
			throw(-1);
		}
	}

	CStringSerializeBuffer& operator<<(const char *pszData)
	{
		strcpy((char*)m_lpBufCur, pszData);
		m_lpBufCur += strlen(pszData);;
		return *this;
	}

	CStringSerializeBuffer& operator<<(const CString &strData)
	{
#ifdef _UNICODE
		int nLen = 2*(strData.GetLength());//周宏军 20200706  此处修改后，在UNICODE下，
#else
		int nLen = String_Char_Count(strData);
#endif

		if (m_lpBufCur + nLen <= m_lpBufMax) 
		{
#ifdef _UNICODE
			wcscpy((wchar_t*)m_lpBufCur,strData);  //周宏军 20200706  此处修改后，在UNICODE下，
#else
			CString_to_char(strData, m_lpBufCur);
#endif
			m_lpBufCur += nLen;
		}
		else
		{
			throw(-1);
		}
		return *this;
	}

	CStringSerializeBuffer& operator<<(const wchar_t *pData)
	{
		//ASSERT(pData != NULL);
		int nLen = 2*(wcslen(pData));
		if (m_lpBufCur + nLen <= m_lpBufMax) 
		{
			memcpy(m_lpBufCur, pData, nLen);
			m_lpBufCur += nLen;
		}
		else
		{
			throw(-1);
		}

		return *this; 
	}
	CStringSerializeBuffer& operator<<(BSTR str)
	{
		int nLen = 2*(wcslen(str));
		if (m_lpBufCur + nLen <= m_lpBufMax) 
		{
			memcpy(m_lpBufCur, str, nLen);
			m_lpBufCur += nLen;
		}
		else
		{
			throw(-1);
		}

		return *this; 
	}

	CStringSerializeBuffer& operator>>(CString &strData)
	{
#ifdef _UNICODE
		int nLen = 2*(wcslen((wchar_t*)m_pchData));
#else
		int nLen = strlen(m_pchData);
#endif
		if (m_pchData + nLen <= m_lpBufMax)
		{
#ifdef _UNICODE
			strData = (wchar_t*)m_pchData;
#else
			strData = (char*)m_pchData;
#endif
		}
		else
		{
			throw(-1);
		}
		
		return *this; 
	}

	CStringSerializeBuffer& operator>>(wchar_t *strData)
	{
		int nLen = 2*(wcslen((wchar_t*)m_pchData));
		if (m_pchData + nLen <= m_lpBufMax)
		{
			strData = (wchar_t*)m_pchData;
		}
		else
		{
			throw(-1);
		}
		
		return *this; 
	}
	CStringSerializeBuffer& operator>>(BSTR *strData)
	{
		int nLen = 2*(wcslen((BSTR)m_pchData));

		if (m_pchData + nLen <= m_lpBufMax)
		{
			*strData = ::SysAllocString((BSTR)m_pchData);
		}
		else
		{
			throw(-1);
		}

		return *this; 
	}


protected:
	static const long DEFAULT_BUFF_LENGTH;

};

#endif // !defined(_StringSerializeBuffer_H__)
