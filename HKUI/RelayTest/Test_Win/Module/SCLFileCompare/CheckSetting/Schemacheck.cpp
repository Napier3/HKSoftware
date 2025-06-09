//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Schemacheck.cpp  Schemacheck


#include "stdafx.h"
#include "Schemacheck.h"

Schemacheck::Schemacheck()
{
	//初始化属性
	m_nChose = 0;

	//初始化成员变量
}

Schemacheck::~Schemacheck()
{
}

long Schemacheck::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strChoseKey, oNode, m_nChose);
	xml_GetAttibuteValue(pXmlKeys->m_strVertionKey, oNode, m_strVertion);
	xml_GetAttibuteValue(pXmlKeys->m_strMethodKey, oNode, m_strMethod);
	return 0;
}

long Schemacheck::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strChoseKey, oElement, m_nChose);
	xml_SetAttributeValue(pXmlKeys->m_strVertionKey, oElement, m_strVertion);
	xml_SetAttributeValue(pXmlKeys->m_strMethodKey, oElement, m_strMethod);
	return 0;
}

long Schemacheck::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nChose);
		BinarySerializeCalLen(oBinaryBuffer, m_strVertion);
		BinarySerializeCalLen(oBinaryBuffer, m_strMethod);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nChose);
		BinarySerializeRead(oBinaryBuffer, m_strVertion);
		BinarySerializeRead(oBinaryBuffer, m_strMethod);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nChose);
		BinarySerializeWrite(oBinaryBuffer, m_strVertion);
		BinarySerializeWrite(oBinaryBuffer, m_strMethod);
	}
	return 0;
}

void Schemacheck::InitAfterRead()
{
}

BOOL Schemacheck::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	Schemacheck *p = (Schemacheck*)pObj;

	if(m_nChose != p->m_nChose)
	{
		return FALSE;
	}

	if(m_strVertion != p->m_strVertion)
	{
		return FALSE;
	}

	if(m_strMethod != p->m_strMethod)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL Schemacheck::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	Schemacheck *p = (Schemacheck*)pDest;

	p->m_nChose = m_nChose;
	p->m_strVertion = m_strVertion;
	p->m_strMethod = m_strMethod;
	return TRUE;
}

CBaseObject* Schemacheck::Clone()
{
	Schemacheck *p = new Schemacheck();
	Copy(p);
	return p;
}

long Schemacheck::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Chose"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Vertion"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Method"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Name"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("ID"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long Schemacheck::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	strTemp.Format(_T("%d"), m_nChose);
	pListCtrl->SetItemText(lItemIndex, 1, strTemp);
	pListCtrl->SetItemText(lItemIndex, 2, m_strVertion);
	pListCtrl->SetItemText(lItemIndex, 3, m_strMethod);
	pListCtrl->SetItemText(lItemIndex, 4, m_strName);
	pListCtrl->SetItemText(lItemIndex, 5, m_strID);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

