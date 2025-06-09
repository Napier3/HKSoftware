// OverCurrentCharK1.cpp: 实现文件
//

#include "stdafx.h"

#include "RioOverCurrentCharK1.h"

// COverCurrentCharK1

CRioOverCurrentCharK1::CRioOverCurrentCharK1()
{
	//初始化属性
	m_strValue = _T("");
	m_strValueFormula = _T("");
    m_strType = _T("");
    m_strRefParam = _T("");

}

CRioOverCurrentCharK1::~CRioOverCurrentCharK1()
{
}

long CRioOverCurrentCharK1::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);

	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetElementText(pXmlKeys->m_strValueFormulaKey, oNode, m_strValueFormula);
    xml_GetElementText(pXmlKeys->m_strRefParamKey, oNode, m_strRefParam);

	return 0;
}

long CRioOverCurrentCharK1::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);

	xml_SetElementText(pXmlKeys->m_strValueKey, oXMLDoc, oElement, m_strValue);
	xml_SetElementText(pXmlKeys->m_strValueFormulaKey, oXMLDoc, oElement, m_strValueFormula);
    xml_SetElementText(pXmlKeys->m_strRefParamKey, oXMLDoc, oElement, m_strRefParam);

	return 0;
}

long CRioOverCurrentCharK1::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRioOverCurrentCharK1::InitAfterRead()
{

}

BOOL CRioOverCurrentCharK1::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioOverCurrentCharK1 *p = (CRioOverCurrentCharK1*)pObj;

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

BOOL CRioOverCurrentCharK1::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioOverCurrentCharK1 *p = (CRioOverCurrentCharK1*)pDest;

	p->m_strValue = m_strValue;
	p->m_strValueFormula = m_strValueFormula;
    p->m_strRefParam = m_strRefParam;

	return TRUE;
}

CBaseObject* CRioOverCurrentCharK1::Clone()
{
    CRioOverCurrentCharK1 *p = new CRioOverCurrentCharK1();
	Copy(p);
	return p;
}

BOOL CRioOverCurrentCharK1::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_VALUEREFLIST
	)
	{
		return TRUE;
	}
	
	return FALSE;
}

CExBaseObject* CRioOverCurrentCharK1::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

     if (strClassID == pXmlKeys->m_strValueRefListKey)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

CExBaseObject* CRioOverCurrentCharK1::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_VALUEREFLIST)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

void CRioOverCurrentCharK1::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
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
