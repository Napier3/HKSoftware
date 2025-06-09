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
	m_nProtocol_File = 0;
	m_nIndex_Engine_Dir = 0;
	::GetLocalTime(&m_tmCreate_Time);

	//初始化成员变量
}

CIot_Engine::~CIot_Engine()
{
}

long CIot_Engine::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_EngineKey, oNode, m_nIndex_Engine);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FolderKey, oNode, m_nIndex_Folder);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strEngine_IdKey, oNode, m_nEngine_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strRule_IdKey, oNode, m_nRule_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_FileKey, oNode, m_nProtocol_File);
	xml_GetAttibuteValue(pXmlKeys->m_strComm_TypeKey, oNode, m_strComm_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Engine_DirKey, oNode, m_nIndex_Engine_Dir);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_File_SKey, oNode, m_strProtocol_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	return 0;
}

long CIot_Engine::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_EngineKey, oElement, m_nIndex_Engine);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FolderKey, oElement, m_nIndex_Folder);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strEngine_IdKey, oElement, m_nEngine_Id);
	xml_SetAttributeValue(pXmlKeys->m_strRule_IdKey, oElement, m_nRule_Id);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_FileKey, oElement, m_nProtocol_File);
	xml_SetAttributeValue(pXmlKeys->m_strComm_TypeKey, oElement, m_strComm_Type);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Engine_DirKey, oElement, m_nIndex_Engine_Dir);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_File_SKey, oElement, m_strProtocol_File_S);
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
		BinarySerializeCalLen(oBinaryBuffer, m_nProtocol_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strComm_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Engine_Dir);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol_File_S);
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
		BinarySerializeRead(oBinaryBuffer, m_nProtocol_File);
		BinarySerializeRead(oBinaryBuffer, m_strComm_Type);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Engine_Dir);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol_File_S);
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
		BinarySerializeWrite(oBinaryBuffer, m_nProtocol_File);
		BinarySerializeWrite(oBinaryBuffer, m_strComm_Type);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Engine_Dir);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol_File_S);
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

	if(m_nProtocol_File != p->m_nProtocol_File)
	{
		return FALSE;
	}

	if(m_strComm_Type != p->m_strComm_Type)
	{
		return FALSE;
	}

	if(m_nIndex_Engine_Dir != p->m_nIndex_Engine_Dir)
	{
		return FALSE;
	}

	if(m_strProtocol_File_S != p->m_strProtocol_File_S)
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
	p->m_nProtocol_File = m_nProtocol_File;
	p->m_strComm_Type = m_strComm_Type;
	p->m_nIndex_Engine_Dir = m_nIndex_Engine_Dir;
	p->m_strProtocol_File_S = m_strProtocol_File_S;
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
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strEngine_IdKey, m_nEngine_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strRule_IdKey, m_nRule_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_nProtocol_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strComm_TypeKey, m_strComm_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Engine_DirKey, m_nIndex_Engine_Dir);
	pRecordset->GetFieldValue(pXmlKeys->m_strProtocol_File_SKey, m_strProtocol_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

long CIot_Engine::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strEngine_IdKey, m_nEngine_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strRule_IdKey, m_nRule_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_nProtocol_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strComm_TypeKey, m_strComm_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Engine_DirKey, m_nIndex_Engine_Dir);
	pRecordset->SetFieldValue(pXmlKeys->m_strProtocol_File_SKey, m_strProtocol_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

BOOL CIot_Engine::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TEMPLATEFOLDER)
	{
		m_nIndex_Folder = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEVICE_CLASSIFY)
	{
		m_nIndex_Device_Classify = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_ENGINE_DIR)
	{
		m_nIndex_Engine_Dir = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

