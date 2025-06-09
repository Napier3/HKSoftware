//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceClassifyType.cpp  CIot_DeviceClassifyType


#include "stdafx.h"
#include "Iot_DeviceClassifyType.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceClassifyType::CIot_DeviceClassifyType()
{
	//初始化属性
	m_nIndex_Device_type = 0;
	m_nIndex_Device_Classify = 0;

	//初始化成员变量
}

CIot_DeviceClassifyType::~CIot_DeviceClassifyType()
{
}

long CIot_DeviceClassifyType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_TypeKey, oNode, m_nIndex_Device_type);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceclassifyKey, oNode, m_strDeviceclassify);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strCodeKey, oNode, m_strCode);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	return 0;
}

long CIot_DeviceClassifyType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_TypeKey, oElement, m_nIndex_Device_type);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceclassifyKey, oElement, m_strDeviceclassify);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strCodeKey, oElement, m_strCode);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	return 0;
}

long CIot_DeviceClassifyType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_type);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceclassify);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strCode);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_type);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceclassify);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strCode);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_type);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceclassify);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strCode);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
	}
	return 0;
}

void CIot_DeviceClassifyType::InitAfterRead()
{
}

BOOL CIot_DeviceClassifyType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceClassifyType *p = (CIot_DeviceClassifyType*)pObj;

	if(m_nIndex_Device_type != p->m_nIndex_Device_type)
	{
		return FALSE;
	}

	if(m_strDeviceclassify != p->m_strDeviceclassify)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strCode != p->m_strCode)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Classify != p->m_nIndex_Device_Classify)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_DeviceClassifyType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceClassifyType *p = (CIot_DeviceClassifyType*)pDest;

	p->m_nIndex_Device_type = m_nIndex_Device_type;
	p->m_strDeviceclassify = m_strDeviceclassify;
	p->m_strName = m_strName;
	p->m_strCode = m_strCode;
	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	return TRUE;
}

CBaseObject* CIot_DeviceClassifyType::Clone()
{
	CIot_DeviceClassifyType *p = new CIot_DeviceClassifyType();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceClassifyType::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceClassifyType *p = new CIot_DeviceClassifyType();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceClassifyType::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_type);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceclassifyKey, m_strDeviceclassify);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	return 0;
}

long CIot_DeviceClassifyType::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_type);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceclassifyKey, m_strDeviceclassify);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	return 0;
}

BOOL CIot_DeviceClassifyType::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEVICE_CLASSIFY)
	{
		m_nIndex_Device_Classify = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

