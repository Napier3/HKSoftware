//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskDevModel.cpp  CIot_TypeTaskDevModel


#include "stdafx.h"
#include "Iot_TypeTaskDevModel.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTaskDevModel::CIot_TypeTaskDevModel()
{
	//初始化属性
	m_nIndex_Data = 0;
	m_nIndex_Task = 0;

	//初始化成员变量
}

CIot_TypeTaskDevModel::~CIot_TypeTaskDevModel()
{
}

long CIot_TypeTaskDevModel::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DataKey, oNode, m_nIndex_Data);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strData_TypeKey, oNode, m_strData_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	return 0;
}

long CIot_TypeTaskDevModel::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_DataKey, oElement, m_nIndex_Data);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strData_TypeKey, oElement, m_strData_Type);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	return 0;
}

long CIot_TypeTaskDevModel::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strData_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strData_Type);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strData_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
	}
	return 0;
}

void CIot_TypeTaskDevModel::InitAfterRead()
{
}

BOOL CIot_TypeTaskDevModel::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_TypeTaskDevModel *p = (CIot_TypeTaskDevModel*)pObj;

	if(m_nIndex_Data != p->m_nIndex_Data)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
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

BOOL CIot_TypeTaskDevModel::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_TypeTaskDevModel *p = (CIot_TypeTaskDevModel*)pDest;

	p->m_nIndex_Data = m_nIndex_Data;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strData_Type = m_strData_Type;
	p->m_strValue = m_strValue;
	p->m_strUnit = m_strUnit;
	return TRUE;
}

CBaseObject* CIot_TypeTaskDevModel::Clone()
{
	CIot_TypeTaskDevModel *p = new CIot_TypeTaskDevModel();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskDevModel::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskDevModel *p = new CIot_TypeTaskDevModel();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTaskDevModel::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_ReadFields(pRecordset, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DataKey, m_nIndex_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strData_TypeKey, m_strData_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->GetFieldValue(pXmlKeys->m_strUnitKey, m_strUnit);
	return 0;
}

long CIot_TypeTaskDevModel::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_WriteFields(pRecordset, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DataKey, m_nIndex_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strData_TypeKey, m_strData_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->SetFieldValue(pXmlKeys->m_strUnitKey, m_strUnit);
	return 0;
}

BOOL CIot_TypeTaskDevModel::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

//先根据名称查询，查到就更新。查不到就插入
BOOL CIot_TypeTaskDevModel::WriteToDB(CXDbBaseLib *pXDbLib, CDvmData *pData)
{
	m_strName = pData->m_strName;
	m_strID = pData->m_strID;
	m_strValue = pData->m_strValue;
	m_strUnit = pData->m_strUnit;
	m_strData_Type = pData->m_strDataType;

	BOOL bRet = TRUE;
	CString strSql,strDevModelTable,strIndex_TaskKey;
	strDevModelTable = CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevModelKey();
	strIndex_TaskKey = CIot_AtsMngrXmlRWKeys::Index_TaskKey();

	strSql.Format(_T("select * from %s where %s=\"%d\" and name=\"%s\" limit 1"),strDevModelTable
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
CIot_TypeTaskDevModels::CIot_TypeTaskDevModels()
{
	//初始化属性

	//初始化成员变量
}

CIot_TypeTaskDevModels::~CIot_TypeTaskDevModels()
{
}

long CIot_TypeTaskDevModels::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TypeTaskDevModels::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIot_TypeTaskDevModels::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CIot_TypeTaskDevModels::InitAfterRead()
{
}

BOOL CIot_TypeTaskDevModels::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTaskDevModels *p = (CIot_TypeTaskDevModels*)pObj;

	return TRUE;
}

BOOL CIot_TypeTaskDevModels::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTaskDevModels *p = (CIot_TypeTaskDevModels*)pDest;

	return TRUE;
}

CBaseObject* CIot_TypeTaskDevModels::Clone()
{
	CIot_TypeTaskDevModels *p = new CIot_TypeTaskDevModels();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskDevModels::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskDevModels *p = new CIot_TypeTaskDevModels();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TypeTaskDevModels::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TYPETASKDEVMODEL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TypeTaskDevModels::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TypeTaskDevModelKey)
	{
		pNew = new CIot_TypeTaskDevModel();
	}

	return pNew;
}

CExBaseObject* CIot_TypeTaskDevModels::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TYPETASKDEVMODEL)
	{
		pNew = new CIot_TypeTaskDevModel();
	}

	return pNew;
}

CExBaseObject* CIot_TypeTaskDevModels::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

	pNew = new CIot_TypeTaskDevModel();

	return pNew;
}

BOOL CIot_TypeTaskDevModels::QueryTypeTaskDevModels(CXDbBaseLib *pXDbLib, long nIndex_TypeTask)
{
	CString strTable, strKey, strSql;
	strTable = CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevModelKey();
	strKey = CIot_AtsMngrXmlRWKeys::Index_TaskKey();
	strSql.Format(_T("select * from %s where %s=\"%d\""),strTable, strSql, nIndex_TypeTask);

	return DB_SelectSqlEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}