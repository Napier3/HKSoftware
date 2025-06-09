//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Device_Classify.cpp  CIot_Device_Classify


#include "stdafx.h"
#include "Iot_Device_Classify.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Device_Classify::CIot_Device_Classify()
{
	//初始化属性
	m_nIndex_Device_Classify = 0;

	//初始化成员变量
}

CIot_Device_Classify::~CIot_Device_Classify()
{
}

long CIot_Device_Classify::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strCodeKey, oNode, m_strCode);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	return 0;
}

long CIot_Device_Classify::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strCodeKey, oElement, m_strCode);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	return 0;
}

long CIot_Device_Classify::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeCalLen(oBinaryBuffer, m_strCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeRead(oBinaryBuffer, m_strCode);
		BinarySerializeRead(oBinaryBuffer, m_strName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeWrite(oBinaryBuffer, m_strCode);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
	}
	return 0;
}

void CIot_Device_Classify::InitAfterRead()
{
}

BOOL CIot_Device_Classify::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Device_Classify *p = (CIot_Device_Classify*)pObj;

	if(m_nIndex_Device_Classify != p->m_nIndex_Device_Classify)
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

BOOL CIot_Device_Classify::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Device_Classify *p = (CIot_Device_Classify*)pDest;

	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	p->m_strCode = m_strCode;
	p->m_strName = m_strName;
	return TRUE;
}

CBaseObject* CIot_Device_Classify::Clone()
{
	CIot_Device_Classify *p = new CIot_Device_Classify();
	Copy(p);
	return p;
}

CBaseObject* CIot_Device_Classify::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Device_Classify *p = new CIot_Device_Classify();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_Device_Classify::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

long CIot_Device_Classify::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strCodeKey, m_strCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	return 0;
}

