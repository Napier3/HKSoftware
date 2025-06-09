// OverCurrentChar.cpp : 实现文件
//

#include "stdafx.h"
#include "RioOverCurrentChar.h"


// COverCurrentChar

CRioOverCurrentChar::CRioOverCurrentChar()
{
    //初始化属性
//    m_strName = _T("OverCurrentChar节点");
    m_strType = _T("");
    m_strBlockType = _T("");
//    m_strID = _T("");
	m_strEnabled = _T("");
}

CRioOverCurrentChar::~CRioOverCurrentChar()
{
}

long CRioOverCurrentChar::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	xml_GetAttibuteValue(pXmlKeys->m_strEnabledKey, oNode, m_strEnabled);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
    return 0;
}

long CRioOverCurrentChar::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
    xml_SetAttributeValue(pXmlKeys->m_strEnabledKey, oElement, m_strEnabled);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


    return 0;
}

long CRioOverCurrentChar::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioOverCurrentChar::IsEqualOwn(CBaseObject* pObj)
{
    if(this == pObj)
    {
        return TRUE;
    }

    CRioOverCurrentChar *p = (CRioOverCurrentChar*)pObj;


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

BOOL CRioOverCurrentChar::CopyOwn(CBaseObject* pDest)
{
    if(this == pDest)
    {
        return TRUE;
    }

    CRioOverCurrentChar *p = (CRioOverCurrentChar*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;
	p->m_strEnabled = m_strEnabled;
    return TRUE;
}

CBaseObject* CRioOverCurrentChar::Clone()
{
    CRioOverCurrentChar *p = new CRioOverCurrentChar();
    Copy(p);
    return p;
}

BOOL CRioOverCurrentChar::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR_A ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR_B ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR_P ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR_Q ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR_K1 ||
        nClassID == XRIOCLASSID_OVERCURRENT_CHAR_K2
            )
    {
        return TRUE;
    }
    return FALSE;
}

CExBaseObject* CRioOverCurrentChar::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
    CExBaseObject *pNew  = NULL;
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strOverCurrentCharAKey)
    {
        pNew = new CRioOverCurrentCharA();
    }
    if (strClassID == pXmlKeys->m_strOverCurrentCharBKey)
    {
        pNew = new CRioOverCurrentCharB();
    }
    if (strClassID == pXmlKeys->m_strOverCurrentCharPKey)
    {
        pNew = new CRioOverCurrentCharP();
    }
    if (strClassID == pXmlKeys->m_strOverCurrentCharQKey)
    {
        pNew = new CRioOverCurrentCharQ();
    }
    if (strClassID == pXmlKeys->m_strOverCurrentCharK1Key)
    {
        pNew = new CRioOverCurrentCharK1();
    }
    if (strClassID == pXmlKeys->m_strOverCurrentCharK2Key)
    {
        pNew = new CRioOverCurrentCharK2();
    }

    return pNew;
}

CExBaseObject* CRioOverCurrentChar::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
    CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR_A)
    {
        pNew = new CRioOverCurrentCharA();
    }
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR_B)
    {
        pNew = new CRioOverCurrentCharB();
    }
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR_P)
    {
        pNew = new CRioOverCurrentCharP();
    }
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR_Q)
    {
        pNew = new CRioOverCurrentCharQ();
    }
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR_K1)
    {
        pNew = new CRioOverCurrentCharK1();
    }
    if (nClassID == XRIOCLASSID_OVERCURRENT_CHAR_K2)
    {
        pNew = new CRioOverCurrentCharK2();
    }

    return pNew;
}

void CRioOverCurrentChar::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strOverCurrentInfo;
    strOverCurrentInfo.Format(_T("OverCurrent Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strOverCurrentInfo, 0, 0, htiParent);
    pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}
