//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetHisData_DevSvc.cpp  CPkg_GetHisData_DevSvc


#include "stdafx.h"
#include "Pkg_GetHisData_DevSvc.h"

CPkg_GetHisData_DevSvc::CPkg_GetHisData_DevSvc()
{
	m_arrayNotMust[0] = PkgData_Node_Interval;
}

CPkg_GetHisData_DevSvc::~CPkg_GetHisData_DevSvc()
{
}

long CPkg_GetHisData_DevSvc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMaxNumberKey, oNode, m_strMaxNumber);
	xml_GetAttibuteValue(pXmlKeys->m_strIntervalKey, oNode, m_strInterval);
	xml_GetAttibuteValue(pXmlKeys->m_strEndTimeKey, oNode, m_strEndTime);
	xml_GetAttibuteValue(pXmlKeys->m_strStartTimeKey, oNode, m_strStartTime);
	xml_GetAttibuteValue(pXmlKeys->m_strServiceIdKey, oNode, m_strServiceId);
	return 0;
}

long CPkg_GetHisData_DevSvc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMaxNumberKey, oElement, m_strMaxNumber);
	xml_SetAttributeValue(pXmlKeys->m_strIntervalKey, oElement, m_strInterval);
	xml_SetAttributeValue(pXmlKeys->m_strEndTimeKey, oElement, m_strEndTime);
	xml_SetAttributeValue(pXmlKeys->m_strStartTimeKey, oElement, m_strStartTime);
	xml_SetAttributeValue(pXmlKeys->m_strServiceIdKey, oElement, m_strServiceId);
	return 0;
}

long CPkg_GetHisData_DevSvc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMaxNumber);
		BinarySerializeCalLen(oBinaryBuffer, m_strInterval);
		BinarySerializeCalLen(oBinaryBuffer, m_strEndTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strStartTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strServiceId);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMaxNumber);
		BinarySerializeRead(oBinaryBuffer, m_strInterval);
		BinarySerializeRead(oBinaryBuffer, m_strEndTime);
		BinarySerializeRead(oBinaryBuffer, m_strStartTime);
		BinarySerializeRead(oBinaryBuffer, m_strServiceId);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMaxNumber);
		BinarySerializeWrite(oBinaryBuffer, m_strInterval);
		BinarySerializeWrite(oBinaryBuffer, m_strEndTime);
		BinarySerializeWrite(oBinaryBuffer, m_strStartTime);
		BinarySerializeWrite(oBinaryBuffer, m_strServiceId);
	}
	return 0;
}

void CPkg_GetHisData_DevSvc::InitAfterRead()
{
}

BOOL CPkg_GetHisData_DevSvc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetHisData_DevSvc *p = (CPkg_GetHisData_DevSvc*)pObj;

	if(m_strMaxNumber != p->m_strMaxNumber)
	{
		return FALSE;
	}

	if(m_strInterval != p->m_strInterval)
	{
		return FALSE;
	}

	if(m_strEndTime != p->m_strEndTime)
	{
		return FALSE;
	}

	if(m_strStartTime != p->m_strStartTime)
	{
		return FALSE;
	}

	if(m_strServiceId != p->m_strServiceId)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetHisData_DevSvc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetHisData_DevSvc *p = (CPkg_GetHisData_DevSvc*)pDest;

	p->m_strMaxNumber = m_strMaxNumber;
	p->m_strInterval = m_strInterval;
	p->m_strEndTime = m_strEndTime;
	p->m_strStartTime = m_strStartTime;
	p->m_strServiceId = m_strServiceId;
	return TRUE;
}

CBaseObject* CPkg_GetHisData_DevSvc::Clone()
{
	CPkg_GetHisData_DevSvc *p = new CPkg_GetHisData_DevSvc();
	Copy(p);
	return p;
}

long CPkg_GetHisData_DevSvc::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("MaxNumber"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Interval"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("EndTime"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("StartTime"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("ServiceId"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetHisData_DevSvc::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strMaxNumber);
	pListCtrl->SetItemText(lItemIndex, 2, m_strInterval);
	pListCtrl->SetItemText(lItemIndex, 3, m_strEndTime);
	pListCtrl->SetItemText(lItemIndex, 4, m_strStartTime);
	pListCtrl->SetItemText(lItemIndex, 5, m_strServiceId);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetHisData_DevSvc::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetHisData_DevSvc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetHisData_DevSvc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetHisData_DevSvc::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strMaxNumberKey, m_strMaxNumber);
	pRecordset->GetFieldValue(pXmlKeys->m_strIntervalKey, m_strInterval);
	pRecordset->GetFieldValue(pXmlKeys->m_strEndTimeKey, m_strEndTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strStartTimeKey, m_strStartTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	return 0;
}

long CPkg_GetHisData_DevSvc::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strMaxNumberKey, m_strMaxNumber);
	pRecordset->SetFieldValue(pXmlKeys->m_strIntervalKey, m_strInterval);
	pRecordset->SetFieldValue(pXmlKeys->m_strEndTimeKey, m_strEndTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strStartTimeKey, m_strStartTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	return 0;
}

CDvmDataset* CPkg_GetHisData_DevSvc::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Services;
	pDataset->m_strDataType = PkgData_Type_Object;
	//lmy,20230919添加
	pDataset->m_dwItemData = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ServiceId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_StartTime);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_EndTime);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Interval, 0);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_MaxNumber);

	return pDataset;
}