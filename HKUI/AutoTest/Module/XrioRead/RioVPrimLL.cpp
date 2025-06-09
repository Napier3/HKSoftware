// RioVPrimLL.cpp: ʵ���ļ�
//

#include "stdafx.h"

#include "RioVPrimLL.h"

// CRioVPrimLL

CRioVPrimLL::CRioVPrimLL()
{
	//��ʼ������
	m_strValue = _T("");
	m_strValueFormula = _T("");
    m_strType = _T("");
    m_strRefParam = _T("");

}

CRioVPrimLL::~CRioVPrimLL()
{
}

long CRioVPrimLL::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);

	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetElementText(pXmlKeys->m_strValueFormulaKey, oNode, m_strValueFormula);
    xml_GetElementText(pXmlKeys->m_strRefParamKey, oNode, m_strRefParam);

	return 0;
}

long CRioVPrimLL::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);

	xml_SetElementText(pXmlKeys->m_strValueKey, oXMLDoc, oElement, m_strValue);
	xml_SetElementText(pXmlKeys->m_strValueFormulaKey, oXMLDoc, oElement, m_strValueFormula);
    xml_SetElementText(pXmlKeys->m_strRefParamKey, oXMLDoc, oElement, m_strRefParam);

	return 0;
}

long CRioVPrimLL::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueFormula);
        BinarySerializeCalLen(oBinaryBuffer, m_strRefParam);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strValueFormula);
        BinarySerializeRead(oBinaryBuffer, m_strRefParam);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strValueFormula);
        BinarySerializeWrite(oBinaryBuffer, m_strRefParam);
	}
	return 0;
}

void CRioVPrimLL::InitAfterRead()
{

}

BOOL CRioVPrimLL::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRioVPrimLL *p = (CRioVPrimLL*)pObj;

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strValueFormula != p->m_strValueFormula)
	{
		return FALSE;
	}

    if(m_strRefParam != p->m_strRefParam)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRioVPrimLL::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRioVPrimLL *p = (CRioVPrimLL*)pDest;

	p->m_strValue = m_strValue;
	p->m_strValueFormula = m_strValueFormula;
    p->m_strRefParam = m_strRefParam;

	return TRUE;
}

CBaseObject* CRioVPrimLL::Clone()
{
	CRioVPrimLL *p = new CRioVPrimLL();
	Copy(p);
	return p;
}

BOOL CRioVPrimLL::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_VALUEREFLIST
	)
	{
		return TRUE;
	}
	
	return FALSE;
}

CExBaseObject* CRioVPrimLL::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

     if (strClassID == pXmlKeys->m_strValueRefListKey)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

CExBaseObject* CRioVPrimLL::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_VALUEREFLIST)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

void CRioVPrimLL::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
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
