//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TestStandard.cpp  CIot_TestStandard


#include "stdafx.h"
#include "Iot_TestStandard.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TestStandard::CIot_TestStandard()
{
	//初始化属性
	m_nId = 0;
	m_nIndex_Device_Type = 0;
	::GetLocalTime(&m_tmCreate_Time);

	//初始化成员变量
}

CIot_TestStandard::~CIot_TestStandard()
{
}

long CIot_TestStandard::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strnIdKey, oNode, m_nId);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_TypeKey, oNode, m_nIndex_Device_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strStandard_NameKey, oNode, m_strStandard_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	return 0;
}

long CIot_TestStandard::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strnIdKey, oElement, m_nId);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_TypeKey, oElement, m_nIndex_Device_Type);
	xml_SetAttributeValue(pXmlKeys->m_strStandard_NameKey, oElement, m_strStandard_Name);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	return 0;
}

long CIot_TestStandard::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nId);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strStandard_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nId);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeRead(oBinaryBuffer, m_strStandard_Name);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nId);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strStandard_Name);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
	}
	return 0;
}

void CIot_TestStandard::InitAfterRead()
{
}

BOOL CIot_TestStandard::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TestStandard *p = (CIot_TestStandard*)pObj;

	if(m_nId != p->m_nId)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Type != p->m_nIndex_Device_Type)
	{
		return FALSE;
	}

	if(m_strStandard_Name != p->m_strStandard_Name)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TestStandard::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TestStandard *p = (CIot_TestStandard*)pDest;

	p->m_nId = m_nId;
	p->m_nIndex_Device_Type = m_nIndex_Device_Type;
	p->m_strStandard_Name = m_strStandard_Name;
	p->m_tmCreate_Time = m_tmCreate_Time;
	return TRUE;
}

CBaseObject* CIot_TestStandard::Clone()
{
	CIot_TestStandard *p = new CIot_TestStandard();
	Copy(p);
	return p;
}

CBaseObject* CIot_TestStandard::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TestStandard *p = new CIot_TestStandard();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TestStandard::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strnIdKey, m_nId);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strStandard_NameKey, m_strStandard_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

long CIot_TestStandard::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strnIdKey, m_nId);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strStandard_NameKey, m_strStandard_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

BOOL CIot_TestStandard::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	return TRUE;
}

