//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_ULevel.cpp  CAts_Wzd_ULevel


#include "stdafx.h"
#include "Ats_Wzd_ULevel.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_ULevel::CAts_Wzd_ULevel()
{
	//初始化属性
	m_nIndex_ULevel = 0;
	m_nIndex_Profession = 0;

	//初始化成员变量
}

CAts_Wzd_ULevel::~CAts_Wzd_ULevel()
{
}

long CAts_Wzd_ULevel::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ULevelKey, oNode, m_nIndex_ULevel);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ProfessionKey, oNode, m_nIndex_Profession);
	return 0;
}

long CAts_Wzd_ULevel::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_ULevelKey, oElement, m_nIndex_ULevel);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ProfessionKey, oElement, m_nIndex_Profession);
	return 0;
}

long CAts_Wzd_ULevel::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_ULevel);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Profession);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_ULevel);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Profession);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_ULevel);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Profession);
	}
	return 0;
}

void CAts_Wzd_ULevel::InitAfterRead()
{
	m_strName = m_strID;
}

BOOL CAts_Wzd_ULevel::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_ULevel *p = (CAts_Wzd_ULevel*)pObj;

	if(m_nIndex_ULevel != p->m_nIndex_ULevel)
	{
		return FALSE;
	}

	if(m_nIndex_Profession != p->m_nIndex_Profession)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_ULevel::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_ULevel *p = (CAts_Wzd_ULevel*)pDest;

	p->m_nIndex_ULevel = m_nIndex_ULevel;
	p->m_nIndex_Profession = m_nIndex_Profession;
	return TRUE;
}

CBaseObject* CAts_Wzd_ULevel::Clone()
{
	CAts_Wzd_ULevel *p = new CAts_Wzd_ULevel();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_ULevel::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_ULevel *p = new CAts_Wzd_ULevel();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_ULevel::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ULevelKey, m_nIndex_ULevel);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ProfessionKey, m_nIndex_Profession);
	//pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strULevelIDKey, m_strID);
	return 0;
}

long CAts_Wzd_ULevel::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ULevelKey, m_nIndex_ULevel);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ProfessionKey, m_nIndex_Profession);
	//pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strULevelIDKey, m_strID);
	return 0;
}

BOOL CAts_Wzd_ULevel::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSGBWIZRDCLASSID_CATS_WZD_PROFESSIONALDIR)
	{
		m_nIndex_Profession = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

