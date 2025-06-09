// OverCurrentUnit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RioOverCurrentUnit.h"


// COverCurrentUnit

CRioOverCurrentUnit::CRioOverCurrentUnit()
{
    //��ʼ������
//    m_strName = _T("OverCurrentUnit�ڵ�");
    m_strType = _T("");
    m_strBlockType = _T("");
//    m_strID = _T("");
}

CRioOverCurrentUnit::~CRioOverCurrentUnit()
{
}

long CRioOverCurrentUnit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
    return 0;
}

long CRioOverCurrentUnit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


    return 0;
}

long CRioOverCurrentUnit::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioOverCurrentUnit::IsEqualOwn(CBaseObject* pObj)
{
    if(this == pObj)
    {
        return TRUE;
    }

    CRioOverCurrentUnit *p = (CRioOverCurrentUnit*)pObj;


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

BOOL CRioOverCurrentUnit::CopyOwn(CBaseObject* pDest)
{
    if(this == pDest)
    {
        return TRUE;
    }

    CRioOverCurrentUnit *p = (CRioOverCurrentUnit*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;

    return TRUE;
}

CBaseObject* CRioOverCurrentUnit::Clone()
{
    CRioOverCurrentUnit *p = new CRioOverCurrentUnit();
    Copy(p);
    return p;
}

BOOL CRioOverCurrentUnit::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_OVERCURRENT_UNIT ||
        nClassID == XRIOCLASSID_OVERCURRENT_TABLE ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHARI2T ||
        nClassID == XRIOCLASSID_TINDEX ||
        nClassID == XRIOCLASSID_ACTIVE
            )
    {
        return TRUE;
    }
    return FALSE;
}

CExBaseObject* CRioOverCurrentUnit::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
    CExBaseObject *pNew  = NULL;
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strOverCurrentTableKey)
    {
        pNew = new CRioOverCurrentTable();
    }  
    if (strClassID == pXmlKeys->m_strOverCurrentCharKey)
    {
        pNew = new CRioOverCurrentChar();
    }
    if (strClassID == pXmlKeys->m_strOverCurrentCharI2TKey)
    {
        pNew = new CRioOverCurrentCharI2T();
    }
    if (strClassID == pXmlKeys->m_strActiveKey)
    {
        pNew = new CRioActive();
    }
    if (strClassID == pXmlKeys->m_strTIndexKey)
    {
        pNew = new CRioTIndex();
    }

    return pNew;
}

CExBaseObject* CRioOverCurrentUnit::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
    CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_OVERCURRENT_TABLE)
    {
        pNew = new CRioOverCurrentTable();
    }
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR)
    {
        pNew = new CRioOverCurrentChar();
    }
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHARI2T)
    {
        pNew = new CRioOverCurrentCharI2T();
    }
    if (nClassID == XRIOCLASSID_ACTIVE)
    {
        pNew = new CRioActive();
    }
    if (nClassID == XRIOCLASSID_TINDEX)
    {
        pNew = new CRioTIndex();
    }

    return pNew;
}

void CRioOverCurrentUnit::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strOverCurrentInfo;
    strOverCurrentInfo.Format(_T("OverCurrent Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strOverCurrentInfo, 0, 0, htiParent);
    pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}
