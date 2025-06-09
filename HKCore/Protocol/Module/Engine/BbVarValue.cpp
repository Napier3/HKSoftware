#include "StdAfx.h"
#include "BbVarValue.h"
#include "../../../Module/API/StringApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBbVarValue::CBbVarValue(void)
{
	vt = VVT_EMPTY;
	pdblVal = NULL;
}

CBbVarValue::~CBbVarValue(void)
{
}


CString CBbVarValue::ToString()
{
	CString strVal;
	ToString(strVal);
	return strVal;
}
void CBbVarValue::ToString(CString &strVal)
{

}

void CBbVarValue::FromString(const CString &strValue)
{

}

void CBbVarValue::FromString(BSTR bstrValue)
{
	char *pString = NULL;
	BSTR_to_char(bstrValue, &pString);
	FromString(pString);
	delete pString;
}

void CBbVarValue::FromString(char* pszValue)
{
	fltVal = (FLOAT)atof(pszValue);
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
CBbVarValue* CBbVarValue::Clone()
{
	CBbVarValue* pNew = new CBbVarValue();
	Copy(pNew);
	return pNew;
}

BOOL CBbVarValue::Copy(CBbVarValue* pDest)
{
	pDest->vt = vt;
	switch(vt)
	{
	case VVT_I1				: pDest->cVal = cVal; break;
	case VVT_UI1			: pDest->bVal = bVal; break;
	case VVT_I2				: pDest->iVal = iVal; break;
	case VVT_UI2			: pDest->uiVal = uiVal; break;
	case VVT_INT			: pDest->intVal = intVal; break;
	case VVT_UINT			: pDest->uintVal = uintVal; break;
	case VVT_I4				: pDest->lVal = lVal; break;
	case VVT_UI4			: pDest->ulVal = ulVal; break;
	case VVT_R4 			: pDest->fltVal = fltVal; break;
	case VVT_R8 			: pDest->dblVal = dblVal; break;
	case VVT_BSTR			: pDest->bstrVal = bstrVal; break;
	case VVT_REF | VVT_I1	: pDest->pcVal = pcVal; break;
	case VVT_REF | VVT_UI1	: pDest->pbVal = pbVal; break;
	case VVT_REF | VVT_I2	: pDest->piVal = piVal; break;
	case VVT_REF | VVT_UI2	: pDest->puiVal = puiVal; break;
	case VVT_REF | VVT_INT	: pDest->pintVal = pintVal; break;
	case VVT_REF | VVT_UINT	: pDest->puintVal = puintVal; break;
	case VVT_REF | VVT_I4	: pDest->plVal = plVal; break;
	case VVT_REF | VVT_UI4	: pDest->pulVal = pulVal; break;
	case VVT_REF | VVT_R4	: pDest->pfltVal = pfltVal; break;
	case VVT_REF | VVT_R8	: pDest->pdblVal = pdblVal; break;
	case VVT_REF | VVT_BSTR	: pDest->pbstrVal = pbstrVal; break;
	default: return FALSE;
	}
	return TRUE;
}

BOOL CBbVarValue::IsEqual(CBbVarValue* pObj)
{
	if (vt != pObj->vt)
	{
		return FALSE;
	}
	BOOL ret;
	switch(vt)
	{
	case VVT_I1				: ret = (pObj->cVal == cVal) ? TRUE : FALSE; break;
	case VVT_UI1			: ret = (pObj->bVal == bVal) ? TRUE : FALSE; break;
	case VVT_I2				: ret = (pObj->iVal == iVal) ? TRUE : FALSE; break;
	case VVT_UI2			: ret = (pObj->uiVal == uiVal) ? TRUE : FALSE; break;
	case VVT_INT			: ret = (pObj->intVal == intVal) ? TRUE : FALSE; break;
	case VVT_UINT			: ret = (pObj->uintVal == uintVal) ? TRUE : FALSE; break;
	case VVT_I4				: ret = (pObj->lVal == lVal) ? TRUE : FALSE; break;
	case VVT_UI4			: ret = (pObj->ulVal == ulVal) ? TRUE : FALSE; break;
	case VVT_R4 			: ret = (pObj->fltVal == fltVal) ? TRUE : FALSE; break;
	case VVT_R8 			: ret = (pObj->dblVal == dblVal) ? TRUE : FALSE; break;
	case VVT_BSTR			: ret = (pObj->bstrVal == bstrVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_I1	: ret = (pObj->pcVal == pcVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_UI1	: ret = (pObj->pbVal == pbVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_I2	: ret = (pObj->piVal == piVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_UI2	: ret = (pObj->puiVal == puiVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_INT	: ret = (pObj->pintVal == pintVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_UINT	: ret = (pObj->puintVal == puintVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_I4	: ret = (pObj->plVal == plVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_UI4	: ret = (pObj->pulVal == pulVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_R4	: ret = (pObj->pfltVal == pfltVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_R8	: ret = (pObj->pdblVal == pdblVal) ? TRUE : FALSE; break;
	case VVT_REF | VVT_BSTR	: ret = (pObj->pbstrVal == pbstrVal) ? TRUE : FALSE; break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL CBbVarValue::Clear()
{
	switch(vt)
	{
	case VVT_I1				: cVal = 0; break;
	case VVT_UI1			: bVal = 0; break;
	case VVT_I2				: iVal = 0; break;
	case VVT_UI2			: uiVal = 0; break;
	case VVT_INT			: intVal = 0; break;
	case VVT_UINT			: uintVal = 0; break;
	case VVT_I4				: lVal = 0; break;
	case VVT_UI4			: ulVal = 0; break;
	case VVT_R4 			: fltVal = 0; break;
	case VVT_R8 			: dblVal = 0; break;
	case VVT_BSTR			: bstrVal = 0; break;
	case VVT_REF | VVT_I1	: pcVal = NULL; break;
	case VVT_REF | VVT_UI1	: pbVal = NULL; break;
	case VVT_REF | VVT_I2	: piVal = NULL; break;
	case VVT_REF | VVT_UI2	: puiVal = NULL; break;
	case VVT_REF | VVT_INT	: pintVal = NULL; break;
	case VVT_REF | VVT_UINT	: puintVal = NULL; break;
	case VVT_REF | VVT_I4	: plVal = NULL; break;
	case VVT_REF | VVT_UI4	: pulVal = NULL; break;
	case VVT_REF | VVT_R4	: pfltVal = NULL; break;
	case VVT_REF | VVT_R8	: pdblVal = NULL; break;
	case VVT_REF | VVT_BSTR	: pbstrVal = NULL; break;
	default: break;
	}
	vt = VVT_EMPTY;
	return TRUE;
}