//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotTestTask.cpp  CIotTestTask


#include "stdafx.h"
#include "IotTestTask.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotTestTask::CIotTestTask()
{
	//初始化属性
	m_nIndex_Test_Task = 0;
	m_nIndex_Dept = 0;
	m_nIndex_Template = 0;
	::GetLocalTime(&m_tmTm_Begin);
	::GetLocalTime(&m_tmTm_End);
	::GetLocalTime(&m_tmCreate_Time);
	m_nIndex_Tester = 0;
	m_nIndex_Device_Type = 0;
	m_nTime_Long_Total_Test = 0;
	m_nIndex_Bench = 0;

	//初始化成员变量
}

CIotTestTask::~CIotTestTask()
{
}

long CIotTestTask::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_TaskKey, oNode, m_nIndex_Test_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeptKey, oNode, m_nIndex_Dept);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TemplateKey, oNode, m_nIndex_Template);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_BeginKey, oNode, m_tmTm_Begin);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_EndKey, oNode, m_tmTm_End);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TesterKey, oNode, m_nIndex_Tester);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_TypeKey, oNode, m_nIndex_Device_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strTime_Long_Total_TestKey, oNode, m_nTime_Long_Total_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	return 0;
}

long CIotTestTask::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_TaskKey, oElement, m_nIndex_Test_Task);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeptKey, oElement, m_nIndex_Dept);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TemplateKey, oElement, m_nIndex_Template);
	xml_SetAttributeValue(pXmlKeys->m_strTm_BeginKey, oElement, m_tmTm_Begin);
	xml_SetAttributeValue(pXmlKeys->m_strTm_EndKey, oElement, m_tmTm_End);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TesterKey, oElement, m_nIndex_Tester);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_TypeKey, oElement, m_nIndex_Device_Type);
	xml_SetAttributeValue(pXmlKeys->m_strTime_Long_Total_TestKey, oElement, m_nTime_Long_Total_Test);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	return 0;
}

long CIotTestTask::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_End);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Tester);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_nTime_Long_Total_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_End);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Tester);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeRead(oBinaryBuffer, m_nTime_Long_Total_Test);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_End);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Tester);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeWrite(oBinaryBuffer, m_nTime_Long_Total_Test);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
	}
	return 0;
}

void CIotTestTask::InitAfterRead()
{
}

BOOL CIotTestTask::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIotTestTask *p = (CIotTestTask*)pObj;

	if(m_nIndex_Test_Task != p->m_nIndex_Test_Task)
	{
		return FALSE;
	}

	if(m_nIndex_Dept != p->m_nIndex_Dept)
	{
		return FALSE;
	}

	if(m_nIndex_Template != p->m_nIndex_Template)
	{
		return FALSE;
	}

	if(m_nIndex_Tester != p->m_nIndex_Tester)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Type != p->m_nIndex_Device_Type)
	{
		return FALSE;
	}

	if(m_nTime_Long_Total_Test != p->m_nTime_Long_Total_Test)
	{
		return FALSE;
	}

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIotTestTask::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotTestTask *p = (CIotTestTask*)pDest;

	p->m_nIndex_Test_Task = m_nIndex_Test_Task;
	p->m_nIndex_Dept = m_nIndex_Dept;
	p->m_nIndex_Template = m_nIndex_Template;
	p->m_tmTm_Begin = m_tmTm_Begin;
	p->m_tmTm_End = m_tmTm_End;
	p->m_tmCreate_Time = m_tmCreate_Time;
	p->m_nIndex_Tester = m_nIndex_Tester;
	p->m_nIndex_Device_Type = m_nIndex_Device_Type;
	p->m_nTime_Long_Total_Test = m_nTime_Long_Total_Test;
	p->m_nIndex_Bench = m_nIndex_Bench;
	return TRUE;
}

CBaseObject* CIotTestTask::Clone()
{
	CIotTestTask *p = new CIotTestTask();
	Copy(p);
	return p;
}

CBaseObject* CIotTestTask::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotTestTask *p = new CIotTestTask();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotTestTask::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CIotTestTask::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CIotTestTask::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CIotTestTask::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_BeginKey, m_tmTm_Begin);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_EndKey, m_tmTm_End);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TesterKey, m_nIndex_Tester);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strTime_Long_Total_TestKey, m_nTime_Long_Total_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

long CIotTestTask::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_BeginKey, m_tmTm_Begin);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_EndKey, m_tmTm_End);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TesterKey, m_nIndex_Tester);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strTime_Long_Total_TestKey, m_nTime_Long_Total_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

BOOL CIotTestTask::QueryByBenchSN(CXDbBaseLib *pXDbLib,const CString &strBenchSN)
{
	CString strBenchTable,strTestTaskTable,strIndex_TestTaskKey,strSql;
	strBenchTable = CIot_AtsMngrXmlRWKeys::CIot_BenchKey();
	strTestTaskTable = CIot_AtsMngrXmlRWKeys::CIotTestTaskKey();
	strIndex_TestTaskKey = CIot_AtsMngrXmlRWKeys::Index_Test_TaskKey();

	strSql.Format(_T("select * from %s where %s=(select %s from %s where code=\"%s\" limit 1) limit 1")
		,strTestTaskTable,strIndex_TestTaskKey,strIndex_TestTaskKey,strBenchTable,strBenchSN);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}