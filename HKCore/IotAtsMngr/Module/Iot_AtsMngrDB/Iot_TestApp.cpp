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
	m_nIndex_Dept = 0;
	m_nIndex_Device_Classify = 0;
	m_nIndex_Device_Type = 0;
	m_nIndex_Factory = 0;
	m_nIndex_Engine = 0;
	m_nPort = 0;
	m_nIndex_Model = 0;
	m_nTest_State = DEV_TEST_STATE_NOMAL;
	m_nConnect_State = DEV_CONNECT_STATE_OFF;
	::GetLocalTime(&m_tmCreate_Time);
	m_nIsUpdate = 0;// 当天的更新天数是否已更新。一天可能使用多次，但只能累计使用天数+1
	m_nUseDays = 0;   //当年的使用天数，每年1月1日0点清零
	m_nUseDaysAll = 0;  //总的使用天数
	m_nUseCounts = 0;

	//初始化成员变量
}

CIot_TestApp::~CIot_TestApp()
{
}

long CIot_TestApp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestappKey, oNode, m_nIndex_Testapp);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeptKey, oNode, m_nIndex_Dept);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_TypeKey, oNode, m_nIndex_Device_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FactoryKey, oNode, m_nIndex_Factory);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_EngineKey, oNode, m_nIndex_Engine);
	xml_GetAttibuteValue(pXmlKeys->m_strIpKey, oNode, m_strIp);
	xml_GetAttibuteValue(pXmlKeys->m_strPortKey, oNode, m_nPort);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ModelKey, oNode, m_nIndex_Model);
	xml_GetAttibuteValue(pXmlKeys->m_strTest_StateKey, oNode, m_nTest_State);
	xml_GetAttibuteValue(pXmlKeys->m_strConnect_StateKey, oNode, m_nConnect_State);	
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	xml_GetAttibuteValue(pXmlKeys->m_strUseDaysKey, oNode, m_nUseDays);
	xml_GetAttibuteValue(pXmlKeys->m_strUseDaysAllKey, oNode, m_nUseDaysAll);
	xml_GetAttibuteValue(pXmlKeys->m_strUseCountsKey, oNode, m_nUseCounts);
	xml_GetAttibuteValue(pXmlKeys->m_strIsUpdateKey, oNode, m_nIsUpdate);
	return 0;
}

long CIot_TestApp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestappKey, oElement, m_nIndex_Testapp);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeptKey, oElement, m_nIndex_Dept);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_TypeKey, oElement, m_nIndex_Device_Type);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FactoryKey, oElement, m_nIndex_Factory);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_EngineKey, oElement, m_nIndex_Engine);
	xml_SetAttributeValue(pXmlKeys->m_strIpKey, oElement, m_strIp);
	xml_SetAttributeValue(pXmlKeys->m_strPortKey, oElement, m_nPort);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ModelKey, oElement, m_nIndex_Model);
	xml_SetAttributeValue(pXmlKeys->m_strTest_StateKey, oElement, m_nTest_State);
	xml_SetAttributeValue(pXmlKeys->m_strConnect_StateKey, oElement, m_nConnect_State);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	xml_SetAttributeValue(pXmlKeys->m_strUseDaysKey, oElement, m_nUseDays);
	xml_SetAttributeValue(pXmlKeys->m_strUseDaysAllKey, oElement, m_nUseDaysAll);
	xml_SetAttributeValue(pXmlKeys->m_strUseCountsKey, oElement, m_nUseCounts);
	xml_SetAttributeValue(pXmlKeys->m_strIsUpdateKey, oElement, m_nIsUpdate);
	return 0;
}

long CIot_TestApp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeCalLen(oBinaryBuffer, m_strIp);
		BinarySerializeCalLen(oBinaryBuffer, m_nPort);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Model);
		BinarySerializeCalLen(oBinaryBuffer, m_nTest_State);
		BinarySerializeCalLen(oBinaryBuffer, m_nConnect_State);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseDays);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseDaysAll);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseCounts);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsUpdate);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeRead(oBinaryBuffer, m_strIp);
		BinarySerializeRead(oBinaryBuffer, m_nPort);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Model);
		BinarySerializeRead(oBinaryBuffer, m_nTest_State);
		BinarySerializeRead(oBinaryBuffer, m_nConnect_State);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeRead(oBinaryBuffer, m_nUseDays);
		BinarySerializeRead(oBinaryBuffer, m_nUseDaysAll);
		BinarySerializeRead(oBinaryBuffer, m_nUseCounts);
		BinarySerializeRead(oBinaryBuffer, m_nIsUpdate);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeWrite(oBinaryBuffer, m_strIp);
		BinarySerializeWrite(oBinaryBuffer, m_nPort);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Model);
		BinarySerializeWrite(oBinaryBuffer, m_nTest_State);
		BinarySerializeWrite(oBinaryBuffer, m_nConnect_State);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeWrite(oBinaryBuffer, m_nUseDays);
		BinarySerializeWrite(oBinaryBuffer, m_nUseDaysAll);
		BinarySerializeWrite(oBinaryBuffer, m_nUseCounts);
		BinarySerializeWrite(oBinaryBuffer, m_nIsUpdate);
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

	if(m_nIndex_Dept != p->m_nIndex_Dept)
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

	if(m_nIndex_Engine != p->m_nIndex_Engine)
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

	if(m_nIndex_Model != p->m_nIndex_Model)
	{
		return FALSE;
	}

	if(m_nTest_State != p->m_nTest_State)
	{
		return FALSE;
	}

	if(m_nConnect_State != p->m_nConnect_State)
	{
		return FALSE;
	}

	if(m_nUseDays != p->m_nUseDays)
	{
		return FALSE;
	}

	if(m_nUseDaysAll != p->m_nUseDaysAll)
	{
		return FALSE;
	}

	if(m_nUseCounts != p->m_nUseCounts)
	{
		return FALSE;
	}

	if(m_nIsUpdate != p->m_nIsUpdate)
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
	p->m_nIndex_Dept = m_nIndex_Dept;
	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	p->m_nIndex_Device_Type = m_nIndex_Device_Type;
	p->m_nIndex_Factory = m_nIndex_Factory;
	p->m_nIndex_Engine = m_nIndex_Engine;
	p->m_strIp = m_strIp;
	p->m_nPort = m_nPort;
	p->m_nIndex_Model = m_nIndex_Model;
	p->m_nTest_State = m_nTest_State;
	p->m_nConnect_State = m_nConnect_State;
	p->m_tmCreate_Time = m_tmCreate_Time;
	p->m_nUseDays = m_nUseDays;
	p->m_nUseDaysAll = m_nUseDaysAll;
	p->m_nUseCounts = m_nUseCounts;
	p->m_nIsUpdate = m_nIsUpdate;
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
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->GetFieldValue(pXmlKeys->m_strModelKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->GetFieldValue(pXmlKeys->m_strPortKey, m_nPort);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ModelKey, m_nIndex_Model);
	pRecordset->GetFieldValue(pXmlKeys->m_strTest_StateKey, m_nTest_State);
	pRecordset->GetFieldValue(pXmlKeys->m_strConnect_StateKey, m_nConnect_State);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	pRecordset->GetFieldValue(pXmlKeys->m_strUseDaysKey, m_nUseDays);
	pRecordset->GetFieldValue(pXmlKeys->m_strUseDaysAllKey, m_nUseDaysAll);
	pRecordset->GetFieldValue(pXmlKeys->m_strUseCountsKey, m_nUseCounts);
	pRecordset->GetFieldValue(pXmlKeys->m_strIsUpdateKey, m_nIsUpdate);
	return 0;
}

long CIot_TestApp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->SetFieldValue(pXmlKeys->m_strModelKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->SetFieldValue(pXmlKeys->m_strPortKey, m_nPort);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ModelKey, m_nIndex_Model);
	pRecordset->SetFieldValue(pXmlKeys->m_strTest_StateKey, m_nTest_State);
	pRecordset->SetFieldValue(pXmlKeys->m_strConnect_StateKey, m_nConnect_State);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	pRecordset->SetFieldValue(pXmlKeys->m_strUseDaysKey, m_nUseDays);
	pRecordset->SetFieldValue(pXmlKeys->m_strUseDaysAllKey, m_nUseDaysAll);
	pRecordset->SetFieldValue(pXmlKeys->m_strUseCountsKey, m_nUseCounts);
	pRecordset->SetFieldValue(pXmlKeys->m_strIsUpdateKey, m_nIsUpdate);
	return 0;
}

BOOL CIot_TestApp::QueryByDeviceSN(CXDbBaseLib *pXDbLib,const CString &strDeviceSN)
{
	if (strDeviceSN.IsEmpty())
	{
		return FALSE;
	}

	CString strTestAppTable,strSNKey,strSql;
	strTestAppTable = CIot_AtsMngrXmlRWKeys::CIot_TestAppKey();
	strSNKey = CIot_AtsMngrXmlRWKeys::SnKey();

	strSql.Format(_T("select * from %s where %s=\"%s\" limit 1"),strTestAppTable,strSNKey,strDeviceSN);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}