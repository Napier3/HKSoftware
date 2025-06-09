#pragma once

#ifdef XML_USE_TINYXML

#include "../API/StringApi.h"
#include "XmlRWBase.h"
#include "tinyXml/tinyxml.h"
#include "../API/StringApi.h"

#ifndef _PSX_QT_LINUX_
#include<comdef.h>
#endif

class CXmlRWNodeList_Tiny :public CXmlRWNodeListBase
{
public:
	CXmlRWNodeList_Tiny();
	CXmlRWNodeList_Tiny(TiXmlElement *pXMLNodeList);
	virtual ~CXmlRWNodeList_Tiny()	{FreeRWObj();}

	virtual long GetXmlRWType(){return _TINY_XML_TYPE_;}
	virtual long GetNodeNum();
	virtual CXmlRWNodeBase* GetChild(const long &nChildIndex);
	virtual void operator=(TiXmlElement *pNodeList);
	virtual void FreeRWObj();

public:
	TiXmlElement *m_pTinyXmlNodeList;
private:
	CXmlRWNodeBase *m_pCurChildNode;
};


class CXmlRWNode_Tiny :public CXmlRWNodeBase
{
public:
	CXmlRWNode_Tiny();
	CXmlRWNode_Tiny(TiXmlElement *pXMLNode);
	virtual ~CXmlRWNode_Tiny()	{FreeRWObj();}

	virtual long GetXmlRWType(){return _TINY_XML_TYPE_;}
	virtual BOOL IsValid();
	virtual CString GetNodeName();
	virtual CXmlRWNodeBase* GetChildNode(const CString &strNodeName);
	virtual CXmlRWNodeBase* GetChildNode(BSTR strNodeName);
	virtual CXmlRWNodeListBase* GetChildNodes();
	virtual void FreeRWObj();
	virtual void operator=(CXmlRWNode_Tiny &oRWNode);
	virtual void operator=(TiXmlElement *pElement);

	virtual BOOL xml_PutText(const CString &strText);
	virtual CString xml_GetText();

	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal);
#ifndef _PSX_IDE_QT_
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue);
#endif
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys);
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

// 	//用于linux下转换wchar_t与char
// 	const char* WCHARtoCHAR(const wchar_t* pwstr);

public:
	TiXmlElement *m_pTinyXmlNode;
private:
	CXmlRWNodeList_Tiny m_oChildNodeList;
	CXmlRWNodeBase *m_pCurChildNode;
};

class CXmlRWElement_Tiny  :public CXmlRWElementBase
{
public:
	CXmlRWElement_Tiny();
	virtual ~CXmlRWElement_Tiny()	{FreeRWObj();}

	virtual long GetXmlRWType(){return _TINY_XML_TYPE_;}
	virtual BOOL IsEmpty(){return (m_pTinyXmlElement == NULL);}
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual CXmlRWElementBase* GetCurChildElement();
	virtual void operator=(TiXmlElement *pNodeList);
	virtual void FreeRWObj();

	virtual BOOL xml_PutText(const CString &strText);
	virtual CString xml_GetText();

	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal);
#ifndef _PSX_IDE_QT_
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue);
#endif
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys);
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

// 	//用于linux下转换wchar_t与char
// 	const char* WCHARtoCHAR(const wchar_t* pwstr);
public:
	TiXmlElement *m_pTinyXmlElement;

private:
	CXmlRWElementBase *m_pCurChildElement;
};


class CXmlRWDoc_Tiny:public CXmlRWDocBase
{
public:
	CXmlRWDoc_Tiny();
	virtual ~CXmlRWDoc_Tiny()	{FreeRWObj();}

	virtual BOOL IsValid(){return m_pTinyXmlDoc != NULL;}
	virtual long GetXmlRWType(){return _TINY_XML_TYPE_;}
	virtual CXmlRWNodeBase* GetDocNode();
	virtual CXmlRWElementBase* CreateElement(BSTR bstElementKey,CXmlRWElementBase *pParent);
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual BOOL CreateInstruction(const CString &strVersion,const CString &strEncode);
	virtual CXmlRWElementBase* GetDocElement(){return &m_oDocElement;}
	virtual BOOL SaveXml(const CString &strFilePath);
	virtual void FreeRWObj();
	virtual BOOL GetXml(CString &strXML);
	virtual long GetXml_ASCII(char **ppszRetBuffer, long nOffset);
	virtual BOOL SetXml(BSTR strXML);

// 	//用于linux下转换wchar_t与char
// 	const char* WCHARtoCHAR(const wchar_t* pwstr);

	static CXmlRWDocBase* CreateXmlRWDoc()
	{
		return new CXmlRWDoc_Tiny();
	}

	virtual BOOL xml_OpenFile(const CString &strFile)
	{
		return m_pTinyXmlDoc->LoadFile(strFile);//读取指定位置的XML源;
	}

public:
	TiXmlDocument *m_pTinyXmlDoc;
private:
	CXmlRWElement_Tiny m_oDocElement;
	CXmlRWNode_Tiny m_oDocNode;
};

#endif  // XML_USE_TINYXML
