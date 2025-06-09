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

CIot_DeviceReportEx::CIot_DeviceReportEx()
{
	//初始化属性
	m_nIndex_Rptex = 0;
	m_nIndex_Device_Test = 0;
	m_nDoc_File = 0;
	m_nPdf_File = 0;
	m_nDoc_File_S = 0;
	m_nPdf_File_S = 0;

	//初始化成员变量
}

CIot_DeviceReportEx::~CIot_DeviceReportEx()
{
}

long CIot_DeviceReportEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_RptexKey, oNode, m_nIndex_Rptex);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_TestKey, oNode, m_nIndex_Device_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_nDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_FileKey, oNode, m_nPdf_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_nDoc_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strPdf_File_SKey, oNode, m_nPdf_File_S);
	return 0;
}

long CIot_DeviceReportEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_RptexKey, oElement, m_nIndex_Rptex);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_TestKey, oElement, m_nIndex_Device_Test);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_nDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_FileKey, oElement, m_nPdf_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_nDoc_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strPdf_File_SKey, oElement, m_nPdf_File_S);
	return 0;
}

long CIot_DeviceReportEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Rptex);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_nDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_nPdf_File);
		BinarySerializeCalLen(oBinaryBuffer, m_nDoc_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_nPdf_File_S);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Rptex);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Test);
		BinarySerializeRead(oBinaryBuffer, m_nDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_nPdf_File);
		BinarySerializeRead(oBinaryBuffer, m_nDoc_File_S);
		BinarySerializeRead(oBinaryBuffer, m_nPdf_File_S);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Rptex);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Test);
		BinarySerializeWrite(oBinaryBuffer, m_nDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_nPdf_File);
		BinarySerializeWrite(oBinaryBuffer, m_nDoc_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_nPdf_File_S);
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

	if(m_nIndex_Rptex != p->m_nIndex_Rptex)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Test != p->m_nIndex_Device_Test)
	{
		return FALSE;
	}

	if(m_nDoc_File != p->m_nDoc_File)
	{
		return FALSE;
	}

	if(m_nPdf_File != p->m_nPdf_File)
	{
		return FALSE;
	}

	if(m_nDoc_File_S != p->m_nDoc_File_S)
	{
		return FALSE;
	}

	if(m_nPdf_File_S != p->m_nPdf_File_S)
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

	p->m_nIndex_Rptex = m_nIndex_Rptex;
	p->m_nIndex_Device_Test = m_nIndex_Device_Test;
	p->m_nDoc_File = m_nDoc_File;
	p->m_nPdf_File = m_nPdf_File;
	p->m_nDoc_File_S = m_nDoc_File_S;
	p->m_nPdf_File_S = m_nPdf_File_S;
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
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_RptexKey, m_nIndex_Rptex);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TestKey, m_nIndex_Device_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_nDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_FileKey, m_nPdf_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_nDoc_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_nPdf_File_S);
	return 0;
}

long CIot_DeviceReportEx::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_RptexKey, m_nIndex_Rptex);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TestKey, m_nIndex_Device_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_nDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_FileKey, m_nPdf_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_nDoc_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strPdf_File_SKey, m_nPdf_File_S);
	return 0;
}

BOOL CIot_DeviceReportEx::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEVICETEST)
	{
		m_nIndex_Device_Test = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

