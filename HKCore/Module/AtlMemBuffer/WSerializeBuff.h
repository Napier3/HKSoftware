// SerializeBuff.h: interface for the CWSerializeBuff class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_WSERIALIZEBUFF_H__)
#define _WSERIALIZEBUFF_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWSerializeBuff
{
protected:
	char *m_pchData;
	char *m_lpBufCur;
	char *m_lpBufMax;
	
	void Init();
	void FreeBuff();

	//WRITE/READ operations flags
	UINT	m_nOperation;
	long	m_nBufCurLen;
	BOOL	m_bAttach;
	long    m_nBufferLength;

public:
	CWSerializeBuff();
	CWSerializeBuff(int nLen);
	CWSerializeBuff(wchar_t *pBuff,int nLen);
	CWSerializeBuff(char *pBuff,int nLen);
	virtual ~CWSerializeBuff();
	void GetBuffer(wchar_t** pBuffer, long *nBufferLen);
	void GetBuffer(char** pBuffer, long *nBufferLen);
	void AttachBuffer(wchar_t *pBuffer, long nBufferLen);
	void AttachBuffer(char *pBuffer, long nBufferLen);
	void DettachBuffer();
	
	BOOL ReadFromFile(const CComBSTR &strFile);
	BOOL WriteToFile(const CComBSTR &strFile);	
	//////////////////////////////////////////////////////////////////////////
	//接口定义重载
	
	//缓冲区的长度管理
	virtual BOOL AllocDefaultBuffer();	
	virtual BOOL AllocBuffer(long lExpandPercent);	
	virtual BOOL SetBufferLength(int nLen);
	virtual int  GetBufferLength();
	virtual void ResetBufferPointer();
	
	//缓冲区的读写模式
	virtual void SetReadMode();
	virtual void SetWriteMode();
	virtual void SetCalSizeMode();
	virtual BOOL IsReadMode();
	virtual BOOL IsWriteMode();
	virtual BOOL IsCalSizeMode();	
	
	//缓冲区的数据
	virtual long SetBuffer(VARIANT *pvarBuff);
	virtual long GetBuffer(VARIANT *pvarBuff);
	
	//缓冲区写方法
	virtual long Char(char ch);
	virtual long Byte(BYTE by);
	virtual long Word(WORD w);
	virtual long Long (LONG l);
	virtual long DWord(DWORD dw);
	virtual long Float(float f);
	virtual long Double(double d);
	virtual long Int(int i);
	virtual long Short(short w);
	virtual long Wchar(wchar_t ch);
	virtual long Unsigned(unsigned u);
	virtual long String(const CComBSTR &strData);
	virtual long String(BSTR strData);
	virtual long Currency(const CURRENCY &cy);
	
	//缓冲区读方法
	virtual long Char(char *ch);
	virtual long Byte(BYTE *by);
	virtual long Word(WORD *w);
	virtual long Long (LONG *l);
	virtual long DWord(DWORD *dw);
	virtual long Float(float *f);
	virtual long Double(double *d);
	virtual long Int(int *i);
	virtual long Short(short *w);
	virtual long Wchar(wchar_t *ch);
	virtual long Unsigned(unsigned *u);
	virtual long RString(CComBSTR &strData);
	virtual long String(BSTR *strData);
	virtual long Currency(CURRENCY *strData);
	
	//增加缓冲区的长度
	virtual long AddBufferLength(long lLen);

public:
	// Serialize member function 
	// WRITE operations
	CWSerializeBuff& operator<<(char ch)
	{
		if (m_lpBufCur + sizeof(char) <= m_lpBufMax) 
		{
			*( BYTE*)m_lpBufCur = ch; 	
			m_lpBufCur += sizeof(char); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator<<(BYTE by)
	{
		if (m_lpBufCur + sizeof(BYTE) <= m_lpBufMax) 
		{
			*( BYTE*)m_lpBufCur = by; 	
			m_lpBufCur += sizeof(BYTE); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator<<(WORD w)
	{ 
		if (m_lpBufCur + sizeof(WORD) <= m_lpBufMax) 
		{
			*( WORD*)m_lpBufCur = w; 
			m_lpBufCur += sizeof(WORD);
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator<<(LONG l)
	{ 
		if (m_lpBufCur + sizeof(LONG) <= m_lpBufMax) 
		{
			*( LONG*)m_lpBufCur = l; 
			m_lpBufCur += sizeof(LONG); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator<<(DWORD dw)
	{ 
		if (m_lpBufCur + sizeof(DWORD) <= m_lpBufMax) 
		{
			*( DWORD*)m_lpBufCur = dw; 
			m_lpBufCur += sizeof(DWORD); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator<<(float f)
	{ 
		if (m_lpBufCur + sizeof(float) <= m_lpBufMax) 
		{
			*( float*)m_lpBufCur = *(float*)&f; 
			m_lpBufCur += sizeof(float); 
		}
		else
		{
			throw(-1);
		}
		return *this;
	}
	CWSerializeBuff& operator<<(double d)
	{ 
		if (m_lpBufCur + sizeof(double) <= m_lpBufMax) 
		{
			*( double*)m_lpBufCur = *(double*)&d; 
			m_lpBufCur += sizeof(double);
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}

	CWSerializeBuff& operator<<(int i)
	{ 
		return CWSerializeBuff::operator<<((LONG)i); 
	}
	CWSerializeBuff& operator<<(short w)
	{ 
		return CWSerializeBuff::operator<<((WORD)w); 
	}
	CWSerializeBuff& operator<<(unsigned u)
	{ 
		return CWSerializeBuff::operator<<((LONG)u); 
	}
	CWSerializeBuff& operator<<(const CComBSTR &strData)
	{
		int nLen = 2*(strData.Length() +1);
		if (m_lpBufCur + nLen <= m_lpBufMax) 
		{
			wcscpy((wchar_t*)m_lpBufCur,strData);
			m_lpBufCur += nLen;
		}
		else
		{
			throw(-1);
		}
		return *this;
	}

	CWSerializeBuff& operator<<(const wchar_t *pData)
	{
		//ASSERT(pData != NULL);
		int nLen = 2*(wcslen(pData)+1);
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
	CWSerializeBuff& operator<<(BSTR str)
	{
		int nLen = 2*(wcslen(str)+1);
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
	CWSerializeBuff& operator<<(const CURRENCY &c)
	{
		//ASSERT(pData != NULL);
		int nLen = sizeof(c);
		if (m_lpBufCur + nLen <= m_lpBufMax) 
		{
			memcpy(m_lpBufCur, &c, nLen);
			m_lpBufCur += nLen;
		}
		else
		{
			throw(-1);
		}

		return *this; 
	}
	// READ operations
	CWSerializeBuff& operator>>(char& ch)
	{ 
		if (m_lpBufCur + sizeof(char) <= m_lpBufMax)
		{
			ch = *( BYTE*)m_lpBufCur; 
			m_lpBufCur += sizeof(char); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator>>(BYTE& by)
	{ 
		if (m_lpBufCur + sizeof(BYTE) <= m_lpBufMax)
		{
			by = *( BYTE*)m_lpBufCur; 
			m_lpBufCur += sizeof(BYTE); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator>>(WORD& w)
	{ 
		if (m_lpBufCur + sizeof(WORD) <= m_lpBufMax)
		{
			w = *( WORD*)m_lpBufCur; 
			m_lpBufCur += sizeof(WORD);
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator>>(LONG& l)
	{ 
		if (m_lpBufCur + sizeof(LONG) <= m_lpBufMax)
		{
			l = *( LONG*)m_lpBufCur; 
			m_lpBufCur += sizeof(LONG); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator>>(wchar_t& l)
	{ 
		if (m_lpBufCur + sizeof(wchar_t) <= m_lpBufMax)
		{
			l = *( wchar_t*)m_lpBufCur; 
			m_lpBufCur += sizeof(wchar_t); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator>>(DWORD& dw)
	{ 
		if (m_lpBufCur + sizeof(DWORD) <= m_lpBufMax)
		{
			dw = *( DWORD*)m_lpBufCur; 
			m_lpBufCur += sizeof(DWORD); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator>>(float& f)
	{ 
		if (m_lpBufCur + sizeof(float) <= m_lpBufMax)
		{
			*(float*)&f = *( float*)m_lpBufCur; 
			m_lpBufCur += sizeof(float); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator>>(double& d)
	{ 
		if (m_lpBufCur + sizeof(double) <= m_lpBufMax)
		{
			*(double*)&d = *( double*)m_lpBufCur;
			m_lpBufCur += sizeof(double); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator>>(int& i)
	{ 
		return CWSerializeBuff::operator>>((LONG&)i); 
	}
	CWSerializeBuff& operator>>(short& w)
	{ 
		return CWSerializeBuff::operator>>((WORD&)w); 
	}
	CWSerializeBuff& operator>>(unsigned& u)
	{ 
		return CWSerializeBuff::operator>>((LONG&)u); 
	}
	CWSerializeBuff& operator>>(CComBSTR &strData)
	{
		int nLen = 2*(wcslen((wchar_t*)m_lpBufCur)+1);
		if (m_lpBufCur + nLen <= m_lpBufMax)
		{
			
			strData = (wchar_t*)m_lpBufCur;
			m_lpBufCur += nLen; 
		}
		else
		{
			throw(-1);
		}
		
		return *this; 
	}

	CWSerializeBuff& operator>>(wchar_t *strData)
	{
		int nLen = 2*(wcslen((wchar_t*)m_lpBufCur)+1);
		if (m_lpBufCur + nLen <= m_lpBufMax)
		{
			
			strData = (wchar_t*)m_lpBufCur;
			m_lpBufCur += nLen; 
		}
		else
		{
			throw(-1);
		}
		
		return *this; 
	}
	CWSerializeBuff& operator>>(BSTR *strData)
	{
		int nLen = 2*(wcslen((BSTR)m_lpBufCur)+1);
		if (m_lpBufCur + nLen <= m_lpBufMax)
		{
			
			*strData = ::SysAllocString((BSTR)m_lpBufCur);
			m_lpBufCur += nLen; 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CWSerializeBuff& operator>>(CURRENCY &c)
	{
		int nLen = sizeof(c);
		if (m_lpBufCur + nLen <= m_lpBufMax)
		{
			
			memcpy(&c,m_lpBufCur, nLen);
			m_lpBufCur += nLen; 
		}
		else
		{
			throw(-1);
		}
		
		return *this; 
	}
	// calculate size operations
	CWSerializeBuff& operator+=(char& ch)
	{ 
		m_nBufCurLen += sizeof(char); 
		return *this; 
	}
	CWSerializeBuff& operator+=(BYTE& by)
	{ 
		m_nBufCurLen += sizeof(BYTE); 
		return *this; 
	}
	CWSerializeBuff& operator+=(WORD& w)
	{ 
		m_nBufCurLen += sizeof(WORD);
		return *this; 
	}
	CWSerializeBuff& operator+=(LONG& l)
	{ 
		m_nBufCurLen += sizeof(LONG); 
		return *this; 
	}
	CWSerializeBuff& operator+=(DWORD& dw)
	{ 
		m_nBufCurLen += sizeof(DWORD); 
		return *this; 
	}
	CWSerializeBuff& operator+=(float& f)
	{ 
		m_nBufCurLen += sizeof(float); 
		return *this; 
	}
	CWSerializeBuff& operator+=(double& d)
	{ 
		m_nBufCurLen += sizeof(double); 
		return *this; 
	}
	CWSerializeBuff& operator+=(int& i)
	{ 
		return CWSerializeBuff::operator+=((LONG&)i); 
	}
	CWSerializeBuff& operator+=(short& w)
	{ 
		return CWSerializeBuff::operator+=((WORD&)w); 
	}
	CWSerializeBuff& operator+=(unsigned& u)
	{ 
		return CWSerializeBuff::operator+=((LONG&)u); 
	}
	CWSerializeBuff& operator+=(CComBSTR &strData)
	{
		m_nBufCurLen += 2*(strData.Length() + 1); 
		return *this; 
	}
	CWSerializeBuff& operator+=(wchar_t *strData)
	{
		m_nBufCurLen += 2 * ( wcslen(strData) + 1 ); 
		return *this; 
	}

private:
	static const long DEFAULT_BUFF_LENGTH;
	enum SerializeBuffMode
	{
		MODE_CALSIZE,
		MODE_WRITE,
		MODE_READ
	};
};

#endif // !defined(_WSERIALIZEBUFF_H__)
