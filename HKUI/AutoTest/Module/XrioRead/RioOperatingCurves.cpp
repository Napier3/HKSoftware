// OperatingCurves.cpp : 实现文件
//

#include "stdafx.h"
#include "RioOperatingCurves.h"



// COperatingCurves

CRioOperatingCurves::CRioOperatingCurves()
{
	//初始化属性
//        m_strName = _T("OperatingCurves节点");
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioOperatingCurves::~CRioOperatingCurves()
{
}

long CRioOperatingCurves::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	return 0;
}

long CRioOperatingCurves::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);


	return 0;
}

long CRioOperatingCurves::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CRioOperatingCurves::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioOperatingCurves *p = (CRioOperatingCurves*)pObj;


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

BOOL CRioOperatingCurves::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioOperatingCurves *p = (CRioOperatingCurves*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioOperatingCurves::Clone()
{
    CRioOperatingCurves *p = new CRioOperatingCurves();
	Copy(p);
	return p;
}

BOOL CRioOperatingCurves::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_OPERATINGCURVES ||
        nClassID == XRIOCLASSID_INVERSEPARAMETERCURVE ||
        nClassID == XRIOCLASSID_I2TPARAMETERCURVE ||
        nClassID == XRIOCLASSID_IACPARAMETERCURVE ||
        nClassID == XRIOCLASSID_CUSTOMCURVE ||
        nClassID ==  XRIOCLASSID_STANDARDCURVE
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioOperatingCurves::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strInverseParameterCurveKey)
	{
        pNew = new CRioInverseParameterCurve();
	}
    if (strClassID == pXmlKeys->m_strStandardCurveKey)
    {
        pNew = new CRioStandardCurve();
    }
    if (strClassID == pXmlKeys->m_strI2TParameterCurveKey)
    {
        pNew = new CRioI2TParameterCurve();
    }
    if (strClassID == pXmlKeys->m_strIACParameterCurveKey)
    {
        pNew = new CRioIACParameterCurve();
    }
    if (strClassID == pXmlKeys->m_strCustomCurveKey)
    {
        pNew = new CRioCustomCurve();
    }

	return pNew;
}

CExBaseObject* CRioOperatingCurves::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_INVERSEPARAMETERCURVE)
	{
        pNew = new CRioInverseParameterCurve();
	}
    if (nClassID == XRIOCLASSID_STANDARDCURVE)
    {
        pNew = new CRioStandardCurve();
    }
    if (nClassID == XRIOCLASSID_I2TPARAMETERCURVE)
    {
        pNew = new CRioI2TParameterCurve();
    }
    if (nClassID == XRIOCLASSID_CUSTOMCURVE)
    {
        pNew = new CRioCustomCurve();
    }
    if (nClassID == XRIOCLASSID_IACPARAMETERCURVE)
    {
        pNew = new CRioIACParameterCurve();
    }

	return pNew;
}

void CRioOperatingCurves::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strOperatingCurvesInfo;
    strOperatingCurvesInfo.Format(_T("OperatingCurves Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strOperatingCurvesInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

