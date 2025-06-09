// RioTripTime.cpp: 实现文件
//

#include "stdafx.h"

#include "RioTripTime.h"

// CRioTripTime

CRioTripTime::CRioTripTime()
{
	//初始化属性
	m_strValue = _T("");
    m_strType = _T("");

}

CRioTripTime::~CRioTripTime()
{
}

long CRioTripTime::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);

	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CRioTripTime::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);

	xml_SetElementText(pXmlKeys->m_strValueKey, oXMLDoc, oElement, m_strValue);

	return 0;
}

long CRioTripTime::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CRioTripTime::InitAfterRead()
{

}

BOOL CRioTripTime::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioTripTime *p = (CRioTripTime*)pObj;

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CRioTripTime::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioTripTime *p = (CRioTripTime*)pDest;

	p->m_strValue = m_strValue;

	return TRUE;
}

CBaseObject* CRioTripTime::Clone()
{
	CRioTripTime *p = new CRioTripTime();
	Copy(p);
	return p;
}

BOOL CRioTripTime::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_VALUEREFLIST
	)
	{
		return TRUE;
	}
	
	return FALSE;
}

CExBaseObject* CRioTripTime::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

     if (strClassID == pXmlKeys->m_strValueRefListKey)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

CExBaseObject* CRioTripTime::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_VALUEREFLIST)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

void CRioTripTime::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{

}

//BOOL CRioDeviceMode::GetParameterFullPath(CString &strValue)
//{
//	CExBaseObject *pParent = (CExBaseObject*)GetParent();
//	CString strTmp;
//	strTmp = m_strType;

//	while(pParent != NULL)
//	{
//		if ((pParent->GetClassID() != XRIOCLASSID_DEVICE_MODEL)&&(pParent->GetClassID() != XRIOCLASSID_NAMEPLATE))
//		{
//			break;
//		}

//		strValue.Format(_T("%s$%s"),pParent->m_strID,strTmp);
//		strTmp = strValue;
//		pParent = (CExBaseObject*)pParent->GetParent();
//	}

//	return TRUE;
//}

//BOOL CRioDeviceMode::GetParameterValue(CString &strValue)
//{
//	strValue = m_strValue;

//	if (GetCount() == 0)
//	{
//		return TRUE;
//	}

//	BOOL bRet = FALSE;
//	POS pos_list = GetHeadPosition();
//	CExBaseList *pCurList = NULL;
//	CXrioEnumValue *pCurEnumValue = NULL;

//	while(pos_list)
//	{
//		pCurList = (CExBaseList *)GetNext(pos_list);

//		if (pCurList->GetClassID() == XRIOCLASSID_ENUMLIST)
//		{
//			pCurEnumValue = (CXrioEnumValue*)pCurList->FindByID(m_strValue);
//			strValue = pCurEnumValue->m_strName;
//			bRet = TRUE;
//			break;
//		}
//	}

//	return bRet;
//}
