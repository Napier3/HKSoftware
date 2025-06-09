// OverCurrentElements.cpp : 实现文件
//

#include "stdafx.h"
#include "RioOverCurrentElements.h"



// COverCurrentElements

CRioOverCurrentElements::CRioOverCurrentElements()
{
	//初始化属性
//        m_strName = _T("OverCurrentElements节点");
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioOverCurrentElements::~CRioOverCurrentElements()
{
}

long CRioOverCurrentElements::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	return 0;
}

long CRioOverCurrentElements::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);


	return 0;
}

long CRioOverCurrentElements::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{

        BinarySerializeCalLen(oBinaryBuffer, m_strType);
        BinarySerializeCalLen(oBinaryBuffer, m_strBlockType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{

        BinarySerializeRead(oBinaryBuffer, m_strType);
        BinarySerializeRead(oBinaryBuffer, m_strBlockType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{

        BinarySerializeWrite(oBinaryBuffer, m_strType);
        BinarySerializeWrite(oBinaryBuffer, m_strBlockType);
	}
	return 0;
}

BOOL CRioOverCurrentElements::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRioOverCurrentElements *p = (CRioOverCurrentElements*)pObj;


    if(m_strType != p->m_strType)
	{
		return FALSE;
	}
    if (m_strBlockType != p->m_strBlockType)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CRioOverCurrentElements::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioOverCurrentElements *p = (CRioOverCurrentElements*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioOverCurrentElements::Clone()
{
	CRioOverCurrentElements *p = new CRioOverCurrentElements();
	Copy(p);
	return p;
}

BOOL CRioOverCurrentElements::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_OVERCURRENTELEMENTS ||
        nClassID == XRIOCLASSID_TIMEDOVERCURRENTELEMENT
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioOverCurrentElements::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strTimedOverCurrentElementKey)
	{
        pNew = new CRioTimedOverCurrentElement();
	}

	return pNew;
}

CExBaseObject* CRioOverCurrentElements::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_TIMEDOVERCURRENTELEMENT)
	{
        pNew = new CRioTimedOverCurrentElement();
	}

	return pNew;
}

void CRioOverCurrentElements::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strOverCurrentElementsInfo;
    strOverCurrentElementsInfo.Format(_T("OverCurrentElements Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strOverCurrentElementsInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

