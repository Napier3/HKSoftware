// CustomCurve.cpp : 实现文件
//

#include "stdafx.h"
#include "RioCustomCurve.h"


// CCustomCurve

CRioCustomCurve::CRioCustomCurve()
{
	//初始化属性
//    m_strName = _T("");
    m_strType = _T("");
	m_strBlockType = _T("");
//    m_strID = _T("");
	m_strEnabled = _T("");
}

CRioCustomCurve::~CRioCustomCurve()
{
}

long CRioCustomCurve::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	xml_GetAttibuteValue(pXmlKeys->m_strEnabledKey, oNode, m_strEnabled);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);

	return 0;
}

long CRioCustomCurve::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
    xml_SetAttributeValue(pXmlKeys->m_strEnabledKey, oElement, m_strEnabled);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


	return 0;
}

long CRioCustomCurve::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioCustomCurve::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioCustomCurve *p = (CRioCustomCurve*)pObj;


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

BOOL CRioCustomCurve::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioCustomCurve *p = (CRioCustomCurve*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;
	p->m_strEnabled = m_strEnabled;
	
	return TRUE;
}

CBaseObject* CRioCustomCurve::Clone()
{
    CRioCustomCurve *p = new CRioCustomCurve();
	Copy(p);
	return p;
}

BOOL CRioCustomCurve::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_CUSTOMCURVE ||
        nClassID == XRIOCLASSID_CURVEPOINTS || nClassID == XRIOCLASSID_ACTIVE
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioCustomCurve::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strCurvePointsKey)
	{
        pNew = new CRioCurvePoints();
	}
    if(strClassID == pXmlKeys->m_strActiveKey)
    {
        pNew = new CRioActive();
    }
	return pNew;
}

CExBaseObject* CRioCustomCurve::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

     if (nClassID == XRIOCLASSID_CURVEPOINTS)
	{
        pNew = new CRioCurvePoints();
	}
    if(nClassID == XRIOCLASSID_ACTIVE)
    {
        pNew = new CRioActive();
    }
	return pNew;
}

void CRioCustomCurve::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strInverseParameterCurveInfo;
    strInverseParameterCurveInfo.Format(_T("InverseParameterCurve Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strInverseParameterCurveInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}


