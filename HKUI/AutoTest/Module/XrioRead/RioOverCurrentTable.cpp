// OverCurrentTable.cpp : 实现文件
//

#include "stdafx.h"
#include "RioOverCurrentTable.h"


// COverCurrentTable

CRioOverCurrentTable::CRioOverCurrentTable()
{
    //初始化属性
//    m_strName = _T("OverCurrentTable节点");
    m_strType = _T("");
    m_strBlockType = _T("");
//    m_strID = _T("");
	m_strEnabled = _T("");
}

CRioOverCurrentTable::~CRioOverCurrentTable()
{
}

long CRioOverCurrentTable::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	xml_GetAttibuteValue(pXmlKeys->m_strEnabledKey, oNode, m_strEnabled);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
    return 0;
}

long CRioOverCurrentTable::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
    xml_SetAttributeValue(pXmlKeys->m_strEnabledKey, oElement, m_strEnabled);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


    return 0;
}

long CRioOverCurrentTable::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
    if(oBinaryBuffer.IsCalSizeMode())
    {

        BinarySerializeCalLen(oBinaryBuffer, m_strType);
        BinarySerializeCalLen(oBinaryBuffer, m_strBlockType);
        BinarySerializeCalLen(oBinaryBuffer, m_strID);
BinarySerializeCalLen(oBinaryBuffer, m_strEnabled);
    }
    else if(oBinaryBuffer.IsReadMode())
    {

        BinarySerializeRead(oBinaryBuffer, m_strType);
        BinarySerializeRead(oBinaryBuffer, m_strBlockType);
        BinarySerializeRead(oBinaryBuffer, m_strID);
BinarySerializeRead(oBinaryBuffer, m_strEnabled);
    }
    else if(oBinaryBuffer.IsWriteMode())
    {

        BinarySerializeWrite(oBinaryBuffer, m_strType);
        BinarySerializeWrite(oBinaryBuffer, m_strBlockType);
        BinarySerializeWrite(oBinaryBuffer, m_strID);
BinarySerializeWrite(oBinaryBuffer, m_strEnabled);
    }
    return 0;
}


BOOL CRioOverCurrentTable::IsEqualOwn(CBaseObject* pObj)
{
    if(this == pObj)
    {
        return TRUE;
    }

    CRioOverCurrentTable *p = (CRioOverCurrentTable*)pObj;


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
if(m_strEnabled != p->m_strEnabled)
	{
		return FALSE;
	}


    return TRUE;
}

BOOL CRioOverCurrentTable::CopyOwn(CBaseObject* pDest)
{
    if(this == pDest)
    {
        return TRUE;
    }

    CRioOverCurrentTable *p = (CRioOverCurrentTable*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;
	p->m_strEnabled = m_strEnabled;
    return TRUE;
}

CBaseObject* CRioOverCurrentTable::Clone()
{
    CRioOverCurrentTable *p = new CRioOverCurrentTable();
    Copy(p);
    return p;
}

BOOL CRioOverCurrentTable::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_POINT ||
        nClassID == XRIOCLASSID_OVERCURRENT_TABLE
            )
    {
        return TRUE;
    }
    return FALSE;
}

CExBaseObject* CRioOverCurrentTable::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
    CExBaseObject *pNew  = NULL;
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strPointKey)
    {
        pNew = new CRioDiffPoint();
    }

    return pNew;
}

CExBaseObject* CRioOverCurrentTable::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
    CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_POINT)
    {
        pNew = new CRioDiffPoint();
    }

    return pNew;
}

void CRioOverCurrentTable::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strOverCurrentInfo;
    strOverCurrentInfo.Format(_T("OverCurrent Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strOverCurrentInfo, 0, 0, htiParent);
    pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}
