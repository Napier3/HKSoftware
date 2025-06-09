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
	m_nTotalItems_Protocol = 0;
	m_nTotalItems_Function = 0;
	m_nIndex_Test_Device = 0;
	m_nIndex_Test_Task = 0;
	m_nIndex_Bench = 0;
	m_nIndex_Device = 0;
	::GetLocalTime(&m_tmCreate_Time);
	m_nTotalTime = 0;
	m_nRemainTime = 0;
	m_nCurrItem = 0;
	m_nTotalItems = 0;
	m_strDeviceState = _T("待检");

	//初始化成员变量
}

CIot_TestTaskDevice::~CIot_TestTaskDevice()
{
}

long CIot_TestTaskDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_DeviceKey, oNode, m_nIndex_Test_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_TaskKey, oNode, m_nIndex_Test_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);

	xml_GetAttibuteValue(pXmlKeys->m_strSn_DeviceKey, oNode, m_strDeviceSN);
	xml_GetAttibuteValue(pXmlKeys->m_strDevice_StateKey, oNode, m_strDeviceState);
	xml_GetAttibuteValue(pXmlKeys->m_strTotalItemsKey, oNode, m_nTotalItems);
	xml_GetAttibuteValue(pXmlKeys->m_strCurrItemKey, oNode, m_nCurrItem);
	xml_GetAttibuteValue(pXmlKeys->m_strTotalTimeKey, oNode, m_nTotalTime);
	xml_GetAttibuteValue(pXmlKeys->m_strRemainTimeKey, oNode, m_nRemainTime);
	xml_GetAttibuteValue(pXmlKeys->m_strTotalItemsProtocolKey, oNode, m_nTotalItems_Protocol);
	xml_GetAttibuteValue(pXmlKeys->m_strTotalItemsFunctionKey, oNode, m_nTotalItems_Function);
	return 0;
}

long CIot_TestTaskDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_DeviceKey, oElement, m_nIndex_Test_Device);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_TaskKey, oElement, m_nIndex_Test_Task);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceKey, oElement, m_nIndex_Device);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);

	xml_SetAttributeValue(pXmlKeys->m_strSn_DeviceKey, oElement, m_strDeviceSN);
	xml_SetAttributeValue(pXmlKeys->m_strDevice_StateKey, oElement, m_strDeviceState);
	xml_SetAttributeValue(pXmlKeys->m_strTotalItemsKey, oElement, m_nTotalItems);
	xml_SetAttributeValue(pXmlKeys->m_strCurrItemKey, oElement, m_nCurrItem);
	xml_SetAttributeValue(pXmlKeys->m_strTotalTimeKey, oElement, m_nTotalTime);
	xml_SetAttributeValue(pXmlKeys->m_strRemainTimeKey, oElement, m_nRemainTime);
	xml_SetAttributeValue(pXmlKeys->m_strTotalItemsProtocolKey, oElement, m_nTotalItems_Protocol);
	xml_SetAttributeValue(pXmlKeys->m_strTotalItemsFunctionKey, oElement, m_nTotalItems_Function);
	return 0;
}

long CIot_TestTaskDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceSN);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceState);
		BinarySerializeCalLen(oBinaryBuffer, m_nTotalItems);
		BinarySerializeCalLen(oBinaryBuffer, m_nCurrItem);
		BinarySerializeCalLen(oBinaryBuffer, m_nTotalTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nRemainTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nTotalItems_Protocol);
		BinarySerializeCalLen(oBinaryBuffer, m_nTotalItems_Function);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Device);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceSN);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceState);
		BinarySerializeRead(oBinaryBuffer, m_nTotalItems);
		BinarySerializeRead(oBinaryBuffer, m_nCurrItem);
		BinarySerializeRead(oBinaryBuffer, m_nTotalTime);
		BinarySerializeRead(oBinaryBuffer, m_nRemainTime);
		BinarySerializeRead(oBinaryBuffer, m_nTotalItems_Protocol);
		BinarySerializeRead(oBinaryBuffer, m_nTotalItems_Function);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Device);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceSN);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceState);
		BinarySerializeWrite(oBinaryBuffer, m_nTotalItems);
		BinarySerializeWrite(oBinaryBuffer, m_nCurrItem);
		BinarySerializeWrite(oBinaryBuffer, m_nTotalTime);
		BinarySerializeWrite(oBinaryBuffer, m_nRemainTime);
		BinarySerializeWrite(oBinaryBuffer, m_nTotalItems_Protocol);
		BinarySerializeWrite(oBinaryBuffer, m_nTotalItems_Function);
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

	if(m_nIndex_Test_Task != p->m_nIndex_Test_Task)
	{
		return FALSE;
	}

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_strDeviceSN != p->m_strDeviceSN)
	{
		return FALSE;
	}

	if(m_strDeviceState != p->m_strDeviceState)
	{
		return FALSE;
	}

	if(m_nTotalItems != p->m_nTotalItems)
	{
		return FALSE;
	}

	if(m_nCurrItem != p->m_nCurrItem)
	{
		return FALSE;
	}

	if(m_nTotalTime != p->m_nTotalTime)
	{
		return FALSE;
	}

	if(m_nRemainTime != p->m_nRemainTime)
	{
		return FALSE;
	}

	if(m_nTotalItems_Protocol != p->m_nTotalItems_Protocol)
	{
		return FALSE;
	}

	if(m_nTotalItems_Function != p->m_nTotalItems_Function)
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
	p->m_nIndex_Test_Task = m_nIndex_Test_Task;
	p->m_nIndex_Bench = m_nIndex_Bench;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_tmCreate_Time = m_tmCreate_Time;

	p->m_strDeviceState = m_strDeviceState;
	p->m_strDeviceSN = m_strDeviceSN;
	p->m_nTotalItems = m_nTotalItems;
	p->m_nCurrItem = m_nCurrItem;
	p->m_nTotalTime = m_nTotalTime;
	p->m_nRemainTime = m_nRemainTime;
	p->m_nTotalItems_Protocol = m_nTotalItems_Protocol;
	p->m_nTotalItems_Function = m_nTotalItems_Function;
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
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_DeviceKey, m_nIndex_Test_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);

	pRecordset->GetFieldValue(pXmlKeys->m_strSn_DeviceKey, m_strDeviceSN);
	pRecordset->GetFieldValue(pXmlKeys->m_strDevice_StateKey, m_strDeviceState);
	pRecordset->GetFieldValue(pXmlKeys->m_strTotalItemsKey, m_nTotalItems);
	pRecordset->GetFieldValue(pXmlKeys->m_strCurrItemKey, m_nCurrItem);
	pRecordset->GetFieldValue(pXmlKeys->m_strTotalTimeKey, m_nTotalTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strRemainTimeKey, m_nRemainTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strTotalItemsProtocolKey, m_nTotalItems_Protocol);
	pRecordset->GetFieldValue(pXmlKeys->m_strTotalItemsFunctionKey, m_nTotalItems_Function);
	return 0;
}

long CIot_TestTaskDevice::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_DeviceKey, m_nIndex_Test_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);

	pRecordset->SetFieldValue(pXmlKeys->m_strSn_DeviceKey, m_strDeviceSN);
	pRecordset->SetFieldValue(pXmlKeys->m_strDevice_StateKey, m_strDeviceState);
	pRecordset->SetFieldValue(pXmlKeys->m_strTotalItemsKey, m_nTotalItems);
	pRecordset->SetFieldValue(pXmlKeys->m_strCurrItemKey, m_nCurrItem);
	pRecordset->SetFieldValue(pXmlKeys->m_strTotalTimeKey, m_nTotalTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strRemainTimeKey, m_nRemainTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strTotalItemsProtocolKey, m_nTotalItems_Protocol);
	pRecordset->SetFieldValue(pXmlKeys->m_strTotalItemsFunctionKey, m_nTotalItems_Function);
	return 0;
}

BOOL CIot_TestTaskDevice::QueryDeviceByDeviceSN( CXDbBaseLib *pXDbLib,const CString &strDeviceSN )
{
	CString strTable,strSql;
	strTable = CIot_AtsMngrXmlRWKeys::CIot_TestTaskDeviceKey();

	strSql.Format(_T("select * from %s where sn_device=\"%s\" limit 1"),strTable,strDeviceSN);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

