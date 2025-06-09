// Arc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RioArc.h"


// CRioArc

CRioArc::CRioArc()
{
    //��ʼ������
//    m_strName = _T("Arc�ڵ�");
    m_strType = _T("");
    m_strBlockType = _T("");
//    m_strID = _T("");
	m_strEnabled = _T("");
}

CRioArc::~CRioArc()
{
}

long CRioArc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
    xml_GetAttibuteValue(pXmlKeys->m_strEnabledKey, oNode, m_strEnabled);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
    return 0;
}

long CRioArc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
	xml_SetAttributeValue(pXmlKeys->m_strEnabledKey, oElement, m_strEnabled);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


    return 0;
}

long CRioArc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioArc::IsEqualOwn(CBaseObject* pObj)
{
    if(this == pObj)
    {
        return TRUE;
    }

    CRioArc *p = (CRioArc*)pObj;


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

BOOL CRioArc::CopyOwn(CBaseObject* pDest)
{
    if(this == pDest)
    {
        return TRUE;
    }

    CRioArc *p = (CRioArc*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;
	p->m_strEnabled = m_strEnabled;

    return TRUE;
}

CBaseObject* CRioArc::Clone()
{
    CRioArc *p = new CRioArc();
    Copy(p);
    return p;
}

BOOL CRioArc::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_ARC ||
            nClassID == XRIOCLASSID_REFPOINT_MAG ||
            nClassID == XRIOCLASSID_REFPOINT_ANGLE ||
            nClassID == XRIOCLASSID_REFPOINT_RADIUS ||
            nClassID == XRIOCLASSID_REFPOINT_STARTANGLE ||
            nClassID == XRIOCLASSID_REFPOINT_ENDANGLE ||
            nClassID == XRIOCLASSID_REFPOINT_DIR
            )
    {
        return TRUE;
    }
    return FALSE;
}

CExBaseObject* CRioArc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
    CExBaseObject *pNew  = NULL;
    CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

 if (strClassID == pXmlKeys->m_strRefPointMagKey)
    {
        pNew = new CRioRefPointMag();
    }
 else if (strClassID == pXmlKeys->m_strRefPointAngleKey)
 {
     pNew = new CRioRefPointAngle();
 }
 else if (strClassID == pXmlKeys->m_strRadiusKey)
 {
     pNew = new CRioRadius();
 }
 else if (strClassID == pXmlKeys->m_strStartAngleKey)
 {
     pNew = new CRioStartAngle();
 }
 else if (strClassID == pXmlKeys->m_strEndAngleKey)
 {
     pNew = new CRioEndAngle();
 }
 else if (strClassID == pXmlKeys->m_strDirKey)
 {
     pNew = new CRioDir();
 }

    return pNew;
}

CExBaseObject* CRioArc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
    CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_REFPOINT_MAG)
    {
        pNew = new CRioRefPointMag();
    }
   else if (nClassID == XRIOCLASSID_REFPOINT_ANGLE)
    {
        pNew = new CRioRefPointAngle();
    }
    else if (nClassID == XRIOCLASSID_REFPOINT_RADIUS)
    {
        pNew = new CRioRadius();
    }
    else if (nClassID == XRIOCLASSID_REFPOINT_STARTANGLE)
    {
        pNew = new CRioStartAngle();
    }
    else if (nClassID == XRIOCLASSID_REFPOINT_ENDANGLE)
    {
        pNew = new CRioEndAngle();
    }
    else if (nClassID == XRIOCLASSID_REFPOINT_DIR)
    {
        pNew = new CRioDir();
    }

    return pNew;
}

void CRioArc::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strArcInfo;
    strArcInfo.Format(_T("ArcType = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strArcInfo, 0, 0, htiParent);
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
