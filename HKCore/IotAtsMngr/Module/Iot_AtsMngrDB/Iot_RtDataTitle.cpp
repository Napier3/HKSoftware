//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RtDataTitle.cpp  CIot_RtDataTitle


#include "stdafx.h"
#include "Iot_RtDataTitle.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RtDataTitle::CIot_RtDataTitle()
{
	//初始化属性
	m_nIndex_Data_Definition = 0;
	m_nIndex_Data = 0;

	//初始化成员变量
}

CIot_RtDataTitle::~CIot_RtDataTitle()
{
}

long CIot_RtDataTitle::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data_DefinitionKey, oNode, m_nIndex_Data_Definition);
	xml_GetAttibuteValue(pXmlKeys->m_strName_DataKey, oNode, m_strName_Data);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DataKey, oNode, m_nIndex_Data);
	xml_GetAttibuteValue(pXmlKeys->m_strUnit_DataKey, oNode, m_strUnit_Data);
	xml_GetAttibuteValue(pXmlKeys->m_strData_TypeKey, oNode, m_strData_Type);
	return 0;
}

long CIot_RtDataTitle::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data_DefinitionKey, oElement, m_nIndex_Data_Definition);
	xml_SetAttributeValue(pXmlKeys->m_strName_DataKey, oElement, m_strName_Data);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DataKey, oElement, m_nIndex_Data);
	xml_SetAttributeValue(pXmlKeys->m_strUnit_DataKey, oElement, m_strUnit_Data);
	xml_SetAttributeValue(pXmlKeys->m_strData_TypeKey, oElement, m_strData_Type);
	return 0;
}

long CIot_RtDataTitle::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data_Definition);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_strData_Type);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data_Definition);
		BinarySerializeRead(oBinaryBuffer, m_strName_Data);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data);
		BinarySerializeRead(oBinaryBuffer, m_strUnit_Data);
		BinarySerializeRead(oBinaryBuffer, m_strData_Type);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data_Definition);
		BinarySerializeWrite(oBinaryBuffer, m_strName_Data);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit_Data);
		BinarySerializeWrite(oBinaryBuffer, m_strData_Type);
	}
	return 0;
}

void CIot_RtDataTitle::InitAfterRead()
{
}

BOOL CIot_RtDataTitle::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RtDataTitle *p = (CIot_RtDataTitle*)pObj;

	if(m_nIndex_Data_Definition != p->m_nIndex_Data_Definition)
	{
		return FALSE;
	}

	if(m_strName_Data != p->m_strName_Data)
	{
		return FALSE;
	}

	if(m_nIndex_Data != p->m_nIndex_Data)
	{
		return FALSE;
	}

	if(m_strUnit_Data != p->m_strUnit_Data)
	{
		return FALSE;
	}

	if(m_strData_Type != p->m_strData_Type)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RtDataTitle::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RtDataTitle *p = (CIot_RtDataTitle*)pDest;

	p->m_nIndex_Data_Definition = m_nIndex_Data_Definition;
	p->m_strName_Data = m_strName_Data;
	p->m_nIndex_Data = m_nIndex_Data;
	p->m_strUnit_Data = m_strUnit_Data;
	p->m_strData_Type = m_strData_Type;
	return TRUE;
}

CBaseObject* CIot_RtDataTitle::Clone()
{
	CIot_RtDataTitle *p = new CIot_RtDataTitle();
	Copy(p);
	return p;
}

CBaseObject* CIot_RtDataTitle::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RtDataTitle *p = new CIot_RtDataTitle();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RtDataTitle::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data_DefinitionKey, m_nIndex_Data_Definition);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_DataKey, m_strName_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DataKey, m_nIndex_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strUnit_DataKey, m_strUnit_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strData_TypeKey, m_strData_Type);
	return 0;
}

long CIot_RtDataTitle::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data_DefinitionKey, m_nIndex_Data_Definition);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_DataKey, m_strName_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DataKey, m_nIndex_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strUnit_DataKey, m_strUnit_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strData_TypeKey, m_strData_Type);
	return 0;
}

