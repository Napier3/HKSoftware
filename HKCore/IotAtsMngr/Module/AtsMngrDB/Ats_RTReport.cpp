//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_RTReport.cpp  CAts_RTReport


#include "stdafx.h"
#include "Ats_RTReport.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_RTReport::CAts_RTReport()
{
	//初始化属性
	m_nIndex_Report = 0;
	m_nIndex_TaskBatch = 0;
	m_nIndex_Task = 0;
	::GetLocalTime(&m_tmUpdateTime);
	m_nDataLen = 0;
	m_nDataPosOfFile = 0;

	//初始化成员变量
}

CAts_RTReport::~CAts_RTReport()
{
}

long CAts_RTReport::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ReportKey, oNode, m_nIndex_Report);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskBatchKey, oNode, m_nIndex_TaskBatch);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TaskKey, oNode, m_nIndex_Task);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceTypeIDKey, oNode, m_strDeviceTypeID);
	xml_GetAttibuteValue(pXmlKeys->m_strItemPathIDKey, oNode, m_strItemPathID);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIDKey, oNode, m_strDeviceID);
	xml_GetAttibuteValue(pXmlKeys->m_strUpdateTimeKey, oNode, m_tmUpdateTime);
	xml_GetAttibuteValue(pXmlKeys->m_strDataLenKey, oNode, m_nDataLen);
	xml_GetAttibuteValue(pXmlKeys->m_strDataPosOfFileKey, oNode, m_nDataPosOfFile);
	return 0;
}

long CAts_RTReport::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_ReportKey, oElement, m_nIndex_Report);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskBatchKey, oElement, m_nIndex_TaskBatch);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TaskKey, oElement, m_nIndex_Task);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceTypeIDKey, oElement, m_strDeviceTypeID);
	xml_SetAttributeValue(pXmlKeys->m_strItemPathIDKey, oElement, m_strItemPathID);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceIDKey, oElement, m_strDeviceID);
	xml_SetAttributeValue(pXmlKeys->m_strUpdateTimeKey, oElement, m_tmUpdateTime);
	xml_SetAttributeValue(pXmlKeys->m_strDataLenKey, oElement, m_nDataLen);
	xml_SetAttributeValue(pXmlKeys->m_strDataPosOfFileKey, oElement, m_nDataPosOfFile);
	return 0;
}

long CAts_RTReport::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Report);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_TaskBatch);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceTypeID);
		BinarySerializeCalLen(oBinaryBuffer, m_strItemPathID);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceID);
		BinarySerializeCalLen(oBinaryBuffer, m_tmUpdateTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nDataLen);
		BinarySerializeCalLen(oBinaryBuffer, m_nDataPosOfFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Report);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_TaskBatch);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceTypeID);
		BinarySerializeRead(oBinaryBuffer, m_strItemPathID);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceID);
		BinarySerializeRead(oBinaryBuffer, m_tmUpdateTime);
		BinarySerializeRead(oBinaryBuffer, m_nDataLen);
		BinarySerializeRead(oBinaryBuffer, m_nDataPosOfFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Report);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_TaskBatch);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Task);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceTypeID);
		BinarySerializeWrite(oBinaryBuffer, m_strItemPathID);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceID);
		BinarySerializeWrite(oBinaryBuffer, m_tmUpdateTime);
		BinarySerializeWrite(oBinaryBuffer, m_nDataLen);
		BinarySerializeWrite(oBinaryBuffer, m_nDataPosOfFile);
	}
	return 0;
}

void CAts_RTReport::InitAfterRead()
{
}

BOOL CAts_RTReport::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_RTReport *p = (CAts_RTReport*)pObj;

	if(m_nIndex_Report != p->m_nIndex_Report)
	{
		return FALSE;
	}

	if(m_nIndex_TaskBatch != p->m_nIndex_TaskBatch)
	{
		return FALSE;
	}

	if(m_nIndex_Task != p->m_nIndex_Task)
	{
		return FALSE;
	}

	if(m_strDeviceTypeID != p->m_strDeviceTypeID)
	{
		return FALSE;
	}

	if(m_strItemPathID != p->m_strItemPathID)
	{
		return FALSE;
	}

	if(m_strDeviceID != p->m_strDeviceID)
	{
		return FALSE;
	}

	if(m_nDataLen != p->m_nDataLen)
	{
		return FALSE;
	}

	if(m_nDataPosOfFile != p->m_nDataPosOfFile)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_RTReport::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_RTReport *p = (CAts_RTReport*)pDest;

	p->m_nIndex_Report = m_nIndex_Report;
	p->m_nIndex_TaskBatch = m_nIndex_TaskBatch;
	p->m_nIndex_Task = m_nIndex_Task;
	p->m_strDeviceTypeID = m_strDeviceTypeID;
	p->m_strItemPathID = m_strItemPathID;
	p->m_strDeviceID = m_strDeviceID;
	p->m_tmUpdateTime = m_tmUpdateTime;
	p->m_nDataLen = m_nDataLen;
	p->m_nDataPosOfFile = m_nDataPosOfFile;
	return TRUE;
}

CBaseObject* CAts_RTReport::Clone()
{
	CAts_RTReport *p = new CAts_RTReport();
	Copy(p);
	return p;
}

CBaseObject* CAts_RTReport::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_RTReport *p = new CAts_RTReport();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CAts_RTReport::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ReportKey, m_nIndex_Report);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskBatchKey, m_nIndex_TaskBatch);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceTypeIDKey, m_strDeviceTypeID);
	pRecordset->GetFieldValue(pXmlKeys->m_strItemPathIDKey, m_strItemPathID);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIDKey, m_strDeviceID);
	pRecordset->GetFieldValue(pXmlKeys->m_strUpdateTimeKey, m_tmUpdateTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataLenKey, m_nDataLen);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataPosOfFileKey, m_nDataPosOfFile);
	return 0;
}

long CAts_RTReport::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ReportKey, m_nIndex_Report);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskBatchKey, m_nIndex_TaskBatch);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TaskKey, m_nIndex_Task);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceTypeIDKey, m_strDeviceTypeID);
	pRecordset->SetFieldValue(pXmlKeys->m_strItemPathIDKey, m_strItemPathID);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIDKey, m_strDeviceID);
	pRecordset->SetFieldValue(pXmlKeys->m_strUpdateTimeKey, m_tmUpdateTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataLenKey, m_nDataLen);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataPosOfFileKey, m_nDataPosOfFile);
	return 0;
}

BOOL CAts_RTReport::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSCLASSID_CATS_RTTASKBATCH)
	{
		m_nIndex_TaskBatch = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSCLASSID_CATS_RTTASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

BOOL CAts_RTReport::GenerateValueBlobFile(const CString &strRootPath,const CString &strID,CString &strFile)
{
	CString strFolder;
	strFolder.AppendFormat(_T("%s%s\\%s\\%s\\"),strRootPath,m_strDeviceTypeID,m_strDeviceID,m_strItemPathID);
	CreateAllDirectories(strFolder);

	strFile.Format(_T("%s_%04d%02d%02d%02d%02d%02d%03d.blob"),strID,m_tmUpdateTime.wYear
		,m_tmUpdateTime.wMonth,m_tmUpdateTime.wDay
		,m_tmUpdateTime.wHour,m_tmUpdateTime.wMinute
		,m_tmUpdateTime.wSecond,m_tmUpdateTime.wMilliseconds);

	return TRUE;
}