//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetDevice.cpp  CEpCapNetDevice


#include "stdafx.h"
#include "EpCapNetDevice.h"

CEpCapNetDevice::CEpCapNetDevice()
{
	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
}

CEpCapNetDevice::~CEpCapNetDevice()
{
}

long CEpCapNetDevice::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strIPKey, oNode, m_strIP);
	return 0;
}

long CEpCapNetDevice::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	xml_SetAttributeValue(pXmlKeys->m_strIPKey, oElement, m_strIP);
	return 0;
}

long CEpCapNetDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_strIP);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
		BinarySerializeRead(oBinaryBuffer, m_strIP);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
		BinarySerializeWrite(oBinaryBuffer, m_strIP);
	}
	return 0;
}

void CEpCapNetDevice::InitAfterRead()
{
}

BOOL CEpCapNetDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapNetDevice *p = (CEpCapNetDevice*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	if(m_strIP != p->m_strIP)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapNetDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapNetDevice *p = (CEpCapNetDevice*)pDest;

	p->m_strName = m_strName;
	p->m_nIndex = m_nIndex;
	p->m_strIP = m_strIP;
	return TRUE;
}

CBaseObject* CEpCapNetDevice::Clone()
{
	CEpCapNetDevice *p = new CEpCapNetDevice();
	Copy(p);
	return p;
}

long CEpCapNetDevice::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Index"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("IP"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CEpCapNetDevice::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	strTemp.Format(_T("%d"), m_nIndex);
	pListCtrl->SetItemText(lItemIndex, 2, strTemp);
	pListCtrl->SetItemText(lItemIndex, 3, m_strIP);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

