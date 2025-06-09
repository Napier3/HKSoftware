//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RtDeviceData.cpp  CIot_RtDeviceData


#include "stdafx.h"
#include "Iot_RtDeviceData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RtDeviceData::CIot_RtDeviceData()
{
	//初始化属性
	m_nIndex_Device_Data = 0;
	m_nIndex_Device = 0;
	::GetLocalTime(&m_tmTm_Update);
	m_nIs_Warning = 0;

	//初始化成员变量
}

CIot_RtDeviceData::~CIot_RtDeviceData()
{
}

long CIot_RtDeviceData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_DataKey, oNode, m_nIndex_Device_Data);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strSnKey, oNode, m_strSn);
	xml_GetAttibuteValue(pXmlKeys->m_strData_FormatKey, oNode, m_strData_Format);
	xml_GetAttibuteValue(pXmlKeys->m_strDataKey, oNode, m_strData);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_UpdateKey, oNode, m_tmTm_Update);
	xml_GetAttibuteValue(pXmlKeys->m_strIs_WarningKey, oNode, m_nIs_Warning);
	return 0;
}

long CIot_RtDeviceData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_DataKey, oElement, m_nIndex_Device_Data);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceKey, oElement, m_nIndex_Device);
	xml_SetAttributeValue(pXmlKeys->m_strSnKey, oElement, m_strSn);
	xml_SetAttributeValue(pXmlKeys->m_strData_FormatKey, oElement, m_strData_Format);
	xml_SetAttributeValue(pXmlKeys->m_strDataKey, oElement, m_strData);
	xml_SetAttributeValue(pXmlKeys->m_strTm_UpdateKey, oElement, m_tmTm_Update);
	xml_SetAttributeValue(pXmlKeys->m_strIs_WarningKey, oElement, m_nIs_Warning);
	return 0;
}

long CIot_RtDeviceData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn);
		BinarySerializeCalLen(oBinaryBuffer, m_strData_Format);
		BinarySerializeCalLen(oBinaryBuffer, m_strData);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeCalLen(oBinaryBuffer, m_nIs_Warning);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Data);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_strSn);
		BinarySerializeRead(oBinaryBuffer, m_strData_Format);
		BinarySerializeRead(oBinaryBuffer, m_strData);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeRead(oBinaryBuffer, m_nIs_Warning);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Data);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_strSn);
		BinarySerializeWrite(oBinaryBuffer, m_strData_Format);
		BinarySerializeWrite(oBinaryBuffer, m_strData);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeWrite(oBinaryBuffer, m_nIs_Warning);
	}
	return 0;
}

void CIot_RtDeviceData::InitAfterRead()
{
}

BOOL CIot_RtDeviceData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RtDeviceData *p = (CIot_RtDeviceData*)pObj;

	if(m_nIndex_Device_Data != p->m_nIndex_Device_Data)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_strSn != p->m_strSn)
	{
		return FALSE;
	}

	if(m_strData_Format != p->m_strData_Format)
	{
		return FALSE;
	}

	if(m_strData != p->m_strData)
	{
		return FALSE;
	}

	if(m_nIs_Warning != p->m_nIs_Warning)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RtDeviceData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RtDeviceData *p = (CIot_RtDeviceData*)pDest;

	p->m_nIndex_Device_Data = m_nIndex_Device_Data;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_strSn = m_strSn;
	p->m_strData_Format = m_strData_Format;
	p->m_strData = m_strData;
	p->m_tmTm_Update = m_tmTm_Update;
	p->m_nIs_Warning = m_nIs_Warning;
	return TRUE;
}

CBaseObject* CIot_RtDeviceData::Clone()
{
	CIot_RtDeviceData *p = new CIot_RtDeviceData();
	Copy(p);
	return p;
}

CBaseObject* CIot_RtDeviceData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RtDeviceData *p = new CIot_RtDeviceData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RtDeviceData::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_DataKey, m_nIndex_Device_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->GetFieldValue(pXmlKeys->m_strData_FormatKey, m_strData_Format);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataKey, m_strData);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	pRecordset->GetFieldValue(pXmlKeys->m_strIs_WarningKey, m_nIs_Warning);
	return 0;
}

long CIot_RtDeviceData::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_DataKey, m_nIndex_Device_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->SetFieldValue(pXmlKeys->m_strData_FormatKey, m_strData_Format);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataKey, m_strData);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	pRecordset->SetFieldValue(pXmlKeys->m_strIs_WarningKey, m_nIs_Warning);
	return 0;
}

BOOL CIot_RtDeviceData::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEVICE)
	{
		m_nIndex_Device = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

