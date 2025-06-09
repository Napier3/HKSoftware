//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SchemaCheckSetting.cpp  CSchemaCheckSetting


#include "stdafx.h"
#include "SchemaCheckSetting.h"

CSchemaCheckSetting::CSchemaCheckSetting()
{
	//初始化属性
	m_nBeSelected = 0;

	//初始化成员变量
}

CSchemaCheckSetting::~CSchemaCheckSetting()
{
}

long CSchemaCheckSetting::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBeSelectedKey, oNode, m_nBeSelected);
	xml_GetAttibuteValue(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionTypeKey, oNode, m_strVersionType);
	xml_GetAttibuteValue(pXmlKeys->m_strXmlMethodKey, oNode, m_strXmlMethod);
	return 0;
}

long CSchemaCheckSetting::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strBeSelectedKey, oElement, m_nBeSelected);
	xml_SetAttributeValue(pXmlKeys->m_strDescriptionKey, oElement, m_strDescription);
	xml_SetAttributeValue(pXmlKeys->m_strVersionTypeKey, oElement, m_strVersionType);
	xml_SetAttributeValue(pXmlKeys->m_strXmlMethodKey, oElement, m_strXmlMethod);
	return 0;
}

long CSchemaCheckSetting::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nBeSelected);
		BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersionType);
		BinarySerializeCalLen(oBinaryBuffer, m_strXmlMethod);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nBeSelected);
		BinarySerializeRead(oBinaryBuffer, m_strDescription);
		BinarySerializeRead(oBinaryBuffer, m_strVersionType);
		BinarySerializeRead(oBinaryBuffer, m_strXmlMethod);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nBeSelected);
		BinarySerializeWrite(oBinaryBuffer, m_strDescription);
		BinarySerializeWrite(oBinaryBuffer, m_strVersionType);
		BinarySerializeWrite(oBinaryBuffer, m_strXmlMethod);
	}
	return 0;
}

void CSchemaCheckSetting::InitAfterRead()
{
}

BOOL CSchemaCheckSetting::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSchemaCheckSetting *p = (CSchemaCheckSetting*)pObj;

	if(m_nBeSelected != p->m_nBeSelected)
	{
		return FALSE;
	}

	if(m_strDescription != p->m_strDescription)
	{
		return FALSE;
	}

	if(m_strVersionType != p->m_strVersionType)
	{
		return FALSE;
	}

	if(m_strXmlMethod != p->m_strXmlMethod)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSchemaCheckSetting::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSchemaCheckSetting *p = (CSchemaCheckSetting*)pDest;

	p->m_nBeSelected = m_nBeSelected;
	p->m_strDescription = m_strDescription;
	p->m_strVersionType = m_strVersionType;
	p->m_strXmlMethod = m_strXmlMethod;
	return TRUE;
}

CBaseObject* CSchemaCheckSetting::Clone()
{
	CSchemaCheckSetting *p = new CSchemaCheckSetting();
	Copy(p);
	return p;
}

long CSchemaCheckSetting::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("BeSelected"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Description"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("VersionType"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("XmlMethod"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CSchemaCheckSetting::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	strTemp.Format(_T("%d"), m_nBeSelected);
	pListCtrl->SetItemText(lItemIndex, 1, strTemp);
	pListCtrl->SetItemText(lItemIndex, 2, m_strDescription);
	pListCtrl->SetItemText(lItemIndex, 3, m_strVersionType);
	pListCtrl->SetItemText(lItemIndex, 4, m_strXmlMethod);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

