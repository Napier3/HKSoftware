//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchConfig.cpp  CXMatchConfig


#include "stdafx.h"
#include "XMatchConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXMatchConfig::CXMatchConfig()
{
	//初始化属性
	m_pXMatchDatarefs = NULL;
	m_pXMatchDatasetRefs = NULL;

	//初始化成员变量
}

CXMatchConfig::~CXMatchConfig()
{
}

long CXMatchConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSrcDatasetPathKey, oNode, m_strSrcDatasetPath);
	return 0;
}

long CXMatchConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSrcDatasetPathKey, oElement, m_strSrcDatasetPath);
	return 0;
}

CExBaseObject* CXMatchConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXMatchDatarefsKey)
	{
		m_pXMatchDatarefs = new CXMatchDatarefs();
		pNew = m_pXMatchDatarefs;
	}
	else if (strClassID == pXmlKeys->m_strCXMatchDatasetRefsKey)
	{
		m_pXMatchDatasetRefs = new CXMatchDatasetRefs();
		pNew = m_pXMatchDatasetRefs;
	}

	return pNew;
}

CExBaseObject* CXMatchConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == XMCFGCLASSID_CXMATCHDATAREFS)
	{
		m_pXMatchDatarefs = new CXMatchDatarefs();
	}
	else if (nClassID == XMCFGCLASSID_CXMATCHDATASETREFS)
	{
		m_pXMatchDatasetRefs = new CXMatchDatasetRefs();
	}

	return pNew;
}

void CXMatchConfig::InitAfterRead()
{
	if (m_pXMatchDatasetRefs == NULL)
	{
		m_pXMatchDatasetRefs = new CXMatchDatasetRefs();
		AddNewChild(m_pXMatchDatasetRefs);
	}

	if (m_pXMatchDatarefs == NULL)
	{
		m_pXMatchDatarefs = new CXMatchDatarefs();
		AddNewChild(m_pXMatchDatarefs);
	}
}

