// LanguageNameParser.cpp: implementation of the CLanguageNameParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LanguageNameParser.h"
#include "LanguageMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char CLanguageNameParser::g_chLanguageSeparator = '$';

CLanguageNameParser::CLanguageNameParser()
{
	memset((void*)(&m_oLanguageString), 0, sizeof(LANGUAGESTRING)*MAX_LanguageString);
	m_pLanguageStringBuffer = new char[LanguageString_Buffer_DefLen];
	m_nLanguageStringBufferLen = LanguageString_Buffer_DefLen;
	m_pCurrLanguageStringPos = NULL;
	m_nLanguageStringCount = 0; 
}

CLanguageNameParser::~CLanguageNameParser()
{
	delete m_pLanguageStringBuffer;
	m_pLanguageStringBuffer = NULL;
}

long CLanguageNameParser::ParseLanguageString(CString &strName)
{
	memset((void*)(&m_oLanguageString), 0, sizeof(LANGUAGESTRING)*MAX_LanguageString);
	m_nLanguageStringCount = 0;

	InitBuffer(strName);

	char *pTemp = GetBufferBeginPos();
	char *pEnd = GetBufferEndPos();
	char *pLangBegin = NULL;
	char *pLangEnd = NULL;

	while (pTemp <= pEnd)
	{
		if (*pTemp == g_chLanguageSeparator)
		{
			if (pLangBegin == NULL)
			{
				pLangBegin = pTemp;
				*pTemp = 0;
			}
			else
			{
				pLangEnd = pTemp;
				*pTemp = 0;
				m_oLanguageString[m_nLanguageStringCount].pLanguageStringBegin = pLangBegin+1;
				m_oLanguageString[m_nLanguageStringCount].pLanguageStringEnd = pLangEnd-1;
				pLangBegin = NULL;
				pLangEnd = NULL;
				m_nLanguageStringCount++;
			}
		}
		
		pTemp++;
	}

	if (pLangBegin != NULL)
	{
		CString strTemp;
		strTemp.Format(_T("Error Langeuage String: [%s]"), strName);
		debug_trace(strTemp);
	}

	Parse();
	strName = m_pLanguageStringBuffer;

	return m_nLanguageStringCount;
}

void CLanguageNameParser::ReAllocLanguageStringBuffer()
{
	long nLen = m_nLanguageStringBufferLen + LanguageString_Buffer_DefLen;
	char *pLanguageStringBuffer = new char[nLen];
	memcpy(pLanguageStringBuffer, m_pLanguageStringBuffer, m_nLanguageStringBufferLen);
	m_pCurrLanguageStringPos = pLanguageStringBuffer + (m_pCurrLanguageStringPos - m_pLanguageStringBuffer);
	m_nLanguageStringBufferLen = nLen;
	delete m_pLanguageStringBuffer;
	m_pLanguageStringBuffer = 	pLanguageStringBuffer; 		
}

void CLanguageNameParser::Parse()
{
	long nIndex = 0;
	memset(m_pLanguageStringBuffer, 0, m_nLanguageStringBufferLen);
	char *pTemp = GetBufferBeginPos();
	char *pEnd = GetBufferEndPos();
	char *pString = NULL;
	m_pCurrLanguageStringPos = m_pLanguageStringBuffer;
	long nStringLen = 0;
	char *pLanguageStringBegin = NULL;
	CString strLangString;

	pString = GetString();
	char pszStringTemp[1024];

	while (IsPoiterInBuffer(pString))
	{
		pLanguageStringBegin = m_oLanguageString[nIndex].pLanguageStringBegin;

		if (pString == pLanguageStringBegin)
		{
				strLangString = GetLanguageStringByID(CString(pLanguageStringBegin));
				CString_to_char(strLangString, pszStringTemp);
				nStringLen = strlen(pszStringTemp);
				
				if (nStringLen + m_pCurrLanguageStringPos > m_nLanguageStringBufferLen + m_pLanguageStringBuffer)
				{
					ReAllocLanguageStringBuffer();
				}
				
				strcat(m_pCurrLanguageStringPos, pszStringTemp);
				m_pCurrLanguageStringPos += nStringLen;
				nIndex++;

#ifdef _DEBUG_LANGUAGE_MNGR
				Debug_RegisterString(pLanguageStringBegin, _T(""));
#endif
		}
		else
		{
			nStringLen = strlen(pString);

			if (nStringLen + m_pCurrLanguageStringPos > m_nLanguageStringBufferLen + m_pLanguageStringBuffer)
			{
				ReAllocLanguageStringBuffer();
			}

			strcat(m_pCurrLanguageStringPos, pString);
			m_pCurrLanguageStringPos += nStringLen;
		}

		pString = NextString();
	}	
}

