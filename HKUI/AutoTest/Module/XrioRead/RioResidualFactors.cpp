// CRioResidualFactors.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioObjectCfg.h"
#include "RioResidualFactors.h"


// CRioResidualFactors

CRioResidualFactors::CRioResidualFactors()
{
	//初始化属性
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioResidualFactors::~CRioResidualFactors()
{
}

long CRioResidualFactors::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	return 0;
}

long CRioResidualFactors::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);


	return 0;
}

long CRioResidualFactors::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CRioResidualFactors::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRioResidualFactors *p = (CRioResidualFactors*)pObj;


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

BOOL CRioResidualFactors::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioResidualFactors *p = (CRioResidualFactors*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioResidualFactors::Clone()
{
	CRioResidualFactors *p = new CRioResidualFactors();
	Copy(p);
	return p;
}

BOOL CRioResidualFactors::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_RESIDUALFACTORS ||
        nClassID == XRIOCLASSID_VLNVN ||
        nClassID == XRIOCLASSID_ININOM
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioResidualFactors::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strVLNVNKey)
	{
        pNew = new CRioVLNVN();
	}
    else if (strClassID == pXmlKeys->m_strININOMKey)
	{
        pNew = new CRioININOM();
	}

	return pNew;
}

CExBaseObject* CRioResidualFactors::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_VLNVN)
	{
        pNew = new CRioVLNVN();
	}
    else if (nClassID == XRIOCLASSID_ININOM)
	{
        pNew = new CRioININOM();
	}

	return pNew;
}

void CRioResidualFactors::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strResidualFactors;
    strResidualFactors.Format(_T("ResidualFactors Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strResidualFactors, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

//CExBaseObject *CRioDevice::FindParaByName(const CString &strMap,const CString &strForeignId)
//{
//	CXrioCustomParameter *pParameter = NULL;
//	CExBaseObject *pCurObj = NULL;
//	CExBaseObject *pFind = FindOwnParaByName(strMap,strForeignId);

//	POS pos_para = GetHeadPosition();

//	while((pos_para)&&(pFind == NULL))
//	{
//		pCurObj = GetNext(pos_para);

//		if (pCurObj->GetClassID() == XRIOCLASSID_CUSTOMBLOCK)
//		{
//			pFind = ((CRioDevice*)pCurObj)->FindParaByName(strMap,strForeignId);
//		}
//	}

//	return pFind;
//}

//CExBaseObject *CRioDevice::FindParaByFullPath(const CString &strMap)
//{
//	CXrioCustomParameter *pParameter = NULL;
//	CExBaseObject *pCurObj = NULL;
//	CString strParaID,strMapPath;
//	long nIndex = strMap.Find('$');

//	if (nIndex == -1)
//	{
//		strParaID = strMap;
//		strMapPath = _T("");
//	}
//	else
//	{
//		strParaID = strMap.Left(nIndex);
//		strMapPath = strMap.Mid(nIndex+1);
//	}

//	CExBaseObject *pFind = FindByID(strParaID);

//	if (pFind == NULL)
//	{
//		return NULL;
//	}

//	if (pFind->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER)
//	{
//		return pFind;
//	}
//	else if (pFind->GetClassID() == XRIOCLASSID_CUSTOMBLOCK)
//	{
//		CRioDevice *pCurBlock = (CRioDevice*)pFind;
//		return pCurBlock->FindParaByFullPath(strMapPath);
//	}
//	else
//		return NULL;
//}

//CExBaseObject *CRioDevice::FindOwnParaByName(const CString &strMap,const CString &strForeignId)
//{
//	CXrioCustomParameter *pParameter = NULL;
//	CExBaseObject *pCurObj = NULL;
//	CExBaseObject *pFind = NULL;

//	POS pos_para = GetHeadPosition();

//	while(pos_para)
//	{
//		pCurObj = GetNext(pos_para);

//		if (pCurObj->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER)
//		{
//			pParameter = (CXrioCustomParameter *)pCurObj;

//			if ((pParameter->m_strID == strMap)&&((strForeignId.IsEmpty())||(pParameter->m_strForeignId == strForeignId)))
//			{
//				pFind = pParameter;
//				break;
//			}
//		}
//	}

//	return pFind;
//}
