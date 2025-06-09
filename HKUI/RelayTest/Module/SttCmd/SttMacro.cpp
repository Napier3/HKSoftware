//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacro.cpp  CSttMacro


#include "stdafx.h"
#include "SttMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMacro::CSttMacro()
{
	//初始化属性
	m_pParas = NULL;
	m_pResults = NULL;
	m_pSearchResults = NULL;

	//初始化成员变量
	m_bCreateMacroChild = false;
}

CSttMacro::~CSttMacro()
{
}

BOOL CSttMacro::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttMacro *p = (CSttMacro*)pDest;

	p->m_strVersion = m_strVersion;
	p->m_strType = m_strType;
	p->m_strRemark = m_strRemark;
	return TRUE;
}

CBaseObject* CSttMacro::Clone()
{
	CSttMacro *p = new CSttMacro();
	Copy(p);
	return p;
}

CBaseObject* CSttMacro::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacro *p = new CSttMacro();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttMacro::CanPaste(UINT nClassID)
{
	return FALSE;
}


long CSttMacro::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

    CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strRemarkKey, oNode, m_strRemark);
    return 0;
}

long CSttMacro::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

    CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strRemarkKey, oElement, m_strRemark);

    return 0;
}


CExBaseObject* CSttMacro::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCSttParasKey)
	{
		m_pParas = new CSttParas();
		pNew = m_pParas;
	}
	else if (strClassID == pXmlKeys->m_strCSttResultsKey)
	{
		m_pResults = new CSttResults();
		pNew = m_pResults;
	}
	else if (strClassID == pXmlKeys->m_strCSttSearchResultsKey)
	{
		m_pSearchResults = new CSttSearchResults();
		pNew = m_pSearchResults;
	}

	return pNew;
}

//ReadXml
long CSttMacro::XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys)
{
	if (m_bCreateMacroChild)
	{
		return CExBaseList::XmlReadChildren(oNodes, pXmlRWKeys);
	}

    return 0;
}

//WriteXml
// long CSttMacro::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
//     return 0;
// }

CSttParas* CSttMacro::GetParas()
{
	if (m_pParas == NULL)
	{
		m_pParas = new CSttParas();
		AddNewChild(m_pParas);
	}

	return m_pParas;
}

CSttResults* CSttMacro::GetResults()
{
	if (m_pResults == NULL)
	{
		m_pResults = new CSttResults();
		AddNewChild(m_pResults);
	}

	return m_pResults;
}

CSttSearchResults* CSttMacro::GetSearchResults()
{
	if (m_pSearchResults == NULL)
	{
		m_pSearchResults = new CSttSearchResults();
		AddNewChild(m_pSearchResults);
	}

	return m_pSearchResults;
}

void CSttMacro::SetParameter(const CString &strMacroID, CDataGroup *pParas)
{
	m_strName = strMacroID;
	m_strID = strMacroID;

	if (pParas == NULL)
	{
		return;
	}

	CSttParas *pSttParas = GetParas();
	pSttParas->AttachParas(pParas);
}

