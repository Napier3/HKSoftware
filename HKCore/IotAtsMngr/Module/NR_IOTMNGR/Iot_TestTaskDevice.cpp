//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TestTaskDevice.cpp  CIot_TestTaskDevice


#include "stdafx.h"
#include "Iot_TestTaskDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TestTaskDevice::CIot_TestTaskDevice()
{
	//初始化属性
	m_nIndex_Test_Device = 0;
	m_nIndex_Device = 0;
	m_nIndex_Bench = 0;
	m_nIndex_Test_Task = 0;

	//初始化成员变量
}

CIot_TestTaskDevice::~CIot_TestTaskDevice()
{
}

long CIot_TestTaskDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_DeviceKey, oNode, m_nIndex_Test_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_DeviceKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_TaskKey, oNode, m_nIndex_Test_Task);
	return 0;
}

long CIot_TestTaskDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_DeviceKey, oElement, m_nIndex_Test_Device);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceKey, oElement, m_nIndex_Device);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	xml_SetAttributeValue(pXmlKeys->m_strSn_DeviceKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_TaskKey, oElement, m_nIndex_Test_Task);
	return 0;
}

long CIot_TestTaskDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Task);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Device);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Task);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Device);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Task);
	}
	return 0;
}

void CIot_TestTaskDevice::InitAfterRead()
{
}

BOOL CIot_TestTaskDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TestTaskDevice *p = (CIot_TestTaskDevice*)pObj;

	if(m_nIndex_Test_Device != p->m_nIndex_Test_Device)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_nIndex_Test_Task != p->m_nIndex_Test_Task)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TestTaskDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TestTaskDevice *p = (CIot_TestTaskDevice*)pDest;

	p->m_nIndex_Test_Device = m_nIndex_Test_Device;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_nIndex_Bench = m_nIndex_Bench;
	p->m_strID = m_strID;
	p->m_nIndex_Test_Task = m_nIndex_Test_Task;
	return TRUE;
}

CBaseObject* CIot_TestTaskDevice::Clone()
{
	CIot_TestTaskDevice *p = new CIot_TestTaskDevice();
	Copy(p);
	return p;
}

CBaseObject* CIot_TestTaskDevice::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TestTaskDevice *p = new CIot_TestTaskDevice();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TestTaskDevice::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_DeviceKey, m_nIndex_Test_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_DeviceKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	return 0;
}

long CIot_TestTaskDevice::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_DeviceKey, m_nIndex_Test_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_DeviceKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	return 0;
}

BOOL CIot_TestTaskDevice::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEVICE)
	{
		m_nIndex_Device = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_BENCH)
	{
		m_nIndex_Bench = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

