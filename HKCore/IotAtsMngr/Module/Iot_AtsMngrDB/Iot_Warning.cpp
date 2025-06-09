//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Warning.cpp  CIot_Warning


#include "stdafx.h"
#include "Iot_Warning.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Warning::CIot_Warning()
{
	//初始化属性
	m_nIndex_Warning = 0;
	m_nIndex_Device = 0;
	m_fVal_Warning = 0.0;
	::GetLocalTime(&m_tmTm_Warning);
}

CIot_Warning::~CIot_Warning()
{
}

long CIot_Warning::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strIndex_WarningKey, oNode, m_nIndex_Warning);
	xml_GetElementText(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetElementText(pXmlKeys->m_strVal_WarningKey, oNode, m_fVal_Warning);
	xml_GetElementText(pXmlKeys->m_strSnKey, oNode, m_strSn);
	xml_GetElementText(pXmlKeys->m_strEventKey, oNode, m_strEvent);
	xml_GetElementText(pXmlKeys->m_strTm_WarningKey, oNode, m_tmTm_Warning);
	return 0;
}

long CIot_Warning::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strIndex_WarningKey, oXMLDoc, oElement, m_nIndex_Warning);
	xml_SetElementText(pXmlKeys->m_strIndex_DeviceKey, oXMLDoc, oElement, m_nIndex_Device);
	xml_SetElementText(pXmlKeys->m_strVal_WarningKey, oXMLDoc, oElement, m_fVal_Warning);
	xml_SetElementText(pXmlKeys->m_strSnKey, oXMLDoc, oElement, m_strSn);
	xml_SetElementText(pXmlKeys->m_strEventKey, oXMLDoc, oElement, m_strEvent);
	xml_SetElementText(pXmlKeys->m_strTm_WarningKey, oXMLDoc, oElement, m_tmTm_Warning);

	return 0;
}

long CIot_Warning::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Warning);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_fVal_Warning);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn);
		BinarySerializeCalLen(oBinaryBuffer, m_strEvent);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Warning);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Warning);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_fVal_Warning);
		BinarySerializeRead(oBinaryBuffer, m_strSn);
		BinarySerializeRead(oBinaryBuffer, m_strEvent);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Warning);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Warning);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_fVal_Warning);
		BinarySerializeWrite(oBinaryBuffer, m_strSn);
		BinarySerializeWrite(oBinaryBuffer, m_strEvent);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Warning);
	}
	return 0;
}

void CIot_Warning::InitAfterRead()
{
}

BOOL CIot_Warning::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Warning *p = (CIot_Warning*)pObj;

	if(m_nIndex_Warning != p->m_nIndex_Warning)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_fVal_Warning != p->m_fVal_Warning)
	{
		return FALSE;
	}

	if(m_strSn != p->m_strSn)
	{
		return FALSE;
	}

	if(m_strEvent != p->m_strEvent)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Warning::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Warning *p = (CIot_Warning*)pDest;

	p->m_nIndex_Warning = m_nIndex_Warning;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_strEvent = m_strEvent;
	p->m_strSn = m_strSn;
	p->m_fVal_Warning = m_fVal_Warning;
	p->m_tmTm_Warning = m_tmTm_Warning;
	return TRUE;
}

CBaseObject* CIot_Warning::Clone()
{
	CIot_Warning *p = new CIot_Warning();
	Copy(p);
	return p;
}

CBaseObject* CIot_Warning::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Warning *p = new CIot_Warning();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_Warning::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_WarningKey, m_nIndex_Warning);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strVal_WarningKey, m_fVal_Warning);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->GetFieldValue(pXmlKeys->m_strEventKey, m_strEvent);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_WarningKey, m_tmTm_Warning);
	return 0;
}

long CIot_Warning::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_WarningKey, m_nIndex_Warning);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strVal_WarningKey, m_fVal_Warning);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strSn);
	pRecordset->SetFieldValue(pXmlKeys->m_strEventKey, m_strEvent);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_WarningKey, m_tmTm_Warning);
	return 0;
}
