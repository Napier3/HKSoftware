//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_Template.cpp  CAts_Wzd_Template


#include "stdafx.h"
#include "Ats_Wzd_Template.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_Template::CAts_Wzd_Template()
{
	//初始化属性
	m_nIndex_Station = 0;
	m_nIndex_InterVal = 0;
	m_nIndex_ULevel = 0;
	m_nIndex_Template = 0;
	m_nIndex_Company = 0;

	//初始化成员变量
}

CAts_Wzd_Template::~CAts_Wzd_Template()
{
}

long CAts_Wzd_Template::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_StationKey, oNode, m_nIndex_Station);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_InterVallKey, oNode, m_nIndex_InterVal);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ULevelKey, oNode, m_nIndex_ULevel);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TemplateKey, oNode, m_nIndex_Template);
	xml_GetAttibuteValue(pXmlKeys->m_strFullPathKey, oNode, m_strFullPath);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplateFileNameKey, oNode, m_strTemplateFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strDvmFileNameKey, oNode, m_strDvmFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strPortectSetSetKey, oNode, m_strPortectSet);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_CompanyKey, oNode, m_nIndex_Company);
	return 0;
}

long CAts_Wzd_Template::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_StationKey, oElement, m_nIndex_Station);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_InterVallKey, oElement, m_nIndex_InterVal);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ULevelKey, oElement, m_nIndex_ULevel);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TemplateKey, oElement, m_nIndex_Template);
	xml_SetAttributeValue(pXmlKeys->m_strFullPathKey, oElement, m_strFullPath);
	xml_SetAttributeValue(pXmlKeys->m_strTemplateFileNameKey, oElement, m_strTemplateFileName);
	xml_SetAttributeValue(pXmlKeys->m_strDvmFileNameKey, oElement, m_strDvmFileName);
	xml_SetAttributeValue(pXmlKeys->m_strPortectSetSetKey, oElement, m_strPortectSet);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_CompanyKey, oElement, m_nIndex_Company);
	return 0;
}

long CAts_Wzd_Template::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Station);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_InterVal);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_ULevel);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeCalLen(oBinaryBuffer, m_strFullPath);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplateFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strPortectSet);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Company);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Station);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_InterVal);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_ULevel);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeRead(oBinaryBuffer, m_strFullPath);
		BinarySerializeRead(oBinaryBuffer, m_strTemplateFileName);
		BinarySerializeRead(oBinaryBuffer, m_strDvmFileName);
		BinarySerializeRead(oBinaryBuffer, m_strPortectSet);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Company);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Station);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_InterVal);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_ULevel);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeWrite(oBinaryBuffer, m_strFullPath);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplateFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strDvmFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strPortectSet);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Company);
	}
	return 0;
}

void CAts_Wzd_Template::InitAfterRead()
{
}

BOOL CAts_Wzd_Template::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_Template *p = (CAts_Wzd_Template*)pObj;

	if(m_nIndex_Station != p->m_nIndex_Station)
	{
		return FALSE;
	}

	if(m_nIndex_InterVal != p->m_nIndex_InterVal)
	{
		return FALSE;
	}

	if(m_nIndex_ULevel != p->m_nIndex_ULevel)
	{
		return FALSE;
	}

	if(m_nIndex_Template != p->m_nIndex_Template)
	{
		return FALSE;
	}

	if(m_strFullPath != p->m_strFullPath)
	{
		return FALSE;
	}

	if(m_strTemplateFileName != p->m_strTemplateFileName)
	{
		return FALSE;
	}

	if(m_strDvmFileName != p->m_strDvmFileName)
	{
		return FALSE;
	}

	if(m_strPortectSet != p->m_strPortectSet)
	{
		return FALSE;
	}

	if(m_nIndex_Company != p->m_nIndex_Company)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_Template::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_Template *p = (CAts_Wzd_Template*)pDest;

	p->m_nIndex_Station = m_nIndex_Station;
	p->m_nIndex_InterVal = m_nIndex_InterVal;
	p->m_nIndex_ULevel = m_nIndex_ULevel;
	p->m_nIndex_Template = m_nIndex_Template;
	p->m_strFullPath = m_strFullPath;
	p->m_strTemplateFileName = m_strTemplateFileName;
	p->m_strDvmFileName = m_strDvmFileName;
	p->m_strPortectSet = m_strPortectSet;
	p->m_nIndex_Company = m_nIndex_Company;
	return TRUE;
}

CBaseObject* CAts_Wzd_Template::Clone()
{
	CAts_Wzd_Template *p = new CAts_Wzd_Template();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_Template::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_Template *p = new CAts_Wzd_Template();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_Template::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_StationKey, m_nIndex_Station);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_InterVallKey, m_nIndex_InterVal);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ULevelKey, m_nIndex_ULevel);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
// 	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
// 	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strFullPathKey, m_strFullPath);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemplateFileNameKey, m_strTemplateFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvmFileNameKey, m_strDvmFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strPortectSetSetKey, m_strPortectSet);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_CompanyKey, m_nIndex_Company);
	return 0;
}

long CAts_Wzd_Template::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_StationKey, m_nIndex_Station);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_InterVallKey, m_nIndex_InterVal);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ULevelKey, m_nIndex_ULevel);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
// 	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
// 	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strFullPathKey, m_strFullPath);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemplateFileNameKey, m_strTemplateFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvmFileNameKey, m_strDvmFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strPortectSetSetKey, m_strPortectSet);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_CompanyKey, m_nIndex_Company);
	return 0;
}

BOOL CAts_Wzd_Template::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TRANSSTATION)
	{
		m_nIndex_Station = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_INTERVAL)
	{
		m_nIndex_InterVal = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_ULEVEL)
	{
		m_nIndex_ULevel = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_OPERMAINTAINCOP)
	{
		m_nIndex_Company = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

