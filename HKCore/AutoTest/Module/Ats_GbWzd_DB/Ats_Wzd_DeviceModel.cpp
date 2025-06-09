//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_DeviceModel.cpp  CAts_Wzd_DeviceModel


#include "stdafx.h"
#include "Ats_Wzd_DeviceModel.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DeviceModel::CAts_Wzd_DeviceModel()
{
	//初始化属性
	m_nIndex_DeviceModel = 0;
	m_nIndex_DeviceType = 0;
	m_nIndex_Factory = 0;

	//初始化成员变量
}

CAts_Wzd_DeviceModel::~CAts_Wzd_DeviceModel()
{
}

long CAts_Wzd_DeviceModel::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceModelKey, oNode, m_nIndex_DeviceModel);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceTypeKey, oNode, m_nIndex_DeviceType);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FactoryKey, oNode, m_nIndex_Factory);
	return 0;
}

long CAts_Wzd_DeviceModel::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceModelKey, oElement, m_nIndex_DeviceModel);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceTypeKey, oElement, m_nIndex_DeviceType);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FactoryKey, oElement, m_nIndex_Factory);
	return 0;
}

long CAts_Wzd_DeviceModel::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceModel);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceType);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Factory);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceModel);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceType);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Factory);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceModel);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceType);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Factory);
	}
	return 0;
}

void CAts_Wzd_DeviceModel::InitAfterRead()
{
	m_strName = m_strID;
}

BOOL CAts_Wzd_DeviceModel::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_DeviceModel *p = (CAts_Wzd_DeviceModel*)pObj;

	if(m_nIndex_DeviceModel != p->m_nIndex_DeviceModel)
	{
		return FALSE;
	}

	if(m_nIndex_DeviceType != p->m_nIndex_DeviceType)
	{
		return FALSE;
	}

	if(m_nIndex_Factory != p->m_nIndex_Factory)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_DeviceModel::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_DeviceModel *p = (CAts_Wzd_DeviceModel*)pDest;

	p->m_nIndex_DeviceModel = m_nIndex_DeviceModel;
	p->m_nIndex_DeviceType = m_nIndex_DeviceType;
	p->m_nIndex_Factory = m_nIndex_Factory;
	return TRUE;
}

CBaseObject* CAts_Wzd_DeviceModel::Clone()
{
	CAts_Wzd_DeviceModel *p = new CAts_Wzd_DeviceModel();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DeviceModel::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DeviceModel *p = new CAts_Wzd_DeviceModel();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_DeviceModel::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceModelKey, m_nIndex_DeviceModel);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceTypeKey, m_nIndex_DeviceType);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceModelIDKey, m_strID);
	//pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

long CAts_Wzd_DeviceModel::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceModelKey, m_nIndex_DeviceModel);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceTypeKey, m_nIndex_DeviceType);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceModelIDKey, m_strID);
	//pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

BOOL CAts_Wzd_DeviceModel::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICETYPE)
	{
		m_nIndex_DeviceType = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_FACTORY)
	{
		m_nIndex_Factory = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

