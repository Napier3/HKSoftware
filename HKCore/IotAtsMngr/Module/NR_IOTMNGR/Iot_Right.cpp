//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Right.cpp  CIot_Right


#include "stdafx.h"
#include "Iot_Right.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Right::CIot_Right()
{
	//初始化属性
	m_nVal_Right = 0;

	//初始化成员变量
}

CIot_Right::~CIot_Right()
{
}

long CIot_Right::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strVal_RightKey, oNode, m_nVal_Right);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);
	return 0;
}

long CIot_Right::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strVal_RightKey, oElement, m_nVal_Right);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strDescriptionKey, oElement, m_strDescription);
	return 0;
}

long CIot_Right::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nVal_Right);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nVal_Right);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strDescription);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nVal_Right);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strDescription);
	}
	return 0;
}

void CIot_Right::InitAfterRead()
{
}

BOOL CIot_Right::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Right *p = (CIot_Right*)pObj;

	if(m_nVal_Right != p->m_nVal_Right)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strDescription != p->m_strDescription)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Right::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Right *p = (CIot_Right*)pDest;

	p->m_nVal_Right = m_nVal_Right;
	p->m_strName = m_strName;
	p->m_strDescription = m_strDescription;
	return TRUE;
}

CBaseObject* CIot_Right::Clone()
{
	CIot_Right *p = new CIot_Right();
	Copy(p);
	return p;
}

CBaseObject* CIot_Right::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Right *p = new CIot_Right();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_Right::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strVal_RightKey, m_nVal_Right);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDescriptionKey, m_strDescription);
	return 0;
}

long CIot_Right::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strVal_RightKey, m_nVal_Right);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDescriptionKey, m_strDescription);
	return 0;
}

