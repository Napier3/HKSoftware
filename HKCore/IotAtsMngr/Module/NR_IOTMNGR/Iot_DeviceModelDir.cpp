//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceModelDir.cpp  CIot_DeviceModelDir


#include "stdafx.h"
#include "Iot_DeviceModelDir.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceModelDir::CIot_DeviceModelDir()
{
	//初始化属性
	m_nIndex_Model_Dir = 0;
	m_nParent_Index = 0;
	::GetLocalTime(&m_tmCreate_Time);

	//初始化成员变量
}

CIot_DeviceModelDir::~CIot_DeviceModelDir()
{
}

long CIot_DeviceModelDir::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Model_DirKey, oNode, m_nIndex_Model_Dir);
	xml_GetAttibuteValue(pXmlKeys->m_strDir_NameKey, oNode, m_strDir_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strParent_IndexKey, oNode, m_nParent_Index);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	return 0;
}

long CIot_DeviceModelDir::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Model_DirKey, oElement, m_nIndex_Model_Dir);
	xml_SetAttributeValue(pXmlKeys->m_strDir_NameKey, oElement, m_strDir_Name);
	xml_SetAttributeValue(pXmlKeys->m_strParent_IndexKey, oElement, m_nParent_Index);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	return 0;
}

long CIot_DeviceModelDir::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Model_Dir);
		BinarySerializeCalLen(oBinaryBuffer, m_strDir_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_nParent_Index);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Model_Dir);
		BinarySerializeRead(oBinaryBuffer, m_strDir_Name);
		BinarySerializeRead(oBinaryBuffer, m_nParent_Index);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Model_Dir);
		BinarySerializeWrite(oBinaryBuffer, m_strDir_Name);
		BinarySerializeWrite(oBinaryBuffer, m_nParent_Index);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
	}
	return 0;
}

void CIot_DeviceModelDir::InitAfterRead()
{
}

BOOL CIot_DeviceModelDir::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceModelDir *p = (CIot_DeviceModelDir*)pObj;

	if(m_nIndex_Model_Dir != p->m_nIndex_Model_Dir)
	{
		return FALSE;
	}

	if(m_strDir_Name != p->m_strDir_Name)
	{
		return FALSE;
	}

	if(m_nParent_Index != p->m_nParent_Index)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_DeviceModelDir::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceModelDir *p = (CIot_DeviceModelDir*)pDest;

	p->m_nIndex_Model_Dir = m_nIndex_Model_Dir;
	p->m_strDir_Name = m_strDir_Name;
	p->m_nParent_Index = m_nParent_Index;
	p->m_tmCreate_Time = m_tmCreate_Time;
	return TRUE;
}

CBaseObject* CIot_DeviceModelDir::Clone()
{
	CIot_DeviceModelDir *p = new CIot_DeviceModelDir();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceModelDir::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceModelDir *p = new CIot_DeviceModelDir();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceModelDir::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Model_DirKey, m_nIndex_Model_Dir);
	pRecordset->GetFieldValue(pXmlKeys->m_strDir_NameKey, m_strDir_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strParent_IndexKey, m_nParent_Index);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

long CIot_DeviceModelDir::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Model_DirKey, m_nIndex_Model_Dir);
	pRecordset->SetFieldValue(pXmlKeys->m_strDir_NameKey, m_strDir_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strParent_IndexKey, m_nParent_Index);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

