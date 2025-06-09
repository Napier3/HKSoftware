// BinaryTextConvert.cpp: implementation of the CBinaryTextConvert class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BinaryTextConvert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//const long MAX_OF_CONVERT_STRING = 20;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char CBinaryTextConvert::g_tabHexCharacters[16] = {	'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' }; 

CBinaryTextConvert::CBinaryTextConvert()
{
	
}


CBinaryTextConvert::~CBinaryTextConvert()
{
// 	CBufferBase m_oBufferBinary;
// 	CBufferBase m_oBufferText;
}


void CBinaryTextConvert::SetText(const char *strText)
{
	m_oBufferText.InitBuffer(strText);
}

void CBinaryTextConvert::SetText(const CString &strText)
{
	m_oBufferText.InitBuffer(strText);
}


void CBinaryTextConvert::SetBinary(BYTE *pBuffer, long nLength)
{
	m_oBufferBinary.InitBuffer((char*)pBuffer, (char*)(pBuffer + nLength) );
}


BOOL CBinaryTextConvert::GetString(CString &strText)
{
	strText = m_oBufferText.GetBufferBeginPos();
	return TRUE;
}

BOOL CBinaryTextConvert::GetString(char *pString, long &nLength)
{
	char *pBuffer = m_oBufferText.GetBufferBeginPos();
	nLength = strlen(pBuffer);
	strcpy(pString, pBuffer);

	return TRUE;
}

BOOL CBinaryTextConvert::GetString(char **ppString, long &nLength)
{
	char *pBuffer = m_oBufferText.GetBufferBeginPos();
	nLength = strlen(pBuffer);
	*ppString = new char[nLength + 5];
	strcpy(*ppString, pBuffer);

	return TRUE;
}

BOOL CBinaryTextConvert::GetBinary(BYTE *pBuffer, long &nLength)
{
	char *pBegin = m_oBufferBinary.GetBufferBeginPos();
	char *pEnd = m_oBufferBinary.GetBufferEndPos();
	nLength = pEnd - pBegin;
	memcpy(pBuffer, pBegin,  nLength);

	return TRUE;
}

BOOL CBinaryTextConvert::GetBinary(BYTE **ppBuffer, long &nLength)
{
	char *pBegin = m_oBufferBinary.GetBufferBeginPos();
	char *pEnd = m_oBufferBinary.GetBufferEndPos();
	nLength = pEnd - pBegin;
	*ppBuffer = new BYTE[nLength + 5];
	memcpy(*ppBuffer, pBegin,  nLength);

	return TRUE;
}

BOOL CBinaryTextConvert::GetBinaryRef(BYTE **ppBuffer, long &nLength)
{
	char *pBegin = m_oBufferBinary.GetBufferBeginPos();
	char *pEnd = m_oBufferBinary.GetPointer();
	
	*ppBuffer = (BYTE*)pBegin;
	nLength = pEnd - pBegin;

	return TRUE;
}

BOOL CBinaryTextConvert::ConvertBinaryToText()
{
	long nLength = m_oBufferBinary.GetLength();
	long nTextLen = nLength * 3;
	m_oBufferText.InitBuffer(nTextLen);

	BYTE *pBinary = (BYTE*)m_oBufferBinary.GetBufferBeginPos();
	BYTE *pBinaryEnd = (BYTE*)m_oBufferBinary.GetBufferEndPos();
	BYTE *pText = (BYTE*)m_oBufferText.GetBufferBeginPos();
	BYTE *pCurr = pBinary;

	while (pCurr < pBinaryEnd)
	{
		ValueToString_Hex(*pCurr, pText);
		pText += 3;
		pCurr++;
	}

	return TRUE;
}

BOOL CBinaryTextConvert::ConvertTextToBinary(BOOL bHasSpaceGap)
{
	long nLength = m_oBufferText.GetLength();
	long nTextLen = 0;
	BYTE *pText = (BYTE *)m_oBufferText.GetBufferBeginPos();

	if (*pText == '0' && (*(pText+1) == 'x' || *(pText+1) == 'X') )
	{
		nLength -= 2;
		pText += 2;
	}
	
	if (bHasSpaceGap)
	{
		nTextLen = nLength / 3;
	}
	else
	{
		nTextLen = nLength / 2;
	}

	m_oBufferBinary.InitBuffer(nTextLen);

	BYTE *pTextEnd = (BYTE *)m_oBufferText.GetBufferEndPos();
	BYTE *pBinary = (BYTE *)m_oBufferBinary.GetBufferBeginPos();
	BYTE *pCurr = pText;
	BOOL bTrue = TRUE;
	BYTE *pBinaryHead = pBinary;

	while (pCurr < pTextEnd)
	{
		bTrue = StringToValue_Hex(pCurr, *pBinary, bHasSpaceGap);

		if (!bTrue)
		{
			break;
		}

		pCurr = GetNextChar(pCurr, pTextEnd, bHasSpaceGap);
		pBinary += 1;
	}

	m_oBufferBinary.OffsetPointer(pBinary - pBinaryHead);
	return bTrue;
}

BYTE* CBinaryTextConvert::GetNextChar(BYTE *pCurr, BYTE *pEnd, BOOL bHasSpaceGap)
{
	if (bHasSpaceGap)
	{
		pCurr += 3;
	}
	else
	{
		pCurr += 2;
	}

	while (pCurr < pEnd)
	{
		if (*pCurr == '\r' || *pCurr == '\n' || *pCurr == VK_SPACE)
		{
			pCurr++;
		}
		else
		{
			break;
		}
	}

	return pCurr;
}

