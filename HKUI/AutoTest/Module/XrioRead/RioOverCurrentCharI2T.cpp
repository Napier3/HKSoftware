// OverCurrentCharI2T.cpp : 实现文件
//

#include "stdafx.h"
#include "RioOverCurrentCharI2T.h"


// COverCurrentCharI2T

CRioOverCurrentCharI2T::CRioOverCurrentCharI2T()
{
    //初始化属性
//    m_strName = _T("OverCurrentCharI2T节点");
    m_strType = _T("");
    m_strBlockType = _T("");
//    m_strID = _T("");
	m_strEnabled = _T("");
}

CRioOverCurrentCharI2T::~CRioOverCurrentCharI2T()
{
}

long CRioOverCurrentCharI2T::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	xml_GetAttibuteValue(pXmlKeys->m_strEnabledKey, oNode, m_strEnabled);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
    return 0;
}

long CRioOverCurrentCharI2T::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
    xml_SetAttributeValue(pXmlKeys->m_strEnabledKey, oElement, m_strEnabled);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


    return 0;
}

long CRioOverCurrentCharI2T::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioOverCurrentCharI2T::IsEqualOwn(CBaseObject* pObj)
{
    if(this == pObj)
    {
        return TRUE;
    }

    CRioOverCurrentCharI2T *p = (CRioOverCurrentCharI2T*)pObj;


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

BOOL CRioOverCurrentCharI2T::CopyOwn(CBaseObject* pDest)
{
    if(this == pDest)
    {
        return TRUE;
    }

    CRioOverCurrentCharI2T *p = (CRioOverCurrentCharI2T*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;
	p->m_strEnabled = m_strEnabled;
    return TRUE;
}

CBaseObject* CRioOverCurrentCharI2T::Clone()
{
    CRioOverCurrentCharI2T *p = new CRioOverCurrentCharI2T();
    Copy(p);
    return p;
}

BOOL CRioOverCurrentCharI2T::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHARI2T ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR_A ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR_P ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR_Q
            )
    {
        return TRUE;
    }
    return FALSE;
}

CExBaseObject* CRioOverCurrentCharI2T::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
    CExBaseObject *pNew  = NULL;
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strOverCurrentCharAKey)
    {
        pNew = new CRioOverCurrentCharA();
    }
    if (strClassID == pXmlKeys->m_strOverCurrentCharPKey)
    {
        pNew = new CRioOverCurrentCharP();
    }
    if (strClassID == pXmlKeys->m_strOverCurrentCharQKey)
    {
        pNew = new CRioOverCurrentCharQ();
    }

    return pNew;
}

CExBaseObject* CRioOverCurrentCharI2T::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
    CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR_A)
    {
        pNew = new CRioOverCurrentCharA();
    }
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR_P)
    {
        pNew = new CRioOverCurrentCharP();
    }
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR_Q)
    {
        pNew = new CRioOverCurrentCharQ();
    }

    return pNew;
}

void CRioOverCurrentCharI2T::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strOverCurrentInfo;
    strOverCurrentInfo.Format(_T("OverCurrent Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strOverCurrentInfo, 0, 0, htiParent);
    pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}
