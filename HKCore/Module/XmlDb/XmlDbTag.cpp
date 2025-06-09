#include "StdAfx.h"
#include "XmlDbTag.h"

CXmlDbTag::CXmlDbTag(void)
{
}

CXmlDbTag::~CXmlDbTag(void)
{
}

void CXmlDbTag::Init()
{
	//
}

void CXmlDbTag::InitAfterSerialize()
{
	//
}

//´®ÐÐ»¯
long CXmlDbTag::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer->IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strData);
	}
	else if (oBinaryBuffer->IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strData);
	}
	else if (oBinaryBuffer->IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strData);
	}

	return 0;
}

long CXmlDbTag::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);//CXmlDbKeys *pXmlDbKeys = (CXmlDbKeys *)pXmlRWKeys;

	BSTR bstr = m_strData.AllocSysString();
	oNode->get_text(&bstr);
	m_strData = bstr;
	::SysFreeString(bstr);

	return 0;
}

long CXmlDbTag::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);
	//´ý¼ìÑé
	oElemen->put_text(_bstr_t(m_strData));

	return 0;
}

//±à¼­
BOOL CXmlDbTag::IsEqualOwn(CBaseObject* pObj)
{
	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	ASSERT(pObj->GetClassID() == CLASSID_XMLDBTAG);
	CXmlDbTag *pTag = (CXmlDbTag *)pObj;

	if (m_strData != pTag->m_strData)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXmlDbTag::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);
	ASSERT(pDest->GetClassID() == CLASSID_XMLDBTAG);

	if(!CExBaseObject::CopyOwn(pDest))
	{
		return FALSE;
	}

	CXmlDbTag *pTag = (CXmlDbTag *)pDest;
	pTag->m_strData = m_strData;

	return TRUE;
}

CBaseObject* CXmlDbTag::Clone()
{
	CXmlDbTag* pNew = new CXmlDbTag();

	if (Copy(pNew))
	{
		return pNew;
	}

	return NULL;
}

void CXmlDbTag::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(m_strData, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}