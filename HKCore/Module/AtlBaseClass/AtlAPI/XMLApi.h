// XMLApi.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XMLAPI_H__)
#define _XMLAPI_H__

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif
#import "../../Module/xml/msxml.dll"
#import "../../Module/xml/msxml2.dll"

//BSTR是指针,在xml_FindAttibute()函数中使用了ComBSTR
MSXML::IXMLDOMNodePtr xml_FindAttibute(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs);
MSXML::IXMLDOMNodePtr xml_FindAttibute(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode);

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, CComBSTR &strAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs, CComBSTR &strAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, long &nAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs, long &nAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, double &dAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs, double &dAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs, short &unAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, short &unAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, float &fAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNamedNodeMapPtr oAttrs, float &fAttrVal);

BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML::IXMLDOMNodePtr oNode, _bstr_t &strAttrVal);

//MSXML2 GetAttibuteValues 声明
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, CComBSTR &strAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, long &nAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, double &dAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, short &unAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, float &fAttrVal);
BOOL xml_GetAttibuteValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, _variant_t &vValue);


//MSXML2 SetAttibuteValue 声明
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, CComBSTR &strAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, long &nAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, double &dAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, short &unAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, float &fAttrVal);
BOOL xml_SetAttributeValue(const BSTR strAttrName, MSXML2::IXMLDOMNodePtr oNode, VARIANT &vValue);

#endif // !defined(_XMLAPI_H__)
