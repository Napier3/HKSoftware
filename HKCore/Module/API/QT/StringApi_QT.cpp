#include "../StringApi.h"

#include <locale.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long String_Char_Count(const CString &strText)
{
	return strText.toLocal8Bit().length();//zhouhj 20220402 Qt下获取字符长度,包含中文字符
// #ifdef _UNICODE
// 
// 	const wchar_t *bstr = strText;
// 	return String_Char_Count(bstr);

// #else
// 
// 	return strText.GetLength();
// 
// #endif
}

size_t CString_to_char(const CString &strSrc, char* pstrDest)
{
    size_t sz=0;

    char*  tmp;

    //2020-12-24  lijunqing
    //QByteArray ba = strSrc.toLocal8Bit();
    //QByteArray ba = strSrc.toAscii();
    const char *pszRet = strSrc.GetString();

    //tmp=ba.data();
    strcpy(pstrDest, pszRet);
    sz = strlen(pstrDest);

    return sz;
}

size_t CString_to_char(const CString &strSrc, char* pstrDest, long nLen)
{
    QByteArray oArrByte = strSrc.toLocal8Bit();
    const char *tmp = oArrByte.data();
    //const char *tmp = strSrc.toUtf8().constData();
    strcpy(pstrDest, tmp);

    nLen = strlen(pstrDest);
    return nLen;
}

size_t CString_to_char(const CString &strSrc, char** ppstrDest)
{
	const size_t strsize= String_Char_Count(strSrc) + 1;

	size_t sz=0;
	*ppstrDest = new char[strsize+2];

	QByteArray oArrByte = strSrc.toLocal8Bit();//zhouhj 20220301 参考size_t CString_to_char(const CString &strSrc, char* pstrDest, long nLen)函数修改
	const char *tmp = oArrByte.data();
//    const char *tmp = strSrc.toUtf8().constData();
    strcpy(*ppstrDest, tmp);

	sz = strlen(*ppstrDest);
	return sz;
}


size_t CString_to_wchar(const CString &strSrc, wchar_t* pstrDest)
{
	//周宏军  20200227
	strSrc.toWCharArray(pstrDest);
	return strSrc.GetLength();
//	const wchar_t *pwszSrc =reinterpret_cast<const wchar_t *>(strSrc.utf16());
//	wcscpy(pstrDest, pwszSrc);
//	return strSrc.GetLength();
}

size_t CString_to_wchar(const CString &strSrc, wchar_t** ppstrDest)
{
    long nLen = strSrc.GetLength();
    *ppstrDest = new wchar_t[nLen+2];
    memset(*ppstrDest,0,sizeof(wchar_t)*(nLen+2));	//周宏军  20200227
    return CString_to_wchar(strSrc, *ppstrDest);
}

size_t BSTR_to_char(BSTR strSrc, char* pstrDest)
{
    return str_wchar_to_char(pstrDest, strSrc);
}

size_t BSTR_to_char(BSTR strSrc, char** ppstrDest)
{
	const size_t strsize = String_Char_Count(strSrc) + 2;
	size_t sz=0;
	*ppstrDest = new char[strsize+2];

   sz = BSTR_to_char(strSrc, *ppstrDest);

	return sz;
}

long CString_To_long(const CString &strValue)
{
#ifdef _UNICODE
	return wcstol(strValue.GetString(), NULL, 10);
#else
	return strtol(strValue.GetString(), NULL, 10);
#endif

// 	float fValue = strValue.toFloat();//zhouhj 20220312  strValue.toLong()模式,在字符串中包含小数点时转换失败,故按此方式转换
// 	long nValue = fValue;
// 
// 	if ((fValue-nValue)>=0.5)
// 	{
// 		nValue++;
// 	}
// 	else if ((fValue-nValue)<=-0.5)
// 	{
// 		nValue--;
// 	}
// 
//     return nValue;
}

unsigned long CString_To_ulong(const CString &strValue)
{
#ifdef _UNICODE
	return wcstoul(strValue.GetString(), NULL, 10);
#else
	return strtoul(strValue.GetString(), NULL, 10);
#endif
}

__int64 CString_To_i64(const CString &strValue)
{
    return strValue.toLongLong();
}

double CString_To_double(const CString &strValue)
{
    return strValue.toDouble();
}

UINT CString_HEX_to_UINT(const CString &strText)
{
	UINT nValue = 0;
	char *pszText = NULL;

#ifdef UNICODE
	CString_to_char(strText, &pszText);
#else
	pszText = (char*)strText.GetString();
#endif

	if (strText.GetLength() < 2)
	{
		sscanf(pszText,_T("%d"),&nValue);

#ifdef UNICODE
		delete pszText;
#endif

		return nValue;
	}

	char ch0 = strText.GetAt(0);
	char ch1 = strText.GetAt(1);

	if (ch0 == '0' && ( (ch1=='x') || (ch1 == 'X')) )
		sscanf(pszText,_T("%x"),&nValue);
	else
		sscanf(pszText,_T("%d"),&nValue);

#ifdef UNICODE
	delete pszText;
#endif

	return nValue;
}

BOOL CString_to_CTime(const CString &strTime, CTime &tm, BOOL bErrUseCurrTime)
{
#ifdef USE_Custom_CDateTime
    CTime tm1 = CTime::GetTime_FromString(strTime);
    tm = tm1;
#else
    QDateTime t = CTime::fromString(strTime);
    tm = t;
#endif
/*	COleDateTime tmOle;
	
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
*/
	return FALSE;
}

/*
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
*/
