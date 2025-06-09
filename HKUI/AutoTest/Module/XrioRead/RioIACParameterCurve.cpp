// IACParameterCurve.cpp : 实现文件
//

#include "stdafx.h"
#include "RioIACParameterCurve.h"


// CIACParameterCurve

CRioIACParameterCurve::CRioIACParameterCurve()
{
	//初始化属性
//    m_strName = _T("");
	m_strType = _T("");
	m_strBlockType = _T("");
//    m_strID = _T("");
	m_strEnabled = _T("");
}

CRioIACParameterCurve::~CRioIACParameterCurve()
{
}

long CRioIACParameterCurve::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	xml_GetAttibuteValue(pXmlKeys->m_strEnabledKey, oNode, m_strEnabled);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);

	return 0;
}

long CRioIACParameterCurve::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
    xml_SetAttributeValue(pXmlKeys->m_strEnabledKey, oElement, m_strEnabled);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


	return 0;
}

long CRioIACParameterCurve::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioIACParameterCurve::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioIACParameterCurve *p = (CRioIACParameterCurve*)pObj;


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

BOOL CRioIACParameterCurve::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioIACParameterCurve *p = (CRioIACParameterCurve*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;
	p->m_strEnabled = m_strEnabled;
	
	return TRUE;
}

CBaseObject* CRioIACParameterCurve::Clone()
{
    CRioIACParameterCurve *p = new CRioIACParameterCurve();
	Copy(p);
	return p;
}

BOOL CRioIACParameterCurve::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_IACPARAMETERCURVE||
        nClassID == XRIOCLASSID_PARAMETERA||
        nClassID == XRIOCLASSID_PARAMETERB||
        nClassID == XRIOCLASSID_PARAMETERC||
        nClassID == XRIOCLASSID_PARAMETERD||
        nClassID == XRIOCLASSID_PARAMETERE||
        nClassID == XRIOCLASSID_ACTIVE||
        nClassID == XRIOCLASSID_STANDARDCURVE_NAME
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioIACParameterCurve::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strParameterAKey)
	{
        pNew = new CRioParameterA();
	}
    if (strClassID == pXmlKeys->m_strParameterBKey)
    {
        pNew = new CRioParameterB();
    }
    if (strClassID == pXmlKeys->m_strParameterCKey)
    {
        pNew = new CRioParameterC();
    }
    if (strClassID == pXmlKeys->m_strParameterDKey)
    {
        pNew = new CRioParameterD();
    }
    if (strClassID == pXmlKeys->m_strParameterEKey)
    {
        pNew = new CRioParameterE();
    }
    if (strClassID == pXmlKeys->m_strActiveKey)
    {
        pNew = new CRioActive();
    }
    if (strClassID == pXmlKeys->m_strStandardCurveNameKey)
    {
        pNew = new CRioStandardCurveName();
    }

	return pNew;
}

CExBaseObject* CRioIACParameterCurve::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

     if (nClassID == XRIOCLASSID_PARAMETERA)
	{
        pNew = new CRioParameterA();
	}
     if (nClassID == XRIOCLASSID_PARAMETERB)
     {
         pNew = new CRioParameterB();
     }
     if (nClassID == XRIOCLASSID_PARAMETERC)
     {
         pNew = new CRioParameterC();
     }
     if (nClassID == XRIOCLASSID_PARAMETERD)
     {
         pNew = new CRioParameterD();
     }
     if (nClassID == XRIOCLASSID_PARAMETERE)
     {
         pNew = new CRioParameterE();
     }
     if (nClassID == XRIOCLASSID_ACTIVE)
     {
         pNew = new CRioActive();
     }
     if (nClassID == XRIOCLASSID_STANDARDCURVE_NAME)
     {
         pNew = new CRioStandardCurveName();
     }

	return pNew;
}

void CRioIACParameterCurve::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strInverseParameterCurveInfo;
    strInverseParameterCurveInfo.Format(_T("InverseParameterCurve Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strInverseParameterCurveInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}


