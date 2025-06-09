//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EcdmData.cpp  CEcdmData


#include "stdafx.h"
#include "EcdmData.h"

CEcdmData::CEcdmData()
{
	//初始化属性
	m_nDataType = 0;
	m_fMin = 0;
	m_fMax = 0;
	m_nDead = 0;
	m_nIndex = 0;

	//初始化成员变量
	m_nOffset = 0;
}

CEcdmData::~CEcdmData()
{
}

long CEcdmData::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_nDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strMinKey, oNode, m_fMin);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxKey, oNode, m_fMax);
	xml_GetAttibuteValue(pXmlKeys->m_strDeadKey, oNode, m_nDead);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	return 0;
}

long CEcdmData::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_nDataType);
	xml_SetAttributeValue(pXmlKeys->m_strMinKey, oElement, m_fMin);
	xml_SetAttributeValue(pXmlKeys->m_strMaxKey, oElement, m_fMax);
	xml_SetAttributeValue(pXmlKeys->m_strDeadKey, oElement, m_nDead);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	return 0;
}

BOOL CEcdmData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEcdmData *p = (CEcdmData*)pDest;

	p->m_strUnit = m_strUnit;
	p->m_nDataType = m_nDataType;
	p->m_fMin = m_fMin;
	p->m_fMax = m_fMax;
	p->m_nDead = m_nDead;
	p->m_nIndex = m_nIndex;
	return TRUE;
}

CBaseObject* CEcdmData::Clone()
{
	CEcdmData *p = new CEcdmData();
	Copy(p);
	return p;
}

long CEcdmData::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	strTemp.Format(_T("%d"), m_nIndex);
	pListCtrl->SetItemText(lItemIndex, 3, strTemp);
	pListCtrl->SetItemText(lItemIndex, 4, m_strUnit);
	strTemp.Format(_T("%d"), m_nDataType);
	pListCtrl->SetItemText(lItemIndex, 5, strTemp);

	strTemp.Format(_T("%f"), m_fMin);
	pListCtrl->SetItemText(lItemIndex, 6, strTemp);
	strTemp.Format(_T("%f"), m_fMax);
	pListCtrl->SetItemText(lItemIndex, 7, strTemp);
	strTemp.Format(_T("%d"), m_nDead);
	pListCtrl->SetItemText(lItemIndex, 8, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

long CEcdmData::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 50);
	pListCtrl->InsertColumn(1, _T("名称"));
	pListCtrl->SetColumnWidth(1, 240);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 60);
	pListCtrl->InsertColumn(3, _T("索引"));
	pListCtrl->SetColumnWidth(3, 50);
	pListCtrl->InsertColumn(4, _T("Unit"));
	pListCtrl->SetColumnWidth(4, 40);
	pListCtrl->InsertColumn(5, _T("类型"));
	pListCtrl->SetColumnWidth(5, 60);
	pListCtrl->InsertColumn(6, _T("Min"));
	pListCtrl->SetColumnWidth(6, 100);
	pListCtrl->InsertColumn(7, _T("Max"));
	pListCtrl->SetColumnWidth(7, 100);
	pListCtrl->InsertColumn(8, _T("Dead"));
	pListCtrl->SetColumnWidth(8, 50);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

BOOL CEcdmData::FindData(long nDataType,long nItemIndex)
{
	if (m_nDataType != nDataType)
	{
		return FALSE;
	}

	if (nItemIndex != m_nIndex + m_nOffset)
	{
		return FALSE;
	}

	return TRUE;
}

void CEcdmData::InitOffset(long nYxAddr, long nYcAddr, long nYtAddr)
{
	if (m_nDataType == 0)
	{
		m_nOffset = nYxAddr;
	}
	else if (m_nDataType == 1)
	{
		m_nOffset = nYcAddr;
	}
	else if (m_nDataType == 2)
	{
		m_nOffset = nYtAddr;
	}
}