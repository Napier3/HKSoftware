#pragma once

#ifdef JSON_USE_

#include "../API/StringApi.h"
#include "../BaseClass/TLinkList.h"
#include "JSON/CJSON.h"
#include "XmlRWBase.h"
#include<iostream>
#include<locale>
#include <fstream>
#include<string>

class CJsonNode;
class CXmlRWNodeList_Json;

typedef CTLinkList<CJsonNode>  CJson_NodeList;

extern BOOL g_bMergeSameToArray;


class CJsonNode :public CXmlRWNodeListBase
{
public:
	CJsonNode();
	CJsonNode(CJSON *pNode);
	virtual ~CJsonNode()	{}

	virtual long GetXmlRWType(){return _JSON_TYPE_;}
	virtual BOOL IsValid();
	virtual CString GetNodeName();
	virtual CXmlRWNodeBase* GetChildNode(const CString &strNodeName);
	CXmlRWNodeBase* GetChildNode(const CString &strNodeName, const CString &strAttrID, const CString &strAttrValue);
	virtual CXmlRWNodeBase* GetChildNode(BSTR strNodeName);
	virtual CXmlRWNodeBase* GetChildNode(BSTR strNodeName, BSTR strAttrID, BSTR strAttrValue);
	virtual CXmlRWNodeListBase* GetChildNodes();
	virtual void FreeRWObj();

    virtual void operator=(CJsonNode &oRWNode);
    virtual void operator=(CJSON *pNode);

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

	//2021-12-13 yzj 获取解析中数据的类型,用于判断json传入的值的type和定义类内变量的type是否一致
	virtual long xml_GetAttibuteType(const BSTR strAttrName);
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

	BOOL GetValue_String(CJSON *pAttrItem,CString &strValue);//zhouhj 20220313 增加用于根据实际数据类型获取对应值
	BOOL GetValue_Long(CJSON *pAttrItem,long &nValue);
	BOOL GetValue_Double(CJSON *pAttrItem,double &dValue);
	BOOL GetValue_n64(CJSON *pAttrItem,__int64 &n64Value);

public:
	CJSON *m_pJsonNode;
	CJSON *m_pJsonRootNode;

protected:
	CXmlRWNodeBase* FindLocalChildNode(CJSON *pNode);
	CJson_NodeList m_oJsonList;
};

class CXmlRWElement_Json : public CJsonNode
{
public:
	CXmlRWElement_Json();
	virtual ~CXmlRWElement_Json()	{}

	virtual long GetXmlRWType(){return _JSON_TYPE_;}
	virtual BOOL IsEmpty(){return (m_pJsonNode == NULL);}
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual CXmlRWElementBase* GetCurChildElement();
	virtual void operator=(CJSON *pNode);

    virtual void FreeRWObj();
};

class CXmlRWNodeList_Json :public CXmlRWElement_Json
{
public:
	CXmlRWNodeList_Json();
	CXmlRWNodeList_Json(CJSON *pNodeList);
	virtual ~CXmlRWNodeList_Json()	{}

	virtual long GetXmlRWType(){return _JSON_TYPE_;}
	virtual long GetNodeNum();
	virtual CXmlRWNodeBase* GetChild(const long &nChildIndex);
	void operator=(CJSON *pNodeList);
//	virtual void FreeRWObj();
};

///////////////////////////////////////////////////////////////////


class CJsonRWDoc:public CXmlRWDocBase
{
public:
	CJsonRWDoc();
	virtual ~CJsonRWDoc();

	virtual BOOL IsValid(){return m_pJsonDoc != NULL;}

	virtual long GetXmlRWType(){return _JSON_TYPE_;}
	virtual CXmlRWNodeBase* GetDocNode();
	virtual CXmlRWNodeBase* GetFirstRootNode();
	virtual CXmlRWElementBase* CreateElement(BSTR bstElementKey,CXmlRWElementBase *pParent);
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual BOOL CreateInstruction(const CString &strVersion,const CString &strEncode);
	virtual CXmlRWElementBase* GetDocElement();//{return &m_oDocElement;}

	static CXmlRWDocBase* CreateXmlRWDoc()
	{
		return new CJsonRWDoc();
	}	
	
    virtual BOOL xml_OpenFile(const CString &strFile);
	virtual BOOL SaveXml(const CString &strFilePath);
	virtual void FreeRWObj();
	virtual BOOL GetXml(CString &strXML);
	virtual long GetXml(char **ppszRetBuffer, long nOffset, bool bUtf8=true);
	virtual long GetXml_ASCII(char **ppszRetBuffer, long nOffset);	//lijunqing 2022-3-11

	virtual BOOL SetXml(BSTR strXML);
    virtual BOOL SetXml_ASCII(char *strXML,long nLen);
	virtual BOOL SetXml_UTF8(char *strXML, long nLen);


public:
	CJSON *m_pJsonDoc;

private:
	CXmlRWNodeList_Json m_oDocElement;
	CXmlRWNodeList_Json m_oDocFirstRootNode;
};

//20210630 xxy CJSON对象编码为gbk,生成字节流为UTF-8
extern CJSON *CJSON_Parse_UTF8(const char *value);
extern char  *CJSON_Print_UTF8(CJSON *item, long nOffset=0);

#endif //JSON_USE_
