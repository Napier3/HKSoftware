//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceTest.cpp  CIot_DeviceTest


#include "stdafx.h"
#include "Iot_DeviceTest.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceTest::CIot_DeviceTest()
{
	//初始化属性
	m_nIndex_Device_Test = 0;
	m_nIndex_User = 0;
	m_nIndex_Bench = 0;
	m_nIndex_Devicetype = 0;
	m_nIndex_Factory = 0;
	m_nIndex_Dept = 0;
	m_nIndex_Engine = 0;
	m_nIndex_Test = 0;
	::GetLocalTime(&m_tmTm_Begin);
	::GetLocalTime(&m_tmTm_End);
	m_nReport_Result = 0;

	//初始化成员变量
}

CIot_DeviceTest::~CIot_DeviceTest()
{
}

long CIot_DeviceTest::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_TestKey, oNode, m_nIndex_Device_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_UserKey, oNode, m_nIndex_User);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DevicetypeKey, oNode, m_nIndex_Devicetype);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FactoryKey, oNode, m_nIndex_Factory);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeptKey, oNode, m_nIndex_Dept);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_EngineKey, oNode, m_nIndex_Engine);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestKey, oNode, m_nIndex_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_BeginKey, oNode, m_tmTm_Begin);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_EndKey, oNode, m_tmTm_End);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplate_FileKey, oNode, m_strTemplate_File);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_FileKey, oNode, m_strProtocol_File);
	xml_GetAttibuteValue(pXmlKeys->m_strIecfg_FileKey, oNode, m_strIecfg_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvm_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_FileKey, oNode, m_strPdf_File);
	xml_GetAttibuteValue(pXmlKeys->m_strGbrpt_FileKey, oNode, m_strGbrpt_File);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_Data_FileKey, oNode, m_strRpt_Data_File);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_Data_File_FormatKey, oNode, m_strRpt_Data_File_Format);
	xml_GetAttibuteValue(pXmlKeys->m_strTestapp_UsedKey, oNode, m_strTestapp_Used);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceclassifyKey, oNode, m_strDeviceclassify);
	xml_GetAttibuteValue(pXmlKeys->m_strModelKey, oNode, m_strModel);
	xml_GetAttibuteValue(pXmlKeys->m_strPcap_FileKey, oNode, m_strPcap_File);
	xml_GetAttibuteValue(pXmlKeys->m_strReport_ResultKey, oNode, m_nReport_Result);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplate_File_SKey, oNode, m_strTemplate_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_File_SKey, oNode, m_strProtocol_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strIecfg_File_SKey, oNode, m_strIecfg_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_File_SKey, oNode, m_strDvm_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_strDoc_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_File_SKey, oNode, m_strPdf_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strGbrpt_File_SKey, oNode, m_strGbrpt_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_Data_File_SKey, oNode, m_strRpt_Data_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strPcap_File_SKey, oNode, m_strPcap_File_S);
	return 0;
}

long CIot_DeviceTest::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_TestKey, oElement, m_nIndex_Device_Test);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_UserKey, oElement, m_nIndex_User);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DevicetypeKey, oElement, m_nIndex_Devicetype);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FactoryKey, oElement, m_nIndex_Factory);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeptKey, oElement, m_nIndex_Dept);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_EngineKey, oElement, m_nIndex_Engine);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestKey, oElement, m_nIndex_Test);
	xml_SetAttributeValue(pXmlKeys->m_strTm_BeginKey, oElement, m_tmTm_Begin);
	xml_SetAttributeValue(pXmlKeys->m_strTm_EndKey, oElement, m_tmTm_End);
	xml_SetAttributeValue(pXmlKeys->m_strTemplate_FileKey, oElement, m_strTemplate_File);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_FileKey, oElement, m_strProtocol_File);
	xml_SetAttributeValue(pXmlKeys->m_strIecfg_FileKey, oElement, m_strIecfg_File);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvm_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_FileKey, oElement, m_strPdf_File);
	xml_SetAttributeValue(pXmlKeys->m_strGbrpt_FileKey, oElement, m_strGbrpt_File);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_Data_FileKey, oElement, m_strRpt_Data_File);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_Data_File_FormatKey, oElement, m_strRpt_Data_File_Format);
	xml_SetAttributeValue(pXmlKeys->m_strTestapp_UsedKey, oElement, m_strTestapp_Used);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceclassifyKey, oElement, m_strDeviceclassify);
	xml_SetAttributeValue(pXmlKeys->m_strModelKey, oElement, m_strModel);
	xml_SetAttributeValue(pXmlKeys->m_strPcap_FileKey, oElement, m_strPcap_File);
	xml_SetAttributeValue(pXmlKeys->m_strReport_ResultKey, oElement, m_nReport_Result);
	xml_SetAttributeValue(pXmlKeys->m_strTemplate_File_SKey, oElement, m_strTemplate_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_File_SKey, oElement, m_strProtocol_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strIecfg_File_SKey, oElement, m_strIecfg_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_File_SKey, oElement, m_strDvm_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_strDoc_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_File_SKey, oElement, m_strPdf_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strGbrpt_File_SKey, oElement, m_strGbrpt_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_Data_File_SKey, oElement, m_strRpt_Data_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strPcap_File_SKey, oElement, m_strPcap_File_S);
	return 0;
}

long CIot_DeviceTest::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_User);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Devicetype);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_End);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strIecfg_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbrpt_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Data_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Data_File_Format);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestapp_Used);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceclassify);
		BinarySerializeCalLen(oBinaryBuffer, m_strModel);
		BinarySerializeCalLen(oBinaryBuffer, m_strPcap_File);
		BinarySerializeCalLen(oBinaryBuffer, m_nReport_Result);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplate_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strIecfg_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbrpt_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Data_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strPcap_File_S);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Test);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_User);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Devicetype);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_End);
		BinarySerializeRead(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeRead(oBinaryBuffer, m_strIecfg_File);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File);
		BinarySerializeRead(oBinaryBuffer, m_strGbrpt_File);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Data_File);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Data_File_Format);
		BinarySerializeRead(oBinaryBuffer, m_strTestapp_Used);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceclassify);
		BinarySerializeRead(oBinaryBuffer, m_strModel);
		BinarySerializeRead(oBinaryBuffer, m_strPcap_File);
		BinarySerializeRead(oBinaryBuffer, m_nReport_Result);
		BinarySerializeRead(oBinaryBuffer, m_strTemplate_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strIecfg_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strGbrpt_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Data_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strPcap_File_S);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Test);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_User);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Devicetype);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Factory);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Engine);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_End);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeWrite(oBinaryBuffer, m_strIecfg_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File);
		BinarySerializeWrite(oBinaryBuffer, m_strGbrpt_File);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Data_File);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Data_File_Format);
		BinarySerializeWrite(oBinaryBuffer, m_strTestapp_Used);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceclassify);
		BinarySerializeWrite(oBinaryBuffer, m_strModel);
		BinarySerializeWrite(oBinaryBuffer, m_strPcap_File);
		BinarySerializeWrite(oBinaryBuffer, m_nReport_Result);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplate_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strIecfg_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strGbrpt_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Data_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strPcap_File_S);
	}
	return 0;
}

void CIot_DeviceTest::InitAfterRead()
{
}

BOOL CIot_DeviceTest::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_DeviceTest *p = (CIot_DeviceTest*)pObj;

	if(m_nIndex_Device_Test != p->m_nIndex_Device_Test)
	{
		return FALSE;
	}

	if(m_nIndex_User != p->m_nIndex_User)
	{
		return FALSE;
	}

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	if(m_nIndex_Devicetype != p->m_nIndex_Devicetype)
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

	if(m_nIndex_Test != p->m_nIndex_Test)
	{
		return FALSE;
	}

	if(m_strTemplate_File != p->m_strTemplate_File)
	{
		return FALSE;
	}

	if(m_strProtocol_File != p->m_strProtocol_File)
	{
		return FALSE;
	}

	if(m_strIecfg_File != p->m_strIecfg_File)
	{
		return FALSE;
	}

	if(m_strDvm_File != p->m_strDvm_File)
	{
		return FALSE;
	}

	if(m_strDoc_File != p->m_strDoc_File)
	{
		return FALSE;
	}

	if(m_strPdf_File != p->m_strPdf_File)
	{
		return FALSE;
	}

	if(m_strGbrpt_File != p->m_strGbrpt_File)
	{
		return FALSE;
	}

	if(m_strRpt_Data_File != p->m_strRpt_Data_File)
	{
		return FALSE;
	}

	if(m_strRpt_Data_File_Format != p->m_strRpt_Data_File_Format)
	{
		return FALSE;
	}

	if(m_strTestapp_Used != p->m_strTestapp_Used)
	{
		return FALSE;
	}

	if(m_strDeviceclassify != p->m_strDeviceclassify)
	{
		return FALSE;
	}

	if(m_strModel != p->m_strModel)
	{
		return FALSE;
	}

	if(m_strPcap_File != p->m_strPcap_File)
	{
		return FALSE;
	}

	if(m_nReport_Result != p->m_nReport_Result)
	{
		return FALSE;
	}

	if(m_strTemplate_File_S != p->m_strTemplate_File_S)
	{
		return FALSE;
	}

	if(m_strProtocol_File_S != p->m_strProtocol_File_S)
	{
		return FALSE;
	}

	if(m_strIecfg_File_S != p->m_strIecfg_File_S)
	{
		return FALSE;
	}

	if(m_strDvm_File_S != p->m_strDvm_File_S)
	{
		return FALSE;
	}

	if(m_strDoc_File_S != p->m_strDoc_File_S)
	{
		return FALSE;
	}

	if(m_strPdf_File_S != p->m_strPdf_File_S)
	{
		return FALSE;
	}

	if(m_strGbrpt_File_S != p->m_strGbrpt_File_S)
	{
		return FALSE;
	}

	if(m_strRpt_Data_File_S != p->m_strRpt_Data_File_S)
	{
		return FALSE;
	}

	if(m_strPcap_File_S != p->m_strPcap_File_S)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_DeviceTest::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_DeviceTest *p = (CIot_DeviceTest*)pDest;

	p->m_nIndex_Device_Test = m_nIndex_Device_Test;
	p->m_nIndex_User = m_nIndex_User;
	p->m_nIndex_Bench = m_nIndex_Bench;
	p->m_nIndex_Devicetype = m_nIndex_Devicetype;
	p->m_nIndex_Factory = m_nIndex_Factory;
	p->m_nIndex_Dept = m_nIndex_Dept;
	p->m_nIndex_Engine = m_nIndex_Engine;
	p->m_nIndex_Test = m_nIndex_Test;
	p->m_tmTm_Begin = m_tmTm_Begin;
	p->m_tmTm_End = m_tmTm_End;
	p->m_strTemplate_File = m_strTemplate_File;
	p->m_strProtocol_File = m_strProtocol_File;
	p->m_strIecfg_File = m_strIecfg_File;
	p->m_strDvm_File = m_strDvm_File;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strPdf_File = m_strPdf_File;
	p->m_strGbrpt_File = m_strGbrpt_File;
	p->m_strRpt_Data_File = m_strRpt_Data_File;
	p->m_strRpt_Data_File_Format = m_strRpt_Data_File_Format;
	p->m_strTestapp_Used = m_strTestapp_Used;
	p->m_strDeviceclassify = m_strDeviceclassify;
	p->m_strModel = m_strModel;
	p->m_strPcap_File = m_strPcap_File;
	p->m_nReport_Result = m_nReport_Result;
	p->m_strTemplate_File_S = m_strTemplate_File_S;
	p->m_strProtocol_File_S = m_strProtocol_File_S;
	p->m_strIecfg_File_S = m_strIecfg_File_S;
	p->m_strDvm_File_S = m_strDvm_File_S;
	p->m_strDoc_File_S = m_strDoc_File_S;
	p->m_strPdf_File_S = m_strPdf_File_S;
	p->m_strGbrpt_File_S = m_strGbrpt_File_S;
	p->m_strRpt_Data_File_S = m_strRpt_Data_File_S;
	p->m_strPcap_File_S = m_strPcap_File_S;
	return TRUE;
}

CBaseObject* CIot_DeviceTest::Clone()
{
	CIot_DeviceTest *p = new CIot_DeviceTest();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceTest::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceTest *p = new CIot_DeviceTest();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceTest::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TestKey, m_nIndex_Device_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DevicetypeKey, m_nIndex_Devicetype);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_BeginKey, m_tmTm_Begin);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_EndKey, m_tmTm_End);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemplate_FileKey, m_strTemplate_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_strProtocol_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strIecfg_FileKey, m_strIecfg_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strGbrpt_FileKey, m_strGbrpt_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_Data_FileKey, m_strRpt_Data_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_Data_File_FormatKey, m_strRpt_Data_File_Format);
	pRecordset->GetFieldValue(pXmlKeys->m_strTestapp_UsedKey, m_strTestapp_Used);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceclassifyKey, m_strDeviceclassify);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strModelKey, m_strModel);
	pRecordset->GetFieldValue(pXmlKeys->m_strPcap_FileKey, m_strPcap_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strReport_ResultKey, m_nReport_Result);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemplate_File_SKey, m_strTemplate_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strProtocol_File_SKey, m_strProtocol_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strIecfg_File_SKey, m_strIecfg_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strGbrpt_File_SKey, m_strGbrpt_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_Data_File_SKey, m_strRpt_Data_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strPcap_File_SKey, m_strPcap_File_S);
	return 0;
}

long CIot_DeviceTest::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TestKey, m_nIndex_Device_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DevicetypeKey, m_nIndex_Devicetype);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FactoryKey, m_nIndex_Factory);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_EngineKey, m_nIndex_Engine);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_BeginKey, m_tmTm_Begin);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_EndKey, m_tmTm_End);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemplate_FileKey, m_strTemplate_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_strProtocol_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strIecfg_FileKey, m_strIecfg_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strGbrpt_FileKey, m_strGbrpt_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_Data_FileKey, m_strRpt_Data_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_Data_File_FormatKey, m_strRpt_Data_File_Format);
	pRecordset->SetFieldValue(pXmlKeys->m_strTestapp_UsedKey, m_strTestapp_Used);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceclassifyKey, m_strDeviceclassify);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strModelKey, m_strModel);
	pRecordset->SetFieldValue(pXmlKeys->m_strPcap_FileKey, m_strPcap_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strReport_ResultKey, m_nReport_Result);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemplate_File_SKey, m_strTemplate_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strProtocol_File_SKey, m_strProtocol_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strIecfg_File_SKey, m_strIecfg_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strGbrpt_File_SKey, m_strGbrpt_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_Data_File_SKey, m_strRpt_Data_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strPcap_File_SKey, m_strPcap_File_S);
	return 0;
}

BOOL CIot_DeviceTest::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_USER)
	{
		m_nIndex_User = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_BENCH)
	{
		m_nIndex_Bench = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_FACTORY)
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

	return TRUE;
}

