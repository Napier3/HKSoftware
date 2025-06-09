#include "StdAfx.h"
#include "TXmlDbTags.h"
#include "TXmlDbTag.h"

CTXmlDbTags::CTXmlDbTags(void)
{
}

CTXmlDbTags::~CTXmlDbTags(void)
{
}

void CTXmlDbTags::Init()
{
	//
}

long CTXmlDbTags::InitAfterSerialize()
{
	//
	return 0;
}

//串行化
long CTXmlDbTags::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	return CExBaseObject::SerializeOwn(oBinaryBuffer);
}

long CTXmlDbTags::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;//CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
}

long CTXmlDbTags::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	return 0;//CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);
}

//创建子对象
CExBaseObject* CTXmlDbTags::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CXmlDbKeys::g_pXmlDbKeys->m_strTagKey)
	{
		CTXmlDbTag *pChild = new CTXmlDbTag();
		return pChild;
	}

	return NULL;
}

CExBaseObject* CTXmlDbTags::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	if (nClassID == CLASSID_TXMLDBTAG)
	{
		CTXmlDbTag *pChild = new CTXmlDbTag();
		return pChild;
	}

	return NULL;
}

//编辑
BOOL CTXmlDbTags::IsEqualOwn(CBaseObject* pObj)
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

BOOL CTXmlDbTags::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);
	ASSERT(pDest->GetClassID() == CLASSID_TXMLDBTAGS);

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

CBaseObject* CTXmlDbTags::Clone()
{
	CTXmlDbTags* pNew = new CTXmlDbTags();

	if (Copy(pNew))
	{
		return pNew;
	}

	return NULL;
}


void CTXmlDbTags::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(_T("tgs"), 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);

	InsertChildrenTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData);
}