//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Template.cpp  CIot_Template


#include "stdafx.h"
#include "Iot_Template.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Template::CIot_Template()
{
	//初始化属性
	m_nIndex_Template = 0;
	m_nIndex_Folder = 0;
	m_nIndex_Devicetype = 0;
	::GetLocalTime(&m_tmTm_Update);
	m_nCnt_File_Doc_Ex = 0;
	m_nVersion = 0;

	//初始化成员变量
}

CIot_Template::~CIot_Template()
{
}

long CIot_Template::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TemplateKey, oNode, m_nIndex_Template);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FolderKey, oNode, m_nIndex_Folder);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DevicetypeKey, oNode, m_nIndex_Devicetype);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplate_FileKey, oNode, m_strTemplate_File);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_FileKey, oNode, m_strProtocol_File);
	xml_GetAttibuteValue(pXmlKeys->m_strIecfg_FileKey, oNode, m_strIecfg_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvm_File);
	xml_GetAttibuteValue(pXmlKeys->m_strGbxml_FileKey, oNode, m_strGbxml_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strXml_FileKey, oNode, m_strXml_File);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_UpdateKey, oNode, m_tmTm_Update);
	xml_GetAttibuteValue(pXmlKeys->m_strCnt_File_Doc_ExKey, oNode, m_nCnt_File_Doc_Ex);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_nVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strFile_ReportKey, oNode, m_strFile_Report);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplate_File_SKey, oNode, m_strTemplate_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_File_SKey, oNode, m_strProtocol_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strIecfg_File_SKey, oNode, m_strIecfg_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_File_SKey, oNode, m_strDvm_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strGbxml_File_SKey, oNode, m_strGbxml_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_strDoc_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strXml_File_SKey, oNode, m_strXml_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strFile_Report_SKey, oNode, m_strFile_Report_S);
	return 0;
}

long CIot_Template::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_TemplateKey, oElement, m_nIndex_Template);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FolderKey, oElement, m_nIndex_Folder);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DevicetypeKey, oElement, m_nIndex_Devicetype);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strTemplate_FileKey, oElement, m_strTemplate_File);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_FileKey, oElement, m_strProtocol_File);
	xml_SetAttributeValue(pXmlKeys->m_strIecfg_FileKey, oElement, m_strIecfg_File);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvm_File);
	xml_SetAttributeValue(pXmlKeys->m_strGbxml_FileKey, oElement, m_strGbxml_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strXml_FileKey, oElement, m_strXml_File);
	xml_SetAttributeValue(pXmlKeys->m_strTm_UpdateKey, oElement, m_tmTm_Update);
	xml_SetAttributeValue(pXmlKeys->m_strCnt_File_Doc_ExKey, oElement, m_nCnt_File_Doc_Ex);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_nVersion);
	xml_SetAttributeValue(pXmlKeys->m_strFile_ReportKey, oElement, m_strFile_Report);
	xml_SetAttributeValue(pXmlKeys->m_strTemplate_File_SKey, oElement, m_strTemplate_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_File_SKey, oElement, m_strProtocol_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strIecfg_File_SKey, oElement, m_strIecfg_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_File_SKey, oElement, m_strDvm_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strGbxml_File_SKey, oElement, m_strGbxml_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_strDoc_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strXml_File_SKey, oElement, m_strXml_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strFile_Report_SKey, oElement, m_strFile_Report_S);
	return 0;
}

long CIot_Template::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Devicetype);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strIecfg_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxml_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strXml_File);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeCalLen(oBinaryBuffer, m_nCnt_File_Doc_Ex);
		BinarySerializeCalLen(oBinaryBuffer, m_nVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile_Report);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplate_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strIecfg_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxml_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strXml_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile_Report_S);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Devicetype);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeRead(oBinaryBuffer, m_strIecfg_File);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File);
		BinarySerializeRead(oBinaryBuffer, m_strGbxml_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strXml_File);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeRead(oBinaryBuffer, m_nCnt_File_Doc_Ex);
		BinarySerializeRead(oBinaryBuffer, m_nVersion);
		BinarySerializeRead(oBinaryBuffer, m_strFile_Report);
		BinarySerializeRead(oBinaryBuffer, m_strTemplate_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strIecfg_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strGbxml_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strXml_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strFile_Report_S);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Devicetype);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeWrite(oBinaryBuffer, m_strIecfg_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File);
		BinarySerializeWrite(oBinaryBuffer, m_strGbxml_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strXml_File);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Update);
		BinarySerializeWrite(oBinaryBuffer, m_nCnt_File_Doc_Ex);
		BinarySerializeWrite(oBinaryBuffer, m_nVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strFile_Report);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplate_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strIecfg_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strGbxml_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strXml_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strFile_Report_S);
	}
	return 0;
}

void CIot_Template::InitAfterRead()
{
}

BOOL CIot_Template::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Template *p = (CIot_Template*)pObj;

	if(m_nIndex_Template != p->m_nIndex_Template)
	{
		return FALSE;
	}

	if(m_nIndex_Folder != p->m_nIndex_Folder)
	{
		return FALSE;
	}

	if(m_nIndex_Devicetype != p->m_nIndex_Devicetype)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
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

	if(m_strGbxml_File != p->m_strGbxml_File)
	{
		return FALSE;
	}

	if(m_strDoc_File != p->m_strDoc_File)
	{
		return FALSE;
	}

	if(m_strXml_File != p->m_strXml_File)
	{
		return FALSE;
	}

	if(m_nCnt_File_Doc_Ex != p->m_nCnt_File_Doc_Ex)
	{
		return FALSE;
	}

	if(m_nVersion != p->m_nVersion)
	{
		return FALSE;
	}

	if(m_strFile_Report != p->m_strFile_Report)
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

	if(m_strGbxml_File_S != p->m_strGbxml_File_S)
	{
		return FALSE;
	}

	if(m_strDoc_File_S != p->m_strDoc_File_S)
	{
		return FALSE;
	}

	if(m_strXml_File_S != p->m_strXml_File_S)
	{
		return FALSE;
	}

	if(m_strFile_Report_S != p->m_strFile_Report_S)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Template::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Template *p = (CIot_Template*)pDest;

	p->m_nIndex_Template = m_nIndex_Template;
	p->m_nIndex_Folder = m_nIndex_Folder;
	p->m_nIndex_Devicetype = m_nIndex_Devicetype;
	p->m_strName = m_strName;
	p->m_strTemplate_File = m_strTemplate_File;
	p->m_strProtocol_File = m_strProtocol_File;
	p->m_strIecfg_File = m_strIecfg_File;
	p->m_strDvm_File = m_strDvm_File;
	p->m_strGbxml_File = m_strGbxml_File;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strXml_File = m_strXml_File;
	p->m_tmTm_Update = m_tmTm_Update;
	p->m_nCnt_File_Doc_Ex = m_nCnt_File_Doc_Ex;
	p->m_nVersion = m_nVersion;
	p->m_strFile_Report = m_strFile_Report;
	p->m_strTemplate_File_S = m_strTemplate_File_S;
	p->m_strProtocol_File_S = m_strProtocol_File_S;
	p->m_strIecfg_File_S = m_strIecfg_File_S;
	p->m_strDvm_File_S = m_strDvm_File_S;
	p->m_strGbxml_File_S = m_strGbxml_File_S;
	p->m_strDoc_File_S = m_strDoc_File_S;
	p->m_strXml_File_S = m_strXml_File_S;
	p->m_strFile_Report_S = m_strFile_Report_S;
	return TRUE;
}

CBaseObject* CIot_Template::Clone()
{
	CIot_Template *p = new CIot_Template();
	Copy(p);
	return p;
}

CBaseObject* CIot_Template::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Template *p = new CIot_Template();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Template::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TEMPLATEDOCEX)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Template::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TemplateDocExKey)
	{
		pNew = new CIot_TemplateDocEx();
	}

	return pNew;
}

CExBaseObject* CIot_Template::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TEMPLATEDOCEX)
	{
		pNew = new CIot_TemplateDocEx();
	}

	return pNew;
}
long CIot_Template::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DevicetypeKey, m_nIndex_Devicetype);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemplate_FileKey, m_strTemplate_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_strProtocol_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strIecfg_FileKey, m_strIecfg_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strGbxml_FileKey, m_strGbxml_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strXml_FileKey, m_strXml_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	pRecordset->GetFieldValue(pXmlKeys->m_strCnt_File_Doc_ExKey, m_nCnt_File_Doc_Ex);
	pRecordset->GetFieldValue(pXmlKeys->m_strVersionKey, m_nVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strFile_ReportKey, m_strFile_Report);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemplate_File_SKey, m_strTemplate_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strProtocol_File_SKey, m_strProtocol_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strIecfg_File_SKey, m_strIecfg_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strGbxml_File_SKey, m_strGbxml_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strXml_File_SKey, m_strXml_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strFile_Report_SKey, m_strFile_Report_S);
	return 0;
}

long CIot_Template::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DevicetypeKey, m_nIndex_Devicetype);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemplate_FileKey, m_strTemplate_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_strProtocol_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strIecfg_FileKey, m_strIecfg_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strGbxml_FileKey, m_strGbxml_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strXml_FileKey, m_strXml_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_UpdateKey, m_tmTm_Update);
	pRecordset->SetFieldValue(pXmlKeys->m_strCnt_File_Doc_ExKey, m_nCnt_File_Doc_Ex);
	pRecordset->SetFieldValue(pXmlKeys->m_strVersionKey, m_nVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strFile_ReportKey, m_strFile_Report);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemplate_File_SKey, m_strTemplate_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strProtocol_File_SKey, m_strProtocol_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strIecfg_File_SKey, m_strIecfg_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_File_SKey, m_strDvm_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strGbxml_File_SKey, m_strGbxml_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strXml_File_SKey, m_strXml_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strFile_Report_SKey, m_strFile_Report_S);
	return 0;
}

BOOL CIot_Template::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TEMPLATEFOLDER)
	{
		m_nIndex_Folder = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

CExBaseObject* CIot_Template::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_TemplateDocEx();

	return pNew;
}
