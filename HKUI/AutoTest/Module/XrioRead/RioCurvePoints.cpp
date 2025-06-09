// CurvePoints.cpp : 实现文件
//

#include "stdafx.h"
#include "RioCurvePoints.h"



// CRioCurvePoints

CRioCurvePoints::CRioCurvePoints()
{
	//初始化属性
//        m_strName = _T("CurvePoints节点");
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioCurvePoints::~CRioCurvePoints()
{
}

long CRioCurvePoints::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	return 0;
}

long CRioCurvePoints::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);


	return 0;
}

long CRioCurvePoints::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CRioCurvePoints::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioCurvePoints *p = (CRioCurvePoints*)pObj;


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

BOOL CRioCurvePoints::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioCurvePoints *p = (CRioCurvePoints*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioCurvePoints::Clone()
{
    CRioCurvePoints *p = new CRioCurvePoints();
	Copy(p);
	return p;
}

BOOL CRioCurvePoints::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_CURVEPOINTS ||
        nClassID == XRIOCLASSID_CURVEPOINT
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioCurvePoints::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strCurvePointKey)
	{
        pNew = new CRioCurvePoint();
	}

	return pNew;
}

CExBaseObject* CRioCurvePoints::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_CURVEPOINT)
	{
        pNew = new CRioCurvePoint();
	}

	return pNew;
}

void CRioCurvePoints::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strOperatingCurvesInfo;
    strOperatingCurvesInfo.Format(_T("OperatingCurves Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strOperatingCurvesInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

