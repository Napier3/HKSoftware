#include "stdafx.h"
#include "StringApi.h"

// #ifndef _PSX_IDE_QT_
// #include <locale.h>
// #endif

 #ifndef _PSX_IDE_QT_
 #include "VC/StringApi_VC.cpp"
// #else
// #include<QTextCodec>
// #include "QT/StringApi_QT.cpp"
 #endif

long String_Char_Count(BSTR strText)
{
	const wchar_t *bstr = strText;
	return String_Char_Count(bstr);
}

BOOL _P_CompareString(const CString &str1, const CString &str2)
{
	if (str1 == str2)
	{
		return TRUE;
	}

	if (str2.Find(str1) >= 0)
	{
		return TRUE;
	}

	if (str1.Find(str2) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}


size_t CString_to_char_ex(const CString &strSrc, char* pstrDest)
{
	char *pstrTemp = NULL;

	size_t sz = CString_to_char(strSrc, &pstrTemp);
	strcpy(pstrDest, pstrTemp);
	delete pstrTemp;

	return sz;
}

BOOL CString_To_SystemTime_GetVal(char* &pszString, WORD &nVal)
{
	char *pString = pszString;
	BOOL bTrue = FALSE;
	
	while (*pString != 0)
	{
		if ('0' <= *pString && *pString <= '9')
		{
			break;
		}

		pString++;
	}

	nVal = 0;

	while (*pString != 0)
	{
		if ('0' <= *pString && *pString <= '9')
		{
			nVal *= 10;
			nVal += *pString - '0';
			pString++;
			bTrue = TRUE;
		}
		else
		{
			break;
		}
	}

	pszString = pString;

	return bTrue;
}


BOOL CString_To_SystemTime_GetVal(wchar_t* &pszString, WORD &nVal)
{
	wchar_t *pString = pszString;
	BOOL bTrue = FALSE;

	while (*pString != 0)
	{
		if ('0' <= *pString && *pString <= '9')
		{
			break;
		}

		pString++;
	}

	nVal = 0;

	while (*pString != 0)
	{
		if ('0' <= *pString && *pString <= '9')
		{
			nVal *= 10;
			nVal += *pString - '0';
			pString++;
			bTrue = TRUE;
		}
		else
		{
			break;
		}
	}

	pszString = pString;

	return bTrue;
}


BOOL CString_To_SystemTime(wchar_t *strTime, SYSTEMTIME &time)
{
	memset(&time, 0, sizeof(time));

	if (!CString_To_SystemTime_GetVal(strTime, time.wYear))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wMonth))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wDay))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wHour))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wMinute))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wSecond))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wMilliseconds))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CString_To_SystemTime(char* strTime, SYSTEMTIME &time)
{
	memset(&time, 0, sizeof(time));

	if (!CString_To_SystemTime_GetVal(strTime, time.wYear))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wMonth))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wDay))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wHour))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wMinute))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wSecond))
	{
		return FALSE;
	}

	if (!CString_To_SystemTime_GetVal(strTime, time.wMilliseconds))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CString_To_SystemTime(const CString &strTime, SYSTEMTIME &time)
{
#ifdef _UNICODE
	wchar_t *pszTime = (wchar_t *)strTime.GetString();
	return CString_To_SystemTime(pszTime, time);
#else
	char *pszTime = (char *)strTime.GetString();
	return CString_To_SystemTime(pszTime, time);
#endif
}

BOOL MacString_to_String(const CString &strMacString, CString &strReturn)
{
	if (strMacString.GetLength() != 17)
	{
		return FALSE;
	}

	long nPos = 0;
	CString strTemp1, strTemp2;
	nPos = strMacString.Find('-');

	if (nPos <= 0)
	{
		return FALSE;
	}
	strTemp1 = strMacString.Left(nPos);
	strReturn.AppendFormat(strTemp1);
	strTemp2 = strMacString.Mid(nPos+1);

	nPos = strTemp2.Find('-');

	if (nPos <= 0)
	{
		return FALSE;
	}
	strTemp1 = strTemp2.Left(nPos);
	strReturn.AppendFormat(strTemp1);
	strTemp2 = strTemp2.Mid(nPos+1);

	nPos = strTemp2.Find('-');

	if (nPos <= 0)
	{
		return FALSE;
	}
	strTemp1 = strTemp2.Left(nPos);
	strReturn.AppendFormat(strTemp1);
	strTemp2 = strTemp2.Mid(nPos+1);

	nPos = strTemp2.Find('-');

	if (nPos <= 0)
	{
		return FALSE;
	}
	strTemp1 = strTemp2.Left(nPos);
	strReturn.AppendFormat(strTemp1);
	strTemp2 = strTemp2.Mid(nPos+1);

	nPos = strTemp2.Find('-');

	if (nPos <= 0)
	{
		return FALSE;
	}
	strTemp1 = strTemp2.Left(nPos);
	strReturn.AppendFormat(strTemp1);
	strTemp1 = strTemp2.Mid(nPos+1);
	strReturn.AppendFormat(strTemp1);

	return TRUE;
}

void Double_To_FeeString(double fValue,CString &strCost,long nPrecision)
{
	if (nPrecision < 0)
	{
		nPrecision = 2;
	}

	long nOffset = 0;
	CString strFormat;
	if (nPrecision == 0)
	{
		strCost.Format(_T("%d"),(int)fValue);
		nOffset = 3;//0:**,***
	}
	else
	{
		strFormat.Format(_T("%%.%df"),nPrecision);
		strCost.Format(strFormat,fValue);
		nOffset = 4 + nPrecision;//2:**,***.**
	}
	
	long nLen = strCost.GetLength();
	long nPos = nLen - nOffset;  //**,***.**

	while (nPos > 0)
	{
		strCost.Insert(nPos, ',');
		nPos -= 3;
	}
}

void Float_To_FeeString(float fValue,CString &strCost,long nPrecision)
{
	Double_To_FeeString((double)fValue,strCost,nPrecision);
}

void Number_String_To_1000(CString &strNumber)
{
	long nPos = 0;
	nPos = strNumber.Find('.');
	long nLen = strNumber.GetLength();

	if (nPos < 0)
	{
		nPos = nLen - 3;
	}
	else
	{
		nPos = nPos - 3;
	}

	while (nPos > 0)
	{
		strNumber.Insert(nPos, ',');
		nPos -= 3;
	}
}

//char* 与 wchar*之间的转换  2019-12-1   lijunqing
int str_char_to_wchar(wchar_t **ppwszDest, const char *pszSrc, long nLen)
{
	if (nLen == -1)
	{
		nLen = strlen(pszSrc);
	}

	long nLenNew = nLen  + 5;
	*ppwszDest = new wchar_t[nLenNew];
	memset(*ppwszDest, 0, nLenNew*sizeof(wchar_t));

	return str_char_to_wchar(*ppwszDest, pszSrc, nLen);
}

int str_char_to_wchar(wchar_t *pwszDest, const char *pszSrc, long nLen)
{
	if (nLen == -1)
	{
		nLen = strlen(pszSrc);
	}

    long nLen2 =  -1;
#ifdef _PSX_IDE_QT_
    memset(pwszDest, 0, (nLen)*sizeof(wchar_t));
//    QTextCodec *codec =QTextCodec::codecForName("GBK"); //1
    QString strTmp = /*codec->toUnicode*/(pszSrc);//2
    strTmp.toWCharArray(pwszDest);
    nLen2 = wcslen(pwszDest);
#else
    nLen2 = mbstowcs(pwszDest, pszSrc, nLen);
#endif
	return nLen2;
}

int str_wchar_to_char(char **ppszDest, const wchar_t *pwszSrc, long nLen)
{
	if (nLen == -1)
	{
		nLen = wcslen(pwszSrc);
	}

	*ppszDest = new char[nLen*2+2];
	memset(*ppszDest, 0, 2*nLen+2);

	return str_wchar_to_char(*ppszDest, pwszSrc, nLen);
}

int str_wchar_to_char(char *pszDest, const wchar_t *pwszSrc, long nLen)
{
	setlocale(LC_ALL,("chs"));//20200202 zhouhj 调用wcstombs之前先调此句;否则wcstombs不会处理超过255的字符

	if (nLen == -1)
	{
		nLen = wcslen(pwszSrc);
	}

	nLen = wcstombs(pszDest, pwszSrc, nLen);
	return nLen;
}

int str_formart_cal(const wchar_t *strFormat)
{
	const wchar_t *p = strFormat;
	int nCount = 0;

	while (*p != 0)
	{
		if (*p == '%')
		{
			if (*(p+1) != 0)
			{
				if (*(p+1) == 's' || *(p+1) == 'S')
				{
					nCount++;
				}
			}
		}

		p++;
	}

	return nCount;
}


int str_formart_cal(const char *strFormat)
{
	const char *p = strFormat;
	int nCount = 0;

	while (*p != 0)
	{
		if (*p == '%')
		{
			if (*(p+1) != 0)
			{
				if (*(p+1) == 's' || *(p+1) == 'S')
				{
					nCount++;
				}
			}
		}

		p++;
	}

	return nCount;
}

void str_formart_v(const wchar_t *strFormat, va_list &args, CString &strText)
{
    long nLen = 0;
    wchar_t pwszText[1024];

    nLen = vswprintf(pwszText, 1024, strFormat, args );
	pwszText[nLen] = 0;

#ifndef _PSX_IDE_QT_
	strText = pwszText;
#else
    strText = QString::fromWCharArray(pwszText);
#endif
}

void str_formart_v(const char *strFormat, va_list &args, CString &strText)
{
    long nLen = 0;
    char pszText[1024];
    nLen = vsprintf( pszText, strFormat, args );
	pszText[nLen] = 0;
	strText = pszText;
}

#ifndef _PSX_QT_LINUX_                                         //周宏军  20200516解决编码方式问题
void charUtf8_to_wcharGBK(char *pszUtf8,long nSrcLen,wchar_t **ppwszGbk,long &nDestLen) 
{
	long nLen = MultiByteToWideChar(CP_UTF8, 0, pszUtf8, nSrcLen, NULL, 0);

	*ppwszGbk = new wchar_t[nSrcLen+1];
	memset(*ppwszGbk, 0, (nSrcLen+1)*sizeof(wchar_t));

	charUtf8_to_wcharGBK(pszUtf8, nSrcLen, *ppwszGbk, nDestLen);
// #ifdef UNICODE
// 	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pszUtf8, -1, *ppwszGbk, nSrcLen);
// #else
// 	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)pszUtf8, -1, *ppwszGbk, nSrcLen);
// #endif
// 
// 	nDestLen = WideCharToMultiByte(CP_ACP, 0, *ppwszGbk, -1, NULL, 0, NULL, NULL);
}

void charUtf8_to_wcharGBK(char *pszUtf8,long nSrcLen,wchar_t *pwszGbk,long &nDestLen)
{
#ifdef UNICODE
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pszUtf8, nSrcLen, pwszGbk, nSrcLen);
#else
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)pszUtf8, nSrcLen, pwszGbk, nSrcLen);
#endif

	nDestLen = WideCharToMultiByte(CP_ACP, 0, pwszGbk, nSrcLen, NULL, 0, NULL, NULL);
}

void charUtf8_to_charGBK(char *pszUtf8,long nSrcLen,char **ppszGbk,long &nDestLen) 
{
	int nLen= 0;
	wchar_t *pwszGbk = new wchar_t[nSrcLen+1];
	memset(pwszGbk, 0, (nSrcLen+1)*sizeof(wchar_t));

#ifdef UNICODE
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pszUtf8, -1, pwszGbk, nSrcLen);
#else
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)pszUtf8, -1, pwszGbk, nSrcLen);
#endif

	nDestLen = WideCharToMultiByte(CP_ACP, 0, pwszGbk, -1, NULL, 0, NULL, NULL);

	*ppszGbk=new char[nDestLen+1];
	memset(*ppszGbk, 0, nDestLen+1);
	WideCharToMultiByte (CP_ACP, 0, pwszGbk, -1, *ppszGbk, nDestLen, NULL,NULL);

	delete[] pwszGbk;
}

void charUtf8_to_charGBK(char *pszUtf8,long nSrcLen,char *pszGbk,long &nDestLen) 
{
	int nLen= 0;
	wchar_t *pwszGbk = new wchar_t[nSrcLen+1];
	memset(pwszGbk, 0, (nSrcLen+1)*sizeof(wchar_t));

#ifdef UNICODE
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pszUtf8, -1, pwszGbk, nSrcLen);
#else
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)pszUtf8, -1, pwszGbk, nSrcLen);
#endif

	nDestLen = WideCharToMultiByte(CP_ACP, 0, pwszGbk, -1, NULL, 0, NULL, NULL);

	memset(pszGbk, 0, nDestLen+1);
	WideCharToMultiByte (CP_ACP, 0, pwszGbk, -1, pszGbk, nDestLen, NULL,NULL);

	delete[] pwszGbk;
}

void charGBK_to_charUtf8(char *pszGbk,long nSrcLen,char **ppszUtf8,long &nDestLen) 
{
	long nLen = MultiByteToWideChar(CP_ACP, 0, pszGbk, nSrcLen, NULL, 0);
	wchar_t *pwszUtf8 = new wchar_t[nLen+1];
	memset(pwszUtf8, 0, (nLen+1)*sizeof(wchar_t));

#ifdef UNICODE
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszGbk, -1, pwszUtf8, nLen);
#else
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)pszGbk, -1, pwszUtf8, nLen);
#endif

	nDestLen = WideCharToMultiByte(CP_UTF8, 0, pwszUtf8, nLen, NULL, 0, NULL, NULL);

	*ppszUtf8 = new char[nDestLen+1];
	memset(*ppszUtf8, 0, nDestLen+1);
	WideCharToMultiByte (CP_UTF8, 0, pwszUtf8, -1, *ppszUtf8, nDestLen, NULL,NULL);

	delete[] pwszUtf8;
}

void charGBK_to_charUtf8(char *pszGbk,long nSrcLen,char *pszUtf8,long &nDestLen) 
{
	long nLen = MultiByteToWideChar(CP_ACP, 0, pszGbk, nSrcLen, NULL, 0);
	wchar_t *pwszUtf8 = new wchar_t[nLen+1];
	memset(pwszUtf8, 0, (nLen+1)*sizeof(wchar_t));

#ifdef UNICODE
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszGbk, -1, pwszUtf8, nLen);
#else
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)pszGbk, -1, pwszUtf8, nLen);
#endif

	nDestLen = WideCharToMultiByte(CP_UTF8, 0, pwszUtf8, nLen, NULL, 0, NULL, NULL);

	memset(pszUtf8, 0, nDestLen+1);
	WideCharToMultiByte (CP_UTF8, 0, pwszUtf8, -1, pszUtf8, nDestLen, NULL,NULL);

	delete[] pwszUtf8;
}

void wchar_to_charUtf8(wchar_t *pwszGbk,long nSrcLen,char **ppszUtf8,long &nDestLen) 
{
	nDestLen = WideCharToMultiByte(CP_UTF8, 0, pwszGbk, nSrcLen, NULL, 0, NULL, NULL);

	*ppszUtf8 = new char[nDestLen+1];
	memset(*ppszUtf8, 0, nDestLen+1);
	WideCharToMultiByte (CP_UTF8, 0, pwszGbk, -1, *ppszUtf8, nDestLen, NULL,NULL);
}

void wchar_to_charUtf8(wchar_t *pwszGbk,long nSrcLen,char *pszUtf8,long &nDestLen) 
{
	nDestLen = WideCharToMultiByte(CP_UTF8, 0, pwszGbk, nSrcLen, NULL, 0, NULL, NULL);

	memset(pszUtf8, 0, nDestLen+1);
	WideCharToMultiByte (CP_UTF8, 0, pwszGbk, -1, pszUtf8, nDestLen, NULL,NULL);
}

#endif
