//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceReportEx.cpp  CIot_DeviceReportEx


#include "stdafx.h"
#include "Iot_DeviceReportEx.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//扩展报告表
CIot_DeviceReportEx::CIot_DeviceReportEx()
{
	//初始化属性
	m_nIndex_Device_Histest = 0;
	m_nIndex_RptEx = 0;

	//初始化成员变量
}

CIot_DeviceReportEx::~CIot_DeviceReportEx()
{
}

long CIot_DeviceReportEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_HistestKey, oNode, m_nIndex_Device_Histest);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexRptExKey, oNode, m_nIndex_RptEx);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_strDoc_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_FileKey, oNode, m_strPdf_File);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_File_SKey, oNode, m_strPdf_File_S);
	return 0;
}

long CIot_DeviceReportEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_HistestKey, oElement, m_nIndex_Device_Histest);
	xml_SetAttributeValue(pXmlKeys->m_strIndexRptExKey, oElement, m_nIndex_RptEx);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_strDoc_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_FileKey, oElement, m_strPdf_File);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_File_SKey, oElement, m_strPdf_File_S);

	return 0;
}

long CIot_DeviceReportEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Histest);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_RptEx);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File_S);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Histest);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_RptEx);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File_S);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Histest);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_RptEx);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File_S);
	}
	return 0;
}

void CIot_DeviceReportEx::InitAfterRead()
{
}

BOOL CIot_DeviceReportEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceReportEx *p = (CIot_DeviceReportEx*)pObj;

	if(m_nIndex_Device_Histest != p->m_nIndex_Device_Histest)
	{
		return FALSE;
	}

	if(m_nIndex_RptEx != p->m_nIndex_RptEx)
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

	return TRUE;
}

BOOL CIot_DeviceReportEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceReportEx *p = (CIot_DeviceReportEx*)pDest;

	p->m_nIndex_Device_Histest = m_nIndex_Device_Histest;
	p->m_nIndex_RptEx = m_nIndex_RptEx;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strDoc_File_S = m_strDoc_File_S;
	p->m_strPdf_File = m_strPdf_File;
	p->m_strPdf_File_S = m_strPdf_File_S;

	return TRUE;
}

CBaseObject* CIot_DeviceReportEx::Clone()
{
	CIot_DeviceReportEx *p = new CIot_DeviceReportEx();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceReportEx::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceReportEx *p = new CIot_DeviceReportEx();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceReportEx::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_HistestKey, m_nIndex_Device_Histest);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndexRptExKey, m_nIndex_RptEx);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_S);

	return 0;
}

long CIot_DeviceReportEx::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_HistestKey, m_nIndex_Device_Histest);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndexRptExKey, m_nIndex_RptEx);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_S);
	
	return 0;
}

BOOL CIot_DeviceReportEx::UpdateDeviceReportEx(CXDbBaseLib *pXDbLib)
{
	CString strDeviceReportExTable,strSql;
	CString strIndex_DeviceHisTestKey;

	strDeviceReportExTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceHisTestKey();
	strIndex_DeviceHisTestKey = CIot_AtsMngrXmlRWKeys::Index_Device_HistestKey();

	strSql.Format(_T("select * from %s where %s=%d limit 1")
		,strDeviceReportExTable,strIndex_DeviceHisTestKey,m_nIndex_Device_Histest);

	CIot_DeviceReportEx oDeviceReportEx;
	if (oDeviceReportEx.DB_Select_OwnEx(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql))
	{
		m_nIndex_RptEx = oDeviceReportEx.m_nIndex_RptEx;
		return DB_Update(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}

	return DB_Insert(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
}

// void CIot_DeviceReportEx::SetTestType(const CString &strTestType)
// {
// 	m_nTest_Type = DEVICE_TEST_TYPE_SERVICE;
// 
// 	if (strTestType == TEST_TYPE_IOT)
// 	{
// 		m_nTest_Type = DEVICE_TEST_TYPE_PROTOCOL;
// 	}
// 	else if (strTestType == TEST_TYPE_MQTT)
// 	{
// 		m_nTest_Type = DEVICE_TEST_TYPE_MQTTPROTOCOL;
// 	}
// }

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
/*
BOOL CIot_DeviceReportEx::UpdateAttrs(const CString &strTestType,CJSON *pArrData)
{
	if (pArrData->type != CJSON_Array)
	{
		return FALSE;
	}

	//SetTestType(strTestType);

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

void CIot_DeviceReportEx::UpdateAttr(const CString &strID,const CString &strValue)
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
*/