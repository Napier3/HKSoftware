#pragma once

#ifdef XML_USE_MSXML

#include "..\API\StringApi.h"
#include "XmlRWBase.h"
#import "msxml2.dll"

class CXmlRWNodeList_MS :public CXmlRWNodeListBase
{
public:
	CXmlRWNodeList_MS();
	CXmlRWNodeList_MS(MSXML2::IXMLDOMNodeListPtr &pXMLNodeList);
	virtual ~CXmlRWNodeList_MS()	{FreeRWObj();}

	virtual long GetXmlRWType(){return _MS_XML_TYPE_;}
	virtual long GetNodeNum();
	virtual CXmlRWNodeBase* GetChild(const long &nChildIndex);
	virtual void operator=(MSXML2::IXMLDOMNodeListPtr &pNodeList);
	virtual void FreeRWObj();

public:
	MSXML2::IXMLDOMNodeListPtr m_oMSXMLNodeList;

private:
	CXmlRWNodeBase *m_pCurChildNode;
};

class CXmlRWNode_MS :public CXmlRWNodeBase
{
public:
	CXmlRWNode_MS();
	CXmlRWNode_MS(const MSXML2::IXMLDOMNodePtr &pXMLNode);
	virtual ~CXmlRWNode_MS()	{FreeRWObj();}

	virtual long GetXmlRWType(){return _MS_XML_TYPE_;}
	virtual BOOL IsValid();
	virtual CString GetNodeName();
	virtual CXmlRWNodeBase* GetChildNode(const CString &strNodeName);
	virtual CXmlRWNodeBase* GetChildNode(BSTR strNodeName);
	virtual CXmlRWNodeListBase* GetChildNodes();
	virtual void FreeRWObj();

	virtual BOOL xml_PutText(const CString &strText);
	virtual CString xml_GetText();

	virtual BOOL xml_GetCDATA(CString &strText);
	virtual BOOL xml_SetCDATA(CXmlRWDocBase &oXMLDoc,const CString &strText);

	virtual void operator=(CXmlRWNode_MS &oRWNode);
	virtual void operator=(MSXML2::IXMLDOMNodePtr &pNode);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, CString &strAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, float &fAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, _variant_t &vValue);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal);
	virtual BOOL xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys);

public:
	MSXML2::IXMLDOMNodePtr m_oMSXMLNode;

private:
	CXmlRWNodeList_MS m_oChildNodeList;
	CXmlRWNodeBase *m_pCurChildNode;
};



class CXmlRWElement_MS  :public CXmlRWElementBase
{
public:
	CXmlRWElement_MS();
	virtual ~CXmlRWElement_MS()	{FreeRWObj();}

public:
	virtual long GetXmlRWType(){return _MS_XML_TYPE_;}
	virtual BOOL IsEmpty(){return (m_oMSXMLElement == NULL);}
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual CXmlRWElementBase* GetCurChildElement();
	virtual void operator=(MSXML2::IXMLDOMNodeListPtr &pNodeList);
	virtual void operator=(MSXML2::IXMLDOMElementPtr &pNodeList);
	virtual void operator=(MSXML2::IXMLDOMNodePtr &pNode);
	virtual void FreeRWObj();

	virtual BOOL xml_PutText(const CString &strText);
	virtual CString xml_GetText();

	virtual BOOL xml_GetCDATA(CString &strText);
	virtual BOOL xml_SetCDATA(CXmlRWDocBase &oXMLDoc,const CString &strText);

	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, CString &strAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, float &fAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, _variant_t &vValue);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal);
	virtual BOOL xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys);

public:
	MSXML2::IXMLDOMElementPtr m_oMSXMLElement;

private:
	CXmlRWElementBase *m_pCurChildElement;
};


class CXmlRWDoc_MS:public CXmlRWDocBase
{
public:
	CXmlRWDoc_MS();
	virtual ~CXmlRWDoc_MS()	{FreeRWObj();}

	virtual BOOL IsValid(){return (m_oMSXMLDoc != NULL);}

	static CXmlRWDocBase* CreateXmlRWDoc()
	{
		return new CXmlRWDoc_MS();
	}

	virtual long GetXmlRWType(){return _MS_XML_TYPE_;}
	virtual CXmlRWNodeBase* GetDocNode();
	virtual CXmlRWNodeBase* GetFirstRootNode();
	virtual CXmlRWElementBase* CreateElement(BSTR bstElementKey,CXmlRWElementBase *pParent);
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual BOOL CreateInstruction(const CString &strVersion,const CString &strEncode);
	virtual CXmlRWElementBase* GetDocElement(){return &m_oDocElement;}
	virtual BOOL xml_OpenFile(const CString &strFile);
	void operator=(MSXML2::IXMLDOMDocumentPtr &pDoc);
	virtual BOOL SaveXml(const CString &strFilePath);
	virtual void FreeRWObj();
	virtual BOOL GetXml(CString &strXML);
	virtual BOOL SetXml(BSTR strXML);

public:
	MSXML2::IXMLDOMDocumentPtr m_oMSXMLDoc;

private:
	CXmlRWElement_MS m_oDocElement;
	CXmlRWNode_MS m_oDocNode;
	CXmlRWNode_MS m_oDocFirstRootNode;
};

#endif  //XML_USE_MSXML
