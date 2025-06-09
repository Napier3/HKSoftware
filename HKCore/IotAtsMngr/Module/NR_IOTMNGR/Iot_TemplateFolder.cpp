//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TemplateFolder.cpp  CIot_TemplateFolder


#include "stdafx.h"
#include "Iot_TemplateFolder.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TemplateFolder::CIot_TemplateFolder()
{
	//初始化属性
	m_nIndex_Folder = 0;
	m_nIndex_Parent_Folder = 0;
	::GetLocalTime(&m_tmTm_Create);

	//初始化成员变量
}

CIot_TemplateFolder::~CIot_TemplateFolder()
{
}

long CIot_TemplateFolder::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FolderKey, oNode, m_nIndex_Folder);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Parent_FolderKey, oNode, m_nIndex_Parent_Folder);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strTm_CreateKey, oNode, m_tmTm_Create);
	return 0;
}

long CIot_TemplateFolder::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_FolderKey, oElement, m_nIndex_Folder);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Parent_FolderKey, oElement, m_nIndex_Parent_Folder);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strTm_CreateKey, oElement, m_tmTm_Create);
	return 0;
}

long CIot_TemplateFolder::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Parent_Folder);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTm_Create);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Parent_Folder);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_tmTm_Create);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Parent_Folder);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_tmTm_Create);
	}
	return 0;
}

void CIot_TemplateFolder::InitAfterRead()
{
}

BOOL CIot_TemplateFolder::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_TemplateFolder *p = (CIot_TemplateFolder*)pObj;

	if(m_nIndex_Folder != p->m_nIndex_Folder)
	{
		return FALSE;
	}

	if(m_nIndex_Parent_Folder != p->m_nIndex_Parent_Folder)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TemplateFolder::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_TemplateFolder *p = (CIot_TemplateFolder*)pDest;

	p->m_nIndex_Folder = m_nIndex_Folder;
	p->m_nIndex_Parent_Folder = m_nIndex_Parent_Folder;
	p->m_strName = m_strName;
	p->m_tmTm_Create = m_tmTm_Create;
	return TRUE;
}

CBaseObject* CIot_TemplateFolder::Clone()
{
	CIot_TemplateFolder *p = new CIot_TemplateFolder();
	Copy(p);
	return p;
}

CBaseObject* CIot_TemplateFolder::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TemplateFolder *p = new CIot_TemplateFolder();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_TemplateFolder::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TEMPLATEFOLDER)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOT_TEMPLATE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TemplateFolder::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TemplateFolderKey)
	{
		pNew = new CIot_TemplateFolder();
	}
	else if (strClassID == pXmlKeys->m_strCIot_TemplateKey)
	{
		pNew = new CIot_Template();
	}

	return pNew;
}

CExBaseObject* CIot_TemplateFolder::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TEMPLATEFOLDER)
	{
		pNew = new CIot_TemplateFolder();
	}
	else if (nClassID == IOTCLASSID_CIOT_TEMPLATE)
	{
		pNew = new CIot_Template();
	}

	return pNew;
}
long CIot_TemplateFolder::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Parent_FolderKey, m_nIndex_Parent_Folder);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strTm_CreateKey, m_tmTm_Create);
	return 0;
}

long CIot_TemplateFolder::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Parent_FolderKey, m_nIndex_Parent_Folder);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strTm_CreateKey, m_tmTm_Create);
	return 0;
}

