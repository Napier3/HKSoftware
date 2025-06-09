//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceModel.cpp  CIot_DeviceModel


#include "stdafx.h"
#include "Iot_DeviceModel.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceModel::CIot_DeviceModel()
{
	//初始化属性
	m_nIndex_Model = 0;
	m_nIndex_Device_Classify = 0;
	m_nIndex_Device_Type = 0;
	m_nIndex_Factory = 0;
	m_nIndex_Model_Dir = 0;
	::GetLocalTime(&m_tmCreate_Time);

	//初始化成员变量
}

CIot_DeviceModel::~CIot_DeviceModel()
{
}

long CIot_DeviceModel::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ModelKey, oNode, m_nIndex_Model);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_TypeKey, oNode, m_nIndex_Device_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FactoryKey, oNode, m_nIndex_Factory);
	xml_GetAttibuteValue(pXmlKeys->m_strFile_NameKey, oNode, m_strFile_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strPath_Protocol_FileKey, oNode, m_strPath_Protocol_File);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Model_DirKey, oNode, m_nIndex_Model_Dir);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	return 0;
}

long CIot_DeviceModel::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_ModelKey, oElement, m_nIndex_Model);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_TypeKey, oElement, m_nIndex_Device_Type);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FactoryKey, oElement, m_nIndex_Factory);
	xml_SetAttributeValue(pXmlKeys->m_strFile_NameKey, oElement, m_strFile_Name);
	xml_SetAttributeValue(pXmlKeys->m_strPath_Protocol_FileKey, oElement, m_strPath_Protocol_File);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Model_DirKey, oElement, m_nIndex_Model_Dir);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	return 0;
}

long CIot_DeviceModel::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Model);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strPath_Protocol_File);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Model_Dir);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Model);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeRead(oBinaryBuffer, m_strFile_Name);
		BinarySerializeRead(oBinaryBuffer, m_strPath_Protocol_File);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Model_Dir);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Model);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeWrite(oBinaryBuffer, m_strFile_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strPath_Protocol_File);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Model_Dir);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
	}
	return 0;
}

void CIot_DeviceModel::InitAfterRead()
{
}

BOOL CIot_DeviceModel::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceModel *p = (CIot_DeviceModel*)pObj;

	if(m_nIndex_Model != p->m_nIndex_Model)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Classify != p->m_nIndex_Device_Classify)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Type != p->m_nIndex_Device_Type)
	{
		return FALSE;
	}

	if(m_nIndex_Factory != p->m_nIndex_Factory)
	{
		return FALSE;
	}

	if(m_strFile_Name != p->m_strFile_Name)
	{
		return FALSE;
	}

	if(m_strPath_Protocol_File != p->m_strPath_Protocol_File)
	{
		return FALSE;
	}

	if(m_nIndex_Model_Dir != p->m_nIndex_Model_Dir)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_DeviceModel::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceModel *p = (CIot_DeviceModel*)pDest;

	p->m_nIndex_Model = m_nIndex_Model;
	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	p->m_nIndex_Device_Type = m_nIndex_Device_Type;
	p->m_nIndex_Factory = m_nIndex_Factory;
	p->m_strFile_Name = m_strFile_Name;
	p->m_strPath_Protocol_File = m_strPath_Protocol_File;
	p->m_nIndex_Model_Dir = m_nIndex_Model_Dir;
	p->m_tmCreate_Time = m_tmCreate_Time;
	return TRUE;
}

CBaseObject* CIot_DeviceModel::Clone()
{
	CIot_DeviceModel *p = new CIot_DeviceModel();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceModel::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceModel *p = new CIot_DeviceModel();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceModel::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ModelKey, m_nIndex_Model);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->GetFieldValue(pXmlKeys->m_strFile_NameKey, m_strFile_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strPath_Protocol_FileKey, m_strPath_Protocol_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Model_DirKey, m_nIndex_Model_Dir);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

long CIot_DeviceModel::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ModelKey, m_nIndex_Model);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->SetFieldValue(pXmlKeys->m_strFile_NameKey, m_strFile_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strPath_Protocol_FileKey, m_strPath_Protocol_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Model_DirKey, m_nIndex_Model_Dir);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

BOOL CIot_DeviceModel::QueryDevicesByIndexModel(CXDbBaseLib *pXDbLib,long nIndex_Model)
{
	CString strDeviceModelTable;
	CString strIndex_ModelKey,strSql;

	strDeviceModelTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceModelKey();
	strIndex_ModelKey =  CIot_AtsMngrXmlRWKeys::Index_ModelKey();

	strSql.Format(_T("select * from %s where %s=%d limit 1"), strDeviceModelTable, strIndex_ModelKey, nIndex_Model);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}