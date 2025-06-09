//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RuleEngineConfig.cpp  CIot_RuleEngineConfig


#include "stdafx.h"
#include "Iot_RuleEngineConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RuleEngineConfig::CIot_RuleEngineConfig()
{
	//初始化属性
	m_nId = 0;
	m_nDevice_Classify_Id = 0;

	//初始化成员变量
}

CIot_RuleEngineConfig::~CIot_RuleEngineConfig()
{
}

long CIot_RuleEngineConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strnIdKey, oNode, m_nId);
	xml_GetAttibuteValue(pXmlKeys->m_strCodeKey, oNode, m_strCode);
	xml_GetAttibuteValue(pXmlKeys->m_strDevice_Classify_IdKey, oNode, m_nDevice_Classify_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strComm_TypeKey, oNode, m_strComm_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strSuffix_FileKey, oNode, m_strSuffix_File);
	return 0;
}

long CIot_RuleEngineConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strnIdKey, oElement, m_nId);
	xml_SetAttributeValue(pXmlKeys->m_strCodeKey, oElement, m_strCode);
	xml_SetAttributeValue(pXmlKeys->m_strDevice_Classify_IdKey, oElement, m_nDevice_Classify_Id);
	xml_SetAttributeValue(pXmlKeys->m_strComm_TypeKey, oElement, m_strComm_Type);
	xml_SetAttributeValue(pXmlKeys->m_strSuffix_FileKey, oElement, m_strSuffix_File);
	return 0;
}

long CIot_RuleEngineConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nId);
		BinarySerializeCalLen(oBinaryBuffer, m_strCode);
		BinarySerializeCalLen(oBinaryBuffer, m_nDevice_Classify_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strComm_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strSuffix_File);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nId);
		BinarySerializeRead(oBinaryBuffer, m_strCode);
		BinarySerializeRead(oBinaryBuffer, m_nDevice_Classify_Id);
		BinarySerializeRead(oBinaryBuffer, m_strComm_Type);
		BinarySerializeRead(oBinaryBuffer, m_strSuffix_File);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nId);
		BinarySerializeWrite(oBinaryBuffer, m_strCode);
		BinarySerializeWrite(oBinaryBuffer, m_nDevice_Classify_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strComm_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strSuffix_File);
	}
	return 0;
}

void CIot_RuleEngineConfig::InitAfterRead()
{
}

BOOL CIot_RuleEngineConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RuleEngineConfig *p = (CIot_RuleEngineConfig*)pObj;

	if(m_nId != p->m_nId)
	{
		return FALSE;
	}

	if(m_strCode != p->m_strCode)
	{
		return FALSE;
	}

	if(m_nDevice_Classify_Id != p->m_nDevice_Classify_Id)
	{
		return FALSE;
	}

	if(m_strComm_Type != p->m_strComm_Type)
	{
		return FALSE;
	}

	if(m_strSuffix_File != p->m_strSuffix_File)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RuleEngineConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RuleEngineConfig *p = (CIot_RuleEngineConfig*)pDest;

	p->m_nId = m_nId;
	p->m_strCode = m_strCode;
	p->m_nDevice_Classify_Id = m_nDevice_Classify_Id;
	p->m_strComm_Type = m_strComm_Type;
	p->m_strSuffix_File = m_strSuffix_File;
	return TRUE;
}

CBaseObject* CIot_RuleEngineConfig::Clone()
{
	CIot_RuleEngineConfig *p = new CIot_RuleEngineConfig();
	Copy(p);
	return p;
}

CBaseObject* CIot_RuleEngineConfig::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RuleEngineConfig *p = new CIot_RuleEngineConfig();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RuleEngineConfig::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strnIdKey, m_nId);
	pRecordset->GetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strDevice_Classify_IdKey, m_nDevice_Classify_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strComm_TypeKey, m_strComm_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strSuffix_FileKey, m_strSuffix_File);
	return 0;
}

long CIot_RuleEngineConfig::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strnIdKey, m_nId);
	pRecordset->SetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strDevice_Classify_IdKey, m_nDevice_Classify_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strComm_TypeKey, m_strComm_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strSuffix_FileKey, m_strSuffix_File);
	return 0;
}

BOOL CIot_RuleEngineConfig::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	return TRUE;
}

