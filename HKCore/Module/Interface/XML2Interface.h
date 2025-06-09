//////////////////////////////////////////////////////////////////////////
//XML2Interface.h
//XML组件的接口定义和扩展文件

#ifndef _XML2_INTERFACE_H__
#define _XML2_INTERFACE_H__

#import "msxml2.dll"
// 
// BOOL xml_OpenFile(MSXML2::IXMLDOMDocumentPtr &pDoc, const CString &strFile);
// 
// MSXML2::IXMLDOMNodePtr xml_FindAttibute(const BSTR &strAttrName, MSXML2::IXMLDOMNamedNodeMapPtr oAttrs);
// MSXML2::IXMLDOMNodePtr xml_FindAttibute(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode);
// 
// //MSXML2 GetAttibuteValues 声明
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWElementBase &oElement, CString &strAttrVal);
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWElementBase &oElement, wchar_t *strAttrVal);
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWElementBase &oElement, long &nAttrVal);
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWElementBase &oElement, DWORD &dwAttrVal);
// BOOL xml_GetAttibuteValue_Color(const BSTR &strAttrName, CXmlRWElementBase &oElement, COLORREF &crAttrVal);
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWElementBase &oElement, double &dAttrVal);
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWElementBase &oElement, short &unAttrVal);
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWElementBase &oElement, float &fAttrVal);
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWElementBase &oElement, _variant_t &vValue);
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWElementBase &oElement, SYSTEMTIME &tmSys);
// 
// inline BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetAttibuteValue(strAttrName, oElement, strAttrVal);
// }
// 
// inline BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWNodeBase &oNode, long &nAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetAttibuteValue(strAttrName, oElement, nAttrVal);
// }
// 
// inline BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWNodeBase &oNode, DWORD &nAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetAttibuteValue(strAttrName, oElement, nAttrVal);
// }
// 
// inline BOOL xml_GetAttibuteValue_Color(const BSTR &strAttrName, CXmlRWNodeBase &oNode, COLORREF &crAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetAttibuteValue_Color(strAttrName, oElement, crAttrVal);
// }
// 
// inline BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWNodeBase &oNode, double &dAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetAttibuteValue(strAttrName, oElement, dAttrVal);
// }
// 
// inline BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWNodeBase &oNode, short &unAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetAttibuteValue(strAttrName, oElement, unAttrVal);
// }
// 
// inline BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWNodeBase &oNode, float &fAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetAttibuteValue(strAttrName, oElement, fAttrVal);
// }
// 
// inline BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWNodeBase &oNode, _variant_t &vValue)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetAttibuteValue(strAttrName, oElement, vValue);
// }
// 
// inline BOOL xml_GetAttibuteValue(const BSTR &strAttrName, CXmlRWNodeBase &oNode, SYSTEMTIME &tmSys)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetAttibuteValue(strAttrName, oElement, tmSys);
// }
// 
// inline BOOL xml_GetCDATA(CXmlRWNodeBase &oNode, CString &strText)
// {
// 	MSXML2::IXMLDOMCDATASectionPtr oCDTA =  oNode->GetfirstChild();
// 
// 	if (oCDTA != NULL)
// 	{
// 		strText = (char*)oCDTA->Getxml();
// 		long nLen = strText.GetLength();
// 		strText = strText.Mid(9, nLen-12);
// 	}
// 	else
// 	{
// 		strText = (char*)oNode->Gettext();
// 		strText.Trim();
// 	}
// 	
// 	return TRUE;
// }
// 
// //MSXML2 SetAttibuteValue 声明
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, const CString &strAttrVal);
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, const wchar_t *strAttrVal);
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, long &nAttrVal);
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, DWORD &dwAttrVal);
// BOOL xml_SetAttributeValue_Color(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, COLORREF &crAttrVal);
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, double &dAttrVal);
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, short &unAttrVal);
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, float &fAttrVal);
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, VARIANT &vValue);
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, const SYSTEMTIME &tmSys);
// BOOL xml_SetCDATA(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, const CString &strText);
// 
// 
// 
// 
// //////////////////////////////////////////////////////////////////////////
// //
// BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWElementBase &oElement, CString &strAttrVal);
// BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWElementBase &oElement, long &nAttrVal);
// BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWElementBase &oElement, DWORD &dwAttrVal);
// BOOL xml_GetElementText_Color(const BSTR &strAttrName, CXmlRWElementBase &oElement, COLORREF &crAttrVal);
// BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWElementBase &oElement, double &dAttrVal);
// BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWElementBase &oElement, short &unAttrVal);
// BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWElementBase &oElement, float &fAttrVal);
// BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWElementBase &oElement, _variant_t &vValue);
// BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWElementBase &oElement, SYSTEMTIME &tmSys);
// 
// //ShaoLei 2018.09.21
// BOOL xml_GetElementText(CXmlRWElementBase &oElement, CString &strAttrVal);
// BOOL xml_GetElementText(CXmlRWElementBase &oElement, long &nAttrVal);
// BOOL xml_GetElementText(CXmlRWElementBase &oElement, DWORD &dwAttrVal);
// BOOL xml_GetElementText_Color(CXmlRWElementBase &oElement, COLORREF &crAttrVal);
// BOOL xml_GetElementText(CXmlRWElementBase &oElement, double &dAttrVal);
// BOOL xml_GetElementText(CXmlRWElementBase &oElement, short &unAttrVal);
// BOOL xml_GetElementText(CXmlRWElementBase &oElement, float &fAttrVal);
// BOOL xml_GetElementText(CXmlRWElementBase &oElement, _variant_t &vValue);
// BOOL xml_GetElementText(CXmlRWElementBase &oElement, SYSTEMTIME &tmSys);
// 
// 
// inline BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(strAttrName, oElement, strAttrVal);
// }
// 
// inline BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWNodeBase &oNode, long &nAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(strAttrName, oElement, nAttrVal);
// }
// 
// inline BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWNodeBase &oNode, DWORD &nAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(strAttrName, oElement, nAttrVal);
// }
// 
// inline BOOL xml_GetElement_Color(const BSTR &strAttrName, CXmlRWNodeBase &oNode, COLORREF &crAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElement_Color(strAttrName, oElement, crAttrVal);
// }
// 
// inline BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWNodeBase &oNode, double &dAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(strAttrName, oElement, dAttrVal);
// }
// 
// inline BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWNodeBase &oNode, short &unAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(strAttrName, oElement, unAttrVal);
// }
// 
// inline BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWNodeBase &oNode, float &fAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(strAttrName, oElement, fAttrVal);
// }
// 
// inline BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWNodeBase &oNode, _variant_t &vValue)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(strAttrName, oElement, vValue);
// }
// 
// inline BOOL xml_GetElementText(const BSTR &strAttrName, CXmlRWNodeBase &oNode, SYSTEMTIME &tmSys)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(strAttrName, oElement, tmSys);
// }
// 
// //ShaoLei 2018.09.21
// inline BOOL xml_GetElementText(CXmlRWNodeBase &oNode, CString &strAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(oElement, strAttrVal);
// }
// 
// inline BOOL xml_GetElementText(CXmlRWNodeBase &oNode, long &nAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(oElement, nAttrVal);
// }
// 
// inline BOOL xml_GetElementText(CXmlRWNodeBase &oNode, DWORD &nAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(oElement, nAttrVal);
// }
// 
// inline BOOL xml_GetElement_Color(CXmlRWNodeBase &oNode, COLORREF &crAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElement_Color(oElement, crAttrVal);
// }
// 
// inline BOOL xml_GetElementText(CXmlRWNodeBase &oNode, double &dAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(oElement, dAttrVal);
// }
// 
// inline BOOL xml_GetElementText(CXmlRWNodeBase &oNode, short &unAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(oElement, unAttrVal);
// }
// 
// inline BOOL xml_GetElementText(CXmlRWNodeBase &oNode, float &fAttrVal)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(oElement, fAttrVal);
// }
// 
// inline BOOL xml_GetElementText(CXmlRWNodeBase &oNode, _variant_t &vValue)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(oElement, vValue);
// }
// 
// inline BOOL xml_GetElementText(CXmlRWNodeBase &oNode, SYSTEMTIME &tmSys)
// {
// 	MSXML2::IXMLDOMElementPtr oElement = oNode;
// 	return xml_GetElementText(oElement, tmSys);
// } 
// 
// BOOL xml_SetElementText(const BSTR &strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, const CString &strAttrVal);
// BOOL xml_SetElementText(const BSTR &strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, long &nAttrVal);
// BOOL xml_SetElementText(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, DWORD &dwAttrVal);
// BOOL xml_SetElementText_Color(const BSTR &strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, COLORREF &crAttrVal);
// BOOL xml_SetElementText(const BSTR &strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParente, double &dAttrVal);
// BOOL xml_SetElementText(const BSTR &strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, short &unAttrVal);
// BOOL xml_SetElementText(const BSTR &strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, float &fAttrVal);
// BOOL xml_SetElementText(const BSTR &strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, VARIANT &vValue);
// BOOL xml_SetElementText(const BSTR &strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, const SYSTEMTIME &tmSys);
// 
// //ShaoLei 2018.09.21
// BOOL xml_SetElementText(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, const CString &strAttrVal);
// BOOL xml_SetElementText(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, long &nAttrVal);
// BOOL xml_SetElementText(MSXML2::IXMLDOMNodePtr oNode, DWORD &dwAttrVal);
// BOOL xml_SetElementText_Color(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, COLORREF &crAttrVal);
// BOOL xml_SetElementText(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParente, double &dAttrVal);
// BOOL xml_SetElementText(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, short &unAttrVal);
// BOOL xml_SetElementText(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, float &fAttrVal);
// BOOL xml_SetElementText(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, VARIANT &vValue);
// BOOL xml_SetElementText(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, const SYSTEMTIME &tmSys);

#endif
