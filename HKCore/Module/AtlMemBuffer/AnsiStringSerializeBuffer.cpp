// AnsiStringSerializeBuffer.cpp: implementation of the CAnsiStringSerializeBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AnsiStringSerializeBuffer.h"
#include "..\System\AtlFile.h"
#include "..\..\Module\System\GloblaApi.h"

const long CAnsiStringSerializeBuffer::DEFAULT_BUFF_LENGTH   = 1024;
const long CAnsiStringSerializeBuffer::NUMBER_TBUFFER_LENGTH = 40;
const long CAnsiStringSerializeBuffer::DOUBLE_MAX_PRECISION  = 6;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAnsiStringSerializeBuffer::CAnsiStringSerializeBuffer()
{
	Init();
	SetBufferLen(DEFAULT_BUFF_LENGTH);
}

CAnsiStringSerializeBuffer::CAnsiStringSerializeBuffer(int nLen)
{
	Init();
	SetBufferLen(nLen);
}

CAnsiStringSerializeBuffer::CAnsiStringSerializeBuffer(char *pBuff,int nLen)
{
	Init();
	SetBufferLen(nLen);
	memcpy(m_pchData,pBuff,nLen);
}

CAnsiStringSerializeBuffer::~CAnsiStringSerializeBuffer()
{
	FreeBuff();
}

 void CAnsiStringSerializeBuffer::Init()
{
	m_pchData = NULL;
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
}

 void CAnsiStringSerializeBuffer::FreeBuff()
{
	if (m_pchData != NULL)
	{
		delete m_pchData;
		m_pchData = NULL;
	}
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
}


void CAnsiStringSerializeBuffer::AllocMemBuff(long nLen)
{
	if (nLen <= 0)
	{
		nLen = DEFAULT_BUFF_LENGTH;
	}

	if (nLen < m_nBufferLength)
	{
		m_lpBufCur = m_pchData;
		m_lpBufMax = m_pchData + m_nBufferLength;
		return;
	}

	FreeBuff();
	m_nBufferLength = nLen;
	m_pchData = new char [m_nBufferLength+10];
	memset(m_pchData, 0, m_nBufferLength+1);
	m_lpBufCur = m_pchData;
	m_lpBufMax = m_pchData + m_nBufferLength;
}

void CAnsiStringSerializeBuffer::SetBufferLen(int nLen)
{
	AllocMemBuff(nLen);
}

int  CAnsiStringSerializeBuffer::GetBufferLen()
{
	return 	m_nBufferLength;
}

void CAnsiStringSerializeBuffer::ResetBuffCurr()
{
	m_lpBufCur = m_pchData;
}

//������������
long CAnsiStringSerializeBuffer::GetBuffer(VARIANT *pvarString)
{
	SAFEARRAYBOUND bound;
	SAFEARRAY * pFilter = NULL; 
	long lIndex = 0;
	
	bound.cElements = m_nBufferLength;
	bound.lLbound=0;
	pFilter = SafeArrayCreate(VT_UI1,1,&bound);
	
	for(int i = 0; i < m_nBufferLength; i++)
	{
		SafeArrayPutElement(pFilter,&lIndex,(void*)&m_pchData[i]);
		lIndex++;
	}		
	
	V_VT(pvarString) = VT_UI1 | VT_ARRAY; 
	V_ARRAY(pvarString) = pFilter; 
	
	return lIndex;
}

long CAnsiStringSerializeBuffer::GetBuffer2(BSTR *pbstr)
{
	char_to_BSTR(m_pchData, pbstr);
	return 0;//AnsiStrToBSTR(m_pchData,pbstr);
}


//long CAnsiStringSerializeBuffer::GetBuffer(SysTool::IStringSerialBufferPtr &oSBuffer)
//{
//	BSTR bstr;
//	GetBuffer2(&bstr);
//	oSBuffer->SetBufferLength(m_nBufferLength);
//	oSBuffer->put_String(bstr);
//	::SysFreeString(bstr);
//}
//
long CAnsiStringSerializeBuffer::WriteString(const char *pstrData)
{
	ReAllocMemBuff(strlen(pstrData));
	
	while(*pstrData != 0)
	{
		*m_lpBufCur = *pstrData;
		m_lpBufCur++;
		pstrData++;
	}
	
	*m_lpBufCur = 0;
	
	return 0;
}

long CAnsiStringSerializeBuffer::WriteString(BSTR &bstrData)
{
	long lLen = wcslen(bstrData);
	ReAllocMemBuff(lLen * 2);
	
	int nLen = WideCharToMultiByte(CP_ACP, 0, bstrData, -1, 
		m_lpBufCur, lLen * 2, NULL, NULL);
	
	if (nLen > 0)
	{
		m_lpBufCur += (nLen-1);
	}
	
	return (m_lpBufCur - m_pchData);
}

long CAnsiStringSerializeBuffer::WriteLong(long nVal, long nWidth, bool bFill0)
{
	char pTempBuffer[NUMBER_TBUFFER_LENGTH];
	ReAllocMemBuff(NUMBER_TBUFFER_LENGTH);
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


long CAnsiStringSerializeBuffer::WriteUnsignedLong(unsigned long nVal, long nWidth, bool bFill0)
{
	char pTempBuffer[NUMBER_TBUFFER_LENGTH];
	ReAllocMemBuff(NUMBER_TBUFFER_LENGTH);
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

long CAnsiStringSerializeBuffer::WriteHex(unsigned long nVal, long it, long nWidth, bool bFill0)
{
	char pTempBuffer[NUMBER_TBUFFER_LENGTH];
	ReAllocMemBuff(NUMBER_TBUFFER_LENGTH);
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

long CAnsiStringSerializeBuffer::WriteDouble(double dVal, long nWidth, bool bFill0, long nPrecision)
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

	//����
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
	WriteUnsignedLong(nLVal, nPrecision, true);
	
	return 0;
}

//���ӻ������ĳ���
long CAnsiStringSerializeBuffer::IncreaseBuffLen(long lLen)	
{
	m_nBufferLength += lLen;
	return m_nBufferLength;
}

BOOL CAnsiStringSerializeBuffer::WriteToFile(const char *pszFile)
{
	CAtlFile file;
	
	if ( ! file.Open(pszFile, CAtlFile::modeCreate | CAtlFile::modeWrite | CAtlFile::typeText))
	{
		return FALSE;
	}

	file.WriteHuge(m_pchData, m_lpBufCur - m_pchData);
	file.Close();

	return TRUE;
}

int CAnsiStringSerializeBuffer::sprintf(const char* fmt, ...)
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
	
    //��ʼ��
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
                    xs = XS_FLAG; //û��ǰ׺������ɵ���ʽ��ɨ��
                    xo = XO_CONTINUE;
                }
				else
                {
                    xs = XS_PROC; //��ǰ׺�����ȴ���ǰ׺��
                    xo = XO_PAUSE;
                }
            }
			else if(*token == '\0')
            {
                xs = XS_PROC; //���ɵ�����ǰ׺��
                xo = XO_PAUSE;
            }
			else
            {
                xs = XS_SKIP; //����ǰ׺��ɨ��
                xo = XO_CONTINUE;
            }
            break;
        case XS_FLAG:
            if(s_is_flag(*token))
            {
                xf_flag = *token;
                xs = XS_FLAG; //����ռλ��ɨ��
                xo = XO_CONTINUE;
            }
			else
            {
                xs = XS_WIDTH; //���ɵ�ռλ��ɨ��
                xo = XO_PAUSE;
            }
            break;
        case XS_WIDTH:
            if(s_is_digit(*token))
            {
                tk_width[width_count ++] = *token;
                xs = XS_WIDTH; //����ռλ��ɨ��
                xo = XO_CONTINUE;
            }
			else if(*token == '.')
            {
                xs = XS_PREC; //���ɵ�����ɨ��
                xo = XO_CONTINUE;
            }
			else
            {
                xs = XS_SIZE; //���ɵ�����ָʾɨ��
                xo = XO_PAUSE;
            }
            break;
        case XS_PREC:
            if(s_is_digit(*token))
            {
                tk_prec[prec_count ++] = *token;
                xs = XS_PREC; //��������ɨ��
                xo = XO_CONTINUE;
            }
			else
            {
                xs = XS_SIZE; //���ɵ�����ָʾɨ��
                xo = XO_PAUSE;
            }
            break;
        case XS_SIZE:
            if(s_is_size(*token))
            {
                xf_size = *token;
                xs = XS_TYPE; //���ɵ���ʽ��ɨ��
                xo = XO_CONTINUE;
            }
			else
            {
                xs = XS_TYPE; //���ɵ���ʽ��ɨ��
                xo = XO_PAUSE;
            }
            break;
        case XS_TYPE:
            if(s_is_type(*token))
            {
                xf_type = *token;
                xs = XS_PROC; //���ɵ������ʽ
                xo = XO_CONTINUE;
            }
			else
            {
                xs = XS_PROC; //��Ч��ʽ��������ɵ�ǰ׺������
                xo = XO_CONTINUE;
            }
            break;
        case XS_PROC:
            if(xf_type) //�����ʽ��
            {
                tk_width[width_count] = '\0';
                xf_width = atoi(tk_width);
                tk_prec[prec_count] = '\0';
                xf_prec = atoi(tk_prec);
                if(!xf_flag)
				{
					xf_flag = ' ';
				}
				
                if(xf_prec && xf_prec > DOUBLE_MAX_PRECISION) //������󾫶�Ϊ6
				{
					xf_prec = DOUBLE_MAX_PRECISION;
				}
				
                //���������Ԫ�ĸ�ʽ��
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
			else //����ǰ׺��
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


int CAnsiStringSerializeBuffer::_tk_sprintf(char flag,int width,int prec,char size,char type,va_list* parg)
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
			BSTR bstr =  va_arg(*parg, BSTR);
			WriteString(bstr);
			break;
		}
		
	default :
		break;
	}
	
    return 0;
}
