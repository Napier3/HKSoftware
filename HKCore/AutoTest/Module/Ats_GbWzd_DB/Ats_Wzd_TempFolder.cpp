//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_TempFolder.cpp  CAts_Wzd_TempFolder


#include "stdafx.h"
#include "Ats_Wzd_TempFolder.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_TempFolder::CAts_Wzd_TempFolder()
{
	//初始化属性
	m_nIndex_Folder = 0;
	m_nIndex_ParentFolder = 0;
	m_nSelect = 1;

	//初始化成员变量
}

CAts_Wzd_TempFolder::~CAts_Wzd_TempFolder()
{
}

long CAts_Wzd_TempFolder::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_FolderKey, oNode, m_nIndex_Folder);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ParentFolderKey, oNode, m_nIndex_ParentFolder);
	return 0;
}

long CAts_Wzd_TempFolder::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_FolderKey, oElement, m_nIndex_Folder);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ParentFolderKey, oElement, m_nIndex_ParentFolder);
	return 0;
}

long CAts_Wzd_TempFolder::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_ParentFolder);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_ParentFolder);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Folder);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_ParentFolder);
	}
	return 0;
}

void CAts_Wzd_TempFolder::InitAfterRead()
{
}

BOOL CAts_Wzd_TempFolder::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_TempFolder *p = (CAts_Wzd_TempFolder*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nIndex_Folder != p->m_nIndex_Folder)
	{
		return FALSE;
	}

	if(m_nIndex_ParentFolder != p->m_nIndex_ParentFolder)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAts_Wzd_TempFolder::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_TempFolder *p = (CAts_Wzd_TempFolder*)pDest;

	p->m_strName = m_strName;
	p->m_nIndex_Folder = m_nIndex_Folder;
	p->m_nIndex_ParentFolder = m_nIndex_ParentFolder;
	return TRUE;
}

CBaseObject* CAts_Wzd_TempFolder::Clone()
{
	CAts_Wzd_TempFolder *p = new CAts_Wzd_TempFolder();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_TempFolder::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_TempFolder *p = new CAts_Wzd_TempFolder();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_TempFolder::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
	{
		return TRUE;
	}

	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_TempFolder::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_TempFolderKey)
	{
		pNew = new CAts_Wzd_TempFolder();
	}
	else if (strClassID == pXmlKeys->m_strCAts_Wzd_TemplateUnitKey)
	{
		pNew = new CAts_Wzd_TemplateUnit();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_TempFolder::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
	{
		pNew = new CAts_Wzd_TempFolder();
	}
	else if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT)
	{
		pNew = new CAts_Wzd_TemplateUnit();
	}

	return pNew;
}
long CAts_Wzd_TempFolder::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ParentFolderKey, m_nIndex_ParentFolder);
	return 0;
}

long CAts_Wzd_TempFolder::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_FolderKey, m_nIndex_Folder);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ParentFolderKey, m_nIndex_ParentFolder);
	return 0;
}

CExBaseObject* CAts_Wzd_TempFolder::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_TempFolder();

	return pNew;
}

CAts_Wzd_TempFolder* CAts_Wzd_TempFolder::FindChildFolderByIndex(long nIndex)
{
	CAts_Wzd_TempFolder *pFind = NULL;
	CAts_Wzd_TempFolder *pFolder = NULL;
	POS pos = GetHeadPosition();
	UINT nClassID;

	while (pos != NULL)
	{
		CExBaseObject *pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
		{
			continue;
		}

		pFolder = (CAts_Wzd_TempFolder *)pObj;

		if (pFolder->m_nIndex_Folder == nIndex)
		{
			pFind = pFolder;
			break;
		}
	}

	return pFind;
}

void CAts_Wzd_TempFolder::RemoveAllTemplateUnits()
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT)
		{
			Remove(pObj);
			continue;
		}

		if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER)
		{
			CAts_Wzd_TempFolder *pFolder = (CAts_Wzd_TempFolder *)pObj;
			pFolder->RemoveAllTemplateUnits();
		}
	}
}