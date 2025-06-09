// SerializeBufferBase.h: interface for the CSerializeBufferBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SerializeBufferBase_H__)
#define _SerializeBufferBase_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../API/StringApi.h"

class CSerializeBufferBase
{
protected:
	char *m_pchData;
	char *m_lpBufCur;
	char *m_lpBufMax;
	
	void Init();

	//WRITE/READ operations flags
	UINT	m_nOperation;
	long	m_nBufCurLen;
	long    m_nBufferLength;

	BOOL m_bCharSetUnicode;


protected:	
	static const long NUMBER_TBUFFER_LENGTH;
	static const long DOUBLE_MAX_PRECISION;

	typedef enum{
		IT_DECIMAL = 0,    //十进制
		IT_HEX     = 1,    //十六进制
		IT_OCTAL   = 2,    //八进制
		IT_BINARY  = 3,    //二进制
		IT_HEX_LOW = 4     //十六进制
	}INT_TYPE;

	//定义扫描机的动作
	typedef enum{
		XO_PAUSE = 0,    //暂停
		XO_CONTINUE = 1    //继续
	}XF_OPERA;

	//定义扫描机的状态
	typedef enum{
		XS_SKIP = 0,     //扫描前缀串
		XS_PROC = 1,     //需处理当前格式或前缀串
		XS_FLAG = 2,     //扫描添位符
		XS_WIDTH = 3,    //扫描占宽
		XS_PREC = 4,     //扫描精度
		XS_SIZE= 5,      //扫描整形指示
		XS_TYPE = 6,     //扫描格式符
		XS_TERM = 7      //扫描终止
	}XF_STATUS;   

	int _tk_sprintf(char flag,int width,int prec,char size,char type,va_list* parg);	

	//判断是否添位符
	bool s_is_flag(char ch)   
	{  return ((ch == '0' || ch == ' ' || ch == '#')? true : false);	}

	//判断是否是数字
	bool s_is_digit(char ch)  
	{  return   ((ch >= '0' && ch <= '9')? true : false);	}

	//判断是否是整形指示
	bool s_is_size(char ch)    
	{  return ((ch == 'h' || ch == 'l')? true : false);	}

	//判断是否是格式符
	bool s_is_type(char ch)    
	{  
		return ((ch == 'c' || ch == 'C' || ch == 'd' || ch == 'u' 
			|| ch == 'x' || ch == 'X' || ch == 'f'|| ch == 's' || ch == 'S'
			|| ch == 'b' || ch == 'B' || ch == 'o' || ch == 'O')? 1 : 0);	
	}

public:
	//缓冲区写方法
	virtual long WriteString(const char *pstrData);
	virtual long WriteString_N_0(const char *pstrData);
	virtual long WriteString(BSTR &bstrData);
	virtual long WriteLong(long nVal, long nWidth, bool bFill0);
	virtual long WriteUnsignedLong(unsigned long nVal, long nWidth, bool bFill0);
	virtual long WriteHex(unsigned long nVal, long it, long nWidth, bool bFill0);
	virtual long WriteDouble(double dVal, long nWidth, bool bFill0, long nPrecision);
    virtual long WriteChar(char ch);
    virtual long WriteWChar(wchar_t wch);

    //2020-12-27 lijunqing
    //缓冲区读方法
    virtual long ReadString(char *pstrData);

public:
	CSerializeBufferBase();
	virtual ~CSerializeBufferBase();

	void RepalceChar(CHAR chSrc, CHAR chDest, long nLen);

	void SetCharSetUnicode()	{	m_bCharSetUnicode = 1;	}
	void SetCharSetAscii()		{	m_bCharSetUnicode = 0;	}

	void Offset(long nOffset)
	{
		m_lpBufCur += nOffset;
	}
	void SeekTo(long nPos)
	{
		m_lpBufCur = m_pchData + nPos;
	}
	BOOL IsEof()
	{
		return (m_lpBufCur >= m_lpBufMax);
	}
	long Tell()
	{
		return m_lpBufCur - m_pchData;
	}
	long Tell_Curr_to_End()	{	return m_lpBufMax - m_lpBufCur;	}
	//不考虑pPos不在缓冲区范围的异常
	long Tell(char *pPos)	{	return pPos - m_pchData;	}
	long Tell_Curr_to_End(char *pPos)	{	return pPos - m_pchData;	}

	char* Buffer()	{	return m_pchData;	}
	char* BufferCurr()	{	return m_lpBufCur;	}
	


	//缓冲区的长度管理
	virtual BOOL SetBufferLength(int nLen)		{ nLen = 0;	return -1;	};
	virtual int  GetBufferLength();
	virtual void ResetBufferPointer();
	BOOL CmpBuffer(BYTE *pBuffer, long nLenCmp);
	
	//缓冲区的读写模式
	virtual void SetReadMode();
	virtual void SetWriteMode();
	virtual void SetCalSizeMode();
	virtual BOOL IsReadMode();
	virtual BOOL IsWriteMode();
	virtual BOOL IsCalSizeMode();	
	
	//缓冲区的数据
#ifndef _PSX_IDE_QT_
    virtual long SetBuffer(VARIANT *pvarBuff);
	virtual long GetBuffer(VARIANT *pvarBuff);
#endif
    virtual long GetAnsiBuffer(CString &strText);
	
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
#ifndef _PSX_IDE_QT_
    virtual long Unsigned(unsigned u);
#endif
    virtual long String(const CString &strData);
	virtual long String(BSTR strData);
#ifndef _PSX_IDE_QT_
    virtual long Currency(const CURRENCY &cy);
#endif
    virtual long Systemtime(const SYSTEMTIME &tm);
    virtual void Append(char *pBuffer, long nLen);

	
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
#ifndef _PSX_IDE_QT_
    virtual long Unsigned(unsigned *u);
#endif
    virtual long String(CString *pstrData);
	virtual long String(char *pstrData, long nLen);
	virtual long String(BSTR *strData);
#ifndef _PSX_IDE_QT_
        virtual long Currency(CURRENCY *strData);
#endif
        virtual long Systemtime(SYSTEMTIME *tm);

	virtual char ReadChar();
	virtual BYTE ReadByte();
	virtual WORD ReadWord();
	virtual LONG ReadLong ();
	virtual DWORD ReadDWord();
	virtual float ReadFloat();
	virtual double ReadDouble();
	virtual int ReadInt();
	virtual short ReadShort();
	virtual wchar_t ReadWchar();
#ifndef _PSX_IDE_QT_
    virtual unsigned ReadUnsigned();
    virtual CURRENCY ReadCurrency();
#endif
    virtual SYSTEMTIME ReadSystemtime();

	
	//增加缓冲区的长度
	virtual long AddBufferLength(long lLen);
	virtual long EnsureBuffer(long nWriteLen);

	int sprintf(const char* fmt, ...);
public:
	// Serialize member function 
	// WRITE operations
	void WriteBufferEx(LPVOID pBuffer, DWORD dwLen)
	{
		DWord(dwLen);
		WriteBuffer(pBuffer, dwLen);
	}

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

	CSerializeBufferBase& operator<<(char ch)
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
    CSerializeBufferBase& operator<<(wchar_t ch)
    {
        if (m_lpBufCur + sizeof(wchar_t) <= m_lpBufMax)
        {
            *( wchar_t*)m_lpBufCur = ch;
            m_lpBufCur += sizeof(wchar_t);
        }
        else
        {
            throw(-1);
        }
        return *this;
    }
	CSerializeBufferBase& operator<<(BYTE by)
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
#ifndef _PSX_IDE_QT_
	CSerializeBufferBase& operator<<(WORD w)
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
#endif

    CSerializeBufferBase& operator<<(LONG l)
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

    CSerializeBufferBase& operator<<(DWORD dw)
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

	CSerializeBufferBase& operator<<(volatile __int64 n64)
	{ 
		if (m_lpBufCur + sizeof(__int64) <= m_lpBufMax) 
		{
			*(volatile __int64*)m_lpBufCur = n64; 
			m_lpBufCur += sizeof(__int64); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}

	CSerializeBufferBase& operator<<(float f)
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
	CSerializeBufferBase& operator<<(double d)
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

	CSerializeBufferBase& operator<<(int i)
	{ 
            if (m_lpBufCur + sizeof(int) <= m_lpBufMax)
            {
                    *( int*)m_lpBufCur = *(int*)&i;
                    m_lpBufCur += sizeof(int);
            }
            else
            {
                    throw(-1);
            }
            return *this;
	}
	CSerializeBufferBase& operator<<(short w)
	{ 
        if (m_lpBufCur + sizeof(short) <= m_lpBufMax)
        {
                *( short*)m_lpBufCur = w;
                m_lpBufCur += sizeof(short);
        }
        else
        {
                throw(-1);
        }
        return *this;
	}
#ifndef _PSX_IDE_QT_
    CSerializeBufferBase& operator<<(unsigned u)
	{ 
		return CSerializeBufferBase::operator<<((LONG)u); 
	}
#endif

    CSerializeBufferBase& operator<<(const CString &strData)
	{
#ifdef _UNICODE
		int nLen = 2*(strData.GetLength() +1);
#else
		int nLen = strData.GetLength() +1;
#endif

		if (m_lpBufCur + nLen <= m_lpBufMax) 
		{
#ifdef _UNICODE
                        //wcscpy((wchar_t*)m_lpBufCur,strData);
                        CString_to_wchar(strData, (wchar_t*)m_lpBufCur);
			m_lpBufCur += nLen;
#else
			//2024-10-18 zhouyangyong 移植优化
                        //strcpy((char*)m_lpBufCur, strData);
			//CString_to_char(strData, (char*)m_lpBufCur);
			nLen = CString_to_char(strData, (char*)m_lpBufCur) + 1;
			while (*m_lpBufCur != 0)
			{
				m_lpBufCur++;
			}

			m_lpBufCur++;
#endif
//			m_lpBufCur += nLen;
		}
		else
		{
			throw(-1);
		}
		return *this;
	}

	CSerializeBufferBase& operator<<(const wchar_t *pData)
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
	CSerializeBufferBase& operator<<(BSTR str)
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
	CSerializeBufferBase& operator<<(char *pData)
	{
		//ASSERT(pData != NULL);
		int nLen = strlen(pData)+1;
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
#ifndef _PSX_IDE_QT_
        CSerializeBufferBase& operator<<(const CURRENCY &c)
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
#endif
        CSerializeBufferBase& operator<<(const SYSTEMTIME &tm)
	{
		//ASSERT(pData != NULL);
		int nLen = sizeof(tm);
		if (m_lpBufCur + nLen <= m_lpBufMax) 
		{
			memcpy(m_lpBufCur, &tm, nLen);
			m_lpBufCur += nLen;
		}
		else
		{
			throw(-1);
		}

		return *this; 
	}

	// READ operations
	long ReadBuffer(LPVOID pBuffer, DWORD dwLen)
	{
		if (m_lpBufCur + dwLen <= m_lpBufMax) 
		{
			memcpy(pBuffer, m_lpBufCur, dwLen);
			m_lpBufCur += dwLen;
			return 1;
		}
		else
		{
			throw(-1);
			return 0;
		}
	}
	long ReadBuffer(LPVOID pBuffer, DWORD dwLen, long nCount)
	{
		long nLen = dwLen * nCount;

		if (m_lpBufCur + nLen <= m_lpBufMax) 
		{
			memcpy(pBuffer, m_lpBufCur, nLen);
			m_lpBufCur += nLen;
			return nCount;
		}
		else
		{
			throw(-1);
			return 0;
		}
	}

	CSerializeBufferBase& operator>>(char& ch)
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
	CSerializeBufferBase& operator>>(BYTE& by)
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
#ifndef _PSX_IDE_QT_
	CSerializeBufferBase& operator>>(WORD& w)
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
#endif
    CSerializeBufferBase& operator>>(LONG& l)
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

#ifndef USE_WCHAR_T_AS_EXTERNAL_TYPE
	CSerializeBufferBase& operator>>(wchar_t& l)
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
#endif
	CSerializeBufferBase& operator>>(DWORD& dw)
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

	CSerializeBufferBase& operator>>(volatile __int64& n64)
	{ 
		if (m_lpBufCur + sizeof(__int64) <= m_lpBufMax)
		{
			n64 = *(volatile __int64*)m_lpBufCur; 
			m_lpBufCur += sizeof(__int64); 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}

	CSerializeBufferBase& operator>>(float& f)
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
	CSerializeBufferBase& operator>>(double& d)
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
	CSerializeBufferBase& operator>>(int& i)
	{ 
            if (m_lpBufCur + sizeof(int) <= m_lpBufMax)
            {
                    *(int*)&i = *( int*)m_lpBufCur;
                    m_lpBufCur += sizeof(int);
            }
            else
            {
                    throw(-1);
            }
            return *this;
        }
    CSerializeBufferBase& operator>>(short& w)
	{ 
        if (m_lpBufCur + sizeof(short) <= m_lpBufMax)
        {
                *(short*)&w = *( short*)m_lpBufCur;
                m_lpBufCur += sizeof(short);
        }
        else
        {
                throw(-1);
        }
        return *this;
	}
#ifndef _PSX_IDE_QT_
        CSerializeBufferBase& operator>>(unsigned& u)
	{ 
		return CSerializeBufferBase::operator>>((LONG&)u); 
	}
#endif

    CSerializeBufferBase& operator>>(CString &strData)
	{
#ifdef _UNICODE
		int nLen = 2*(wcslen((wchar_t*)m_lpBufCur)+1);
#else
		int nLen;
		
		if (m_bCharSetUnicode)
		{
			nLen = 2*(wcslen((wchar_t*)m_lpBufCur)+1);
		}
		else
		{
			nLen = strlen(m_lpBufCur)+1;
		}
#endif
		if (m_lpBufCur + nLen <= m_lpBufMax)
		{
#ifdef _UNICODE
			strData = (wchar_t*)m_lpBufCur;
#else
			if (m_bCharSetUnicode)
			{
				strData = (wchar_t*)m_lpBufCur;
			}
			else
			{
				strData = (char*)m_lpBufCur;
			}
#endif

			m_lpBufCur += nLen; 
		}
		else
		{
			throw(-1);
		}
		
		return *this; 
	}

	CSerializeBufferBase& operator>>(wchar_t *strData)
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
	CSerializeBufferBase& operator>>(BSTR *strData)
	{
		int nLen = 2*(wcslen((BSTR)m_lpBufCur)+1);
		if (m_lpBufCur + nLen <= m_lpBufMax)
		{
			*strData = new wchar_t[nLen];
			wcscpy(*strData, (BSTR)m_lpBufCur);
			m_lpBufCur += nLen; 
		}
		else
		{
			throw(-1);
		}
		return *this; 
	}
	CSerializeBufferBase& operator>>(char *strData)
	{
		int nLen = strlen(m_lpBufCur)+1;
		if (m_lpBufCur + nLen <= m_lpBufMax)
		{
			strcpy(strData , m_lpBufCur);
			m_lpBufCur += nLen; 
		}
		else
		{
			throw(-1);
		}

		return *this; 
	}
#ifndef _PSX_IDE_QT_
        CSerializeBufferBase& operator>>(CURRENCY &c)
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
#endif
        CSerializeBufferBase& operator>>(SYSTEMTIME &tm)
	{
		int nLen = sizeof(tm);
		if (m_lpBufCur + nLen <= m_lpBufMax)
		{

			memcpy(&tm,m_lpBufCur, nLen);
			m_lpBufCur += nLen; 
		}
		else
		{
			throw(-1);
		}

		return *this; 
	}
        // calculate size operations
        CSerializeBufferBase& operator+=(char& ch)
	{ 
#ifdef _PSX_IDE_QT_
            (void)ch;
#endif
        m_nBufCurLen += sizeof(ch);
		return *this; 
	}
	CSerializeBufferBase& operator+=(BYTE& by)
	{ 
#ifdef _PSX_IDE_QT_
            (void)by;
#endif
        m_nBufCurLen += sizeof(by);
		return *this; 
	}
	CSerializeBufferBase& operator+=(WORD& w)
    {
#ifdef _PSX_IDE_QT_
            (void)w;
#endif
        m_nBufCurLen += sizeof(w);
		return *this; 
	}
#ifndef _PSX_IDE_QT_
        CSerializeBufferBase& operator+=(LONG& l)
	{ 
		m_nBufCurLen += sizeof(LONG); 
		return *this; 
	}
#endif
        CSerializeBufferBase& operator+=(DWORD& dw)
	{ 
#ifdef _PSX_IDE_QT_
            (void)dw;
#endif
        m_nBufCurLen += sizeof(dw);
		return *this; 
	}
	CSerializeBufferBase& operator+=(float& f)
	{ 
#ifdef _PSX_IDE_QT_
            (void)f;
#endif
        m_nBufCurLen += sizeof(f);
		return *this; 
	}
	CSerializeBufferBase& operator+=(double& d)
	{ 
#ifdef _PSX_IDE_QT_
            (void)d;
#endif
        m_nBufCurLen += sizeof(d);
		return *this; 
	}
	CSerializeBufferBase& operator+=(int& i)
	{ 
#ifdef _PSX_IDE_QT_
            (void)i;
#endif
                m_nBufCurLen += sizeof(i);
                return *this;
	}
	CSerializeBufferBase& operator+=(short& w)
	{ 
		return CSerializeBufferBase::operator+=((WORD&)w); 
	}
#ifndef _PSX_IDE_QT_
        CSerializeBufferBase& operator+=(unsigned& u)
	{ 
		return CSerializeBufferBase::operator+=((LONG&)u); 
	}
#endif
    CSerializeBufferBase& operator+=(CString &strData)
	{
		m_nBufCurLen += 2*(strData.GetLength() + 1); 
		return *this; 
	}
	CSerializeBufferBase& operator+=(wchar_t *strData)
	{
		m_nBufCurLen += 2 * ( wcslen(strData) + 1 ); 
		return *this; 
	}


protected:
	static const long DEFAULT_BUFF_LENGTH;
	enum SerializeBufferBaseMode
	{
		MODE_CALSIZE,
		MODE_WRITE,
		MODE_READ
	};
};

#endif // !defined(_SerializeBufferBase_H__)
