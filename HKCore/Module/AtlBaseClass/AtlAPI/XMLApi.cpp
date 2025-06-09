// XMLApi.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XMLApi.h"
#include "..\..\Module\AtlBaseClass\AtlGloblaApi.h"

MSXML::IXMLDOMNodePtr xml_FindAttibute(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs)
{
	long nCount = oAttrs->Getlength();
	long nIndex = 0;
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	MSXML::IXMLDOMNodePtr oAttrFine = NULL;
	_bstr_t nodeName;
	BSTR    bstrNodeName;
	CComBSTR comAttName(strAttrName);
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oAttr = oAttrs->Getitem(nIndex);
		nodeName = oAttr->GetnodeName();
		bstrNodeName = nodeName.GetBSTR();
		if (comAttName == bstrNodeName)
		{
			oAttrFine = oAttr;
			break;
		}
	}
	
	return oAttrFine;
}

MSXML::IXMLDOMNodePtr xml_FindAttibute(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode)
{
	MSXML::IXMLDOMNamedNodeMapPtr oAttrs = NULL;
	oNode->get_attributes(&oAttrs);

	return xml_FindAttibute(strAttrName, oAttrs);
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, CComBSTR &strAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oNode);

	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		strAttrVal = (BSTR)(_bstr_t(oAttr->nodeTypedValue));
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs, CComBSTR &strAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oAttrs);
	
	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		strAttrVal = (BSTR)(_bstr_t(oAttr->nodeTypedValue));
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, long &nAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oNode);
	
	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		nAttrVal = oAttr->nodeTypedValue;
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs, long &nAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oAttrs);
	
	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		nAttrVal = oAttr->nodeTypedValue;
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, double &dAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oNode);
	
	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		dAttrVal = oAttr->nodeTypedValue;
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs, double &dAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oAttrs);
	
	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		dAttrVal = oAttr->nodeTypedValue;
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, short &unAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oNode);
	
	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		unAttrVal = oAttr->nodeTypedValue;
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs,short &unAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oAttrs);
	
	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		unAttrVal = oAttr->nodeTypedValue;
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, float &dAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oNode);

	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		dAttrVal = oAttr->nodeTypedValue;
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs, float &dAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oAttrs);

	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		dAttrVal = oAttr->nodeTypedValue;
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, _bstr_t &vAttrVal)
{
	MSXML::IXMLDOMNodePtr oAttr = NULL;
	oAttr = xml_FindAttibute(strAttrName, oNode);

	if (oAttr == NULL)
	{
		return FALSE;
	}
	else
	{
		vAttrVal = oAttr->nodeTypedValue;
		return TRUE;
	}
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, CComBSTR &strAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
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

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, long &nAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
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
		break;
	default:
		break;
	}
	

	return FALSE;
}

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, double &dAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
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

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, short &unAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
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

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, float &fAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
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

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, _variant_t &vValue)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
	if (oElement==NULL)
	{
		return FALSE;
	}
	vValue = oElement->getAttribute(strAttrName);

	return TRUE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, CComBSTR &strAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
	if (oElement==NULL)
	{
		return FALSE;
	}
	VARIANT Value;
	Value.vt = VT_BSTR;
	Value.bstrVal = strAttrVal;
	oElement->setAttribute(strAttrName,Value);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode,long &nAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
	if (oElement==NULL)
	{
		return FALSE;
	}
	VARIANT Value;
	Value.vt = VT_I4;
	Value.lVal = nAttrVal;
	oElement->setAttribute(strAttrName,Value);
	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, double &dAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
	if (oElement==NULL)
	{
		return FALSE;
	}
	VARIANT Value;
	Value.vt = VT_R8;
	Value.dblVal = dAttrVal;
	oElement->setAttribute(strAttrName,Value);
	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, short &unAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
	if (oElement==NULL)
	{
		return FALSE;
	}
	VARIANT Value;
	Value.vt = VT_I2;
	Value.iVal = unAttrVal;
	oElement->setAttribute(strAttrName,Value);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, float &fAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
	if (oElement==NULL)
	{
		return FALSE;
	}
	VARIANT Value;
	Value.vt = VT_R4;
	Value.fltVal = fAttrVal;
	oElement->setAttribute(strAttrName,Value);

	return FALSE;
}

BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, VARIANT &vValue)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oNode->QueryInterface(__uuidof(MSXML2::IXMLDOMElementPtr),(void**)&oElement);
	if (oElement==NULL)
	{
		return FALSE;
	}
	oElement->setAttribute(strAttrName,vValue);
	return TRUE;
}
