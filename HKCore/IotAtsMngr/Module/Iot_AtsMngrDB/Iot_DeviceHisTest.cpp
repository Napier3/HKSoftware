//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceHisTest.cpp  CIot_DeviceHisTest


#include "stdafx.h"
#include "Iot_DeviceHisTest.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceHisTest::CIot_DeviceHisTest()
{
	//初始化属性
	m_nIndex_Device_Histest = 0;
	m_nIndex_Device = 0;
	m_nIndex_User = 0;
	m_nIndex_Test_Task = 0;
	::GetLocalTime(&m_tmTm_Begin);
	::GetLocalTime(&m_tmTm_End);
	m_nReport_Result = 0;
	m_nTest_Type = 0;

	//初始化成员变量
}

CIot_DeviceHisTest::~CIot_DeviceHisTest()
{
}

long CIot_DeviceHisTest::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_HistestKey, oNode, m_nIndex_Device_Histest);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_UserKey, oNode, m_nIndex_User);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Test_TaskKey, oNode, m_nIndex_Test_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_BeginKey, oNode, m_tmTm_Begin);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_EndKey, oNode, m_tmTm_End);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_strDoc_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_FileKey, oNode, m_strPdf_File);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_File_SKey, oNode, m_strPdf_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strGbrpt_FileKey, oNode, m_strGbrpt_File);
	xml_GetAttibuteValue(pXmlKeys->m_strGbrpt_File_SKey, oNode, m_strGbrpt_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strPcap_FileKey, oNode, m_strPcap_File);
	xml_GetAttibuteValue(pXmlKeys->m_strPcap_File_SKey, oNode, m_strPcap_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_Data_FileKey, oNode, m_strRpt_Data_File);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_Data_File_SKey, oNode, m_strRpt_Data_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_Data_File_FormatKey, oNode, m_strRpt_Data_File_Format);
	xml_GetAttibuteValue(pXmlKeys->m_strReport_ResultKey, oNode, m_nReport_Result);
	xml_GetAttibuteValue(pXmlKeys->m_strTest_TypeKey, oNode, m_nTest_Type);
	return 0;
}

long CIot_DeviceHisTest::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_HistestKey, oElement, m_nIndex_Device_Histest);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceKey, oElement, m_nIndex_Device);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_UserKey, oElement, m_nIndex_User);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Test_TaskKey, oElement, m_nIndex_Test_Task);
	xml_SetAttributeValue(pXmlKeys->m_strTm_BeginKey, oElement, m_tmTm_Begin);
	xml_SetAttributeValue(pXmlKeys->m_strTm_EndKey, oElement, m_tmTm_End);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_strDoc_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_FileKey, oElement, m_strPdf_File);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_File_SKey, oElement, m_strPdf_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strGbrpt_FileKey, oElement, m_strGbrpt_File);
	xml_SetAttributeValue(pXmlKeys->m_strGbrpt_File_SKey, oElement, m_strGbrpt_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strPcap_FileKey, oElement, m_strPcap_File);
	xml_SetAttributeValue(pXmlKeys->m_strPcap_File_SKey, oElement, m_strPcap_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_Data_FileKey, oElement, m_strRpt_Data_File);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_Data_File_SKey, oElement, m_strRpt_Data_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_Data_File_FormatKey, oElement, m_strRpt_Data_File_Format);
	xml_SetAttributeValue(pXmlKeys->m_strReport_ResultKey, oElement, m_nReport_Result);
	xml_SetAttributeValue(pXmlKeys->m_strTest_TypeKey, oElement, m_nTest_Type);
	return 0;
}

long CIot_DeviceHisTest::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Histest);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_User);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_End);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbrpt_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbrpt_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strPcap_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strPcap_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Data_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Data_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Data_File_Format);
		BinarySerializeCalLen(oBinaryBuffer, m_nReport_Result);
		BinarySerializeCalLen(oBinaryBuffer, m_nTest_Type);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Histest);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_User);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_End);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strGbrpt_File);
		BinarySerializeRead(oBinaryBuffer, m_strGbrpt_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strPcap_File);
		BinarySerializeRead(oBinaryBuffer, m_strPcap_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Data_File);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Data_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Data_File_Format);
		BinarySerializeRead(oBinaryBuffer, m_nReport_Result);
		BinarySerializeRead(oBinaryBuffer, m_nTest_Type);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Histest);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_User);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test_Task);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Begin);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_End);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strGbrpt_File);
		BinarySerializeWrite(oBinaryBuffer, m_strGbrpt_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strPcap_File);
		BinarySerializeWrite(oBinaryBuffer, m_strPcap_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Data_File);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Data_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Data_File_Format);
		BinarySerializeWrite(oBinaryBuffer, m_nReport_Result);
		BinarySerializeWrite(oBinaryBuffer, m_nTest_Type);
	}
	return 0;
}

void CIot_DeviceHisTest::InitAfterRead()
{
}

BOOL CIot_DeviceHisTest::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceHisTest *p = (CIot_DeviceHisTest*)pObj;

	if(m_nIndex_Device_Histest != p->m_nIndex_Device_Histest)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_nIndex_User != p->m_nIndex_User)
	{
		return FALSE;
	}

	if(m_nIndex_Test_Task != p->m_nIndex_Test_Task)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strDoc_File != p->m_strDoc_File)
	{
		return FALSE;
	}

	if(m_strDoc_File_S != p->m_strDoc_File_S)
	{
		return FALSE;
	}

	if(m_strPdf_File != p->m_strPdf_File)
	{
		return FALSE;
	}

	if(m_strPdf_File_S != p->m_strPdf_File_S)
	{
		return FALSE;
	}

	if(m_strGbrpt_File != p->m_strGbrpt_File)
	{
		return FALSE;
	}

	if(m_strGbrpt_File_S != p->m_strGbrpt_File_S)
	{
		return FALSE;
	}

	if(m_strPcap_File != p->m_strPcap_File)
	{
		return FALSE;
	}

	if(m_strPcap_File_S != p->m_strPcap_File_S)
	{
		return FALSE;
	}

	if(m_strRpt_Data_File != p->m_strRpt_Data_File)
	{
		return FALSE;
	}

	if(m_strRpt_Data_File_S != p->m_strRpt_Data_File_S)
	{
		return FALSE;
	}

	if(m_strRpt_Data_File_Format != p->m_strRpt_Data_File_Format)
	{
		return FALSE;
	}

	if(m_nReport_Result != p->m_nReport_Result)
	{
		return FALSE;
	}

	if(m_nTest_Type != p->m_nTest_Type)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_DeviceHisTest::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceHisTest *p = (CIot_DeviceHisTest*)pDest;

	p->m_nIndex_Device_Histest = m_nIndex_Device_Histest;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_nIndex_User = m_nIndex_User;
	p->m_nIndex_Test_Task = m_nIndex_Test_Task;
	p->m_tmTm_Begin = m_tmTm_Begin;
	p->m_tmTm_End = m_tmTm_End;
	p->m_strName = m_strName;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strDoc_File_S = m_strDoc_File_S;
	p->m_strPdf_File = m_strPdf_File;
	p->m_strPdf_File_S = m_strPdf_File_S;
	p->m_strGbrpt_File = m_strGbrpt_File;
	p->m_strGbrpt_File_S = m_strGbrpt_File_S;
	p->m_strPcap_File = m_strPcap_File;
	p->m_strPcap_File_S = m_strPcap_File_S;
	p->m_strRpt_Data_File = m_strRpt_Data_File;
	p->m_strRpt_Data_File_S = m_strRpt_Data_File_S;
	p->m_strRpt_Data_File_Format = m_strRpt_Data_File_Format;
	p->m_nReport_Result = m_nReport_Result;
	p->m_nTest_Type = m_nTest_Type;
	return TRUE;
}

CBaseObject* CIot_DeviceHisTest::Clone()
{
	CIot_DeviceHisTest *p = new CIot_DeviceHisTest();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceHisTest::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceHisTest *p = new CIot_DeviceHisTest();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceHisTest::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_HistestKey, m_nIndex_Device_Histest);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_BeginKey, m_tmTm_Begin);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_EndKey, m_tmTm_End);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strGbrpt_FileKey, m_strGbrpt_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strGbrpt_File_SKey, m_strGbrpt_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strPcap_FileKey, m_strPcap_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strPcap_File_SKey, m_strPcap_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_Data_FileKey, m_strRpt_Data_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_Data_File_SKey, m_strRpt_Data_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_Data_File_FormatKey, m_strRpt_Data_File_Format);
	pRecordset->GetFieldValue(pXmlKeys->m_strReport_ResultKey, m_nReport_Result);
	pRecordset->GetFieldValue(pXmlKeys->m_strTest_TypeKey, m_nTest_Type);
	return 0;
}

long CIot_DeviceHisTest::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_HistestKey, m_nIndex_Device_Histest);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Test_TaskKey, m_nIndex_Test_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_BeginKey, m_tmTm_Begin);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_EndKey, m_tmTm_End);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strGbrpt_FileKey, m_strGbrpt_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strGbrpt_File_SKey, m_strGbrpt_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strPcap_FileKey, m_strPcap_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strPcap_File_SKey, m_strPcap_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_Data_FileKey, m_strRpt_Data_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_Data_File_SKey, m_strRpt_Data_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_Data_File_FormatKey, m_strRpt_Data_File_Format);
	pRecordset->SetFieldValue(pXmlKeys->m_strReport_ResultKey, m_nReport_Result);
	pRecordset->SetFieldValue(pXmlKeys->m_strTest_TypeKey, m_nTest_Type);
	return 0;
}

BOOL CIot_DeviceHisTest::UpdateDeviceHisTest(CXDbBaseLib *pXDbLib)
{
	CString strDeviceHisTestTable,strSql,strTmBegin;
	CString strIndex_DeviceKey,strTm_BeginKey;

	SystemTime_To_String(m_tmTm_Begin,strTmBegin);
	strDeviceHisTestTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceHisTestKey();
	strIndex_DeviceKey = CIot_AtsMngrXmlRWKeys::Index_DeviceKey();
	strTm_BeginKey = CIot_AtsMngrXmlRWKeys::Tm_BeginKey();

	strSql.Format(_T("select * from %s where %s=%d and %s=\"%s\" limit 1")
		,strDeviceHisTestTable,strIndex_DeviceKey,m_nIndex_Device,strTm_BeginKey,strTmBegin);

	CIot_DeviceHisTest oDeviceHisTest;
	if (oDeviceHisTest.DB_Select_OwnEx(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql))
	{
		m_nIndex_Device_Histest = oDeviceHisTest.m_nIndex_Device_Histest;
		return DB_Update(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}

	return DB_Insert(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
}

void CIot_DeviceHisTest::SetTestType(const CString &strTestType)
{
	m_nTest_Type = DEVICE_TEST_TYPE_SERVICE;

	if (strTestType == TEST_TYPE_IOT)
	{
		m_nTest_Type = DEVICE_TEST_TYPE_PROTOCOL;
	}
	else if (strTestType == TEST_TYPE_MQTT)
	{
		m_nTest_Type = DEVICE_TEST_TYPE_MQTTPROTOCOL;
	}
}

/*******************************
"data":[
{
"id":"test_name",
"value":"测试名称"
},
{
"id":"testuser",
"value":"用户登录名"
},
{
"id":"DeviceSN",
"value":"123456123456"
},
{
"id":"tm_begin",
"value":"2021-3-24 10:10:10"
},
{
"id":"tm_end",
"value":"2021-3-24 10:10:10"
},
{
"id":"doc_file",
"value":"报告文件名.doc"
},
{
"id":"doc_file_s",
"value":" doc_file  http文件传输返回的服务器路径fileName"
},
{
"id":"pcap_file",
"value":"报告文件名_pcap.rar"
},
{
"id":"pcap_file_s",
"value":" pcap_file  http文件传输返回的服务器路径fileName"
},
{
"id":"report_result",
"value":"0/1"
}
]
*******************************/
BOOL CIot_DeviceHisTest::UpdateAttrs(const CString &strTestType,CJSON *pArrData)
{
	if (pArrData->type != CJSON_Array)
	{
		return FALSE;
	}

	SetTestType(strTestType);

	int nArrSize = CJSON_GetArraySize(pArrData);
	CJSON *pData = NULL;
	CJSON *pAttr = NULL;
	CJSON *pAttrVal = NULL;
	CString strID,strValue;

	for (int i=0; i<nArrSize; i++)
	{
		pData = CJSON_GetArrayItem(pArrData,i);

		pAttr = CJSON_GetObjectItem(pData, "id");
		if (pAttr != NULL)
		{
			strID = pAttr->valuestring;

			pAttrVal = CJSON_GetObjectItem(pData, "value");
			if (pAttrVal != NULL)
			{
				strValue = pAttrVal->valuestring;

				//更新属性
				UpdateAttr(strID,strValue);
			}
		}	
	}

	return TRUE;
}

void CIot_DeviceHisTest::UpdateAttr(const CString &strID,const CString &strValue)
{
	CString strGbkValue;
	char *pBuffer = NULL;
	long nLen = strValue.GetLength();
	charUtf8_to_charGBK(const_cast<char*>(strValue.GetString()), nLen, &pBuffer, nLen);
	strGbkValue = pBuffer;
	delete pBuffer;

	if (strID == _T("test_name"))
	{
		m_strName = strGbkValue;
	}
	else if (strID == _T("testuser"))
	{
		m_strLoginName = strGbkValue;
	}
	else if (strID == _T("DeviceSN"))
	{
		m_strDeviceSN = strGbkValue;
	}
	else if (strID == _T("tm_begin"))
	{
		CString_To_SystemTime(strValue,m_tmTm_Begin);
	}
	else if (strID == _T("tm_end"))
	{
		CString_To_SystemTime(strValue,m_tmTm_End);
	}
	else if (strID == _T("doc_file"))
	{
		m_strDoc_File = strGbkValue;
	}
	else if (strID == _T("doc_file_s"))
	{
		m_strDoc_File_S = strGbkValue;
	}
	else if (strID == _T("pcap_file"))
	{
		m_strPcap_File = strGbkValue;
	}
	else if (strID == _T("pcap_file_s"))
	{
		m_strPcap_File_S = strGbkValue;
	}
	else if (strID == _T("report_result"))
	{
		m_nReport_Result = CString_To_long(strValue);
	}
}