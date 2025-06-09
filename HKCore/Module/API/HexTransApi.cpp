// HexTransApi.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HexTransApi.h"
#include "StringApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long HexToValue(const char *pszSrcHex, long nLen, BYTE *pDest, char chSplit)
{
	BYTE *pCurr = pDest;
	const char *pEnd = pszSrcHex + nLen;
	const char *pSrc = pszSrcHex;
	long nCount = 0;

	if ( (*pSrc == '0') && ( (*(pSrc+1) == 'x') || (*(pSrc+1) == 'X') ) )
	{
		if (nLen <= 2)
		{
			return 0;
		}

		pSrc += 2;
	}

	long nOneHexLen = 2;

	if (chSplit != 0)
	{
		if (*(pSrc+2) == chSplit)
		{
			nOneHexLen++;
		}
	}

	while (pSrc < pEnd)
	{
		*pCurr = HexToValue(*pSrc, *(pSrc+1));
		pCurr++;
		pSrc+=nOneHexLen;
		nCount++;
	}

	*pCurr = 0;

	return nCount;
}

long HexToValue(const wchar_t *pszSrcHex, long nLen, BYTE *pDest, char chSplit)
{
	BYTE *pCurr = pDest;
	const wchar_t *pEnd = pszSrcHex + nLen;
	const wchar_t *pSrc = pszSrcHex;
	long nCount = 0;

	if ( (*pSrc == '0') && ( (*(pSrc+1) == 'x') || (*(pSrc+1) == 'X') ) )
	{
		if (nLen <= 2)
		{
			return 0;
		}

		pSrc += 2;
	}

	long nOneHexLen = 2;

	if (chSplit != 0)
	{
		if (*(pSrc+2) == chSplit)
		{
			nOneHexLen++;
		}
	}

	while (pSrc < pEnd)
	{
		*pCurr = HexToValue(*pSrc, *(pSrc+1));
		pCurr++;
		pSrc+=nOneHexLen;
		nCount++;
	}

	*pCurr = 0;

	return nCount;
}

long HexToValue(const char *pszSrcHex, BYTE *pDest, char chSplit)
{
	long nLen = strlen(pszSrcHex);
	return HexToValue(pszSrcHex, nLen, pDest, chSplit);
// 	BYTE *pCurr = pDest;
// 	const char *pEnd = pszSrcHex + nLen;
// 	const char *pSrc = pszSrcHex;
// 	long nCount = 0;
// 
// 	if ( (*pSrc == '0') && ( (*(pSrc+1) == 'x') || (*(pSrc+1) == 'X') ) )
// 	{
// 		if (nLen <= 2)
// 		{
// 			return 0;
// 		}
// 
// 		pSrc += 2;
// 	}
// 
// 	long nOneHexLen = 2;
// 
// 	if (chSplit != 0)
// 	{
// 		if (*(pSrc+2) == chSplit)
// 		{
// 			nOneHexLen++;
// 		}
// 	}
// 
// 	while (pSrc < pEnd)
// 	{
// 		*pCurr = HexToValue((BYTE)*pSrc, *(pSrc+1));
// 		pCurr++;
// 		pSrc+=nOneHexLen;
// 		nCount++;
// 	}
// 
// 	*pCurr = 0;
// 
// 	return nCount;
}


BOOL HexToLong(const char *pszHex, long &nValue)
{
	const char *pTemp = pszHex;

	if (*pTemp == '0' && (*(pTemp+1) == 'x' || *(pTemp+1) == 'X') )
	{
		pTemp += 2;
	}

	long nLen = strlen(pTemp);
	long nIndex = 0;

	if (nLen >= 8)
	{
		nLen = 8;
	}

	nValue = 0;

	for (nIndex=0; nIndex<nLen; nIndex++)
	{
		nValue *= 16;
		nValue += HexToValue((BYTE)(*pTemp));
		pTemp++;
	}

	return TRUE;
}

BOOL HexToDWORD(const CString &strHex, DWORD &dwValue)
{
	char *pszBuffer = NULL;
	CString_to_char(strHex, &pszBuffer);
	BOOL b = HexToDWORD(pszBuffer, dwValue);
	delete pszBuffer;
	return b;
}

BOOL HexToDWORD(const char *pszHex, DWORD &dwValue)
{
	const char *pTemp = pszHex;

	if (*pTemp == '0' && (*(pTemp+1) == 'x' || *(pTemp+1) == 'X') )
	{
		pTemp += 2;
	}

	long nLen = strlen(pTemp);
	long nIndex = 0;

	if (nLen >= 8)
	{
		nLen = 8;
	}

	dwValue = 0;

	for (nIndex=0; nIndex<nLen; nIndex++)
	{
		dwValue *= 16;
		dwValue += HexToValue((BYTE)(*pTemp));
		pTemp++;
	}

	return TRUE;
}


BOOL HexTo_i64(const CString &strHex, __uint64 &u64Value)
{
	char *pszBuffer = NULL;
	CString_to_char(strHex, &pszBuffer);
	BOOL b = HexTo_i64(pszBuffer, u64Value);
	delete pszBuffer;
	return b;
}

BOOL HexTo_i64(const char *pszHex, __uint64 &u64Value)
{
	const char *pTemp = pszHex;

	if (*pTemp == '0' && (*(pTemp+1) == 'x' || *(pTemp+1) == 'X') )
	{
		pTemp += 2;
	}

	long nLen = strlen(pTemp);
	long nIndex = 0;

	if (nLen >= 16)
	{
		nLen = 16;
	}

	u64Value = 0;

	for (nIndex=0; nIndex<nLen; nIndex++)
	{
		u64Value *= 16;
		u64Value += HexToValue((BYTE)(*pTemp));
		pTemp++;
	}

	return TRUE;
}

void ValueToHexAdd_0X(char **pDestHex, BOOL bAdd0X)
{
	if (bAdd0X)
	{
		**pDestHex = '0';
		(*pDestHex)++;
		**pDestHex = 'x';
		(*pDestHex)++;
	}
}

void ValueToHexAdd_Value(const BYTE byteValue, char **pDestHex, BOOL bAddSpace)
{
	ValueToHex(byteValue, **pDestHex, *(*pDestHex+1));
	*pDestHex+=2;

	if (bAddSpace)
	{
		**pDestHex = VK_SPACE;
		(*pDestHex)++;
	}
}

void ValueToHexAdd_Value(const BYTE **pszSrc, char **pDestHex, BOOL bAddSpace)
{
	ValueToHex(**pszSrc, **pDestHex, *(*pDestHex+1));
	(*pszSrc)++;
	(*pDestHex)+=2;

	if (bAddSpace)
	{
		**pDestHex = VK_SPACE;
		(*pDestHex)++;
	}
}

void ValueToHex(const BYTE *pszSrc, long nLen, char *pDestHex, BOOL bAddSpace, BOOL bAdd0X)
{
	char *pCurr = pDestHex;
	const BYTE *pEnd = pszSrc + nLen;
	const BYTE *pSrc = pszSrc;

	ValueToHexAdd_0X(&pCurr, bAdd0X);

	while (pSrc < pEnd)
	{
		ValueToHexAdd_Value(&pSrc, &pCurr, bAddSpace);
// 		ValueToHex(*pSrc, *pCurr, *(pCurr+1));
// 		pSrc++;
// 		pCurr+=2;
// 
// 		if (bAddSpace)
// 		{
// 			*pCurr = VK_SPACE;
// 			pCurr++;
// 		}
	}

	*pCurr = 0;
}



void ValueToHex(BYTE byteValue, char *pDestHex, BOOL bAddSpace, BOOL bAdd0X)
{
	char *pCurr = pDestHex;

	ValueToHexAdd_0X(&pCurr, bAdd0X);
	ValueToHexAdd_Value(byteValue, &pCurr, bAddSpace);

	*pCurr = 0;
}

void ValueToHex(WORD wValue, char *pDestHex, BOOL bAddSpace, BOOL bAdd0X)
{
	char *pCurr = pDestHex;

	ValueToHexAdd_0X(&pCurr, bAdd0X);
	BYTE 	byteValue = (wValue >> 8 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = wValue & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);

	*pCurr = 0;
}


void ValueToHex(DWORD dwValue, char *pDestHex, BOOL bAddSpace, BOOL bAdd0X)
{
	char *pCurr = pDestHex;

	ValueToHexAdd_0X(&pCurr, bAdd0X);
	BYTE byteValue = (dwValue >> 24 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = (dwValue >> 16 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = (dwValue >> 8 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = dwValue & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);

	*pCurr = 0;
}

void ValueToHex(__uint64 u64Value, char *pDestHex, BOOL bAddSpace, BOOL bAdd0X)
{
	char *pCurr = pDestHex;

	ValueToHexAdd_0X(&pCurr, bAdd0X);
	BYTE byteValue = (u64Value >> 56 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = (u64Value >> 48 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = (u64Value >> 40 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = (u64Value >> 32 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);

	byteValue = (u64Value >> 24 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = (u64Value >> 16 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = (u64Value >> 8 ) & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);
	byteValue = u64Value & 0x00FF;
	ValueToHexAdd_Value(byteValue , &pCurr, bAddSpace);

	*pCurr = 0;
}

