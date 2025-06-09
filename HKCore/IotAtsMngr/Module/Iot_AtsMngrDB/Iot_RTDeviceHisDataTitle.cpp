//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RTDeviceHisDataTitle.cpp  CIot_RTDeviceHisDataTitle


#include "stdafx.h"
#include "Iot_RTDeviceHisDataTitle.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RTDeviceHisDataTitle::CIot_RTDeviceHisDataTitle()
{
	//初始化属性
	m_nIndex_His_Data_Title = 0;
	m_nIndex_Device_Type = 0;
}

CIot_RTDeviceHisDataTitle::~CIot_RTDeviceHisDataTitle()
{
}

long CIot_RTDeviceHisDataTitle::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strIndex_His_Data_TitleKey, oNode, m_nIndex_His_Data_Title);
	xml_GetElementText(pXmlKeys->m_strIndex_Device_TypeKey, oNode, m_nIndex_Device_Type);
	xml_GetElementText(pXmlKeys->m_strDataKey, oNode, m_strData);
	xml_GetElementText(pXmlKeys->m_strDataNameKey, oNode, m_strDataName);
	xml_GetElementText(pXmlKeys->m_strDataIdKey, oNode, m_strDataID);
	xml_GetElementText(pXmlKeys->m_strDataUnitKey, oNode, m_strDataUnit);
	
	return 0;
}

long CIot_RTDeviceHisDataTitle::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strIndex_His_Data_TitleKey, oXMLDoc, oElement, m_nIndex_His_Data_Title);
	xml_SetElementText(pXmlKeys->m_strIndex_Device_TypeKey, oXMLDoc, oElement, m_nIndex_Device_Type);
	xml_SetElementText(pXmlKeys->m_strDataKey, oXMLDoc, oElement, m_strData);
	xml_SetElementText(pXmlKeys->m_strDataNameKey, oXMLDoc, oElement, m_strDataName);
	xml_SetElementText(pXmlKeys->m_strDataIdKey, oXMLDoc, oElement, m_strDataID);
	xml_SetElementText(pXmlKeys->m_strDataUnitKey, oXMLDoc, oElement, m_strDataUnit);

	return 0;
}

long CIot_RTDeviceHisDataTitle::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_His_Data_Title);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strData);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataUnit);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_His_Data_Title);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeRead(oBinaryBuffer, m_strData);
		BinarySerializeRead(oBinaryBuffer, m_strDataName);
		BinarySerializeRead(oBinaryBuffer, m_strDataID);
		BinarySerializeRead(oBinaryBuffer, m_strDataUnit);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_His_Data_Title);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strData);
		BinarySerializeWrite(oBinaryBuffer, m_strDataName);
		BinarySerializeWrite(oBinaryBuffer, m_strDataID);
		BinarySerializeWrite(oBinaryBuffer, m_strDataUnit);
	}
	return 0;
}

void CIot_RTDeviceHisDataTitle::InitAfterRead()
{
}

BOOL CIot_RTDeviceHisDataTitle::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RTDeviceHisDataTitle *p = (CIot_RTDeviceHisDataTitle*)pObj;

	if(m_nIndex_His_Data_Title != p->m_nIndex_His_Data_Title)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Type != p->m_nIndex_Device_Type)
	{
		return FALSE;
	}

	if(m_strData != p->m_strData)
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
	
	if(m_strDataUnit != p->m_strDataUnit)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RTDeviceHisDataTitle::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RTDeviceHisDataTitle *p = (CIot_RTDeviceHisDataTitle*)pDest;

	p->m_nIndex_His_Data_Title = m_nIndex_His_Data_Title;
	p->m_nIndex_Device_Type = m_nIndex_Device_Type;
	p->m_strDataID = m_strDataID;
	p->m_strDataName = m_strDataName;
	p->m_strData = m_strData;
	p->m_strDataUnit = m_strDataUnit;
	return TRUE;
}

CBaseObject* CIot_RTDeviceHisDataTitle::Clone()
{
	CIot_RTDeviceHisDataTitle *p = new CIot_RTDeviceHisDataTitle();
	Copy(p);
	return p;
}

CBaseObject* CIot_RTDeviceHisDataTitle::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RTDeviceHisDataTitle *p = new CIot_RTDeviceHisDataTitle();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RTDeviceHisDataTitle::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_His_Data_TitleKey, m_nIndex_His_Data_Title);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataKey, m_strData);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataNameKey, m_strDataName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataIdKey, m_strDataID);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataUnitKey, m_strDataUnit);
	return 0;
}

long CIot_RTDeviceHisDataTitle::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_His_Data_TitleKey, m_nIndex_His_Data_Title);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataKey, m_strData);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataNameKey, m_strDataName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataIdKey, m_strDataID);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataUnitKey, m_strDataUnit);
	return 0;
}