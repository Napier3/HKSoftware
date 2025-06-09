//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetModelResp_Mod.cpp  CPkg_GetModelResp_Mod


#include "stdafx.h"
#include "Pkg_GetModelResp_Mod.h"

CPkg_GetModelResp_Mod::CPkg_GetModelResp_Mod()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetModelResp_Mod::~CPkg_GetModelResp_Mod()
{
}

long CPkg_GetModelResp_Mod::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModelNameKey, oNode, m_strModelName);
	xml_GetAttibuteValue(pXmlKeys->m_strModifyTimeKey, oNode, m_strModifyTime);
	xml_GetAttibuteValue(pXmlKeys->m_strFullPathFileNameKey, oNode, m_strFullPathFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strFileCrcKey, oNode, m_strFileCrc);
	return 0;
}

long CPkg_GetModelResp_Mod::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strModelNameKey, oElement, m_strModelName);
	xml_SetAttributeValue(pXmlKeys->m_strModifyTimeKey, oElement, m_strModifyTime);
	xml_SetAttributeValue(pXmlKeys->m_strFullPathFileNameKey, oElement, m_strFullPathFileName);
	xml_SetAttributeValue(pXmlKeys->m_strFileCrcKey, oElement, m_strFileCrc);
	return 0;
}

long CPkg_GetModelResp_Mod::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strModelName);
		BinarySerializeCalLen(oBinaryBuffer, m_strModifyTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileCrc);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strModelName);
		BinarySerializeRead(oBinaryBuffer, m_strModifyTime);
		BinarySerializeRead(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeRead(oBinaryBuffer, m_strFileCrc);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strModelName);
		BinarySerializeWrite(oBinaryBuffer, m_strModifyTime);
		BinarySerializeWrite(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strFileCrc);
	}
	return 0;
}

void CPkg_GetModelResp_Mod::InitAfterRead()
{
}

BOOL CPkg_GetModelResp_Mod::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetModelResp_Mod *p = (CPkg_GetModelResp_Mod*)pObj;

	if(m_strModelName != p->m_strModelName)
	{
		return FALSE;
	}

	if(m_strModifyTime != p->m_strModifyTime)
	{
		return FALSE;
	}

	if(m_strFullPathFileName != p->m_strFullPathFileName)
	{
		return FALSE;
	}

	if(m_strFileCrc != p->m_strFileCrc)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetModelResp_Mod::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetModelResp_Mod *p = (CPkg_GetModelResp_Mod*)pDest;

	p->m_strModelName = m_strModelName;
	p->m_strModifyTime = m_strModifyTime;
	p->m_strFullPathFileName = m_strFullPathFileName;
	p->m_strFileCrc = m_strFileCrc;
	return TRUE;
}

CBaseObject* CPkg_GetModelResp_Mod::Clone()
{
	CPkg_GetModelResp_Mod *p = new CPkg_GetModelResp_Mod();
	Copy(p);
	return p;
}

long CPkg_GetModelResp_Mod::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ModelName"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ModifyTime"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("FullPathFileName"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("FileCrc"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetModelResp_Mod::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strModelName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strModifyTime);
	pListCtrl->SetItemText(lItemIndex, 3, m_strFullPathFileName);
	pListCtrl->SetItemText(lItemIndex, 4, m_strFileCrc);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetModelResp_Mod::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetModelResp_Mod::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetModelResp_Mod::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetModelResp_Mod::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strModelNameKey, m_strModelName);
	pRecordset->GetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	return 0;
}

long CPkg_GetModelResp_Mod::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strModelNameKey, m_strModelName);
	pRecordset->SetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	return 0;
}

