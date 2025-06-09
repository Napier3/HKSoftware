// AtlGloblaApi.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ATLGLOBALAPI_H__)
#define _ATLGLOBALAPI_H__

#include <comutil.h>
#include "..\AtlMemBuffer\AnsiStringPrintf.h"

inline void CComBSTR_LPCTSTR(const CComBSTR &oComBstr, LPCTSTR strLPCT)
{
	USES_CONVERSION;   
	strLPCT   =   W2T(oComBstr);
}

inline void char_to_BSTR(const char *pstrSrc, BSTR *bstrDest)
{
	*bstrDest = _com_util::ConvertStringToBSTR(pstrSrc);
}

inline long bstr_to_char(BSTR bstrSrc, char *pstrDest)
{
	long nLen = wcslen(bstrSrc);
	return WideCharToMultiByte(CP_ACP, 0, bstrSrc, -1, pstrDest, nLen, NULL, NULL); 
}

inline void wchar_t_to_ComBSTR(wchar_t* pSrcBegin, wchar_t* pSrcEnd, CComBSTR &oStr)
{
	long nLen = 0;
	
	if(pSrcEnd < pSrcBegin)
	{
		nLen = 1;
	}
	else
	{
		nLen = pSrcEnd - pSrcBegin + 2;
	}
	
	oStr.m_str = ::SysAllocStringLen(NULL, nLen);

	if (nLen > 1)
	{
		memcpy(oStr.m_str, pSrcBegin, (nLen-1)*sizeof(wchar_t));
	}

	memset(oStr.m_str + nLen-1, 0, sizeof(wchar_t));
}

inline BOOL VARIANT_to_long(const VARIANT &vValue, long &nValue)
{
	BOOL bTrue = TRUE;

	switch(vValue.vt)
	{
	case VT_I2:
		nValue = vValue.iVal;
		break;
	case VT_I4:
		nValue = vValue.lVal;
		break;
	case VT_UI2:
		nValue = vValue.uiVal;
		break;
	case VT_UI4:
		nValue = vValue.ulVal;
		break;
	case VT_INT:
		nValue = vValue.intVal;
		break;
	case VT_UINT:
		nValue = vValue.uintVal;
		break;
	default:
		bTrue = FALSE;
		break;
	}
	
	return bTrue;
}


inline BOOL VARIANT_to_CComBSTR(const VARIANT &vValue, CComBSTR &bstrValue)
{
	BOOL bTrue = TRUE;

	switch(vValue.vt)
	{
	case VT_BSTR:
		bstrValue = vValue.bstrVal;
		break;
	default:
		bTrue = FALSE;
		break;
	}

	return bTrue;
}

inline BOOL VARIANT_to_CComBSTR(const VARIANT &vValue, BSTR* pbstrValue)
{
	BOOL bTrue = TRUE;
	
	switch(vValue.vt)
	{
	case VT_BSTR:
		*pbstrValue = vValue.bstrVal;
		break;
	default:
		bTrue = FALSE;
		break;
	}
	
	return bTrue;
}

inline float _bstr_to_float(const CComBSTR &bstrVal)
{
	char pszBuff[32];
	memset(pszBuff, 0, 32);
	WideCharToMultiByte(CP_ACP, 0, bstrVal, wcslen(bstrVal), pszBuff, 32, NULL, NULL); 
	return (float)(atof(pszBuff));
}

inline double _bstr_to_double(const CComBSTR &bstrVal)
{
	char pszBuff[32];
	memset(pszBuff, 0, 32);
	WideCharToMultiByte(CP_ACP, 0, bstrVal, wcslen(bstrVal), pszBuff, 32, NULL, NULL); 
	return atof(pszBuff);
}

inline long _str_i_cmp_(const char *dst, const char *src)
{
	int ch1, ch2;
	
	do 
	{		
		if ( ((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z') )
		{
			ch1 += 0x20;
		}
		
		if ( ((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z') )
		{	
			ch2 += 0x20;
		}
		
	} while ( (ch1 != 0) && (ch2 != 0) && (ch1 == ch2) );
	
	return(ch1 - ch2);
}

inline void LONG_to_CComBSTR(long n,CComBSTR &bstr)
{
	char pszBuffer[32];
	CAnsiStringPrintf oStrPrintf(pszBuffer);
	oStrPrintf.sprintf("%d", n);
	char_to_BSTR(pszBuffer, &bstr);
}

inline void FLOAT_to_CComBSTR(float f,CComBSTR &bstr)
{
	char pszBuffer[32];
	CAnsiStringPrintf oStrPrintf(pszBuffer);
	oStrPrintf.sprintf("%f", f);
	char_to_BSTR(pszBuffer, &bstr);
}
#endif // !defined(_ATLGLOBALAPI_H__)
