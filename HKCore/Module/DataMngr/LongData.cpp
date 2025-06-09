//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//LongData.cpp  CLongData


#include "stdafx.h"
#include "LongData.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CLongData::CLongData()
{
	//初始化属性
	m_nReserved = 0;
	m_nType = 0;
	m_nShow = 0;
	m_nEnable = 0;
	m_nReserved2 = 0;

	//初始化成员变量
}

CLongData::~CLongData()
{
}

long CLongData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataTypeID);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strFormatKey, oNode, m_strFormat);
	xml_GetAttibuteValue(pXmlKeys->m_strRemarkKey, oNode, m_strRemark);
	xml_GetAttibuteValue(pXmlKeys->m_strDefaultValueKey, oNode, m_strDefaultValue);
	xml_GetAttibuteValue(pXmlKeys->m_strReservedKey, oNode, m_nReserved);
	xml_GetAttibuteValue(pXmlKeys->m_strValueNameKey, oNode, m_strValueName);
	xml_GetAttibuteValue(pXmlKeys->m_strScriptKey, oNode, m_strScript);
	xml_GetAttibuteValue(pXmlKeys->m_strMessageKey, oNode, m_strMessage);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_nType);
	xml_GetAttibuteValue(pXmlKeys->m_strShowKey, oNode, m_nShow);
	xml_GetAttibuteValue(pXmlKeys->m_strEnableKey, oNode, m_nEnable);
	xml_GetAttibuteValue(pXmlKeys->m_strReserved2Key, oNode, m_nReserved2);
	return 0;
}

long CLongData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataTypeID);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strFormatKey, oElement, m_strFormat);
	xml_SetAttributeValue(pXmlKeys->m_strRemarkKey, oElement, m_strRemark);
	xml_SetAttributeValue(pXmlKeys->m_strDefaultValueKey, oElement, m_strDefaultValue);
	xml_SetAttributeValue(pXmlKeys->m_strReservedKey, oElement, m_nReserved);
	xml_SetAttributeValue(pXmlKeys->m_strValueNameKey, oElement, m_strValueName);
	xml_SetAttributeValue(pXmlKeys->m_strScriptKey, oElement, m_strScript);
	xml_SetAttributeValue(pXmlKeys->m_strMessageKey, oElement, m_strMessage);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_nType);
	xml_SetAttributeValue(pXmlKeys->m_strShowKey, oElement, m_nShow);
	xml_SetAttributeValue(pXmlKeys->m_strEnableKey, oElement, m_nEnable);
	xml_SetAttributeValue(pXmlKeys->m_strReserved2Key, oElement, m_nReserved2);
	return 0;
}

long CLongData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataTypeID);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strFormat);
		BinarySerializeCalLen(oBinaryBuffer, m_strRemark);
		BinarySerializeCalLen(oBinaryBuffer, m_strDefaultValue);
		BinarySerializeCalLen(oBinaryBuffer, m_nReserved);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueName);
		BinarySerializeCalLen(oBinaryBuffer, m_strScript);
		BinarySerializeCalLen(oBinaryBuffer, m_strMessage);
		BinarySerializeCalLen(oBinaryBuffer, m_nType);
		BinarySerializeCalLen(oBinaryBuffer, m_nShow);
		BinarySerializeCalLen(oBinaryBuffer, m_nEnable);
		BinarySerializeCalLen(oBinaryBuffer, m_nReserved2);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataTypeID);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strFormat);
		BinarySerializeRead(oBinaryBuffer, m_strRemark);
		BinarySerializeRead(oBinaryBuffer, m_strDefaultValue);
		BinarySerializeRead(oBinaryBuffer, m_nReserved);
		BinarySerializeRead(oBinaryBuffer, m_strValueName);
		BinarySerializeRead(oBinaryBuffer, m_strScript);
		BinarySerializeRead(oBinaryBuffer, m_strMessage);
		BinarySerializeRead(oBinaryBuffer, m_nType);
		BinarySerializeRead(oBinaryBuffer, m_nShow);
		BinarySerializeRead(oBinaryBuffer, m_nEnable);
		BinarySerializeRead(oBinaryBuffer, m_nReserved2);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataTypeID);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strFormat);
		BinarySerializeWrite(oBinaryBuffer, m_strRemark);
		BinarySerializeWrite(oBinaryBuffer, m_strDefaultValue);
		BinarySerializeWrite(oBinaryBuffer, m_nReserved);
		BinarySerializeWrite(oBinaryBuffer, m_strValueName);
		BinarySerializeWrite(oBinaryBuffer, m_strScript);
		BinarySerializeWrite(oBinaryBuffer, m_strMessage);
		BinarySerializeWrite(oBinaryBuffer, m_nType);
		BinarySerializeWrite(oBinaryBuffer, m_nShow);
		BinarySerializeWrite(oBinaryBuffer, m_nEnable);
		BinarySerializeWrite(oBinaryBuffer, m_nReserved2);
	}
	return 0;
}

void CLongData::InitAfterRead()
{
}

BOOL CLongData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CLongData *p = (CLongData*)pObj;

	if(m_strDataTypeID != p->m_strDataTypeID)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strFormat != p->m_strFormat)
	{
		return FALSE;
	}

	if(m_strRemark != p->m_strRemark)
	{
		return FALSE;
	}

	if(m_strDefaultValue != p->m_strDefaultValue)
	{
		return FALSE;
	}

	if(m_nReserved != p->m_nReserved)
	{
		return FALSE;
	}

	if(m_strValueName != p->m_strValueName)
	{
		return FALSE;
	}

	if(m_strScript != p->m_strScript)
	{
		return FALSE;
	}

	if(m_strMessage != p->m_strMessage)
	{
		return FALSE;
	}

	if(m_nType != p->m_nType)
	{
		return FALSE;
	}

	if(m_nShow != p->m_nShow)
	{
		return FALSE;
	}

	if(m_nEnable != p->m_nEnable)
	{
		return FALSE;
	}

	if(m_nReserved2 != p->m_nReserved2)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CLongData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CLongData *p = (CLongData*)pDest;

	p->m_strDataTypeID = m_strDataTypeID;
	p->m_strUnit = m_strUnit;
	p->m_strValue = m_strValue;
	p->m_strFormat = m_strFormat;
	p->m_strRemark = m_strRemark;
	p->m_strDefaultValue = m_strDefaultValue;
	p->m_nReserved = m_nReserved;
	p->m_strValueName = m_strValueName;
	p->m_strScript = m_strScript;
	p->m_strMessage = m_strMessage;
	p->m_nType = m_nType;
	p->m_nShow = m_nShow;
	p->m_nEnable = m_nEnable;
	p->m_nReserved2 = m_nReserved2;
	return TRUE;
}

CBaseObject* CLongData::Clone()
{
	CLongData *p = new CLongData();
	Copy(p);
	return p;
}

long CLongData::InitListCtrlColumns(CListCtrl *pListCtrl)
{
#ifdef NOT_USE_XLANGUAGE
	pListCtrl->InsertColumn(0, _T("编号"));
#else
	pListCtrl->InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/);
#endif

	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("DataTypeID"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Unit"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("Value"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->InsertColumn(6, _T("Format"));
	pListCtrl->SetColumnWidth(6, 80);
	pListCtrl->InsertColumn(7, _T("Remark"));
	pListCtrl->SetColumnWidth(7, 80);
	pListCtrl->InsertColumn(8, _T("DefaultValue"));
	pListCtrl->SetColumnWidth(8, 80);
	pListCtrl->InsertColumn(9, _T("Reserved"));
	pListCtrl->SetColumnWidth(9, 80);
	pListCtrl->InsertColumn(10, _T("ValueName"));
	pListCtrl->SetColumnWidth(10, 80);
	pListCtrl->InsertColumn(11, _T("Script"));
	pListCtrl->SetColumnWidth(11, 80);
	pListCtrl->InsertColumn(12, _T("Message"));
	pListCtrl->SetColumnWidth(12, 80);
	pListCtrl->InsertColumn(13, _T("Type"));
	pListCtrl->SetColumnWidth(13, 80);
	pListCtrl->InsertColumn(14, _T("Show"));
	pListCtrl->SetColumnWidth(14, 80);
	pListCtrl->InsertColumn(15, _T("Enable"));
	pListCtrl->SetColumnWidth(15, 80);
	pListCtrl->InsertColumn(16, _T("Reserved2"));
	pListCtrl->SetColumnWidth(16, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CLongData::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strDataTypeID);
	pListCtrl->SetItemText(lItemIndex, 4, m_strUnit);
	pListCtrl->SetItemText(lItemIndex, 5, m_strValue);
	pListCtrl->SetItemText(lItemIndex, 6, m_strFormat);
	pListCtrl->SetItemText(lItemIndex, 7, m_strRemark);
	pListCtrl->SetItemText(lItemIndex, 8, m_strDefaultValue);
	strTemp.Format(_T("%d"), m_nReserved);
	pListCtrl->SetItemText(lItemIndex, 9, strTemp);
	pListCtrl->SetItemText(lItemIndex, 10, m_strValueName);
	pListCtrl->SetItemText(lItemIndex, 11, m_strScript);
	pListCtrl->SetItemText(lItemIndex, 12, m_strMessage);
	strTemp.Format(_T("%d"), m_nType);
	pListCtrl->SetItemText(lItemIndex, 13, strTemp);
	strTemp.Format(_T("%d"), m_nShow);
	pListCtrl->SetItemText(lItemIndex, 14, strTemp);
	strTemp.Format(_T("%d"), m_nEnable);
	pListCtrl->SetItemText(lItemIndex, 15, strTemp);
	strTemp.Format(_T("%d"), m_nReserved2);
	pListCtrl->SetItemText(lItemIndex, 16, strTemp);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

