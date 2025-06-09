//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_Factory.cpp  CAts_Wzd_Factory


#include "stdafx.h"
#include "Ats_Wzd_Factory.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_Factory::CAts_Wzd_Factory()
{
	//初始化属性
	m_nIndex_Factory = 0;

	//初始化成员变量
}

CAts_Wzd_Factory::~CAts_Wzd_Factory()
{
}

long CAts_Wzd_Factory::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FactoryKey, oNode, m_nIndex_Factory);
	return 0;
}

long CAts_Wzd_Factory::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_FactoryKey, oElement, m_nIndex_Factory);
	return 0;
}

long CAts_Wzd_Factory::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Factory);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Factory);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Factory);
	}
	return 0;
}

void CAts_Wzd_Factory::InitAfterRead()
{
}

BOOL CAts_Wzd_Factory::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_Factory *p = (CAts_Wzd_Factory*)pObj;

	if(m_nIndex_Factory != p->m_nIndex_Factory)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_Factory::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_Factory *p = (CAts_Wzd_Factory*)pDest;

	p->m_nIndex_Factory = m_nIndex_Factory;
	return TRUE;
}

CBaseObject* CAts_Wzd_Factory::Clone()
{
	CAts_Wzd_Factory *p = new CAts_Wzd_Factory();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_Factory::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_Factory *p = new CAts_Wzd_Factory();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_Factory::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->GetFieldValue(pXmlKeys->m_strFactoryNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strFactoryIDKey, m_strID);
	return 0;
}

long CAts_Wzd_Factory::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->SetFieldValue(pXmlKeys->m_strFactoryNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strFactoryIDKey, m_strID);
	return 0;
}

