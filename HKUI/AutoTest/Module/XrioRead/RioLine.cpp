// Line.cpp : 实现文件
//

#include "stdafx.h"
#include "RioLine.h"


// CLine

CRioLine::CRioLine()
{
	//初始化属性
//    m_strName = _T("Line节点");
	m_strType = _T("");
	m_strBlockType = _T("");
//    m_strID = _T("");
	m_strEnabled = _T("");
}

CRioLine::~CRioLine()
{
}

long CRioLine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
    xml_GetAttibuteValue(pXmlKeys->m_strEnabledKey, oNode, m_strEnabled);
    xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
	return 0;
}

long CRioLine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
	xml_SetAttributeValue(pXmlKeys->m_strEnabledKey, oElement, m_strEnabled);
    xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
    xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);


	return 0;
}

long CRioLine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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


BOOL CRioLine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioLine *p = (CRioLine*)pObj;


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

BOOL CRioLine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioLine *p = (CRioLine*)pDest;

    p->m_strType = m_strType;
    p->m_strBlockType = m_strBlockType;
    p->m_strID = m_strID;
	p->m_strEnabled = m_strEnabled;
	
	return TRUE;
}

CBaseObject* CRioLine::Clone()
{
    CRioLine *p = new CRioLine();
	Copy(p);
	return p;
}

BOOL CRioLine::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_LINE ||
        nClassID == XRIOCLASSID_REFPOINT_R ||
        nClassID == XRIOCLASSID_REFPOINT_X ||
        nClassID == XRIOCLASSID_INSIDE ||
        nClassID == XRIOCLASSID_ANGLE
	)
	{
		return TRUE;
	}
	return FALSE;
}

CExBaseObject* CRioLine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
   if (strClassID == pXmlKeys->m_strRefPointRKey)
	{
        pNew = new CRioRefPointR();
	}
   else if (strClassID == pXmlKeys->m_strRefPointXKey)
   {
       pNew = new CRioRefPointX();
   }
  else if (strClassID == pXmlKeys->m_strAngleKey)
   {
       pNew = new CRioAngle();
   }
   else if (strClassID == pXmlKeys->m_strInsideKey)
   {
       pNew = new CRioInside();
   }

	return pNew;
}

CExBaseObject* CRioLine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

     if (nClassID == XRIOCLASSID_REFPOINT_R)
	{
        pNew = new CRioRefPointR();
	}
    else if (nClassID == XRIOCLASSID_REFPOINT_X)
     {
         pNew = new CRioRefPointX();
     }
   else  if (nClassID == XRIOCLASSID_ANGLE)
     {
         pNew = new CRioAngle();
     }
     else  if (nClassID == XRIOCLASSID_INSIDE)
     {
         pNew = new CRioInside();
     }

	return pNew;
}

void CRioLine::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
    CString strLineInfo;
    strLineInfo.Format(_T("LineInfoType = %s"),m_strType.GetString());
    m_dwItemData = (DWORD)pTreeCtrl->InsertItem(strLineInfo, 0, 0, htiParent);
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
