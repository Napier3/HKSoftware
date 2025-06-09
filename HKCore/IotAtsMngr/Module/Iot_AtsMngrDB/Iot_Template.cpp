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
	m_nIndex_Template_Dir = 0;
	m_nIndex_Device_Classify = 0;
	m_nIndex_Device_Type = 0;
	::GetLocalTime(&m_tmUpload_Time);
	m_nCnt_File_Doc_Ex = 0;
	m_nVersion = 0;

	//初始化成员变量
}

CIot_Template::~CIot_Template()
{
}

long CIot_Template::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TemplateKey, oNode, m_nIndex_Template);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Template_DirKey, oNode, m_nIndex_Template_Dir);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oNode, m_nIndex_Device_Classify);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Device_TypeKey, oNode, m_nIndex_Device_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTemplate_FileKey, oNode, m_strTemplate_File);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocol_FileKey, oNode, m_strProtocol_File);
	xml_GetAttibuteValue(pXmlKeys->m_strIecfg_FileKey, oNode, m_strIecfg_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDvm_FileKey, oNode, m_strDvm_File);
	xml_GetAttibuteValue(pXmlKeys->m_strGbxml_FileKey, oNode, m_strGbxml_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strXml_FileKey, oNode, m_strXml_File);
	xml_GetAttibuteValue(pXmlKeys->m_strUpload_TimeKey, oNode, m_tmUpload_Time);
	xml_GetAttibuteValue(pXmlKeys->m_strCnt_File_Doc_ExKey, oNode, m_nCnt_File_Doc_Ex);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_nVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strFile_ReportKey, oNode, m_strFile_Report);
	xml_GetAttibuteValue(pXmlKeys->m_strSvr_Relate_PathKey, oNode, m_strSvr_Relate_Path);
	xml_GetAttibuteValue(pXmlKeys->m_strItem_Gen_FileKey, oNode, m_strItem_Gen_File);
	xml_GetAttibuteValue(pXmlKeys->m_strItem_Gen_File_SKey, oNode, m_strItem_Gen_File_S);
	return 0;
}

long CIot_Template::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_TemplateKey, oElement, m_nIndex_Template);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Template_DirKey, oElement, m_nIndex_Template_Dir);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_ClassifyKey, oElement, m_nIndex_Device_Classify);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Device_TypeKey, oElement, m_nIndex_Device_Type);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strTemplate_FileKey, oElement, m_strTemplate_File);
	xml_SetAttributeValue(pXmlKeys->m_strProtocol_FileKey, oElement, m_strProtocol_File);
	xml_SetAttributeValue(pXmlKeys->m_strIecfg_FileKey, oElement, m_strIecfg_File);
	xml_SetAttributeValue(pXmlKeys->m_strDvm_FileKey, oElement, m_strDvm_File);
	xml_SetAttributeValue(pXmlKeys->m_strGbxml_FileKey, oElement, m_strGbxml_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strXml_FileKey, oElement, m_strXml_File);
	xml_SetAttributeValue(pXmlKeys->m_strUpload_TimeKey, oElement, m_tmUpload_Time);
	xml_SetAttributeValue(pXmlKeys->m_strCnt_File_Doc_ExKey, oElement, m_nCnt_File_Doc_Ex);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_nVersion);
	xml_SetAttributeValue(pXmlKeys->m_strFile_ReportKey, oElement, m_strFile_Report);
	xml_SetAttributeValue(pXmlKeys->m_strSvr_Relate_PathKey, oElement, m_strSvr_Relate_Path);
	xml_SetAttributeValue(pXmlKeys->m_strItem_Gen_FileKey, oElement, m_strItem_Gen_File);
	xml_SetAttributeValue(pXmlKeys->m_strItem_Gen_File_SKey, oElement, m_strItem_Gen_File_S);
	return 0;
}

long CIot_Template::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template_Dir);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strIecfg_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvm_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxml_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strXml_File);
		BinarySerializeCalLen(oBinaryBuffer, m_tmUpload_Time);
		BinarySerializeCalLen(oBinaryBuffer, m_nCnt_File_Doc_Ex);
		BinarySerializeCalLen(oBinaryBuffer, m_nVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile_Report);
		BinarySerializeCalLen(oBinaryBuffer, m_strSvr_Relate_Path);
		BinarySerializeCalLen(oBinaryBuffer, m_strItem_Gen_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strItem_Gen_File_S);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template_Dir);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeRead(oBinaryBuffer, m_strIecfg_File);
		BinarySerializeRead(oBinaryBuffer, m_strDvm_File);
		BinarySerializeRead(oBinaryBuffer, m_strGbxml_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strXml_File);
		BinarySerializeRead(oBinaryBuffer, m_tmUpload_Time);
		BinarySerializeRead(oBinaryBuffer, m_nCnt_File_Doc_Ex);
		BinarySerializeRead(oBinaryBuffer, m_nVersion);
		BinarySerializeRead(oBinaryBuffer, m_strFile_Report);
		BinarySerializeRead(oBinaryBuffer, m_strSvr_Relate_Path);
		BinarySerializeRead(oBinaryBuffer, m_strItem_Gen_File);
		BinarySerializeRead(oBinaryBuffer, m_strItem_Gen_File_S);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template_Dir);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Classify);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol_File);
		BinarySerializeWrite(oBinaryBuffer, m_strIecfg_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDvm_File);
		BinarySerializeWrite(oBinaryBuffer, m_strGbxml_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strXml_File);
		BinarySerializeWrite(oBinaryBuffer, m_tmUpload_Time);
		BinarySerializeWrite(oBinaryBuffer, m_nCnt_File_Doc_Ex);
		BinarySerializeWrite(oBinaryBuffer, m_nVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strFile_Report);
		BinarySerializeWrite(oBinaryBuffer, m_strSvr_Relate_Path);
		BinarySerializeWrite(oBinaryBuffer, m_strItem_Gen_File);
		BinarySerializeWrite(oBinaryBuffer, m_strItem_Gen_File_S);
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

	if(m_nIndex_Template_Dir != p->m_nIndex_Template_Dir)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Classify != p->m_nIndex_Device_Classify)
	{
		return FALSE;
	}

	if(m_nIndex_Device_Type != p->m_nIndex_Device_Type)
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

	if(m_strSvr_Relate_Path != p->m_strSvr_Relate_Path)
	{
		return FALSE;
	}

	if(m_strItem_Gen_File != p->m_strItem_Gen_File)
	{
		return FALSE;
	}

	if(m_strItem_Gen_File_S != p->m_strItem_Gen_File_S)
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
	p->m_nIndex_Template_Dir = m_nIndex_Template_Dir;
	p->m_nIndex_Device_Classify = m_nIndex_Device_Classify;
	p->m_nIndex_Device_Type = m_nIndex_Device_Type;
	p->m_strName = m_strName;
	p->m_strTemplate_File = m_strTemplate_File;
	p->m_strProtocol_File = m_strProtocol_File;
	p->m_strIecfg_File = m_strIecfg_File;
	p->m_strDvm_File = m_strDvm_File;
	p->m_strGbxml_File = m_strGbxml_File;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strXml_File = m_strXml_File;
	p->m_tmUpload_Time = m_tmUpload_Time;
	p->m_nCnt_File_Doc_Ex = m_nCnt_File_Doc_Ex;
	p->m_nVersion = m_nVersion;
	p->m_strFile_Report = m_strFile_Report;
	p->m_strSvr_Relate_Path = m_strSvr_Relate_Path;
	p->m_strItem_Gen_File = m_strItem_Gen_File;
	p->m_strItem_Gen_File_S = m_strItem_Gen_File_S;
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

long CIot_Template::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Template_DirKey, m_nIndex_Template_Dir);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemplate_FileKey, m_strTemplate_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_strProtocol_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strIecfg_FileKey, m_strIecfg_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strGbxml_FileKey, m_strGbxml_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strXml_FileKey, m_strXml_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strUpload_TimeKey, m_tmUpload_Time);
	pRecordset->GetFieldValue(pXmlKeys->m_strCnt_File_Doc_ExKey, m_nCnt_File_Doc_Ex);
	pRecordset->GetFieldValue(pXmlKeys->m_strVersionKey, m_nVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strFile_ReportKey, m_strFile_Report);
	pRecordset->GetFieldValue(pXmlKeys->m_strSvr_Relate_PathKey, m_strSvr_Relate_Path);
	pRecordset->GetFieldValue(pXmlKeys->m_strItem_Gen_FileKey, m_strItem_Gen_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strItem_Gen_File_SKey, m_strItem_Gen_File_S);
	return 0;
}

long CIot_Template::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Template_DirKey, m_nIndex_Template_Dir);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_ClassifyKey, m_nIndex_Device_Classify);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Device_TypeKey, m_nIndex_Device_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemplate_FileKey, m_strTemplate_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strProtocol_FileKey, m_strProtocol_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strIecfg_FileKey, m_strIecfg_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDvm_FileKey, m_strDvm_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strGbxml_FileKey, m_strGbxml_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strXml_FileKey, m_strXml_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strUpload_TimeKey, m_tmUpload_Time);
	pRecordset->SetFieldValue(pXmlKeys->m_strCnt_File_Doc_ExKey, m_nCnt_File_Doc_Ex);
	pRecordset->SetFieldValue(pXmlKeys->m_strVersionKey, m_nVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strFile_ReportKey, m_strFile_Report);
	pRecordset->SetFieldValue(pXmlKeys->m_strSvr_Relate_PathKey, m_strSvr_Relate_Path);
	pRecordset->SetFieldValue(pXmlKeys->m_strItem_Gen_FileKey, m_strItem_Gen_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strItem_Gen_File_SKey, m_strItem_Gen_File_S);
	return 0;
}

BOOL CIot_Template::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	return TRUE;
}

//测试模板上传时，数据库name属性填写为文件名称（去掉后缀）
BOOL CIot_Template::QureyTemplateByName(CXDbBaseLib *pXDbLib, const CString &strFileName)
{
	CString strTemplateTable,strSql;
	strTemplateTable = CIot_AtsMngrXmlRWKeys::CIot_TemplateKey();

	CString strName = ChangeFilePostfix(strFileName,_T(""));

	strSql.Format(_T("select * from %s where name=\"%s\" limit 1"),strTemplateTable,strFileName);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}

