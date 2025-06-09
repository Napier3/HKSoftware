// OverCurrentGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "RioOverCurrentGroup.h"


// COverCurrentGroup

CRioOverCurrentGroup::CRioOverCurrentGroup()
{
    //初始化属性
//    m_strName = _T("OverCurrentGroup节点");
    m_strType = _T("");
    m_strBlockType = _T("");
//    m_strID = _T("");
}

CRioOverCurrentGroup::~CRioOverCurrentGroup()
{
}

long CRioOverCurrentGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
    return 0;
}

long CRioOverCurrentGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


    return 0;
}

long CRioOverCurrentGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioOverCurrentGroup::IsEqualOwn(CBaseObject* pObj)
{
    if(this == pObj)
    {
        return TRUE;
    }

    CRioOverCurrentGroup *p = (CRioOverCurrentGroup*)pObj;


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

BOOL CRioOverCurrentGroup::CopyOwn(CBaseObject* pDest)
{
    if(this == pDest)
    {
        return TRUE;
    }

    CRioOverCurrentGroup *p = (CRioOverCurrentGroup*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;

    return TRUE;
}

CBaseObject* CRioOverCurrentGroup::Clone()
{
    CRioOverCurrentGroup *p = new CRioOverCurrentGroup();
    Copy(p);
    return p;
}

BOOL CRioOverCurrentGroup::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_OVERCURRENT_GROUP ||
        nClassID == XRIOCLASSID_OVERCURRENT_UNIT
            )
    {
        return TRUE;
    }
    return FALSE;
}

CExBaseObject* CRioOverCurrentGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
    CExBaseObject *pNew  = NULL;
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strOverCurrentUnitKey)
    {
        pNew = new CRioOverCurrentUnit();
    }

    return pNew;
}

CExBaseObject* CRioOverCurrentGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
    CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_OVERCURRENT_UNIT)
    {
        pNew = new CRioOverCurrentUnit();
    }

    return pNew;
}

void CRioOverCurrentGroup::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strOverCurrentInfo;
    strOverCurrentInfo.Format(_T("OverCurrent Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strOverCurrentInfo, 0, 0, htiParent);
    pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}
