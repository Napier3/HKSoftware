// CRioNominalValues.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioObjectCfg.h"
#include "RioNominalValues.h"


// CRioNominalValues

CRioNominalValues::CRioNominalValues()
{
	//初始化属性
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioNominalValues::~CRioNominalValues()
{
}

long CRioNominalValues::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	return 0;
}

long CRioNominalValues::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);


	return 0;
}

long CRioNominalValues::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioNominalValues::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRioNominalValues *p = (CRioNominalValues*)pObj;


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

BOOL CRioNominalValues::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioNominalValues *p = (CRioNominalValues*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioNominalValues::Clone()
{
	CRioNominalValues *p = new CRioNominalValues();
	Copy(p);
	return p;
}

BOOL CRioNominalValues::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_NOMINALVALUES ||
        nClassID == XRIOCLASSID_PHASES ||
        nClassID == XRIOCLASSID_FNOM ||
        nClassID == XRIOCLASSID_VNOM ||
        nClassID == XRIOCLASSID_VPRIM_LL ||
        nClassID == XRIOCLASSID_INOM ||
        nClassID == XRIOCLASSID_IPRIM
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioNominalValues::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strPhasesKey)
	{
        pNew = new CRioPhases();
	}
    else if (strClassID == pXmlKeys->m_strFNomKey)
	{
        pNew = new CRioFNom();
	}
    else if (strClassID == pXmlKeys->m_strVNomKey)
	{
        pNew = new CRioVNom();
	}
    else if (strClassID == pXmlKeys->m_strVPrimLLKey)
    {
        pNew = new CRioVPrimLL();
    }
    else if (strClassID == pXmlKeys->m_strINomKey)
    {
        pNew = new CRioINom();
    }
    else if (strClassID == pXmlKeys->m_strIPrimKey)
    {
        pNew = new CRioIPrim();
    }

	return pNew;
}

CExBaseObject* CRioNominalValues::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_PHASES)
	{
        pNew = new CRioPhases();
	}
    else if (nClassID == XRIOCLASSID_FNOM)
	{
        pNew = new CRioFNom();
	}
    else if (nClassID == XRIOCLASSID_VNOM)
	{
        pNew = new CRioVNom();
	}
    else if (nClassID == XRIOCLASSID_VPRIM_LL)
    {
        pNew = new CRioVPrimLL();
    }
    else if (nClassID == XRIOCLASSID_INOM)
    {
        pNew = new CRioINom();
    }
    else if (nClassID == XRIOCLASSID_IPRIM)
    {
        pNew = new CRioIPrim();
    }

	return pNew;
}

void CRioNominalValues::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strNominalValues;
    strNominalValues.Format(_T("NominalValues Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strNominalValues, 0, 0, htiParent);
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
