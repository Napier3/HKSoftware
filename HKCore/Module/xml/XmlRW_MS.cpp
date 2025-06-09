#include "StdAfx.h"
#include "XmlRW_MS.h"
#include "..\MemBuffer\BufferBase.h"

#ifdef XML_USE_MSXML

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlRWNodeList_MS::CXmlRWNodeList_MS()
{
	m_oMSXMLNodeList = NULL;
	m_pCurChildNode = NULL;
}

CXmlRWNodeList_MS::CXmlRWNodeList_MS(MSXML2::IXMLDOMNodeListPtr &pXMLNodeList)
{
	m_oMSXMLNodeList = pXMLNodeList;
}

long CXmlRWNodeList_MS::GetNodeNum()
{
	long nNum = 0;

	m_oMSXMLNodeList->get_length(&nNum);

	return nNum;
}

CXmlRWNodeBase* CXmlRWNodeList_MS::GetChild(const long &nChildIndex)
{
	if (m_pCurChildNode == NULL)
	{
		m_pCurChildNode = new CXmlRWNode_MS;
	}

	MSXML2::IXMLDOMNodePtr oNode = NULL;
	oNode = m_oMSXMLNodeList->Getitem(nChildIndex);
	CXmlRWNode_MS *pCurChildNode = (CXmlRWNode_MS *)m_pCurChildNode;
	*pCurChildNode = oNode;
	return pCurChildNode;
}

void CXmlRWNodeList_MS::operator=(MSXML2::IXMLDOMNodeListPtr &pNodeList)
{
	FreeRWObj();
	m_oMSXMLNodeList = pNodeList;
}

void CXmlRWNodeList_MS::FreeRWObj()
{
	m_oMSXMLNodeList = NULL;

	if (m_pCurChildNode != NULL)
	{
		delete m_pCurChildNode;
		m_pCurChildNode = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXmlRWNode_MS::CXmlRWNode_MS()
{
	m_oMSXMLNode = NULL;
	m_pCurChildNode = NULL;
}

CXmlRWNode_MS::CXmlRWNode_MS(const MSXML2::IXMLDOMNodePtr &pXMLNode)
{
	m_oMSXMLNode = pXMLNode;
}

CString CXmlRWNode_MS::GetNodeName()
{
	CString strNodeName;
#ifdef UNICODE
	CString strNodeNameTmp =  _bstr_t(m_oMSXMLNode->GetnodeName());
	strNodeName = strNodeNameTmp;
#else
	BSTR bstrNodeName =  m_oMSXMLNode->GetnodeName();
	strNodeName = bstrNodeName;
#endif
	return strNodeName;
}

BOOL CXmlRWNode_MS::IsValid()
{
	return (m_oMSXMLNode != NULL);
}

CXmlRWNodeBase* CXmlRWNode_MS::GetChildNode(const CString &strNodeName)
{
	if (m_pCurChildNode == NULL)
	{
		m_pCurChildNode = new CXmlRWNode_MS;
	}

	_bstr_t bstr = L"//";
	bstr += _bstr_t(strNodeName);
	MSXML2::IXMLDOMNodePtr oChildren = NULL;
	oChildren = m_oMSXMLNode->selectSingleNode(bstr);//返回控件中与 XPath 参数（参数1）匹配的第一个子节点；
	CXmlRWNode_MS *pCurChildNode = (CXmlRWNode_MS*)m_pCurChildNode;
	*pCurChildNode = oChildren;
	return m_pCurChildNode;
}


CXmlRWNodeBase* CXmlRWNode_MS::GetChildNode(BSTR strNodeName)
{
	if (m_pCurChildNode == NULL)
	{
		m_pCurChildNode = new CXmlRWNode_MS;
	}

	_bstr_t bstr = L"//";
	bstr += strNodeName;
	MSXML2::IXMLDOMNodePtr oChildren = NULL;
	oChildren = m_oMSXMLNode->selectSingleNode(bstr);//返回控件中与 XPath 参数（参数1）匹配的第一个子节点；
	CXmlRWNode_MS *pCurChildNode = (CXmlRWNode_MS*)m_pCurChildNode;
	*pCurChildNode = oChildren;
	return m_pCurChildNode;
}

CXmlRWNodeListBase* CXmlRWNode_MS::GetChildNodes()
{
	MSXML2::IXMLDOMNodeListPtr oChildren = m_oMSXMLNode->GetchildNodes();
	m_oChildNodeList = oChildren;

	//oChildNodes = (CXmlRWNodeList_MS&)m_oTempNodeList; 
	//((CXmlRWNodeList_MS&)oChildNodes) = oChildren;
	return &m_oChildNodeList;
}

void CXmlRWNode_MS::operator=(CXmlRWNode_MS &oRWNode)
{
	FreeRWObj();
	m_oMSXMLNode = oRWNode.m_oMSXMLNode;
}

void CXmlRWNode_MS::operator=(MSXML2::IXMLDOMNodePtr &pNode)
{
	FreeRWObj();
	m_oMSXMLNode = pNode;
}

void CXmlRWNode_MS::FreeRWObj()
{
	m_oMSXMLNode = NULL;

	if (m_pCurChildNode != NULL)
	{
		delete m_pCurChildNode;
		m_pCurChildNode = NULL;
	}
}

BOOL CXmlRWNode_MS::xml_PutText(const CString &strText)
{
	if (m_oMSXMLNode == NULL)
	{
		return FALSE;
	}

	m_oMSXMLNode->put_text(_bstr_t(strText));
	return TRUE;
}

CString CXmlRWNode_MS::xml_GetText()
{
	CString strText;
	strText = "";

	if (m_oMSXMLNode != NULL)
	{
		strText = (BSTR)(m_oMSXMLNode->Gettext());
	}

	return strText;
}

BOOL CXmlRWNode_MS::xml_GetCDATA(CString &strText)
{
	MSXML2::IXMLDOMCDATASectionPtr oCDTA =  m_oMSXMLNode->GetfirstChild();

	if (oCDTA != NULL)
	{
		strText = (char*)oCDTA->Getxml();
		long nLen = strText.GetLength();
		strText = strText.Mid(9, nLen-12);
	}
	else
	{
		strText = (char*)m_oMSXMLNode->Gettext();
		strText.Trim();
	}

	return TRUE;
}

BOOL CXmlRWNode_MS::xml_SetCDATA(CXmlRWDocBase &oXMLDoc,const CString &strText)
{
	BOOL bTrue = TRUE;

	if (!oXMLDoc.IsValid())
	{
		return FALSE;
	}

	try 
	{
		MSXML2::IXMLDOMNodePtr oNode;
		oNode = ((CXmlRWDoc_MS&)oXMLDoc).m_oMSXMLDoc->createCDATASection(_T(""));
		ASSERT( oNode != NULL);
		m_oMSXMLNode->appendChild(oNode);
		oNode->put_text((_bstr_t)strText);
	} 
	catch(...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}


BOOL CXmlRWNode_MS::xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, strAttrVal);
}
BOOL CXmlRWNode_MS::xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, strAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, nAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, dwAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, crAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, dAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, unAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, fAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, vValue);
}

BOOL CXmlRWNode_MS::xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetAttibuteValue(strAttrName, tmSys);
}

BOOL CXmlRWNode_MS::xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	BSTR bstrVal = strAttrVal.AllocSysString();
	oElement->setAttribute(strAttrName, bstrVal);
	::SysFreeString(bstrVal);

	return FALSE;
}
BOOL CXmlRWNode_MS::xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName, strAttrVal);

	return FALSE;
}

BOOL CXmlRWNode_MS::xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName, nAttrVal);

	return FALSE;
}

BOOL CXmlRWNode_MS::xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName, dwAttrVal);

	return FALSE;
}

BOOL CXmlRWNode_MS::xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	CString strColor;
	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	oElement->setAttribute(strAttrName, _bstr_t(pszColor));

	return FALSE;
}

BOOL CXmlRWNode_MS::xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName, dAttrVal);

	return FALSE;
}

BOOL CXmlRWNode_MS::xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName,unAttrVal);

	return FALSE;
}

BOOL CXmlRWNode_MS::xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName,fAttrVal);

	return FALSE;
}

BOOL CXmlRWNode_MS::xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

	oElement->setAttribute(strAttrName,vValue);

	return TRUE;
}

BOOL CXmlRWNode_MS::xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys)
{
	MSXML2::IXMLDOMElementPtr oElement = m_oMSXMLNode;

	if (oElement==NULL)
	{
		return FALSE;
	}

#ifdef _UNICODE
	wchar_t wstr[40];
	wsprintf(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	oElement->setAttribute(strAttrName, wstr);
#else
	char wstr[40];
	sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	oElement->setAttribute(strAttrName, _bstr_t(wstr));
#endif
	return TRUE;
}

BOOL CXmlRWNode_MS::xml_GetElementText(const BSTR strAttrName, CString &strAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, strAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, strAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetElementText(const BSTR strAttrName, long &nAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, nAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, dwAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, crAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	if (m_oMSXMLNode==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLNode->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		BSTR bstr = oNode->Gettext();
		crAttrVal = GetRGBColor((CString)bstr, crAttrVal);
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWNode_MS::xml_GetElementText(const BSTR strAttrName, double &dAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, dAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetElementText(const BSTR strAttrName, short &unAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, unAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetElementText(const BSTR strAttrName, float &fAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, fAttrVal);
}

BOOL CXmlRWNode_MS::xml_GetElementText(const BSTR strAttrName, _variant_t &vValue)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, vValue);
}

BOOL CXmlRWNode_MS::xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLNode;
	return oElement.xml_GetElementText(strAttrName, tmSys);
}

BOOL CXmlRWNode_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal)
{
	CString strVal;
	MSXML2::IXMLDOMElementPtr oElement = NULL;
	ASSERT(strAttrName != NULL);

	oElement = ((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->createElement(strAttrName);

	if (m_oMSXMLNode == NULL)
	{
		((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->appendChild(oElement);
	}
	else
	{
		m_oMSXMLNode->appendChild(oElement);
	}

	MSXML2::IXMLDOMNodePtr oChildNode = oElement;
	oChildNode->put_text(_bstr_t(strAttrVal));

	return TRUE;
}

BOOL CXmlRWNode_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal)
{
	CString strVal;
	strVal.Format(_T("%d"), nAttrVal);

	return xml_SetElementText(strAttrName, pXMLDoc, strVal);
}

BOOL CXmlRWNode_MS::xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal)
{
	CString strVal;
	MSXML2::IXMLDOMElementPtr oElement = NULL;
	ASSERT(strAttrName != NULL);

	oElement = ((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->createElement(strAttrName);

	if (m_oMSXMLNode == NULL)
	{
		((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->appendChild(oElement);
	}
	else
	{
		m_oMSXMLNode->appendChild(oElement);
	}

	MSXML2::IXMLDOMNodePtr oChildNode = oElement;
	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	oChildNode->put_text(_bstr_t(pszColor));//zhouhj 20191010 不确定

	return TRUE;
}

BOOL CXmlRWNode_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal)
{
	CString strVal;
	strVal.Format(_T("%f"), dAttrVal);

	return xml_SetElementText(strAttrName, pXMLDoc, strVal);
}

BOOL CXmlRWNode_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal)
{
	CString strVal;
	strVal.Format(_T("%d"), unAttrVal);

	return xml_SetElementText(strAttrName, pXMLDoc, strVal);

	return TRUE;
}

BOOL CXmlRWNode_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal)
{
	CString strVal;
	strVal.Format(_T("%f"), fAttrVal);

	return xml_SetElementText(strAttrName, pXMLDoc, strVal);
}

BOOL CXmlRWNode_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue)
{
	CString strVal;
	MSXML2::IXMLDOMElementPtr oElement = NULL;
	ASSERT(strAttrName != NULL);

	oElement = ((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->createElement(strAttrName);

	if (m_oMSXMLNode == NULL)
	{
		((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->appendChild(oElement);
	}
	else
	{
		m_oMSXMLNode->appendChild(oElement);
	}

	MSXML2::IXMLDOMNodePtr oChildNode = oElement;
	oChildNode->put_text(_bstr_t(vValue));//zhouhj 20191010 不确定

	return TRUE;
}

BOOL CXmlRWNode_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys)
{
	CString strVal;
	MSXML2::IXMLDOMElementPtr oElement = NULL;
	ASSERT(strAttrName != NULL);

	oElement = ((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->createElement(strAttrName);

	if (m_oMSXMLNode == NULL)
	{
		((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->appendChild(oElement);
	}
	else
	{
		m_oMSXMLNode->appendChild(oElement);
	}

	MSXML2::IXMLDOMNodePtr oChildNode = oElement;

#ifdef _UNICODE
	wchar_t wstr[40];
	wsprintf(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	oElement->setAttribute(strAttrName, wstr);
#else
	char wstr[40];
	sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	oElement->setAttribute(strAttrName, _bstr_t(wstr));
#endif

	oChildNode->put_text(_bstr_t(wstr));//zhouhj 20191010 不确定
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlRWElement_MS::CXmlRWElement_MS()
{
	m_oMSXMLElement = NULL;
	m_pCurChildElement = NULL;
}

BOOL CXmlRWElement_MS::AppendChild(CXmlRWElementBase &oRWElement)
{
	m_oMSXMLElement->appendChild(((CXmlRWElement_MS&)oRWElement).m_oMSXMLElement);
	return TRUE;
}

void CXmlRWElement_MS::operator=(MSXML2::IXMLDOMNodeListPtr &pNodeList)
{
	FreeRWObj();
	m_oMSXMLElement = pNodeList;
}

void CXmlRWElement_MS::operator=(MSXML2::IXMLDOMElementPtr &pNodeList)
{
	FreeRWObj();
	m_oMSXMLElement = pNodeList;
}

void CXmlRWElement_MS::operator=(MSXML2::IXMLDOMNodePtr &pNodeList)
{
	FreeRWObj();
	m_oMSXMLElement = pNodeList;
}

void CXmlRWElement_MS::FreeRWObj()
{
	m_oMSXMLElement = NULL;

	if (m_pCurChildElement != NULL)
	{
		delete m_pCurChildElement;
		m_pCurChildElement = NULL;
	}
}

BOOL CXmlRWElement_MS::xml_PutText(const CString &strText)
{
	if (m_oMSXMLElement == NULL)
	{
		return FALSE;
	}

	m_oMSXMLElement->put_text(_bstr_t(strText));
	return TRUE;
}

CString CXmlRWElement_MS::xml_GetText()
{
	CString strText;
	strText = "";

	if (m_oMSXMLElement != NULL)
	{
		strText = (BSTR)(m_oMSXMLElement->Gettext());
	}

	return strText;
}

BOOL CXmlRWElement_MS::xml_GetCDATA(CString &strText)
{
	MSXML2::IXMLDOMCDATASectionPtr oCDTA =  m_oMSXMLElement->GetfirstChild();

	if (oCDTA != NULL)
	{
		strText = (char*)oCDTA->Getxml();
		long nLen = strText.GetLength();
		strText = strText.Mid(9, nLen-12);
	}
	else
	{
		strText = (char*)m_oMSXMLElement->Gettext();
		strText.Trim();
	}

	return TRUE;
}

BOOL CXmlRWElement_MS::xml_SetCDATA(CXmlRWDocBase &oXMLDoc,const CString &strText)
{
	BOOL bTrue = TRUE;

	if (!oXMLDoc.IsValid())
	{
		return FALSE;
	}

	try 
	{
		MSXML2::IXMLDOMNodePtr oNode;
		oNode = ((CXmlRWDoc_MS&)oXMLDoc).m_oMSXMLDoc->createCDATASection(_T(""));
		ASSERT( oNode != NULL);
		m_oMSXMLElement->appendChild(oNode);
		oNode->put_text((_bstr_t)strText);
	} 
	catch(...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}


CXmlRWElementBase* CXmlRWElement_MS::GetCurChildElement()
{
	if (m_pCurChildElement == NULL)
	{
		m_pCurChildElement = new CXmlRWElement_MS;
	}

	return m_pCurChildElement;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue(const BSTR strAttrName, CString &strAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = m_oMSXMLElement->getAttribute(strAttrName);

	if (Value.vt == VT_BSTR)
	{
		strAttrVal = Value.bstrVal;
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue(const BSTR strAttrName, wchar_t *strAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = m_oMSXMLElement->getAttribute(strAttrName);

	if (Value.vt == VT_BSTR)
	{
		wcscpy(strAttrVal, Value.bstrVal);
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue(const BSTR strAttrName, long &nAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = m_oMSXMLElement->getAttribute(strAttrName);//找到debug元素对应的节点，获取其属性值；
	BSTR str;

	switch (Value.vt)
	{
	case VT_I4:
		nAttrVal = Value.intVal;
		return TRUE;
	case VT_BSTR:
		str = Value.bstrVal;
		nAttrVal = _wtoi(str);//将const wchar_t *str 类型转换为整型；
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = m_oMSXMLElement->getAttribute(strAttrName);
	BSTR str;

	switch (Value.vt)
	{
	case VT_I4:
		dwAttrVal = Value.intVal;
		return TRUE;
	case VT_BSTR:
		str = Value.bstrVal;
		dwAttrVal = _wtoi(str);
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	VARIANT Value;
	Value = m_oMSXMLElement->getAttribute(strAttrName);
	BSTR str;

	switch (Value.vt)
	{
	case VT_I4:
		crAttrVal = Value.intVal;
		return TRUE;
	case VT_UI4:
		crAttrVal = Value.ulVal;
		return TRUE;
	case VT_BSTR:
		str = Value.bstrVal;
		crAttrVal = GetRGBColor((CString)str, crAttrVal);
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue(const BSTR strAttrName, double &dAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	_variant_t Value;
	Value = m_oMSXMLElement->getAttribute(strAttrName);

	if (Value.vt == VT_NULL)
	{
		return FALSE;
	}

	Value.ChangeType(VT_R8);

	if (Value.vt == VT_R8)
	{
		dAttrVal = Value.dblVal;
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue(const BSTR strAttrName, short &unAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	_variant_t Value;
	Value = m_oMSXMLElement->getAttribute(strAttrName);

	if (Value.vt == VT_NULL)
	{
		return FALSE;
	}

	Value.ChangeType(VT_I2);

	if (Value.vt == VT_I2)
	{
		unAttrVal = Value.iVal;
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue(const BSTR strAttrName, float &fAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	_variant_t Value;
	Value = m_oMSXMLElement->getAttribute(strAttrName);

	if (Value.vt == VT_NULL)
	{
		return FALSE;
	}

	Value.ChangeType(VT_R4);

	if (Value.vt == VT_R4)
	{
		fAttrVal = Value.fltVal;
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue(const BSTR strAttrName, _variant_t &vValue)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	vValue = m_oMSXMLElement->getAttribute(strAttrName);

	return TRUE;
}

BOOL CXmlRWElement_MS::xml_GetAttibuteValue(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	_variant_t Value;
	Value = m_oMSXMLElement->getAttribute(strAttrName);
	ASSERT (Value.vt == VT_BSTR);

	if (Value.vt != VT_BSTR)
	{
		return FALSE;
	}

	CBufferBase oBuffer(Value.bstrVal);
	oBuffer.FormatBuffer();
	oBuffer.FormatBuffer('-');
	oBuffer.FormatBuffer('T');
	oBuffer.FormatBuffer('Z');
	// 	oBuffer.FormatBuffer('t');
	// 	oBuffer.FormatBuffer('z');
	oBuffer.FormatBuffer(':');
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

	return TRUE;
}

BOOL CXmlRWElement_MS::xml_SetAttributeValue(const BSTR strAttrName,const CString &strAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	BSTR bstrVal = strAttrVal.AllocSysString();
	m_oMSXMLElement->setAttribute(strAttrName, bstrVal);
	::SysFreeString(bstrVal);

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_SetAttributeValue(const BSTR strAttrName,const wchar_t *strAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	m_oMSXMLElement->setAttribute(strAttrName, strAttrVal);

	return FALSE;

}

BOOL CXmlRWElement_MS::xml_SetAttributeValue(const BSTR strAttrName, long &nAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	m_oMSXMLElement->setAttribute(strAttrName, nAttrVal);

	return FALSE;

}

BOOL CXmlRWElement_MS::xml_SetAttributeValue(const BSTR strAttrName, DWORD &dwAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	m_oMSXMLElement->setAttribute(strAttrName, dwAttrVal);

	return FALSE;

}

BOOL CXmlRWElement_MS::xml_SetAttributeValue_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	CString strColor;
	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	m_oMSXMLElement->setAttribute(strAttrName, _bstr_t(pszColor));

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_SetAttributeValue(const BSTR strAttrName, double &dAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	m_oMSXMLElement->setAttribute(strAttrName, dAttrVal);

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_SetAttributeValue(const BSTR strAttrName, short &unAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	m_oMSXMLElement->setAttribute(strAttrName,unAttrVal);

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_SetAttributeValue(const BSTR strAttrName, float &fAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	m_oMSXMLElement->setAttribute(strAttrName,fAttrVal);

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_SetAttributeValue(const BSTR strAttrName, _variant_t &vValue)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	m_oMSXMLElement->setAttribute(strAttrName,vValue);

	return TRUE;
}

BOOL CXmlRWElement_MS::xml_SetAttributeValue(const BSTR strAttrName,const SYSTEMTIME &tmSys)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

#ifdef _UNICODE
	wchar_t wstr[40];
	wsprintf(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	m_oMSXMLElement->setAttribute(strAttrName, wstr);
#else
	char wstr[40];
	sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	m_oMSXMLElement->setAttribute(strAttrName, _bstr_t(wstr));
#endif
	return TRUE;
}

BOOL CXmlRWElement_MS::xml_GetElementText(const BSTR strAttrName, CString &strAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		strAttrVal = (BSTR)(oNode->Gettext());
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetElementText(const BSTR strAttrName, wchar_t *strAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		CString strValue;
		strValue = (BSTR)(oNode->Gettext());
		strAttrVal = strValue.AllocSysString();
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetElementText(const BSTR strAttrName, long &nAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		nAttrVal = _wtol(bstr);
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetElementText(const BSTR strAttrName, DWORD &dwAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		dwAttrVal = _wtol(bstr);
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetElement_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	CXmlRWElement_MS oElement;
	oElement = m_oMSXMLElement;
	return oElement.xml_GetElementText(strAttrName, crAttrVal);
}


BOOL CXmlRWElement_MS::xml_GetElementText_Color(const BSTR strAttrName, COLORREF &crAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		BSTR bstr = oNode->Gettext();
		crAttrVal = GetRGBColor((CString)bstr, crAttrVal);
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetElementText(const BSTR strAttrName, double &dAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		dAttrVal = _wtof(bstr);
		return TRUE;
	}

	return FALSE;
}
BOOL CXmlRWElement_MS::xml_GetElementText(const BSTR strAttrName, short &unAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		unAttrVal = (short)_wtol(bstr);
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetElementText(const BSTR strAttrName, float &fAttrVal)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		_bstr_t bstr = oNode->Gettext();
		fAttrVal = (float)_wtof(bstr);
		return TRUE;
	}


	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetElementText(const BSTR strAttrName, _variant_t &vValue)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		vValue = oNode->Gettext();
		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_GetElementText(const BSTR strAttrName, SYSTEMTIME &tmSys)
{
	if (m_oMSXMLElement==NULL)
	{
		return FALSE;
	}

	MSXML2::IXMLDOMNodePtr oNode = m_oMSXMLElement->selectSingleNode(strAttrName);

	if (oNode != NULL)
	{
		CString strAttrVal;
		strAttrVal = (BSTR)(oNode->Gettext());

		CBufferBase oBuffer(strAttrVal);
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

		return TRUE;
	}

	return FALSE;
}

BOOL CXmlRWElement_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const CString &strAttrVal)
{
	CString strVal;
	MSXML2::IXMLDOMElementPtr oElement = NULL;
	ASSERT(strAttrName != NULL);

	oElement = ((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->createElement(strAttrName);

	if (m_oMSXMLElement == NULL)
	{
		((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->appendChild(oElement);
	}
	else
	{
		m_oMSXMLElement->appendChild(oElement);
	}

	MSXML2::IXMLDOMNodePtr oChildNode = oElement;
	oChildNode->put_text(_bstr_t(strAttrVal));

	return TRUE;
}

BOOL CXmlRWElement_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, long &nAttrVal)
{
	CString strVal;
	strVal.Format(_T("%d"), nAttrVal);

	return xml_SetElementText(strAttrName, pXMLDoc, strVal);
}

BOOL CXmlRWElement_MS::xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, COLORREF &crAttrVal)
{
	CString strVal;
	MSXML2::IXMLDOMElementPtr oElement = NULL;
	ASSERT(strAttrName != NULL);

	oElement = ((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->createElement(strAttrName);

	if (m_oMSXMLElement == NULL)
	{
		((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->appendChild(oElement);
	}
	else
	{
		m_oMSXMLElement->appendChild(oElement);
	}

	MSXML2::IXMLDOMNodePtr oChildNode = oElement;
	char pszColor[40];
	GetRGBColor(crAttrVal, pszColor);
	oChildNode->put_text(_bstr_t(pszColor));//zhouhj 20191010 不确定

	return TRUE;
}

BOOL CXmlRWElement_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, double &dAttrVal)
{
	CString strVal;
	strVal.Format(_T("%f"), dAttrVal);

	return xml_SetElementText(strAttrName, pXMLDoc, strVal);
}

BOOL CXmlRWElement_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, short &unAttrVal)
{
	CString strVal;
	strVal.Format(_T("%d"), unAttrVal);

	return xml_SetElementText(strAttrName, pXMLDoc, strVal);

	return TRUE;
}

BOOL CXmlRWElement_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, float &fAttrVal)
{
	CString strVal;
	strVal.Format(_T("%f"), fAttrVal);

	return xml_SetElementText(strAttrName, pXMLDoc, strVal);
}

BOOL CXmlRWElement_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, VARIANT &vValue)
{
	CString strVal;
	MSXML2::IXMLDOMElementPtr oElement = NULL;
	ASSERT(strAttrName != NULL);

	oElement = ((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->createElement(strAttrName);

	if (m_oMSXMLElement == NULL)
	{
		((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->appendChild(oElement);
	}
	else
	{
		m_oMSXMLElement->appendChild(oElement);
	}

	MSXML2::IXMLDOMNodePtr oChildNode = oElement;
	oChildNode->put_text(_bstr_t(vValue));//zhouhj 20191010 不确定

	return TRUE;
}

BOOL CXmlRWElement_MS::xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase *pXMLDoc, const SYSTEMTIME &tmSys)
{
	CString strVal;
	MSXML2::IXMLDOMElementPtr oElement = NULL;
	ASSERT(strAttrName != NULL);

	oElement = ((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->createElement(strAttrName);

	if (m_oMSXMLElement == NULL)
	{
		((CXmlRWDoc_MS*)pXMLDoc)->m_oMSXMLDoc->appendChild(oElement);
	}
	else
	{
		m_oMSXMLElement->appendChild(oElement);
	}

	MSXML2::IXMLDOMNodePtr oChildNode = oElement;
	
#ifdef _UNICODE
	wchar_t wstr[40];
	wsprintf(wstr, L"%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	oElement->setAttribute(strAttrName, wstr);
#else
	char wstr[40];
	sprintf(wstr, "%4d-%02d-%02dT%02d:%02d:%02dZ",	tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
	oElement->setAttribute(strAttrName, _bstr_t(wstr));
#endif

	oChildNode->put_text(_bstr_t(wstr));//zhouhj 20191010 不确定
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CXmlRWDoc_MS::CXmlRWDoc_MS():CXmlRWDocBase()
{
	m_oMSXMLDoc = NULL;
	m_oMSXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
}

CXmlRWNodeBase* CXmlRWDoc_MS::GetDocNode()
{
	MSXML2::IXMLDOMNodePtr oDocRoot = m_oMSXMLDoc->GetdocumentElement();
	m_oDocNode = oDocRoot;
	return &m_oDocNode;
}

CXmlRWNodeBase* CXmlRWDoc_MS::GetFirstRootNode()
{
	MSXML2::IXMLDOMNodePtr oDocRoot = m_oMSXMLDoc->GetdocumentElement();
	m_oDocFirstRootNode = oDocRoot;
	return &m_oDocFirstRootNode;
}

CXmlRWElementBase* CXmlRWDoc_MS::CreateElement(BSTR bstElementKey,CXmlRWElementBase *pParent)
{
	MSXML2::IXMLDOMElementPtr oElement;
	oElement = m_oMSXMLDoc->createElement(bstElementKey);
	CXmlRWElement_MS *pRWElement_MS = (CXmlRWElement_MS *)pParent->GetCurChildElement();
	*pRWElement_MS = oElement;

	if (pParent->IsEmpty())
	{
		AppendChild(*pRWElement_MS);
	}
	else
	{
		pParent->AppendChild(*pRWElement_MS);
	}

	return pRWElement_MS;
}

BOOL CXmlRWDoc_MS::AppendChild(CXmlRWElementBase &oRWElement)
{
	m_oMSXMLDoc->appendChild(((CXmlRWElement_MS&)oRWElement).m_oMSXMLElement);
	return TRUE;
}

BOOL CXmlRWDoc_MS::CreateInstruction(const CString &strVersion,const CString &strEnCode)
{
	MSXML2::IXMLDOMProcessingInstructionPtr pProInstruction; // xml声明
	CString strtileCode;
	strtileCode.Format(_T("version=\"%s\" encoding=\"%s\""),strVersion ,strEnCode);
	pProInstruction = m_oMSXMLDoc->createProcessingInstruction((_bstr_t)_T("xml"), (_bstr_t)strtileCode);
	m_oMSXMLDoc->appendChild(pProInstruction);
	return TRUE;
}

BOOL CXmlRWDoc_MS::SaveXml(const CString &strFilePath)
{
	BSTR strTemp = strFilePath.AllocSysString();
	m_oMSXMLDoc->save(strTemp);
	::SysFreeString(strTemp);
	return TRUE;
}

void CXmlRWDoc_MS::FreeRWObj()
{
	m_oMSXMLDoc = NULL;
}

BOOL CXmlRWDoc_MS::xml_OpenFile(const CString &strFile)
{
	m_oMSXMLDoc = NULL;
	HRESULT hr = m_oMSXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));

	if(!SUCCEEDED(hr)) 
	{ 
		return FALSE;
	} 

	BSTR bstrFile = strFile.AllocSysString();//SysAllocString为一个BSTR申请了内存 ，将 CString 转化成 BSTR；
	BOOL bTrue = m_oMSXMLDoc->load(bstrFile);//读取指定位置的XML源;
	::SysFreeString(bstrFile);//释放空间；

	return bTrue;
}

void CXmlRWDoc_MS::operator=(MSXML2::IXMLDOMDocumentPtr &pDoc)
{
	m_oMSXMLDoc = pDoc;
}

BOOL CXmlRWDoc_MS::GetXml(CString &strXML)
{
	if (m_oMSXMLDoc == NULL)
	{
		return FALSE;
	}

	strXML = (LPCSTR)m_oMSXMLDoc->Getxml();
	return TRUE;
}

BOOL CXmlRWDoc_MS::SetXml(BSTR strXML)
{
	if (m_oMSXMLDoc == NULL)
	{
		return FALSE;
	}

	m_oMSXMLDoc->loadXML(strXML);
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif XML_USE_MSXML
