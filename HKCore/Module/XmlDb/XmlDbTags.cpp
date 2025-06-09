#include "StdAfx.h"
#include "XmlDbTags.h"
#include "XmlDbTag.h"

CXmlDbTags::CXmlDbTags(void)
{
	m_strName = _T("自描述");
}

CXmlDbTags::~CXmlDbTags(void)
{
}

void CXmlDbTags::Init()
{
	//
}

long CXmlDbTags::InitAfterSerialize()
{
	//
	return 0;
}

//串行化
long CXmlDbTags::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	return CExBaseObject::SerializeOwn(oBinaryBuffer);
}

long CXmlDbTags::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;//CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
}

long CXmlDbTags::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	return 0;//CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);
}

//创建子对象
CExBaseObject* CXmlDbTags::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CXmlDbKeys::g_pXmlDbKeys->m_strTagKey)
	{
		CXmlDbTag *pChild = new CXmlDbTag();
		return pChild;
	}

	return NULL;
}

CExBaseObject* CXmlDbTags::CreateNewChild(long nClassID)
{
	if (nClassID == CLASSID_XMLDBTAG)
	{
		CXmlDbTag *pChild = new CXmlDbTag();
		return pChild;
	}

	return NULL;
}

//编辑
BOOL CXmlDbTags::IsEqualOwn(CBaseObject* pObj)
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

BOOL CXmlDbTags::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);
	ASSERT(pDest->GetClassID() == CLASSID_XMLDBTAGS);

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

CBaseObject* CXmlDbTags::Clone()
{
	CXmlDbTags* pNew = new CXmlDbTags();

	if (Copy(pNew))
	{
		return pNew;
	}

	return NULL;
}

void CXmlDbTags::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(_T("tgs"), 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);

	InsertChildrenTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData);
}