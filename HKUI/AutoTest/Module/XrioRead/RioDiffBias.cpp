// DiffBias.cpp : 实现文件
//

#include "stdafx.h"
#include "RioDiffBias.h"


// CDiffBias

CRioDiffBias::CRioDiffBias()
{
	//初始化属性
//    m_strName = _T("DiffBias节点");
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioDiffBias::~CRioDiffBias()
{
}

long CRioDiffBias::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
	return 0;
}

long CRioDiffBias::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


	return 0;
}

long CRioDiffBias::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioDiffBias::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioDiffBias *p = (CRioDiffBias*)pObj;


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

BOOL CRioDiffBias::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioDiffBias *p = (CRioDiffBias*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioDiffBias::Clone()
{
    CRioDiffBias *p = new CRioDiffBias();
	Copy(p);
	return p;
}

BOOL CRioDiffBias::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_DIFFBIAS ||
        nClassID == XRIOCLASSID_TRIPCHAR ||
        nClassID == XRIOCLASSID_ACTIVE
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioDiffBias::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strTripCharKey)
	{
        pNew = new CRioTripChar();
	}
    if(strClassID == pXmlKeys->m_strActiveKey)
    {
        pNew = new CRioActive();
    }
	return pNew;
}

CExBaseObject* CRioDiffBias::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_TRIPCHAR)
	{
        pNew = new CRioTripChar();
	}
    if(nClassID == XRIOCLASSID_ACTIVE)
    {
        pNew = new CRioActive();
    }
	return pNew;
}

void CRioDiffBias::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strDiffBiasInfo;
    strDiffBiasInfo.Format(_T("DiffBias Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strDiffBiasInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}


