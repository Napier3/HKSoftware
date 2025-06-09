//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTask.cpp  CIot_TypeTask


#include "stdafx.h"
#include "Iot_TypeTask.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTask::CIot_TypeTask()
{
	//初始化属性
	m_nIndex_Task = 0;
	m_nState_Create = 0;
	m_nCnt_Sample = 0;
	m_nTask_State = TYPE_TASK_STATE_NORMAL;
	m_nTask_Rpt_State = TYPE_TASK_RPT_STATE_NORMAL;

	//初始化成员变量
}

CIot_TypeTask::~CIot_TypeTask()
{
}

long CIot_TypeTask::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strId_UserKey, oNode, m_strId_User);
	xml_GetAttibuteValue(pXmlKeys->m_strState_CreateKey, oNode, m_nState_Create);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_SampleKey, oNode, m_strSn_Sample);
	xml_GetAttibuteValue(pXmlKeys->m_strName_SampleKey, oNode, m_strName_Sample);
	xml_GetAttibuteValue(pXmlKeys->m_strModel_SampleKey, oNode, m_strModel_Sample);
	xml_GetAttibuteValue(pXmlKeys->m_strCnt_SampleKey, oNode, m_nCnt_Sample);
	xml_GetAttibuteValue(pXmlKeys->m_strName_ClientKey, oNode, m_strName_Client);
	xml_GetAttibuteValue(pXmlKeys->m_strName_ManufactorKey, oNode, m_strName_Manufactor);
	xml_GetAttibuteValue(pXmlKeys->m_strAddress_ClientKey, oNode, m_strAddress_Client);
	xml_GetAttibuteValue(pXmlKeys->m_strAddress_ManufactorKey, oNode, m_strAddress_Manufactor);
	xml_GetAttibuteValue(pXmlKeys->m_strName_TemplateKey, oNode, m_strName_Template);
	xml_GetAttibuteValue(pXmlKeys->m_strPic_FileKey, oNode, m_strPic_File);
	xml_GetAttibuteValue(pXmlKeys->m_strPic_File_SKey, oNode, m_strPic_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strTask_FileKey, oNode, m_strTask_File);
	xml_GetAttibuteValue(pXmlKeys->m_strTask_File_SKey, oNode, m_strTask_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvm_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_File_SKey, oNode, m_strDvm_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_strDoc_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strId_MaininspectionKey, oNode, m_strId_Maininspection);
	xml_GetAttibuteValue(pXmlKeys->m_strId_CheckerKey, oNode, m_strId_Checker);
	xml_GetAttibuteValue(pXmlKeys->m_strId_ProofreaderKey, oNode, m_strId_Proofreader);
	xml_GetAttibuteValue(pXmlKeys->m_strInspection_TypeKey, oNode, m_strInspection_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strTask_StateKey, oNode, m_nTask_State);
	xml_GetAttibuteValue(pXmlKeys->m_strTask_Rpt_StateKey, oNode, m_nTask_Rpt_State);
	return 0;
}

long CIot_TypeTask::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strId_UserKey, oElement, m_strId_User);
	xml_SetAttributeValue(pXmlKeys->m_strState_CreateKey, oElement, m_nState_Create);
	xml_SetAttributeValue(pXmlKeys->m_strSn_SampleKey, oElement, m_strSn_Sample);
	xml_SetAttributeValue(pXmlKeys->m_strName_SampleKey, oElement, m_strName_Sample);
	xml_SetAttributeValue(pXmlKeys->m_strModel_SampleKey, oElement, m_strModel_Sample);
	xml_SetAttributeValue(pXmlKeys->m_strCnt_SampleKey, oElement, m_nCnt_Sample);
	xml_SetAttributeValue(pXmlKeys->m_strName_ClientKey, oElement, m_strName_Client);
	xml_SetAttributeValue(pXmlKeys->m_strName_ManufactorKey, oElement, m_strName_Manufactor);
	xml_SetAttributeValue(pXmlKeys->m_strAddress_ClientKey, oElement, m_strAddress_Client);
	xml_SetAttributeValue(pXmlKeys->m_strAddress_ManufactorKey, oElement, m_strAddress_Manufactor);
	xml_SetAttributeValue(pXmlKeys->m_strName_TemplateKey, oElement, m_strName_Template);
	xml_SetAttributeValue(pXmlKeys->m_strPic_FileKey, oElement, m_strPic_File);
	xml_SetAttributeValue(pXmlKeys->m_strPic_File_SKey, oElement, m_strPic_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strTask_FileKey, oElement, m_strTask_File);
	xml_SetAttributeValue(pXmlKeys->m_strTask_File_SKey, oElement, m_strTask_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvm_File);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_File_SKey, oElement, m_strDvm_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_strDoc_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strId_MaininspectionKey, oElement, m_strId_Maininspection);
	xml_SetAttributeValue(pXmlKeys->m_strId_CheckerKey, oElement, m_strId_Checker);
	xml_SetAttributeValue(pXmlKeys->m_strId_ProofreaderKey, oElement, m_strId_Proofreader);
	xml_SetAttributeValue(pXmlKeys->m_strInspection_TypeKey, oElement, m_strInspection_Type);
	xml_SetAttributeValue(pXmlKeys->m_strTask_StateKey, oElement, m_nTask_State);
	xml_SetAttributeValue(pXmlKeys->m_strTask_Rpt_StateKey, oElement, m_nTask_Rpt_State);
	return 0;
}

long CIot_TypeTask::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strId_User);
		BinarySerializeCalLen(oBinaryBuffer, m_nState_Create);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn_Sample);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_Sample);
		BinarySerializeCalLen(oBinaryBuffer, m_strModel_Sample);
		BinarySerializeCalLen(oBinaryBuffer, m_nCnt_Sample);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_Client);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_Manufactor);
		BinarySerializeCalLen(oBinaryBuffer, m_strAddress_Client);
		BinarySerializeCalLen(oBinaryBuffer, m_strAddress_Manufactor);
		BinarySerializeCalLen(oBinaryBuffer, m_strName_Template);
		BinarySerializeCalLen(oBinaryBuffer, m_strPic_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strPic_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strTask_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strTask_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strId_Maininspection);
		BinarySerializeCalLen(oBinaryBuffer, m_strId_Checker);
		BinarySerializeCalLen(oBinaryBuffer, m_strId_Proofreader);
		BinarySerializeCalLen(oBinaryBuffer, m_strInspection_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_nTask_State);
		BinarySerializeCalLen(oBinaryBuffer, m_nTask_Rpt_State);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strId_User);
		BinarySerializeRead(oBinaryBuffer, m_nState_Create);
		BinarySerializeRead(oBinaryBuffer, m_strSn_Sample);
		BinarySerializeRead(oBinaryBuffer, m_strName_Sample);
		BinarySerializeRead(oBinaryBuffer, m_strModel_Sample);
		BinarySerializeRead(oBinaryBuffer, m_nCnt_Sample);
		BinarySerializeRead(oBinaryBuffer, m_strName_Client);
		BinarySerializeRead(oBinaryBuffer, m_strName_Manufactor);
		BinarySerializeRead(oBinaryBuffer, m_strAddress_Client);
		BinarySerializeRead(oBinaryBuffer, m_strAddress_Manufactor);
		BinarySerializeRead(oBinaryBuffer, m_strName_Template);
		BinarySerializeRead(oBinaryBuffer, m_strPic_File);
		BinarySerializeRead(oBinaryBuffer, m_strPic_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strTask_File);
		BinarySerializeRead(oBinaryBuffer, m_strTask_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strId_Maininspection);
		BinarySerializeRead(oBinaryBuffer, m_strId_Checker);
		BinarySerializeRead(oBinaryBuffer, m_strId_Proofreader);
		BinarySerializeRead(oBinaryBuffer, m_strInspection_Type);
		BinarySerializeRead(oBinaryBuffer, m_nTask_State);
		BinarySerializeRead(oBinaryBuffer, m_nTask_Rpt_State);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strId_User);
		BinarySerializeWrite(oBinaryBuffer, m_nState_Create);
		BinarySerializeWrite(oBinaryBuffer, m_strSn_Sample);
		BinarySerializeWrite(oBinaryBuffer, m_strName_Sample);
		BinarySerializeWrite(oBinaryBuffer, m_strModel_Sample);
		BinarySerializeWrite(oBinaryBuffer, m_nCnt_Sample);
		BinarySerializeWrite(oBinaryBuffer, m_strName_Client);
		BinarySerializeWrite(oBinaryBuffer, m_strName_Manufactor);
		BinarySerializeWrite(oBinaryBuffer, m_strAddress_Client);
		BinarySerializeWrite(oBinaryBuffer, m_strAddress_Manufactor);
		BinarySerializeWrite(oBinaryBuffer, m_strName_Template);
		BinarySerializeWrite(oBinaryBuffer, m_strPic_File);
		BinarySerializeWrite(oBinaryBuffer, m_strPic_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strTask_File);
		BinarySerializeWrite(oBinaryBuffer, m_strTask_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strId_Maininspection);
		BinarySerializeWrite(oBinaryBuffer, m_strId_Checker);
		BinarySerializeWrite(oBinaryBuffer, m_strId_Proofreader);
		BinarySerializeWrite(oBinaryBuffer, m_strInspection_Type);
		BinarySerializeWrite(oBinaryBuffer, m_nTask_State);
		BinarySerializeWrite(oBinaryBuffer, m_nTask_Rpt_State);
	}
	return 0;
}

void CIot_TypeTask::InitAfterRead()
{
}

BOOL CIot_TypeTask::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTask *p = (CIot_TypeTask*)pObj;

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_strId_User != p->m_strId_User)
	{
		return FALSE;
	}

	if(m_nState_Create != p->m_nState_Create)
	{
		return FALSE;
	}

	if(m_strSn_Sample != p->m_strSn_Sample)
	{
		return FALSE;
	}

	if(m_strName_Sample != p->m_strName_Sample)
	{
		return FALSE;
	}

	if(m_strModel_Sample != p->m_strModel_Sample)
	{
		return FALSE;
	}

	if(m_nCnt_Sample != p->m_nCnt_Sample)
	{
		return FALSE;
	}

	if(m_strName_Client != p->m_strName_Client)
	{
		return FALSE;
	}

	if(m_strName_Manufactor != p->m_strName_Manufactor)
	{
		return FALSE;
	}

	if(m_strAddress_Client != p->m_strAddress_Client)
	{
		return FALSE;
	}

	if(m_strAddress_Manufactor != p->m_strAddress_Manufactor)
	{
		return FALSE;
	}

	if(m_strName_Template != p->m_strName_Template)
	{
		return FALSE;
	}

	if(m_strPic_File != p->m_strPic_File)
	{
		return FALSE;
	}

	if(m_strPic_File_S != p->m_strPic_File_S)
	{
		return FALSE;
	}

	if(m_strTask_File != p->m_strTask_File)
	{
		return FALSE;
	}

	if(m_strTask_File_S != p->m_strTask_File_S)
	{
		return FALSE;
	}

	if(m_strDvm_File != p->m_strDvm_File)
	{
		return FALSE;
	}

	if(m_strDvm_File_S != p->m_strDvm_File_S)
	{
		return FALSE;
	}

	if(m_strDoc_File != p->m_strDoc_File)
	{
		return FALSE;
	}

	if(m_strDoc_File_S != p->m_strDoc_File_S)
	{
		return FALSE;
	}

	if(m_strId_Maininspection != p->m_strId_Maininspection)
	{
		return FALSE;
	}

	if(m_strId_Checker != p->m_strId_Checker)
	{
		return FALSE;
	}

	if(m_strId_Proofreader != p->m_strId_Proofreader)
	{
		return FALSE;
	}

	if(m_strInspection_Type != p->m_strInspection_Type)
	{
		return FALSE;
	}

	if(m_nTask_State != p->m_nTask_State)
	{
		return FALSE;
	}

	if(m_nTask_Rpt_State != p->m_nTask_Rpt_State)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TypeTask::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTask *p = (CIot_TypeTask*)pDest;

	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strId_User = m_strId_User;
	p->m_nState_Create = m_nState_Create;
	p->m_strSn_Sample = m_strSn_Sample;
	p->m_strName_Sample = m_strName_Sample;
	p->m_strModel_Sample = m_strModel_Sample;
	p->m_nCnt_Sample = m_nCnt_Sample;
	p->m_strName_Client = m_strName_Client;
	p->m_strName_Manufactor = m_strName_Manufactor;
	p->m_strAddress_Client = m_strAddress_Client;
	p->m_strAddress_Manufactor = m_strAddress_Manufactor;
	p->m_strName_Template = m_strName_Template;
	p->m_strPic_File = m_strPic_File;
	p->m_strPic_File_S = m_strPic_File_S;
	p->m_strTask_File = m_strTask_File;
	p->m_strTask_File_S = m_strTask_File_S;
	p->m_strDvm_File = m_strDvm_File;
	p->m_strDvm_File_S = m_strDvm_File_S;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strDoc_File_S = m_strDoc_File_S;
	p->m_strId_Maininspection = m_strId_Maininspection;
	p->m_strId_Checker = m_strId_Checker;
	p->m_strId_Proofreader = m_strId_Proofreader;
	p->m_strInspection_Type = m_strInspection_Type;
	p->m_nTask_State = m_nTask_State;
	p->m_nTask_Rpt_State = m_nTask_Rpt_State;
	return TRUE;
}

CBaseObject* CIot_TypeTask::Clone()
{
	CIot_TypeTask *p = new CIot_TypeTask();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTask::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTask *p = new CIot_TypeTask();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTask::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_UserKey, m_strId_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strState_CreateKey, m_nState_Create);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_SampleKey, m_strSn_Sample);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_SampleKey, m_strName_Sample);
	pRecordset->GetFieldValue(pXmlKeys->m_strModel_SampleKey, m_strModel_Sample);
	pRecordset->GetFieldValue(pXmlKeys->m_strCnt_SampleKey, m_nCnt_Sample);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_ClientKey, m_strName_Client);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_ManufactorKey, m_strName_Manufactor);
	pRecordset->GetFieldValue(pXmlKeys->m_strAddress_ClientKey, m_strAddress_Client);
	pRecordset->GetFieldValue(pXmlKeys->m_strAddress_ManufactorKey, m_strAddress_Manufactor);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_TemplateKey, m_strName_Template);
	pRecordset->GetFieldValue(pXmlKeys->m_strPic_FileKey, m_strPic_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strPic_File_SKey, m_strPic_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strTask_FileKey, m_strTask_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strTask_File_SKey, m_strTask_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_MaininspectionKey, m_strId_Maininspection);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_CheckerKey, m_strId_Checker);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_ProofreaderKey, m_strId_Proofreader);
	pRecordset->GetFieldValue(pXmlKeys->m_strInspection_TypeKey, m_strInspection_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strTask_StateKey, m_nTask_State);
	pRecordset->GetFieldValue(pXmlKeys->m_strTask_Rpt_StateKey, m_nTask_Rpt_State);
	return 0;
}

long CIot_TypeTask::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_UserKey, m_strId_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strState_CreateKey, m_nState_Create);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_SampleKey, m_strSn_Sample);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_SampleKey, m_strName_Sample);
	pRecordset->SetFieldValue(pXmlKeys->m_strModel_SampleKey, m_strModel_Sample);
	pRecordset->SetFieldValue(pXmlKeys->m_strCnt_SampleKey, m_nCnt_Sample);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_ClientKey, m_strName_Client);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_ManufactorKey, m_strName_Manufactor);
	pRecordset->SetFieldValue(pXmlKeys->m_strAddress_ClientKey, m_strAddress_Client);
	pRecordset->SetFieldValue(pXmlKeys->m_strAddress_ManufactorKey, m_strAddress_Manufactor);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_TemplateKey, m_strName_Template);
	pRecordset->SetFieldValue(pXmlKeys->m_strPic_FileKey, m_strPic_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strPic_File_SKey, m_strPic_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strTask_FileKey, m_strTask_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strTask_File_SKey, m_strTask_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_MaininspectionKey, m_strId_Maininspection);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_CheckerKey, m_strId_Checker);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_ProofreaderKey, m_strId_Proofreader);
	pRecordset->SetFieldValue(pXmlKeys->m_strInspection_TypeKey, m_strInspection_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strTask_StateKey, m_nTask_State);
	pRecordset->SetFieldValue(pXmlKeys->m_strTask_Rpt_StateKey, m_nTask_Rpt_State);
	return 0;
}

BOOL CIot_TypeTask::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	return TRUE;
}

BOOL CIot_TypeTask::QueryTypeTaskByIndex(CXDbBaseLib *pXDbLib, long nIndex_TypeTask)
{
	CString strTypeTaskTable, strPKey, strSql;
	strTypeTaskTable = CIot_AtsMngrXmlRWKeys::CIot_TypeTaskKey();
	strPKey = CIot_AtsMngrXmlRWKeys::Index_TaskKey();

	strSql.Format(_T("select * from %s where %s=\"%s\" limit 1"),strTypeTaskTable, strPKey, nIndex_TypeTask);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

BOOL CIot_TypeTask::UpdateSampleCnt(CXDbBaseLib *pXDbLib, long nIndex_TypeTask, long nSampleCnt)
{
	BOOL bRet = QueryTypeTaskByIndex(pXDbLib, nIndex_TypeTask);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("查询委托任务表失败！[%d]"), nIndex_TypeTask);
		return FALSE;
	}

	m_nCnt_Sample = nSampleCnt;

	return DB_Update(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
}