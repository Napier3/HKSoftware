//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ShortData.cpp  CShortData


#include "stdafx.h"
#include "ShortData.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CShortData::CShortData()
{
	//初始化属性
	m_nReserved = 0;

	//初始化成员变量
	m_dTime = 0;
}

CShortData::~CShortData()
{
}

long CShortData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
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
	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_dTime);
	
	return 0;
}

long CShortData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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
	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_dTime);

	return 0;
}

long CShortData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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
		BinarySerializeCalLen(oBinaryBuffer, m_dTime);
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

		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_1)
		{
			BinarySerializeRead(oBinaryBuffer, m_dTime);
		}
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
		BinarySerializeWrite(oBinaryBuffer, m_dTime);
	}
	return 0;
}

void CShortData::InitAfterRead()
{
}

BOOL CShortData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CShortData *p = (CShortData*)pObj;

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

	return TRUE;
}

BOOL CShortData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CShortData *p = (CShortData*)pDest;

	p->m_strDataTypeID = m_strDataTypeID;
	p->m_strUnit = m_strUnit;
	p->m_strValue = m_strValue;
	p->m_strFormat = m_strFormat;
	p->m_strRemark = m_strRemark;
	p->m_strDefaultValue = m_strDefaultValue;
	p->m_nReserved = m_nReserved;
	return TRUE;
}

CBaseObject* CShortData::Clone()
{
	CShortData *p = new CShortData();
	Copy(p);
	return p;
}

long CShortData::InitListCtrlColumns(CListCtrl *pListCtrl)
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
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CShortData::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
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
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}


CExBaseObject* CShortData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == CDataMngrXmlRWKeys::CValueKey())
	{
		pNew = new CValue();
	}

	return pNew;
}

CExBaseObject* CShortData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CVALUE)
	{
		pNew = new CValue();
	}

	return pNew;
}

void CShortData::ResetData()
{
	if (m_strDefaultValue.GetLength() == 0)
	{
		return;
	}

	m_strValue = m_strDefaultValue;
}

void CShortData::StringSerialize(CStringSerializeBuffer &oBinaryBuffer)
{
	oBinaryBuffer << m_strID;
	oBinaryBuffer << _T("=");
	oBinaryBuffer << m_strValue;
	oBinaryBuffer << _T(";");
}

//xxy
CString CShortData::GetAttrValue(const CString &strValueID)
{
	CString strValue = _T("");

	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
	{
		strValue = m_strName;
	}
	else if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
	{
		strValue = m_strID;
	}
	else if (strValueID == CDataMngrXmlRWKeys::ValueKey())
	{
		strValue = m_strValue;
	}
	else if (strValueID == CDataMngrXmlRWKeys::DataTypeKey())
	{
		strValue = m_strDataTypeID;
	}
	else if (strValueID == CDataMngrXmlRWKeys::UnitKey())
	{
		strValue = m_strUnit;
	}
	else if (strValueID == CDataMngrXmlRWKeys::DefaultValueKey())
	{
		strValue = m_strDefaultValue;
	}
	else if (strValueID == CDataMngrXmlRWKeys::FormatKey())
	{
		strValue = m_strFormat;
	}
	else if (strValueID == CDataMngrXmlRWKeys::RemarkKey())
	{
		strValue = m_strRemark;
	}

	return strValue;
}