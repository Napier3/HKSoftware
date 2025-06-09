//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DmdtNodeData.cpp  CDmdtNodeData


#include "stdafx.h"
#include "DmdtNodeData.h"

CDmdtNodeData::CDmdtNodeData()
{
	//初始化属性

	//初始化成员变量
}

CDmdtNodeData::~CDmdtNodeData()
{
}

long CDmdtNodeData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDmDataTemplateXmlRWKeys *pXmlKeys = (CDmDataTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_strIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	return 0;
}

long CDmdtNodeData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDmDataTemplateXmlRWKeys *pXmlKeys = (CDmDataTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_strIndex);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	return 0;
}

long CDmdtNodeData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strIndex);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strIndex);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
	}
	return 0;
}

void CDmdtNodeData::InitAfterRead()
{
}

BOOL CDmdtNodeData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDmdtNodeData *p = (CDmdtNodeData*)pObj;

	if(m_strIndex != p->m_strIndex)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDmdtNodeData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDmdtNodeData *p = (CDmdtNodeData*)pDest;

	p->m_strIndex = m_strIndex;
	p->m_strUnit = m_strUnit;
	return TRUE;
}

CBaseObject* CDmdtNodeData::Clone()
{
	CDmdtNodeData *p = new CDmdtNodeData();
	Copy(p);
	return p;
}

long CDmdtNodeData::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 60);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 140);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 100);
	pListCtrl->InsertColumn(3, _T("Index"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Unit"));
	pListCtrl->SetColumnWidth(4, 60);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CDmdtNodeData::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strIndex);
	pListCtrl->SetItemText(lItemIndex, 4, m_strUnit);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

