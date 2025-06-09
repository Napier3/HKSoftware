// RioTolerances.cpp : 实现文件
//

#include "stdafx.h"
#include "RioTolerances.h"



// CRioTolerances

CRioTolerances::CRioTolerances()
{
	//初始化属性
	m_strType = _T("");
	m_strBlockType = _T("");
}

CRioTolerances::~CRioTolerances()
{
}

long CRioTolerances::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
	return 0;
}

long CRioTolerances::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);


	return 0;
}

long CRioTolerances::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CRioTolerances::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRioTolerances *p = (CRioTolerances*)pObj;


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

BOOL CRioTolerances::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioTolerances *p = (CRioTolerances*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
	
	return TRUE;
}

CBaseObject* CRioTolerances::Clone()
{
	CRioTolerances *p = new CRioTolerances();
	Copy(p);
	return p;
}

BOOL CRioTolerances::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_TOLERANCES ||
        nClassID == XRIOCLASSID_TTPL_VALID ||
        nClassID == XRIOCLASSID_TTOLPLUS ||
        nClassID == XRIOCLASSID_TTMI_VALID ||
        nClassID == XRIOCLASSID_TTOLMINUS ||
        nClassID == XRIOCLASSID_TTRL_VALID||
        nClassID == XRIOCLASSID_TTOLREL||
        nClassID == XRIOCLASSID_ZTRL_VALID||
        nClassID == XRIOCLASSID_ZTOLREL||
        nClassID == XRIOCLASSID_ZTAB_VALID||
        nClassID == XRIOCLASSID_ZTOLABS
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioTolerances::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strTTPLValidKey)
	{
        pNew = new CRioTTPLValid();
	}
    if (strClassID == pXmlKeys->m_strTTOLPlusKey)
    {
        pNew = new CRioTTOLPlus();
    }
    if (strClassID == pXmlKeys->m_strTTMIValidKey)
    {
        pNew = new CRioTTMIValid();
    }
    if (strClassID == pXmlKeys->m_strTTOLMinusKey)
    {
        pNew = new CRioTTOLMinus();
    }
    if (strClassID == pXmlKeys->m_strTTRLValidKey)
    {
        pNew = new CRioTTRLValid();
    }
    if (strClassID == pXmlKeys->m_strTTOLRelKey)
    {
        pNew = new CRioTTOLRel();
    }
    if (strClassID == pXmlKeys->m_strZTRLValidKey)
    {
        pNew = new CRioZTRLValid();
    }
    if (strClassID == pXmlKeys->m_strZTOLRelKey)
    {
        pNew = new CRioZTOLRel();
    }
    if (strClassID == pXmlKeys->m_strZTABValidKey)
    {
        pNew = new CRioZTABValid();
    }
    if (strClassID == pXmlKeys->m_strZTOLAbsKey)
    {
        pNew = new CRioZTOLAbs();
    }

	return pNew;
}

CExBaseObject* CRioTolerances::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_TTPL_VALID)
    {
        pNew = new CRioTTPLValid();
	}
    if (nClassID == XRIOCLASSID_TTOLPLUS)
    {
        pNew = new CRioTTOLPlus();
    }
    if (nClassID == XRIOCLASSID_TTMI_VALID)
    {
        pNew = new CRioTTMIValid();
    }
    if (nClassID == XRIOCLASSID_TTOLMINUS)
    {
        pNew = new CRioTTOLMinus();
    }
    if (nClassID == XRIOCLASSID_TTRL_VALID)
    {
        pNew = new CRioTTRLValid();
    }
    if (nClassID == XRIOCLASSID_TTOLREL)
    {
        pNew = new CRioTTOLRel();
    }
    if (nClassID == XRIOCLASSID_ZTRL_VALID)
    {
        pNew = new CRioZTRLValid();
    }
    if (nClassID == XRIOCLASSID_ZTOLREL)
    {
        pNew = new CRioZTOLRel();
    }
    if (nClassID == XRIOCLASSID_ZTAB_VALID)
    {
        pNew = new CRioZTABValid();
    }
    if (nClassID == XRIOCLASSID_ZTOLABS)
    {
        pNew = new CRioZTOLAbs();
    }

	return pNew;
}

void CRioTolerances::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strZonesInfo;
    strZonesInfo.Format(_T("Zones Type = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strZonesInfo, 0, 0, htiParent);
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
