#include "StdAfx.h"
#include "XmlDbMngr.h"

CXmlDbMngr::CXmlDbMngr(void)
{
	m_pTXmlDatabase = new CTXmlDatabase();
	m_pXmlDatabase = new CXmlDatabase();
	ASSERT(m_pTXmlDatabase != NULL);
	ASSERT(m_pXmlDatabase != NULL);
}

CXmlDbMngr::~CXmlDbMngr(void)
{
	if (m_pTXmlDatabase != NULL)
	{
		delete m_pTXmlDatabase;
		m_pTXmlDatabase = NULL;
	}
	
	if (m_pXmlDatabase != NULL)
	{
		delete m_pXmlDatabase;
		m_pXmlDatabase = NULL;
	}
	
}

//查找自身的属性值
CTXmlDbTag *CXmlDbMngr::GetTDbTag(const CString &strTTableID, const CString &strTTagID)
{
	ASSERT(m_pTXmlDatabase != NULL);

	CTXmlDbTable *pTTable = m_pTXmlDatabase->GetTDbTable(strTTableID);
	if (pTTable == NULL)
	{
		return NULL;
	}

	return pTTable->GetAttr(strTTagID);
}

BOOL CXmlDbMngr::GetAttrValue(CXmlDbData *pData, const CString &strAttrID, CString &strAttrData)
{
	ASSERT(pData != NULL);

	CTXmlDbTable *pTTable = m_pTXmlDatabase->GetTDbTable(pData->m_strID);
	if (pTTable == NULL)
	{
		return FALSE;
	}

	long nIndex = pTTable->GetAttrIndex(strAttrID);
	if (nIndex == -1)
	{
		return FALSE;
	}

	return pData->GetAttribute(nIndex, strAttrData);
}

//查找子对象
CXmlDbData *CXmlDbMngr::FindChild(CXmlDbData *pParent, const CString &strAttrID, const CString &strAttrData)
{
	ASSERT(pParent != NULL);

	CXmlDbData *pData = NULL;
	POS pos = pParent->GetHeadPosition();
	while (pos != NULL)
	{
		pData = (CXmlDbData*)pParent->GetNext(pos);
		CString strTemp;
		if (pData != NULL && GetAttrValue(pData, strAttrID,strTemp) && strTemp == strAttrData)
		{
			return pData;
		}
	}

	return NULL;
}