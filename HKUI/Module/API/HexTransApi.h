// HexTransApi.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_HEXTRNAS_API_H__)
#define _HEXTRNAS_API_H__

#include "../OSInterface/OSInterface.h"

//二进制数据转换
inline BYTE HexToValue(BYTE ch)
{
	if ('0' <= ch && ch <= '9')
	{
		return (ch - '0');
	}
	else if ('a' <= ch && ch <= 'f')
	{
		return (ch - 'a')+10;
	}
	else
	{
		return (ch - 'A')+10;
	}
}

inline BYTE HexToValue(char ch)
{
	HexToValue((BYTE)ch);
}

inline BYTE HexToValue(WCHAR ch)
{
	return HexToValue((BYTE)ch);
}

inline BYTE HexToValue(BYTE chH, BYTE chL)
{
	BYTE b1 = HexToValue(chH) ;
	BYTE b2 =  HexToValue(chL);
	return b1 * 16 + b2;
}

inline BYTE HexToValue(char chH, char chL)
{
	return HexToValue((BYTE)chH, (BYTE)chL);
}

inline BYTE HexToValue(WCHAR chH, WCHAR chL)
{
	return HexToValue((BYTE)chH, (BYTE)chL);
}

long HexToValue(const char *pszSrcHex, BYTE *pDest, char chSplit=VK_SPACE);
long HexToValue(const char *pszSrcHex, long nLen, BYTE *pDest, char chSplit=VK_SPACE);
long HexToValue(const wchar_t *pszSrcHex, long nLen, BYTE *pDest, char chSplit=VK_SPACE);
BOOL HexToLong(const char *pszHex, long &nValue);
BOOL HexToDWORD(const CString &strHex, DWORD &dwValue);
BOOL HexToDWORD(const char *pszHex, DWORD &dwValue);

//#ifndef _PSX_IDE_QT_
BOOL HexTo_i64(const CString &strHex, __uint64 &u64Value);
BOOL HexTo_i64(const char *pszHex, __uint64 &u64Value);
//#endif

inline char ValueToHex(BYTE ch)
{
	if (0 <= ch && ch <= 9)
	{
		return ch + '0';
	}
	else if (10 <= ch && ch <= 15)
	{
		return ch + 'A' - 10;
	}
	else
	{
		return '0';
	}
}

inline void ValueToHex(BYTE ch, char &chH, char &chL)
{
	chL = ValueToHex((BYTE)(ch & 0x0F));
	chH = ValueToHex((BYTE)((ch >> 4) & 0x0F));
}

void ValueToHex(const BYTE *pszSrc, long nLen, char *pDestHex, BOOL bAddSpace=FALSE, BOOL bAdd0X=TRUE);
void ValueToHex(BYTE byteValue, char *pDestHex, BOOL bAddSpace=FALSE, BOOL bAdd0X=TRUE);
void ValueToHex(WORD wValue, char *pDestHex, BOOL bAddSpace=FALSE, BOOL bAdd0X=TRUE);
void ValueToHex(DWORD dwValue, char *pDestHex, BOOL bAddSpace=FALSE, BOOL bAdd0X=TRUE);

//#ifndef _PSX_IDE_QT_
void ValueToHex(__uint64 dwValue, char *pDestHex, BOOL bAddSpace=FALSE, BOOL bAdd0X=TRUE);
//#endif

#endif // !defined(_HEXTRNAS_API_H__)
