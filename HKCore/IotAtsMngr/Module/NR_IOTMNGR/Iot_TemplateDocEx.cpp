//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TemplateDocEx.cpp  CIot_TemplateDocEx


#include "stdafx.h"
#include "Iot_TemplateDocEx.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TemplateDocEx::CIot_TemplateDocEx()
{
	//初始化属性
	m_nIndex_Template_Doc = 0;
	m_nIndex_Template = 0;

	//初始化成员变量
}

CIot_TemplateDocEx::~CIot_TemplateDocEx()
{
}

long CIot_TemplateDocEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Template_DocKey, oNode, m_nIndex_Template_Doc);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TemplateKey, oNode, m_nIndex_Template);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_RptfileKey, oNode, m_strDoc_Rptfile);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_strDoc_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_Rptfile_SKey, oNode, m_strDoc_Rptfile_S);
	return 0;
}

long CIot_TemplateDocEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Template_DocKey, oElement, m_nIndex_Template_Doc);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TemplateKey, oElement, m_nIndex_Template);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_RptfileKey, oElement, m_strDoc_Rptfile);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_strDoc_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_Rptfile_SKey, oElement, m_strDoc_Rptfile_S);
	return 0;
}

long CIot_TemplateDocEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template_Doc);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_Rptfile);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_Rptfile_S);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template_Doc);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_Rptfile);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_Rptfile_S);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template_Doc);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_Rptfile);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_Rptfile_S);
	}
	return 0;
}

void CIot_TemplateDocEx::InitAfterRead()
{
}

BOOL CIot_TemplateDocEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TemplateDocEx *p = (CIot_TemplateDocEx*)pObj;

	if(m_nIndex_Template_Doc != p->m_nIndex_Template_Doc)
	{
		return FALSE;
	}

	if(m_nIndex_Template != p->m_nIndex_Template)
	{
		return FALSE;
	}

	if(m_strDoc_File != p->m_strDoc_File)
	{
		return FALSE;
	}

	if(m_strDoc_Rptfile != p->m_strDoc_Rptfile)
	{
		return FALSE;
	}

	if(m_strDoc_File_S != p->m_strDoc_File_S)
	{
		return FALSE;
	}

	if(m_strDoc_Rptfile_S != p->m_strDoc_Rptfile_S)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TemplateDocEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TemplateDocEx *p = (CIot_TemplateDocEx*)pDest;

	p->m_nIndex_Template_Doc = m_nIndex_Template_Doc;
	p->m_nIndex_Template = m_nIndex_Template;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strDoc_Rptfile = m_strDoc_Rptfile;
	p->m_strDoc_File_S = m_strDoc_File_S;
	p->m_strDoc_Rptfile_S = m_strDoc_Rptfile_S;
	return TRUE;
}

CBaseObject* CIot_TemplateDocEx::Clone()
{
	CIot_TemplateDocEx *p = new CIot_TemplateDocEx();
	Copy(p);
	return p;
}

CBaseObject* CIot_TemplateDocEx::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TemplateDocEx *p = new CIot_TemplateDocEx();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TemplateDocEx::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Template_DocKey, m_nIndex_Template_Doc);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_RptfileKey, m_strDoc_Rptfile);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_Rptfile_SKey, m_strDoc_Rptfile_S);
	return 0;
}

long CIot_TemplateDocEx::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Template_DocKey, m_nIndex_Template_Doc);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_RptfileKey, m_strDoc_Rptfile);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_Rptfile_SKey, m_strDoc_Rptfile_S);
	return 0;
}

BOOL CIot_TemplateDocEx::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TEMPLATE)
	{
		m_nIndex_Template = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

