//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_DeviceCheckCode.cpp  CAts_Wzd_DeviceCheckCode


#include "stdafx.h"
#include "Ats_Wzd_DeviceCheckCode.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DeviceCheckCode::CAts_Wzd_DeviceCheckCode()
{
	//初始化属性
	m_nIndex_DeviceCheckCode = 0;
	m_nIndex_DeviceVersion = 0;
	m_nIndex_Model = 0;

	//初始化成员变量
}

CAts_Wzd_DeviceCheckCode::~CAts_Wzd_DeviceCheckCode()
{
}

long CAts_Wzd_DeviceCheckCode::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceCheckCodeKey, oNode, m_nIndex_DeviceCheckCode);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceVersionKey, oNode, m_nIndex_DeviceVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceModelKey, oNode, m_nIndex_Model);
	return 0;
}

long CAts_Wzd_DeviceCheckCode::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceCheckCodeKey, oElement, m_nIndex_DeviceCheckCode);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceVersionKey, oElement, m_nIndex_DeviceVersion);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceModelKey, oElement, m_nIndex_Model);
	return 0;
}

long CAts_Wzd_DeviceCheckCode::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceCheckCode);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Model);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceCheckCode);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceVersion);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Model);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceCheckCode);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceVersion);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Model);
	}
	return 0;
}

void CAts_Wzd_DeviceCheckCode::InitAfterRead()
{
	m_strName = m_strID;
}

BOOL CAts_Wzd_DeviceCheckCode::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_DeviceCheckCode *p = (CAts_Wzd_DeviceCheckCode*)pObj;

	if(m_nIndex_DeviceCheckCode != p->m_nIndex_DeviceCheckCode)
	{
		return FALSE;
	}

	if(m_nIndex_DeviceVersion != p->m_nIndex_DeviceVersion)
	{
		return FALSE;
	}

	if(m_nIndex_Model != p->m_nIndex_Model)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_DeviceCheckCode::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_DeviceCheckCode *p = (CAts_Wzd_DeviceCheckCode*)pDest;

	p->m_nIndex_DeviceCheckCode = m_nIndex_DeviceCheckCode;
	p->m_nIndex_DeviceVersion = m_nIndex_DeviceVersion;
	p->m_nIndex_Model = m_nIndex_Model;
	return TRUE;
}

CBaseObject* CAts_Wzd_DeviceCheckCode::Clone()
{
	CAts_Wzd_DeviceCheckCode *p = new CAts_Wzd_DeviceCheckCode();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DeviceCheckCode::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DeviceCheckCode *p = new CAts_Wzd_DeviceCheckCode();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_DeviceCheckCode::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceCheckCodeKey, m_nIndex_DeviceCheckCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceVersionKey, m_nIndex_DeviceVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceModelKey, m_nIndex_Model);
	//pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceCheckCodeIDKey, m_strID);
	return 0;
}

long CAts_Wzd_DeviceCheckCode::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceCheckCodeKey, m_nIndex_DeviceCheckCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceVersionKey, m_nIndex_DeviceVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceModelKey, m_nIndex_Model);
	//pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceCheckCodeIDKey, m_strID);
	return 0;
}

BOOL CAts_Wzd_DeviceCheckCode::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICEVERSION)
	{
		m_nIndex_DeviceVersion = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

