//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Tag.cpp  CTag


#include "stdafx.h"
#include "Tag.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTag::CTag()
{
	//初始化属性

	//初始化成员变量
}

CTag::~CTag()
{
}

long CTag::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CTag::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CTag::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CTag::InitAfterRead()
{
}

BOOL CTag::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTag *p = (CTag*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTag::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTag *p = (CTag*)pDest;

	p->m_strID = m_strID;
	p->m_strDataType = m_strDataType;
	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CTag::Clone()
{
	CTag *p = new CTag();
	Copy(p);
	return p;
}

long CTag::InitListCtrlColumns(CListCtrl *pListCtrl)
{
#ifdef NOT_USE_XLANGUAGE
	pListCtrl->InsertColumn(0, _T("编号"));
#else
	pListCtrl->InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/);
#endif
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ID"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("DataType"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Value"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTag::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strID);
	pListCtrl->SetItemText(lItemIndex, 2, m_strDataType);
	pListCtrl->SetItemText(lItemIndex, 3, m_strValue);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

