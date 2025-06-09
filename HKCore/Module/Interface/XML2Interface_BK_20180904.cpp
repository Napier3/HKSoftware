#include "stdafx.h"
#include "XML2Interface.h"
#include "..\MemBuffer\BufferBase.h"

BOOL xml_OpenFile(MSXML2::IXMLDOMDocumentPtr &oDoc, const CString &strFile)
{
	oDoc = NULL;
	HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));

	if(!SUCCEEDED(hr)) 
	{ 
		return FALSE;
	} 

	BSTR bstrFile = strFile.AllocSysString();
	BOOL bTrue = oDoc->load(bstrFile);
	::SysFreeString(bstrFile);

	return bTrue;
}
MSXML2::IXMLDOMNodePtr xml_FindAttibute(const BSTR &strAttrName, MSXML2::IXMLDOMNamedNodeMapPtr oAttrs)
{
	long nCount = oAttrs->Getlength();
	long nIndex = 0;
	MSXML2::IXMLDOMNodePtr oAttr = NULL;
	MSXML2::IXMLDOMNodePtr oAttrFine = NULL;
	_bstr_t nodeName;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oAttr = oAttrs->Getitem(nIndex);
		nodeName = oAttr->GetnodeName();

		if (wcscmp(strAttrName, nodeName) == 0)
		{
			oAttrFine = oAttr;
			break;
		}
	}

	return oAttrFine;
}

MSXML2::IXMLDOMNodePtr xml_FindAttibute(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode)
{
	MSXML2::IXMLDOMNamedNodeMapPtr oAttrs = NULL;
	oNode->get_attributes(&oAttrs);

	return xml_FindAttibute(strAttrName, oAttrs);
}


BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, CString &strAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = oElement->getAttribute(strAttrName);

	if (Value.vt == VT_BSTR)
	{
		strAttrVal = Value.bstrVal;
		return TRUE;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, wchar_t *strAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = oElement->getAttribute(strAttrName);

	if (Value.vt == VT_BSTR)
	{
		wcscpy(strAttrVal, Value.bstrVal);
		return TRUE;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, long &nAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = oElement->getAttribute(strAttrName);
	BSTR str;

	switch (Value.vt)
	{
	case VT_I4:
		nAttrVal = Value.intVal;
		return TRUE;
	case VT_BSTR:
		str = Value.bstrVal;
		nAttrVal = _wtoi(str);
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, DWORD &dwAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = oElement->getAttribute(strAttrName);
	BSTR str;

	switch (Value.vt)
	{
	case VT_I4:
		dwAttrVal = Value.intVal;
		return TRUE;
	case VT_BSTR:
		str = Value.bstrVal;
		dwAttrVal = _wtoi(str);
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}


BOOL xml_GetAttibuteValue_Color(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, COLORREF &crAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = oElement->getAttribute(strAttrName);
	BSTR str;

	switch (Value.vt)
	{
	case VT_I4:
		crAttrVal = Value.intVal;
		return TRUE;
	case VT_UI4:
		crAttrVal = Value.ulVal;
		return TRUE;
	case VT_BSTR:
		str = Value.bstrVal;
		crAttrVal = GetRGBColor((CString)str, crAttrVal);
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, double &dAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	_variant_t Value;
	Value = oElement->getAttribute(strAttrName);
	
	if (Value.vt == VT_NULL)
	{
		return FALSE;
	}
	
	Value.ChangeType(VT_R8);
	
	if (Value.vt == VT_R8)
	{
		dAttrVal = Value.dblVal;
		return TRUE;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, short &unAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	_variant_t Value;
	Value = oElement->getAttribute(strAttrName);

	if (Value.vt == VT_NULL)
	{
		return FALSE;
	}

	Value.ChangeType(VT_I2);
	
	if (Value.vt == VT_I2)
	{
		unAttrVal = Value.iVal;
		return TRUE;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, float &fAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	_variant_t Value;
	Value = oElement->getAttribute(strAttrName);

	if (Value.vt == VT_NULL)
	{
		return FALSE;
	}

	Value.ChangeType(VT_R4);
	
	if (Value.vt == VT_R4)
	{
		fAttrVal = Value.fltVal;
		return TRUE;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, _variant_t &vValue)
{
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	vValue = oElement->getAttribute(strAttrName);

	return TRUE;
}

//XML日期时间格式："2010-06-30T09:30:47Z"
//此种转换方式效率不高，但是考虑系统在读取xml文件时，不可能有太多的日期时间数据
//所以可以使用此种方法实现     lijq
BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, SYSTEMTIME &tmSys)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	_variant_t Value;
	Value = oElement->getAttribute(strAttrName);
	ASSERT (Value.vt == VT_BSTR);

	if (Value.vt != VT_BSTR)
	{
		return FALSE;
	}

	CBufferBase oBuffer(Value.bstrVal);
	oBuffer.FormatBuffer();
	oBuffer.FormatBuffer('-');
	oBuffer.FormatBuffer('T');
	oBuffer.FormatBuffer('Z');
// 	oBuffer.FormatBuffer('t');
// 	oBuffer.FormatBuffer('z');
	oBuffer.FormatBuffer(':');
	oBuffer.FormatBuffer('/');

	oBuffer.ResetPointer();
	const char* pszTemp;

	pszTemp = oBuffer.GetString();
	if (oBuffer.IsPoiterInBuffer(pszTemp))
	{
		tmSys.wYear = atoi(pszTemp);
	}

	pszTemp = oBuffer.NextString();
	if(oBuffer.IsPoiterInBuffer(pszTemp))
	{
		tmSys.wMonth = atoi(pszTemp);
	}

	pszTemp = oBuffer.NextString();
	if(oBuffer.IsPoiterInBuffer(pszTemp))
	{
		tmSys.wDay = atoi(pszTemp);
	}

	pszTemp = oBuffer.NextString();
	if(oBuffer.IsPoiterInBuffer(pszTemp))
	{
		tmSys.wMinute = atoi(pszTemp);
	}

	pszTemp = oBuffer.NextString();
	if(oBuffer.IsPoiterInBuffer(pszTemp))
	{
		tmSys.wSecond = atoi(pszTemp);
	}

	pszTemp = oBuffer.NextString();
	if(oBuffer.IsPoiterInBuffer(pszTemp))
	{
		tmSys.wMilliseconds = atoi(pszTemp);
	}

	return TRUE;
}

BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, const CString &strAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	BSTR bstrVal = strAttrVal.AllocSysString();
	oElement->setAttribute(strAttrName, bstrVal);
	::SysFreeString(bstrVal);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, const wchar_t *strAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName, strAttrVal);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode,long &nAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	oElement->setAttribute(strAttrName, nAttrVal);
	
	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode,DWORD &dwAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName, dwAttrVal);

	return FALSE;
}

BOOL xml_SetAttributeValue_Color(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, COLORREF &crAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	CString strColor;
	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	oElement->setAttribute(strAttrName, _bstr_t(pszColor));

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, double &dAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	oElement->setAttribute(strAttrName, dAttrVal);
	
	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, short &unAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	oElement->setAttribute(strAttrName,unAttrVal);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, float &fAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName,fAttrVal);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, VARIANT &vValue)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	oElement->setAttribute(strAttrName,vValue);
	
	return TRUE;
}

BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, const SYSTEMTIME &tmSys)
{
	MSXML2::IXMLDOMElementPtr oElement = oNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

#ifdef _UNICODE
	wchar_t wstr[40];
	wsprintf(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	oElement->setAttribute(strAttrName, wstr);
#else
	char wstr[40];
	sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	oElement->setAttribute(strAttrName, _bstr_t(wstr));
#endif
	return TRUE;
}

BOOL xml_SetCDATA(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, const CString &strText)
{
	BOOL bTrue = TRUE;

	try 
	{
		MSXML2::IXMLDOMNodePtr oNode;
		oNode = oXMLDoc->createCDATASection(_T(""));
		ASSERT( oNode != NULL);
		oElement->appendChild(oNode);
		oNode->put_text((_bstr_t)strText);
	} 
	catch(...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}



//////////////////////////////////////////////////////////////////////////
//
BOOL xml_GetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, CString &strAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = oElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		strAttrVal = (BSTR)(oNode->Gettext());
		return TRUE;
	}

	return FALSE;
}


BOOL xml_GetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, long &nAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = oElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		nAttrVal = _wtol(bstr);
		return TRUE;
	}

	return FALSE;
}


BOOL xml_GetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, DWORD &dwAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = oElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		dwAttrVal = _wtol(bstr);
		return TRUE;
	}

	return FALSE;
}


BOOL xml_GetElementText_Color(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, COLORREF &crAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = oElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		BSTR bstr = oNode->Gettext();
		crAttrVal = GetRGBColor((CString)bstr, crAttrVal);
		return TRUE;
	}


	return FALSE;
}

BOOL xml_GetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, double &dAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = oElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		dAttrVal = _wtof(bstr);
		return TRUE;
	}


	return FALSE;
}

BOOL xml_GetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, short &unAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = oElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		unAttrVal = (short)_wtol(bstr);
		return TRUE;
	}


	return FALSE;
}

BOOL xml_GetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, float &fAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = oElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		fAttrVal = (float)_wtof(bstr);
		return TRUE;
	}


	return FALSE;
}

BOOL xml_GetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, _variant_t &vValue)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = oElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		vValue = oNode->Gettext();
		return TRUE;
	}

	return FALSE;
}

BOOL xml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, const CString &strAttrVal)
{
	CString strVal;
	MSXML2::IXMLDOMElementPtr oElement = NULL;
	ASSERT(strAttrName != NULL);

	oElement = oXMLDoc->createElement(strAttrName);

	if (oParent == NULL)
	{
		oXMLDoc->appendChild(oElement);
	}
	else
	{
		oParent->appendChild(oElement);
	}

	MSXML2::IXMLDOMNodePtr oChildNode = oElement;
	oChildNode->put_text(_bstr_t(strAttrVal));

	return TRUE;
}

BOOL xml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, long &nAttrVal)
{
	CString strVal;
	strVal.Format(_T("%d"), nAttrVal);
	
	return xml_SetElementText(strAttrName, oXMLDoc, oParent, strVal);
}

BOOL xml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, DWORD &dwAttrVal)
{
	CString strVal;
	strVal.Format(_T("%d"), dwAttrVal);

	return xml_SetElementText(strAttrName, oXMLDoc, oParent, strVal);

	return TRUE;
}

BOOL xml_SetElementText_Color(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, COLORREF &crAttrVal)
{
	return TRUE;
}

BOOL xml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, double &dAttrVal)
{
	CString strVal;
	strVal.Format(_T("%f"), dAttrVal);

	return xml_SetElementText(strAttrName, oXMLDoc, oParent, strVal);
}

BOOL xml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, short &unAttrVal)
{
	return TRUE;
}

BOOL xml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, float &fAttrVal)
{
	CString strVal;
	strVal.Format(_T("%f"), fAttrVal);

	return xml_SetElementText(strAttrName, oXMLDoc, oParent, strVal);
}

BOOL xml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, VARIANT &vValue)
{
	return TRUE;
}

BOOL xml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, const SYSTEMTIME &tmSys)
{
	return TRUE;
}

