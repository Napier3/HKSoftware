// MhoShape.cpp : 实现文件
//

#include "stdafx.h"
#include "RioMhoShape.h"



// CMhoShape

CRioMhoShape::CRioMhoShape()
{
	//初始化属性
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioMhoShape::~CRioMhoShape()
{
}

long CRioMhoShape::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	return 0;
}

long CRioMhoShape::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);


	return 0;
}

long CRioMhoShape::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CRioMhoShape::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioMhoShape *p = (CRioMhoShape*)pObj;


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

BOOL CRioMhoShape::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioMhoShape *p = (CRioMhoShape*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioMhoShape::Clone()
{
    CRioMhoShape *p = new CRioMhoShape();
	Copy(p);
	return p;
}

BOOL CRioMhoShape::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_MHOSHAPE ||
        nClassID == XRIOCLASSID_ANGLE ||
        nClassID == XRIOCLASSID_REACH ||
        nClassID == XRIOCLASSID_OFFSET
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioMhoShape::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strAngleKey)
	{
        pNew = new CRioAngle();
	}
    if (strClassID == pXmlKeys->m_strReachKey)
    {
        pNew = new CRioMhoReach();
    }
    if (strClassID == pXmlKeys->m_strOffsetKey)
    {
        pNew = new CRioMhoOffset();
    }

	return pNew;
}

CExBaseObject* CRioMhoShape::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_ANGLE)
	{
        pNew = new CRioAngle();
	}
    if (nClassID == XRIOCLASSID_REACH)
    {
        pNew = new CRioMhoReach();
    }
    if (nClassID == XRIOCLASSID_OFFSET)
    {
        pNew = new CRioMhoOffset();
    }

	return pNew;
}

void CRioMhoShape::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strGenricShapeInfo;
    strGenricShapeInfo.Format(_T("GenricShape Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strGenricShapeInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

