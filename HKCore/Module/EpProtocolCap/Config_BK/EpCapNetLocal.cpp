//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetLocal.cpp  CEpCapNetLocal


#include "stdafx.h"
#include "EpCapNetLocal.h"

CEpCapNetLocal::CEpCapNetLocal()
{
	//初始化属性
	m_nIndex = 0;

	//初始化成员变量
}

CEpCapNetLocal::~CEpCapNetLocal()
{
}

long CEpCapNetLocal::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	return 0;
}

long CEpCapNetLocal::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	return 0;
}

long CEpCapNetLocal::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
	}
	return 0;
}

void CEpCapNetLocal::InitAfterRead()
{
}

BOOL CEpCapNetLocal::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapNetLocal *p = (CEpCapNetLocal*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapNetLocal::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapNetLocal *p = (CEpCapNetLocal*)pDest;

	p->m_strName = m_strName;
	p->m_nIndex = m_nIndex;
	return TRUE;
}

CBaseObject* CEpCapNetLocal::Clone()
{
	CEpCapNetLocal *p = new CEpCapNetLocal();
	Copy(p);
	return p;
}

long CEpCapNetLocal::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Index"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CEpCapNetLocal::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	strTemp.Format(_T("%d"), m_nIndex);
	pListCtrl->SetItemText(lItemIndex, 2, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CEpCapNetLocal::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPNETDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapNetLocal::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapNetDeviceKey)
	{
		pNew = new CEpCapNetDevice();
	}

	return pNew;
}

CExBaseObject* CEpCapNetLocal::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPNETDEVICE)
	{
		pNew = new CEpCapNetDevice();
	}

	return pNew;
}
