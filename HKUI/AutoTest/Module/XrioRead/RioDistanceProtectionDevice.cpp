// DistanceProtectionDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "RioDistanceProtectionDevice.h"



// CDistanceProtectionDevice

CRioDistanceProtectionDevice::CRioDistanceProtectionDevice()
{
	//初始化属性
//        m_strName = _T("DistanceProtectionDevice节点");
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioDistanceProtectionDevice::~CRioDistanceProtectionDevice()
{
}

long CRioDistanceProtectionDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	return 0;
}

long CRioDistanceProtectionDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);


	return 0;
}

long CRioDistanceProtectionDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CRioDistanceProtectionDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioDistanceProtectionDevice *p = (CRioDistanceProtectionDevice*)pObj;


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

BOOL CRioDistanceProtectionDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioDistanceProtectionDevice *p = (CRioDistanceProtectionDevice*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioDistanceProtectionDevice::Clone()
{
    CRioDistanceProtectionDevice *p = new CRioDistanceProtectionDevice();
	Copy(p);
	return p;
}

BOOL CRioDistanceProtectionDevice::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_PROTECTIONDEVICE ||
        nClassID == XRIOCLASSID_ZONES
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioDistanceProtectionDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strZonesKey)
	{
        pNew = new CRioZones();
	}

	return pNew;
}

CExBaseObject* CRioDistanceProtectionDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_ZONES)
	{
        pNew = new CRioZones();
	}

	return pNew;
}

void CRioDistanceProtectionDevice::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strZoneInfo;
    strZoneInfo.Format(_T("Zone Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strZoneInfo, 0, 0, htiParent);
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
