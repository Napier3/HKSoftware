#include "stdafx.h"
#include "XML2Interface.h"
#include "..\MemBuffer\BufferBase.h"

BOOL xml_OpenFile(MSXML::IXMLDOMDocumentPtr &oDoc, const CString &strFile)
{
	oDoc = NULL;
	HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML::DOMDocument));

	if(!SUCCEEDED(hr)) 
	{ 
		return FALSE;
	} 

	BSTR bstrFile = strFile.AllocSysString();
	BOOL bTrue = oDoc->load(bstrFile);
	::SysFreeString(bstrFile);

	return bTrue;
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, CString &strAttrVal)
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

BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, long &nAttrVal)
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

BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, double &dAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	_variant_t Value;
	Value = oElement->getAttribute(strAttrName);
	Value.ChangeType(VT_R8);
	
	if (Value.vt == VT_R8)
	{
		dAttrVal = Value.dblVal;
		return TRUE;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, short &unAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	_variant_t Value;
	Value = oElement->getAttribute(strAttrName);
	Value.ChangeType(VT_I2);
	
	if (Value.vt == VT_I2)
	{
		unAttrVal = Value.iVal;
		return TRUE;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, float &fAttrVal)
{
	if (oElement==NULL)
	{
		return FALSE;
	}

	_variant_t Value;
	Value = oElement->getAttribute(strAttrName);
	Value.ChangeType(VT_R4);
	
	if (Value.vt == VT_R4)
	{
		fAttrVal = Value.fltVal;
		return TRUE;
	}

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, _variant_t &vValue)
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
BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, SYSTEMTIME &tmSys)
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

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, const CString &strAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	BSTR bstrVal = strAttrVal.AllocSysString();
	oElement->setAttribute(strAttrName, bstrVal);
	::SysFreeString(bstrVal);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode,long &nAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	oElement->setAttribute(strAttrName, nAttrVal);
	
	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, double &dAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	oElement->setAttribute(strAttrName, dAttrVal);
	
	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, short &unAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	oElement->setAttribute(strAttrName,unAttrVal);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, float &fAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName,fAttrVal);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, VARIANT &vValue)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	
	if (oElement==NULL)
	{
		return FALSE;
	}
	
	oElement->setAttribute(strAttrName,vValue);
	
	return TRUE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, const SYSTEMTIME &tmSys)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	wchar_t wstr[40];
	wsprintf(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);

	oElement->setAttribute(strAttrName, wstr);

	return TRUE;
}