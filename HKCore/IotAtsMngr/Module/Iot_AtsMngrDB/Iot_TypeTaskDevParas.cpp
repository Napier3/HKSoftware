//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskDevParas.cpp  CIot_TypeTaskDevParas


#include "stdafx.h"
#include "Iot_TypeTaskDevParas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTaskDevParas::CIot_TypeTaskDevParas()
{
	//初始化属性
	m_nIndex_Paras = 0;
	m_nIndex_Task = 0;
	m_nId_Dev = 0;

	//初始化成员变量
}

CIot_TypeTaskDevParas::~CIot_TypeTaskDevParas()
{
}

long CIot_TypeTaskDevParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ParasKey, oNode, m_nIndex_Paras);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strId_DevKey, oNode, m_nId_Dev);
	xml_GetAttibuteValue(pXmlKeys->m_strData_TypeKey, oNode, m_strData_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	return 0;
}

long CIot_TypeTaskDevParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_ParasKey, oElement, m_nIndex_Paras);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strId_DevKey, oElement, m_nId_Dev);
	xml_SetAttributeValue(pXmlKeys->m_strData_TypeKey, oElement, m_strData_Type);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	return 0;
}

long CIot_TypeTaskDevParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Paras);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_nId_Dev);
		BinarySerializeCalLen(oBinaryBuffer, m_strData_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Paras);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_nId_Dev);
		BinarySerializeRead(oBinaryBuffer, m_strData_Type);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Paras);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_nId_Dev);
		BinarySerializeWrite(oBinaryBuffer, m_strData_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
	}
	return 0;
}

void CIot_TypeTaskDevParas::InitAfterRead()
{
}

BOOL CIot_TypeTaskDevParas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_TypeTaskDevParas *p = (CIot_TypeTaskDevParas*)pObj;

	if(m_nIndex_Paras != p->m_nIndex_Paras)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_nId_Dev != p->m_nId_Dev)
	{
		return FALSE;
	}

	if(m_strData_Type != p->m_strData_Type)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TypeTaskDevParas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_TypeTaskDevParas *p = (CIot_TypeTaskDevParas*)pDest;

	p->m_nIndex_Paras = m_nIndex_Paras;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_nId_Dev = m_nId_Dev;
	p->m_strData_Type = m_strData_Type;
	p->m_strValue = m_strValue;
	p->m_strUnit = m_strUnit;
	return TRUE;
}

CBaseObject* CIot_TypeTaskDevParas::Clone()
{
	CIot_TypeTaskDevParas *p = new CIot_TypeTaskDevParas();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskDevParas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskDevParas *p = new CIot_TypeTaskDevParas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTaskDevParas::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_ReadFields(pRecordset, pXmlRWKeys);

	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ParasKey, m_nIndex_Paras);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_DevKey, m_nId_Dev);
	pRecordset->GetFieldValue(pXmlKeys->m_strData_TypeKey, m_strData_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->GetFieldValue(pXmlKeys->m_strUnitKey, m_strUnit);
	return 0;
}

long CIot_TypeTaskDevParas::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_WriteFields(pRecordset, pXmlRWKeys);

	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ParasKey, m_nIndex_Paras);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_DevKey, m_nId_Dev);
	pRecordset->SetFieldValue(pXmlKeys->m_strData_TypeKey, m_strData_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->SetFieldValue(pXmlKeys->m_strUnitKey, m_strUnit);
	return 0;
}

BOOL CIot_TypeTaskDevParas::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

//先根据名称查询，查到就更新。查不到就插入
BOOL CIot_TypeTaskDevParas::WriteToDB(CXDbBaseLib *pXDbLib, CDvmData *pData)
{
	m_strName = pData->m_strName;
	m_strID = pData->m_strID;
	m_strValue = pData->m_strValue;
	m_strUnit = pData->m_strUnit;
	m_strData_Type = pData->m_strDataType;

	BOOL bRet = TRUE;
	CString strSql,strDevParasTable,strIndex_TaskKey;
	strDevParasTable = CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevParasKey();
	strIndex_TaskKey = CIot_AtsMngrXmlRWKeys::Index_TaskKey();
	
	strSql.Format(_T("select * from %s where %s=\"%d\" and name=\"%s\" limit 1"),strDevParasTable
		, strIndex_TaskKey, m_nIndex_Task, m_strName);
	bRet = DB_Select_OwnEx(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);

	if (bRet)
	{
		return DB_Update(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		return DB_Insert_Own(pXDbLib, NULL, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, NULL);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
CIot_TypeTaskDevParases::CIot_TypeTaskDevParases()
{
	//初始化属性

	//初始化成员变量
}

CIot_TypeTaskDevParases::~CIot_TypeTaskDevParases()
{
}

long CIot_TypeTaskDevParases::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TypeTaskDevParases::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TypeTaskDevParases::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_TypeTaskDevParases::InitAfterRead()
{
}

BOOL CIot_TypeTaskDevParases::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTaskDevParases *p = (CIot_TypeTaskDevParases*)pObj;

	return TRUE;
}

BOOL CIot_TypeTaskDevParases::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTaskDevParases *p = (CIot_TypeTaskDevParases*)pDest;

	return TRUE;
}

CBaseObject* CIot_TypeTaskDevParases::Clone()
{
	CIot_TypeTaskDevParases *p = new CIot_TypeTaskDevParases();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskDevParases::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskDevParases *p = new CIot_TypeTaskDevParases();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TypeTaskDevParases::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TYPETASKDEVPARAS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TypeTaskDevParases::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TypeTaskDevParasKey)
	{
		pNew = new CIot_TypeTaskDevParas();
	}

	return pNew;
}

CExBaseObject* CIot_TypeTaskDevParases::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TYPETASKDEVPARAS)
	{
		pNew = new CIot_TypeTaskDevParas();
	}

	return pNew;
}

CExBaseObject* CIot_TypeTaskDevParases::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

	pNew = new CIot_TypeTaskDevParas();

	return pNew;
}

BOOL CIot_TypeTaskDevParases::QueryTypeTaskDevParases(CXDbBaseLib *pXDbLib, long nIndex_TypeTask)
{
	CString strTable, strKey, strSql;
	strTable = CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevParasKey();
	strKey = CIot_AtsMngrXmlRWKeys::Index_TaskKey();
	strSql.Format(_T("select * from %s where %s=\"%d\""),strTable, strSql, nIndex_TypeTask);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}