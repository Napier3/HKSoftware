//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Engine.cpp  CIot_Engine


#include "stdafx.h"
#include "Iot_Engine.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Engine::CIot_Engine()
{
	//初始化属性
	m_nIndex_Engine = 0;
	m_nIndex_Folder = 0;
	m_nIndex_Device_Classify = 0;
	m_nEngine_Id = 0;
	m_nRule_Id = 0;
	m_nIndex_Engine_Dir = 0;
	::GetLocalTime(&m_tmCreate_Time);

	//初始化成员变量
}

CIot_Engine::~CIot_Engine()
{
}

long CIot_Engine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_EngineKey, oNode, m_nIndex_Engine);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FolderKey, oNode, m_nIndex_Folder);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strEngine_IdKey, oNode, m_nEngine_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strRule_IdKey, oNode, m_nRule_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strFile_NameKey, oNode, m_strFile_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strPath_Protocol_FileKey, oNode, m_strPath_Protocol_File);
	xml_GetAttibuteValue(pXmlKeys->m_strComm_TypeKey, oNode, m_strComm_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strRemarkKey, oNode, m_strRemark);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Engine_DirKey, oNode, m_nIndex_Engine_Dir);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	return 0;
}

long CIot_Engine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_EngineKey, oElement, m_nIndex_Engine);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FolderKey, oElement, m_nIndex_Folder);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strEngine_IdKey, oElement, m_nEngine_Id);
	xml_SetAttributeValue(pXmlKeys->m_strRule_IdKey, oElement, m_nRule_Id);
	xml_SetAttributeValue(pXmlKeys->m_strFile_NameKey, oElement, m_strFile_Name);
	xml_SetAttributeValue(pXmlKeys->m_strPath_Protocol_FileKey, oElement, m_strPath_Protocol_File);
	xml_SetAttributeValue(pXmlKeys->m_strComm_TypeKey, oElement, m_strComm_Type);
	xml_SetAttributeValue(pXmlKeys->m_strRemarkKey, oElement, m_strRemark);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Engine_DirKey, oElement, m_nIndex_Engine_Dir);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	return 0;
}

long CIot_Engine::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nEngine_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_nRule_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strPath_Protocol_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strComm_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strRemark);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Engine_Dir);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nEngine_Id);
		BinarySerializeRead(oBinaryBuffer, m_nRule_Id);
		BinarySerializeRead(oBinaryBuffer, m_strFile_Name);
		BinarySerializeRead(oBinaryBuffer, m_strPath_Protocol_File);
		BinarySerializeRead(oBinaryBuffer, m_strComm_Type);
		BinarySerializeRead(oBinaryBuffer, m_strRemark);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Engine_Dir);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nEngine_Id);
		BinarySerializeWrite(oBinaryBuffer, m_nRule_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strFile_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strPath_Protocol_File);
		BinarySerializeWrite(oBinaryBuffer, m_strComm_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strRemark);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Engine_Dir);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
	}
	return 0;
}

void CIot_Engine::InitAfterRead()
{
}

BOOL CIot_Engine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Engine *p = (CIot_Engine*)pObj;

	if(m_nIndex_Engine != p->m_nIndex_Engine)
	{
		return FALSE;
	}

	if(m_nIndex_Folder != p->m_nIndex_Folder)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Classify != p->m_nIndex_Device_Classify)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nEngine_Id != p->m_nEngine_Id)
	{
		return FALSE;
	}

	if(m_nRule_Id != p->m_nRule_Id)
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

	if(m_strComm_Type != p->m_strComm_Type)
	{
		return FALSE;
	}

	if(m_strRemark != p->m_strRemark)
	{
		return FALSE;
	}

	if(m_nIndex_Engine_Dir != p->m_nIndex_Engine_Dir)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Engine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Engine *p = (CIot_Engine*)pDest;

	p->m_nIndex_Engine = m_nIndex_Engine;
	p->m_nIndex_Folder = m_nIndex_Folder;
	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	p->m_strName = m_strName;
	p->m_nEngine_Id = m_nEngine_Id;
	p->m_nRule_Id = m_nRule_Id;
	p->m_strFile_Name = m_strFile_Name;
	p->m_strPath_Protocol_File = m_strPath_Protocol_File;
	p->m_strComm_Type = m_strComm_Type;
	p->m_strRemark = m_strRemark;
	p->m_nIndex_Engine_Dir = m_nIndex_Engine_Dir;
	p->m_tmCreate_Time = m_tmCreate_Time;
	return TRUE;
}

CBaseObject* CIot_Engine::Clone()
{
	CIot_Engine *p = new CIot_Engine();
	Copy(p);
	return p;
}

CBaseObject* CIot_Engine::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Engine *p = new CIot_Engine();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_Engine::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strEngine_IdKey, m_nEngine_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strRule_IdKey, m_nRule_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strFile_NameKey, m_strFile_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strPath_Protocol_FileKey, m_strPath_Protocol_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strComm_TypeKey, m_strComm_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strRemarkKey, m_strRemark);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Engine_DirKey, m_nIndex_Engine_Dir);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

long CIot_Engine::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strEngine_IdKey, m_nEngine_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strRule_IdKey, m_nRule_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strFile_NameKey, m_strFile_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strPath_Protocol_FileKey, m_strPath_Protocol_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strComm_TypeKey, m_strComm_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strRemarkKey, m_strRemark);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Engine_DirKey, m_nIndex_Engine_Dir);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

BOOL CIot_Engine::QueryDevicesByIndexEngine(CXDbBaseLib *pXDbLib,long nIndex_Engine)
{
	CString strEngineTable;
	CString strIndex_EngineKey,strSql;

	strEngineTable = CIot_AtsMngrXmlRWKeys::CIot_EngineKey();
	strIndex_EngineKey =  CIot_AtsMngrXmlRWKeys::Index_EngineKey();

	strSql.Format(_T("select * from %s where %s=%d limit 1"), strEngineTable, strIndex_EngineKey, nIndex_Engine);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}