//#include "stdafx.h"
#include "../StringApi.h"

#include <locale.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long String_Char_Count(const CString &strText)
{
#ifdef _UNICODE

	const wchar_t *bstr = strText;
	return String_Char_Count(bstr);

#else

	return strText.GetLength();

#endif
}

size_t CString_to_char(const CString &strSrc, char* pstrDest)
{
	const size_t strsize=String_Char_Count(strSrc)+2;//(strSrc.GetLength()+1)*2; // 宽字符的长度;
	size_t sz=0;

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("chs"));
	wcstombs_s(&sz,pstrDest,strsize,strSrc,_TRUNCATE);
	_wsetlocale(LC_ALL,_T("eng"));
#else
	strcpy(pstrDest, strSrc);
#endif

	sz = strlen(pstrDest);
	return sz;
};

size_t CString_to_char(const CString &strSrc, char* pstrDest, long nLen)
{
	size_t sz=0;

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("chs"));
	wcstombs_s(&sz,pstrDest,nLen,strSrc,_TRUNCATE);
	_wsetlocale(LC_ALL,_T("eng"));
#else
	strcpy(pstrDest, strSrc);
#endif

	sz = strlen(pstrDest);
	return sz;
};

size_t CString_to_char(const CString &strSrc, char** ppstrDest)
{
	const size_t strsize= String_Char_Count(strSrc) + 1;
	size_t sz=0;
	*ppstrDest = new char[strsize+2];

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("chs"));
	wcstombs_s(&sz,*ppstrDest,strsize,strSrc,_TRUNCATE);
	_wsetlocale(LC_ALL,_T("eng"));
#else
	strcpy(*ppstrDest, strSrc);
#endif

	sz = strlen(*ppstrDest);
	return sz;
};

size_t CString_to_wchar(const CString &strSrc, wchar_t* pstrDest)
{
#ifdef _UNICODE
	wcscpy(pstrDest, strSrc);
	return strSrc.GetLength();
#else
	return str_char_to_wchar(pstrDest, strSrc.GetString(), strSrc.GetLength());
#endif
}

size_t CString_to_wchar(const CString &strSrc, wchar_t** ppstrDest)
{
    long nLen = strSrc.GetLength();
    *ppstrDest = new wchar_t[nLen];
    return CString_to_wchar(strSrc, *ppstrDest);
}

size_t BSTR_to_char(BSTR strSrc, char* pstrDest)
{
	const size_t strsize = String_Char_Count(strSrc)+1;
	size_t sz=0;

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("chs"));
#endif

	wcstombs_s(&sz,pstrDest,strsize,strSrc,_TRUNCATE);

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("eng"));
#endif

	sz = strlen(pstrDest);
	return sz;
};

size_t BSTR_to_char(BSTR strSrc, char** ppstrDest)
{
	const size_t strsize = String_Char_Count(strSrc) + 2;
	size_t sz=0;
	*ppstrDest = new char[strsize+2];

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("chs"));
#endif

	wcstombs_s(&sz, *ppstrDest, strsize, strSrc, _TRUNCATE);

#ifdef UNICODE
	_wsetlocale(LC_ALL,_T("eng"));
#endif

	sz = strlen(*ppstrDest);
	return sz;
};

long CString_To_long(const CString &strValue)
{
#ifdef _UNICODE
	return _wtol(strValue);
#else
	return atol(strValue);
#endif
}

unsigned long CString_To_ulong(const CString &strValue)
{
#ifdef _UNICODE
	return wcstoul(strValue, NULL, 10);
#else
	return strtoul(strValue, NULL, 10);
#endif
}

__int64 CString_To_i64(const CString &strValue)
{
#ifdef _UNICODE
	return _wtoi64(strValue);
#else
	return _atoi64(strValue);
#endif
}

double CString_To_double(const CString &strValue)
{
#ifdef _UNICODE
	return _wtof(strValue);
#else
	return atof(strValue);
#endif
}

UINT CString_HEX_to_UINT(const CString &strText)
{
	UINT nValue = 0;
	char ch0 = strText.GetAt(0);
	char ch1 = strText.GetAt(1);

	if (ch0 == '0' && ( (ch1=='x') || (ch1 == 'X')) )
		_stscanf_s((LPCTSTR)strText,_T("%x"),&nValue);
	else
		_stscanf_s((LPCTSTR)strText,_T("%d"),&nValue);

	return nValue;
}

BOOL CString_to_CTime(const CString &strTime, CTime &tm, BOOL bErrUseCurrTime)
{
	COleDateTime tmOle;
	
	if ( tmOle.ParseDateTime(strTime) )
	{
		SYSTEMTIME tmSys;
		tmOle.GetAsSystemTime(tmSys);
		tm = tmSys;
		return TRUE; 
	}
	else
	{
		if (bErrUseCurrTime)
		{
			SYSTEMTIME tmSys;
			::GetLocalTime(&tmSys);
			tm = tmSys;
			return TRUE; 
		}
		else
		{
			return FALSE;
		}
	}
}

 CString VariantToString(_variant_t var)
 {
 	CString strValue;
 	_variant_t var_t;
 	_bstr_t bstr_t;
 
 	COleCurrency var_currency;
 
 	switch(var.vt)
 
 	{
 	case VT_EMPTY:
 
 	case VT_NULL:
		strValue=_T("");
		break;
 
 	case VT_UI1:
		strValue.Format(_T("%d"),var.bVal);
		break;//bool
 
 	case VT_I2:
		strValue.Format(_T("%d"),var.iVal);
		break;//int
 
 	case VT_I4:
		strValue.Format(_T("%d"),var.lVal);
		break;//long
 
 	case VT_R4:
		strValue.Format(_T("%f"),var.fltVal);
		break;//float
 
 	case VT_R8:
		strValue.Format(_T("%f"),var.dblVal);
		break;//
 
 	case VT_CY:
 		var_currency=var;
 		strValue=var_currency.Format(0);
 		break;
 
 	case VT_DISPATCH:
 		{
 			IDispatch *varCon =  var.pdispVal;
 			VARIANT varResult = {0};
 			DISPPARAMS params = {NULL, NULL, 0, 0};
 			varCon->Invoke(0, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &params, &varResult, NULL, NULL);
 			strValue = varResult.bstrVal;
 		}
 		break;
 
 	case VT_BSTR:
 		var_t =var;
 		bstr_t=var_t;
 		strValue.Format(_T("%s"),(const char *)bstr_t);
 		break;
 
 	case VT_DATE:  //时间类型
 		{
			COleDateTime tm = var;
 			strValue = tm.Format(_T("%Y-%m-%d %H:%M:%S"));
 		}
 		break;
 
 	case VT_BOOL:
		strValue.Format(_T("%d"),var.boolVal);
 		break;
 
 	default:
		strValue=_T("");
		break;
 
 	}
 
 	return strValue;
 }
