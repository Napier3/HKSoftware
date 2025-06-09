// RioININOM.cpp: 实现文件
//

#include "stdafx.h"

#include "RioININOM.h"

// CRioININOM

CRioININOM::CRioININOM()
{
	//初始化属性
	m_strValue = _T("");
    m_strType = _T("");

}

CRioININOM::~CRioININOM()
{
}

long CRioININOM::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);

	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CRioININOM::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);

	xml_SetElementText(pXmlKeys->m_strValueKey, oXMLDoc, oElement, m_strValue);

	return 0;
}

long CRioININOM::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRioININOM::InitAfterRead()
{

}

BOOL CRioININOM::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioININOM *p = (CRioININOM*)pObj;

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CRioININOM::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioININOM *p = (CRioININOM*)pDest;

	p->m_strValue = m_strValue;

	return TRUE;
}

CBaseObject* CRioININOM::Clone()
{
	CRioININOM *p = new CRioININOM();
	Copy(p);
	return p;
}

BOOL CRioININOM::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_VALUEREFLIST
	)
	{
		return TRUE;
	}
	
	return FALSE;
}

CExBaseObject* CRioININOM::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

     if (strClassID == pXmlKeys->m_strValueRefListKey)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

CExBaseObject* CRioININOM::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_VALUEREFLIST)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

void CRioININOM::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
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
