//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskRtItems.cpp  CIot_TypeTaskRtItems


#include "stdafx.h"
#include "Iot_TypeTaskRtItems.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TypeTaskRtItems::CIot_TypeTaskRtItems()
{
	//初始化属性
	m_nIndex_Items = 0;
	m_nIndex_Task = 0;
	m_nCnt_Test_Record = 0;
	m_nState = TYPE_TASK_STATE_NORMAL;

	//初始化成员变量
}

CIot_TypeTaskRtItems::~CIot_TypeTaskRtItems()
{
}

long CIot_TypeTaskRtItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ItemsKey, oNode, m_nIndex_Items);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strSnKey, oNode, m_strSn);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_nState);
	xml_GetAttibuteValue(pXmlKeys->m_strId_UserKey, oNode, m_strId_User);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_Sample_DevKey, oNode, m_strSn_Sample_Dev);
	xml_GetAttibuteValue(pXmlKeys->m_strCnt_Test_RecordKey, oNode, m_nCnt_Test_Record);
	xml_GetAttibuteValue(pXmlKeys->m_strGbrpt_FileKey, oNode, m_strGbrpt_File);
	return 0;
}

long CIot_TypeTaskRtItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_ItemsKey, oElement, m_nIndex_Items);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strSnKey, oElement, m_strSn);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_nState);
	xml_SetAttributeValue(pXmlKeys->m_strId_UserKey, oElement, m_strId_User);
	xml_SetAttributeValue(pXmlKeys->m_strSn_Sample_DevKey, oElement, m_strSn_Sample_Dev);
	xml_SetAttributeValue(pXmlKeys->m_strCnt_Test_RecordKey, oElement, m_nCnt_Test_Record);
	xml_SetAttributeValue(pXmlKeys->m_strGbrpt_FileKey, oElement, m_strGbrpt_File);
	return 0;
}

long CIot_TypeTaskRtItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn);
		BinarySerializeCalLen(oBinaryBuffer, m_nState);
		BinarySerializeCalLen(oBinaryBuffer, m_strId_User);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeCalLen(oBinaryBuffer, m_nCnt_Test_Record);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbrpt_File);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strSn);
		BinarySerializeRead(oBinaryBuffer, m_nState);
		BinarySerializeRead(oBinaryBuffer, m_strId_User);
		BinarySerializeRead(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeRead(oBinaryBuffer, m_nCnt_Test_Record);
		BinarySerializeRead(oBinaryBuffer, m_strGbrpt_File);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strSn);
		BinarySerializeWrite(oBinaryBuffer, m_nState);
		BinarySerializeWrite(oBinaryBuffer, m_strId_User);
		BinarySerializeWrite(oBinaryBuffer, m_strSn_Sample_Dev);
		BinarySerializeWrite(oBinaryBuffer, m_nCnt_Test_Record);
		BinarySerializeWrite(oBinaryBuffer, m_strGbrpt_File);
	}
	return 0;
}

void CIot_TypeTaskRtItems::InitAfterRead()
{
}

BOOL CIot_TypeTaskRtItems::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TypeTaskRtItems *p = (CIot_TypeTaskRtItems*)pObj;

	if(m_nIndex_Items != p->m_nIndex_Items)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strSn != p->m_strSn)
	{
		return FALSE;
	}

	if(m_nState != p->m_nState)
	{
		return FALSE;
	}

	if(m_strId_User != p->m_strId_User)
	{
		return FALSE;
	}

	if(m_strSn_Sample_Dev != p->m_strSn_Sample_Dev)
	{
		return FALSE;
	}

	if(m_nCnt_Test_Record != p->m_nCnt_Test_Record)
	{
		return FALSE;
	}

	if(m_strGbrpt_File != p->m_strGbrpt_File)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TypeTaskRtItems::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TypeTaskRtItems *p = (CIot_TypeTaskRtItems*)pDest;

	p->m_nIndex_Items = m_nIndex_Items;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strName = m_strName;
	p->m_strSn = m_strSn;
	p->m_nState = m_nState;
	p->m_strId_User = m_strId_User;
	p->m_strSn_Sample_Dev = m_strSn_Sample_Dev;
	p->m_nCnt_Test_Record = m_nCnt_Test_Record;
	p->m_strGbrpt_File = m_strGbrpt_File;
	return TRUE;
}

CBaseObject* CIot_TypeTaskRtItems::Clone()
{
	CIot_TypeTaskRtItems *p = new CIot_TypeTaskRtItems();
	Copy(p);
	return p;
}

CBaseObject* CIot_TypeTaskRtItems::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TypeTaskRtItems *p = new CIot_TypeTaskRtItems();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TypeTaskRtItems::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_UserKey, m_strId_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
	pRecordset->GetFieldValue(pXmlKeys->m_strCnt_Test_RecordKey, m_nCnt_Test_Record);
	pRecordset->GetFieldValue(pXmlKeys->m_strGbrpt_FileKey, m_strGbrpt_File);
	return 0;
}

long CIot_TypeTaskRtItems::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_UserKey, m_strId_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
	pRecordset->SetFieldValue(pXmlKeys->m_strCnt_Test_RecordKey, m_nCnt_Test_Record);
	pRecordset->SetFieldValue(pXmlKeys->m_strGbrpt_FileKey, m_strGbrpt_File);
	return 0;
}

BOOL CIot_TypeTaskRtItems::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TYPETASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

