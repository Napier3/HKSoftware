// XrioCustomParameter.cpp: 实现文件
//

#include "stdafx.h"

#include "XrioObjectCfg.h"
#include "XrioListCfg.h"
#include "XrioCustomParameter.h"

// CXrioCustomParameter

CXrioCustomParameter::CXrioCustomParameter()
{
	//初始化属性
	//m_strID = _T("");
	m_strEnabled = _T("true");
	m_strDescription = _T("");
	m_strForeignId = _T("");
	m_strDataType = _T("");
	m_strValue = _T("");
	m_strValueFormula = _T("");
	m_strMaxValue = _T("");
	m_strMinValue = _T("");
	m_strUnit = _T("");
}

CXrioCustomParameter::~CXrioCustomParameter()
{
}

long CXrioCustomParameter::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strEnabledKey, oNode, m_strEnabled);
	xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetElementText(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);
	xml_GetElementText(pXmlKeys->m_strForeignIdKey, oNode, m_strForeignId);
	xml_GetElementText(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetElementText(pXmlKeys->m_strValueFormulaKey, oNode, m_strValueFormula);
	xml_GetElementText(pXmlKeys->m_strMaxValueKey, oNode, m_strMaxValue);
	xml_GetElementText(pXmlKeys->m_strMinValueKey, oNode, m_strMinValue);
	xml_GetElementText(pXmlKeys->m_strUnitKey, oNode, m_strUnit);

	if (m_strEnabled == _T(""))
	{
		m_strEnabled = _T("true");
	}

	return 0;
}

long CXrioCustomParameter::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strEnabledKey, oElement, m_strEnabled);
	xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);
	xml_SetElementText(pXmlKeys->m_strDescriptionKey, oXMLDoc, oElement, m_strDescription);
	xml_SetElementText(pXmlKeys->m_strForeignIdKey, oXMLDoc, oElement, m_strForeignId);
	xml_SetElementText(pXmlKeys->m_strDataTypeKey, oXMLDoc, oElement, m_strDataType);
	xml_SetElementText(pXmlKeys->m_strValueKey, oXMLDoc, oElement, m_strValue);
	xml_SetElementText(pXmlKeys->m_strValueFormulaKey, oXMLDoc, oElement, m_strValueFormula);
	xml_SetElementText(pXmlKeys->m_strMaxValueKey, oXMLDoc, oElement, m_strMaxValue);
	xml_SetElementText(pXmlKeys->m_strMinValueKey, oXMLDoc, oElement, m_strMinValue);
	xml_SetElementText(pXmlKeys->m_strUnitKey, oXMLDoc, oElement, m_strUnit);

	return 0;
}

long CXrioCustomParameter::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_strEnabled);
		BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
		BinarySerializeCalLen(oBinaryBuffer, m_strForeignId);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueFormula);
		BinarySerializeCalLen(oBinaryBuffer, m_strMaxValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strMinValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_strEnabled);
		BinarySerializeRead(oBinaryBuffer, m_strDescription);
		BinarySerializeRead(oBinaryBuffer, m_strForeignId);
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strValueFormula);
		BinarySerializeRead(oBinaryBuffer, m_strMaxValue);
		BinarySerializeRead(oBinaryBuffer, m_strMinValue);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_strEnabled);
		BinarySerializeWrite(oBinaryBuffer, m_strDescription);
		BinarySerializeWrite(oBinaryBuffer, m_strForeignId);
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strValueFormula);
		BinarySerializeWrite(oBinaryBuffer, m_strMaxValue);
		BinarySerializeWrite(oBinaryBuffer, m_strMinValue);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
	}
	return 0;
}

void CXrioCustomParameter::InitAfterRead()
{

}

BOOL CXrioCustomParameter::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioCustomParameter *p = (CXrioCustomParameter*)pObj;

	/*if(m_strID != p->m_strID)
	{
		return FALSE;
	}*/

	if(m_strEnabled != p->m_strEnabled)
	{
		return FALSE;
	}

	if(m_strDescription != p->m_strDescription)
	{
		return FALSE;
	}

	if(m_strForeignId != p->m_strForeignId)
	{
		return FALSE;
	}

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strMaxValue != p->m_strMaxValue)
	{
		return FALSE;
	}

	if(m_strMinValue != p->m_strMinValue)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strValueFormula != p->m_strValueFormula)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXrioCustomParameter::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioCustomParameter *p = (CXrioCustomParameter*)pDest;

	//p->m_strID = m_strID;
	p->m_strEnabled = m_strEnabled;
	p->m_strDescription = m_strDescription;
	p->m_strForeignId = m_strForeignId;
	p->m_strDataType = m_strDataType;
	p->m_strMaxValue = m_strMaxValue;
	p->m_strMinValue = m_strMinValue;
	p->m_strValue = m_strValue;
	p->m_strValueFormula = m_strValueFormula;
	p->m_strUnit = m_strUnit;

	return TRUE;
}

CBaseObject* CXrioCustomParameter::Clone()
{
	CXrioCustomParameter *p = new CXrioCustomParameter();
	Copy(p);
	return p;
}

BOOL CXrioCustomParameter::CanPaste(UINT nClassID)
{
	if (nClassID == XRIOCLASSID_ENUMLIST ||
	    nClassID == XRIOCLASSID_ENABLEDREFLIST ||
	    nClassID == XRIOCLASSID_VALUEREFLIST
	)
	{
		return TRUE;
	}
	
	return FALSE;
}

CExBaseObject* CXrioCustomParameter::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strEnumListKey)
	{
		pNew = new CXrioEnumList();
	}
	else if (strClassID == pXmlKeys->m_strEnabledRefListKey)
	{
		pNew = new CXrioEnabledRefList();
	}
	else if (strClassID == pXmlKeys->m_strValueRefListKey)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

CExBaseObject* CXrioCustomParameter::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XRIOCLASSID_ENUMLIST)
	{
		pNew = new CXrioEnumList();
	}
	else if (nClassID == XRIOCLASSID_ENABLEDREFLIST)
	{
		pNew = new CXrioEnabledRefList();
	}
	else if (nClassID == XRIOCLASSID_VALUEREFLIST)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

void CXrioCustomParameter::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{

}

BOOL CXrioCustomParameter::GetParameterFullPath(CString &strValue)
{
	CExBaseObject *pParent = (CExBaseObject*)GetParent();
	CString strTmp;
	strTmp = m_strID;

	while(pParent != NULL)
	{
		if ((pParent->GetClassID() != XRIOCLASSID_CUSTOMPARAMETER)&&(pParent->GetClassID() != XRIOCLASSID_CUSTOMBLOCK))
		{
			break;
		}

		strValue.Format(_T("%s$%s"),pParent->m_strID,strTmp);
		strTmp = strValue;
		pParent = (CExBaseObject*)pParent->GetParent();
	}

	return TRUE;
}

BOOL CXrioCustomParameter::GetParameterValue(CString &strValue)
{
	strValue = m_strValue;

	if (GetCount() == 0)
	{
		return TRUE;
	}

	BOOL bRet = FALSE;
	POS pos_list = GetHeadPosition();
	CExBaseList *pCurList = NULL;
	CXrioEnumValue *pCurEnumValue = NULL;

	while(pos_list)
	{
		pCurList = (CExBaseList *)GetNext(pos_list);

		if (pCurList->GetClassID() == XRIOCLASSID_ENUMLIST)
		{
			pCurEnumValue = (CXrioEnumValue*)pCurList->FindByID(m_strValue);
			strValue = pCurEnumValue->m_strName;
			bRet = TRUE;
			break;
		}
	}

	return bRet;
}
