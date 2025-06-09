// SerializeBufferBase.cpp: implementation of the CSerializeBufferBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SerializeBufferBase.h"
//#include "..\AtlBaseClass\AtlFile.h"
#include <stdarg.h>
#include "../MemBuffer/BufferBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const long CSerializeBufferBase::DEFAULT_BUFF_LENGTH = 512;
	
const long CSerializeBufferBase::NUMBER_TBUFFER_LENGTH = 40;
const long CSerializeBufferBase::DOUBLE_MAX_PRECISION  = 6;

CSerializeBufferBase::CSerializeBufferBase()
{
	Init();
	m_nOperation = MODE_WRITE;
	m_nBufCurLen = 0;
	m_bCharSetUnicode = 0;
}

CSerializeBufferBase::~CSerializeBufferBase()
{
	
}

void CSerializeBufferBase::RepalceChar(CHAR chSrc, CHAR chDest, long nLen)
{
	CHAR *p = m_pchData;
	CHAR *pEnd = m_pchData + nLen;
	
	while (p < pEnd )
	{
		if (*p == chSrc)
		{
			*p = chDest;
		}

		p++;
	}
}

BOOL CSerializeBufferBase::CmpBuffer(BYTE *pBuffer, long nLenCmp)
{
	if (m_lpBufCur + nLenCmp > m_lpBufMax)
	{
		return FALSE;
	}

	if (nLenCmp <= 0)
	{
		return FALSE;
	}

	return (memcmp(m_lpBufCur, pBuffer, nLenCmp) == 0);
}

void CSerializeBufferBase::Init()
{
	m_pchData = NULL;
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
	m_nBufCurLen = 0;
	m_nBufferLength = 0;
}

int  CSerializeBufferBase::GetBufferLength()
{
	if (MODE_CALSIZE == m_nOperation)
	{
		return 	m_nBufCurLen;
	}
	else if (MODE_READ == m_nOperation)
	{
		return m_nBufCurLen;
	}
	else
	{
		return m_lpBufCur - m_pchData;
	}
}

void CSerializeBufferBase::ResetBufferPointer()
{
	m_lpBufCur = m_pchData;
}

void CSerializeBufferBase::SetReadMode()
{
	m_nOperation = MODE_READ;
}

void CSerializeBufferBase::SetWriteMode()
{
	m_nBufCurLen = 0;
	m_nOperation = MODE_WRITE;
}

void CSerializeBufferBase::SetCalSizeMode()
{
	m_nOperation = MODE_CALSIZE;
}

BOOL CSerializeBufferBase::IsReadMode()
{
	return (m_nOperation == MODE_READ);
}

BOOL CSerializeBufferBase::IsWriteMode()
{
	return (m_nOperation == MODE_WRITE);
}

BOOL CSerializeBufferBase::IsCalSizeMode()
{
	return (m_nOperation == MODE_CALSIZE);
}

#ifndef _PSX_IDE_QT_
long CSerializeBufferBase::SetBuffer(VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	
	long lIndex = 0;
	SAFEARRAY *pFilter = V_ARRAY(pvarBuff); 
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != S_OK)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != S_OK)
		return -1;
	
	SetBufferLength(lUBound-lLBound+1);

	for(int i=lLBound;i<=lUBound;i++)
	{
		SafeArrayGetElement(pFilter,&lIndex,&m_pchData[lIndex]);
		lIndex++;
	}		

	return lIndex;
}

long CSerializeBufferBase::GetBuffer(VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound;
	SAFEARRAY * pFilter = NULL; 
	long lIndex = 0;

	bound.cElements = m_nBufCurLen;
	bound.lLbound=0;
	pFilter = SafeArrayCreate(VT_UI1,1,&bound);
	unsigned char uc = 0;
	for(int i = 0; i < m_nBufCurLen; i++)
	{
		uc = (unsigned char)m_pchData[i];
		SafeArrayPutElement(pFilter,&lIndex,(void*)&uc);
		lIndex++;
	}		

	V_VT(pvarBuff) = VT_UI1 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 
	
	return lIndex;
}
#endif

long CSerializeBufferBase::GetAnsiBuffer(CString &strText)
{
	char *pEnd = m_lpBufCur;
	char *pString = m_pchData;

	while (pString < pEnd)
	{
		pString = GetString(pString, pEnd);

		if (pString == NULL)
		{
			break;
		}

		strText += pString;
		pString = NextString(pString, pEnd);

		if (pString == NULL)
		{
			break;
		}
	}

	return strText.GetLength();
}

//缓冲区写方法
long CSerializeBufferBase::Char(char ch)
{
	*this << ch;
	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::Byte(BYTE by)
{
	*this << by;
	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::Word(WORD w)
{
	*this << w;
	return (m_lpBufCur - m_pchData);	
}

long CSerializeBufferBase::Long (LONG l)
{
    *this << (int)l;
	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::DWord(DWORD dw)
{
	*this << dw;
	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::Float(float f)
{
	*this << f;
	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::Double(double d)
{
	*this << d;
	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::Int(int i)
{
	*this << i;
	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::Short(short w)
{
	*this << w;
	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::Wchar(wchar_t wch)
{
	*this << wch;
	return (m_lpBufCur - m_pchData);
}


#ifndef _PSX_IDE_QT_
long CSerializeBufferBase::Unsigned(unsigned u)
{
    *this << u;
	return (m_lpBufCur - m_pchData);
}
#endif

long CSerializeBufferBase::String(const CString &strData)
{
	*this << strData;
	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::String(BSTR strData)
{
	*this << strData;
	return (m_lpBufCur - m_pchData);
}

#ifndef _PSX_IDE_QT_
long CSerializeBufferBase::Currency(const CURRENCY &cy)
{
	*this << cy;
	return (m_lpBufCur - m_pchData);
}
#endif

long CSerializeBufferBase::Systemtime(const SYSTEMTIME &tm)
{
	*this << tm;
	return (m_lpBufCur - m_pchData);
}


void CSerializeBufferBase::Append(char *pBuffer, long nLen)
{
	if (m_lpBufCur + nLen < m_lpBufMax) 
	{
		memcpy(m_lpBufCur, pBuffer, nLen);
		m_lpBufCur += nLen;
	}
	else
	{
		throw(-1);
	}
}

//缓冲区读方法
long CSerializeBufferBase::Char(char *ch)
{
	*this >> *ch;
	return 0;
}

long CSerializeBufferBase::Byte(BYTE *by)
{
	*this >> *by;
	return 0;
}

long CSerializeBufferBase::Word(WORD *w)
{
#ifndef _PSX_IDE_QT_
    *this >> *w;
#endif
    return 0;
}

long CSerializeBufferBase::Long (LONG *l)
{
    *this >> *l;
	return 0;
}

long CSerializeBufferBase::DWord(DWORD *dw)
{
	*this >> *dw;
	return 0;
}

long CSerializeBufferBase::Float(float *f)
{
	*this >> *f;
	return 0;
}

long CSerializeBufferBase::Double(double *d)
{
	*this >> *d;
	return 0;
}

long CSerializeBufferBase::Int(int *i)
{
	*this >> *i;
	return 0;
}

long CSerializeBufferBase::Short(short *w)
{
    *this >> *w;
    return 0;
}

long CSerializeBufferBase::Wchar(wchar_t *ch)
{
	*this >> *ch;
	return 0;
}

#ifndef _PSX_IDE_QT_
long CSerializeBufferBase::Unsigned(unsigned *u)
{
	*this >> *u;
	return 0;
}
#endif

long CSerializeBufferBase::String(CString *pstrData)
{
	*this >> *pstrData;
	return 0;
}

long CSerializeBufferBase::String(char *pstrData, long nLen)
{
	memcpy(pstrData, m_lpBufCur, nLen);
	m_lpBufCur += nLen;
	pstrData[nLen] = 0;

	return nLen;
}

long CSerializeBufferBase::String(BSTR *strData)
{
	*this >> strData;
	return 0;
}

#ifndef _PSX_IDE_QT_
long CSerializeBufferBase::Currency(CURRENCY *cy)
{
	*this >> *cy;
	return 0;
}
#endif

long CSerializeBufferBase::Systemtime(SYSTEMTIME *tm)
{
	*this >> *tm;
	return 0;
}

//Read Buffer Data
char CSerializeBufferBase::ReadChar()
{
	char ch;
	*this >> ch;
	return ch;
}

BYTE CSerializeBufferBase::ReadByte()
{
	BYTE by;
	*this >> by;
	return by;
}

WORD CSerializeBufferBase::ReadWord()
{
	WORD w;
#ifndef _PSX_IDE_QT_
    *this >> w;
#endif
    return w;
}

LONG CSerializeBufferBase::ReadLong ()
{
	LONG l;
	*this >> l;
	return l;
}

DWORD CSerializeBufferBase::ReadDWord()
{
	DWORD dw;
	*this >> dw;
	return dw;
}

float CSerializeBufferBase::ReadFloat()
{
	float f;
	*this >> f;
	return f;
}

double CSerializeBufferBase::ReadDouble()
{
	double d;
	*this >> d;
	return d;
}

int CSerializeBufferBase::ReadInt()
{
	int i;
	*this >> i;
	return i;
}

short CSerializeBufferBase::ReadShort()
{
	short w;
    *this >> w;
	return w;
}

wchar_t CSerializeBufferBase::ReadWchar()
{
	wchar_t ch;
	*this >> ch;
	return ch;
}

#ifndef _PSX_IDE_QT_
unsigned CSerializeBufferBase::ReadUnsigned()
{
    unsigned u;
    *this >> u;
    return u;
}
#endif


#ifndef _PSX_IDE_QT_
CURRENCY CSerializeBufferBase::ReadCurrency()
{
	CURRENCY cy;
	*this >> cy;
	return cy;
}
#endif

SYSTEMTIME CSerializeBufferBase::ReadSystemtime()
{
	SYSTEMTIME tm;
	*this >> tm;
	return tm;
}

//增加缓冲区的长度
long CSerializeBufferBase::AddBufferLength(long lLen)
{
	m_nBufCurLen += lLen;
	return m_nBufCurLen;	
}

long CSerializeBufferBase::EnsureBuffer(long nWriteLen)
{
	if (m_lpBufCur + nWriteLen >= m_pchData + m_nBufCurLen)
	{
		char *pBuffer = m_pchData;
		long nLen = m_nBufCurLen;
		long nCurrLen = m_lpBufCur - m_pchData;
		m_nBufCurLen += nWriteLen + DEFAULT_BUFF_LENGTH;
		
		m_pchData = new char[m_nBufCurLen + 10];
		memcpy(m_pchData, pBuffer, nCurrLen);
		m_lpBufMax = m_pchData + m_nBufCurLen;
		m_lpBufCur = m_pchData + nCurrLen;
		delete pBuffer;
	}
	else
	{
	}
	
	return m_nBufCurLen;
}

long CSerializeBufferBase::WriteString(const char *pstrData)
{
	do
	{
		*m_lpBufCur = *pstrData;
		m_lpBufCur++;
		pstrData++;
	}while	(*pstrData != 0);

	*m_lpBufCur = 0;
	m_lpBufCur++;

	return 0;
}

long CSerializeBufferBase::WriteString_N_0(const char *pstrData)
{
	do
	{
		*m_lpBufCur = *pstrData;
		m_lpBufCur++;
		pstrData++;
	}while	(*pstrData != 0);

	*m_lpBufCur = 0;

	return 0;
}

long CSerializeBufferBase::WriteString(BSTR &bstrData)
{
	long lLen = wcslen(bstrData);

//	int nLen = WideCharToMultiByte(CP_ACP, 0, bstrData, -1,
//		m_lpBufCur, lLen * 2, NULL, NULL);

    int nLen = str_wchar_to_char(m_lpBufCur, bstrData, lLen);
	m_lpBufCur += (nLen-1);

	return (m_lpBufCur - m_pchData);
}

long CSerializeBufferBase::WriteLong(long nVal, long nWidth, bool bFill0)
{
	char pTempBuffer[NUMBER_TBUFFER_LENGTH];
	char *pTemp = pTempBuffer;
	long nCount = 0;

	if (nVal < 0)
	{
		*m_lpBufCur = '-';
		m_lpBufCur++;
		nVal = 0 - nVal;
	}

	do 
	{
		*pTemp = nVal % 10 + '0';
		nVal /= 10;
		pTemp++;
		nCount++;
	} while(nVal > 0);

	nWidth -= nCount;
	char cFill = '0';
	if (!bFill0)
	{
		cFill = ' ';
	}

	if (nWidth > 0)
	{
		do 
		{
			*m_lpBufCur = cFill;
			m_lpBufCur++;
			nWidth--;
		} while(nWidth > 0);
	}

	nCount--;
	do 
	{
		*m_lpBufCur = pTempBuffer[nCount];
		m_lpBufCur++;
		nCount--;
	} while(nCount >= 0);

	*m_lpBufCur = 0;

	return 0; 
}


long CSerializeBufferBase::WriteUnsignedLong(unsigned long nVal, long nWidth, bool bFill0)
{
	char pTempBuffer[NUMBER_TBUFFER_LENGTH];
	char *pTemp = pTempBuffer;
	long nCount = 0;

	do 
	{
		*pTemp = (char)(nVal % 10 + '0');
		nVal /= 10;
		pTemp++;
		nCount++;
	} while(nVal > 0);

	nWidth -= nCount;
	char cFill = '0';
	if (!bFill0)
	{
		cFill = ' ';
	}

	if (nWidth > 0)
	{
		do 
		{
			*m_lpBufCur = cFill;
			m_lpBufCur++;
			nWidth--;
		} while(nWidth > 0);
	}

	nCount--;
	do 
	{
		*m_lpBufCur = pTempBuffer[nCount];
		m_lpBufCur++;
		nCount--;
	} while(nCount >= 0);

	*m_lpBufCur = 0;

	return 0; 
}

long CSerializeBufferBase::WriteHex(unsigned long nVal, long it, long nWidth, bool bFill0)
{
	char pTempBuffer[NUMBER_TBUFFER_LENGTH];
	char *pTemp = pTempBuffer;
	long nCount = 0;
	unsigned char ncTemp = 0;

	switch(it) 
	{
	case IT_HEX:
		do 
		{
			ncTemp = (unsigned char)(nVal & 0x0F);
			*pTemp = (ncTemp > 9 ? (ncTemp-10) + 'A' : ncTemp + '0');
			nVal = nVal >> 4;
			nCount++;
			pTemp++;
		} while(nVal > 0);

		break;
	case IT_HEX_LOW:
		do 
		{
			ncTemp = (unsigned char)(nVal & 0x0F);
			*pTemp = (ncTemp > 9 ? (ncTemp-10) + 'a' : ncTemp + '0');
			nVal = nVal >> 4;
			nCount++;
			pTemp++;
		} while(nVal > 0);

		break;
	case IT_OCTAL:
		do 
		{
			ncTemp = (unsigned char)((nVal & 0x07) + '0');
			*pTemp = ncTemp;
			nVal = nVal >> 3;
			nCount++;
			pTemp++;
		} while(nVal > 0);

		break;
	case IT_BINARY:
		do 
		{
			ncTemp = (unsigned char)( (nVal & 0x01) + '0');
			*pTemp = ncTemp;
			nVal = nVal >> 1;
			nCount++;
			pTemp++;
		} while(nVal > 0);

		break;
	default:
		WriteLong(nVal, 0, false);
		break;
	}

	*pTemp = 0;
	nWidth -= nCount;
	char cFill = '0';

	if (!bFill0)
	{
		cFill = ' ';
	}

	if (nWidth > 0)
	{
		do 
		{
			*m_lpBufCur = cFill;
			m_lpBufCur++;
			nWidth--;
		} while(nWidth > 0);
	}

	nCount--;
	do 
	{
		*m_lpBufCur = pTempBuffer[nCount];
		m_lpBufCur++;
		nCount--;
	} while(nCount >= 0);

	*m_lpBufCur = 0;

	return 0; 
}

long CSerializeBufferBase::WriteDouble(double dVal, long nWidth, bool bFill0, long nPrecision)
{
	if (dVal < 0)
	{
		*m_lpBufCur = '-';
		m_lpBufCur++;
		dVal = 0 - dVal;
	}

	unsigned long nHVal = (unsigned long)dVal;
	dVal = dVal - nHVal;


	if (nPrecision <= 0)
	{
		nPrecision = DOUBLE_MAX_PRECISION;
	}

	//精度
	long nTemp = nPrecision;

	do {
		dVal *= 10;
		nTemp--;
	} while(nTemp > 0);

	dVal += 0.5;
	unsigned long nLVal = (unsigned long)dVal;

	WriteUnsignedLong(nHVal, nWidth - 1 - nPrecision, bFill0);
	*m_lpBufCur = '.';
	m_lpBufCur++;
	WriteUnsignedLong(nLVal, nPrecision, TRUE);

	return 0;
}

long CSerializeBufferBase::WriteChar(char ch)
{
    *m_lpBufCur = ch;
    m_lpBufCur += 1;
    return 1;
}

long CSerializeBufferBase::WriteWChar(wchar_t wch)
{
    if (wch > 0x00FF)
    {
        *m_lpBufCur = ((wch >> 8) & 0xFF);
        m_lpBufCur++;
    }

    *m_lpBufCur = (wch & 0xFF);
    m_lpBufCur++;

    *m_lpBufCur = 0;

    return 2;
}

//2020-12-27 lijunqing
long CSerializeBufferBase::ReadString(char *pstrData)
{
    char *p = pstrData;
    do
    {
        *p = *m_lpBufCur;
        m_lpBufCur++;
        p++;
    }while	(*m_lpBufCur != 0);

	m_lpBufCur++;
	*p = 0;

    return p - pstrData;
}

int CSerializeBufferBase::_tk_sprintf(char flag, int width, int prec, char size, char type, va_list* parg)
{
	switch(type)
	{
	case 'c':
		{
			EnsureBuffer(1);
			char ch = va_arg(*parg,char);
			WriteChar(ch);
			break;
		}
	case 'C':
		{
			EnsureBuffer(2);
			wchar_t wch;
			wch = va_arg(*parg,wchar_t);
			WriteWChar(wch);
			break;
		}
	case 'd':
		{
			EnsureBuffer(4);
			long nVal = va_arg(*parg, long);
			WriteLong(nVal, width, true);
			break;
		}
	case 'u':
		{
			EnsureBuffer(4);
			unsigned long un = va_arg(*parg,unsigned long);
			WriteUnsignedLong(un, 0, false);
			break;
		}
	case 'x':
		{
			EnsureBuffer(6);
			unsigned long n = va_arg(*parg,unsigned long);
			WriteHex(n, IT_HEX_LOW, width, true);
			break;
		}
	case 'X':
		{
			EnsureBuffer(6);
			unsigned long n = va_arg(*parg,unsigned long);
			WriteHex(n, IT_HEX, width, true);
			break;
		}
	case 'o':
	case 'O':
		{
			EnsureBuffer(10);
			unsigned long n = va_arg(*parg,unsigned long);
			WriteHex(n, IT_OCTAL, width, true);
			break;
		}
	case 'b':
	case 'B':
		{
			EnsureBuffer(34);
			unsigned long n = va_arg(*parg,unsigned long);
			WriteHex(n, IT_BINARY, width, true);
			break;
		}
	case 'f':
		{
			EnsureBuffer(32);
			double d = va_arg(*parg,double);
			WriteDouble(d, width, true, prec);
			break;
		}
	case 's':
		{
			char *pstr =  va_arg(*parg,char*);
			EnsureBuffer(strlen(pstr) + 1);
			WriteString_N_0(pstr);
			break;
		}
	case 'S':
		{
			BSTR bstr =  va_arg(*parg, BSTR);
			EnsureBuffer(wcslen(bstr) + 1);
			WriteString(bstr);
			break;
		}

	default :
		break;
	}

	return 0;
}


int CSerializeBufferBase::sprintf(const char* fmt, ...)
{
	EnsureBuffer(1024);

	va_list arg;
	char xf_flag = 0;
	int  xf_width = 0;
	int  xf_prec = 0;
	char xf_size = 0;
	char xf_type = 0;
	char tk_width[40], tk_prec[40];
	int  width_count = 0;
	int  prec_count = 0;
	int  tk_count = 0;

	//初始化
	XF_STATUS xs = XS_SKIP;
	XF_OPERA xo = XO_PAUSE;

	char* token = (char*)fmt;

	va_start(arg,fmt);

	while(xs != XS_TERM)
	{
		switch(xs)
		{
		case XS_SKIP:
			if(*token == '%' && *(token + 1) != '%')
			{
				if(!tk_count)
				{
					xs = XS_FLAG; //没有前缀串则过渡到格式串扫描
					xo = XO_CONTINUE;
				}
				else
				{
					xs = XS_PROC; //有前缀串则先处理前缀串
					xo = XO_PAUSE;
				}
			}
			else if(*token == '\0')
			{
				xs = XS_PROC; //过渡到处理前缀串
				xo = XO_PAUSE;
			}
			else
			{
				xs = XS_SKIP; //继续前缀串扫描
				xo = XO_CONTINUE;
			}
			break;
		case XS_FLAG:
			if(s_is_flag(*token))
			{
				xf_flag = *token;
				xs = XS_FLAG; //继续占位符扫描
				xo = XO_CONTINUE;
			}
			else
			{
				xs = XS_WIDTH; //过渡到占位宽扫描
				xo = XO_PAUSE;
			}
			break;
		case XS_WIDTH:
			if(s_is_digit(*token))
			{
				tk_width[width_count ++] = *token;
				xs = XS_WIDTH; //继续占位宽扫描
				xo = XO_CONTINUE;
			}
			else if(*token == '.')
			{
				xs = XS_PREC; //过渡到精度扫描
				xo = XO_CONTINUE;
			}
			else
			{
				xs = XS_SIZE; //过渡到整形指示扫描
				xo = XO_PAUSE;
			}
			break;
		case XS_PREC:
			if(s_is_digit(*token))
			{
				tk_prec[prec_count ++] = *token;
				xs = XS_PREC; //继续精度扫描
				xo = XO_CONTINUE;
			}
			else
			{
				xs = XS_SIZE; //过渡到整形指示扫描
				xo = XO_PAUSE;
			}
			break;
		case XS_SIZE:
			if(s_is_size(*token))
			{
				xf_size = *token;
				xs = XS_TYPE; //过渡到格式符扫描
				xo = XO_CONTINUE;
			}
			else
			{
				xs = XS_TYPE; //过渡到格式符扫描
				xo = XO_PAUSE;
			}
			break;
		case XS_TYPE:
			if(s_is_type(*token))
			{
				xf_type = *token;
				xs = XS_PROC; //过渡到处理格式
				xo = XO_CONTINUE;
			}
			else
			{
				xs = XS_PROC; //无效格式符，则过渡到前缀串处理
				xo = XO_CONTINUE;
			}
			break;
		case XS_PROC:
			if(xf_type) //处理格式串
			{
				tk_width[width_count] = '\0';
				xf_width = atoi(tk_width);
				tk_prec[prec_count] = '\0';
				xf_prec = atoi(tk_prec);
				if(!xf_flag)
				{
					xf_flag = ' ';
				}

				if(xf_prec && xf_prec > DOUBLE_MAX_PRECISION) //限制最大精度为6
				{
					xf_prec = DOUBLE_MAX_PRECISION;
				}

				//处理这个单元的格式串
				_tk_sprintf(xf_flag,xf_width,xf_prec,xf_size,xf_type,&arg);

				if(*token == '\0')
				{
					xs = XS_TERM;
				}
				else
				{
					xs = XS_SKIP;
				}

				xo = XO_PAUSE;
			}
			else //处理前缀串
			{
				memcpy(m_lpBufCur, (void*)(token - tk_count), tk_count * sizeof(char));
				m_lpBufCur += tk_count;

				if(*token == '\0')
				{
					xs = XS_TERM;
				}
				else
				{
					xs = XS_SKIP;
				}

				xo = XO_PAUSE;
			}

			xf_flag = 0;
			xf_width = 0;
			xf_prec = 0;
			xf_size = 0;
			xf_type = 0;
			width_count = prec_count = tk_count = 0;

			break;
		}

		if(xo == XO_CONTINUE)
		{
			token ++;
			tk_count ++;
		}
	}

	va_end(arg);
	*m_lpBufCur = '\0';

	return (m_lpBufCur - m_pchData);
}
