// AnsiStringPrintf.cpp: implementation of the CAnsiStringPrintf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AnsiStringPrintf.h"

const long CAnsiStringPrintf::NUMBER_TBUFFER_LENGTH = 40;
const long CAnsiStringPrintf::DOUBLE_MAX_PRECISION  = 6;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CAnsiStringPrintf::CAnsiStringPrintf()
{
	Init();
}

CAnsiStringPrintf::CAnsiStringPrintf(char *pDestBuff)
{
	Init();
	m_pchData = pDestBuff;
	m_lpBufCur = m_pchData;
}

CAnsiStringPrintf::~CAnsiStringPrintf()
{
	Init();
}

void CAnsiStringPrintf::Init()
{
	m_pchData = NULL;
	m_lpBufCur = NULL;
}

#ifndef _PSX_IDE_QT_
//缓冲区的数据
long CAnsiStringPrintf::GetBuffer(VARIANT *pvarString)
{
	SAFEARRAYBOUND bound;
	SAFEARRAY * pFilter = NULL; 
	long lIndex = 0;
	long nLen = m_lpBufCur - m_pchData;

	bound.cElements = nLen;
	bound.lLbound=0;
	pFilter = SafeArrayCreate(VT_UI1,1,&bound);
	
	for(int i = 0; i < nLen; i++)
	{
		SafeArrayPutElement(pFilter,&lIndex,(void*)&m_pchData[i]);
		lIndex++;
	}		
	
	V_VT(pvarString) = VT_UI1 | VT_ARRAY; 
	V_ARRAY(pvarString) = pFilter; 
	
	return lIndex;
}

long CAnsiStringPrintf::GetBuffer2(BSTR *pbstr)
{
	return 0;//AnsiStrToBSTR(m_pchData,pbstr);
}
#endif

long CAnsiStringPrintf::WriteString(const char *pstrData)
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

#ifndef _PSX_IDE_QT_
long CAnsiStringPrintf::WriteString(BSTR &bstrData)
{
	long lLen = wcslen(bstrData);
	
	int nLen = WideCharToMultiByte(CP_ACP, 0, bstrData, -1, 
		m_lpBufCur, lLen * 2, NULL, NULL);
	
	m_lpBufCur += (nLen-1);
	
	return (m_lpBufCur - m_pchData);
}
#endif

long CAnsiStringPrintf::WriteLong(long nVal, long nWidth, bool bFill0)
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


long CAnsiStringPrintf::WriteUnsignedLong(unsigned long nVal, long nWidth, bool bFill0)
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

long CAnsiStringPrintf::WriteHex(unsigned long nVal, long it, long nWidth, bool bFill0)
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

long CAnsiStringPrintf::WriteDouble(double dVal, long nWidth, bool bFill0, long nPrecision)
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
	WriteUnsignedLong(nLVal, 0, false);
	
	return 0;
}

int CAnsiStringPrintf::sprintf(const char* fmt, ...)
{
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


int CAnsiStringPrintf::_tk_sprintf(char flag, int width, int prec, char size, char type, va_list* parg)
{
    switch(type)
    {
    case 'c':
		{
			char ch = va_arg(*parg,char);
			WriteChar(ch);
			break;
		}
    case 'C':
		{
			wchar_t wch;
			wch = va_arg(*parg,wchar_t);
			WriteWChar(wch);
			break;
		}
    case 'd':
		{
			long nVal = va_arg(*parg, long);
			WriteLong(nVal, width, true);
			break;
		}
    case 'u':
		{
			unsigned long un = va_arg(*parg,unsigned long);
			WriteUnsignedLong(un, 0, false);
			break;
		}
	case 'x':
		{
			unsigned long n = va_arg(*parg,unsigned long);
			WriteHex(n, IT_HEX_LOW, width, true);
			break;
		}
	case 'X':
		{
			unsigned long n = va_arg(*parg,unsigned long);
			WriteHex(n, IT_HEX, width, true);
			break;
		}
	case 'o':
	case 'O':
		{
			unsigned long n = va_arg(*parg,unsigned long);
			WriteHex(n, IT_OCTAL, width, true);
			break;
		}
	case 'b':
	case 'B':
		{
			unsigned long n = va_arg(*parg,unsigned long);
			WriteHex(n, IT_BINARY, width, true);
			break;
		}
	case 'f':
		{
			double d = va_arg(*parg,double);
			WriteDouble(d, width, true, prec);
			break;
		}
    case 's':
		{
			char *pstr =  va_arg(*parg,char*);
			WriteString(pstr);
			break;
		}
    case 'S':
		{
#ifndef _PSX_IDE_QT_
            BSTR bstr =  va_arg(*parg, BSTR);
			WriteString(bstr);
#endif
			break;
		}
		
	default :
		break;
	}
	
    return 0;
}
