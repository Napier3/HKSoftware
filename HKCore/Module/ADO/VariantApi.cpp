#include "stdafx.h"
#include "VariantApi.h"



BOOL VariantToCString(const _variant_t &var, CString &strValue)  
{  
	BOOL bRet = TRUE; 
	switch (var.vt)  
	{  
	case VT_BSTR:    //字符串  
	case VT_LPSTR:  
	case VT_LPWSTR:  
		strValue = (LPCTSTR)(_bstr_t)var;  
		break;  
	case VT_I1:        //无符号字符  
	case VT_UI1:  
		strValue.Format(_T("%d"), var.bVal); 
		break;  
	case VT_I2:        //短整型  
		strValue.Format(_T("%d"), var.iVal);  
		break;  
	case VT_UI2:    //无符号短整型  
		strValue.Format(_T("%d"), var.uiVal);  
		break;  
	case VT_INT:    //整型  
		strValue.Format(_T("%d"), var.intVal);  
		break;  
	case VT_I4:        //整型  
	case VT_I8:        //长整型  
		strValue.Format(_T("%d"), var.lVal);  
		break;  
	case VT_UINT:    //无符号整型  
		strValue.Format(_T("%d"), var.uintVal);  
		break;  
	case VT_UI4:    //无符号整型  
	case VT_UI8:    //无符号长整型  
		strValue.Format(_T("%d"), var.ulVal);  
		break;  
	case VT_VOID:  
		strValue.Format(_T("%8x"), var.byref);  
		break;  
	case VT_R4:        //浮点型  
		strValue.Format(_T("%.4f"), var.fltVal);  
		break;  
	case VT_R8:        //双精度型  
		strValue.Format(_T("%.8f"), var.dblVal);  
		break;  
	case VT_DECIMAL://小数  
		strValue.Format(_T("%.8f"), (double)var);  
		break;  
	case VT_CY:  
		{  
			COleCurrency cy = var.cyVal;  
			strValue = cy.Format();  
		}  
		break;  
	case VT_BLOB:  
	case VT_BLOB_OBJECT:  
	case 0x2011:  
		strValue = "[BLOB]";  
		break;  
	case VT_BOOL:    //布尔型  
		strValue = var.boolVal ? "TRUE" : "FALSE";  
		break;  
	case VT_DATE:    //日期型  
		{  
			DATE dt = var.date;  
			COleDateTime da = COleDateTime(dt);  
			strValue = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
		}  
		break;  
	case VT_NULL:    //NULL值  
	case VT_EMPTY:    //空  
		strValue = "";  
		break;  
	case VT_UNKNOWN://未知类型  
	default:  
		strValue = "UN_KNOW";  
		bRet = FALSE;
		break;  
	}  
	return bRet;  
} 

BOOL VariantToLong(const _variant_t &vt,long &nValue) 
{
	BOOL ret = TRUE;
	CString strTmp;

	switch (vt.vt)  
	{
	case VT_BSTR:    //字符串  
	case VT_LPSTR:  
	case VT_LPWSTR: 
		strTmp = vt.bstrVal;
		nValue = CString_To_long(strTmp);
		break;
	case VT_I1:        //无符号字符  
	case VT_UI1: 
		nValue = vt.bVal;
		break;  
	case VT_I2:        //短整型  
		nValue = vt.iVal;
		break;  
	case VT_UI2:    //无符号短整型 
		nValue = vt.uiVal;
		break;  
	case VT_INT:    //整型  
		nValue = vt.intVal; 
		break;  
	case VT_I4:        //整型  
	case VT_I8:        //长整型  
		nValue = vt.lVal;
		break;  
	case VT_UINT:    //无符号整型 
		nValue = vt.uintVal;
		break;  
	case VT_UI4:    //无符号整型  
	case VT_UI8:    //无符号长整型 
		nValue = vt.ulVal; 
		break;
	default:
		ret = FALSE;
		break;
	}

	return ret;
}

BOOL VariantToInt64(const _variant_t &vt,__int64 &nValue)
{
	BOOL ret = TRUE;
	CString strTmp;

	switch (vt.vt)  
	{
	case VT_BSTR:    //字符串  
	case VT_LPSTR:  
	case VT_LPWSTR: 
		strTmp = vt.bstrVal;
		nValue = CString_To_i64(strTmp);
		break;
	case VT_I1:        //无符号字符  
	case VT_UI1: 
		nValue = vt.bVal;
		break;  
	case VT_I2:        //短整型  
		nValue = vt.iVal;
		break;  
	case VT_UI2:    //无符号短整型 
		nValue = vt.uiVal;
		break;  
	case VT_INT:    //整型  
		nValue = vt.intVal; 
		break;  
	case VT_I4:        //整型  
	case VT_I8:        //长整型  
		nValue = vt.lVal;
		break;  
	case VT_UINT:    //无符号整型 
		nValue = vt.uintVal;
		break;  
	case VT_UI4:    //无符号整型  
	case VT_UI8:    //无符号长整型 
		nValue = vt.ulVal; 
		break;
	default:
		ret = FALSE;
		break;
	}

	return ret;
}

BOOL VariantToDouble(const _variant_t &vt,double &fValue) 
{
	BOOL ret = TRUE;
	CString strTmp;

	switch (vt.vt)  
	{
	case VT_BSTR:    //字符串  
	case VT_LPSTR:  
	case VT_LPWSTR: 
		strTmp = vt.bstrVal;
		fValue = CString_To_double(strTmp);
		break;
	case VT_R4:        //浮点型  
		fValue = vt.fltVal; 
		break;  
	case VT_R8:        //双精度型 
		fValue = vt.dblVal;
		break;  
	case VT_DECIMAL://小数 
		fValue = (double)vt;
		break;
	default:
		ret = FALSE;
		break;
	}

	return ret;
}

BOOL VariantToFloat(const _variant_t &vt,float &fValue)
{
	BOOL bRet = FALSE;
	double fVal = 0;
	bRet = VariantToDouble(vt,fVal);
	fValue = (float)fVal;
	return bRet;
}

BOOL VariantToDWord(const _variant_t &vt,DWORD &nValue)
{
	BOOL bRet = FALSE;
	long nVal = 0;
	bRet = VariantToLong(vt,nVal);
	nValue = (DWORD)nVal;
	return bRet;
}

BOOL VariantToSystemTime(const _variant_t &var,SYSTEMTIME &tmValue)  
{  
	BOOL bRet = TRUE; 
	switch (var.vt)  
	{   
	case VT_DATE:    //日期型  
		{  
			DATE dt = var.date;  
			COleDateTime da = COleDateTime(dt); 
			tmValue.wYear = da.GetYear();
			tmValue.wMonth = da.GetMonth();
			tmValue.wDay = da.GetDay();
			tmValue.wHour = da.GetHour();
			tmValue.wMinute = da.GetMinute();
			tmValue.wSecond = da.GetSecond();
		}  
		break;  
	default:  
		bRet = FALSE;
		break;  
	}  
	return bRet;  
} 