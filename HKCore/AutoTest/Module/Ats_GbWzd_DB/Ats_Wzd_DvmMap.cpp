//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_DvmMap.cpp  CAts_Wzd_DvmMap


#include "stdafx.h"
#include "Ats_Wzd_DvmMap.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_DvmMap::CAts_Wzd_DvmMap()
{
	//初始化属性
	m_nIndex_DvmMap = 0;

	//初始化成员变量
}

CAts_Wzd_DvmMap::~CAts_Wzd_DvmMap()
{
}

long CAts_Wzd_DvmMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DvmMapKey, oNode, m_nIndex_DvmMap);
	xml_GetAttibuteValue(pXmlKeys->m_strStandDvmFileNameKey, oNode, m_strStandDvmFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strDestDvmFileNameKey, oNode, m_strDestDvmFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strMapFileNameKey, oNode, m_strMapFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strFullPathKey, oNode, m_strFullPath);
	return 0;
}

long CAts_Wzd_DvmMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_DvmMapKey, oElement, m_nIndex_DvmMap);
	xml_SetAttributeValue(pXmlKeys->m_strStandDvmFileNameKey, oElement, m_strStandDvmFileName);
	xml_SetAttributeValue(pXmlKeys->m_strDestDvmFileNameKey, oElement, m_strDestDvmFileName);
	xml_SetAttributeValue(pXmlKeys->m_strMapFileNameKey, oElement, m_strMapFileName);
	xml_SetAttributeValue(pXmlKeys->m_strFullPathKey, oElement, m_strFullPath);
	return 0;
}

long CAts_Wzd_DvmMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_DvmMap);
		BinarySerializeCalLen(oBinaryBuffer, m_strStandDvmFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDestDvmFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strMapFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strFullPath);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_DvmMap);
		BinarySerializeRead(oBinaryBuffer, m_strStandDvmFileName);
		BinarySerializeRead(oBinaryBuffer, m_strDestDvmFileName);
		BinarySerializeRead(oBinaryBuffer, m_strMapFileName);
		BinarySerializeRead(oBinaryBuffer, m_strFullPath);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_DvmMap);
		BinarySerializeWrite(oBinaryBuffer, m_strStandDvmFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strDestDvmFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strMapFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strFullPath);
	}
	return 0;
}

void CAts_Wzd_DvmMap::InitAfterRead()
{
}

BOOL CAts_Wzd_DvmMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_DvmMap *p = (CAts_Wzd_DvmMap*)pObj;

	if(m_nIndex_DvmMap != p->m_nIndex_DvmMap)
	{
		return FALSE;
	}

	if(m_strStandDvmFileName != p->m_strStandDvmFileName)
	{
		return FALSE;
	}

	if(m_strDestDvmFileName != p->m_strDestDvmFileName)
	{
		return FALSE;
	}

	if(m_strMapFileName != p->m_strMapFileName)
	{
		return FALSE;
	}

	if(m_strFullPath != p->m_strFullPath)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_DvmMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_DvmMap *p = (CAts_Wzd_DvmMap*)pDest;

	p->m_nIndex_DvmMap = m_nIndex_DvmMap;
	p->m_strStandDvmFileName = m_strStandDvmFileName;
	p->m_strDestDvmFileName = m_strDestDvmFileName;
	p->m_strMapFileName = m_strMapFileName;
	p->m_strFullPath = m_strFullPath;
	return TRUE;
}

CBaseObject* CAts_Wzd_DvmMap::Clone()
{
	CAts_Wzd_DvmMap *p = new CAts_Wzd_DvmMap();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_DvmMap::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_DvmMap *p = new CAts_Wzd_DvmMap();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_DvmMap::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DvmMapKey, m_nIndex_DvmMap);
	pRecordset->GetFieldValue(pXmlKeys->m_strStandDvmFileNameKey, m_strStandDvmFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDestDvmFileNameKey, m_strDestDvmFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strMapFileNameKey, m_strMapFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strFullPathKey, m_strFullPath);
	return 0;
}

long CAts_Wzd_DvmMap::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DvmMapKey, m_nIndex_DvmMap);
	pRecordset->SetFieldValue(pXmlKeys->m_strStandDvmFileNameKey, m_strStandDvmFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDestDvmFileNameKey, m_strDestDvmFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strMapFileNameKey, m_strMapFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strFullPathKey, m_strFullPath);
	return 0;
}

