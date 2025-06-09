// StringSerializeBufferAscii.h: interface for the CStringSerializeBufferAscii class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_StringSerializeBufferAscii_H__)
#define _StringSerializeBufferAscii_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _DBLIB_USE_SHAREMEM_
#include "ShareMemSerialize.h"
#endif

#include "../API/StringApi.h"

class CStringSerializeBufferAscii
{
public:
	CStringSerializeBufferAscii();
	virtual ~CStringSerializeBufferAscii();

	void RepalceChar(CHAR chSrc, CHAR chDest, long nLen);

	virtual BOOL ReadFromFile(const CString &strFile);//	{	return FALSE;	}
	virtual BOOL WriteToFile(const CString &strFile);//	{	return FALSE;	}

public:
	void SetEncoding(UINT nEncoding)		{	m_nEncoding = nEncoding;	}
	UINT GetEncoding()	{	return m_nEncoding;	}

protected:
	char *m_pchData;
	char *m_lpBufCur;
	char *m_lpBufMax;
	UINT m_nEncoding;
	
	void Init();
	virtual void FreeBuff();

	//WRITE/READ operations flags
	long    m_nBufferLength;

public:
	void SeekToHead()   {	m_lpBufCur = m_pchData;	}
	long Tell()	{	return m_lpBufCur - m_pchData;	}
	long Tell_Curr_to_End()	{	return m_lpBufMax - m_lpBufCur;	}

	//不考虑pPos不在缓冲区范围的异常
	long Tell(char *pPos)	{	return pPos - m_pchData;	}
	long Tell_Curr_to_End(char *pPos)	{	return pPos - m_lpBufCur;	}

	const char* GetBuffer()	{	return m_pchData;	}
	const char* GetBufferCurr()	{	return m_lpBufCur;	}

	void Offset(long nOffset)
	{
		m_lpBufCur += nOffset;
	}

	void AddBufferLength(int nLen)	{	m_nBufferLength += nLen;	}
	
	//缓冲区的长度管理
	virtual BOOL SetBufferLength(int nLen);
	virtual int  GetBufferLength();
	virtual void ResetBufferPointer();
	virtual BOOL AllocBuffer(long lExpandPercent);	
	virtual void ExpandAllocBuffer(long nAddLen);

	void AddBufLenByVal(CString &strValue);
	void AddBufLenByVal(wchar_t *strValue);
	void AddBufLenByVal(long &nValue);
	void AddBufLenByVal(double &fValue);
	void AddBufLenByVal(float &fValue);
	void AddBufLenByVal(DWORD &dwValue);
	void AddBufLenByVal(__int64 &n64Value);
	void AddBufLenByVal(SYSTEMTIME &tmValue);

	//缓冲方法
    virtual void Append(const char *pBuffer, long nLen);
    virtual void AppendEquation(const char *pszID, const char *pszValue);  //2020-11-6  lijunqing
	virtual long Append_MySql(char *pBuffer, long &nLen);
	virtual long String(const CString &strData);
	virtual long String(BSTR strData);
	virtual long String(CString *pstrData);
	virtual long Append_ASCII(const CString &strData);
	virtual void StringEnd();

	virtual long Append_String(const CString &strData);

public:
	// Serialize member function 
	// WRITE operations

	void WriteBuffer(LPVOID pBuffer, DWORD dwLen)
	{
		if (m_lpBufCur + dwLen > m_lpBufMax) 
		{
			ExpandAllocBuffer(dwLen+DEFAULT_BUFF_LENGTH);
		}

		memcpy(m_lpBufCur, pBuffer, dwLen);
		m_lpBufCur += dwLen;
	}

	CStringSerializeBufferAscii& operator<<(const char *pszData)
	{
		strcpy((char*)m_lpBufCur, pszData);
		m_lpBufCur += strlen(pszData);;
		return *this;
	}

	CStringSerializeBufferAscii& operator<<(const CString &strData)
	{
		int nLen = String_Char_Count(strData);

		if (m_lpBufCur + nLen > m_lpBufMax) 
		{
			ExpandAllocBuffer(nLen+DEFAULT_BUFF_LENGTH);
		}

                nLen = CString_to_char(strData, m_lpBufCur, nLen+2);
		m_lpBufCur += nLen;

		return *this;
	}

	CStringSerializeBufferAscii& operator<<(const wchar_t *pData)
	{
		//ASSERT(pData != NULL);
		int nLen = String_Char_Count(pData);

		if (m_lpBufCur + nLen > m_lpBufMax) 
		{
			ExpandAllocBuffer(nLen+DEFAULT_BUFF_LENGTH);
		}

		nLen = BSTR_to_char((BSTR)pData, m_lpBufCur);
		m_lpBufCur += nLen;

		return *this; 
	}
	CStringSerializeBufferAscii& operator<<(BSTR str)
	{
		int nLen = String_Char_Count(str);

		if (m_lpBufCur + nLen > m_lpBufMax) 
		{
			ExpandAllocBuffer(nLen+DEFAULT_BUFF_LENGTH);
		}
	
		nLen = BSTR_to_char(str, m_lpBufCur);
		m_lpBufCur += nLen;

		return *this; 
	}


	CStringSerializeBufferAscii& operator<<(long &nValue)
	{
		sprintf(m_lpBufCur, "%d", nValue);
		m_lpBufCur += strlen(m_lpBufCur);

		return *this; 
	}
	CStringSerializeBufferAscii& operator<<(double &fValue)
	{
		sprintf(m_lpBufCur, "%f", fValue);
		m_lpBufCur += strlen(m_lpBufCur);

		return *this; 
	}
	CStringSerializeBufferAscii& operator<<(float &fValue)
	{
		sprintf(m_lpBufCur, "%f", fValue);
		m_lpBufCur += strlen(m_lpBufCur);

		return *this; 
	}
	CStringSerializeBufferAscii& operator<<(DWORD &dwValue)
	{
		sprintf(m_lpBufCur, "%d", dwValue);
		m_lpBufCur += strlen(m_lpBufCur);

		return *this; 
	}
	CStringSerializeBufferAscii& operator<<(__int64 &n64Value)
	{
		sprintf(m_lpBufCur, "%I64d", n64Value);
		m_lpBufCur += strlen(m_lpBufCur);

		return *this; 
	}
	CStringSerializeBufferAscii& operator<<(SYSTEMTIME &tmValue)
	{
		sprintf(m_lpBufCur, "%d-%d-%d %d:%d:%d", tmValue.wYear, tmValue.wMonth, tmValue.wDay, tmValue.wHour, tmValue.wMinute, tmValue.wSecond);
		m_lpBufCur += strlen(m_lpBufCur);

		return *this; 
	}


	CStringSerializeBufferAscii& operator>>(CString &strData)
	{
		int nLen = strlen(m_pchData);

		if (m_pchData + nLen <= m_lpBufMax)
		{
			strData = m_pchData;
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



inline void CStringSerializeBufferAscii::AddBufLenByVal(CString &strValue)
{
	AddBufferLength(String_Char_Count(strValue) + 2);
}

inline void CStringSerializeBufferAscii::AddBufLenByVal(wchar_t *strValue)
{
	AddBufferLength(String_Char_Count(strValue) + 2);
}

//long int          4        -2147483648～+2141483647
inline void CStringSerializeBufferAscii::AddBufLenByVal(long &nValue)
{
	AddBufferLength(11);
}

// float和double的精度是由尾数的位数来决定的。浮点数在内存中是按科学计数法来存储的，其整数部分始终是一个隐含着的“1”，由于它是不变的，故不能对精度造成影响。
// float：2^23 = 8388608，一共七位，这意味着最多能有7位有效数字，但绝对能保证的为6位，也即float的精度为6~7位有效数字；
// double：2^52 = 4503599627370496，一共16位，同理，double的精度为15~16位。
inline void CStringSerializeBufferAscii::AddBufLenByVal(double &fValue)
{
	AddBufferLength(40);
}

inline void CStringSerializeBufferAscii::AddBufLenByVal(float &fValue)
{
	AddBufferLength(20);
}

//long int          4        -2147483648～+2141483647
inline void CStringSerializeBufferAscii::AddBufLenByVal(DWORD &dwValue)
{
	AddBufferLength(11);
}

//long long long int  8      -9223372036854775808～+9223372036854775807
inline void CStringSerializeBufferAscii::AddBufLenByVal(__int64 &n64Value)
{
	AddBufferLength(20);
}

//2018-10-03 07:23:30 666
inline void CStringSerializeBufferAscii::AddBufLenByVal(SYSTEMTIME &tmValue)
{
	AddBufferLength(23);
}

#ifdef _DBLIB_USE_SHAREMEM_

class CStringSerializeBufferAscii_ShareMem : public CStringSerializeBufferAscii
{
public:
	CStringSerializeBufferAscii_ShareMem();
	virtual ~CStringSerializeBufferAscii_ShareMem();

	virtual BOOL ReadFromFile(const CString &strFile);
	virtual BOOL WriteToFile(const CString &strFile);

public:
	virtual void FreeBuff();
	virtual BOOL SetBufferLength(int nLen);
	virtual BOOL AllocBuffer(long lExpandPercent);	
	virtual void ExpandAllocBuffer(long nAddLen);

private:
	CShareMemSerialize *m_pBufferSm;
	BOOL m_bAttachShareMemSerialize;


public:
	void AttachShareMemSerialize(CShareMemSerialize *pBufferSm);
	void CreateShareMemSerialize(const CString &strSmFile, DWORD dwLen=128);
};
#endif


#endif // !defined(_StringSerializeBufferAscii_H__)
