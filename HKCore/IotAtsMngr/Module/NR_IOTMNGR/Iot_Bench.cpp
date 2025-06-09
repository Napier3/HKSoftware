//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Bench.cpp  CIot_Bench


#include "stdafx.h"
#include "Iot_Bench.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Bench::CIot_Bench()
{
	//初始化属性
	m_nIndex_Bench = 0;
	m_nIndex_Dept = 0;
	m_nIndex_Tester = 0;
	m_nTime_Long_Total_Test = 0;
	m_nTime_Long_Used = 0;
	m_nIndex_Test = 0;
	::GetLocalTime(&m_tmTm_Begin);
	::GetLocalTime(&m_tmTm_End);
	m_nState = 0;
	m_nIndex_Template = 0;
	m_nIndex_Device_Classify = 0;

	//初始化成员变量
	m_pIot_TestTaskDevices = NULL;
	m_pIot_BenchTestApps = NULL;
}

CIot_Bench::~CIot_Bench()
{
}

long CIot_Bench::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeptKey, oNode, m_nIndex_Dept);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_BenchKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strTest_TypeKey, oNode, m_strTest_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TesterKey, oNode, m_nIndex_Tester);
	xml_GetAttibuteValue(pXmlKeys->m_strTime_Long_Total_TestKey, oNode, m_nTime_Long_Total_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strTime_Long_UsedKey, oNode, m_nTime_Long_Used);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestKey, oNode, m_nIndex_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_BeginKey, oNode, m_tmTm_Begin);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_EndKey, oNode, m_tmTm_End);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplate_FileKey, oNode, m_strTemplate_File);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_FileKey, oNode, m_strProtocol_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvm_File);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_nState);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TemplateKey, oNode, m_nIndex_Template);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplate_File_SKey, oNode, m_strTemplate_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_File_SKey, oNode, m_strProtocol_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_File_SKey, oNode, m_strDvm_File_S);
	return 0;
}

long CIot_Bench::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeptKey, oElement, m_nIndex_Dept);
	xml_SetAttributeValue(pXmlKeys->m_strSn_BenchKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strTest_TypeKey, oElement, m_strTest_Type);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TesterKey, oElement, m_nIndex_Tester);
	xml_SetAttributeValue(pXmlKeys->m_strTime_Long_Total_TestKey, oElement, m_nTime_Long_Total_Test);
	xml_SetAttributeValue(pXmlKeys->m_strTime_Long_UsedKey, oElement, m_nTime_Long_Used);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestKey, oElement, m_nIndex_Test);
	xml_SetAttributeValue(pXmlKeys->m_strTm_BeginKey, oElement, m_tmTm_Begin);
	xml_SetAttributeValue(pXmlKeys->m_strTm_EndKey, oElement, m_tmTm_End);
	xml_SetAttributeValue(pXmlKeys->m_strTemplate_FileKey, oElement, m_strTemplate_File);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_FileKey, oElement, m_strProtocol_File);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvm_File);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_nState);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TemplateKey, oElement, m_nIndex_Template);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strTemplate_File_SKey, oElement, m_strTemplate_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_File_SKey, oElement, m_strProtocol_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_File_SKey, oElement, m_strDvm_File_S);
	return 0;
}

long CIot_Bench::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_strTest_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Tester);
		BinarySerializeCalLen(oBinaryBuffer, m_nTime_Long_Total_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_nTime_Long_Used);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_End);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File);
		BinarySerializeCalLen(oBinaryBuffer, m_nState);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplate_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File_S);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_strTest_Type);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Tester);
		BinarySerializeRead(oBinaryBuffer, m_nTime_Long_Total_Test);
		BinarySerializeRead(oBinaryBuffer, m_nTime_Long_Used);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_End);
		BinarySerializeRead(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File);
		BinarySerializeRead(oBinaryBuffer, m_nState);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeRead(oBinaryBuffer, m_strTemplate_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File_S);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Dept);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_strTest_Type);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Tester);
		BinarySerializeWrite(oBinaryBuffer, m_nTime_Long_Total_Test);
		BinarySerializeWrite(oBinaryBuffer, m_nTime_Long_Used);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_End);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File);
		BinarySerializeWrite(oBinaryBuffer, m_nState);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplate_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File_S);
	}
	return 0;
}

void CIot_Bench::InitAfterRead()
{
// 	POS pos = GetHeadPosition();
// 	CBaseObject *p = NULL;
// 	UINT nClassID = 0;
// 
// 	while (pos != NULL)
// 	{
// 		p = GetNext(pos);
// 		nClassID = p->GetClassID();
// 
// 		if (nClassID == IOTCLASSID_CIOT_TESTTASKDEVICES)
// 		{
// 			m_pIot_TestTaskDevices = (CIot_TestTaskDevices*)p;
// 		}
// 		else if (nClassID == IOTCLASSID_CIOT_BENCHTESTAPPS)
// 		{
// 			m_pIot_BenchTestApps = (CIot_BenchTestApps*)p;
// 		}
// 	}
// 
// 	if (m_pIot_TestTaskDevices == NULL)
// 	{
// 		m_pIot_TestTaskDevices = (CIot_TestTaskDevices*)AddNewChild(new CIot_TestTaskDevices());
// 	}
// 
// 	if (m_pIot_BenchTestApps == NULL)
// 	{
// 		m_pIot_BenchTestApps = (CIot_BenchTestApps*)AddNewChild(new CIot_BenchTestApps());
// 	}

}

BOOL CIot_Bench::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Bench *p = (CIot_Bench*)pObj;

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	if(m_nIndex_Dept != p->m_nIndex_Dept)
	{
		return FALSE;
	}

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_strTest_Type != p->m_strTest_Type)
	{
		return FALSE;
	}

	if(m_nIndex_Tester != p->m_nIndex_Tester)
	{
		return FALSE;
	}

	if(m_nTime_Long_Total_Test != p->m_nTime_Long_Total_Test)
	{
		return FALSE;
	}

	if(m_nTime_Long_Used != p->m_nTime_Long_Used)
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

	if(m_strDvm_File != p->m_strDvm_File)
	{
		return FALSE;
	}

	if(m_nState != p->m_nState)
	{
		return FALSE;
	}

	if(m_nIndex_Template != p->m_nIndex_Template)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Classify != p->m_nIndex_Device_Classify)
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

	if(m_strDvm_File_S != p->m_strDvm_File_S)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Bench::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Bench *p = (CIot_Bench*)pDest;

	p->m_nIndex_Bench = m_nIndex_Bench;
	p->m_nIndex_Dept = m_nIndex_Dept;
	p->m_strID = m_strID;
	p->m_strTest_Type = m_strTest_Type;
	p->m_nIndex_Tester = m_nIndex_Tester;
	p->m_nTime_Long_Total_Test = m_nTime_Long_Total_Test;
	p->m_nTime_Long_Used = m_nTime_Long_Used;
	p->m_nIndex_Test = m_nIndex_Test;
	p->m_tmTm_Begin = m_tmTm_Begin;
	p->m_tmTm_End = m_tmTm_End;
	p->m_strTemplate_File = m_strTemplate_File;
	p->m_strProtocol_File = m_strProtocol_File;
	p->m_strDvm_File = m_strDvm_File;
	p->m_nState = m_nState;
	p->m_nIndex_Template = m_nIndex_Template;
	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	p->m_strTemplate_File_S = m_strTemplate_File_S;
	p->m_strProtocol_File_S = m_strProtocol_File_S;
	p->m_strDvm_File_S = m_strDvm_File_S;
	return TRUE;
}

CBaseObject* CIot_Bench::Clone()
{
	CIot_Bench *p = new CIot_Bench();
	Copy(p);
	return p;
}

CBaseObject* CIot_Bench::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Bench *p = new CIot_Bench();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Bench::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_BENCHTESTAPPS)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOT_TESTTASKDEVICES)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Bench::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_BenchTestAppsKey)
	{
		pNew = new CIot_BenchTestApps();
	}
	else if (strClassID == pXmlKeys->m_strCIot_TestTaskDevicesKey)
	{
		pNew = new CIot_TestTaskDevices();
	}

	return pNew;
}

CExBaseObject* CIot_Bench::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_BENCHTESTAPPS)
	{
		pNew = new CIot_BenchTestApps();
	}
	else if (nClassID == IOTCLASSID_CIOT_TESTTASKDEVICES)
	{
		pNew = new CIot_TestTaskDevices();
	}

	return pNew;
}
long CIot_Bench::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_BenchKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strTest_TypeKey, m_strTest_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TesterKey, m_nIndex_Tester);
	pRecordset->GetFieldValue(pXmlKeys->m_strTime_Long_Total_TestKey, m_nTime_Long_Total_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strTime_Long_UsedKey, m_nTime_Long_Used);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_BeginKey, m_tmTm_Begin);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_EndKey, m_tmTm_End);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemplate_FileKey, m_strTemplate_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_strProtocol_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemplate_File_SKey, m_strTemplate_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strProtocol_File_SKey, m_strProtocol_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	return 0;
}

long CIot_Bench::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeptKey, m_nIndex_Dept);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_BenchKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strTest_TypeKey, m_strTest_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TesterKey, m_nIndex_Tester);
	pRecordset->SetFieldValue(pXmlKeys->m_strTime_Long_Total_TestKey, m_nTime_Long_Total_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strTime_Long_UsedKey, m_nTime_Long_Used);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_BeginKey, m_tmTm_Begin);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_EndKey, m_tmTm_End);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemplate_FileKey, m_strTemplate_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_strProtocol_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemplate_File_SKey, m_strTemplate_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strProtocol_File_SKey, m_strProtocol_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	return 0;
}

BOOL CIot_Bench::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEPT)
	{
		m_nIndex_Dept = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TEMPLATE)
	{
		m_nIndex_Template = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEVICE_CLASSIFY)
	{
		m_nIndex_Device_Classify = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

