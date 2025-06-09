//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TestApp.cpp  CIot_TestApp


#include "stdafx.h"
#include "Iot_TestApp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TestApp::CIot_TestApp()
{
	//初始化属性
	m_nIndex_Testapp = 0;
	m_nIndex_Device_Classify_Type = 0;
	m_nIndex_Factory = 0;
	m_nIndex_Dept = 0;
	m_nIndex_Engine = 0;
	m_nIndex_Device_Classify = 0;
	m_nPort = 0;
	m_nState = 0;
	m_nTest_State = 0;

	//初始化成员变量
}

CIot_TestApp::~CIot_TestApp()
{
}

long CIot_TestApp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestappKey, oNode, m_nIndex_Testapp);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_Classify_TypeKey, oNode, m_nIndex_Device_Classify_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FactoryKey, oNode, m_nIndex_Factory);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeptKey, oNode, m_nIndex_Dept);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_EngineKey, oNode, m_nIndex_Engine);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strIpKey, oNode, m_strIp);
	xml_GetAttibuteValue(pXmlKeys->m_strPortKey, oNode, m_nPort);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvm_File);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_nState);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_File_SKey, oNode, m_strDvm_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strTest_StateKey, oNode, m_nTest_State);
	return 0;
}

long CIot_TestApp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestappKey, oElement, m_nIndex_Testapp);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_Classify_TypeKey, oElement, m_nIndex_Device_Classify_Type);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FactoryKey, oElement, m_nIndex_Factory);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeptKey, oElement, m_nIndex_Dept);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_EngineKey, oElement, m_nIndex_Engine);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strIpKey, oElement, m_strIp);
	xml_SetAttributeValue(pXmlKeys->m_strPortKey, oElement, m_nPort);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvm_File);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_nState);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_File_SKey, oElement, m_strDvm_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strTest_StateKey, oElement, m_nTest_State);
	return 0;
}

long CIot_TestApp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeCalLen(oBinaryBuffer, m_strIp);
		BinarySerializeCalLen(oBinaryBuffer, m_nPort);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File);
		BinarySerializeCalLen(oBinaryBuffer, m_nState);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_nTest_State);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify_Type);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeRead(oBinaryBuffer, m_strIp);
		BinarySerializeRead(oBinaryBuffer, m_nPort);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File);
		BinarySerializeRead(oBinaryBuffer, m_nState);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeRead(oBinaryBuffer, m_nTest_State);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify_Type);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeWrite(oBinaryBuffer, m_strIp);
		BinarySerializeWrite(oBinaryBuffer, m_nPort);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File);
		BinarySerializeWrite(oBinaryBuffer, m_nState);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_nTest_State);
	}
	return 0;
}

void CIot_TestApp::InitAfterRead()
{
}

BOOL CIot_TestApp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_TestApp *p = (CIot_TestApp*)pObj;

	if(m_nIndex_Testapp != p->m_nIndex_Testapp)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Classify_Type != p->m_nIndex_Device_Classify_Type)
	{
		return FALSE;
	}

	if(m_nIndex_Factory != p->m_nIndex_Factory)
	{
		return FALSE;
	}

	if(m_nIndex_Dept != p->m_nIndex_Dept)
	{
		return FALSE;
	}

	if(m_nIndex_Engine != p->m_nIndex_Engine)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Classify != p->m_nIndex_Device_Classify)
	{
		return FALSE;
	}

	if(m_strIp != p->m_strIp)
	{
		return FALSE;
	}

	if(m_nPort != p->m_nPort)
	{
		return FALSE;
	}

	if(m_strDvm_File != p->m_strDvm_File)
	{
		return FALSE;
	}

	if(m_nState != p->m_nState)
	{
		return FALSE;
	}

	if(m_strDvm_File_S != p->m_strDvm_File_S)
	{
		return FALSE;
	}

	if(m_nTest_State != p->m_nTest_State)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TestApp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_TestApp *p = (CIot_TestApp*)pDest;

	p->m_nIndex_Testapp = m_nIndex_Testapp;
	p->m_nIndex_Device_Classify_Type = m_nIndex_Device_Classify_Type;
	p->m_nIndex_Factory = m_nIndex_Factory;
	p->m_nIndex_Dept = m_nIndex_Dept;
	p->m_nIndex_Engine = m_nIndex_Engine;
	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	p->m_strIp = m_strIp;
	p->m_nPort = m_nPort;
	p->m_strDvm_File = m_strDvm_File;
	p->m_nState = m_nState;
	p->m_strDvm_File_S = m_strDvm_File_S;
	p->m_nTest_State = m_nTest_State;
	return TRUE;
}

CBaseObject* CIot_TestApp::Clone()
{
	CIot_TestApp *p = new CIot_TestApp();
	Copy(p);
	return p;
}

CBaseObject* CIot_TestApp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TestApp *p = new CIot_TestApp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TestApp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_Classify_TypeKey, m_nIndex_Device_Classify_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strModelKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->GetFieldValue(pXmlKeys->m_strPortKey, m_nPort);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strTest_StateKey, m_nTest_State);
	return 0;
}

long CIot_TestApp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_Classify_TypeKey, m_nIndex_Device_Classify_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strModelKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->SetFieldValue(pXmlKeys->m_strPortKey, m_nPort);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strTest_StateKey, m_nTest_State);
	return 0;
}

BOOL CIot_TestApp::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_FACTORY)
	{
		m_nIndex_Factory = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEPT)
	{
		m_nIndex_Dept = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_ENGINE)
	{
		m_nIndex_Engine = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEVICE_CLASSIFY)
	{
		m_nIndex_Device_Classify = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

