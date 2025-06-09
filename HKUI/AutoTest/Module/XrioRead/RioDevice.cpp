// CRioDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioObjectCfg.h"
#include "RioDevice.h"


// CRioDevice

CRioDevice::CRioDevice()
{
	//初始化属性
//    m_strName = _T("Device节点");
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioDevice::~CRioDevice()
{
}

long CRioDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
	return 0;
}

long CRioDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
   xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


	return 0;
}

long CRioDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRioDevice *p = (CRioDevice*)pObj;


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

BOOL CRioDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioDevice *p = (CRioDevice*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioDevice::Clone()
{
	CRioDevice *p = new CRioDevice();
	Copy(p);
	return p;
}

BOOL CRioDevice::CanPaste(UINT nClassID)
{
	if (nClassID == XRIOCLASSID_DEVICE ||
	    nClassID == XRIOCLASSID_NAMEPLATE ||
	    nClassID == XRIOCLASSID_LOCATION ||
        nClassID == XRIOCLASSID_NOMINALVALUES ||
        nClassID == XRIOCLASSID_RESIDUALFACTORS ||
        nClassID == XRIOCLASSID_LIMITS ||
        nClassID == XRIOCLASSID_MISC
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strNameplateKey)
	{
        pNew = new CRioNameplate();
	}
    else if (strClassID == pXmlKeys->m_strLocationKey)
	{
        pNew = new CRioLocation();
	}
    else if (strClassID == pXmlKeys->m_strNominalValuesKey)
	{
        pNew = new CRioNominalValues();
	}
    else if (strClassID == pXmlKeys->m_strResidualFactorsKey)
    {
        pNew = new CRioResidualFactors();
    }
    else if (strClassID == pXmlKeys->m_strLimitsKey)
    {
        pNew = new CRioLimits();
    }
    else if (strClassID == pXmlKeys->m_strMiscKey)
    {
        pNew = new CRioMisc();
    }

	return pNew;
}

CExBaseObject* CRioDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_NAMEPLATE)
	{
        pNew = new CRioNameplate();
	}
    else if (nClassID == XRIOCLASSID_LOCATION)
	{
        pNew = new CRioLocation();
	}
    else if (nClassID == XRIOCLASSID_NOMINALVALUES)
	{
        pNew = new CRioNominalValues();
	}
    else if (nClassID == XRIOCLASSID_RESIDUALFACTORS)
    {
        pNew = new CRioResidualFactors();
    }
    else if (nClassID == XRIOCLASSID_LIMITS)
    {
        pNew = new CRioLimits();
    }
    else if (nClassID == XRIOCLASSID_MISC)
    {
        pNew = new CRioMisc();
    }

	return pNew;
}

void CRioDevice::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strDeviceInfo;
    strDeviceInfo.Format(_T("Device Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strDeviceInfo, 0, 0, htiParent);
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
