//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetHisEvent_Device.cpp  CPkg_GetHisEvent_Device


#include "stdafx.h"
#include "Pkg_GetHisEvent_Device.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_GetHisEvent_Device::CPkg_GetHisEvent_Device()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetHisEvent_Device::~CPkg_GetHisEvent_Device()
{
}

long CPkg_GetHisEvent_Device::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strStartTimeKey, oNode, m_strStartTime);
	xml_GetAttibuteValue(pXmlKeys->m_strEndTimeKey, oNode, m_strEndTime);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxNumberKey, oNode, m_strMaxNumber);
	return 0;
}

long CPkg_GetHisEvent_Device::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strStartTimeKey, oElement, m_strStartTime);
	xml_SetAttributeValue(pXmlKeys->m_strEndTimeKey, oElement, m_strEndTime);
	xml_SetAttributeValue(pXmlKeys->m_strMaxNumberKey, oElement, m_strMaxNumber);
	return 0;
}

long CPkg_GetHisEvent_Device::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strStartTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strEndTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strMaxNumber);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strStartTime);
		BinarySerializeRead(oBinaryBuffer, m_strEndTime);
		BinarySerializeRead(oBinaryBuffer, m_strMaxNumber);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strStartTime);
		BinarySerializeWrite(oBinaryBuffer, m_strEndTime);
		BinarySerializeWrite(oBinaryBuffer, m_strMaxNumber);
	}
	return 0;
}

void CPkg_GetHisEvent_Device::InitAfterRead()
{
}

BOOL CPkg_GetHisEvent_Device::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetHisEvent_Device *p = (CPkg_GetHisEvent_Device*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strStartTime != p->m_strStartTime)
	{
		return FALSE;
	}

	if(m_strEndTime != p->m_strEndTime)
	{
		return FALSE;
	}

	if(m_strMaxNumber != p->m_strMaxNumber)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetHisEvent_Device::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetHisEvent_Device *p = (CPkg_GetHisEvent_Device*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strStartTime = m_strStartTime;
	p->m_strEndTime = m_strEndTime;
	p->m_strMaxNumber = m_strMaxNumber;
	return TRUE;
}

CBaseObject* CPkg_GetHisEvent_Device::Clone()
{
	CPkg_GetHisEvent_Device *p = new CPkg_GetHisEvent_Device();
	Copy(p);
	return p;
}

CBaseObject* CPkg_GetHisEvent_Device::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_GetHisEvent_Device *p = new CPkg_GetHisEvent_Device();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_GetHisEvent_Device::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetHisEvent_Device::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetHisEvent_Device::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetHisEvent_Device::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strStartTimeKey, m_strStartTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strEndTimeKey, m_strEndTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strMaxNumberKey, m_strMaxNumber);
	return 0;
}

long CPkg_GetHisEvent_Device::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strStartTimeKey, m_strStartTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strEndTimeKey, m_strEndTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strMaxNumberKey, m_strMaxNumber);
	return 0;
}

CDvmDataset* CPkg_GetHisEvent_Device::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Devices;
	pDataset->m_strDataType = PkgData_Type_Array;

	pDataset->m_dwItemData = 1;
	CTcpEdgePkgData::AddNewData(pDataset,PkgData_Node_DeviceID);
	CTcpEdgePkgData::AddNewData(pDataset,PkgData_Node_StartTime);
	CTcpEdgePkgData::AddNewData(pDataset,PkgData_Node_EndTime);
	CTcpEdgePkgData::AddNewData(pDataset,PkgData_Node_MaxNumber);

	return pDataset;
}

long CPkg_GetHisEvent_Device::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("StartTime"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("EndTime"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("MaxNumber"));
	pListCtrl->SetColumnWidth(4, 80);

	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetHisEvent_Device::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strStartTime);
	pListCtrl->SetItemText(lItemIndex, 3, m_strEndTime);
	pListCtrl->SetItemText(lItemIndex, 4, m_strMaxNumber);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}
