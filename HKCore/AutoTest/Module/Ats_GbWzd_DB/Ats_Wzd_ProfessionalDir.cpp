//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_ProfessionalDir.cpp  CAts_Wzd_ProfessionalDir


#include "stdafx.h"
#include "Ats_Wzd_ProfessionalDir.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_ProfessionalDir::CAts_Wzd_ProfessionalDir()
{
	//初始化属性
	m_nHasULevel = 0;
	m_nIndex_Profession = 0;

	//初始化成员变量
}

CAts_Wzd_ProfessionalDir::~CAts_Wzd_ProfessionalDir()
{
}

long CAts_Wzd_ProfessionalDir::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strHasULevelKey, oNode, m_nHasULevel);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ProfessionKey, oNode, m_nIndex_Profession);
	return 0;
}

long CAts_Wzd_ProfessionalDir::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strHasULevelKey, oElement, m_nHasULevel);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ProfessionKey, oElement, m_nIndex_Profession);
	return 0;
}

long CAts_Wzd_ProfessionalDir::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nHasULevel);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Profession);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nHasULevel);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Profession);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nHasULevel);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Profession);
	}
	return 0;
}

void CAts_Wzd_ProfessionalDir::InitAfterRead()
{
}

BOOL CAts_Wzd_ProfessionalDir::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_ProfessionalDir *p = (CAts_Wzd_ProfessionalDir*)pObj;

	if(m_nHasULevel != p->m_nHasULevel)
	{
		return FALSE;
	}

	if(m_nIndex_Profession != p->m_nIndex_Profession)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_ProfessionalDir::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_ProfessionalDir *p = (CAts_Wzd_ProfessionalDir*)pDest;

	p->m_nHasULevel = m_nHasULevel;
	p->m_nIndex_Profession = m_nIndex_Profession;
	return TRUE;
}

CBaseObject* CAts_Wzd_ProfessionalDir::Clone()
{
	CAts_Wzd_ProfessionalDir *p = new CAts_Wzd_ProfessionalDir();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_ProfessionalDir::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_ProfessionalDir *p = new CAts_Wzd_ProfessionalDir();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_ProfessionalDir::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strProfessionNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strProfessionIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strHasULevelKey, m_nHasULevel);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ProfessionKey, m_nIndex_Profession);
	return 0;
}

long CAts_Wzd_ProfessionalDir::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strProfessionNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strProfessionIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strHasULevelKey, m_nHasULevel);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ProfessionKey, m_nIndex_Profession);
	return 0;
}

