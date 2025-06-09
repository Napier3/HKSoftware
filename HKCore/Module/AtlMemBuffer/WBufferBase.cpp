#include "stdafx.h"
#include "WBufferBase.h"
// #include "..\AtlBaseClass\AtlFile.h"
//#include "..\AtlBaseClass\ATLGloblaApi.h"

#define MENBUFFERLENEX  50

CWBufferBase::CWBufferBase()
{
	Init();
}

CWBufferBase::CWBufferBase(const CComBSTR &strBuff)
{
	Init();

	InitBuffer(strBuff);
}

CWBufferBase::CWBufferBase(wchar_t* pszBuff)
{
	Init();
	InitBuffer(pszBuff);
}

CWBufferBase::CWBufferBase(const CWBufferBase *pBuffer)
{
	Init();
	InitBuffer(pBuffer);
}

CWBufferBase::CWBufferBase(wchar_t* pBuffBegin,wchar_t* pBuffEnd)
{
	Init();
	InitBuffer(pBuffBegin,pBuffEnd);
}

CWBufferBase::~CWBufferBase()
{
	Release();
}

void CWBufferBase::Init()
{
	m_nBufferLength = 0;

	m_pBuffer = NULL;		//文件存储区地址
	m_nLength = 0;			//文件长度
	m_pPointer = NULL;		//文件执行指针
	m_bFormartAllChar = true;
}

//*********************************************************************
//ReadFromFile				public
//*********************************************************************
//描述：	从文件中获取数据
//参数：	strFile：文件名称
//返回：	无
BOOL CWBufferBase::ReadFromFile(const CComBSTR &strFile)
{
	Release();

	USES_CONVERSION;   
	LPCTSTR   szFile;   
	szFile   =   W2T(strFile);
	
	CFile file;
	BOOL bTrue = file.Open(szFile, CFile::modeRead);
	if(bTrue)
	{
		m_nLength = file.GetLength();
		AllocMemBuffer(m_nLength);
		file.Read(m_pBuffer,m_nLength*sizeof(wchar_t));
		m_pBuffer[m_nLength] = 0;
		file.Close();

		FormatBufferEx();
		ResetPointer();
	}

	return bTrue;
}

BOOL CWBufferBase::WriteToFile(const CComBSTR &strFile)
{
	CFile file;
	USES_CONVERSION;   
	LPCTSTR   szFile;   
	szFile   =   W2T(strFile);
    BOOL bOpen = file.Open(szFile, CFile::modeCreate|CFile::modeWrite);

	if (bOpen)
	{
		file.Write(m_pBuffer,m_nLength*sizeof(wchar_t));
		file.Close();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//*********************************************************************
//InitBuffer				public
//*********************************************************************
//描述：	初始化缓冲区
//参数：	strBuff：文本数据
//返回：	无
void CWBufferBase::InitBuffer(const CComBSTR &strBuff)
{
	long nLen = strBuff.Length();
	
	AllocMemBuffer(nLen);
	wcscpy(m_pBuffer,strBuff);
	ResetPointer();
}

void CWBufferBase::InitBuffer(BSTR strBuff)
{
	long nLen = wcslen(strBuff);
	
	AllocMemBuffer(nLen);
	wcscpy(m_pBuffer,strBuff);
	ResetPointer();
}

void CWBufferBase::AllocMemBuffer(long nBufferLen)
{
	if (m_nBufferLength < nBufferLen || nBufferLen <= 0)
	{
		Release();
		m_nBufferLength = nBufferLen + MENBUFFERLENEX;
		m_pBuffer = new wchar_t [m_nBufferLength];
	}
	else
	{
	}

	m_nLength = nBufferLen;	
	ZeroMemory(m_pBuffer,(m_nBufferLength)*sizeof(wchar_t));
}

void CWBufferBase::InitBuffer(const CWBufferBase *pBuffer)
{
	AllocMemBuffer(pBuffer->m_nLength);
	CopyMemory(m_pBuffer,pBuffer->m_pBuffer, m_nLength*sizeof(wchar_t));
	m_pBuffer[m_nLength] = 0;
	ResetPointer();
}

void CWBufferBase::InitBuffer(wchar_t* pBuffBegin,wchar_t* pBuffEnd)
{
	if (pBuffBegin == NULL || pBuffEnd == NULL)
		return;

	long nLen = pBuffEnd - pBuffBegin+1;
	AllocMemBuffer(nLen);
	CopyMemory(m_pBuffer,pBuffBegin,m_nLength);
	m_pBuffer[m_nLength] = 0;
	ResetPointer();
}

void CWBufferBase::InitBufferEx(const CComBSTR &strBuff,long lSizeExpandRatio)
{
	long nLenEx = strBuff.Length();
	nLenEx = (long)(nLenEx * (100 + lSizeExpandRatio) / 100.f);
	AllocMemBuffer(nLenEx);
	wcscpy(m_pBuffer,strBuff);
	ResetPointer();
}

void CWBufferBase::InitBufferEx(const CWBufferBase *pBuffer,long lSizeExpandRatio)
{
	long nLenEx = pBuffer->m_nLength;
	nLenEx = (long)(nLenEx * (100 + lSizeExpandRatio) / 100.f);
	AllocMemBuffer(nLenEx);
	CopyMemory(m_pBuffer, pBuffer->m_pBuffer, pBuffer->m_nLength);
	
	ResetPointer();
}

//*********************************************************************
//FormatBuffer				public
//*********************************************************************
//描述：	格式化缓冲区
//参数：	无
//返回：	无
void CWBufferBase::FormatBuffer()
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
void CWBufferBase::FormatBuffer(wchar_t ch, wchar_t chReplace)
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

void CWBufferBase::EnableFormartAllChar(bool bEnable)
{
	m_bFormartAllChar = bEnable;
}

void CWBufferBase::FormatBufferEx()
{
	//FormatBuffer('\r');
	//FormatBuffer('\n');
}

BOOL CWBufferBase::Part(wchar_t *pszSrc,wchar_t *pszLeft,wchar_t *pszRight,wchar_t *pszPart,wchar_t *pszEnd)
{
	BOOL bTrue = TRUE;
	if (pszSrc==NULL || pszLeft==NULL || pszRight==NULL || pszPart==NULL)
	{
		return FALSE;
	}

	long lLenPart = wcslen(pszPart);
	long lLenEnd = wcslen(pszEnd);
	wchar_t *pTemp = NULL;
	wchar_t *pCurr = NULL;
	pCurr = pszSrc;

	//分隔符号左边
	while(TRUE)
	{
		if(*pCurr == 0)
		{
			bTrue = FALSE;
			break;
		}
		
		if(wcsncmp(pCurr, pszEnd, lLenEnd))
		{
			bTrue = FALSE;
			break;
		}

		if(wcsncmp(pCurr, pszPart, lLenPart))
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
	pCurr += lLenPart;	//跳过分隔符号 pszPart

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

			if(wcsncmp(pCurr,pszPart,lLenPart))
				break;

			*pszRight = *pCurr;
			pszRight++;
			pCurr++;
		}
	}
	
	*pszRight = 0;
	return bTrue;
}

BOOL CWBufferBase::Part(wchar_t *pszSrc,wchar_t *pszLeft,wchar_t *pszRight,wchar_t cPart,wchar_t cEnd)
{
	BOOL bTrue = TRUE;
	if (pszSrc == NULL || pszLeft==NULL || pszRight==NULL)
	{
		return FALSE;
	}

	wchar_t *pTemp = NULL;
	wchar_t *pCurr = NULL;
	pCurr = pszSrc;
	pTemp = pszLeft;
	
	//分隔符号左边
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
	pCurr++;	//跳过分隔符号 cPart

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

void CWBufferBase::FormatBufferAroundSeparate(wchar_t ch,wchar_t chReplace)
{
	wchar_t *pTemp = m_pBuffer;
	wchar_t *pEqualPos = m_pBuffer;
	wchar_t *pBuffEndPos = GetBufferEndPos();
	wchar_t *pSrcBegin = m_pBuffer;
	wchar_t *pSrcEnd = NULL;
	wchar_t *pDest = m_pBuffer;
	
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
bool CWBufferBase::IsASeparateChar(wchar_t ch)
{
	return false;
}

//*********************************************************************
//Release				private
//*********************************************************************
//描述：	释放CWBufferBase动态分配的缓冲区内存空间
//参数：	无
//返回：	无
void CWBufferBase::Release()
{
	m_nBufferLength = 0;
	m_nLength = 0;
	m_pPointer = NULL;
	
	if(m_pBuffer != NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
}

wchar_t* CWBufferBase::GetString()
{
	while(!*m_pPointer)
		m_pPointer++;

	return m_pPointer;
}

wchar_t* CWBufferBase::NextString() 
{
	m_pPointer += wcslen(m_pPointer);
	return GetString();
}

wchar_t* CWBufferBase::GetBufferEndPos()
{
	return m_pBuffer + m_nLength;
}

wchar_t* CWBufferBase::GetBufferBeginPos()
{
	return m_pBuffer;
}

void CWBufferBase::ResetPointer()
{
	m_pPointer = m_pBuffer;
}

BOOL CWBufferBase::IsLegal()
{
	return (m_pBuffer != NULL);
}

BOOL CWBufferBase::IsPoiterInBuffer()
{
	return IsPoiterInBuffer(m_pPointer);
}

BOOL CWBufferBase::IsPoiterInBuffer(wchar_t* p)
{
	return (p >= m_pBuffer && p < m_pBuffer + m_nLength);
}

void FormatBuffer(wchar_t *pBuffBegin,wchar_t *pBuffEnd,wchar_t ch,wchar_t chReplace)
{
	wchar_t *pTemp = pBuffBegin;

	while(pTemp<=pBuffEnd)
	{
		if (*pTemp == ch)
			*pTemp = chReplace;

		pTemp++;
	}
}
