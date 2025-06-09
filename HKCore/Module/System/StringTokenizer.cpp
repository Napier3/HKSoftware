// StringTokenizer.cpp: implementation of the CStringTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringTokenizer.h"

#include "../API/StringApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringTokenizer::CStringTokenizer()
{
	m_pData = NULL;
	m_chDelimiter = ' ';
	m_pIndex = NULL;
	m_nLength = 0;
	m_bAttach = FALSE;
}

CStringTokenizer::CStringTokenizer(const char *pszDataLine)
{
	m_pData = NULL;
	m_chDelimiter = ' ';
	m_pIndex = NULL;
	m_nLength = 0;
	
	Init(pszDataLine,' ');
	m_bAttach = FALSE;
}

CStringTokenizer::CStringTokenizer(const char *pszDataLine,char chDelimiter)
{
	m_pData = NULL;
	m_chDelimiter = ' ';
	m_pIndex = NULL;
	m_nLength = 0;
	Init(pszDataLine,chDelimiter);
	m_bAttach = FALSE;
}

CStringTokenizer::~CStringTokenizer()
{
	Free();
}

void CStringTokenizer::Free()
{
	if (m_pData != NULL)
	{
		if (!m_bAttach)
		{
			delete m_pData;
		}

		m_pData = NULL;
	}

	m_pIndex = NULL;
	m_nLength = 0;
	m_bAttach = FALSE;
}

void CStringTokenizer::Format(char chDelimiter)
{
	if (!m_bAttach)
	{
		m_pData[m_nLength] = 0;
		m_pData[m_nLength+1] = 0;
	}

	char *pTemp = m_pData;
	char *pEnd = m_pData + m_nLength;

	while (pTemp < pEnd)
	{
		if (*pTemp == chDelimiter)
		{
			*pTemp = 0;
		}

		pTemp++;
	}

	m_pIndex = m_pData;
}

void CStringTokenizer::Init(const char *pszDataLine,char chDelimiter)
{
	Free();

	if (pszDataLine == NULL)
	{
		return;
	}

	m_chDelimiter = chDelimiter;
	m_nLength = strlen(pszDataLine) + 1;
	m_pData = new char [m_nLength+3];
	//ZeroMemory(m_pData, m_nLength+3);
	memcpy(m_pData,pszDataLine,m_nLength);

	Format(chDelimiter);
// 	m_pData[m_nLength-1] = chDelimiter;
// 	m_pData[m_nLength] = 0;
// 
// 	char *pTemp = m_pData;
// 	while (*pTemp != 0)
// 	{
// 		if (*pTemp == chDelimiter)
// 		{
// 			*pTemp = 0;
// 		}
// 		pTemp++;
// 	}
// 
// 	m_pIndex = m_pData;
}

void CStringTokenizer::AttatchInit(char *pszDataLine,char chDelimiter)
{
	Free();

	if (pszDataLine == NULL)
	{
		return;
	}

	m_bAttach = TRUE;
	m_chDelimiter = chDelimiter;
	m_nLength = strlen(pszDataLine) + 1;
	m_pData = pszDataLine;
	Format(chDelimiter);
}

void CStringTokenizer::Init(const CString &strDataLine,char chDelimiter)
{
	Free();

    m_nLength = strDataLine.GetLength() + 1;

    CString_to_char(strDataLine, &m_pData);

/*
#ifdef _UNICODE
	long nLength = m_nLength * 2 + 2;
	m_pData = new char[nLength];
	_wsetlocale(LC_ALL,_T("chs"));
	size_t sz=0;
	wcstombs_s(&sz, m_pData, nLength, strDataLine,_TRUNCATE);
	_wsetlocale(LC_ALL,_T("eng"));
#else
	m_pData = new char [m_nLength+10];
	strcpy(m_pData, strDataLine);
#endif
*/

/*
#ifdef _UNICODE
	m_nLength = m_nLength * 2 + 2;
	m_pData = new char[m_nLength];
	_wsetlocale(LC_ALL,_T("chs"));
	size_t sz=0;
	wcstombs_s(&sz, m_pData, m_nLength, strDataLine,_TRUNCATE);
	_wsetlocale(LC_ALL,_T("eng"));
#else
	m_pData = new char [m_nLength+10];
	strcpy(m_pData, strDataLine);
#endif
*/

	Format(chDelimiter);
}

BOOL CStringTokenizer::HasMoreElements()
{
	BOOL bTrue = TRUE;
	if (m_pIndex == NULL || m_pData == NULL || m_nLength <= 0)
	{
		bTrue = FALSE;
	}

	if (bTrue)
	{
		if (m_pIndex >= m_pData && m_pIndex < m_pData + m_nLength)
		{
			bTrue = TRUE;
		}
		else
		{
			bTrue = FALSE;
		}
	}

	return bTrue;
}

const char* CStringTokenizer::NextToken()
{
	if (m_pIndex == NULL || m_pData == NULL)
		return NULL;
	
	char *pString = NULL;
	char *pTemp = m_pIndex;
	char *pEnd = m_pData + m_nLength;

	//get current string and move to next string
	//if (pTemp < pEnd)   //2019-8-23  lijunqing
	if (pTemp < pEnd)
	{
		pString = pTemp;
		m_pIndex = pString + strlen(pString) + 1;
	}
	else
	{
		m_pIndex = pEnd;
	}

	return pString;
}

const char* CStringTokenizer::GetToken(long nIndex)
{
	if (m_pIndex == NULL || m_pData == NULL)
		return NULL;

	char *pString = NULL;
	char *pTemp = m_pData;
	char *pEnd = m_pData + m_nLength;
	long nStringIndex = 0;

	while (pTemp < pEnd)
	{
		if (*pTemp == 0)
		{
			pTemp++;
			continue;
		}

		if (nStringIndex == nIndex)
		{
			pString = pTemp;
			break;
		}
		else
		{
			nStringIndex++;
			pTemp = pTemp + strlen(pTemp) + 1;
		}
	}

	return pString;
}

void CStringTokenizer::ResetIndexPointer()
{
	m_pIndex = m_pData;
}

long CStringTokenizer::GetStringsCount()
{
	long nCount = 0;
	char *pTemp = m_pData;
	char *pEnd = m_pData + m_nLength;
	
	//get current string and move to next string
	while (pTemp < pEnd)
	{
		if (*pTemp == 0)
		{
			nCount++;
		}
		pTemp++;
	}
	return nCount;
}

//xxy 20210427
BOOL CStringTokenizer::HasSubString(const CString &strSub)
{
	ASSERT(!strSub.IsEmpty());
	CString str;
	BOOL bRet = FALSE;

	while(TRUE)
	{
		str = NextToken();

		if (strSub == str)
		{
			bRet = TRUE;
		}

		if (str.IsEmpty())
		{
			break;
		}
	}

	ResetIndexPointer();
	return bRet;
}