// TripChar.cpp : 实现文件
//

#include "stdafx.h"
#include "RioTripChar.h"


// CTripChar

CRioTripChar::CRioTripChar()
{
	//初始化属性
//    m_strName = _T("CripChar节点");
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioTripChar::~CRioTripChar()
{
}

long CRioTripChar::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
	return 0;
}

long CRioTripChar::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
   xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


	return 0;
}

long CRioTripChar::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioTripChar::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRioTripChar *p = (CRioTripChar*)pObj;


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

BOOL CRioTripChar::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioTripChar *p = (CRioTripChar*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioTripChar::Clone()
{
	CRioTripChar *p = new CRioTripChar();
	Copy(p);
	return p;
}

BOOL CRioTripChar::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_POINT ||
        nClassID == XRIOCLASSID_TRIPCHAR
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioTripChar::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strPointKey)
	{
        pNew = new CRioDiffPoint();
	}

	return pNew;
}

CExBaseObject* CRioTripChar::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_POINT)
	{
        pNew = new CRioDiffPoint();
	}

	return pNew;
}

void CRioTripChar::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strTripCharInfo;
    strTripCharInfo.Format(_T("TripChar Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strTripCharInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}


