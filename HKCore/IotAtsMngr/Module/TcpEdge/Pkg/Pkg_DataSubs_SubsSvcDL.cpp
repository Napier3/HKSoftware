//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSubs_SubsSvcDL.cpp  CPkg_DataSubs_SubsSvcDL


#include "stdafx.h"
#include "Pkg_DataSubs_SubsSvcDL.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_DataSubs_SubsSvcDL::CPkg_DataSubs_SubsSvcDL()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataSubs_SubsSvcDL::~CPkg_DataSubs_SubsSvcDL()
{
}

long CPkg_DataSubs_SubsSvcDL::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataReferKey, oNode, m_strDataRefer);
	xml_GetAttibuteValue(pXmlKeys->m_strDZTypeKey, oNode, m_strDZType);
	xml_GetAttibuteValue(pXmlKeys->m_strDZValKey, oNode, m_strDZVal);
	return 0;
}

long CPkg_DataSubs_SubsSvcDL::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataReferKey, oElement, m_strDataRefer);
	xml_SetAttributeValue(pXmlKeys->m_strDZTypeKey, oElement, m_strDZType);
	xml_SetAttributeValue(pXmlKeys->m_strDZValKey, oElement, m_strDZVal);
	return 0;
}

long CPkg_DataSubs_SubsSvcDL::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataRefer);
		BinarySerializeCalLen(oBinaryBuffer, m_strDZType);
		BinarySerializeCalLen(oBinaryBuffer, m_strDZVal);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataRefer);
		BinarySerializeRead(oBinaryBuffer, m_strDZType);
		BinarySerializeRead(oBinaryBuffer, m_strDZVal);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataRefer);
		BinarySerializeWrite(oBinaryBuffer, m_strDZType);
		BinarySerializeWrite(oBinaryBuffer, m_strDZVal);
	}
	return 0;
}

void CPkg_DataSubs_SubsSvcDL::InitAfterRead()
{
}

BOOL CPkg_DataSubs_SubsSvcDL::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSubs_SubsSvcDL *p = (CPkg_DataSubs_SubsSvcDL*)pObj;

	if(m_strDataRefer != p->m_strDataRefer)
	{
		return FALSE;
	}

	if(m_strDZType != p->m_strDZType)
	{
		return FALSE;
	}

	if(m_strDZVal != p->m_strDZVal)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_DataSubs_SubsSvcDL::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSubs_SubsSvcDL *p = (CPkg_DataSubs_SubsSvcDL*)pDest;

	p->m_strDataRefer = m_strDataRefer;
	p->m_strDZType = m_strDZType;
	p->m_strDZVal = m_strDZVal;
	return TRUE;
}

CBaseObject* CPkg_DataSubs_SubsSvcDL::Clone()
{
	CPkg_DataSubs_SubsSvcDL *p = new CPkg_DataSubs_SubsSvcDL();
	Copy(p);
	return p;
}

CBaseObject* CPkg_DataSubs_SubsSvcDL::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_DataSubs_SubsSvcDL *p = new CPkg_DataSubs_SubsSvcDL();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}


long CPkg_DataSubs_SubsSvcDL::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DataRefer"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("DZType"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("DZVal"));
	pListCtrl->SetColumnWidth(3, 80);

	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSubs_SubsSvcDL::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDataRefer);
	pListCtrl->SetItemText(lItemIndex, 2, m_strDZType);
	pListCtrl->SetItemText(lItemIndex, 3, m_strDZVal);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSubs_SubsSvcDL::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSubs_SubsSvcDL::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSubs_SubsSvcDL::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_DataSubs_SubsSvcDL::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->GetFieldValue(pXmlKeys->m_strDZTypeKey, m_strDZType);
	pRecordset->GetFieldValue(pXmlKeys->m_strDZValKey, m_strDZVal);
	return 0;
}

long CPkg_DataSubs_SubsSvcDL::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->SetFieldValue(pXmlKeys->m_strDZTypeKey, m_strDZType);
	pRecordset->SetFieldValue(pXmlKeys->m_strDZValKey, m_strDZVal);
	return 0;
}

CDvmDataset* CPkg_DataSubs_SubsSvcDL::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_DataList;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DataRefer);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DZType, 0);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DZVal,0);


	return  pDataset;
}