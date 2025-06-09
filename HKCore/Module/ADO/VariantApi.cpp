#include "stdafx.h"
#include "VariantApi.h"



BOOL VariantToCString(const _variant_t &var, CString &strValue)  
{  
	BOOL bRet = TRUE; 
	switch (var.vt)  
	{  
	case VT_BSTR:    //�ַ���  
	case VT_LPSTR:  
	case VT_LPWSTR:  
		strValue = (LPCTSTR)(_bstr_t)var;  
		break;  
	case VT_I1:        //�޷����ַ�  
	case VT_UI1:  
		strValue.Format(_T("%d"), var.bVal); 
		break;  
	case VT_I2:        //������  
		strValue.Format(_T("%d"), var.iVal);  
		break;  
	case VT_UI2:    //�޷��Ŷ�����  
		strValue.Format(_T("%d"), var.uiVal);  
		break;  
	case VT_INT:    //����  
		strValue.Format(_T("%d"), var.intVal);  
		break;  
	case VT_I4:        //����  
	case VT_I8:        //������  
		strValue.Format(_T("%d"), var.lVal);  
		break;  
	case VT_UINT:    //�޷�������  
		strValue.Format(_T("%d"), var.uintVal);  
		break;  
	case VT_UI4:    //�޷�������  
	case VT_UI8:    //�޷��ų�����  
		strValue.Format(_T("%d"), var.ulVal);  
		break;  
	case VT_VOID:  
		strValue.Format(_T("%8x"), var.byref);  
		break;  
	case VT_R4:        //������  
		strValue.Format(_T("%.4f"), var.fltVal);  
		break;  
	case VT_R8:        //˫������  
		strValue.Format(_T("%.8f"), var.dblVal);  
		break;  
	case VT_DECIMAL://С��  
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
	case VT_BOOL:    //������  
		strValue = var.boolVal ? "TRUE" : "FALSE";  
		break;  
	case VT_DATE:    //������  
		{  
			DATE dt = var.date;  
			COleDateTime da = COleDateTime(dt);  
			strValue = da.Format(_T("%Y-%m-%d %H:%M:%S"));  
		}  
		break;  
	case VT_NULL:    //NULLֵ  
	case VT_EMPTY:    //��  
		strValue = "";  
		break;  
	case VT_UNKNOWN://δ֪����  
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
	case VT_BSTR:    //�ַ���  
	case VT_LPSTR:  
	case VT_LPWSTR: 
		strTmp = vt.bstrVal;
		nValue = CString_To_long(strTmp);
		break;
	case VT_I1:        //�޷����ַ�  
	case VT_UI1: 
		nValue = vt.bVal;
		break;  
	case VT_I2:        //������  
		nValue = vt.iVal;
		break;  
	case VT_UI2:    //�޷��Ŷ����� 
		nValue = vt.uiVal;
		break;  
	case VT_INT:    //����  
		nValue = vt.intVal; 
		break;  
	case VT_I4:        //����  
	case VT_I8:        //������  
		nValue = vt.lVal;
		break;  
	case VT_UINT:    //�޷������� 
		nValue = vt.uintVal;
		break;  
	case VT_UI4:    //�޷�������  
	case VT_UI8:    //�޷��ų����� 
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
	case VT_BSTR:    //�ַ���  
	case VT_LPSTR:  
	case VT_LPWSTR: 
		strTmp = vt.bstrVal;
		nValue = CString_To_i64(strTmp);
		break;
	case VT_I1:        //�޷����ַ�  
	case VT_UI1: 
		nValue = vt.bVal;
		break;  
	case VT_I2:        //������  
		nValue = vt.iVal;
		break;  
	case VT_UI2:    //�޷��Ŷ����� 
		nValue = vt.uiVal;
		break;  
	case VT_INT:    //����  
		nValue = vt.intVal; 
		break;  
	case VT_I4:        //����  
	case VT_I8:        //������  
		nValue = vt.lVal;
		break;  
	case VT_UINT:    //�޷������� 
		nValue = vt.uintVal;
		break;  
	case VT_UI4:    //�޷�������  
	case VT_UI8:    //�޷��ų����� 
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
	case VT_BSTR:    //�ַ���  
	case VT_LPSTR:  
	case VT_LPWSTR: 
		strTmp = vt.bstrVal;
		fValue = CString_To_double(strTmp);
		break;
	case VT_R4:        //������  
		fValue = vt.fltVal; 
		break;  
	case VT_R8:        //˫������ 
		fValue = vt.dblVal;
		break;  
	case VT_DECIMAL://С�� 
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
	case VT_DATE:    //������  
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