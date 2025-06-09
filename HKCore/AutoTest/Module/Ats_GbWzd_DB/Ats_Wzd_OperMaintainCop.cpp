//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_OperMaintainCop.cpp  CAts_Wzd_OperMaintainCop


#include "stdafx.h"
#include "Ats_Wzd_OperMaintainCop.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_OperMaintainCop::CAts_Wzd_OperMaintainCop()
{
	//初始化属性
	m_nIndex_Company = 0;

	//初始化成员变量
}

CAts_Wzd_OperMaintainCop::~CAts_Wzd_OperMaintainCop()
{
}

long CAts_Wzd_OperMaintainCop::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_CompanyKey, oNode, m_nIndex_Company);
	return 0;
}

long CAts_Wzd_OperMaintainCop::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_CompanyKey, oElement, m_nIndex_Company);
	return 0;
}

long CAts_Wzd_OperMaintainCop::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Company);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Company);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Company);
	}
	return 0;
}

void CAts_Wzd_OperMaintainCop::InitAfterRead()
{
}

BOOL CAts_Wzd_OperMaintainCop::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_Wzd_OperMaintainCop *p = (CAts_Wzd_OperMaintainCop*)pObj;

	if(m_nIndex_Company != p->m_nIndex_Company)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_OperMaintainCop::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAts_Wzd_OperMaintainCop *p = (CAts_Wzd_OperMaintainCop*)pDest;

	p->m_nIndex_Company = m_nIndex_Company;
	return TRUE;
}

CBaseObject* CAts_Wzd_OperMaintainCop::Clone()
{
	CAts_Wzd_OperMaintainCop *p = new CAts_Wzd_OperMaintainCop();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_OperMaintainCop::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_OperMaintainCop *p = new CAts_Wzd_OperMaintainCop();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_Wzd_OperMaintainCop::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_CompanyKey, m_nIndex_Company);
	pRecordset->GetFieldValue(pXmlKeys->m_strCompanyNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strCompanyIDKey, m_strID);
	return 0;
}

long CAts_Wzd_OperMaintainCop::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_CompanyKey, m_nIndex_Company);
	pRecordset->SetFieldValue(pXmlKeys->m_strCompanyNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strCompanyIDKey, m_strID);
	return 0;
}

