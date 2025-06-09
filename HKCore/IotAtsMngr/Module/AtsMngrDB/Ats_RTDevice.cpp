//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_RTDevice.cpp  CAts_RTDevice


#include "stdafx.h"
#include "Ats_RTDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_RTDevice::CAts_RTDevice()
{
	//初始化属性
	m_nIndex_Device = 0;
	m_nIndex_TaskBatch = 0;
	m_nIndex_Task = 0;
	m_nTestBatch = 0;

	SetTestProgress_NoStart();
}

CAts_RTDevice::~CAts_RTDevice()
{
}

long CAts_RTDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskBatchKey, oNode, m_nIndex_TaskBatch);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceTypeNameKey, oNode, m_strDeviceTypeName);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceTypeIDKey, oNode, m_strDeviceTypeID);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strTestBatchKey, oNode, m_nTestBatch);
	return 0;
}

long CAts_RTDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceKey, oElement, m_nIndex_Device);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskBatchKey, oElement, m_nIndex_TaskBatch);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceTypeNameKey, oElement, m_strDeviceTypeName);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceTypeIDKey, oElement, m_strDeviceTypeID);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strTestBatchKey, oElement, m_nTestBatch);
	return 0;
}

long CAts_RTDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_TaskBatch);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceTypeName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceTypeID);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nTestBatch);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_TaskBatch);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceTypeName);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceTypeID);
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nTestBatch);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_TaskBatch);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceTypeName);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceTypeID);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nTestBatch);
	}
	return 0;
}

void CAts_RTDevice::InitAfterRead()
{
}

BOOL CAts_RTDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_RTDevice *p = (CAts_RTDevice*)pObj;

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_nIndex_TaskBatch != p->m_nIndex_TaskBatch)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_strDeviceTypeName != p->m_strDeviceTypeName)
	{
		return FALSE;
	}

	if(m_strDeviceTypeID != p->m_strDeviceTypeID)
	{
		return FALSE;
	}

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_nTestBatch != p->m_nTestBatch)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_RTDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_RTDevice *p = (CAts_RTDevice*)pDest;

	p->m_nIndex_Device = m_nIndex_Device;
	p->m_nIndex_TaskBatch = m_nIndex_TaskBatch;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strDeviceTypeName = m_strDeviceTypeName;
	p->m_strDeviceTypeID = m_strDeviceTypeID;
	p->m_strID = m_strID;
	p->m_nTestBatch = m_nTestBatch;
	return TRUE;
}

CBaseObject* CAts_RTDevice::Clone()
{
	CAts_RTDevice *p = new CAts_RTDevice();
	Copy(p);
	return p;
}

CBaseObject* CAts_RTDevice::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_RTDevice *p = new CAts_RTDevice();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_RTDevice::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CAts_RTDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CAts_RTDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CAts_RTDevice::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskBatchKey, m_nIndex_TaskBatch);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceTypeNameKey, m_strDeviceTypeName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceTypeIDKey, m_strDeviceTypeID);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strTestBatchKey, m_nTestBatch);
	return 0;
}

long CAts_RTDevice::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskBatchKey, m_nIndex_TaskBatch);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceTypeNameKey, m_strDeviceTypeName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceTypeIDKey, m_strDeviceTypeID);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strTestBatchKey, m_nTestBatch);
	return 0;
}

BOOL CAts_RTDevice::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSCLASSID_CATS_RTTASKBATCH)
	{
		m_nIndex_TaskBatch = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSCLASSID_CATS_RTTASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

void CAts_RTDevice::SetTestProgress_NoStart()
{
	m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_NOTBEGIN;
	m_nTimeOut = 0;
	m_dwStartTime = 0;
}

void CAts_RTDevice::SetTestProgress_Start(DWORD dwStartTime,long nTimeOut)
{
	m_nTimeOut = nTimeOut;
	m_dwStartTime = dwStartTime;
	m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_WAITING;
}

void CAts_RTDevice::SetTestProgress_HasReport()
{
	m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_HASREPORT;
}

void CAts_RTDevice::SetTestProgress_TimeOut()
{
	m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_TIMEOUT;
}

BOOL CAts_RTDevice::IsTestProgress_HasReport()
{
	return (m_nTestProgress == ATS_DEVICE_TEST_PROGRESS_TIMEOUT);
}

BOOL CAts_RTDevice::IsTestProgress_Finish(DWORD dwCurTime)
{
	if (m_nTestProgress == ATS_DEVICE_TEST_PROGRESS_NOTBEGIN)
	{
		return FALSE;
	}

	if ((m_nTestProgress == ATS_DEVICE_TEST_PROGRESS_HASREPORT) || (m_nTestProgress == ATS_DEVICE_TEST_PROGRESS_TIMEOUT))
	{
		return TRUE;
	}

	if(dwCurTime - m_dwStartTime >= m_nTimeOut)
	{
		m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_TIMEOUT;
		return TRUE;
	}
	
	return FALSE;
}