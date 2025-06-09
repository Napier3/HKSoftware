#include "stdafx.h"
#include "XmlRW_Pugi.h"

#include"../API/StringConvert/String_Utf8_To_Gbk.h"
#ifndef _PSX_QT_LINUX_
#include "oleauto.h"
#endif

#ifdef XML_USE_PUGIXML


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlRWNodeList_Pugi::CXmlRWNodeList_Pugi()
{
    m_oPugiXmlNode = pugi::xml_node();
//	m_pCurChildNode = NULL;
}

CXmlRWNodeList_Pugi::CXmlRWNodeList_Pugi(pugi::xml_node &oXMLNodeList)
{
    m_oPugiXmlNode = oXMLNodeList;
}

long CXmlRWNodeList_Pugi::GetNodeNum()
{
    long nNum = 0;

    nNum = m_oPugiXmlNode.child_number();

    return nNum;
}

CXmlRWNodeBase* CXmlRWNodeList_Pugi::GetChild(const long &nChildIndex)
{
    pugi::xml_node oCurChild = m_oPugiXmlNode.child(nChildIndex);
    return FindLocalChildNode(oCurChild);
}

void CXmlRWNodeList_Pugi::operator=(pugi::xml_node &oNodeList)
{
    FreeRWObj();
    m_oPugiXmlNode = oNodeList;
}

void CXmlRWNodeList_Pugi::FreeRWObj()
{
    m_oPugiXmlNode = pugi::xml_node();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXmlRWNode_Pugi::CXmlRWNode_Pugi()
{
    m_oPugiXmlNode = pugi::xml_node();
}

CXmlRWNode_Pugi::CXmlRWNode_Pugi(pugi::xml_node &oXMLNode)
{
    m_oPugiXmlNode = oXMLNode;
}

CString CXmlRWNode_Pugi::GetNodeName()
{
    CString strNodeName;
    strNodeName = m_oPugiXmlNode.name();
    return strNodeName;
}

BOOL CXmlRWNode_Pugi::IsValid()
{
    return (!m_oPugiXmlNode.empty());
}

CXmlRWNodeBase* CXmlRWNode_Pugi::FindLocalChildNode(pugi::xml_node &oCurChildNode)
{
    if (oCurChildNode.empty())
    {
        return NULL;
    }

    CXmlRWNode_Pugi *pPugiNode = NULL;
    CXmlRWNode_Pugi *pFind = NULL;
    POS pos = m_oPugiList.GetHeadPosition();

    while(pos)
    {
        pPugiNode = m_oPugiList.GetNext(pos);

        if (pPugiNode->m_oPugiXmlNode == oCurChildNode)
        {
            pFind = pPugiNode;
        }
    }

    if (pFind == NULL)
    {
        pFind = new CXmlRWNodeList_Pugi;
        m_oPugiList.AddTail(pFind);
        *pFind = oCurChildNode;
    }

    return pFind;
}

CXmlRWNodeBase* CXmlRWNode_Pugi::GetChildNode(const CString &strNodeName)
{
    pugi::xml_node oCurChildNode;
    long nLen = strNodeName.GetLength();

#ifdef _UNICODE

  #ifdef PUGIXML_WCHAR_MODE
    oCurChildNode = m_oPugiXmlNode.child(strNodeName);
  #else
    char *pszNodeName = NULL;
    str_wchar_to_char(&pszNodeName, strNodeName, nLen);
    oCurChildNode = m_oPugiXmlNode.child(pszNodeName);
    delete pszNodeName;
  #endif

#else

  #ifdef PUGIXML_WCHAR_MODE
    wchar_t *pwcsNodeName = strNodeName.AllocSysString();
    oCurChildNode = m_oPugiXmlNode.child(pwcsNodeName);

	#ifdef _PSX_IDE_QT_
	   delete pwcsNodeName;
	#else
	  ::SysFreeString(pwcsNodeName);
	#endif
  #else
    oCurChildNode = m_oPugiXmlNode.child(strNodeName.GetString());
  #endif

#endif

    return FindLocalChildNode(oCurChildNode);
}

CXmlRWNodeBase* CXmlRWNode_Pugi::GetChildNode(const CString &strNodeName, const CString &strAttrID, const CString &strAttrValue)
{
    pugi::xml_node oCurChildNode;
    long nLen = strNodeName.GetLength();
    long nLenID = strAttrID.GetLength();
    long nLenVal = strAttrValue.GetLength();

#ifdef _UNICODE

	#ifdef PUGIXML_WCHAR_MODE
		oCurChildNode = m_oPugiXmlNode.child(strNodeName, strAttrID, strAttrValue);
	#else
		char *pszNodeName = NULL, *pszAttrID=NULL, *pszAtrrValue=NULL;
		str_wchar_to_char(&pszNodeName, strNodeName, nLen);
		str_wchar_to_char(&pszAttrID, strAttrID, nLenID);
		str_wchar_to_char(&pszAtrrValue, strAttrValue, nLenVal);
		oCurChildNode = m_oPugiXmlNode.child(pszNodeName, pszAttrID, pszAtrrValue);
		delete pszNodeName;
		delete pszAttrID;
		delete pszAtrrValue;
	#endif
#else
	#ifdef PUGIXML_WCHAR_MODE
	    wchar_t *pwcsNodeName = strNodeName.AllocSysString();
	    wchar_t *pwcsAttrID = strAttrID.AllocSysString();
		wchar_t *pwcsAttrValue = strAttrValue.AllocSysString();
		oCurChildNode = m_oPugiXmlNode.child(pwcsNodeName, pwcsAttrID, pwcsAttrValue);

		#ifdef _PSX_IDE_QT_
			delete pwcsNodeName;
			delete pwcsAttrID;
			delete pwcsAttrValue;
		#else
			::SysFreeString(pwcsNodeName);
			::SysFreeString(pwcsAttrID);
			::SysFreeString(pwcsAttrValue);
		#endif

	#else
	   oCurChildNode = m_oPugiXmlNode.child(strNodeName.GetString(), strAttrID.GetString(), strAttrValue.GetString());
	#endif
#endif

    return FindLocalChildNode(oCurChildNode);
}

CXmlRWNodeBase* CXmlRWNode_Pugi::GetChildNode(BSTR strNodeName)
{
    pugi::xml_node oCurChildNode;
    oCurChildNode = m_oPugiXmlNode.child(strNodeName);
    return FindLocalChildNode(oCurChildNode);
}

CXmlRWNodeBase* CXmlRWNode_Pugi::GetChildNode(BSTR strNodeName, BSTR strAttrID, BSTR strAttrValue)
{
    pugi::xml_node oCurChildNode;
    oCurChildNode = m_oPugiXmlNode.child(strNodeName, strAttrID, strAttrValue);
    return FindLocalChildNode(oCurChildNode);
}

CXmlRWNodeListBase* CXmlRWNode_Pugi::GetChildNodes()
{
    return (CXmlRWNodeListBase*)FindLocalChildNode(m_oPugiXmlNode);
}


void CXmlRWNode_Pugi::operator=(CXmlRWNode_Pugi &oRWNode)
{
    FreeRWObj();
    m_oPugiXmlNode = oRWNode.m_oPugiXmlNode;
}

void CXmlRWNode_Pugi::operator=(const pugi::xml_node &oXMLNode)
{
    FreeRWObj();
    m_oPugiXmlNode = oXMLNode;
}

void CXmlRWNode_Pugi::FreeRWObj()
{
    m_oPugiXmlNode = pugi::xml_node();
}

BOOL CXmlRWNode_Pugi::xml_PutText(const CString &strText,const BSTR strAttrName)
{
    if (m_oPugiXmlNode == NULL)
    {
        return FALSE;
    }

	wchar_t *pstr = strText.AllocSysString();
    m_oPugiXmlNode.text().set(pstr);
#ifdef _PSX_IDE_QT_
    delete pstr;
#else
    ::SysFreeString(pstr);
#endif
    return TRUE;
}

CString CXmlRWNode_Pugi::xml_GetText(const BSTR strAttrName)
{
    CString strText;
    strText = "";

    if (m_oPugiXmlNode != NULL)
    {
        strText = m_oPugiXmlNode.child_value();
    }

    return strText;
}

BOOL CXmlRWNode_Pugi::xml_GetCDATA(CString &strText,const BSTR strAttrName)
{
    if (m_oPugiXmlNode != NULL)
    {
        strText = m_oPugiXmlNode.child_value();
    }

    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetCDATA(CXmlRWDocBase &oXMLDoc,const CString &strText,const BSTR strAttrName)
{
    if (m_oPugiXmlNode == NULL)
    {
        return FALSE;
    }

#ifndef PUGIXML_WCHAR_MODE
	const char* pstr = strText.GetString();
	m_oPugiXmlNode.append_child(pugi::node_cdata).set_value(pstr);
#else
	wchar_t *pstr = strText.AllocSysString();
    m_oPugiXmlNode.append_child(pugi::node_cdata).set_value(pstr);
//	m_oPugiXmlNode.text().set(strText.AllocSysString());
//	::SysFreeString(pstr);
#ifdef _PSX_IDE_QT_
    delete pstr;
#else
    ::SysFreeString(pstr);
#endif
#endif
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        strAttrVal = attrTmp.value();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        CString strValue;
        strValue = attrTmp.value();
        strAttrVal = strValue.AllocSysString();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        nAttrVal = attrTmp.as_int();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, __int64 &n64AttrVal)
{
	ASSERT(m_oPugiXmlNode!=NULL);
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

	if (attrTmp != NULL)
	{
#ifdef PUGIXML_HAS_LONG_LONG
		n64AttrVal = attrTmp.as_llong();
#endif
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        dwAttrVal = attrTmp.as_uint();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        crAttrVal = attrTmp.as_int();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        dAttrVal = attrTmp.as_double();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        unAttrVal = attrTmp.as_int();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        fAttrVal = attrTmp.as_double();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#ifndef _PSX_IDE_QT_

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        CString strValue;
        strValue = attrTmp.value();
        vValue = strValue;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#endif

BOOL CXmlRWNode_Pugi::xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
    ASSERT(m_oPugiXmlNode!=NULL);
    pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);

    if (attrTmp != NULL)
    {
        CString strTmpValue;
        strTmpValue = attrTmp.value();
        RW_CString_To_SYSTIME(strTmpValue,tmSys);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName,__int64 &n64Val)
{
#ifdef PUGIXML_HAS_LONG_LONG
	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value(n64Val);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value(n64Val);
	}
	
#endif
	return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal)
{
	wchar_t *pstr = strAttrVal.AllocSysString();

	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value(pstr);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value(pstr);
	}
#ifdef _PSX_IDE_QT_
    delete pstr;
#else
    ::SysFreeString(pstr);
#endif
//	::SysFreeString(pstr);
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal)
{
	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value(strAttrVal);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value(strAttrVal);
	}
    return TRUE;
}
BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal)
{
	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value(nAttrVal);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value(nAttrVal);
	}
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value((unsigned int)dwAttrVal);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value((unsigned int)dwAttrVal);
	}
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
    char pszColor[40];
    GetRGBColor(crAttrVal, pszColor);
	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value(pszColor);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value(pszColor);
	}
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal)
{
	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value(dAttrVal);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value(dAttrVal);
	}
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal)
{
	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value(unAttrVal);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value(unAttrVal);
	}
    return TRUE;
}
BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal)
{
	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value(fAttrVal);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value(fAttrVal);
	}
    return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue)
{
    ASSERT(FALSE);
    return FALSE;
}
#endif

BOOL CXmlRWNode_Pugi::xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys)
{
#ifdef PUGIXML_WCHAR_MODE
    wchar_t wstr[40];

//#ifdef _PSX_QT_LINUX_////zhouhj 20210519  由于wsprintfW不支持浮点,所有改用swprintf
    swprintf(wstr, 40, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
// #else
//     wsprintfW(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
// #endif

#else
    char wstr[40];
    sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
#endif

	//zhouhj 2023.11.22 防止重复添加属性
	pugi::xml_attribute attrTmp = m_oPugiXmlNode.attribute(strAttrName);
	if (attrTmp != NULL)
	{
		attrTmp.set_value(wstr);
	} 
	else
	{
		m_oPugiXmlNode.append_attribute(strAttrName).set_value(wstr);
	}
	return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetElementText(const BSTR strAttrName, CString &strAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    strAttrVal = oChild.child_value();
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    CString strValue;
    strValue = oChild.child_value();
    strAttrVal = strValue.AllocSysString();
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetElementText(const BSTR strAttrName, long &nAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    nAttrVal = CString_To_long((CString)oChild.child_value());
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    dwAttrVal = CString_To_ulong((CString)oChild.child_value());
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    crAttrVal = CString_To_long((CString)oChild.child_value());
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    crAttrVal = CString_To_long((CString)oChild.child_value());
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetElementText(const BSTR strAttrName, double &dAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    dAttrVal = CString_To_double((CString)oChild.child_value());
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetElementText(const BSTR strAttrName, short &unAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    unAttrVal = CString_To_long((CString)oChild.child_value());
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_GetElementText(const BSTR strAttrName, float &fAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    fAttrVal = CString_To_double((CString)oChild.child_value());
    return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNode_Pugi::xml_GetElementText(const BSTR strAttrName, _variant_t &vValue)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    CString strAttrVal;
    strAttrVal = oChild.child_value();
    vValue.vt=VT_BSTR;
    vValue.bstrVal=(_bstr_t)strAttrVal;
    return TRUE;
}
#endif

BOOL CXmlRWNode_Pugi::xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
    pugi::xml_node oChild = m_oPugiXmlNode.child(strAttrName);

    if(oChild == NULL)
        return FALSE;

    CString strAttrVal;
    strAttrVal = oChild.child_value();

    RW_CString_To_SYSTIME(strAttrVal,tmSys);
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.append_child(strAttrName);
	wchar_t *pstr = strAttrVal.AllocSysString();
   oChild.text().set(pstr);
//   ::SysFreeString(pstr);
#ifdef _PSX_IDE_QT_
    delete pstr;
#else
    ::SysFreeString(pstr);
#endif
   return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.append_child(strAttrName);

#ifdef PUGIXML_WCHAR_MODE
	wchar_t wstr[40];

//#ifdef _PSX_QT_LINUX_////zhouhj 20210519  由于wsprintfW不支持浮点,所有改用swprintf
    swprintf(wstr, 40,L"%ld",nAttrVal);
// #else
// 	wsprintfW(wstr, L"%ld",	nAttrVal);
// #endif

#else
	char wstr[40];
	sprintf(wstr, "%ld",nAttrVal);
#endif

//     CString strAttrVal;
//     strAttrVal.Format(_T("%ld"),nAttrVal);
// 	wchar_t *pstr = strAttrVal.AllocSysString();
   oChild.text().set(wstr);
//   ::SysFreeString(pstr);
// #ifdef _PSX_IDE_QT_
//     delete pstr;
// #else
//     ::SysFreeString(pstr);
// #endif
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.append_child(strAttrName);
    char pszColor[40];
    GetRGBColor(crAttrVal, pszColor);

#ifdef PUGIXML_WCHAR_MODE
	wchar_t wstr[40];

//#ifdef _PSX_QT_LINUX_////zhouhj 20210519  由于wsprintfW不支持浮点,所有改用swprintf
    swprintf(wstr,40, L"%s",pszColor);
// #else
// 	wsprintfW(wstr, L"%s",	pszColor);
// #endif

#else
	char wstr[40];
	sprintf(wstr, "%s",	pszColor);
#endif

//     CString strAttrVal;
//     strAttrVal.Format(_T("%s"),pszColor);
// 	wchar_t *pstr = strAttrVal.AllocSysString();
	oChild.text().set(wstr);
// #ifdef _PSX_IDE_QT_
//     delete pstr;
// #else
//     ::SysFreeString(pstr);
// #endif
//	::SysFreeString(pstr);
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.append_child(strAttrName);

#ifdef PUGIXML_WCHAR_MODE
	wchar_t wstr[40];

//#ifdef _PSX_QT_LINUX_
    swprintf(wstr,40, L"%lf",dAttrVal);////zhouhj 20210519  由于wsprintfW不支持浮点,所有改用swprintf
// #else
// 	wsprintfW(wstr, L"%lf",	dAttrVal);
// #endif

#else
	char wstr[40];
	sprintf(wstr, "%lf",	dAttrVal);
#endif

//     CString strAttrVal;
//     strAttrVal.Format(_T("%lf"),dAttrVal);
    oChild.text().set(wstr/*strAttrVal.AllocSysString()*/);
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.append_child(strAttrName);

#ifdef PUGIXML_WCHAR_MODE
	wchar_t wstr[40];

//#ifdef _PSX_QT_LINUX_////zhouhj 20210519  由于wsprintfW不支持浮点,所有改用swprintf
    swprintf(wstr, 40,L"%d",unAttrVal);
// #else
// 	wsprintfW(wstr, L"%d",	unAttrVal);
// #endif

#else
	char wstr[40];
	sprintf(wstr, "%d",	unAttrVal);
#endif

//     CString strAttrVal;
//     strAttrVal.Format(_T("%d"),unAttrVal);
// 	wchar_t *pstr = strAttrVal.AllocSysString();
	oChild.text().set(wstr);
// #ifdef _PSX_IDE_QT_
//     delete pstr;
// #else
//     ::SysFreeString(pstr);
// #endif
//	::SysFreeString(pstr);
    return TRUE;
}

BOOL CXmlRWNode_Pugi::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal)
{
    pugi::xml_node oChild = m_oPugiXmlNode.append_child(strAttrName);

#ifdef PUGIXML_WCHAR_MODE
	wchar_t wstr[40];

//#ifdef _PSX_QT_LINUX_////zhouhj 20210519  由于wsprintfW不支持浮点,所有改用swprintf
    swprintf(wstr, 40,L"%f",fAttrVal);
// #else
// 	wsprintfW(wstr, L"%f",	fAttrVal);
// #endif

#else
	char wstr[40];
	sprintf(wstr, "%f",	fAttrVal);
#endif

//     CString strAttrVal;
//     strAttrVal.Format(_T("%lf"),fAttrVal);
// 	wchar_t *pstr = strAttrVal.AllocSysString();
	oChild.text().set(wstr);
// #ifdef _PSX_IDE_QT_
//     delete pstr;
// #else
//     ::SysFreeString(pstr);
// #endif
//	::SysFreeString(pstr);
    return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNode_Pugi::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue)
{
    ASSERT(FALSE);
    return FALSE;
}
#endif

BOOL CXmlRWNode_Pugi::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys)
{
#ifdef PUGIXML_WCHAR_MODE
	wchar_t wstr[40];

//#ifdef _PSX_QT_LINUX_////zhouhj 20210519  由于wsprintfW不支持浮点,所有改用swprintf
    swprintf(wstr, 40,L"%4d-%02d-%02dT%02d:%02d:%02dZ",tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
// #else
// 	wsprintfW(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
// #endif

#else
    char wstr[40];
    sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
#endif

    pugi::xml_node oChild = m_oPugiXmlNode.append_child(strAttrName);
//     CString strAttrVal;
//     strAttrVal = wstr;
// 	wchar_t *pstr = strAttrVal.AllocSysString();
    oChild.text().set(wstr);
// #ifdef _PSX_IDE_QT_
//     delete pstr;
// #else
//     ::SysFreeString(pstr);
// #endif
//	::SysFreeString(pstr);
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXmlRWElement_Pugi::CXmlRWElement_Pugi()
{
    m_oPugiXmlNode = pugi::xml_node();
}

BOOL CXmlRWElement_Pugi::AppendChild(CXmlRWElementBase &oRWElement)
{
    return TRUE;
}

void CXmlRWElement_Pugi::operator=(const pugi::xml_node &oNodeList)
{
    FreeRWObj();
    m_oPugiXmlNode = oNodeList;
}

void CXmlRWElement_Pugi::FreeRWObj()
{
    CXmlRWNode_Pugi::FreeRWObj();
}

CXmlRWElementBase* CXmlRWElement_Pugi::GetCurChildElement()
{
    CXmlRWElement_Pugi *pCurChildElement = new CXmlRWElement_Pugi;
    m_oPugiList.AddTail(pCurChildElement);
    return pCurChildElement;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CXmlRWDoc_Pugi::CXmlRWDoc_Pugi():CXmlRWDocBase()
{
    m_oPugiXmlDoc.reset();
}

CXmlRWNodeBase* CXmlRWDoc_Pugi::GetDocNode()
{
    return GetDocElement();
}

CXmlRWElementBase* CXmlRWDoc_Pugi::GetDocElement()
{
    m_oDocElement = m_oPugiXmlDoc;
    return &m_oDocElement;
}

CXmlRWNodeBase* CXmlRWDoc_Pugi::GetFirstRootNode()
{
    pugi::xml_node oFirstChild = m_oPugiXmlDoc.first_child();
    m_oDocFirstRootNode = oFirstChild;
    return &m_oDocFirstRootNode;
}

CXmlRWElementBase* CXmlRWDoc_Pugi::CreateElement(BSTR bstElementKey,CXmlRWElementBase *pParent)
{
    CXmlRWElement_Pugi *pRWElement_Pugi = (CXmlRWElement_Pugi *)pParent->GetCurChildElement();

    if (pParent->IsEmpty())
    {

        *pRWElement_Pugi = m_oPugiXmlDoc.append_child(bstElementKey);
    }
    else
    {
        *pRWElement_Pugi = ((CXmlRWElement_Pugi*)pParent)->m_oPugiXmlNode.append_child(bstElementKey);
    }

    return pRWElement_Pugi;
}

BOOL CXmlRWDoc_Pugi::AppendChild(CXmlRWElementBase &oRWElement)
{
    return TRUE;
}

BOOL CXmlRWDoc_Pugi::CreateInstruction(const CString &strVersion,const CString &strEnCode)
{
    // 		pugi::xml_node pre = m_oDocU.pPugiXmlDoc->prepend_child(pugi::node_declaration);
    // 		pre.append_attribute(L"version") = L"1.0";
    // 		pre.append_attribute(L"encoding") = strEnCode;
    // 		CString strtileCode;
    // 		strtileCode.Format(("encoding=\"%s\"") ,strEnCode);
    //		pre.append_attribute(strEnCode.AllocSysString());
    //		pre.append_attribute(L"utf-8");
    return TRUE;
}

BOOL CXmlRWDoc_Pugi::xml_OpenFile(const CString &strFile)
{
    try
    {
        std::locale::global(std::locale("chs"));
    }
    catch(...)
    {

    }

    BOOL bRet = FALSE;
//  std::wifstream stream(strFile.GetString());
//    bRet = m_oPugiXmlDoc.load(stream/*strFile*/);//??????λ???XML?;

//    if (!bRet)
    {
#ifdef _PSX_QT_LINUX_
	//yzj 2024.2.2 解决linux下保存文件中文乱码问题
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strFile, &pOldTextCodec);
	bRet = m_oPugiXmlDoc.load_file(strFile.GetString());//??????λ???XML?;
	ResetLocalCodec(pOldTextCodec);
#else
	bRet = m_oPugiXmlDoc.load_file(strFile.GetString());//??????λ???XML?;
#endif
    }

    return bRet;
    //		return m_oPugiXmlDoc.load_file(strFile);//??????λ???XML?;
}

BOOL CXmlRWDoc_Pugi::SaveXml(const CString &strFilePath)
{
#ifdef _PSX_QT_LINUX_
	//yzj 2024.2.2 解决linux下保存文件中文乱码问题
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strFilePath, &pOldTextCodec);
	m_oPugiXmlDoc.save_file(strFilePath.GetString());
	ResetLocalCodec(pOldTextCodec);
#else
    m_oPugiXmlDoc.save_file(strFilePath.GetString());
#endif

#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
	system("sync");
#endif

    return TRUE;
}

BOOL CXmlRWDoc_Pugi::AppendXml(const CString &strFilePath)
{
#ifdef _PSX_QT_LINUX_
	//yzj 2024.2.2 解决linux下保存文件中文乱码问题
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strFilePath, &pOldTextCodec);
	m_oPugiXmlDoc.append_file(strFilePath.GetString());
	ResetLocalCodec(pOldTextCodec);
#else
	m_oPugiXmlDoc.append_file(strFilePath.GetString());
#endif

#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
	system("sync");
#endif

	return TRUE;
}

void CXmlRWDoc_Pugi::FreeRWObj()
{
    m_oPugiXmlDoc.reset();
}

BOOL CXmlRWDoc_Pugi::GetXml(CString &strXML)
{
    if (m_oPugiXmlDoc == NULL)
    {
        return FALSE;
    }

    //pugi::xml_string_writer writer;//?????????????????С??????????????10024
    //m_oPugiXmlDoc.save(writer);
    char *pXMLValue = m_oPugiXmlDoc.get_xml_string_ascii();

#ifdef PUGIXML_WCHAR_MODE

	strXML = (BSTR)pXMLValue;

#else  //PUGIXML_WCHAR_MODE

    strXML = pXMLValue;

#endif  //PUGIXML_WCHAR_MODE

    delete pXMLValue;
	long nLen = strXML.GetLength();

    return TRUE;
}

BOOL CXmlRWDoc_Pugi::SetXml(BSTR strXML)
{
    if (m_oPugiXmlDoc == NULL)
    {
        return FALSE;
    }

    m_oPugiXmlDoc.load_string(strXML);
    return TRUE;
}

BOOL CXmlRWDoc_Pugi::SetXml_ASCII(char *strXML,long nLen)
{
    if (m_oPugiXmlDoc == NULL)
    {
        return FALSE;
    }

    m_oPugiXmlDoc.load_string_ascii(strXML,nLen);
    return TRUE;
}

BOOL CXmlRWDoc_Pugi::SetXml_UTF8(char *strXML, long nLen)
{
    if (m_oPugiXmlDoc == NULL)
    {
        return FALSE;
    }

	m_oPugiXmlDoc.load_string_utf8(strXML,nLen);
    return TRUE;
}


long CXmlRWDoc_Pugi::GetXml(char **ppszRetBuffer, long nOffset)
{
    if (m_oPugiXmlDoc == NULL)
    {
        *ppszRetBuffer = NULL;
        return 0;
    }

    return m_oPugiXmlDoc.get_xml_string_ex(ppszRetBuffer, nOffset);
}

long CXmlRWDoc_Pugi::GetXml_ASCII(char **ppszRetBuffer, long nOffset)
{
	long nRet = GetXml(ppszRetBuffer,nOffset);

	if (nRet > 0)
	{
		char *pszGbk = NULL;
		int nDestLen = 0;
        utf8_to_gbk_r((const unsigned char*)(*ppszRetBuffer),strlen(*ppszRetBuffer),(unsigned char**)&pszGbk,&nDestLen);
		delete (*ppszRetBuffer);
		*ppszRetBuffer = pszGbk;
		nRet = nDestLen;
	}

	return nRet;
}

//xxy 20200516
long CXmlRWDoc_Pugi::GetXml_wchar(wchar_t **ppzszRetBuffer, long nOffset)
{
	if (m_oPugiXmlDoc == NULL)
	{
		*ppzszRetBuffer = NULL;
		return 0;
	}

	return m_oPugiXmlDoc.get_xml_string_wchar(ppzszRetBuffer, nOffset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //XML_USE_PUGIXML
