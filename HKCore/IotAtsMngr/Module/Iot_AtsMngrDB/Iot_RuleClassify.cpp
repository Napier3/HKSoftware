//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RuleClassify.cpp  CIot_RuleClassify


#include "stdafx.h"
#include "Iot_RuleClassify.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RuleClassify::CIot_RuleClassify()
{
	//初始化属性
	m_nId = 0;
	::GetLocalTime(&m_tmCreate_Time);

	//初始化成员变量
}

CIot_RuleClassify::~CIot_RuleClassify()
{
}

long CIot_RuleClassify::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strnIdKey, oNode, m_nId);
	xml_GetAttibuteValue(pXmlKeys->m_strCodeKey, oNode, m_strCode);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	return 0;
}

long CIot_RuleClassify::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strnIdKey, oElement, m_nId);
	xml_SetAttributeValue(pXmlKeys->m_strCodeKey, oElement, m_strCode);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	return 0;
}

long CIot_RuleClassify::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nId);
		BinarySerializeCalLen(oBinaryBuffer, m_strCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nId);
		BinarySerializeRead(oBinaryBuffer, m_strCode);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nId);
		BinarySerializeWrite(oBinaryBuffer, m_strCode);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
	}
	return 0;
}

void CIot_RuleClassify::InitAfterRead()
{
}

BOOL CIot_RuleClassify::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RuleClassify *p = (CIot_RuleClassify*)pObj;

	if(m_nId != p->m_nId)
	{
		return FALSE;
	}

	if(m_strCode != p->m_strCode)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RuleClassify::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RuleClassify *p = (CIot_RuleClassify*)pDest;

	p->m_nId = m_nId;
	p->m_strCode = m_strCode;
	p->m_strName = m_strName;
	p->m_tmCreate_Time = m_tmCreate_Time;
	return TRUE;
}

CBaseObject* CIot_RuleClassify::Clone()
{
	CIot_RuleClassify *p = new CIot_RuleClassify();
	Copy(p);
	return p;
}

CBaseObject* CIot_RuleClassify::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RuleClassify *p = new CIot_RuleClassify();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RuleClassify::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strnIdKey, m_nId);
	pRecordset->GetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

long CIot_RuleClassify::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strnIdKey, m_nId);
	pRecordset->SetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

