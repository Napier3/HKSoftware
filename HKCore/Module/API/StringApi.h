#ifndef _string_api_h__
#define _string_api_h__

#include "../OSInterface/OSInterface.h"

inline long String_Char_Count(const wchar_t *bstrText)
{
    const wchar_t *p = bstrText;
    long nCount = 0;

    while (*p != 0)
    {
        if ( *p > 256)
        {
            nCount += 2;
        }
        else
        {
            nCount++;
        }

        p++;
    }

    return nCount;
}

//long String_Char_Count(BSTR strText);

long String_Char_Count(const CString &strText);

size_t CString_to_char(const CString &strSrc, char* pstrDest);
size_t CString_to_char(const CString &strSrc, char* pstrDest, long nLen);
size_t CString_to_char(const CString &strSrc, char** ppstrDest);
size_t CString_to_wchar(const CString &strSrc, wchar_t* pstrDest);
size_t CString_to_wchar(const CString &strSrc, wchar_t** ppstrDest);

size_t BSTR_to_char(BSTR strSrc, char* pstrDest);
size_t BSTR_to_char(BSTR strSrc, char** ppstrDest);

long CString_To_long(const CString &strValue);
unsigned long CString_To_ulong(const CString &strValue);
__int64 CString_To_i64(const CString &strValue);
double CString_To_double(const CString &strValue);

BOOL _P_CompareString(const CString &str1, const CString &str2);

size_t CString_to_char_ex(const CString &strSrc, char* pstrDest);
UINT CString_HEX_to_UINT(const CString &strText);

BOOL CString_To_SystemTime(wchar_t *strTime, SYSTEMTIME &time);
BOOL CString_To_SystemTime(char* strTime, SYSTEMTIME &time);
BOOL CString_To_SystemTime(const CString &strTime, SYSTEMTIME &time);
BOOL MacString_to_String(const CString &strMacString, CString &strReturn);   //带中划线的mac地址，去掉中划线后返回 

inline void SystemTime_To_String(SYSTEMTIME &time,CString &strTime)
{
    strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
}
inline void SystemTime_To_StringEx(SYSTEMTIME &time,CString &strTime)
{
	strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d %03d"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond,time.wMilliseconds);
}
inline void SystemTime_To_ShortString(SYSTEMTIME &time,CString &strTime)
{
    strTime.Format(_T("%04d-%02d-%02d"), time.wYear, time.wMonth, time.wDay);
}

inline DWORD CString_Binary_to_DWORD(const char *pValue)//zhouhj 20201209 增加用于解析二进制字符串
{
	const char *pTemp = pValue;
	long nLen = strlen(pTemp);
	long nIndex = 0;
	DWORD dwValue = 0;

	if (nLen >= 32)
	{
		nLen = 32;
	}

	dwValue = 0;

	for (nIndex=0; nIndex<nLen; nIndex++)
	{
		dwValue *= 2;

		if (*pTemp == '1')
		{
			dwValue += 1;
		}

		pTemp++;
	}
	return dwValue;
}

inline DWORD CString_Binary_to_DWORD(const CString &strText)//zhouhj 20201209 增加用于解析二进制字符串
{
	DWORD dwValue = 0;
	char *pszBuffer = NULL;
	CString_to_char(strText, &pszBuffer);
	dwValue = CString_Binary_to_DWORD(pszBuffer);
	delete pszBuffer;
	return dwValue;
}

void Float_To_FeeString(float fValue,CString &strCost,long nPrecision=3);
void Double_To_FeeString(double fValue,CString &strCost,long nPrecision=3);
void Number_String_To_1000(CString &strNumber);

BOOL CString_to_CTime(const CString &strTime, CTime &tm, BOOL bErrUseCurrTime=TRUE);
#ifndef _PSX_IDE_QT_
CString VariantToString(_variant_t var);
#endif


//char* <<==>> wchar*  2019-12-1   lijunqing
int str_char_to_wchar(wchar_t **ppwszDest, const char *pszSrc, long nLen=-1);
int str_char_to_wchar(wchar_t *pwszDest, const char *pszSrc, long nLen=-1);
int str_wchar_to_char(char **ppszDest, const wchar_t *pwszSrc, long nLen=-1);
int str_wchar_to_char(char *pszDest, const wchar_t *pwszSrc, long nLen=-1);

void str_formart_v(const wchar_t *strFormat, va_list &args, CString &strText);
void str_formart_v(const char *strFormat, va_list &args, CString &strText);

inline int str_compare(CString &str1, CString &str2)
{
#ifdef _UNICODE
    return wcscmp( str1.GetString(), str2.GetString());
#else
    return strcmp( str1.GetString(), str2.GetString());
#endif
}

inline int str_n_compare(const CString &str1, const CString &str2, int nLen)
{
#ifdef _UNICODE
    return _wcsnicmp( str1.GetString(), str2.GetString(), nLen);
#else
    return strncmp( str1.GetString(), str2.GetString(), nLen);
#endif
}

#ifndef _PSX_QT_LINUX_//X周宏军  20200516解决编码方式问题
//【win】gbk utf-8转换接口
void charUtf8_to_wcharGBK(char *pszUtf8,long nSrcLen,wchar_t **ppwszGbk,long &nDestLen);
void charUtf8_to_wcharGBK(char *pszUtf8,long nSrcLen,wchar_t *pwszGbk,long &nDestLen);
void charUtf8_to_charGBK(char *pszUtf8,long nSrcLen,char **ppszGbk,long &nDestLen);
void charUtf8_to_charGBK(char *pszUtf8,long nSrcLen,char *pszGbk,   long &nDestLen);  //2021-12-30  lijunqing
void charGBK_to_charUtf8(char *pszGbk,long nSrcLen,char **ppszUtf8,long &nDestLen);
void wchar_to_charUtf8(wchar_t *pwszGbk,long nSrcLen,char **ppszUtf8,long &nDestLen);
void charGBK_to_charUtf8(char *pszGbk,long nSrcLen,char *pszUtf8,long &nDestLen);
void wchar_to_charUtf8(wchar_t *pwszGbk,long nSrcLen,char *pszUtf8,long &nDestLen);
#endif

//shaolei 20210818 
#define XSTR_EncodingID_utf8mb4   _T("utf8mb4")  
#define XSTR_EncodingID_utf8      _T("utf8") 
#define XSTR_EncodingID_gb2312    _T("gb2312")
#define XSTR_EncodingIdx_Auto  0
#define XSTR_EncodingIdx_utf8  1
#define XSTR_EncodingIdx_gb2312  2

inline UINT XSTR_Encoding_GetIdx(const CString& strEnconding)
{
	if (strEnconding == XSTR_EncodingID_utf8mb4)
	{
		return XSTR_EncodingIdx_utf8;
	}

	if (strEnconding == XSTR_EncodingID_utf8)
	{
		return XSTR_EncodingIdx_utf8;
	}

	if (strEnconding == XSTR_EncodingID_gb2312)
	{
		return XSTR_EncodingIdx_gb2312;
	}

	return XSTR_EncodingIdx_gb2312;
}

#endif


