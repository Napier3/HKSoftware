//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_DeviceType.cpp  CAts_Wzd_DeviceType


#include "stdafx.h"
#include "Ats_Wzd_DeviceType.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DeviceType::CAts_Wzd_DeviceType()
{
	//初始化属性
	m_nIndex_Profession = 0;
	m_nIndex_DeviceType = 0;

	//初始化成员变量
}

CAts_Wzd_DeviceType::~CAts_Wzd_DeviceType()
{
}

long CAts_Wzd_DeviceType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ProfessionKey, oNode, m_nIndex_Profession);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceTypeKey, oNode, m_nIndex_DeviceType);
	return 0;
}

long CAts_Wzd_DeviceType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_ProfessionKey, oElement, m_nIndex_Profession);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceTypeKey, oElement, m_nIndex_DeviceType);
	return 0;
}

long CAts_Wzd_DeviceType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Profession);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Profession);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Profession);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceType);
	}
	return 0;
}

void CAts_Wzd_DeviceType::InitAfterRead()
{
}

BOOL CAts_Wzd_DeviceType::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_DeviceType *p = (CAts_Wzd_DeviceType*)pObj;

	if(m_nIndex_Profession != p->m_nIndex_Profession)
	{
		return FALSE;
	}

	if(m_nIndex_DeviceType != p->m_nIndex_DeviceType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_DeviceType::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_DeviceType *p = (CAts_Wzd_DeviceType*)pDest;

	p->m_nIndex_Profession = m_nIndex_Profession;
	p->m_nIndex_DeviceType = m_nIndex_DeviceType;
	return TRUE;
}

CBaseObject* CAts_Wzd_DeviceType::Clone()
{
	CAts_Wzd_DeviceType *p = new CAts_Wzd_DeviceType();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DeviceType::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DeviceType *p = new CAts_Wzd_DeviceType();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_DeviceType::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ProfessionKey, m_nIndex_Profession);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceTypeKey, m_nIndex_DeviceType);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceTypeNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceTypeIDKey, m_strID);
	return 0;
}

long CAts_Wzd_DeviceType::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ProfessionKey, m_nIndex_Profession);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceTypeKey, m_nIndex_DeviceType);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceTypeNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceTypeIDKey, m_strID);
	return 0;
}

BOOL CAts_Wzd_DeviceType::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_PROFESSIONALDIR)
	{
		m_nIndex_Profession = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

