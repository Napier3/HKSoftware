//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceOutReport.cpp  CIot_DeviceOutReport


#include "stdafx.h"
#include "Iot_DeviceOutReport.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceOutReport::CIot_DeviceOutReport()
{
	//初始化属性
	m_nIndex_Device = 0;
	m_nIndex_Rpt = 0;

	//初始化成员变量
}

CIot_DeviceOutReport::~CIot_DeviceOutReport()
{
}

long CIot_DeviceOutReport::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndexRptKey, oNode, m_nIndex_Rpt);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_strDoc_File_s);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_FileKey, oNode, m_strPdf_File);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_File_SKey, oNode, m_strPdf_File_s);
	xml_GetAttibuteValue(pXmlKeys->m_strPcap_FileKey, oNode, m_strPcap_File);
	xml_GetAttibuteValue(pXmlKeys->m_strPcap_File_SKey, oNode, m_strPcap_File_s);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_Data_FileKey, oNode, m_strRpt_Data_File);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_Data_File_SKey, oNode, m_strRpt_Data_File_s);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_Data_File_FormatKey, oNode, m_strRpt_Data_File_Format);
	return 0;
}

long CIot_DeviceOutReport::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndexRptKey, oElement, m_nIndex_Rpt);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceKey, oElement, m_nIndex_Device);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_strDoc_File_s);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_FileKey, oElement, m_strPdf_File);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_File_SKey, oElement, m_strPdf_File_s);
	xml_SetAttributeValue(pXmlKeys->m_strPcap_FileKey, oElement, m_strPcap_File);
	xml_SetAttributeValue(pXmlKeys->m_strPcap_File_SKey, oElement, m_strPcap_File_s);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_Data_FileKey, oElement, m_strRpt_Data_File);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_Data_File_SKey, oElement, m_strRpt_Data_File_s);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_Data_File_FormatKey, oElement, m_strRpt_Data_File_Format);
	return 0;
}

long CIot_DeviceOutReport::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Rpt);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File_s);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File_s);
		BinarySerializeCalLen(oBinaryBuffer, m_strPcap_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strPcap_File_s);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Data_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Data_File_s);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Data_File_Format);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Rpt);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File_s);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File_s);
		BinarySerializeRead(oBinaryBuffer, m_strPcap_File);
		BinarySerializeRead(oBinaryBuffer, m_strPcap_File_s);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Data_File);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Data_File_s);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Data_File_Format);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Rpt);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File_s);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File_s);
		BinarySerializeWrite(oBinaryBuffer, m_strPcap_File);
		BinarySerializeWrite(oBinaryBuffer, m_strPcap_File_s);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Data_File);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Data_File_s);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Data_File_Format);
	}
	return 0;
}

void CIot_DeviceOutReport::InitAfterRead()
{
}

BOOL CIot_DeviceOutReport::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceOutReport *p = (CIot_DeviceOutReport*)pObj;

	if(m_nIndex_Rpt != p->m_nIndex_Rpt)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_strDoc_File != p->m_strDoc_File)
	{
		return FALSE;
	}

	if(m_strDoc_File_s != p->m_strDoc_File_s)
	{
		return FALSE;
	}

	if(m_strPdf_File != p->m_strPdf_File)
	{
		return FALSE;
	}

	if(m_strPdf_File_s != p->m_strPdf_File_s)
	{
		return FALSE;
	}

	if(m_strPcap_File != p->m_strPcap_File)
	{
		return FALSE;
	}

	if(m_strPcap_File_s != p->m_strPcap_File_s)
	{
		return FALSE;
	}

	if(m_strRpt_Data_File != p->m_strRpt_Data_File)
	{
		return FALSE;
	}

	if(m_strRpt_Data_File_s != p->m_strRpt_Data_File_s)
	{
		return FALSE;
	}

	if(m_strRpt_Data_File_Format != p->m_strRpt_Data_File_Format)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_DeviceOutReport::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceOutReport *p = (CIot_DeviceOutReport*)pDest;

	p->m_nIndex_Rpt = m_nIndex_Rpt;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strDoc_File_s = m_strDoc_File_s;
	p->m_strPdf_File = m_strPdf_File;
	p->m_strPdf_File_s = m_strPdf_File_s;
	p->m_strPcap_File = m_strPcap_File;
	p->m_strPcap_File_s = m_strPcap_File_s;
	p->m_strRpt_Data_File = m_strRpt_Data_File;
	p->m_strRpt_Data_File_s = m_strRpt_Data_File_s;
	p->m_strRpt_Data_File_Format = m_strRpt_Data_File_Format;

	return TRUE;
}

CBaseObject* CIot_DeviceOutReport::Clone()
{
	CIot_DeviceOutReport *p = new CIot_DeviceOutReport();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceOutReport::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceOutReport *p = new CIot_DeviceOutReport();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceOutReport::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndexRptKey, m_nIndex_Rpt);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_s);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_s);
	pRecordset->GetFieldValue(pXmlKeys->m_strPcap_FileKey, m_strPcap_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strPcap_File_SKey, m_strPcap_File_s);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_Data_FileKey, m_strRpt_Data_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_Data_File_SKey, m_strRpt_Data_File_s);
	pRecordset->GetFieldValue(pXmlKeys->m_strRpt_Data_File_FormatKey, m_strRpt_Data_File_Format);
	return 0;
}

long CIot_DeviceOutReport::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndexRptKey, m_nIndex_Rpt);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_s);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_s);
	pRecordset->SetFieldValue(pXmlKeys->m_strPcap_FileKey, m_strPcap_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strPcap_File_SKey, m_strPcap_File_s);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_Data_FileKey, m_strRpt_Data_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_Data_File_SKey, m_strRpt_Data_File_s);
	pRecordset->SetFieldValue(pXmlKeys->m_strRpt_Data_File_FormatKey, m_strRpt_Data_File_Format);
	return 0;
}

BOOL CIot_DeviceOutReport::UpdateDeviceOutReport(CXDbBaseLib *pXDbLib)
{
	CString strDeviceOutReportTable,strSql;
	CString strIndex_DeviceKey;

	strDeviceOutReportTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceOutReportKey();
	strIndex_DeviceKey = CIot_AtsMngrXmlRWKeys::Index_DeviceKey();

	strSql.Format(_T("select * from %s where %s=%d limit 1")
		,strDeviceOutReportTable,strIndex_DeviceKey,m_nIndex_Device);

	CIot_DeviceOutReport oDeviceOutReport;
	if (oDeviceOutReport.DB_Select_OwnEx(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql))
	{
		m_nIndex_Rpt = oDeviceOutReport.m_nIndex_Rpt;
		return DB_Update(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}

	return DB_Insert(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
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
/*
BOOL CIot_DeviceOutReport::UpdateAttrs(const CString &strTestType,CJSON *pArrData)
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

void CIot_DeviceOutReport::UpdateAttr(const CString &strID,const CString &strValue)
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