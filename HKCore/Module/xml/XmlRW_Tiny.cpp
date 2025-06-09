#include "StdAfx.h"
#include "XmlRW_Tiny.h"

#ifdef XML_USE_TINYXML

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// 用于linux下转换wchar_t与char
#ifdef _PSX_IDE_QT_
 const char* WchartoChar_QT(const wchar_t* pwstr)
 {
 	return QString::fromStdWString(pwstr).toLocal8Bit().data();
 }
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlRWNodeList_Tiny::CXmlRWNodeList_Tiny()
{
	m_pTinyXmlNodeList = NULL;
	m_pCurChildNode = NULL;
}

CXmlRWNodeList_Tiny::CXmlRWNodeList_Tiny(TiXmlElement *pXMLNodeList)
{
	m_pTinyXmlNodeList = pXMLNodeList;
}

long CXmlRWNodeList_Tiny::GetNodeNum()
{
	long nNum = 0;
	nNum = m_pTinyXmlNodeList->Getlength();

	return nNum;
}

CXmlRWNodeBase* CXmlRWNodeList_Tiny::GetChild(const long &nChildIndex)
{
	if (m_pCurChildNode == NULL)
	{
		m_pCurChildNode = new CXmlRWNode_Tiny;
	}

	CXmlRWNode_Tiny *pCurChildNode = (CXmlRWNode_Tiny *)m_pCurChildNode;
	pCurChildNode->m_pTinyXmlNode = (TiXmlElement*)m_pTinyXmlNodeList->Getitem(nChildIndex);
	return m_pCurChildNode;	
}

void CXmlRWNodeList_Tiny::operator=(TiXmlElement *pNodeList)
{
	FreeRWObj();
	m_pTinyXmlNodeList = pNodeList;
}

void CXmlRWNodeList_Tiny::FreeRWObj()
{
	m_pTinyXmlNodeList = NULL;

	if (m_pCurChildNode != NULL)
	{
		delete m_pCurChildNode;
		m_pCurChildNode = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXmlRWNode_Tiny::CXmlRWNode_Tiny()
{
	m_pTinyXmlNode = NULL;
	m_pCurChildNode = NULL;
}

CXmlRWNode_Tiny::CXmlRWNode_Tiny(TiXmlElement *pXMLNode)
{
	m_pTinyXmlNode = pXMLNode;
}

CString CXmlRWNode_Tiny::GetNodeName()
{
	CString strNodeName;
	strNodeName = m_pTinyXmlNode->Value();
	return strNodeName;
}

BOOL CXmlRWNode_Tiny::IsValid()
{
	return (m_pTinyXmlNode != NULL);
}

CXmlRWNodeBase* CXmlRWNode_Tiny::GetChildNode(const CString &strNodeName)
{
	if (m_pCurChildNode == NULL)
	{
		m_pCurChildNode = new CXmlRWNode_Tiny;
	}

	char *pszNodeName = NULL;
	CString_to_char(strNodeName, &pszNodeName);
	((CXmlRWNode_Tiny*)m_pCurChildNode)->m_pTinyXmlNode = (TiXmlElement*)m_pTinyXmlNode->FirstChild(pszNodeName);
	delete pszNodeName;

	return m_pCurChildNode;
}

CXmlRWNodeBase* CXmlRWNode_Tiny::GetChildNode(BSTR strNodeName)
{
	if (m_pCurChildNode == NULL)
	{
		m_pCurChildNode = new CXmlRWNode_Tiny;
	}

	char *pszNodeName = NULL;
	BSTR_to_char(strNodeName, &pszNodeName);
	((CXmlRWNode_Tiny*)m_pCurChildNode)->m_pTinyXmlNode = (TiXmlElement*)m_pTinyXmlNode->FirstChild(pszNodeName);
	delete pszNodeName;

	return m_pCurChildNode;
}

CXmlRWNodeListBase* CXmlRWNode_Tiny::GetChildNodes()
{
	//((CXmlRWNodeList_Tiny&)oChildNodes).m_pTinyXmlNodeList = m_pTinyXmlNode;
	m_oChildNodeList.m_pTinyXmlNodeList = m_pTinyXmlNode;
	return &m_oChildNodeList;
}

void CXmlRWNode_Tiny::operator=(CXmlRWNode_Tiny &oRWNode)
{
	FreeRWObj();
	m_pTinyXmlNode = oRWNode.m_pTinyXmlNode;
}

void CXmlRWNode_Tiny::operator=(TiXmlElement *pElement)
{
	FreeRWObj();
	m_pTinyXmlNode = pElement;
}

void CXmlRWNode_Tiny::FreeRWObj()
{
	m_pTinyXmlNode = NULL;

	if (m_pCurChildNode != NULL)
	{
		delete m_pCurChildNode;
		m_pCurChildNode = NULL;
	}
}

BOOL CXmlRWNode_Tiny::xml_PutText(const CString &strText)
{
	if (m_pTinyXmlNode == NULL)
	{
		return FALSE;
	}

#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strText); 
	m_pTinyXmlNode->SetTextChild(pszConvertedAnsiString);
#else
	m_pTinyXmlNode->SetTextChild(strText);
#endif
#else
	m_pTinyXmlNode->SetTextChild(strText.GetString());
#endif
	return TRUE;
}

CString CXmlRWNode_Tiny::xml_GetText()
{
	CString strText;
	strText = "";

	if (m_pTinyXmlNode)
	{
		const TiXmlNode* node = m_pTinyXmlNode->FirstChild();

		if (node)
		{
			strText = node->Value();

		}
	}

	return strText;
}

BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal)
{
	ASSERT(m_pTinyXmlNode!=NULL);
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	strAttrVal = m_pTinyXmlNode->Attribute(pstr);
#else
	strAttrVal = m_pTinyXmlNode->Attribute(_bstr_t(strAttrName));
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal)
{
	ASSERT(m_pTinyXmlNode!=NULL);
#ifdef _PSX_QT_LINUX_
	CString strValue;
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	strValue = m_pTinyXmlNode->Attribute(pstr);
	strAttrVal = strValue.AllocSysString();
#else
	CString strValue;
	strValue = m_pTinyXmlNode->Attribute(_bstr_t(strAttrName));
	strAttrVal = strValue.AllocSysString();
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&nAttrVal);
#else
	m_pTinyXmlNode->Attribute(_bstr_t(strAttrName),&nAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&dwAttrVal);
#else
	m_pTinyXmlNode->Attribute(_bstr_t(strAttrName),&dwAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	ASSERT(m_pTinyXmlNode!=NULL);
#ifdef _PSX_QT_LINUX_
	CString strAttrVal;
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	strAttrVal = m_pTinyXmlNode->Attribute(pstr);
	crAttrVal = CString_To_long(strAttrVal);
#else
	CString strAttrVal;
	strAttrVal = m_pTinyXmlNode->Attribute(_bstr_t(strAttrName));
	crAttrVal = CString_To_long(strAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&dAttrVal);
#else
	m_pTinyXmlNode->Attribute(_bstr_t(strAttrName),&dAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&unAttrVal);
#else
	m_pTinyXmlNode->Attribute(_bstr_t(strAttrName),&unAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&fAttrVal);
#else
	m_pTinyXmlNode->Attribute(_bstr_t(strAttrName),&fAttrVal);
#endif
	return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue)
{
	ASSERT(m_pTinyXmlNode!=NULL);
	CString strAttrVal;
	strAttrVal = m_pTinyXmlNode->Attribute(_bstr_t(strAttrName));
    vValue = strAttrVal;
	return TRUE;
}
#endif

BOOL CXmlRWNode_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	ASSERT(m_pTinyXmlNode!=NULL);
#ifdef _PSX_QT_LINUX_
	CString strAttrVal;
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	strAttrVal = m_pTinyXmlNode->Attribute(pstr);
	RW_CString_To_SYSTIME(strAttrVal,tmSys);
#else
	CString strAttrVal;
	strAttrVal = m_pTinyXmlNode->Attribute(_bstr_t(strAttrName));
	RW_CString_To_SYSTIME(strAttrVal,tmSys);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->SetAttribute(pstr, strAttrVal);
#else
	m_pTinyXmlNode->SetAttribute(_bstr_t(strAttrName) ,strAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	CString strValue;
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	strValue = strAttrVal;
	m_pTinyXmlNode->SetAttribute(pstr ,strValue);
#else
	CString strValue;
	strValue = strAttrVal;
	m_pTinyXmlNode->SetAttribute(_bstr_t(strAttrName) ,strValue);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&nAttrVal);
#else
	m_pTinyXmlNode->SetAttribute(_bstr_t(strAttrName) ,nAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&dwAttrVal);
#else
	m_pTinyXmlNode->SetAttribute(_bstr_t(strAttrName) ,dwAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->SetAttribute(pstr ,pszColor);
#else
	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	m_pTinyXmlNode->SetAttribute(_bstr_t(strAttrName) ,pszColor);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&dAttrVal);
#else
	m_pTinyXmlNode->SetAttribute(_bstr_t(strAttrName) ,dAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&unAttrVal);
#else
	m_pTinyXmlNode->SetAttribute(_bstr_t(strAttrName) ,unAttrVal);
#endif
	return TRUE;
}
BOOL CXmlRWNode_Tiny::xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->Attribute(pstr,&fAttrVal);
#else
	m_pTinyXmlNode->SetAttribute(_bstr_t(strAttrName) ,fAttrVal);
#endif
	return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNode_Tiny::xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue)
{
#ifdef _PSX_QT_LINUX_
#else
#endif
	ASSERT(FALSE);
	return FALSE;
}
#endif

BOOL CXmlRWNode_Tiny::xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys)
{
#ifdef _UNICODE
	wchar_t wstr[40];
	wsprintf(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
#else
	char wstr[40];
	sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
#endif

#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlNode->SetAttribute(pstr, wstr);
#else
	m_pTinyXmlNode->SetAttribute(_bstr_t(strAttrName) ,wstr);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetElementText(const BSTR strAttrName, CString &strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	strAttrVal = m_pTinyXmlNode->Attribute(pstr);
#else
	strAttrVal = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	CString strValue;
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	strValue = m_pTinyXmlNode->GetAttributeText(pstr);
	strAttrVal = strValue.AllocSysString();
#else
	CString strValue;
	strValue = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	strAttrVal = strValue.AllocSysString();
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetElementText(const BSTR strAttrName, long &nAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlNode->GetAttributeText(pstr);
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &nAttrVal );
		return TRUE;
	}
#else
	const char *pValue = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &nAttrVal );
		return TRUE;
	}
#endif
	return FALSE;
}

BOOL CXmlRWNode_Tiny::xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlNode->GetAttributeText(pstr);
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &dwAttrVal );
		return TRUE;
	}
#else
	const char *pValue = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &dwAttrVal );
		return TRUE;
	}
#endif
	return FALSE;
}

BOOL CXmlRWNode_Tiny::xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strTmp;
	strTmp = m_pTinyXmlNode->GetAttributeText(pstr);
	crAttrVal = CString_To_long(strTmp);
#else
	CString strTmp;
	strTmp = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	crAttrVal = CString_To_long(strTmp);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strAttrVal;
	strAttrVal = m_pTinyXmlNode->GetAttributeText(pstr);
	crAttrVal = CString_To_long(strAttrVal);
#else
	CString strAttrVal;
	strAttrVal = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	crAttrVal = CString_To_long(strAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_GetElementText(const BSTR strAttrName, double &dAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlNode->GetAttributeText(pstr);
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%lf", &dAttrVal );
		return TRUE;
	}
#else
	const char *pValue = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%lf", &dAttrVal );
		return TRUE;
	}
#endif
	return FALSE;
}

BOOL CXmlRWNode_Tiny::xml_GetElementText(const BSTR strAttrName, short &unAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlNode->GetAttributeText(pstr);
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%d", &unAttrVal );
		return TRUE;
	}
#else
	const char *pValue = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%d", &unAttrVal );
		return TRUE;
	}
#endif
	return FALSE;
}

BOOL CXmlRWNode_Tiny::xml_GetElementText(const BSTR strAttrName, float &fAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlNode->GetAttributeText(pstr);
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%f", &fAttrVal );
		return TRUE;
	}
#else
	const char *pValue = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	if (pValue)
	{
		TIXML_SSCANF( pValue, "%f", &fAttrVal );
		return TRUE;
	}
#endif
	return FALSE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNode_Tiny::xml_GetElementText(const BSTR strAttrName, _variant_t &vValue)
{
#ifdef _PSX_QT_LINUX_
#else
#endif
	CString strAttrVal;
	strAttrVal = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	vValue.vt=VT_BSTR;
	vValue.bstrVal=(_bstr_t)strAttrVal;
	return TRUE;
}
#endif

BOOL CXmlRWNode_Tiny::xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strAttrVal;
	strAttrVal = m_pTinyXmlNode->GetAttributeText(pstr);
	RW_CString_To_SYSTIME(strAttrVal,tmSys);
#else
	CString strAttrVal;
	strAttrVal = m_pTinyXmlNode->GetAttributeText(_bstr_t(strAttrName));
	RW_CString_To_SYSTIME(strAttrVal,tmSys);
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(pstr);
	if (pValue == NULL)
	{
		return FALSE;
	}
#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strAttrVal); 
	pValue->SetTextChild(pszConvertedAnsiString);
#else
	pValue->SetTextChild(strAttrVal);
#endif
#else
	pValue->SetTextChild(strAttrVal.GetString());
#endif
#else
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(_bstr_t(strAttrName));
	if (pValue == NULL)
	{
		return FALSE;
	}
#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strAttrVal); 
	pValue->SetTextChild(pszConvertedAnsiString);
#else
	pValue->SetTextChild(strAttrVal);
#endif
#else
	pValue->SetTextChild(strAttrVal.GetString());
#endif
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%ld", nAttrVal);
#else
	sprintf (buf, "%ld", nAttrVal);
#endif

	pValue->SetTextChild(buf);
#else
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%ld", nAttrVal);
#else
	sprintf (buf, "%ld", nAttrVal);
#endif

	pValue->SetTextChild(buf);
#endif

	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	pValue->SetTextChild(pszColor);
#else
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	// 	CString strAttrVal;
	// 	strAttrVal.Format(_T("%s"),pszColor);

	// #ifdef UNICODE
	// 	CT2CA pszConvertedAnsiString(strAttrVal); 
	// 	pValue->SetTextChild(pszConvertedAnsiString);
	// #else
	pValue->SetTextChild(pszColor);
	//#endif
#endif
	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%lf", dAttrVal);
#else
	sprintf (buf, "%lf", dAttrVal);
#endif

	pValue->SetTextChild(buf);
#else
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%lf", dAttrVal);
#else
	sprintf (buf, "%lf", dAttrVal);
#endif

	pValue->SetTextChild(buf);
#endif

	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%d", unAttrVal);
#else
	sprintf (buf, "%d", unAttrVal);
#endif

	pValue->SetTextChild(buf);
#else
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%d", unAttrVal);
#else
	sprintf (buf, "%d", unAttrVal);
#endif

	pValue->SetTextChild(buf);
#endif

	return TRUE;
}

BOOL CXmlRWNode_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%f", fAttrVal);
#else
	sprintf (buf, "%f", fAttrVal);
#endif

	pValue->SetTextChild(buf);
#else
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%f", fAttrVal);
#else
	sprintf (buf, "%f", fAttrVal);
#endif

	pValue->SetTextChild(buf);
#endif

	return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWNode_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue)
{
	ASSERT(FALSE);
	return FALSE;
}
#endif

BOOL CXmlRWNode_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(pstr);

	if (pValue == NULL)
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

	CString strTmp;
	strTmp = wstr;

#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strTmp); 
	pValue->SetTextChild(pszConvertedAnsiString);
#else
	pValue->SetTextChild(strTmp);
#endif
#else
	pValue->SetTextChild(strTmp.GetString());
#endif
#else
	TiXmlElement *pValue = m_pTinyXmlNode->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
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

	CString strTmp;
	strTmp = wstr;

#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strTmp); 
	pValue->SetTextChild(pszConvertedAnsiString);
#else
	pValue->SetTextChild(strTmp);
#endif
#else
	pValue->SetTextChild(strTmp.GetString());
#endif
#endif

	return TRUE;
}

// 用于linux下转换wchar_t与char
// const char* CXmlRWNode_Tiny::WCHARtoCHAR(const wchar_t* pwstr)
// {
// 	return QString::fromStdWString(pwstr).toLocal8Bit().data();
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlRWElement_Tiny::CXmlRWElement_Tiny()
{
	m_pTinyXmlElement = NULL;
	m_pCurChildElement = NULL;
}

BOOL CXmlRWElement_Tiny::AppendChild(CXmlRWElementBase &oRWElement)
{
	m_pTinyXmlElement->LinkEndChild(((CXmlRWElement_Tiny&)oRWElement).m_pTinyXmlElement);
	return TRUE;
}

void CXmlRWElement_Tiny::operator=(TiXmlElement *pNodeList)
{
	FreeRWObj();
	m_pTinyXmlElement = pNodeList;
}

void CXmlRWElement_Tiny::FreeRWObj()
{
	m_pTinyXmlElement = NULL;

	if (m_pCurChildElement != NULL)
	{
		delete m_pCurChildElement;
		m_pCurChildElement = NULL;
	}
}

BOOL CXmlRWElement_Tiny::xml_PutText(const CString &strText)
{
	if (m_pTinyXmlElement == NULL)
	{
		return FALSE;
	}

#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strText); 
	m_pTinyXmlElement->SetTextChild(pszConvertedAnsiString);
#else
	m_pTinyXmlElement->SetTextChild(strText);
#endif
#else
	m_pTinyXmlElement->SetTextChild(strText.GetString());
#endif
	return TRUE;
}

CString CXmlRWElement_Tiny::xml_GetText()
{
	CString strText;
	strText = "";

	if (m_pTinyXmlElement)
	{
		const TiXmlNode* node = m_pTinyXmlElement->FirstChild();

		if (node)
		{
			strText = node->Value();

		}
	}

	return strText;
}

CXmlRWElementBase* CXmlRWElement_Tiny::GetCurChildElement()
{
	if (m_pCurChildElement == NULL)
	{
		m_pCurChildElement = new CXmlRWElement_Tiny;
	}

	return m_pCurChildElement;
}

BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal)
{
	ASSERT(m_pTinyXmlElement!=NULL);
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	strAttrVal = m_pTinyXmlElement->Attribute(pstr);
#else
	strAttrVal = m_pTinyXmlElement->Attribute(_bstr_t(strAttrName));
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal)
{
	ASSERT(m_pTinyXmlElement!=NULL);
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strValue;
	strValue = m_pTinyXmlElement->Attribute(pstr);
	strAttrVal = strValue.AllocSysString();
#else
	CString strValue;
	strValue = m_pTinyXmlElement->Attribute(_bstr_t(strAttrName));
	strAttrVal = strValue.AllocSysString();
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->Attribute(pstr,&nAttrVal);
#else
	m_pTinyXmlElement->Attribute(_bstr_t(strAttrName),&nAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->Attribute(pstr,&dwAttrVal);
#else
	m_pTinyXmlElement->Attribute(_bstr_t(strAttrName),&dwAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	ASSERT(m_pTinyXmlElement!=NULL);
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->Attribute(pstr);
	crAttrVal = GetRGBColor(strAttrVal, crAttrVal);
#else
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->Attribute(_bstr_t(strAttrName));
	crAttrVal = GetRGBColor(strAttrVal, crAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->Attribute(pstr,&dAttrVal);
#else
	m_pTinyXmlElement->Attribute(_bstr_t(strAttrName),&dAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->Attribute(pstr,&unAttrVal);
#else
	m_pTinyXmlElement->Attribute(_bstr_t(strAttrName),&unAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->Attribute(pstr,&fAttrVal);
#else
	m_pTinyXmlElement->Attribute(_bstr_t(strAttrName),&fAttrVal);
#endif
	return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue)
{
	ASSERT(m_pTinyXmlElement!=NULL);
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->Attribute(_bstr_t(strAttrName));
    vValue = strAttrVal;
	return TRUE;
}
#endif

BOOL CXmlRWElement_Tiny::xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	ASSERT(m_pTinyXmlElement!=NULL);
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->Attribute(pstr);
	RW_CString_To_SYSTIME(strAttrVal,tmSys);
#else
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->Attribute(_bstr_t(strAttrName));
	RW_CString_To_SYSTIME(strAttrVal,tmSys);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->SetAttribute(pstr,strAttrVal);
#else
	m_pTinyXmlElement->SetAttribute(_bstr_t(strAttrName) ,strAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strValue;
	strValue = strAttrVal;
	m_pTinyXmlElement->SetAttribute(pstr ,strValue);
#else
	CString strValue;
	strValue = strAttrVal;
	m_pTinyXmlElement->SetAttribute(_bstr_t(strAttrName) ,strValue);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->SetAttribute(pstr ,nAttrVal);
#else
	m_pTinyXmlElement->SetAttribute(_bstr_t(strAttrName) ,nAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->SetAttribute(pstr ,dwAttrVal);
#else
	m_pTinyXmlElement->SetAttribute(_bstr_t(strAttrName) ,dwAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	m_pTinyXmlElement->SetAttribute(pstr ,pszColor);
#else
	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	m_pTinyXmlElement->SetAttribute(_bstr_t(strAttrName) ,pszColor);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->SetAttribute(pstr ,dAttrVal);
#else
	m_pTinyXmlElement->SetAttribute(_bstr_t(strAttrName) ,dAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->SetAttribute(pstr ,unAttrVal);
#else
	m_pTinyXmlElement->SetAttribute(_bstr_t(strAttrName) ,unAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	m_pTinyXmlElement->SetAttribute(pstr ,fAttrVal);
#else
	m_pTinyXmlElement->SetAttribute(_bstr_t(strAttrName) ,fAttrVal);
#endif
	return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWElement_Tiny::xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue)
{
	ASSERT(FALSE);
	return TRUE;
}
#endif

BOOL CXmlRWElement_Tiny::xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys)
{
#ifdef _UNICODE
	wchar_t wstr[40];
	wsprintf(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
#else
	char wstr[40];
	sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
#endif

#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strValue;
	strValue = wstr;
	m_pTinyXmlElement->SetAttribute(pstr ,strValue);
#else
	CString strValue;
	strValue = wstr;
	m_pTinyXmlElement->SetAttribute(_bstr_t(strAttrName) ,strValue);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetElementText(const BSTR strAttrName, CString &strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	strAttrVal = m_pTinyXmlElement->GetAttributeText(pstr);
#else
	strAttrVal = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strValue;
	strValue = m_pTinyXmlElement->GetAttributeText(pstr);
	strAttrVal = strValue.AllocSysString();
#else
	CString strValue;
	strValue = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));
	strAttrVal = strValue.AllocSysString();
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetElementText(const BSTR strAttrName, long &nAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlElement->GetAttributeText(pstr);

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &nAttrVal );
		return TRUE;
	}
#else
	const char *pValue = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &nAttrVal );
		return TRUE;
	}
#endif

	return FALSE;
}

BOOL CXmlRWElement_Tiny::xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlElement->GetAttributeText(pstr);

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &dwAttrVal );
		return TRUE;
	}
#else
	const char *pValue = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &dwAttrVal );
		return TRUE;
	}
#endif

	return FALSE;
}

BOOL CXmlRWElement_Tiny::xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strTmp;
	strTmp = m_pTinyXmlElement->GetAttributeText(pstr);
	crAttrVal = CString_To_long(strTmp);
#else
	CString strTmp;
	strTmp = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));
	crAttrVal = CString_To_long(strTmp);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->GetAttributeText(pstr);
	crAttrVal = CString_To_long(strAttrVal);
#else
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));
	crAttrVal = CString_To_long(strAttrVal);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_GetElementText(const BSTR strAttrName, double &dAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlElement->GetAttributeText(pstr);

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%lf", &dAttrVal );
		return TRUE;
	}
#else
	const char *pValue = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%lf", &dAttrVal );
		return TRUE;
	}
#endif

	return FALSE;
}

BOOL CXmlRWElement_Tiny::xml_GetElementText(const BSTR strAttrName, short &unAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlElement->GetAttributeText(pstr);

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%d", &unAttrVal );
		return TRUE;
	}

#else
	const char *pValue = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%d", &unAttrVal );
		return TRUE;
	}

#endif
	return FALSE;
}

BOOL CXmlRWElement_Tiny::xml_GetElementText(const BSTR strAttrName, float &fAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	const char *pValue = m_pTinyXmlElement->GetAttributeText(pstr);

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%f", &fAttrVal );
		return TRUE;
	}
#else
	const char *pValue = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%f", &fAttrVal );
		return TRUE;
	}
#endif

	return FALSE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWElement_Tiny::xml_GetElementText(const BSTR strAttrName, _variant_t &vValue)
{
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));
	vValue.vt=VT_BSTR;
	vValue.bstrVal=(_bstr_t)strAttrVal;
	return TRUE;
}
#endif

BOOL CXmlRWElement_Tiny::xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->GetAttributeText(pstr);
	RW_CString_To_SYSTIME(strAttrVal,tmSys);
#else
	CString strAttrVal;
	strAttrVal = m_pTinyXmlElement->GetAttributeText(_bstr_t(strAttrName));
	RW_CString_To_SYSTIME(strAttrVal,tmSys);
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strAttrVal); 
	pValue->SetTextChild(pszConvertedAnsiString);
#else
	pValue->SetTextChild(strAttrVal);
#endif
#else
	pValue->SetTextChild(strAttrVal.GetString());
#endif
#else
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strAttrVal); 
	pValue->SetTextChild(pszConvertedAnsiString);
#else
	pValue->SetTextChild(strAttrVal);
#endif
#else
	pValue->SetTextChild(strAttrVal.GetString());
#endif
#endif
	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%ld", nAttrVal);
#else
	sprintf (buf, "%ld", nAttrVal);
#endif

	pValue->SetTextChild(buf);
#else
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%ld", nAttrVal);
#else
	sprintf (buf, "%ld", nAttrVal);
#endif

	pValue->SetTextChild(buf);
#endif

	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	pValue->SetTextChild(pszColor);
#else
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	// 	CString strAttrVal;
	// 	strAttrVal.Format(_T("%s"),pszColor);

	// #ifdef UNICODE
	// 	CT2CA pszConvertedAnsiString(strAttrVal); 
	// 	pValue->SetTextChild(pszConvertedAnsiString);
	// #else
	pValue->SetTextChild(pszColor);
	//#endif
#endif

	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%lf", dAttrVal);
#else
	sprintf (buf, "%lf", dAttrVal);
#endif

	pValue->SetTextChild(buf);
#else
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%lf", dAttrVal);
#else
	sprintf (buf, "%lf", dAttrVal);
#endif

	pValue->SetTextChild(buf);
#endif

	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%d", unAttrVal);
#else
	sprintf (buf, "%d", unAttrVal);
#endif

	pValue->SetTextChild(buf);
#else
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%d", unAttrVal);
#else
	sprintf (buf, "%d", unAttrVal);
#endif

	pValue->SetTextChild(buf);
#endif

	return TRUE;
}

BOOL CXmlRWElement_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(pstr);

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%f", fAttrVal);
#else
	sprintf (buf, "%f", fAttrVal);
#endif

	pValue->SetTextChild(buf);

#else
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
	{
		return FALSE;
	}

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%f", fAttrVal);
#else
	sprintf (buf, "%f", fAttrVal);
#endif

	pValue->SetTextChild(buf);

#endif
	return TRUE;
}

#ifndef _PSX_IDE_QT_
BOOL CXmlRWElement_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue)
{
	ASSERT(FALSE);
	return FALSE;
}
#endif

BOOL CXmlRWElement_Tiny::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strAttrName);
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(pstr);

	if (pValue == NULL)
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

	CString strTmp;
	strTmp = wstr;

#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strTmp); 
	pValue->SetTextChild(pszConvertedAnsiString);
#else
	pValue->SetTextChild(strTmp);
#endif
#else
	pValue->SetTextChild(strTmp.GetString());
#endif

#else
	TiXmlElement *pValue = m_pTinyXmlElement->SetElementChild(_bstr_t(strAttrName));

	if (pValue == NULL)
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

	CString strTmp;
	strTmp = wstr;

#ifndef _PSX_IDE_QT_
#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strTmp); 
	pValue->SetTextChild(pszConvertedAnsiString);
#else
	pValue->SetTextChild(strTmp);
#endif
#else
	pValue->SetTextChild(strTmp.GetString());
#endif

#endif
	return TRUE;
}

// 用于linux下转换wchar_t与char
// const char* CXmlRWElement_Tiny::WCHARtoCHAR(const wchar_t* pwstr)
// {
// 	return QString::fromStdWString(pwstr).toLocal8Bit().data();
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXmlRWDoc_Tiny::CXmlRWDoc_Tiny():CXmlRWDocBase()
{
	m_pTinyXmlDoc = new TiXmlDocument;
}

CXmlRWNodeBase* CXmlRWDoc_Tiny::GetDocNode()
{
	m_oDocNode = (TiXmlElement*)m_pTinyXmlDoc;
	return &m_oDocNode;
}

CXmlRWElementBase* CXmlRWDoc_Tiny::CreateElement(BSTR bstElementKey,CXmlRWElementBase *pParent)
{
	TiXmlElement *pElement = new TiXmlElement((char*)_bstr_t(bstElementKey));
	CXmlRWElement_Tiny *pCurChildElement = (CXmlRWElement_Tiny*)pParent->GetCurChildElement();
	pCurChildElement->m_pTinyXmlElement = pElement;

	if (pParent->IsEmpty())
	{
		AppendChild(*pCurChildElement);
	}
	else
	{
		pParent->AppendChild(*pCurChildElement);
	}

	return pCurChildElement;
}

BOOL CXmlRWDoc_Tiny::AppendChild(CXmlRWElementBase &oRWElement)
{
	m_pTinyXmlDoc->LinkEndChild(((CXmlRWElement_Tiny&)oRWElement).m_pTinyXmlElement);
	return TRUE;
}

BOOL CXmlRWDoc_Tiny::CreateInstruction(const CString &strVersion,const CString &strEnCode)
{
#ifdef UNICODE
	char *pzfVersion = NULL;
	char *pzfEncode = NULL;
	CString_to_char(strVersion , &pzfVersion);
	CString_to_char(strEnCode , &pzfEncode);
	TiXmlDeclaration * xmlDecl = new TiXmlDeclaration(pzfVersion, pzfEncode, "" );
	delete pzfVersion;
	delete pzfEncode;
#else
	TiXmlDeclaration * xmlDecl = new TiXmlDeclaration(strVersion.GetString(), strEnCode.GetString(), "" );
#endif
	m_pTinyXmlDoc->LinkEndChild( xmlDecl );
	return TRUE;
}

BOOL CXmlRWDoc_Tiny::SaveXml(const CString &strFilePath)
{
	char *pszPath = NULL;
	CString_to_char(strFilePath, &pszPath);

	m_pTinyXmlDoc->SaveFile(pszPath);
	m_pTinyXmlDoc->Clear();
	delete []pszPath;
	return TRUE;
}

void CXmlRWDoc_Tiny::FreeRWObj()
{
	delete m_pTinyXmlDoc;
	m_pTinyXmlDoc = NULL;
}

BOOL CXmlRWDoc_Tiny::GetXml(CString &strXML)
{
	if (m_pTinyXmlDoc == NULL)
	{
		return FALSE;
	}
	
	std::string strStdXML;
	m_pTinyXmlDoc->GetXml(strStdXML);
	strXML = strStdXML.c_str();
	return TRUE;
}

long CXmlRWDoc_Tiny::GetXml_ASCII(char **ppszRetBuffer, long nOffset)
{
	if (m_pTinyXmlDoc == NULL)
	{
		return FALSE;
	}

	std::string strStdXML;
	m_pTinyXmlDoc->GetXml(strStdXML);
	*ppszRetBuffer = new char[strStdXML.length() + 1];
	memcpy(*ppszRetBuffer + nOffset, strStdXML.c_str(), strStdXML.length() + 1);

	return strStdXML.length() + nOffset;
}

BOOL CXmlRWDoc_Tiny::SetXml(BSTR strXML)
{
#ifdef _PSX_QT_LINUX_
	char* pstr = (char*)WchartoChar_QT(strXML);
	m_pTinyXmlDoc->Parse(pstr);
#else
	m_pTinyXmlDoc->Parse((_bstr_t)strXML);
#endif
	return TRUE;
}

// 用于linux下转换wchar_t与char
// const char* CXmlRWDoc_Tiny::WCHARtoCHAR(const wchar_t* pwstr)
// {
// 	return QString::fromStdWString(pwstr).toLocal8Bit().data();
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //XML_USE_TINYXML
