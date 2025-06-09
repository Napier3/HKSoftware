//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_DeviceVersion.cpp  CAts_Wzd_DeviceVersion


#include "stdafx.h"
#include "Ats_Wzd_DeviceVersion.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DeviceVersion::CAts_Wzd_DeviceVersion()
{
	//初始化属性
	m_nIndex_DeviceVersion = 0;
	m_nIndex_DeviceModel = 0;

	//初始化成员变量
}

CAts_Wzd_DeviceVersion::~CAts_Wzd_DeviceVersion()
{
}

long CAts_Wzd_DeviceVersion::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceVersionKey, oNode, m_nIndex_DeviceVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceModelKey, oNode, m_nIndex_DeviceModel);
	return 0;
}

long CAts_Wzd_DeviceVersion::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceVersionKey, oElement, m_nIndex_DeviceVersion);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceModelKey, oElement, m_nIndex_DeviceModel);
	return 0;
}

long CAts_Wzd_DeviceVersion::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceModel);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceVersion);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceModel);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceVersion);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceModel);
	}
	return 0;
}

void CAts_Wzd_DeviceVersion::InitAfterRead()
{
	m_strName = m_strID;
}

BOOL CAts_Wzd_DeviceVersion::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_DeviceVersion *p = (CAts_Wzd_DeviceVersion*)pObj;

	if(m_nIndex_DeviceVersion != p->m_nIndex_DeviceVersion)
	{
		return FALSE;
	}

	if(m_nIndex_DeviceModel != p->m_nIndex_DeviceModel)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_DeviceVersion::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_DeviceVersion *p = (CAts_Wzd_DeviceVersion*)pDest;

	p->m_nIndex_DeviceVersion = m_nIndex_DeviceVersion;
	p->m_nIndex_DeviceModel = m_nIndex_DeviceModel;
	return TRUE;
}

CBaseObject* CAts_Wzd_DeviceVersion::Clone()
{
	CAts_Wzd_DeviceVersion *p = new CAts_Wzd_DeviceVersion();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DeviceVersion::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DeviceVersion *p = new CAts_Wzd_DeviceVersion();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_DeviceVersion::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	//pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceVersionIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceVersionKey, m_nIndex_DeviceVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceModelKey, m_nIndex_DeviceModel);
	return 0;
}

long CAts_Wzd_DeviceVersion::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	//pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceVersionIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceVersionKey, m_nIndex_DeviceVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceModelKey, m_nIndex_DeviceModel);
	return 0;
}

BOOL CAts_Wzd_DeviceVersion::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICEMODEL)
	{
		m_nIndex_DeviceModel = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

