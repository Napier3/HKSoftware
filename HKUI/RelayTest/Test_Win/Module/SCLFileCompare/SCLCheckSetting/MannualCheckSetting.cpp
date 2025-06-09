//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MannualCheckSetting.cpp  CMannualCheckSetting


#include "stdafx.h"
#include "MannualCheckSetting.h"

CMannualCheckSetting::CMannualCheckSetting()
{
	//初始化属性
	m_nBeSelected = 0;

	//初始化成员变量
}

CMannualCheckSetting::~CMannualCheckSetting()
{
}

long CMannualCheckSetting::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBeSelectedKey, oNode, m_nBeSelected);
	xml_GetAttibuteValue(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);
	xml_GetAttibuteValue(pXmlKeys->m_strTokenTypeKey, oNode, m_strTokenType);
	return 0;
}

long CMannualCheckSetting::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCSchemaCheckSettingObjectXmlRWKeys *pXmlKeys = (CCSchemaCheckSettingObjectXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strBeSelectedKey, oElement, m_nBeSelected);
	xml_SetAttributeValue(pXmlKeys->m_strDescriptionKey, oElement, m_strDescription);
	xml_SetAttributeValue(pXmlKeys->m_strTokenTypeKey, oElement, m_strTokenType);
	return 0;
}

long CMannualCheckSetting::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nBeSelected);
		BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
		BinarySerializeCalLen(oBinaryBuffer, m_strTokenType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nBeSelected);
		BinarySerializeRead(oBinaryBuffer, m_strDescription);
		BinarySerializeRead(oBinaryBuffer, m_strTokenType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nBeSelected);
		BinarySerializeWrite(oBinaryBuffer, m_strDescription);
		BinarySerializeWrite(oBinaryBuffer, m_strTokenType);
	}
	return 0;
}

void CMannualCheckSetting::InitAfterRead()
{
}

BOOL CMannualCheckSetting::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CMannualCheckSetting *p = (CMannualCheckSetting*)pObj;

	if(m_nBeSelected != p->m_nBeSelected)
	{
		return FALSE;
	}

	if(m_strDescription != p->m_strDescription)
	{
		return FALSE;
	}

	if(m_strTokenType != p->m_strTokenType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMannualCheckSetting::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMannualCheckSetting *p = (CMannualCheckSetting*)pDest;

	p->m_nBeSelected = m_nBeSelected;
	p->m_strDescription = m_strDescription;
	p->m_strTokenType = m_strTokenType;
	return TRUE;
}

CBaseObject* CMannualCheckSetting::Clone()
{
	CMannualCheckSetting *p = new CMannualCheckSetting();
	Copy(p);
	return p;
}

long CMannualCheckSetting::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("BeSelected"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Description"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("TokenType"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CMannualCheckSetting::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	strTemp.Format(_T("%d"), m_nBeSelected);
	pListCtrl->SetItemText(lItemIndex, 1, strTemp);
	pListCtrl->SetItemText(lItemIndex, 2, m_strDescription);
	pListCtrl->SetItemText(lItemIndex, 3, m_strTokenType);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

