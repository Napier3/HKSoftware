// StringTokenizerU.cpp: implementation of the CStringTokenizerU class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StringTokenizerU.h"

#ifndef _PSX_QT_LINUX_
#include "oleauto.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringTokenizerU::CStringTokenizerU()
{
	m_pData = NULL;
	m_chDelimiter = ' ';
	m_pIndex = NULL;
	m_nLength = 0;
}

CStringTokenizerU::CStringTokenizerU(const wchar_t *pszDataLine)
{
	m_pData = NULL;
	m_chDelimiter = ' ';
	m_pIndex = NULL;
	m_nLength = 0;
	
	Init(pszDataLine,' ');
}

CStringTokenizerU::CStringTokenizerU(const wchar_t *pszDataLine,wchar_t chDelimiter)
{
	m_pData = NULL;
	m_chDelimiter = ' ';
	m_pIndex = NULL;
	m_nLength = 0;
	Init(pszDataLine,chDelimiter);
}

CStringTokenizerU::~CStringTokenizerU()
{
	Free();
}

void CStringTokenizerU::Free()
{
	if (m_pData != NULL)
	{
		delete m_pData;
		m_pData = NULL;
	}

	m_pIndex = NULL;
	m_nLength = 0;
}

void CStringTokenizerU::Format(wchar_t chDelimiter)
{
	m_pData[m_nLength] = chDelimiter;
	m_pData[m_nLength+1] = 0;

	wchar_t *pTemp = m_pData;
	while (*pTemp != 0)
	{
		if (*pTemp == chDelimiter)
		{
			*pTemp = 0;
		}
		pTemp++;
	}

	m_pIndex = m_pData;
}

void CStringTokenizerU::Init(const wchar_t *pszDataLine,wchar_t chDelimiter)
{
	Free();

	if (pszDataLine == NULL)
	{
		return;
	}

	m_chDelimiter = chDelimiter;
	m_nLength = wcslen(pszDataLine);
	m_pData = new wchar_t [m_nLength+2];
	memcpy(m_pData,pszDataLine,m_nLength);

	Format(chDelimiter);
}

void CStringTokenizerU::Init(const CString &strDataLine,wchar_t chDelimiter)
{
	Free();

	m_nLength = strDataLine.GetLength();

	m_pData = new wchar_t[m_nLength + 2];

#ifdef _UNICODE
	wcscpy(m_pData, strDataLine);
#else
	BSTR bstr = strDataLine.AllocSysString();
	wcscpy(m_pData, bstr);

#ifdef _PSX_IDE_QT_//zhouhj 20201230 在Qt Windows下,采用另外一种方式,会报错
	delete bstr;
#else
	::SysFreeString(bstr);
#endif
//	
#endif

	Format(chDelimiter);
}

BOOL CStringTokenizerU::HasMoreElements()
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

const wchar_t* CStringTokenizerU::NextToken()
{
	if (m_pIndex == NULL || m_pData == NULL)
		return NULL;
	
	wchar_t *pString = NULL;
	wchar_t *pTemp = m_pIndex;
	wchar_t *pEnd = m_pData + m_nLength;

	if (pTemp != pEnd)
	{
		pString = pTemp;
		m_pIndex = pString + wcslen(pString) + 1;
	}
	else
	{
		m_pIndex = pEnd;
	}

	return pString;
}

void CStringTokenizerU::ResetIndexPointer()
{
	m_pIndex = m_pData;
}

long CStringTokenizerU::GetStringsCount()
{
	long nCount = 0;
	wchar_t *pTemp = m_pData;
	wchar_t *pEnd = m_pData + m_nLength;
	
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

