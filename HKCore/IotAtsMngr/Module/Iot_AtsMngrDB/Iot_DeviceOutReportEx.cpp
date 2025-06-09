//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceHisTest.cpp  CIot_DeviceOutReportEx


#include "stdafx.h"
#include "Iot_DeviceOutReportEx.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceOutReportEx::CIot_DeviceOutReportEx()
{
	//初始化属性
	m_nIndexRptEx = 0;
	m_nIndexRpt = 0;

	//初始化成员变量
}

CIot_DeviceOutReportEx::~CIot_DeviceOutReportEx()
{
}

long CIot_DeviceOutReportEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndexRptExKey, oNode, m_nIndexRptEx);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexRptKey, oNode, m_nIndexRpt);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_strDoc_File_s);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_FileKey, oNode, m_strPdf_File);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_File_SKey, oNode, m_strPdf_File_s);
	return 0;
}

long CIot_DeviceOutReportEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndexRptExKey, oElement, m_nIndexRptEx);
	xml_SetAttributeValue(pXmlKeys->m_strIndexRptKey, oElement, m_nIndexRpt);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_strDoc_File_s);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_FileKey, oElement, m_strPdf_File);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_File_SKey, oElement, m_strPdf_File_s);
	return 0;
}

long CIot_DeviceOutReportEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndexRptEx);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndexRpt);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File_s);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strPdf_File_s);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndexRptEx);
		BinarySerializeRead(oBinaryBuffer, m_nIndexRpt);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File_s);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File);
		BinarySerializeRead(oBinaryBuffer, m_strPdf_File_s);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndexRptEx);
		BinarySerializeWrite(oBinaryBuffer, m_nIndexRpt);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File_s);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File);
		BinarySerializeWrite(oBinaryBuffer, m_strPdf_File_s);
	}
	return 0;
}

void CIot_DeviceOutReportEx::InitAfterRead()
{
}

BOOL CIot_DeviceOutReportEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceOutReportEx *p = (CIot_DeviceOutReportEx*)pObj;

	if(m_nIndexRptEx != p->m_nIndexRptEx)
	{
		return FALSE;
	}

	if(m_nIndexRpt != p->m_nIndexRpt)
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

	return TRUE;
}

BOOL CIot_DeviceOutReportEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceOutReportEx *p = (CIot_DeviceOutReportEx*)pDest;

	p->m_nIndexRptEx = m_nIndexRptEx;
	p->m_nIndexRpt = m_nIndexRptEx;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strDoc_File_s = m_strDoc_File_s;
	p->m_strPdf_File = m_strPdf_File;
	p->m_strPdf_File_s = m_strPdf_File_s;

	return TRUE;
}

CBaseObject* CIot_DeviceOutReportEx::Clone()
{
	CIot_DeviceOutReportEx *p = new CIot_DeviceOutReportEx();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceOutReportEx::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceOutReportEx *p = new CIot_DeviceOutReportEx();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceOutReportEx::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndexRptExKey, m_nIndexRptEx);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndexRptKey, m_nIndexRpt);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_s);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_s);
	return 0;
}

long CIot_DeviceOutReportEx::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndexRptExKey, m_nIndexRptEx);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndexRptKey, m_nIndexRpt);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_s);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_FileKey, m_strPdf_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_strPdf_File_s);
	return 0;
}

BOOL CIot_DeviceOutReportEx::UpdateDeviceOutReportEx(CXDbBaseLib *pXDbLib)
{
	CString strDeviceOutReportExTable,strSql;
	CString strIndexRptKey;

	strDeviceOutReportExTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceOutReportExKey();
	strIndexRptKey = CIot_AtsMngrXmlRWKeys::IndexRptKey();

	strSql.Format(_T("select * from %s where %s=%d limit 1")
		,strDeviceOutReportExTable,strIndexRptKey,m_nIndexRpt);

	CIot_DeviceOutReportEx oDeviceOutReportEx;
	if (oDeviceOutReportEx.DB_Select_OwnEx(pXDbLib,CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql))
	{
		m_nIndexRptEx = oDeviceOutReportEx.m_nIndexRptEx;
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
BOOL CIot_DeviceOutReportEx::UpdateAttrs(const CString &strTestType,CJSON *pArrData)
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

void CIot_DeviceOutReportEx::UpdateAttr(const CString &strID,const CString &strValue)
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