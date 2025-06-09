//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XrioObjectCfg.cpp 

#include "stdafx.h"
#include "XrioObjectCfg.h"

// CXrioUnit

CXrioUnit::CXrioUnit()
{
	
}

CXrioUnit::~CXrioUnit()
{
}

long CXrioUnit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUnitDecimalPlacesKey, oNode, m_strDecimalPlaces);
	xml_GetElementText(pXmlKeys->m_strUnitKey, oNode, m_strUnit);

	return 0;
}

long CXrioUnit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUnitDecimalPlacesKey, oElement, m_strDecimalPlaces);
	xml_SetElementText(pXmlKeys->m_strUnitKey, oXMLDoc, oElement, m_strUnit);
	
	return 0;
}

long CXrioUnit::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDecimalPlaces);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDecimalPlaces);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDecimalPlaces);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
	}
	return 0;
}

void CXrioUnit::InitAfterRead()
{
}

BOOL CXrioUnit::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioUnit *p = (CXrioUnit*)pObj;

	if(m_strDecimalPlaces != p->m_strDecimalPlaces)
	{
		return FALSE;
	}
	
	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXrioUnit::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioUnit *p = (CXrioUnit*)pDest;

	p->m_strDecimalPlaces = m_strDecimalPlaces;
	p->m_strUnit = m_strUnit;
	
	return TRUE;
}

CBaseObject* CXrioUnit::Clone()
{
	CXrioUnit *p = new CXrioUnit();
	Copy(p);
	return p;
}

long CXrioUnit::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 50);
	pListCtrl->InsertColumn(1, _T("小数点位数"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("单位"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CXrioUnit::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDecimalPlaces);
	pListCtrl->SetItemText(lItemIndex, 2, m_strUnit);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
 
	return 0;
}

// CXrioRefParam

CXrioRefParam::CXrioRefParam()
{
	
}

CXrioRefParam::~CXrioRefParam()
{
}

long CXrioRefParam::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRefIdKey, oNode, m_strRefID);
	xml_GetElementText(pXmlKeys->m_strRefParamKey, oNode, m_strRefParam);
	
	return 0;
}

long CXrioRefParam::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRefIdKey, oElement, m_strRefID);
	xml_SetElementText(pXmlKeys->m_strRefParamKey, oXMLDoc, oElement, m_strRefParam);

	return 0;
}

long CXrioRefParam::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strRefID);
		BinarySerializeCalLen(oBinaryBuffer, m_strRefParam);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strRefID);
		BinarySerializeRead(oBinaryBuffer, m_strRefParam);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strRefID);
		BinarySerializeWrite(oBinaryBuffer, m_strRefParam);
	}
	return 0;
}

void CXrioRefParam::InitAfterRead()
{
}

BOOL CXrioRefParam::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioRefParam *p = (CXrioRefParam*)pObj;

	if(m_strRefID != p->m_strRefID)
	{
		return FALSE;
	}

	if(m_strRefParam != p->m_strRefParam)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXrioRefParam::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioRefParam *p = (CXrioRefParam*)pDest;
	p->m_strRefID = m_strRefID;
	p->m_strRefParam = m_strRefParam;
	
	return TRUE;
}

CBaseObject* CXrioRefParam::Clone()
{
	CXrioRefParam *p = new CXrioRefParam();
	Copy(p);
	return p;
}

long CXrioRefParam::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 50);
	pListCtrl->InsertColumn(1, _T("参数ID"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("参数值"));
	pListCtrl->SetColumnWidth(2, 120);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CXrioRefParam::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strRefID);
	pListCtrl->SetItemText(lItemIndex, 2, m_strRefParam);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);

	return 0;
}

// CXrioRefEnum

CXrioRefEnum::CXrioRefEnum()
{
	
}

CXrioRefEnum::~CXrioRefEnum()
{
}

long CXrioRefEnum::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRefIdKey, oNode, m_strRefID);
	xml_GetElementText(pXmlKeys->m_strRefEnumKey, oNode, m_strRefEnum);
	
	return 0;
}

long CXrioRefEnum::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRefIdKey, oElement, m_strRefID);
	xml_SetElementText(pXmlKeys->m_strRefEnumKey, oXMLDoc, oElement, m_strRefEnum);

	return 0;
}

long CXrioRefEnum::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strRefID);
		BinarySerializeCalLen(oBinaryBuffer, m_strRefEnum);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strRefID);
		BinarySerializeRead(oBinaryBuffer, m_strRefEnum);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strRefID);
		BinarySerializeWrite(oBinaryBuffer, m_strRefEnum);
	}
	return 0;
}

void CXrioRefEnum::InitAfterRead()
{
}

BOOL CXrioRefEnum::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioRefEnum *p = (CXrioRefEnum*)pObj;

	if(m_strRefID != p->m_strRefID)
	{
		return FALSE;
	}

	if(m_strRefEnum != p->m_strRefEnum)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXrioRefEnum::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioRefEnum *p = (CXrioRefEnum*)pDest;
	p->m_strRefID = m_strRefID;
	p->m_strRefEnum = m_strRefEnum;
	
	return TRUE;
}

CBaseObject* CXrioRefEnum::Clone()
{
	CXrioRefEnum *p = new CXrioRefEnum();
	Copy(p);
	return p;
}

long CXrioRefEnum::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 50);
	pListCtrl->InsertColumn(1, _T("参数ID"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("参数值"));
	pListCtrl->SetColumnWidth(2, 120);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CXrioRefEnum::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strRefID);
	pListCtrl->SetItemText(lItemIndex, 2, m_strRefEnum);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);

	return 0;
}

// CXrioEnumValue

CXrioEnumValue::CXrioEnumValue()
{

}

CXrioEnumValue::~CXrioEnumValue()
{
}

long CXrioEnumValue::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strEnumIdKey, oNode, m_strEnumId);
	xml_GetAttibuteValue(pXmlKeys->m_strEnumIdKey, oNode, m_strID);
	xml_GetCDATA(oNode, m_strName);

	return 0;
}

long CXrioEnumValue::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strEnumIdKey, oElement, m_strEnumId);
//	xml_SetAttributeValue(pXmlKeys->m_strEnumIdKey, oElement, m_strID);
	xml_SetCDATA(oXMLDoc, oElement, m_strName);

	return 0;
}

long CXrioEnumValue::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strEnumId);
		//BinarySerializeCalLen(oBinaryBuffer, m_strRefEnum);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strEnumId);
		//BinarySerializeRead(oBinaryBuffer, m_strRefEnum);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strEnumId);
		//BinarySerializeWrite(oBinaryBuffer, m_strRefEnum);
	}
	return 0;
}

void CXrioEnumValue::InitAfterRead()
{
}

BOOL CXrioEnumValue::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioEnumValue *p = (CXrioEnumValue*)pObj;

	if(m_strEnumId != p->m_strEnumId)
	{
		return FALSE;
	}

	//if(m_strRefEnum != p->m_strRefEnum)
	//{
	//	return FALSE;
	//}

	return TRUE;
}

BOOL CXrioEnumValue::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioEnumValue *p = (CXrioEnumValue*)pDest;
	p->m_strEnumId = m_strEnumId;
	//p->m_strRefEnum = m_strRefEnum;

	return TRUE;
}

CBaseObject* CXrioEnumValue::Clone()
{
	CXrioEnumValue *p = new CXrioEnumValue();
	Copy(p);
	return p;
}