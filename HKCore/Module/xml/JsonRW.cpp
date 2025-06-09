#include "stdafx.h"
#include "JsonRW.h"
#ifndef _PSX_QT_LINUX_
#include "oleauto.h"
#endif

#include "../API/StringConvert/String_Gbk_To_Utf8.h"

#ifdef JSON_USE_

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL g_bMergeSameToArray = TRUE;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CJsonNode::CJsonNode()
{
	m_pJsonNode = NULL;
	m_pJsonRootNode = NULL;
}

CJsonNode::CJsonNode(CJSON *pNode)
{
    m_pJsonNode = pNode;
	m_pJsonRootNode = NULL;
}

CString CJsonNode::GetNodeName()
{
	CString strNodeName;
	strNodeName = m_pJsonNode->string;
	return strNodeName;
}

BOOL CJsonNode::IsValid()
{
	return (m_pJsonNode != NULL);
}

CXmlRWNodeBase* CJsonNode::FindLocalChildNode(CJSON *pNode)
{
	if (pNode == NULL)
	{
		return NULL;
	}

	CJsonNode *pJsonNode = NULL;
	CJsonNode *pFind = NULL;
	POS pos = m_oJsonList.GetHeadPosition();

	while(pos)
	{
		pJsonNode = m_oJsonList.GetNext(pos);

		if (pJsonNode->m_pJsonNode == pNode)
		{
			pFind = pJsonNode;
		}
	}

	if (pFind == NULL)
	{
		pFind = new CXmlRWNodeList_Json;
		m_oJsonList.AddTail(pFind);
		*pFind = pNode;
		pFind->m_pJsonRootNode = m_pJsonRootNode;
	}

	return pFind;
}

CXmlRWNodeBase* CJsonNode::GetChildNode(const CString &strNodeName)
{
	CJSON *pNode = NULL;

	if (m_pJsonNode == NULL)//20220601  zhouhj 此处根节点解析有问题,但为确保与之前功能使用兼容,暂时还原回之前方式 
	{
		pNode = m_pJsonRootNode;//CJSON_GetObjectItem(m_pJsonRootNode,strNodeName.GetString());
		//shaolei 20220531   
		//pNode = CJSON_GetObjectItem(m_pJsonRootNode,strNodeName.GetString());
	}
	else
	{
		pNode = CJSON_GetObjectItem(m_pJsonNode,strNodeName.GetString());
	}

	return FindLocalChildNode(pNode);
}

CXmlRWNodeBase* CJsonNode::GetChildNode(const CString &strNodeName, const CString &strAttrID, const CString &strAttrValue)
{
	return GetChildNode(strNodeName);
}

CXmlRWNodeBase* CJsonNode::GetChildNode(BSTR strNodeName)
{
	CString strKey;
	strKey = strNodeName;
	return GetChildNode(strKey);
}

CXmlRWNodeBase* CJsonNode::GetChildNode(BSTR strNodeName, BSTR strAttrID, BSTR strAttrValue)
{
	return GetChildNode(strNodeName);
}

CXmlRWNodeListBase* CJsonNode::GetChildNodes()
{
	return (CXmlRWNodeListBase*)FindLocalChildNode(m_pJsonNode);
}

void CJsonNode::operator=(CJsonNode &oRWNode)
{
	FreeRWObj();
	m_pJsonNode = oRWNode.m_pJsonNode;
	m_pJsonRootNode = oRWNode.m_pJsonRootNode;
}

void CJsonNode::operator=(CJSON *pNode)
{
	FreeRWObj();
	m_pJsonNode = pNode;
	m_pJsonRootNode = NULL;
}

void CJsonNode::FreeRWObj()
{
	if (m_pJsonNode != NULL)
	{
		CJSON_Delete(m_pJsonNode);
		m_pJsonNode = NULL;
	}

	m_pJsonRootNode = NULL;
}

BOOL CJsonNode::xml_PutText(const CString &strText,const BSTR strAttrName)
{
    if (m_pJsonNode == NULL)
    {
        return FALSE;
    }

	CString strAttrKey;
	strAttrKey = strAttrName;
	if (strAttrKey.IsEmpty())
	{
		strAttrKey = _T("#text");
	}

	CJSON_AddStringToObject(m_pJsonNode, strAttrKey.GetString(),strText.GetString());

    return TRUE;
}

CString CJsonNode::xml_GetText(const BSTR strAttrName)
{
	CString strRet = _T("");

	if (m_pJsonNode == NULL)
	{
		return strRet;
	}

	CString strAttrKey;
	strAttrKey = strAttrName;
	if (strAttrKey.IsEmpty())
	{
		strAttrKey = _T("#text");
	}

	BOOL bRet = FALSE;
	CJSON *pAttrItem = CJSON_GetObjectItem (m_pJsonNode, strAttrKey.GetString());
	if (pAttrItem != NULL)
	{
		strRet = pAttrItem->valuestring;
	}

	return strRet;
}

BOOL CJsonNode::xml_GetCDATA(CString &strText,const BSTR strAttrName)
{
    if (m_pJsonNode != NULL)
    {
        strText = xml_GetText(strAttrName);
    }

    return TRUE;
}

BOOL CJsonNode::xml_SetCDATA(CXmlRWDocBase &oXMLDoc,const CString &strText,const BSTR strAttrName)
{
	return xml_PutText(strText,strAttrName);
}

BOOL CJsonNode::GetValue_String(CJSON *pAttrItem,CString &strValue)
{
	if (pAttrItem == NULL)
	{
		return FALSE;
	}

	if (pAttrItem->type == CJSON_String)
	{
		strValue = pAttrItem->valuestring;
	}
	else if (pAttrItem->type == CJSON_Int)
	{
		strValue.Format(_T("%d"),pAttrItem->valueint);
	}
	else if (pAttrItem->type == CJSON_Double)
	{
		strValue.Format(_T("%lf"),pAttrItem->valuedouble);
	}
	else if (pAttrItem->type == CJSON_False)
	{
		strValue = _T("0");
	}
	else if (pAttrItem->type == CJSON_True)
	{
		strValue = _T("1");
	}
	else if (pAttrItem->type == CJSON_Number)
	{
		strValue.Format(_T("%lf"),pAttrItem->valuedouble);
	}
	else
	{
		ASSERT(FALSE);
		return FALSE;
	}

	return TRUE;
}

BOOL CJsonNode::GetValue_Long(CJSON *pAttrItem,long &nValue)
{
	if (pAttrItem == NULL)
	{
		return FALSE;
	}

	if (pAttrItem->type == CJSON_String)
	{
		nValue = CString_To_long(pAttrItem->valuestring);
	}
	else if ((pAttrItem->type == CJSON_Int)||(pAttrItem->type == CJSON_Number))
	{
		nValue = pAttrItem->valueint;
	}
	else if (pAttrItem->type == CJSON_Double)
	{
		nValue = pAttrItem->valuedouble;

		if ((pAttrItem->valuedouble-nValue)>=0.5)
		{
			nValue++;
		}
		else if ((pAttrItem->valuedouble-nValue)<=-0.5)
		{
			nValue--;
		}
	}
	else if (pAttrItem->type == CJSON_False)
	{
		nValue = 0;
	}
	else if (pAttrItem->type == CJSON_True)
	{
		nValue = 1;
	}
	else
	{
		ASSERT(FALSE);
		return FALSE;
	}

	return TRUE;
}

BOOL CJsonNode::GetValue_n64(CJSON *pAttrItem,__int64 &n64Value)
{
	if (pAttrItem == NULL)
	{
		return FALSE;
	}

	if (pAttrItem->type == CJSON_String)
	{
		n64Value = CString_To_i64(pAttrItem->valuestring);
	}
	else if ((pAttrItem->type == CJSON_Int)||(pAttrItem->type == CJSON_Number))
	{
		n64Value = pAttrItem->valuen64;
	}
	else if (pAttrItem->type == CJSON_Double)
	{
		n64Value = pAttrItem->valuedouble;

		if ((pAttrItem->valuedouble-n64Value)>=0.5)
		{
			n64Value++;
		}
		else if ((pAttrItem->valuedouble-n64Value)<=-0.5)
		{
			n64Value--;
		}
	}
	else if (pAttrItem->type == CJSON_False)
	{
		n64Value = 0;
	}
	else if (pAttrItem->type == CJSON_True)
	{
		n64Value = 1;
	}
	else
	{
		ASSERT(FALSE);
		return FALSE;
	}

	return TRUE;
}

BOOL CJsonNode::GetValue_Double(CJSON *pAttrItem,double &dValue)
{
	if (pAttrItem == NULL)
	{
		return FALSE;
	}

	if (pAttrItem->type == CJSON_String)
	{
		dValue = CString_To_double(pAttrItem->valuestring);
	}
	else if (pAttrItem->type == CJSON_Int)
	{
		dValue = pAttrItem->valueint;
	}
	else if ((pAttrItem->type == CJSON_Double)||(pAttrItem->type == CJSON_Number))
	{
		dValue = pAttrItem->valuedouble;
	}
	else if (pAttrItem->type == CJSON_False)
	{
		dValue = 0;
	}
	else if (pAttrItem->type == CJSON_True)
	{
		dValue = 1;
	}
	else
	{
		ASSERT(FALSE);
		return FALSE;
	}

	return TRUE;
}

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal)
{
	BOOL bRet = FALSE;

	if (m_pJsonNode == NULL)
	{
		return bRet;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON *pAttrItem = CJSON_GetObjectItem (m_pJsonNode, strKey.GetString());

	if (pAttrItem != NULL)
	{
		bRet = GetValue_String(pAttrItem,strAttrVal);//zhouhj 20220313 增加用于根据实际数据类型获取对应值
	}

	return bRet;
}

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal)
{
	CString strValue;
	BOOL bRet = xml_GetAttibuteValue(strAttrName, strValue);
	if (bRet)
	{
		strAttrVal = strValue.AllocSysString();
	}

	return bRet;
}

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal)
{
	BOOL bRet = FALSE;

	if (m_pJsonNode == NULL)
	{
		return bRet;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON *pAttrItem = CJSON_GetObjectItem (m_pJsonNode, strKey.GetString());

	if (pAttrItem != NULL)
	{
		bRet = GetValue_Long(pAttrItem,nAttrVal);//zhouhj 20220313 增加用于根据实际数据类型获取对应值
	}

	return bRet;
}

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, __int64 &n64AttrVal)
{
	BOOL bRet = FALSE;

	if (m_pJsonNode == NULL)
	{
		return bRet;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON *pAttrItem = CJSON_GetObjectItem (m_pJsonNode, strKey.GetString());

	if (pAttrItem != NULL)
	{
		bRet = GetValue_n64(pAttrItem,n64AttrVal);
	}

	return bRet;
}

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
	long nValue = 0;;
	BOOL bRet = xml_GetAttibuteValue(strAttrName, nValue);
	if (bRet)
	{
		dwAttrVal = nValue;
	}

	return bRet;
}

BOOL CJsonNode::xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	long nValue = 0;
	BOOL bRet = xml_GetAttibuteValue(strAttrName, nValue);
	if (bRet)
	{
		crAttrVal = nValue;
	}

	return bRet;
}

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal)
{
	BOOL bRet = FALSE;

	if (m_pJsonNode == NULL)
	{
		return bRet;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON *pAttrItem = CJSON_GetObjectItem (m_pJsonNode, strKey.GetString());

	if (pAttrItem != NULL)
	{
		bRet = GetValue_Double(pAttrItem,dAttrVal);//zhouhj 20220313 增加用于根据实际数据类型获取对应值
	}

	return bRet;
}

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal)
{
	long nValue = 0;
	BOOL bRet = xml_GetAttibuteValue(strAttrName, nValue);
	if (bRet)
	{
		unAttrVal = nValue;
	}

	return bRet;
}

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal)
{
	double fValue = 0;
	BOOL bRet = xml_GetAttibuteValue(strAttrName, fValue);
	if (bRet)
	{
		fAttrVal = fValue;
	}

	return bRet;
}

//yzj 2021-12-13
long CJsonNode::xml_GetAttibuteType(const BSTR strAttrName)
{
	BOOL bRet = FALSE;

	if (m_pJsonNode == NULL)
	{
		return -1;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON *pAttrItem = CJSON_GetObjectItem (m_pJsonNode, strKey.GetString());
	if (pAttrItem != NULL)
	{
		if(pAttrItem->type == CJSON_Number)
		{
			return pAttrItem->numType;
		}
		return pAttrItem->type;
	}

	return -1;
}

#ifndef _PSX_IDE_QT_

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue)
{
	CString strValue;
	BOOL bRet = xml_GetAttibuteValue(strAttrName, strValue);
	if (bRet)
	{
		vValue = strValue;
	}

	return bRet;
}

#endif

BOOL CJsonNode::xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	CString strValue;
	BOOL bRet = xml_GetAttibuteValue(strAttrName, strValue);
	if (bRet)
	{
		RW_CString_To_SYSTIME(strValue,tmSys);
	}

	return bRet;
}

BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName,__int64 &n64Val)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON_AddNumber_int64ToObject(m_pJsonNode, strKey.GetString(),n64Val);
	return TRUE;
}

BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON_AddStringToObject(m_pJsonNode, strKey.GetString(),strAttrVal.GetString());
    return TRUE;
}

BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey,strValue;
	strKey = strAttrName;
	strValue = strAttrVal;

	CJSON_AddStringToObject(m_pJsonNode, strKey.GetString(),strValue.GetString());
	return TRUE;
}

BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON_AddNumberToObject(m_pJsonNode, strKey.GetString(),nAttrVal);
	return TRUE;
}

BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON_AddNumberToObject(m_pJsonNode, strKey.GetString(),dwAttrVal);
	return TRUE;
}

BOOL CJsonNode::xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	char pszColor[40] = {0};
    GetRGBColor(crAttrVal, pszColor);
    
	CString strKey;
	strKey = strAttrName;

	CJSON_AddStringToObject(m_pJsonNode, strKey.GetString(),pszColor);
	return TRUE;
}

BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON_AddNumberToObject(m_pJsonNode, strKey.GetString(),dAttrVal);
	return TRUE;
}

BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON_AddNumberToObject(m_pJsonNode, strKey.GetString(),unAttrVal);
	return TRUE;
}

BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;

	CJSON_AddNumberToObject(m_pJsonNode, strKey.GetString(),fAttrVal);
	return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue)
{
    ASSERT(FALSE);
    return FALSE;
}
#endif

BOOL CJsonNode::xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

#ifdef _UNICODE
    wchar_t wstr[40];
    wsprintf(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
#else
    char wstr[40];
    sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
#endif

    CString strKey,strValue;
	strKey = strAttrName;
    strValue = wstr;

	CJSON_AddStringToObject(m_pJsonNode, strKey.GetString(),strValue.GetString());
    return TRUE;
}

BOOL CJsonNode::xml_GetElementText(const BSTR strAttrName, CString &strAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;
	CJSON *pNode = CJSON_GetObjectItem(m_pJsonNode,strKey.GetString());
	if (pNode == NULL)
	{
		return FALSE;
	}

    strAttrVal = pNode->valuestring;
    return TRUE;
}

BOOL CJsonNode::xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal)
{
	CString strValue;
	BOOL bRet = xml_GetElementText(strAttrName,strValue);
	if (bRet)
	{
		strAttrVal = strValue.AllocSysString();
	}

    return bRet;
}

BOOL CJsonNode::xml_GetElementText(const BSTR strAttrName, long &nAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;
	CJSON *pNode = CJSON_GetObjectItem(m_pJsonNode,strKey.GetString());
	if (pNode == NULL)
	{
		return FALSE;
	}

	nAttrVal = pNode->valueint;
	return TRUE;
}

BOOL CJsonNode::xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;
	CJSON *pNode = CJSON_GetObjectItem(m_pJsonNode,strKey.GetString());
	if (pNode == NULL)
	{
		return FALSE;
	}

	dwAttrVal = pNode->valueint;
	return TRUE;
}

BOOL CJsonNode::xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	long nValue;
	BOOL bRet = xml_GetElementText(strAttrName,nValue);
	if (bRet)
	{
		crAttrVal = nValue;
	}

	return bRet;
}

BOOL CJsonNode::xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	return xml_GetElement_Color(strAttrName,crAttrVal);
}

BOOL CJsonNode::xml_GetElementText(const BSTR strAttrName, double &dAttrVal)
{
	if (m_pJsonNode == NULL)
	{
		return FALSE;
	}

	CString strKey;
	strKey = strAttrName;
	CJSON *pNode = CJSON_GetObjectItem(m_pJsonNode,strKey.GetString());
	if (pNode == NULL)
	{
		return FALSE;
	}

	dAttrVal = pNode->valuedouble;
	return TRUE;
}

BOOL CJsonNode::xml_GetElementText(const BSTR strAttrName, short &unAttrVal)
{
	long nValue;
	BOOL bRet = xml_GetElementText(strAttrName,nValue);
	if (bRet)
	{
		unAttrVal = nValue;
	}

	return bRet;
}

BOOL CJsonNode::xml_GetElementText(const BSTR strAttrName, float &fAttrVal)
{
	double fValue;
	BOOL bRet = xml_GetElementText(strAttrName,fValue);
	if (bRet)
	{
		fAttrVal = fValue;
	}

	return bRet;
}

#ifndef _PSX_IDE_QT_
BOOL CJsonNode::xml_GetElementText(const BSTR strAttrName, _variant_t &vValue)
{
	CString strValue;
	BOOL bRet = xml_GetElementText(strAttrName,strValue);
	if (bRet)
	{
		vValue.vt=VT_BSTR;
		vValue.bstrVal=(_bstr_t)strValue;
	}

	return bRet;
}
#endif

BOOL CJsonNode::xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	CString strValue;
	BOOL bRet = xml_GetElementText(strAttrName,strValue);
	if (bRet)
	{
		RW_CString_To_SYSTIME(strValue,tmSys);
	}

	return bRet;
}

BOOL CJsonNode::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal)
{
	return xml_SetAttributeValue(strAttrName,strAttrVal);
}

BOOL CJsonNode::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal)
{
    return xml_SetAttributeValue(strAttrName,nAttrVal);
}

BOOL CJsonNode::xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal)
{
    return xml_SetAttributeValue(strAttrName,crAttrVal);
}

BOOL CJsonNode::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal)
{
    return xml_SetAttributeValue(strAttrName,dAttrVal);
}

BOOL CJsonNode::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal)
{
    return xml_SetAttributeValue(strAttrName,unAttrVal);
}

BOOL CJsonNode::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal)
{
    return xml_SetAttributeValue(strAttrName,fAttrVal);
}

#ifndef _PSX_IDE_QT_
BOOL CJsonNode::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue)
{
    ASSERT(FALSE);
    return FALSE;
}
#endif

BOOL CJsonNode::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys)
{
	return xml_SetAttributeValue(strAttrName,tmSys);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXmlRWElement_Json::CXmlRWElement_Json():CJsonNode()
{
   
}

BOOL CXmlRWElement_Json::AppendChild(CXmlRWElementBase &oRWElement)
{
    return TRUE;
}

void CXmlRWElement_Json::operator=(CJSON *pNode)
{
    FreeRWObj();
    m_pJsonNode = pNode;
	m_pJsonRootNode = NULL;
}

void CXmlRWElement_Json::FreeRWObj()
{
    CJsonNode::FreeRWObj();
}

CXmlRWElementBase* CXmlRWElement_Json::GetCurChildElement()
{
    CXmlRWElement_Json *pCurChildElement = new CXmlRWElement_Json;
    m_oJsonList.AddTail(pCurChildElement);
	pCurChildElement->m_pJsonRootNode = m_pJsonRootNode;

    return pCurChildElement;
}

/////////////////////////////////////////////////////////////

CXmlRWNodeList_Json::CXmlRWNodeList_Json():CXmlRWElement_Json()
{

}

CXmlRWNodeList_Json::CXmlRWNodeList_Json(CJSON *pNodeList)
{
	m_pJsonNode = pNodeList;
	m_pJsonRootNode = NULL;
}

long CXmlRWNodeList_Json::GetNodeNum()
{
	ASSERT(m_pJsonNode != NULL);

	long nNum = 0;
	CJSON * pChild = m_pJsonNode->child;

	while(pChild != NULL)
	{
		if(pChild->type == CJSON_Object)
		{
			nNum++;
		}
		else if(pChild->type == CJSON_Array)
		{
			nNum += CJSON_GetArraySize(pChild);
		}

		pChild = pChild->next;
	}

    return nNum;
}

CXmlRWNodeBase* CXmlRWNodeList_Json::GetChild(const long &nChildIndex)
{
	ASSERT(m_pJsonNode != NULL);

	long nIndex = 0;
	CJSON * pChild = m_pJsonNode->child;
	CJSON *pFind = NULL;

	while(pChild != NULL)
	{
		if(pChild->type == CJSON_Object)
		{
			if (nIndex == nChildIndex)
			{
				pFind = pChild;
				break;
			}

			nIndex++;
		}
		else if (pChild->type == CJSON_Array)
		{
			int nArrSize = CJSON_GetArraySize(pChild);

			for (int i=0; i<nArrSize; i++)
			{
				if (nIndex == nChildIndex)
				{
					pFind = CJSON_GetArrayItem(pChild,i);

					//将数组子对象key赋值
					pFind->string = pChild->string;

					break;
				}

				nIndex++;
			}

			if(pFind != NULL)
			{
				break;
			}
		}

		pChild = pChild->next;
	}

	if (pFind == NULL)
	{
		return NULL;
	}

	return FindLocalChildNode(pFind);
}

void CXmlRWNodeList_Json::operator=(CJSON *pNodeList)
{
	FreeRWObj();
	m_pJsonNode = pNodeList;
	m_pJsonRootNode = NULL;
}

////////////////////////////////////////////////////////////

CJsonRWDoc::CJsonRWDoc():CXmlRWDocBase()
{
    m_pJsonDoc = CJSON_CreateObject();
}

CJsonRWDoc::~CJsonRWDoc()	
{
	//清除json节点中数组子对象的string=NULL，否则析构错误
	CJSON_ClearArrayKey(m_pJsonDoc);

	FreeRWObj();
}

CXmlRWNodeBase* CJsonRWDoc::GetDocNode()
{
    return GetDocElement();
}

CXmlRWElementBase* CJsonRWDoc::GetDocElement()
{
    m_oDocElement = NULL;
	m_oDocElement.m_pJsonRootNode = m_pJsonDoc;
    return &m_oDocElement;
}

CXmlRWNodeBase* CJsonRWDoc::GetFirstRootNode()
{
    CJSON * pChild = m_pJsonDoc->child;
    m_oDocFirstRootNode = pChild;
    return &m_oDocFirstRootNode;
}

CXmlRWElementBase* CJsonRWDoc::CreateElement(BSTR bstElementKey,CXmlRWElementBase *pParent)
{
    CXmlRWElement_Json *pRWElement_Json = (CXmlRWElement_Json *)pParent->GetCurChildElement();

	CString strItemKey;
	strItemKey = bstElementKey;
	CJSON *pItem = NULL;

    if (pParent->IsEmpty())
    {					
		//CJSON_AddItemToObject(m_pJsonDoc, strItemKey, pItem);
		pItem = m_pJsonDoc;
    }
    else
    {
		pItem = CJSON_CreateObject();
		CJSON_AddItemToObject(((CXmlRWElement_Json*)pParent)->m_pJsonNode, strItemKey.GetString(), pItem);
    }

	*pRWElement_Json = pItem;
	pRWElement_Json->m_pJsonRootNode = m_pJsonDoc;

    return pRWElement_Json;
}

// CXmlRWElementBase* CJsonRWDoc::CreateArrayElement(BSTR bstElementKey,CXmlRWElementBase *pParent)
// {
// 	CXmlRWElement_Json *pRWElement_Json = (CXmlRWElement_Json *)pParent->GetCurChildElement();
// 
// 	CString strItemKey;
// 	strItemKey = bstElementKey;
// 	CJSON *pItem = CJSON_CreateArray();
// 
// 	if (pParent->IsEmpty())
// 	{					
// 		CJSON_AddItemToObject(m_pJsonDoc, strItemKey, pItem);
// 	}
// 	else
// 	{
// 		CJSON_AddItemToObject(((CXmlRWElement_Json*)pParent)->m_pJsonNode, strItemKey, pItem);
// 	}
// 
// 	*pRWElement_Json = pItem;
// 
// 	return pRWElement_Json;
// }

BOOL CJsonRWDoc::AppendChild(CXmlRWElementBase &oRWElement)
{
    return TRUE;
}

BOOL CJsonRWDoc::CreateInstruction(const CString &strVersion,const CString &strEnCode)
{
	return TRUE;
}

//默认json文件编码为utf-8
BOOL CJsonRWDoc::xml_OpenFile(const CString &strFile)
{
	FILE *fp = fopen(strFile.GetString(), "rb");
	if (fp == NULL)
	{
		return FALSE;
	}

	int file_size = 0;
	fseek( fp,0,SEEK_END );
	//获取文件的大小
	file_size=ftell(fp);

	if (file_size <= 0)
	{
		fclose(fp);
		return FALSE;
	}

	char *pBuf = new char[file_size+2];
	pBuf[file_size] = 0;
	pBuf[file_size+1] = 0;

	fseek( fp,0,SEEK_SET );
	size_t nRead = fread(pBuf, 1,file_size,  fp);
	fclose(fp);

	if (nRead != file_size)
	{
		delete pBuf;
		return FALSE;
	}

	m_pJsonDoc = CJSON_Parse_UTF8(pBuf);
	delete pBuf;
	
	return (m_pJsonDoc != NULL);
}

//默认json文件编码为utf-8
BOOL CJsonRWDoc::SaveXml(const CString &strFilePath)
{
	if (m_pJsonDoc == NULL)
	{
		return FALSE;
	}

	FILE *fp = fopen(strFilePath.GetString(), "w+b");
	if (fp == NULL)
	{
		return FALSE;
	}

	if (g_bMergeSameToArray)
	{
		CJSON_MergeSameItemToArray(m_pJsonDoc);
	}

	char *pBuf = CJSON_Print_UTF8(m_pJsonDoc);
	if (pBuf == NULL)
	{
		return FALSE;
	}

	int nLen = strlen(pBuf);
	fseek( fp,0,SEEK_SET );
	size_t nWrite = fwrite(pBuf, 1, nLen, fp);
	delete pBuf;
	fclose(fp);

	if (nWrite != nLen)
	{
		return FALSE;
	}

    return TRUE;
}

void CJsonRWDoc::FreeRWObj()
{
	if (m_pJsonDoc != NULL)
	{
		CJSON_Delete(m_pJsonDoc);
		m_pJsonDoc = NULL;
	}
}

BOOL CJsonRWDoc::GetXml(CString &strXML)
{
    if (m_pJsonDoc == NULL)
    {
        return FALSE;
    }

	if (g_bMergeSameToArray)
	{
		CJSON_MergeSameItemToArray(m_pJsonDoc);
	}

	char *pBuf = CJSON_Print_UTF8(m_pJsonDoc);
	if (pBuf == NULL)
	{
		return FALSE;
	}

	strXML = pBuf;
	long nLen = strlen(pBuf);
	delete pBuf;

    return TRUE;
}

BOOL CJsonRWDoc::SetXml(BSTR strXML)
{
	if (m_pJsonDoc == NULL)
	{
		return FALSE;
	}

	char *pBuf = NULL;
	int nLen = BSTR_to_char(strXML, &pBuf);
	if (pBuf == NULL)
	{
		return FALSE;
	}

	pBuf[nLen] = 0;

	m_pJsonDoc = CJSON_Parse(pBuf);
	delete pBuf;

	return (m_pJsonDoc != NULL);
}

BOOL CJsonRWDoc::SetXml_ASCII(char *strXML,long nLen)
{
	if (m_pJsonDoc == NULL)
	{
		return FALSE;
	}

	char *pBuf = new char[nLen+1];
	memcpy(pBuf,strXML,nLen);
	pBuf[nLen] = 0;

	m_pJsonDoc = CJSON_Parse(pBuf);
	delete pBuf;

	return (m_pJsonDoc != NULL);
}

BOOL CJsonRWDoc::SetXml_UTF8(char *strXML, long nLen)
{
	if (m_pJsonDoc == NULL)
	{
		return FALSE;
	}

	char *pBuf = new char[nLen+1];
	memcpy(pBuf,strXML,nLen);
	pBuf[nLen] = 0;

	m_pJsonDoc = CJSON_Parse_UTF8(pBuf);
	delete pBuf;

	return (m_pJsonDoc != NULL);
}


long CJsonRWDoc::GetXml(char **ppszRetBuffer, long nOffset, bool bUtf8)
{
	if (m_pJsonDoc == NULL)
	{
		*ppszRetBuffer = NULL;
		return 0;
	}

	if (g_bMergeSameToArray)
	{
		CJSON_MergeSameItemToArray(m_pJsonDoc);
	}

	if (bUtf8)
	{
		*ppszRetBuffer = CJSON_Print_UTF8(m_pJsonDoc, nOffset);
	}
	else
	{
		char *pBuf = CJSON_Print(m_pJsonDoc);

		if (pBuf == NULL)
		{
			return 0;
		}

		if (nOffset > 0)
		{
			long nLen = strlen(pBuf);
			char *pszNewBuffer = new char [nLen + nOffset + 4];
			memcpy(pszNewBuffer + nOffset, pBuf, nLen+1);
			*ppszRetBuffer = pszNewBuffer;
			delete pBuf;
		}
		else
		{
			*ppszRetBuffer = pBuf;         
		}
	}

	return (strlen(*ppszRetBuffer + nOffset) + nOffset);
}

//lijunqing 2022-3-11
long CJsonRWDoc::GetXml_ASCII(char **ppszRetBuffer, long nOffset)
{
	if (m_pJsonDoc == NULL)
	{
		*ppszRetBuffer = NULL;
		return 0;
	}

	if (g_bMergeSameToArray)
	{
		CJSON_MergeSameItemToArray(m_pJsonDoc);
	}

	char *pBuf = CJSON_Print(m_pJsonDoc);

	if (pBuf == NULL)
	{
		return 0;
	}

	long nLen = strlen(pBuf);

	if (nOffset <= 0)
	{
		*ppszRetBuffer = pBuf;
	}
	else
	{
		*ppszRetBuffer = new char[nLen + nOffset+10];
		memset(*ppszRetBuffer, 0, nLen + nOffset+10);
		memcpy((*ppszRetBuffer) + nOffset,pBuf,nLen);
		delete pBuf;
	}

	return (nLen + nOffset);
}

//value: utf8编码，解析成json对象属性为gbk

#include "../API/StringConvert/String_Utf8_To_Gbk.h"

CJSON *CJSON_Parse_UTF8(const char *value)
{
	int nDestLen = 0;
	unsigned char *pszGbk = NULL;
	utf8_to_gbk_r((unsigned char*)value, strlen(value), &pszGbk, &nDestLen);

	CJSON *pRes = CJSON_Parse((char*)pszGbk);
	delete pszGbk;
	 
	return pRes;
}

//json对象属性为gbk,生成字节流为utf8
char  *CJSON_Print_UTF8(CJSON *item, long nOffset)
{
	char *pBuf = CJSON_Print(item);

	if (pBuf == NULL)
	{
		return NULL;
	}

	unsigned char *pszUtf8 = NULL;
	int nDestLen = 0;

    gbk_to_utf8_r((unsigned char*)pBuf, strlen(pBuf), &pszUtf8, &nDestLen, nOffset);

	return (char*)pszUtf8;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //JSON_USE_
