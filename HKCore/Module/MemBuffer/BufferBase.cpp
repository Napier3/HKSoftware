#include "stdafx.h"
#include "BufferBase.h"
#include "../API/StringApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MENBUFFERLENEX  50

CBufferBase::CBufferBase()
{
    Init();
}

CBufferBase::CBufferBase(const CString &strBuff)
{
    Init();
    InitBuffer(strBuff);
}

CBufferBase::CBufferBase(const BSTR &bstrBuff)
{
    Init();
    InitBuffer(bstrBuff);
}

CBufferBase::CBufferBase(const char *pszBuff)
{
    Init();
    InitBuffer(pszBuff);
}

CBufferBase::CBufferBase(const CBufferBase *pBuffer)
{
    Init();
    InitBuffer(pBuffer);
}

CBufferBase::CBufferBase(const char *pBuffBegin,const char *pBuffEnd)
{
    Init();
    InitBuffer(pBuffBegin,pBuffEnd);
}

CBufferBase::~CBufferBase()
{
    Release();
}

void CBufferBase::Init()
{
	m_bAttatch = FALSE;
    m_nCurrBuffLen = 0;

    m_pszFileName = _T("");	//文件名
    m_pBuffer = NULL;		//文件存储区地址
    m_nLength = 0;			//文件长度
    m_pPointer = NULL;		//文件执行指针
    m_nLengthEx = 0;
    m_bFormartAllChar = true;
}

//2021-5-16  lijunqing 
void CBufferBase::Attatch(char *pszBuff)
{
	Release();
	m_nCurrBuffLen =  strlen(pszBuff);
	m_nLength = m_nCurrBuffLen;
	ResetPointer();
	m_bAttatch = TRUE;
	m_pBuffer = pszBuff;
}

char* CBufferBase::Dettatch()
{
	char*pBuffer = m_pBuffer;
	Release();
	return pBuffer;
}

//*********************************************************************
//ReadFromFile				public
//*********************************************************************
//描述：	从文件中获取数据
//参数：	strFile：文件名称
//返回：	无
BOOL CBufferBase::ReadFromFile(const char *pszFile)
{
    if (pszFile == NULL)
        return FALSE;

    return ReadFromFile(CString(pszFile));
}

//*********************************************************************
//ReadFromFile				public
//*********************************************************************
//描述：	从文件中获取数据
//参数：	strFile：文件名称
//返回：	无
BOOL CBufferBase::ReadFromFile(const CString &strFile)
{   
    Release();
    m_pszFileName = strFile;

#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
    InitLocalCodec_BeforeReadWrite(strFile,&pOldTextCodec);//将编码变为utf-8
#endif

    CFile file;
    BOOL bTrue = file.Open(strFile,CFile::modeRead);

#ifdef _PSX_QT_LINUX_
	ResetLocalCodec(pOldTextCodec);
	system("sync");//20220616 写文件后需要同步
#endif

    if(bTrue)
    {
        m_nLength = file.GetLength();
        m_pBuffer = new char [m_nLength+MENBUFFERLENEX];
        file.Read(m_pBuffer,m_nLength);
        m_pBuffer[m_nLength] = 0;
        file.Close();

        FormatBufferEx();
        ResetPointer();
    }
    return bTrue;
}

BOOL CBufferBase::WriteToFile(const char *pszFile)
{
    if (pszFile == NULL)
        return FALSE;

    return WriteToFile(CString(pszFile));
}

BOOL CBufferBase::WriteToFile(const CString &strFile)
{
    CFile file;
    BOOL bOpen = file.Open(strFile,CFile::modeCreate|CFile::modeWrite);
    if (bOpen)
    {
        file.Write(m_pBuffer,m_nLength);
        file.Close();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void CBufferBase::InitBuffer(long nBufferLength)
{
    if (m_nCurrBuffLen < nBufferLength || nBufferLength == 0)
    {
        Release();
        m_nCurrBuffLen = nBufferLength + MENBUFFERLENEX;
        m_pBuffer = new char [m_nCurrBuffLen+10];
    }

    m_nLength = nBufferLength;
    ZeroMemory(m_pBuffer,(m_nCurrBuffLen)*sizeof(char));
    ResetPointer();
}

//*********************************************************************
//InitBuffer				public
//*********************************************************************
//描述：	初始化缓冲区
//参数：	strBuff：文本数据
//返回：	无
void CBufferBase::InitBuffer(const CString &strBuff)
{
    long nLen = strBuff.GetLength();

#ifdef _UNICODE
    nLen *= 2;
    nLen += 10;
#endif

// 	if (m_nCurrBuffLen < nLen || nLen == 0)
// 	{
// 		Release();
// 		m_nCurrBuffLen = nLen + MENBUFFERLENEX;
// 		m_pBuffer = new char [m_nCurrBuffLen];
// 	}
//
// 	m_nLength = nLen;
// 	ZeroMemory(m_pBuffer,(m_nCurrBuffLen)*sizeof(char));
    InitBuffer(nLen);

    long nEndPos = CString_to_char(strBuff, m_pBuffer,m_nCurrBuffLen);
    //nLen = m_nCurrBuffLen - nEndPos;
    //ZeroMemory(m_pBuffer + nEndPos, nLen);
}

void CBufferBase::InitBuffer(const BSTR &bstrBuff)
{
    ASSERT( bstrBuff != NULL);

    long nLen = wcslen(bstrBuff);
    nLen *= 2;
    nLen += 10;

// 	if (m_nCurrBuffLen < nLen || nLen == 0)
// 	{
// 		Release();
// 		m_nCurrBuffLen = nLen + MENBUFFERLENEX;
// 		m_pBuffer = new char [m_nCurrBuffLen];
// 	}
//
// 	m_nLength = nLen;
// 	ZeroMemory(m_pBuffer,(m_nCurrBuffLen)*sizeof(char));
    InitBuffer(nLen);

    str_wchar_to_char( m_pBuffer, bstrBuff);
    //ResetPointer();
}

void CBufferBase::InitBuffer(const char* pszBuff)
{
    long nLen = strlen(pszBuff);

    //if (m_nCurrBuffLen < nLen || nLen == 0)
    //{
    //	Release();
    //	m_nCurrBuffLen = nLen + MENBUFFERLENEX;
    //	m_pBuffer = new char [m_nCurrBuffLen];
    //}

    //m_nLength = nLen;
    //ZeroMemory(m_pBuffer,(m_nCurrBuffLen)*sizeof(char));
    InitBuffer(nLen);

    strcpy(m_pBuffer, pszBuff);
    //ResetPointer();
}

void CBufferBase::InitBuffer(const CBufferBase *pBuffer)
{
    Release();
// 	m_nLength = pBuffer->m_nLength;
// 	m_pBuffer = new char [m_nLength+MENBUFFERLENEX];
// 	ZeroMemory(m_pBuffer,(m_nLength+MENBUFFERLENEX)*sizeof(char));
    InitBuffer(pBuffer->m_nLength);

    CopyMemory(m_pBuffer,pBuffer->m_pBuffer,m_nLength);
    m_pBuffer[m_nLength] = 0;
    //ResetPointer();
}

void CBufferBase::InitBuffer(const char *pBuffBegin,const char *pBuffEnd)
{
    ASSERT (pBuffBegin != NULL);
    ASSERT (pBuffEnd != NULL);
    if (pBuffBegin == NULL)
        return;
    if (pBuffEnd == NULL)
        return;

// 	Release();
// 	m_nLength = pBuffEnd - pBuffBegin;
// 	m_pBuffer = new char [m_nLength+MENBUFFERLENEX];
// 	ZeroMemory(m_pBuffer,(m_nLength+MENBUFFERLENEX)*sizeof(char));
    long nLen = pBuffEnd - pBuffBegin;
    InitBuffer(pBuffEnd - pBuffBegin);

    CopyMemory(m_pBuffer,pBuffBegin,m_nLength);
    m_pBuffer[m_nLength] = 0;
    //ResetPointer();
}

void CBufferBase::InitBufferEx(const CString &strBuff,long lSizeExpandRatio)
{
    Release();
    m_nLength = strBuff.GetLength();
    m_nLengthEx = m_nLength * lSizeExpandRatio / 100;
    m_nLength += m_nLengthEx;
    //m_pBuffer = new char [m_nLength+MENBUFFERLENEX];
    //ZeroMemory(m_pBuffer,(m_nLength+MENBUFFERLENEX)*sizeof(char));

#ifdef _UNICODE
    m_nLength *= 2;
#endif

    InitBuffer(m_nLength);

    CString_to_char(strBuff, m_pBuffer,m_nLength+MENBUFFERLENEX);

    //ResetPointer();
}

void CBufferBase::InitBufferEx(const CBufferBase *pBuffer,long lSizeExpandRatio)
{
    Release();
    m_nLength = pBuffer->m_nLength;
    m_nLengthEx = m_nLength * lSizeExpandRatio / 100;
    m_nLength += m_nLengthEx;
    //m_pBuffer = new char [m_nLength+MENBUFFERLENEX];
    //ZeroMemory(m_pBuffer,(m_nLength+MENBUFFERLENEX)*sizeof(char));
    InitBuffer(m_nLength);
    CopyMemory(m_pBuffer,pBuffer->m_pBuffer,m_nLength);

    ResetPointer();
}

//*********************************************************************
//FormatBuffer				public
//*********************************************************************
//描述：	格式化缓冲区
//参数：	无
//返回：	无
void CBufferBase::FormatBuffer()
{
    //格式化
    int i = 0;
    int iTemp = 0;
    for (i=0;i<m_nLength;i++)
    {
        //忽略掉注释行
        if ((m_pBuffer[i]=='/') && (m_pBuffer[i+1]=='/'))
        {
            iTemp = i;
            while((i<m_nLength) && (m_pBuffer[i]!=10 && m_pBuffer[i]!=13))
            {
                m_pBuffer[i]=0;
                i++;
            }
        }
    }
}

//*********************************************************************
//FormatBuffer				public
//*********************************************************************
//描述：	格式化缓冲区
//参数：	ch：格式化字符
//返回：	无
void CBufferBase::FormatBuffer(char ch,char chReplace)
{
    if(ch == 0)
    {
        return;
    }

    if (m_bFormartAllChar)
    {
        //格式化
        int i = 0;
        int iTemp = 0;
        for (i=0; i<m_nLength; i++)
        {
            if (m_pBuffer[i] == ch)
                m_pBuffer[i] = chReplace;
        }
    }
    else
    {
        FormatBufferAroundSeparate(ch,chReplace);
    }
}

void CBufferBase::FormatBuffer(char *pszText,char chReplace)
{
	long nLen = strlen(pszText);

	if (nLen == 0)
	{
		return;
	}

	char *p = m_pBuffer;
	char *pEnd = m_pBuffer + m_nLength - nLen;

	while (p < pEnd)
	{
		if (memcmp(p, pszText, nLen) == 0)
		{
			memset(p, chReplace, nLen);
			p += nLen;
		}
		else
		{
			p++;
		}
	}

}

void CBufferBase::EnableFormartAllChar(bool bEnable)
{
    m_bFormartAllChar = bEnable;
}

void CBufferBase::FormatBufferEx()
{
    //FormatBuffer('\r');
    //FormatBuffer('\n');
}

BOOL CBufferBase::Part(char *pszSrc,char *pszLeft,char *pszRight,char *pszPart,char *pszEnd)
{
    BOOL bTrue = TRUE;
    ASSERT(pszSrc != NULL);
    ASSERT(pszLeft != NULL);
    ASSERT(pszRight != NULL);
    ASSERT(pszPart != NULL);

    long lLenPart = strlen(pszPart);
    long lLenEnd = strlen(pszEnd);
    char *pTemp = NULL;
    char *pCurr = NULL;
    pCurr = pszSrc;
    //分隔符号左边
    while(TRUE)
    {
        if(*pCurr == 0)
        {
            bTrue = FALSE;
            break;
        }
        if(strncmp(pCurr,pszEnd,lLenEnd))
        {
            bTrue = FALSE;
            break;
        }
        if(strncmp(pCurr,pszPart,lLenPart))
            break;
        pCurr++;
    }
    if(!bTrue)
        return bTrue;
    pTemp = pszSrc;
    while(pTemp < pCurr)
    {
        *pszLeft = *pTemp;
        pszLeft++;
        pTemp++;
    }
    *pszLeft = 0;
    //跳过分隔符号 pszPart
    pCurr += lLenPart;
    //分隔符号右边
    if(pszEnd == NULL)
    {
        while(*pCurr!= 0)
        {
            *pszRight = *pCurr;
            pszRight++;
            pCurr++;
        }
    }
    else
    {
        while(TRUE)
        {
            if(*pCurr == 0)
                break;
            if(strncmp(pCurr,pszPart,lLenPart))
                break;
            *pszRight = *pCurr;
            pszRight++;
            pCurr++;
        }
    }
    *pszRight = 0;
    return bTrue;
}

BOOL CBufferBase::Part(char *pszSrc,char *pszLeft,char *pszRight,char cPart,char cEnd)
{
    BOOL bTrue = TRUE;
    ASSERT(pszSrc != NULL);
    ASSERT(pszLeft != NULL);
    ASSERT(pszRight != NULL);
    if(pszSrc == NULL)
        return FALSE;
    if(pszLeft == NULL)
        return FALSE;
    if(pszRight == NULL)
        return FALSE;

    char *pTemp = NULL;
    char *pCurr = NULL;
    pCurr = pszSrc;
    //分隔符号左边
    pTemp = pszLeft;
    while(TRUE)
    {
        if(*pCurr == 0)
        {
            bTrue = FALSE;
            break;
        }
        if(*pCurr == cEnd)
        {
            bTrue = FALSE;
            break;
        }
        if(*pCurr == cPart)
            break;
        pCurr++;
    }
    if(!bTrue)
        return bTrue;

    pTemp = pszSrc;
    while(pTemp < pCurr)
    {
        *pszLeft = *pTemp;
        pszLeft++;
        pTemp++;
    }
    *pszLeft = 0;
    //跳过分隔符号 cPart
    pCurr++;

    //分隔符号右边
    while(TRUE)
    {
        if(*pCurr == cEnd)
            break;
        *pszRight = *pCurr;
        pszRight++;
        pCurr++;
    }
    *pszRight = 0;

    return bTrue;
}

void CBufferBase::FormatBufferAroundSeparate(char ch,char chReplace)
{
    char *pTemp = m_pBuffer;
    char *pEqualPos = m_pBuffer;
    char *pBuffEndPos = GetBufferEndPos();
    char *pSrcBegin = m_pBuffer;
    char *pSrcEnd = NULL;
    char *pDest = m_pBuffer;

    //起始位置数据的格式化
    while (*pSrcBegin == ch)
    {
        *pSrcBegin = chReplace;
        pSrcBegin++;
    }

    while (IsPoiterInBuffer(pSrcBegin))
    {
        if (IsASeparateChar(*pSrcBegin))
        {
            //分隔符号前部的字符格式化
            pTemp = pSrcBegin - 1;
            while (IsPoiterInBuffer(pTemp) && *pTemp == ch)
            {
                *pTemp = chReplace;
                pTemp--;
            }

            //分隔符号后部的字符格式化
            pTemp = pSrcBegin + 1;
            while (IsPoiterInBuffer(pTemp) && *pTemp == ch)
            {
                *pTemp = chReplace;
                pTemp++;
            }
            pSrcBegin = pTemp;
        }
        else
        {
            pSrcBegin++;
        }
    }
}

//判断字符是否为分隔字符
bool CBufferBase::IsASeparateChar(char ch)
{
    return false;
}

//*********************************************************************
//Release				private
//*********************************************************************
//描述：	释放CBufferBase动态分配的缓冲区内存空间
//参数：	无
//返回：	无
void CBufferBase::Release()
{
    m_nCurrBuffLen = 0;
    m_nLength = 0;
    m_pPointer = NULL;

	if (m_bAttatch)
	{//2021-5-16  lijunqing
		m_pBuffer = NULL;
	}
	else
	{
		if(m_pBuffer != NULL)
		{
			delete []m_pBuffer;
			m_pBuffer = NULL;
		}
	}
}

char* CBufferBase::GetString()
{
    while(TRUE)
    {
        if (!IsPoiterInBuffer())
        {
            return NULL;
        }

        if (*m_pPointer != 0)
        {
            break;
        }

        m_pPointer++;
    }

    return m_pPointer;
}

char* CBufferBase::NextString()
{
    m_pPointer += strlen(m_pPointer);

    if (!IsPoiterInBuffer())
    {
        return NULL;
    }

    return GetString();
}

char* CBufferBase::GetBufferEndPos()
{
    return m_pBuffer + m_nLength;
}

char* CBufferBase::GetBufferBeginPos()
{
    return m_pBuffer;
}

void CBufferBase::ResetPointer()
{
    m_pPointer = m_pBuffer;
}

BOOL CBufferBase::IsLegal()
{
    return (m_pBuffer != NULL);
}


long CBufferBase::GetOffsetFromEnd(char *pPoint)
{
    long nLen = m_pPointer - m_pBuffer - m_nLength;
    return nLen;
}

BOOL CBufferBase::IsPoiterInBuffer()
{
    return IsPoiterInBuffer(m_pPointer);
}

BOOL CBufferBase::IsPoiterInBuffer(const char *p)
{
    if(p >= m_pBuffer && p < m_pBuffer + m_nLength)
        return TRUE;
    else
        return FALSE;
}


//////////////////////////////////////////////////////////////////////////
//CBufferBaseEx
CBufferBaseEx::CBufferBaseEx()
{
    m_nBufferMaxLength = 0;
}

CBufferBaseEx::~CBufferBaseEx()
{

}

void CBufferBaseEx::Release()
{
    CBufferBase::Release();
    m_nBufferMaxLength = 0;
}

void CBufferBaseEx::SetBufferLength(long nLen)
{
    if (nLen < m_nBufferMaxLength)
    {
        return;
    }

    Release();
    m_nBufferMaxLength = nLen+MENBUFFERLENEX;
    m_pBuffer = new char [m_nBufferMaxLength];

    ZeroMemory(m_pBuffer, m_nBufferMaxLength);
    m_nLength = nLen;
}

BOOL CBufferBaseEx::ReadFromFile(const CString &strFile, long nMaxBufferLen)
{
    m_pszFileName = strFile;

    CFile file;
    BOOL bTrue = file.Open(strFile,CFile::modeRead);

    if(bTrue)
    {
        long nLength =  file.GetLength();

        if (nLength > nMaxBufferLen)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("file length == [%d] > max length[%d][%s]")
                , nLength, nMaxBufferLen);
            nLength = nMaxBufferLen;
        }

        if (nLength > m_nBufferMaxLength)
        {
            Release();
            m_nBufferMaxLength = nLength+MENBUFFERLENEX;
            m_pBuffer = new char [m_nBufferMaxLength];
        }

        ZeroMemory(m_pBuffer, m_nBufferMaxLength);
        m_nLength = nLength;

        if (m_nLength > 0)
        {
            file.Read(m_pBuffer,m_nLength);
        }
        else
        {
            bTrue = FALSE;
        }

        m_pBuffer[m_nLength] = 0;

        file.Close();

        FormatBufferEx();
        ResetPointer();
    }
    else
    {

    }

    return bTrue;
}

void FormatBuffer(char *pBuffBegin,char *pBuffEnd,char ch,char chReplace)
{
    //格式化
    char *pTemp = pBuffBegin;
    while(pTemp<=pBuffEnd)
    {
        if (*pTemp == ch)
            *pTemp = chReplace;
        pTemp++;
    }
}

void StringToSystemTime(const CString &strTime, SYSTEMTIME &tmSys)
{
    char pszBuffer[128];
    CString_to_char(strTime, pszBuffer);
    char *pszTemp = pszBuffer;
    char *pszEnd = NULL;

    while (*pszTemp != 0)
    {
        if ('0' > *pszTemp || *pszTemp > '9')
        {
            *pszTemp = 0;
        }

        pszTemp++;
    }

    pszEnd = pszTemp;
    pszTemp = pszBuffer;

    pszTemp = GetString(pszTemp, pszEnd);

    if (pszTemp != NULL)
    {
        tmSys.wYear = atoi(pszTemp);
    }
    else
    {
        return;
    }

    pszTemp = NextString(pszTemp, pszEnd);
    if (pszTemp != NULL)
    {
        tmSys.wMonth = atoi(pszTemp);
    }
    else
    {
        return;
    }

    pszTemp = NextString(pszTemp, pszEnd);
    if (pszTemp != NULL)
    {
        tmSys.wDay = atoi(pszTemp);
    }
    else
    {
        return;
    }

    pszTemp = NextString(pszTemp, pszEnd);
    if (pszTemp != NULL)
    {
        tmSys.wHour = atoi(pszTemp);
    }
    else
    {
        return;
    }

    pszTemp = NextString(pszTemp, pszEnd);
    if (pszTemp != NULL)
    {
        tmSys.wMinute = atoi(pszTemp);
    }
    else
    {
        return;
    }

    pszTemp = NextString(pszTemp, pszEnd);
    if (pszTemp != NULL)
    {
        tmSys.wSecond = atoi(pszTemp);
    }
    else
    {
        return;
    }

    pszTemp = NextString(pszTemp, pszEnd);
    if (pszTemp != NULL)
    {
        tmSys.wMilliseconds = atoi(pszTemp);
    }
}
