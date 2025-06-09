// TimeMultiplier.cpp : 实现文件
//

#include "stdafx.h"
#include "RioTimeMultiplier.h"



// CTimeMultiplier

CRioTimeMultiplier::CRioTimeMultiplier()
{
	//初始化属性
//        m_strName = _T("TimeMultiplier节点");
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioTimeMultiplier::~CRioTimeMultiplier()
{
}

long CRioTimeMultiplier::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	return 0;
}

long CRioTimeMultiplier::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);


	return 0;
}

long CRioTimeMultiplier::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CRioTimeMultiplier::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRioTimeMultiplier *p = (CRioTimeMultiplier*)pObj;


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

BOOL CRioTimeMultiplier::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioTimeMultiplier *p = (CRioTimeMultiplier*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioTimeMultiplier::Clone()
{
	CRioTimeMultiplier *p = new CRioTimeMultiplier();
	Copy(p);
	return p;
}

BOOL CRioTimeMultiplier::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_TIMEMULTIPLIER ||
        nClassID == XRIOCLASSID_TIMEMULTIPLIER_NOMVAL
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioTimeMultiplier::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strNomvalKey)
	{
        pNew = new CRioTimeMultiplierNomval();
	}

	return pNew;
}

CExBaseObject* CRioTimeMultiplier::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_TIMEMULTIPLIER_NOMVAL)
	{
        pNew = new CRioTimeMultiplierNomval();
	}
	return pNew;
}

void CRioTimeMultiplier::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strOperatingCurvesInfo;
    strOperatingCurvesInfo.Format(_T("OperatingCurves Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strOperatingCurvesInfo, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

