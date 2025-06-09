//////////////////////////////////////////////////////////////////////////
//XML2Interface.h
//XML组件的接口定义和扩展文件

#ifndef _XML2_INTERFACE_H__
#define _XML2_INTERFACE_H__

#import "msxml.dll"

BOOL xml_OpenFile(MSXML::IXMLDOMDocumentPtr &oDoc, const CString &strFile);

//MSXML GetAttibuteValues 声明
BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, CString &strAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, long &nAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, double &dAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, short &unAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, float &fAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, _variant_t &vValue);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMElementPtr &oElement, SYSTEMTIME &tmSys);

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMNodePtr &oNode, CString &strAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	return xml_GetAttibuteValue(strAttrName, oElement, strAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMNodePtr &oNode, long &nAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	return xml_GetAttibuteValue(strAttrName, oElement, nAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMNodePtr &oNode, double &dAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	return xml_GetAttibuteValue(strAttrName, oElement, dAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMNodePtr &oNode, short &unAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	return xml_GetAttibuteValue(strAttrName, oElement, unAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMNodePtr &oNode, float &fAttrVal)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	return xml_GetAttibuteValue(strAttrName, oElement, fAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMNodePtr &oNode, _variant_t &vValue)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	return xml_GetAttibuteValue(strAttrName, oElement, vValue);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, const MSXML::IXMLDOMNodePtr &oNode, SYSTEMTIME &tmSys)
{
	MSXML::IXMLDOMElementPtr oElement = oNode;
	return xml_GetAttibuteValue(strAttrName, oElement, tmSys);
}


//MSXML SetAttibuteValue 声明
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, const CString &strAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, long &nAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, double &dAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, short &unAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, float &fAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, VARIANT &vValue);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, const SYSTEMTIME &tmSys);


#endif
