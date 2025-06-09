#include "stdafx.h"
#include "XmlRWBase.h"
#include "../MemBuffer/BufferBase.h"
#include "../API/StringApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXmlRWElementBase::CXmlRWElementBase()
{
}

BOOL CXmlRWElementBase::AppendChild(CXmlRWElementBase &oRWElement)
{
	return FALSE;
}

CXmlRWElementBase* CXmlRWElementBase::GetCurChildElement()
{
	ASSERT(FALSE);
	return NULL;
}

void CXmlRWElementBase::FreeRWObj()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlRWNodeListBase::CXmlRWNodeListBase()
{
}

long CXmlRWNodeListBase::GetNodeNum()
{
	long nNum = 0;
	ASSERT(FALSE);
	return nNum;
}

CXmlRWNodeBase* CXmlRWNodeListBase::GetChild(const long &nChildIndex)
{
	return NULL;
}

void CXmlRWNodeListBase::FreeRWObj()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CXmlRWNodeBase::CXmlRWNodeBase()
{
}

CString CXmlRWNodeBase::GetNodeName()
{
	CString strNodeName;
	strNodeName = _T("");
	return strNodeName;
}

BOOL CXmlRWNodeBase::IsValid()
{
	return FALSE;
}

CXmlRWNodeBase* CXmlRWNodeBase::GetChildNode(const CString &strNodeName)
{
	ASSERT(FALSE);
	return NULL;
}

CXmlRWNodeBase* CXmlRWNodeBase::GetChildNode(const CString &strNodeName, const CString &strAttrID, const CString &strAttrValue)
{
	ASSERT(FALSE);
	return NULL;
}

CXmlRWNodeBase* CXmlRWNodeBase::GetChildNode(BSTR strNodeName)
{
	ASSERT(FALSE);
	return NULL;
}

CXmlRWNodeBase* CXmlRWNodeBase::GetChildNode(BSTR strNodeName, BSTR strAttrID, BSTR strAttrValue)
{
	ASSERT(FALSE);
	return NULL;
}

CXmlRWNodeListBase* CXmlRWNodeBase::GetChildNodes()
{
	ASSERT(FALSE);
	return NULL;
}

void CXmlRWNodeBase::operator=(CXmlRWNodeBase &oRWNode)
{
	ASSERT(FALSE);
}

void CXmlRWNodeBase::FreeRWObj()
{
}

BOOL CXmlRWNodeBase::AppendChild(CXmlRWElementBase &oRWElement)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_PutText(const CString &strText,const BSTR strAttrName){return FALSE;}
CString CXmlRWNodeBase::xml_GetText(const BSTR strAttrName) {return _T("");}

BOOL CXmlRWNodeBase::xml_GetCDATA(CString &strText,const BSTR strAttrName) {return FALSE;}
BOOL CXmlRWNodeBase::xml_SetCDATA(CXmlRWDocBase &oXMLDoc,const CString &strText,const BSTR strAttrName) {return FALSE;}

BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal)
{
	return FALSE;
}
BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, __int64 &n64AttrVal)
{
	return FALSE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNodeBase::xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	return FALSE;
}
#else
BOOL CXmlRWNodeBase::xml_GetAttibuteValue_Color(const BSTR strAttrName, unsigned long &crAttrVal)
{
	return FALSE;
}
#endif

BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal)
{
	return FALSE;
}

//yzj 2021-12-13
long CXmlRWNodeBase::xml_GetAttibuteType(const BSTR strAttrName)
{
	return -1;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	return FALSE;
}
#endif

BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName,__int64 &n64Val)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal)
{
	return FALSE;
}
BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal)
{
	return FALSE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys)
{
	return FALSE;
}
#endif

BOOL CXmlRWNodeBase::xml_GetElementText(const BSTR strAttrName, CString &strAttrVal)
{
	return FALSE;
}
BOOL CXmlRWNodeBase::xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetElementText(const BSTR strAttrName, long &nAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal)
{
	return FALSE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNodeBase::xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	return FALSE;
}
#else
BOOL CXmlRWNodeBase::xml_GetElement_Color(const BSTR strAttrName, DWORD &crAttrVal)
{
	return FALSE;
}
#endif

BOOL CXmlRWNodeBase::xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetElementText(const BSTR strAttrName, double &dAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetElementText(const BSTR strAttrName, short &unAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetElementText(const BSTR strAttrName, float &fAttrVal)
{
	return FALSE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNodeBase::xml_GetElementText(const BSTR strAttrName, _variant_t &vValue)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	return FALSE;
}
#endif

BOOL CXmlRWNodeBase::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal)
{
	return FALSE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNodeBase::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue)
{
	return FALSE;
}

BOOL CXmlRWNodeBase::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys)
{
	return FALSE;
}
#endif

BOOL CXmlRWNodeBase::xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal)
{
	BSTR bstrAttrName = strAttrName.AllocSysString();
	BOOL bRet = xml_SetElementText(bstrAttrName, pXMLDoc, strAttrVal);
	::SysFreeString(bstrAttrName);
	return bRet;
}

BOOL CXmlRWNodeBase::xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal)
{
	BSTR bstrAttrName = strAttrName.AllocSysString();
	BOOL bRet = xml_SetElementText(bstrAttrName, pXMLDoc, nAttrVal);
	::SysFreeString(bstrAttrName);
	return bRet;
}

BOOL CXmlRWNodeBase::xml_SetElementText_Color(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal)
{
	BSTR bstrAttrName = strAttrName.AllocSysString();
	BOOL bRet = xml_SetElementText_Color(bstrAttrName, pXMLDoc, crAttrVal);
	::SysFreeString(bstrAttrName);
	return bRet;
}

BOOL CXmlRWNodeBase::xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal)
{
	BSTR bstrAttrName = strAttrName.AllocSysString();
	BOOL bRet = xml_SetElementText(bstrAttrName, pXMLDoc, dAttrVal);
	::SysFreeString(bstrAttrName);
	return bRet;
}

BOOL CXmlRWNodeBase::xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal)
{
	BSTR bstrAttrName = strAttrName.AllocSysString();
	BOOL bRet = xml_SetElementText(bstrAttrName, pXMLDoc, unAttrVal);
	::SysFreeString(bstrAttrName);
	return bRet;
}

BOOL CXmlRWNodeBase::xml_SetElementText(const CString &strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal)
{
	BSTR bstrAttrName = strAttrName.AllocSysString();
	BOOL bRet = xml_SetElementText(bstrAttrName, pXMLDoc, fAttrVal);
	::SysFreeString(bstrAttrName);
	return bRet;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlRWDocBase::CXmlRWDocBase()
{
}

CXmlRWNodeBase* CXmlRWDocBase::GetDocNode()
{
	ASSERT(FALSE);
	return NULL;
}

CXmlRWElementBase* CXmlRWDocBase::CreateElement(BSTR bstElementKey,CXmlRWElementBase *oParent)
{
	ASSERT(FALSE);
	return NULL;
}

CXmlRWElementBase* CXmlRWDocBase::CreateElement(const CString &stElementKey,CXmlRWElementBase *oParent)
{
	BSTR bstElementKey = stElementKey.AllocSysString();
	CXmlRWElementBase *p = CreateElement(bstElementKey, oParent);
	SysFreeString(bstElementKey);
	return p;
}

BOOL CXmlRWDocBase::AppendChild(CXmlRWElementBase &oRWElement)
{
	ASSERT(FALSE);
	return FALSE;
}

BOOL CXmlRWDocBase::CreateInstruction(const CString &strVersion,const CString &strEnCode)
{
	ASSERT(FALSE);
	return FALSE;
}

BOOL CXmlRWDocBase::xml_OpenFile(const CString &strFile){return FALSE;}

BOOL CXmlRWDocBase::SaveXml(const CString &strFilePath)
{
	ASSERT(FALSE);
	return FALSE;
}

BOOL CXmlRWDocBase::AppendXml(const CString &strFilePath)
{
	ASSERT(FALSE);
	return FALSE;
}

void CXmlRWDocBase::FreeRWObj()
{
}

BOOL CXmlRWDocBase::GetXml(CString &strXML)
{
	ASSERT(FALSE);
	return FALSE;
}

BOOL CXmlRWDocBase::SetXml(BSTR strXML)
{
	ASSERT(FALSE);
	return FALSE;
}

BOOL CXmlRWDocBase::SetXml_ASCII(char *strXML,long nLen)
{
    ASSERT(FALSE);
    return FALSE;
}

BOOL CXmlRWDocBase::SetXml_UTF8(char *strXML, long nLen)
{
    ASSERT(FALSE);
    return FALSE;
}

long CXmlRWDocBase::GetXml_wchar(wchar_t **ppzszRetBuffer, long nOffset){return 0;}

//lijunqing 2022-3-11
long CXmlRWDocBase::GetXml_ASCII(char **ppszRetBuffer, long nOffset){return 0;}


long CXmlRWDocBase::GetXml(char **ppszRetBuffer, long nOffset)
{
	ASSERT(FALSE);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RW_CString_To_SYSTIME(const CString &strTmString,SYSTEMTIME &tmSys)
{
	CBufferBase oBuffer(strTmString);
	oBuffer.FormatBuffer();
	oBuffer.FormatBuffer('-');
	oBuffer.FormatBuffer('T');
	oBuffer.FormatBuffer('Z');
	// 	oBuffer.FormatBuffer('t');
	// 	oBuffer.FormatBuffer('z');
	oBuffer.FormatBuffer(':');
	oBuffer.FormatBuffer(' ');
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
		tmSys.wHour = atoi(pszTemp);
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
}
