//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_TemplateUnit.cpp  CAts_Wzd_TemplateUnit


#include "stdafx.h"
#include "Ats_Wzd_TemplateUnit.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_TemplateUnit::CAts_Wzd_TemplateUnit()
{
	//初始化属性
	m_nIndex_TemplateUnit = 0;
	m_nIndex_Folder = 0;
	m_nIndex_Profession = 0;
	m_nIndex_DeviceType = 0;
	m_nIndex_Factory = 0;
	m_nIndex_ULevel = 0;
	m_nIndex_DeviceModel = 0;
	m_nIndex_DeviceVersion = 0;
	m_nIndex_DeviceCheckCode = 0;

	//初始化成员变量
	m_nSelect = 1;
}

CAts_Wzd_TemplateUnit::~CAts_Wzd_TemplateUnit()
{
}

long CAts_Wzd_TemplateUnit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TemplateUnitKey, oNode, m_nIndex_TemplateUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FolderKey, oNode, m_nIndex_Folder);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ProfessionKey, oNode, m_nIndex_Profession);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceTypeKey, oNode, m_nIndex_DeviceType);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FactoryKey, oNode, m_nIndex_Factory);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ULevelKey, oNode, m_nIndex_ULevel);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplateFileNameKey, oNode, m_strTemplateFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strDvmFileNameKey, oNode, m_strDvmFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strFullPathKey, oNode, m_strFullPath);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceModelKey, oNode, m_nIndex_DeviceModel);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceVersionKey, oNode, m_nIndex_DeviceVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceCheckCodeKey, oNode, m_nIndex_DeviceCheckCode);
	return 0;
}

long CAts_Wzd_TemplateUnit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_TemplateUnitKey, oElement, m_nIndex_TemplateUnit);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FolderKey, oElement, m_nIndex_Folder);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ProfessionKey, oElement, m_nIndex_Profession);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceTypeKey, oElement, m_nIndex_DeviceType);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FactoryKey, oElement, m_nIndex_Factory);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ULevelKey, oElement, m_nIndex_ULevel);
	xml_SetAttributeValue(pXmlKeys->m_strTemplateFileNameKey, oElement, m_strTemplateFileName);
	xml_SetAttributeValue(pXmlKeys->m_strDvmFileNameKey, oElement, m_strDvmFileName);
	xml_SetAttributeValue(pXmlKeys->m_strFullPathKey, oElement, m_strFullPath);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceModelKey, oElement, m_nIndex_DeviceModel);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceVersionKey, oElement, m_nIndex_DeviceVersion);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceCheckCodeKey, oElement, m_nIndex_DeviceCheckCode);
	return 0;
}

long CAts_Wzd_TemplateUnit::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_TemplateUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Profession);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceType);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_ULevel);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplateFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strFullPath);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceModel);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DeviceCheckCode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_TemplateUnit);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Profession);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceType);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_ULevel);
		BinarySerializeRead(oBinaryBuffer, m_strTemplateFileName);
		BinarySerializeRead(oBinaryBuffer, m_strDvmFileName);
		BinarySerializeRead(oBinaryBuffer, m_strFullPath);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceModel);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceVersion);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DeviceCheckCode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_TemplateUnit);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Profession);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceType);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_ULevel);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplateFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strDvmFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strFullPath);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceModel);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceVersion);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DeviceCheckCode);
	}
	return 0;
}

void CAts_Wzd_TemplateUnit::InitAfterRead()
{
	CString strName;
	strName = m_strTemplateFileName.Left(m_strTemplateFileName.GetLength() - 6);
	m_strName = strName;
}

BOOL CAts_Wzd_TemplateUnit::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_TemplateUnit *p = (CAts_Wzd_TemplateUnit*)pObj;

	if(m_nIndex_TemplateUnit != p->m_nIndex_TemplateUnit)
	{
		return FALSE;
	}

	if(m_nIndex_Folder != p->m_nIndex_Folder)
	{
		return FALSE;
	}

	if(m_nIndex_Profession != p->m_nIndex_Profession)
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

	if(m_nIndex_ULevel != p->m_nIndex_ULevel)
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

	if(m_strFullPath != p->m_strFullPath)
	{
		return FALSE;
	}

	if(m_nIndex_DeviceModel != p->m_nIndex_DeviceModel)
	{
		return FALSE;
	}

	if(m_nIndex_DeviceVersion != p->m_nIndex_DeviceVersion)
	{
		return FALSE;
	}

	if(m_nIndex_DeviceCheckCode != p->m_nIndex_DeviceCheckCode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_TemplateUnit::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_TemplateUnit *p = (CAts_Wzd_TemplateUnit*)pDest;

	p->m_nIndex_TemplateUnit = m_nIndex_TemplateUnit;
	p->m_nIndex_Folder = m_nIndex_Folder;
	p->m_nIndex_Profession = m_nIndex_Profession;
	p->m_nIndex_DeviceType = m_nIndex_DeviceType;
	p->m_nIndex_Factory = m_nIndex_Factory;
	p->m_nIndex_ULevel = m_nIndex_ULevel;
	p->m_strTemplateFileName = m_strTemplateFileName;
	p->m_strDvmFileName = m_strDvmFileName;
	p->m_strFullPath = m_strFullPath;
	p->m_nIndex_DeviceModel = m_nIndex_DeviceModel;
	p->m_nIndex_DeviceVersion = m_nIndex_DeviceVersion;
	p->m_nIndex_DeviceCheckCode = m_nIndex_DeviceCheckCode;
	return TRUE;
}

CBaseObject* CAts_Wzd_TemplateUnit::Clone()
{
	CAts_Wzd_TemplateUnit *p = new CAts_Wzd_TemplateUnit();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_TemplateUnit::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_TemplateUnit *p = new CAts_Wzd_TemplateUnit();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_TemplateUnit::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TemplateUnitKey, m_nIndex_TemplateUnit);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ProfessionKey, m_nIndex_Profession);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceTypeKey, m_nIndex_DeviceType);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ULevelKey, m_nIndex_ULevel);
// 	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
// 	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemplateFileNameKey, m_strTemplateFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvmFileNameKey, m_strDvmFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strFullPathKey, m_strFullPath);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceModelKey, m_nIndex_DeviceModel);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceVersionKey, m_nIndex_DeviceVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceCheckCodeKey, m_nIndex_DeviceCheckCode);
	return 0;
}

long CAts_Wzd_TemplateUnit::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TemplateUnitKey, m_nIndex_TemplateUnit);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ProfessionKey, m_nIndex_Profession);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceTypeKey, m_nIndex_DeviceType);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ULevelKey, m_nIndex_ULevel);
// 	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
// 	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemplateFileNameKey, m_strTemplateFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvmFileNameKey, m_strDvmFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strFullPathKey, m_strFullPath);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceModelKey, m_nIndex_DeviceModel);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceVersionKey, m_nIndex_DeviceVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceCheckCodeKey, m_nIndex_DeviceCheckCode);
	return 0;
}

BOOL CAts_Wzd_TemplateUnit::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
	{
		m_nIndex_Folder = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_PROFESSIONALDIR)
	{
		m_nIndex_Profession = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICETYPE)
	{
		m_nIndex_DeviceType = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_FACTORY)
	{
		m_nIndex_Factory = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_ULEVEL)
	{
		m_nIndex_ULevel = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICEMODEL)
	{
		m_nIndex_DeviceModel = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICEVERSION)
	{
		m_nIndex_DeviceVersion = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_DEVICECHECKCODE)
	{
		m_nIndex_DeviceCheckCode = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

