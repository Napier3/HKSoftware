//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceMergeReport.cpp  CIot_DeviceMergeReport


#include "stdafx.h"
#include "Iot_DeviceMergeReport.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceMergeReport::CIot_DeviceMergeReport()
{
	//初始化属性
	m_nIndex_Merge_Report = 0;
	m_nIndex_User = 0;
	m_nSn = 0;

	//初始化成员变量
}

CIot_DeviceMergeReport::~CIot_DeviceMergeReport()
{
}

long CIot_DeviceMergeReport::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Merge_ReportKey, oNode, m_nIndex_Merge_Report);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_UserKey, oNode, m_nIndex_User);
	xml_GetAttibuteValue(pXmlKeys->m_strSnKey, oNode, m_nSn);
	xml_GetAttibuteValue(pXmlKeys->m_strMerge_FileKey, oNode, m_strMerge_File);
	xml_GetAttibuteValue(pXmlKeys->m_strMerge_File_SKey, oNode, m_strMerge_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);
	xml_GetAttibuteValue(pXmlKeys->m_strMerge_IdsKey, oNode, m_strMerge_Ids);
	return 0;
}

long CIot_DeviceMergeReport::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Merge_ReportKey, oElement, m_nIndex_Merge_Report);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_UserKey, oElement, m_nIndex_User);
	xml_SetAttributeValue(pXmlKeys->m_strSnKey, oElement, m_nSn);
	xml_SetAttributeValue(pXmlKeys->m_strMerge_FileKey, oElement, m_strMerge_File);
	xml_SetAttributeValue(pXmlKeys->m_strMerge_File_SKey, oElement, m_strMerge_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDescriptionKey, oElement, m_strDescription);
	xml_SetAttributeValue(pXmlKeys->m_strMerge_IdsKey, oElement, m_strMerge_Ids);
	return 0;
}

long CIot_DeviceMergeReport::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Merge_Report);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_User);
		BinarySerializeCalLen(oBinaryBuffer, m_nSn);
		BinarySerializeCalLen(oBinaryBuffer, m_strMerge_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strMerge_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
		BinarySerializeCalLen(oBinaryBuffer, m_strMerge_Ids);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Merge_Report);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_User);
		BinarySerializeRead(oBinaryBuffer, m_nSn);
		BinarySerializeRead(oBinaryBuffer, m_strMerge_File);
		BinarySerializeRead(oBinaryBuffer, m_strMerge_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDescription);
		BinarySerializeRead(oBinaryBuffer, m_strMerge_Ids);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Merge_Report);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_User);
		BinarySerializeWrite(oBinaryBuffer, m_nSn);
		BinarySerializeWrite(oBinaryBuffer, m_strMerge_File);
		BinarySerializeWrite(oBinaryBuffer, m_strMerge_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDescription);
		BinarySerializeWrite(oBinaryBuffer, m_strMerge_Ids);
	}
	return 0;
}

void CIot_DeviceMergeReport::InitAfterRead()
{
}

BOOL CIot_DeviceMergeReport::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_DeviceMergeReport *p = (CIot_DeviceMergeReport*)pObj;

	if(m_nIndex_Merge_Report != p->m_nIndex_Merge_Report)
	{
		return FALSE;
	}

	if(m_nIndex_User != p->m_nIndex_User)
	{
		return FALSE;
	}

	if(m_nSn != p->m_nSn)
	{
		return FALSE;
	}

	if(m_strMerge_File != p->m_strMerge_File)
	{
		return FALSE;
	}

	if(m_strMerge_File_S != p->m_strMerge_File_S)
	{
		return FALSE;
	}

	if(m_strDescription != p->m_strDescription)
	{
		return FALSE;
	}

	if(m_strMerge_Ids != p->m_strMerge_Ids)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_DeviceMergeReport::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_DeviceMergeReport *p = (CIot_DeviceMergeReport*)pDest;

	p->m_nIndex_Merge_Report = m_nIndex_Merge_Report;
	p->m_nIndex_User = m_nIndex_User;
	p->m_nSn = m_nSn;
	p->m_strMerge_File = m_strMerge_File;
	p->m_strMerge_File_S = m_strMerge_File_S;
	p->m_strDescription = m_strDescription;
	p->m_strMerge_Ids = m_strMerge_Ids;
	return TRUE;
}

CBaseObject* CIot_DeviceMergeReport::Clone()
{
	CIot_DeviceMergeReport *p = new CIot_DeviceMergeReport();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceMergeReport::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceMergeReport *p = new CIot_DeviceMergeReport();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceMergeReport::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Merge_ReportKey, m_nIndex_Merge_Report);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strSnKey, m_nSn);
	pRecordset->GetFieldValue(pXmlKeys->m_strMerge_FileKey, m_strMerge_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strMerge_File_SKey, m_strMerge_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDescriptionKey, m_strDescription);
	pRecordset->GetFieldValue(pXmlKeys->m_strMerge_IdsKey, m_strMerge_Ids);
	return 0;
}

long CIot_DeviceMergeReport::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Merge_ReportKey, m_nIndex_Merge_Report);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strSnKey, m_nSn);
	pRecordset->SetFieldValue(pXmlKeys->m_strMerge_FileKey, m_strMerge_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strMerge_File_SKey, m_strMerge_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDescriptionKey, m_strDescription);
	pRecordset->SetFieldValue(pXmlKeys->m_strMerge_IdsKey, m_strMerge_Ids);
	return 0;
}

