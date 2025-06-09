#pragma once

#include "../API/StringApi.h"
#include "../API/GlobalApi.h"

#define _MS_XML_TYPE_        0
#define _TINY_XML_TYPE_      1
#define _PUGI_XML_TYPE_      2
#define _JSON_TYPE_			 3

#define TEXT_FORMAT_XML   "xml"
#define TEXT_FORMAT_JSON  "json"

inline char* text_GetFormatByIndex(long nIndex)
{
	if (nIndex == _JSON_TYPE_)
	{
		return TEXT_FORMAT_JSON;
	}

	return TEXT_FORMAT_XML;
}

inline long text_GetFormatIndex(const CString &strFormat)
{
	if (strFormat == TEXT_FORMAT_JSON)
	{
		return _JSON_TYPE_;
	}

	return _PUGI_XML_TYPE_;
}


class CXmlRWDocBase;
class CXmlRWNodeListBase;
class CXmlRWElementBase;


class CXmlRWNodeBase
{
protected:
	CXmlRWNodeBase();
public:
	virtual ~CXmlRWNodeBase()	{FreeRWObj();}

public:
	virtual long GetXmlRWType(){return -1;}
	virtual BOOL IsValid();
	virtual CString GetNodeName();
	virtual CXmlRWNodeBase* GetChildNode(const CString &strNodeName);
	virtual CXmlRWNodeBase* GetChildNode(const CString &strNodeName, const CString &strAttrID, const CString &strAttrValue);
	virtual CXmlRWNodeBase* GetChildNode(BSTR strNodeName);
	virtual CXmlRWNodeBase* GetChildNode(BSTR strNodeName, BSTR strAttrID, BSTR strAttrValue);
	virtual CXmlRWNodeListBase* GetChildNodes();
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual void FreeRWObj();
	virtual void operator=(CXmlRWNodeBase &oRWNode);

	virtual BOOL xml_PutText(const CString &strText,const BSTR strAttrName = NULL);
	virtual CString xml_GetText(const BSTR strAttrName = NULL);

	virtual BOOL xml_GetCDATA(CString &strText,const BSTR strAttrName = NULL);
	virtual BOOL xml_SetCDATA(CXmlRWDocBase &oXMLDoc,const CString &strText,const BSTR strAttrName = NULL);

	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal);	
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, __int64 &n64AttrVal);

#ifndef _PSX_IDE_QT_
	virtual BOOL xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal);
#else
	virtual BOOL xml_GetAttibuteValue_Color(const BSTR strAttrName, unsigned long &crAttrVal);
#endif

	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal); 
	//yzj 2021-12-13
	virtual long xml_GetAttibuteType(const BSTR strAttrName);
#ifndef _PSX_IDE_QT_
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue);
	virtual BOOL xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys);
#endif

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
	virtual BOOL xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys);
#endif

	virtual BOOL xml_GetElementText(const BSTR strAttrName, CString &strAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, long &nAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal);

#ifndef _PSX_IDE_QT_
	virtual BOOL xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal);
#else
	virtual BOOL xml_GetElement_Color(const BSTR strAttrName, DWORD &crAttrVal);
#endif

	virtual BOOL xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal);	
	virtual BOOL xml_GetElementText(const BSTR strAttrName, double &dAttrVal);	
	virtual BOOL xml_GetElementText(const BSTR strAttrName, short &unAttrVal);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, float &fAttrVal);

#ifndef _PSX_IDE_QT_
	virtual BOOL xml_GetElementText(const BSTR strAttrName, _variant_t &vValue);
	virtual BOOL xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys);
#endif

    //2022-12-14  lijunqing
    BOOL xml_GetElementText(const CString &strAttrName, CString &strAttrVal)
    {
        BSTR bstr = strAttrName.AllocSysString();
        BOOL bRet = xml_SetAttributeValue(bstr, strAttrVal);
        ::SysFreeString(bstr);
        return bRet;
    }
    BOOL xml_GetElementText(const CString &strAttrName, wchar_t *strAttrVal)
    {
        BSTR bstr = strAttrName.AllocSysString();
        BOOL bRet = xml_SetAttributeValue(bstr, strAttrVal);
        ::SysFreeString(bstr);
        return bRet;
    }
    BOOL xml_GetElementText(const CString &strAttrName, long &nAttrVal)
    {
        BSTR bstr = strAttrName.AllocSysString();
        BOOL bRet = xml_SetAttributeValue(bstr, nAttrVal);
        ::SysFreeString(bstr);
        return bRet;
    }
    BOOL xml_GetElementText(const CString &strAttrName, DWORD &dwAttrVal)
    {
        BSTR bstr = strAttrName.AllocSysString();
        BOOL bRet = xml_SetAttributeValue(bstr, dwAttrVal);
        ::SysFreeString(bstr);
        return bRet;
    }
    BOOL xml_GetElementText(const CString &strAttrName, double &dAttrVal)
    {
        BSTR bstr = strAttrName.AllocSysString();
        BOOL bRet = xml_SetAttributeValue(bstr, dAttrVal);
        ::SysFreeString(bstr);
        return bRet;
    }
    BOOL xml_GetElementText(const CString &strAttrName, short &unAttrVal)
    {
        BSTR bstr = strAttrName.AllocSysString();
        BOOL bRet = xml_SetAttributeValue(bstr, unAttrVal);
        ::SysFreeString(bstr);
        return bRet;
    }
    BOOL xml_GetElementText(const CString &strAttrName, float &fAttrVal)
    {
        BSTR bstr = strAttrName.AllocSysString();
        BOOL bRet = xml_SetAttributeValue(bstr, fAttrVal);
        ::SysFreeString(bstr);
        return bRet;
    }


	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal);	
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal);
	virtual BOOL xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal);	
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal);
#ifndef _PSX_IDE_QT_
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue);
	virtual BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys);
#endif

	virtual BOOL xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal);	
	virtual BOOL xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal);
	virtual BOOL xml_SetElementText_Color(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal);	
	virtual BOOL xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal);
	virtual BOOL xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal);
	virtual BOOL xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal);


public:
	virtual BOOL Puttext(const CString &strText,const BSTR strAttrName = NULL)	{	return xml_PutText(strText,strAttrName);	}
	virtual BOOL put_text(const CString &strText,const BSTR strAttrName = NULL)	{	return xml_PutText(strText,strAttrName);	}
	virtual CString Gettext(const BSTR strAttrName = NULL)	{	return xml_GetText(strAttrName);	}

};


class CXmlRWElementBase : public CXmlRWNodeBase
{
protected:
	CXmlRWElementBase();
public:
	virtual ~CXmlRWElementBase()	{FreeRWObj();}

public:
	virtual long GetXmlRWType(){return -1;}
	virtual CXmlRWElementBase* GetCurChildElement();
	virtual BOOL IsEmpty(){return (NULL);}
	virtual void FreeRWObj();
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
};

class CXmlRWNodeListBase :public CXmlRWElementBase
{
protected:
	CXmlRWNodeListBase();

public:
	virtual ~CXmlRWNodeListBase()	{FreeRWObj();}

public:
	virtual long GetXmlRWType(){return -1;}
	virtual long GetNodeNum();
	virtual CXmlRWNodeBase* GetChild(const long &nChildIndex);
	virtual void FreeRWObj();
};


class CXmlRWDocBase
{
protected:
	CXmlRWDocBase();
public:
	virtual ~CXmlRWDocBase()	{FreeRWObj();}

	virtual BOOL IsValid() {return FALSE;}

public:
	virtual long GetXmlRWType(){return -1;}
	virtual CXmlRWNodeBase* GetDocNode();
	virtual CXmlRWNodeBase* GetFirstRootNode()	{	return NULL;	}
	virtual CXmlRWElementBase* CreateElement(BSTR bstElementKey,CXmlRWElementBase *pParent);
	virtual CXmlRWElementBase* CreateElement(const CString &stElementKey,CXmlRWElementBase *pParent);  //2022-12-13  lijunqing
	virtual BOOL AppendChild(CXmlRWElementBase &oRWElement);
	virtual BOOL CreateInstruction(const CString &strVersion,const CString &strEncode);
	virtual CXmlRWElementBase* GetDocElement(){ASSERT(FALSE);return NULL;}
	virtual BOOL xml_OpenFile(const CString &strFile);
	virtual BOOL SaveXml(const CString &strFilePath);
	virtual BOOL AppendXml(const CString &strFilePath);
	virtual void FreeRWObj();

	virtual BOOL GetXml(CString &strXML);
	virtual long GetXml(char **ppszRetBuffer, long nOffset);
	virtual BOOL SetXml(BSTR strXML);
    virtual BOOL SetXml_ASCII(char *strXML,long nLen);
	virtual BOOL SetXml_UTF8(char *strXML, long nLen);

	//xxy 20200516
	virtual long GetXml_wchar(wchar_t **ppzszRetBuffer, long nOffset);

	//lijunqing 2022-3-11
	virtual long GetXml_ASCII(char **ppszRetBuffer, long nOffset);
};

void RW_CString_To_SYSTIME(const CString &strTmString,SYSTEMTIME &tmSys);

CXmlRWDocBase* xml_CreateXmlRWDoc(long nType);
CXmlRWDocBase* xml_CreateXmlRWDoc(const CString &strFile, long nType);

