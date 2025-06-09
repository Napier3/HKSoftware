//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskStandard.cpp  CIot_TypeTaskStandard


#include "stdafx.h"
#include "Iot_TypeTaskStandard.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTaskStandard::CIot_TypeTaskStandard()
{
	//初始化属性
	m_nId = 0;
	m_nIndex_Task = 0;
	m_nIndex_Device_Type = 0;
	::GetLocalTime(&m_tmCreate_Time);

	//初始化成员变量
}

CIot_TypeTaskStandard::~CIot_TypeTaskStandard()
{
}

long CIot_TypeTaskStandard::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strnIdKey, oNode, m_nId);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_TypeKey, oNode, m_nIndex_Device_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strStandard_NameKey, oNode, m_strStandard_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	return 0;
}

long CIot_TypeTaskStandard::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strnIdKey, oElement, m_nId);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_TypeKey, oElement, m_nIndex_Device_Type);
	xml_SetAttributeValue(pXmlKeys->m_strStandard_NameKey, oElement, m_strStandard_Name);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	return 0;
}

long CIot_TypeTaskStandard::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nId);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strStandard_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nId);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeRead(oBinaryBuffer, m_strStandard_Name);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nId);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strStandard_Name);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
	}
	return 0;
}

void CIot_TypeTaskStandard::InitAfterRead()
{
}

BOOL CIot_TypeTaskStandard::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTaskStandard *p = (CIot_TypeTaskStandard*)pObj;

	if(m_nId != p->m_nId)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
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

BOOL CIot_TypeTaskStandard::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTaskStandard *p = (CIot_TypeTaskStandard*)pDest;

	p->m_nId = m_nId;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_nIndex_Device_Type = m_nIndex_Device_Type;
	p->m_strStandard_Name = m_strStandard_Name;
	p->m_tmCreate_Time = m_tmCreate_Time;
	return TRUE;
}

CBaseObject* CIot_TypeTaskStandard::Clone()
{
	CIot_TypeTaskStandard *p = new CIot_TypeTaskStandard();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskStandard::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskStandard *p = new CIot_TypeTaskStandard();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTaskStandard::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strnIdKey, m_nId);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strStandard_NameKey, m_strStandard_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

long CIot_TypeTaskStandard::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strnIdKey, m_nId);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strStandard_NameKey, m_strStandard_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

BOOL CIot_TypeTaskStandard::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
CIot_TypeTaskStandards::CIot_TypeTaskStandards()
{
	//初始化属性

	//初始化成员变量
}

CIot_TypeTaskStandards::~CIot_TypeTaskStandards()
{
}

long CIot_TypeTaskStandards::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TypeTaskStandards::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TypeTaskStandards::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CIot_TypeTaskStandards::InitAfterRead()
{
}

BOOL CIot_TypeTaskStandards::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTaskStandards *p = (CIot_TypeTaskStandards*)pObj;

	return TRUE;
}

BOOL CIot_TypeTaskStandards::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTaskStandards *p = (CIot_TypeTaskStandards*)pDest;

	return TRUE;
}

CBaseObject* CIot_TypeTaskStandards::Clone()
{
	CIot_TypeTaskStandards *p = new CIot_TypeTaskStandards();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskStandards::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskStandards *p = new CIot_TypeTaskStandards();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TypeTaskStandards::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TYPETASKSTANDARD)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TypeTaskStandards::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TypeTaskStandardKey)
	{
		pNew = new CIot_TypeTaskStandard();
	}

	return pNew;
}

CExBaseObject* CIot_TypeTaskStandards::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TYPETASKSTANDARD)
	{
		pNew = new CIot_TypeTaskStandard();
	}

	return pNew;
}

CExBaseObject* CIot_TypeTaskStandards::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

	pNew = new CIot_TypeTaskStandard();

	return pNew;
}

BOOL CIot_TypeTaskStandards::QueryTypeTaskStandards(CXDbBaseLib *pXDbLib, long nIndex_TypeTask)
{
	CString strTable, strKey, strSql;
	strTable = CIot_AtsMngrXmlRWKeys::CIot_TypeTaskStandardKey();
	strKey = CIot_AtsMngrXmlRWKeys::Index_TaskKey();
	strSql.Format(_T("select * from %s where %s=\"%d\""),strTable, strSql, nIndex_TypeTask);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}