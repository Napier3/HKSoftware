#include "StdAfx.h"
#include "XmlDbData.h"
#include "XmlDbTags.h"
#include "XmlDbTag.h"

CXmlDbData::CXmlDbData(void)
{
	m_pTags = NULL;
}

CXmlDbData::~CXmlDbData(void)
{
}

void CXmlDbData::Init()
{
	//
}

long CXmlDbData::InitAfterSerialize()
{
	//
	return 0;
}

//串行化
long CXmlDbData::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	return CExBaseObject::SerializeOwn(oBinaryBuffer);
}

long CXmlDbData::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
}

long CXmlDbData::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);
}

//创建子对象
CExBaseObject* CXmlDbData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CXmlDbKeys::g_pXmlDbKeys->m_strTagsKey)
	{
		CXmlDbTags *pChild = new CXmlDbTags();
		m_pTags = pChild;
		return pChild;
	}
	else if (strClassID == CXmlDbKeys::g_pXmlDbKeys->m_strDataKey)
	{
		CXmlDbData *pChild = new CXmlDbData();
		return pChild;
	}

	return NULL;
}

CExBaseObject* CXmlDbData::CreateNewChild(long nClassID)
{
	if (nClassID == CLASSID_XMLDBTAGS)
	{
		CXmlDbTags *pChild = new CXmlDbTags();
		m_pTags = pChild;
		return pChild;
	}
	else if (nClassID == CLASSID_XMLDBDATA)
	{
		CXmlDbData *pChild = new CXmlDbData();
		return pChild;
	}

	return NULL;
}

//编辑
BOOL CXmlDbData::IsEqualOwn(CBaseObject* pObj)
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

BOOL CXmlDbData::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);
	ASSERT(pDest->GetClassID() == CLASSID_XMLDBDATA);

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

CBaseObject* CXmlDbData::Clone()
{
	CXmlDbData* pNew = new CXmlDbData();

	if (Copy(pNew))
	{
		return pNew;
	}

	return NULL;
}

void CXmlDbData::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(_T("dat"), 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);

	InsertChildrenTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData);
}

BOOL CXmlDbData::GetAttribute(const CString &strTID, CString &strAttrData)
{
	ASSERT(m_pTags != NULL);

	return FALSE;
}

BOOL CXmlDbData::GetAttribute(UINT nTIDIndex, CString &strAttrData)
{
	ASSERT(m_pTags != NULL && (int)nTIDIndex < m_pTags->GetCount());

	CXmlDbTag *pTag = (CXmlDbTag *)m_pTags->GetAt(nTIDIndex);
	if (pTag == NULL)
	{
		return FALSE;
	}

	strAttrData = pTag->m_strData;
	
	return TRUE;
}

CXmlDbData* CXmlDbData::Find(UINT nTIDIndex, const CString& strAttData)
{
	return NULL;
}