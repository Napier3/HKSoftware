//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Device.cpp  CIot_Device


#include "stdafx.h"
#include "Iot_Device.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Device::CIot_Device()
{
	//初始化属性
	m_nIndex_Device = 0;
	m_nIndex_Devicetype = 0;
	m_nIndex_Factory = 0;
	m_nIndex_Dept = 0;
	m_nIndex_Engine = 0;
	m_nIndex_Device_Classify = 0;
	m_nPort = 0;
	m_nTest_State = 0;
	m_nIndex_Device_Dir = 0;

	//初始化成员变量
}

CIot_Device::~CIot_Device()
{
}

long CIot_Device::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DevicetypeKey, oNode, m_nIndex_Devicetype);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FactoryKey, oNode, m_nIndex_Factory);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeptKey, oNode, m_nIndex_Dept);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_EngineKey, oNode, m_nIndex_Engine);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strPortKey, oNode, m_nPort);
	xml_GetAttibuteValue(pXmlKeys->m_strIpKey, oNode, m_strIp);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvm_File);
	xml_GetAttibuteValue(pXmlKeys->m_strTest_StateKey, oNode, m_nTest_State);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_DirKey, oNode, m_nIndex_Device_Dir);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_File_SKey, oNode, m_strDvm_File_S);
	return 0;
}

long CIot_Device::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceKey, oElement, m_nIndex_Device);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DevicetypeKey, oElement, m_nIndex_Devicetype);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FactoryKey, oElement, m_nIndex_Factory);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeptKey, oElement, m_nIndex_Dept);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_EngineKey, oElement, m_nIndex_Engine);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strPortKey, oElement, m_nPort);
	xml_SetAttributeValue(pXmlKeys->m_strIpKey, oElement, m_strIp);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvm_File);
	xml_SetAttributeValue(pXmlKeys->m_strTest_StateKey, oElement, m_nTest_State);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_DirKey, oElement, m_nIndex_Device_Dir);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_File_SKey, oElement, m_strDvm_File_S);
	return 0;
}

long CIot_Device::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Devicetype);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeCalLen(oBinaryBuffer, m_nPort);
		BinarySerializeCalLen(oBinaryBuffer, m_strIp);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File);
		BinarySerializeCalLen(oBinaryBuffer, m_nTest_State);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Dir);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File_S);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Devicetype);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeRead(oBinaryBuffer, m_nPort);
		BinarySerializeRead(oBinaryBuffer, m_strIp);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File);
		BinarySerializeRead(oBinaryBuffer, m_nTest_State);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Dir);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File_S);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Devicetype);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeWrite(oBinaryBuffer, m_nPort);
		BinarySerializeWrite(oBinaryBuffer, m_strIp);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File);
		BinarySerializeWrite(oBinaryBuffer, m_nTest_State);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Dir);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File_S);
	}
	return 0;
}

void CIot_Device::InitAfterRead()
{
}

BOOL CIot_Device::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_Device *p = (CIot_Device*)pObj;

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_nIndex_Devicetype != p->m_nIndex_Devicetype)
	{
		return FALSE;
	}

	if(m_nIndex_Factory != p->m_nIndex_Factory)
	{
		return FALSE;
	}

	if(m_nIndex_Dept != p->m_nIndex_Dept)
	{
		return FALSE;
	}

	if(m_nIndex_Engine != p->m_nIndex_Engine)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Classify != p->m_nIndex_Device_Classify)
	{
		return FALSE;
	}

	if(m_nPort != p->m_nPort)
	{
		return FALSE;
	}

	if(m_strIp != p->m_strIp)
	{
		return FALSE;
	}

	if(m_strDvm_File != p->m_strDvm_File)
	{
		return FALSE;
	}

	if(m_nTest_State != p->m_nTest_State)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Dir != p->m_nIndex_Device_Dir)
	{
		return FALSE;
	}

	if(m_strDvm_File_S != p->m_strDvm_File_S)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Device::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_Device *p = (CIot_Device*)pDest;

	p->m_nIndex_Device = m_nIndex_Device;
	p->m_nIndex_Devicetype = m_nIndex_Devicetype;
	p->m_nIndex_Factory = m_nIndex_Factory;
	p->m_nIndex_Dept = m_nIndex_Dept;
	p->m_nIndex_Engine = m_nIndex_Engine;
	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	p->m_nPort = m_nPort;
	p->m_strIp = m_strIp;
	p->m_strDvm_File = m_strDvm_File;
	p->m_nTest_State = m_nTest_State;
	p->m_nIndex_Device_Dir = m_nIndex_Device_Dir;
	p->m_strDvm_File_S = m_strDvm_File_S;
	return TRUE;
}

CBaseObject* CIot_Device::Clone()
{
	CIot_Device *p = new CIot_Device();
	Copy(p);
	return p;
}

CBaseObject* CIot_Device::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Device *p = new CIot_Device();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_Device::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DevicetypeKey, m_nIndex_Devicetype);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strModelKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strPortKey, m_nPort);
	pRecordset->GetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strTest_StateKey, m_nTest_State);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_DirKey, m_nIndex_Device_Dir);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	return 0;
}

long CIot_Device::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DevicetypeKey, m_nIndex_Devicetype);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strModelKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strPortKey, m_nPort);
	pRecordset->SetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strTest_StateKey, m_nTest_State);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_DirKey, m_nIndex_Device_Dir);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	return 0;
}

BOOL CIot_Device::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_FACTORY)
	{
		m_nIndex_Factory = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEPT)
	{
		m_nIndex_Dept = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_ENGINE)
	{
		m_nIndex_Engine = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEVICE_CLASSIFY)
	{
		m_nIndex_Device_Classify = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

