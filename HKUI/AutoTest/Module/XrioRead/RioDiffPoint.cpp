// DiffPoint.cpp : 实现文件
//

#include "stdafx.h"
#include "RioDiffPoint.h"


// CDiffPoint

CRioDiffPoint::CRioDiffPoint()
{
	//初始化属性
//    m_strName = _T("DiffPoint节点");
	m_strType = _T("");
	m_strBlockType = _T("");
//    m_strID = _T("");
}

CRioDiffPoint::~CRioDiffPoint()
{
}

long CRioDiffPoint::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
	return 0;
}

long CRioDiffPoint::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


	return 0;
}

long CRioDiffPoint::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{

        BinarySerializeCalLen(oBinaryBuffer, m_strType);
        BinarySerializeCalLen(oBinaryBuffer, m_strBlockType);
        BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{

        BinarySerializeRead(oBinaryBuffer, m_strType);
        BinarySerializeRead(oBinaryBuffer, m_strBlockType);
        BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{

        BinarySerializeWrite(oBinaryBuffer, m_strType);
        BinarySerializeWrite(oBinaryBuffer, m_strBlockType);
        BinarySerializeWrite(oBinaryBuffer, m_strID);
	}
	return 0;
}


BOOL CRioDiffPoint::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioDiffPoint *p = (CRioDiffPoint*)pObj;


    if(m_strType != p->m_strType)
	{
		return FALSE;
	}
    if (m_strBlockType != p->m_strBlockType)
	{
		return FALSE;
	}
    if (m_strID != p->m_strID)
    {
        return FALSE;
    }


	return TRUE;
}

BOOL CRioDiffPoint::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioDiffPoint *p = (CRioDiffPoint*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;
	
	return TRUE;
}

CBaseObject* CRioDiffPoint::Clone()
{
    CRioDiffPoint *p = new CRioDiffPoint();
	Copy(p);
	return p;
}

BOOL CRioDiffPoint::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_POINT ||
        nClassID == XRIOCLASSID_POINT_X ||
        nClassID == XRIOCLASSID_POINT_Y
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioDiffPoint::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strPointXKey)
	{
        pNew = new CRioPointX();
	}
    if (strClassID == pXmlKeys->m_strPointYKey)
    {
        pNew = new CRioPointY();
    }

	return pNew;
}

CExBaseObject* CRioDiffPoint::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


     if (nClassID == XRIOCLASSID_POINT_X)
	{
        pNew = new CRioPointX();
	}
     if (nClassID == XRIOCLASSID_POINT_Y)
     {
         pNew = new CRioPointY();
     }

	return pNew;
}

void CRioDiffPoint::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strCDiffPointInfo;
    strCDiffPointInfo.Format(_T("CDiffPointType = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strCDiffPointInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}


