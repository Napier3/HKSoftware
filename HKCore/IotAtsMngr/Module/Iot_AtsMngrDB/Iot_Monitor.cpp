//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Monitor.cpp  CIot_Monitor


#include "stdafx.h"
#include "Iot_Monitor.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Monitor::CIot_Monitor()
{
	//初始化属性
	m_nIndex_Monitor_Data = 0;
	m_nIndex_Device = 0;
	m_nIndex_SubDept = 0;
}

CIot_Monitor::~CIot_Monitor()
{
}

long CIot_Monitor::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strIndex_Monitor_DataKey, oNode, m_nIndex_Monitor_Data);
	xml_GetElementText(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetElementText(pXmlKeys->m_strDataNameKey, oNode, m_strDataName);
	xml_GetElementText(pXmlKeys->m_strDataIdKey, oNode, m_strDataID);
	xml_GetElementText(pXmlKeys->m_strIndex_SubDeptKey, oNode, m_nIndex_SubDept);
	xml_GetElementText(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	return 0;
}

long CIot_Monitor::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strIndex_Monitor_DataKey, oXMLDoc, oElement, m_nIndex_Monitor_Data);
	xml_SetElementText(pXmlKeys->m_strIndex_DeviceKey, oXMLDoc, oElement, m_nIndex_Device);
	xml_SetElementText(pXmlKeys->m_strValueKey, oXMLDoc, oElement, m_strValue);
	xml_SetElementText(pXmlKeys->m_strDataNameKey, oXMLDoc, oElement, m_strDataName);
	xml_SetElementText(pXmlKeys->m_strDataIdKey, oXMLDoc, oElement, m_strDataID);
	xml_SetElementText(pXmlKeys->m_strIndex_SubDeptKey, oXMLDoc, oElement, m_nIndex_SubDept);
	xml_SetElementText(pXmlKeys->m_strUnitKey, oXMLDoc, oElement, m_strUnit);

	return 0;
}

long CIot_Monitor::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Monitor_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataID);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_SubDept);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Monitor_Data);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strDataName);
		BinarySerializeRead(oBinaryBuffer, m_strDataID);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_SubDept);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Monitor_Data);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strDataName);
		BinarySerializeWrite(oBinaryBuffer, m_strDataID);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_SubDept);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
	}
	return 0;
}

void CIot_Monitor::InitAfterRead()
{
}

BOOL CIot_Monitor::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Monitor *p = (CIot_Monitor*)pObj;

	if(m_nIndex_Monitor_Data != p->m_nIndex_Monitor_Data)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strDataName != p->m_strDataName)
	{
		return FALSE;
	}

	if(m_strDataID != p->m_strDataID)
	{
		return FALSE;
	}

	if(m_nIndex_SubDept != p->m_nIndex_SubDept)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Monitor::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Monitor *p = (CIot_Monitor*)pDest;

	p->m_nIndex_Monitor_Data = m_nIndex_Monitor_Data;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_strDataID = m_strDataID;
	p->m_strDataName = m_strDataName;
	p->m_strValue = m_strValue;
	p->m_strUnit = m_strUnit;
	p->m_nIndex_SubDept = m_nIndex_SubDept;
	return TRUE;
}

CBaseObject* CIot_Monitor::Clone()
{
	CIot_Monitor *p = new CIot_Monitor();
	Copy(p);
	return p;
}

CBaseObject* CIot_Monitor::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Monitor *p = new CIot_Monitor();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_Monitor::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Monitor_DataKey, m_nIndex_Monitor_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataNameKey, m_strDataName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataIdKey, m_strDataID);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_SubDeptKey, m_nIndex_SubDept);
	pRecordset->GetFieldValue(pXmlKeys->m_strUnitKey, m_strUnit);
	return 0;
}

long CIot_Monitor::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Monitor_DataKey, m_nIndex_Monitor_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataNameKey, m_strDataName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataIdKey, m_strDataID);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_SubDeptKey, m_nIndex_SubDept);
	pRecordset->SetFieldValue(pXmlKeys->m_strUnitKey, m_strUnit);
	return 0;
}

BOOL CIot_Monitor::QueryByDeviceIndex(CXDbBaseLib *pXDbLib, long nDeviceIndex)
{
	CString strMonitorTable,strDeviceIndexKey,strSql;
	strMonitorTable = CIot_AtsMngrXmlRWKeys::CIot_MonitorKey();
	strDeviceIndexKey = CIot_AtsMngrXmlRWKeys::Index_DeviceKey();

	strSql.Format(_T("select * from %s where %s=\"%d\" limit 1"),strMonitorTable,strDeviceIndexKey,nDeviceIndex);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}