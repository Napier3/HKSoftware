//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskTestApps.cpp  CIot_TypeTaskTestApps


#include "stdafx.h"
#include "Iot_TypeTaskTestApps.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTaskTestApps::CIot_TypeTaskTestApps()
{
	//初始化属性
	m_nIndex_Test_Record = 0;
	m_nIndex_Task = 0;
	m_nIndex_Testapp = 0;

	//初始化成员变量
}

CIot_TypeTaskTestApps::~CIot_TypeTaskTestApps()
{
}

long CIot_TypeTaskTestApps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_RecordKey, oNode, m_nIndex_Test_Record);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_Sample_DevKey, oNode, m_strSn_Sample_Dev);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestappKey, oNode, m_nIndex_Testapp);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_TestappKey, oNode, m_strSn_Testapp);
	xml_GetAttibuteValue(pXmlKeys->m_strName_TestappKey, oNode, m_strName_Testapp);
	return 0;
}

long CIot_TypeTaskTestApps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_RecordKey, oElement, m_nIndex_Test_Record);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strSn_Sample_DevKey, oElement, m_strSn_Sample_Dev);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestappKey, oElement, m_nIndex_Testapp);
	xml_SetAttributeValue(pXmlKeys->m_strSn_TestappKey, oElement, m_strSn_Testapp);
	xml_SetAttributeValue(pXmlKeys->m_strName_TestappKey, oElement, m_strName_Testapp);
	return 0;
}

long CIot_TypeTaskTestApps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Record);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn_Testapp);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_Testapp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Record);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeRead(oBinaryBuffer, m_strSn_Testapp);
		BinarySerializeRead(oBinaryBuffer, m_strName_Testapp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Record);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeWrite(oBinaryBuffer, m_strSn_Testapp);
		BinarySerializeWrite(oBinaryBuffer, m_strName_Testapp);
	}
	return 0;
}

void CIot_TypeTaskTestApps::InitAfterRead()
{
}

BOOL CIot_TypeTaskTestApps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTaskTestApps *p = (CIot_TypeTaskTestApps*)pObj;

	if(m_nIndex_Test_Record != p->m_nIndex_Test_Record)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_strSn_Sample_Dev != p->m_strSn_Sample_Dev)
	{
		return FALSE;
	}

	if(m_nIndex_Testapp != p->m_nIndex_Testapp)
	{
		return FALSE;
	}

	if(m_strSn_Testapp != p->m_strSn_Testapp)
	{
		return FALSE;
	}

	if(m_strName_Testapp != p->m_strName_Testapp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TypeTaskTestApps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTaskTestApps *p = (CIot_TypeTaskTestApps*)pDest;

	p->m_nIndex_Test_Record = m_nIndex_Test_Record;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strSn_Sample_Dev = m_strSn_Sample_Dev;
	p->m_nIndex_Testapp = m_nIndex_Testapp;
	p->m_strSn_Testapp = m_strSn_Testapp;
	p->m_strName_Testapp = m_strName_Testapp;
	return TRUE;
}

CBaseObject* CIot_TypeTaskTestApps::Clone()
{
	CIot_TypeTaskTestApps *p = new CIot_TypeTaskTestApps();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskTestApps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskTestApps *p = new CIot_TypeTaskTestApps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTaskTestApps::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_RecordKey, m_nIndex_Test_Record);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_TestappKey, m_strSn_Testapp);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_TestappKey, m_strName_Testapp);
	return 0;
}

long CIot_TypeTaskTestApps::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_RecordKey, m_nIndex_Test_Record);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_TestappKey, m_strSn_Testapp);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_TestappKey, m_strName_Testapp);
	return 0;
}

BOOL CIot_TypeTaskTestApps::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

BOOL CIot_TypeTaskTestApps::QueryTestApps(CXDbBaseLib *pXDbLib,const CString &strTestAppSN, const CString &strSN_SampleDev, long nIndex_Task)
{
	if (strTestAppSN.IsEmpty() || strSN_SampleDev.IsEmpty() || nIndex_Task < 0)
	{
		return FALSE;
	}

	CString strTable,strKey1, strKey2, strKey3, strSql;
	strTable = CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestAppsKey();
	strKey1 = CIot_AtsMngrXmlRWKeys::Sn_TestappKey();
	strKey2 = CIot_AtsMngrXmlRWKeys::Number_Sample_DevKey();
	strKey3 = CIot_AtsMngrXmlRWKeys::Index_TaskKey();

	strSql.Format(_T("select * from %s where %s=\"%s\" and %s=\"%s\" and %s=\"%d\"limit 1"),strTable
		, strKey1,strTestAppSN, strKey2,strSN_SampleDev, strKey3,nIndex_Task);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}