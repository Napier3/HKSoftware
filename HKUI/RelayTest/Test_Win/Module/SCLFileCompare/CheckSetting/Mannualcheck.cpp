//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Mannualcheck.cpp  Mannualcheck


#include "stdafx.h"
#include "Mannualcheck.h"

Mannualcheck::Mannualcheck()
{
	//初始化属性
	m_nChose = 0;

	//初始化成员变量
}

Mannualcheck::~Mannualcheck()
{
}

long Mannualcheck::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strChoseKey, oNode, m_nChose);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long Mannualcheck::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strChoseKey, oElement, m_nChose);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long Mannualcheck::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nChose);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nChose);
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nChose);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void Mannualcheck::InitAfterRead()
{
}

BOOL Mannualcheck::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	Mannualcheck *p = (Mannualcheck*)pObj;

	if(m_nChose != p->m_nChose)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL Mannualcheck::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	Mannualcheck *p = (Mannualcheck*)pDest;

	p->m_nChose = m_nChose;
	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* Mannualcheck::Clone()
{
	Mannualcheck *p = new Mannualcheck();
	Copy(p);
	return p;
}

long Mannualcheck::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Chose"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Type"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("ID"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Name"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long Mannualcheck::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	strTemp.Format(_T("%d"), m_nChose);
	pListCtrl->SetItemText(lItemIndex, 1, strTemp);
	pListCtrl->SetItemText(lItemIndex, 2, m_strType);
	pListCtrl->SetItemText(lItemIndex, 3, m_strID);
	pListCtrl->SetItemText(lItemIndex, 4, m_strName);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

