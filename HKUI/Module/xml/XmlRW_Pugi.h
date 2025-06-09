#pragma once

#ifdef XML_USE_PUGIXML

#include "../API/StringApi.h"
#include "../BaseClass/TLinkList.h"
#include "PugiXML/pugixml.hpp"
#include "XmlRWBase.h"
#include<iostream>
#include<locale>
#include <fstream>
#include<string>

class CXmlRWNode_Pugi;
class CXmlRWNodeList_Pugi;

typedef CTLinkList<CXmlRWNode_Pugi>  CPugiXml_NodeList;


class CXmlRWNode_Pugi :public CXmlRWNodeListBase
{
public:
	CXmlRWNode_Pugi();
	CXmlRWNode_Pugi(pugi::xml_node &oXMLNode);
	virtual ~CXmlRWNode_Pugi()	{FreeRWObj();}

	virtual long GetXmlRWType(){return _PUGI_XML_TYPE_;}
	virtual BOOL IsValid();
	virtual CString GetNodeName();
	virtual CXmlRWNodeBase* GetChildNode(const CString &strNodeName);
	CXmlRWNodeBase* GetChildNode(const CString &strNodeName, const CString &strAttrID, const CString &strAttrValue);
	virtual CXmlRWNodeBase* GetChildNode(BSTR strNodeName);
	virtual CXmlRWNodeBase* GetChildNode(BSTR strNodeName, BSTR strAttrID, BSTR strAttrValue);
	virtual CXmlRWNodeListBase* GetChildNodes();
	virtual void FreeRWObj();

    virtual void operator=(CXmlRWNode_Pugi &oRWNode);
    virtual void operator=(const pugi::xml_node &oXMLNode);

	virtual BOOL xml_PutText(const CString &strText,const BSTR strAttrName = NULL);
	virtual CString xml_GetText(const BSTR strAttrName = NULL);

	virtual BOOL xml_GetCDATA(CString &strText,const BSTR strAttrName = NULL);
	virtual BOOL xml_SetCDATA(CXmlRWDocBase &oXMLDoc,const CString &strText,const BSTR strAttrName = NULL);


	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, __int64 &n64AttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal);
#ifndef _PSX_IDE_QT_
    virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue);
#endif
    virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,__int64 &n64Val);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal);
#ifndef _PSX_IDE_QT_
    virtual BOOL xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue);
#endif
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
#ifndef _PSX_IDE_QT_
    virtual BOOL xml_GetElementText(const BSTR strAttrName, _variant_t &vValue);
#endif
    virtual BOOL xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal);
	virtual BOOL xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal);
#ifndef _PSX_IDE_QT_
    virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue);
#endif
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys);

public:
	pugi::xml_node m_oPugiXmlNode;
protected:
	CXmlRWNodeBase* FindLocalChildNode(pugi::xml_node &oCurChildNode);
//	CXmlRWElementBase *m_pCurChildNode;
	CPugiXml_NodeList m_oPugiList;
private:
//	CXmlRWNodeListBase *m_pChildNodeList;
};

class CXmlRWElement_Pugi  :public CXmlRWNode_Pugi
{
public:
	CXmlRWElement_Pugi();
	virtual ~CXmlRWElement_Pugi()	{FreeRWObj();}

	virtual long GetXmlRWType(){return _PUGI_XML_TYPE_;}
	virtual BOOL IsEmpty(){return (m_oPugiXmlNode.empty());}
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual CXmlRWElementBase* GetCurChildElement();
	virtual void operator=(const pugi::xml_node &oNodeList);

    virtual void FreeRWObj();
};

class CXmlRWNodeList_Pugi :public CXmlRWElement_Pugi
{
public:
	CXmlRWNodeList_Pugi();
	CXmlRWNodeList_Pugi(pugi::xml_node &oXMLNodeList);
	virtual ~CXmlRWNodeList_Pugi()	{FreeRWObj();}

	virtual long GetXmlRWType(){return _PUGI_XML_TYPE_;}
	virtual long GetNodeNum();
	virtual CXmlRWNodeBase* GetChild(const long &nChildIndex);
	void operator=(pugi::xml_node &oNodeList);
	virtual void FreeRWObj();

public:
//	pugi::xml_node m_oPugiXmlNodeList;

private:
//	CXmlRWNodeBase *m_pCurChildNode;
};




class CXmlRWDoc_Pugi:public CXmlRWDocBase
{
public:
	CXmlRWDoc_Pugi();
	virtual ~CXmlRWDoc_Pugi()
	{
		FreeRWObj();
	}

	virtual BOOL IsValid(){return m_oPugiXmlDoc != NULL;}

	virtual long GetXmlRWType(){return _PUGI_XML_TYPE_;}
	virtual CXmlRWNodeBase* GetDocNode();
	virtual CXmlRWNodeBase* GetFirstRootNode();
	virtual CXmlRWElementBase* CreateElement(BSTR bstElementKey,CXmlRWElementBase *pParent);
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual BOOL CreateInstruction(const CString &strVersion,const CString &strEncode);
	virtual CXmlRWElementBase* GetDocElement();//{return &m_oDocElement;}

	static CXmlRWDocBase* CreateXmlRWDoc()
	{
		return new CXmlRWDoc_Pugi();
	}	
	
    virtual BOOL xml_OpenFile(const CString &strFile);
	virtual BOOL SaveXml(const CString &strFilePath);
	virtual BOOL AppendXml(const CString &strFilePath);
	virtual void FreeRWObj();
	virtual BOOL GetXml(CString &strXML);
	virtual long GetXml_ASCII(char **ppszRetBuffer, long nOffset);	//zhouhj 20220402 增加对ascii的转换
	virtual long GetXml(char **ppszRetBuffer, long nOffset);
	virtual BOOL SetXml(BSTR strXML);
    virtual BOOL SetXml_ASCII(char *strXML,long nLen);
	virtual BOOL SetXml_UTF8(char *strXML, long nLen);

	//xxy 20200516
	virtual long GetXml_wchar(wchar_t **ppzszRetBuffer, long nOffset);

public:
	pugi::xml_document m_oPugiXmlDoc;

private:
	CXmlRWNodeList_Pugi m_oDocElement;
	CXmlRWNodeList_Pugi m_oDocFirstRootNode;
};

#endif XML_USE_PUGIXML
