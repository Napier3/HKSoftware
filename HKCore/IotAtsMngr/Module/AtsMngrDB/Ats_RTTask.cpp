//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_RTTask.cpp  CAts_RTTask


#include "stdafx.h"
#include "Ats_RTTask.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_RTTask::CAts_RTTask()
{
	//初始化属性
	m_nIndex_Task = 0;
	::GetLocalTime(&m_tmStartTime);
	::GetLocalTime(&m_tmEndTime);

	//初始化成员变量
}

CAts_RTTask::~CAts_RTTask()
{
}

long CAts_RTTask::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strStartTimeKey, oNode, m_tmStartTime);
	xml_GetAttibuteValue(pXmlKeys->m_strEndTimeKey, oNode, m_tmEndTime);
	xml_GetAttibuteValue(pXmlKeys->m_strPacketPathKey, oNode, m_strPacketPath);
	xml_GetAttibuteValue(pXmlKeys->m_strTaskNameKey, oNode, m_strID);
	m_strName = m_strID;
	return 0;
}

long CAts_RTTask::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strStartTimeKey, oElement, m_tmStartTime);
	xml_SetAttributeValue(pXmlKeys->m_strEndTimeKey, oElement, m_tmEndTime);
	xml_SetAttributeValue(pXmlKeys->m_strPacketPathKey, oElement, m_strPacketPath);
	xml_SetAttributeValue(pXmlKeys->m_strTaskNameKey, oElement, m_strID);
	return 0;
}

long CAts_RTTask::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_tmStartTime);
		BinarySerializeCalLen(oBinaryBuffer, m_tmEndTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strPacketPath);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_tmStartTime);
		BinarySerializeRead(oBinaryBuffer, m_tmEndTime);
		BinarySerializeRead(oBinaryBuffer, m_strPacketPath);
		BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_tmStartTime);
		BinarySerializeWrite(oBinaryBuffer, m_tmEndTime);
		BinarySerializeWrite(oBinaryBuffer, m_strPacketPath);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
	}
	return 0;
}

void CAts_RTTask::InitAfterRead()
{
}

BOOL CAts_RTTask::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_RTTask *p = (CAts_RTTask*)pObj;

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_strPacketPath != p->m_strPacketPath)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_RTTask::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_RTTask *p = (CAts_RTTask*)pDest;

	p->m_nIndex_Task = m_nIndex_Task;
	p->m_tmStartTime = m_tmStartTime;
	p->m_tmEndTime = m_tmEndTime;
	p->m_strPacketPath = m_strPacketPath;
	p->m_strID = m_strID;
	p->m_strName = m_strID;
	return TRUE;
}

CBaseObject* CAts_RTTask::Clone()
{
	CAts_RTTask *p = new CAts_RTTask();
	Copy(p);
	return p;
}

CBaseObject* CAts_RTTask::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_RTTask *p = new CAts_RTTask();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_RTTask::CanPaste(UINT nClassID)
{
	if (nClassID == ATSCLASSID_CATS_RTTASKBATCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_RTTask::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_RTTaskBatchKey)
	{
		pNew = new CAts_RTTaskBatch();
	}

	return pNew;
}

CExBaseObject* CAts_RTTask::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSCLASSID_CATS_RTTASKBATCH)
	{
		pNew = new CAts_RTTaskBatch();
	}

	return pNew;
}
long CAts_RTTask::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strStartTimeKey, m_tmStartTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strEndTimeKey, m_tmEndTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strPacketPathKey, m_strPacketPath);
	pRecordset->GetFieldValue(pXmlKeys->m_strTaskNameKey, m_strID);
	m_strName = m_strID;
	return 0;
}

long CAts_RTTask::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strStartTimeKey, m_tmStartTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strEndTimeKey, m_tmEndTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strPacketPathKey, m_strPacketPath);
	pRecordset->SetFieldValue(pXmlKeys->m_strTaskNameKey, m_strID);
	return 0;
}

CExBaseObject* CAts_RTTask::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_RTTaskBatch();

	return pNew;
}

BOOL CAts_RTTask::IsState_Finish()
{
	POS pos = GetHeadPosition();
	CAts_RTTaskBatch *p = NULL;

	while(pos != NULL)
	{
		p = (CAts_RTTaskBatch *)GetNext(pos);

		if (!p->IsState_Finish())
		{
			return FALSE;
		}
	}

	return TRUE;
}

CString CAts_RTTask::GetRawPkgFile()
{
	CreateAllDirectories(m_strPacketPath);

	CString strFile = m_strPacketPath + _T("RawPkgFile.data");

	return strFile;
}