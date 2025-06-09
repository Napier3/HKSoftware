#include "StdAfx.h"
#include "TXmlDbTable.h"
#include "TXmlDbTags.h"

CTXmlDbTable::CTXmlDbTable(void)
{
	m_pTags = NULL;
}

CTXmlDbTable::~CTXmlDbTable(void)
{
}

void CTXmlDbTable::Init()
{
	//
}

long CTXmlDbTable::InitAfterSerialize()
{
	//
	return 0;
}

//串行化
long CTXmlDbTable::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	return CExBaseObject::SerializeOwn(oBinaryBuffer);
}

long CTXmlDbTable::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
}

long CTXmlDbTable::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);
}

//创建子对象
CExBaseObject* CTXmlDbTable::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CXmlDbKeys::g_pXmlDbKeys->m_strTagsKey)
	{
		CTXmlDbTags *pChild = new CTXmlDbTags();
		m_pTags = pChild;
		return pChild;
	}
	else if (strClassID == CXmlDbKeys::g_pXmlDbKeys->m_strDbTableKey)
	{
		CTXmlDbTable *pChild = new CTXmlDbTable();
		return pChild;
	}

	return NULL;
}

CExBaseObject* CTXmlDbTable::CreateNewChild(long nClassID)
{
	if (nClassID == CLASSID_TXMLDBTAGS)
	{
		CTXmlDbTags *pChild = new CTXmlDbTags();
		m_pTags = pChild;
		return pChild;
	}
	else if (nClassID == CLASSID_TXMLDBTABLE)
	{
		CTXmlDbTable *pChild = new CTXmlDbTable();
		return pChild;
	}

	return NULL;
}

//编辑
BOOL CTXmlDbTable::IsEqualOwn(CBaseObject* pObj)
{
	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}
	else if (!IsEqualChildren(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTXmlDbTable::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);
	ASSERT(pDest->GetClassID() == CLASSID_TXMLDBTABLE);

	if(!CExBaseObject::CopyOwn(pDest))
	{
		return FALSE;
	}

	if (!CopyChildren(pDest))
	{
		return FALSE;
	}

	return TRUE;
}

CBaseObject* CTXmlDbTable::Clone()
{
	CTXmlDbTable* pNew = new CTXmlDbTable();

	if (Copy(pNew))
	{
		return pNew;
	}

	return NULL;
}

// void CTXmlDbTable::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
// {
// 	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(_T("db-tbl"), 0, 0, htiParent);
// 	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
// 
// 	InsertChildrenTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData);
// }

CTXmlDbTable *CTXmlDbTable::GetTDbTable(const CString &strTableID)
{
	if (m_strID == strTableID)
	{
		return this;
	}
	
	CTXmlDbTable *pTable = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pTable = (CTXmlDbTable*)GetNext(pos);
		if (pTable != NULL && pTable->GetClassID() == CLASSID_TXMLDBTABLE)
		{
			return pTable->GetTDbTable(strTableID);
		}
	}

	return NULL;
}

CTXmlDbTag *CTXmlDbTable::GetAttr(const CString &strTTagID)
{
	ASSERT(m_pTags != NULL);

	return (CTXmlDbTag *)m_pTags->FindByID(strTTagID);
}

long CTXmlDbTable::GetAttrIndex(const CString &strTTagID)
{
	ASSERT(m_pTags != NULL);

	long nIndex = -1;
	CTXmlDbTag *pTTag = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		nIndex++;
		pTTag = (CTXmlDbTag*)GetNext(pos);
		if (pTTag != NULL && pTTag->m_strID == strTTagID)
		{
			return nIndex;
		}
	}

	return -1;
}