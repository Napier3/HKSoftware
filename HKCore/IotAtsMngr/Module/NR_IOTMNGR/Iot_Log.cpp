//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Log.cpp  CIot_Log


#include "stdafx.h"
#include "Iot_Log.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Log::CIot_Log()
{
	//初始化属性
	m_nIndex_Log = 0;
	m_nIndex_Test = 0;
	::GetLocalTime(&m_tmTm_Update);

	//初始化成员变量
}

CIot_Log::~CIot_Log()
{
}

long CIot_Log::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_LogKey, oNode, m_nIndex_Log);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestKey, oNode, m_nIndex_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strTxt_LogKey, oNode, m_strTxt_Log);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_UpdateKey, oNode, m_tmTm_Update);
	return 0;
}

long CIot_Log::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_LogKey, oElement, m_nIndex_Log);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestKey, oElement, m_nIndex_Test);
	xml_SetAttributeValue(pXmlKeys->m_strTxt_LogKey, oElement, m_strTxt_Log);
	xml_SetAttributeValue(pXmlKeys->m_strTm_UpdateKey, oElement, m_tmTm_Update);
	return 0;
}

long CIot_Log::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Log);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_strTxt_Log);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Update);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Log);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeRead(oBinaryBuffer, m_strTxt_Log);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Update);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Log);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeWrite(oBinaryBuffer, m_strTxt_Log);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Update);
	}
	return 0;
}

void CIot_Log::InitAfterRead()
{
}

BOOL CIot_Log::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Log *p = (CIot_Log*)pObj;

	if(m_nIndex_Log != p->m_nIndex_Log)
	{
		return FALSE;
	}

	if(m_nIndex_Test != p->m_nIndex_Test)
	{
		return FALSE;
	}

	if(m_strTxt_Log != p->m_strTxt_Log)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Log::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Log *p = (CIot_Log*)pDest;

	p->m_nIndex_Log = m_nIndex_Log;
	p->m_nIndex_Test = m_nIndex_Test;
	p->m_strTxt_Log = m_strTxt_Log;
	p->m_tmTm_Update = m_tmTm_Update;
	return TRUE;
}

CBaseObject* CIot_Log::Clone()
{
	CIot_Log *p = new CIot_Log();
	Copy(p);
	return p;
}

CBaseObject* CIot_Log::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Log *p = new CIot_Log();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_Log::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_LogKey, m_nIndex_Log);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strTxt_LogKey, m_strTxt_Log);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	return 0;
}

long CIot_Log::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_LogKey, m_nIndex_Log);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strTxt_LogKey, m_strTxt_Log);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	return 0;
}

