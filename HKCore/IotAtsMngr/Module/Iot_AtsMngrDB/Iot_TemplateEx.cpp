//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TemplateEx.cpp  CIot_TemplateEx


#include "stdafx.h"
#include "Iot_TemplateEx.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TemplateEx::CIot_TemplateEx()
{
	//初始化属性
	m_nIndex_Template_Ex = 0;
	m_nIndex_Template = 0;
	::GetLocalTime(&m_tmCreate_Time);

	//初始化成员变量
}

CIot_TemplateEx::~CIot_TemplateEx()
{
}

long CIot_TemplateEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Template_ExKey, oNode, m_nIndex_Template_Ex);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TemplateKey, oNode, m_nIndex_Template);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_FileKey, oNode, m_strDoc_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_File_SKey, oNode, m_strDoc_File_S);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_RptfileKey, oNode, m_strDoc_Rptfile);
	xml_GetAttibuteValue(pXmlKeys->m_strDoc_Rptfile_SKey, oNode, m_strDoc_Rptfile_S);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	return 0;
}

long CIot_TemplateEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Template_ExKey, oElement, m_nIndex_Template_Ex);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TemplateKey, oElement, m_nIndex_Template);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_FileKey, oElement, m_strDoc_File);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_File_SKey, oElement, m_strDoc_File_S);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_RptfileKey, oElement, m_strDoc_Rptfile);
	xml_SetAttributeValue(pXmlKeys->m_strDoc_Rptfile_SKey, oElement, m_strDoc_Rptfile_S);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	return 0;
}

long CIot_TemplateEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template_Ex);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_Rptfile);
		BinarySerializeCalLen(oBinaryBuffer, m_strDoc_Rptfile_S);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template_Ex);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_Rptfile);
		BinarySerializeRead(oBinaryBuffer, m_strDoc_Rptfile_S);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template_Ex);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_File_S);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_Rptfile);
		BinarySerializeWrite(oBinaryBuffer, m_strDoc_Rptfile_S);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
	}
	return 0;
}

void CIot_TemplateEx::InitAfterRead()
{
}

BOOL CIot_TemplateEx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TemplateEx *p = (CIot_TemplateEx*)pObj;

	if(m_nIndex_Template_Ex != p->m_nIndex_Template_Ex)
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

	if(m_strDoc_File_S != p->m_strDoc_File_S)
	{
		return FALSE;
	}

	if(m_strDoc_Rptfile != p->m_strDoc_Rptfile)
	{
		return FALSE;
	}

	if(m_strDoc_Rptfile_S != p->m_strDoc_Rptfile_S)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TemplateEx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TemplateEx *p = (CIot_TemplateEx*)pDest;

	p->m_nIndex_Template_Ex = m_nIndex_Template_Ex;
	p->m_nIndex_Template = m_nIndex_Template;
	p->m_strDoc_File = m_strDoc_File;
	p->m_strDoc_File_S = m_strDoc_File_S;
	p->m_strDoc_Rptfile = m_strDoc_Rptfile;
	p->m_strDoc_Rptfile_S = m_strDoc_Rptfile_S;
	p->m_tmCreate_Time = m_tmCreate_Time;
	return TRUE;
}

CBaseObject* CIot_TemplateEx::Clone()
{
	CIot_TemplateEx *p = new CIot_TemplateEx();
	Copy(p);
	return p;
}

CBaseObject* CIot_TemplateEx::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TemplateEx *p = new CIot_TemplateEx();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TemplateEx::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Template_ExKey, m_nIndex_Template_Ex);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_RptfileKey, m_strDoc_Rptfile);
	pRecordset->GetFieldValue(pXmlKeys->m_strDoc_Rptfile_SKey, m_strDoc_Rptfile_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

long CIot_TemplateEx::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Template_ExKey, m_nIndex_Template_Ex);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_FileKey, m_strDoc_File);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_File_SKey, m_strDoc_File_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_RptfileKey, m_strDoc_Rptfile);
	pRecordset->SetFieldValue(pXmlKeys->m_strDoc_Rptfile_SKey, m_strDoc_Rptfile_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	return 0;
}

BOOL CIot_TemplateEx::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TEMPLATE)
	{
		m_nIndex_Template = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

