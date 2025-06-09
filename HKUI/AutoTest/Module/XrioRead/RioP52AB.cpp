// RioP52AB.cpp: 实现文件
//

#include "stdafx.h"

#include "RioP52AB.h"

// CRioP52AB

CRioP52AB::CRioP52AB()
{
	//初始化属性
	m_strValue = _T("");
    m_strType = _T("");

}

CRioP52AB::~CRioP52AB()
{
}

long CRioP52AB::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);

	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CRioP52AB::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);

	xml_SetElementText(pXmlKeys->m_strValueKey, oXMLDoc, oElement, m_strValue);

	return 0;
}

long CRioP52AB::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRioP52AB::InitAfterRead()
{

}

BOOL CRioP52AB::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioP52AB *p = (CRioP52AB*)pObj;

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CRioP52AB::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioP52AB *p = (CRioP52AB*)pDest;

	p->m_strValue = m_strValue;

	return TRUE;
}

CBaseObject* CRioP52AB::Clone()
{
	CRioP52AB *p = new CRioP52AB();
	Copy(p);
	return p;
}

BOOL CRioP52AB::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_VALUEREFLIST
	)
	{
		return TRUE;
	}
	
	return FALSE;
}

CExBaseObject* CRioP52AB::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

     if (strClassID == pXmlKeys->m_strValueRefListKey)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

CExBaseObject* CRioP52AB::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_VALUEREFLIST)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

void CRioP52AB::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
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
