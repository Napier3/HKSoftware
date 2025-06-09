//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_CtrlCmd.cpp  CTcpEdgePkgData_CtrlCmd


#include "stdafx.h"
#include "TcpEdgePkgData_CtrlCmd.h"

CTcpEdgePkgData_CtrlCmd::CTcpEdgePkgData_CtrlCmd()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_CtrlCmd::~CTcpEdgePkgData_CtrlCmd()
{
}

long CTcpEdgePkgData_CtrlCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strDataReferKey, oNode, m_strDataRefer);
	xml_GetAttibuteValue(pXmlKeys->m_strCtrlTypeKey, oNode, m_strCtrlType);
	xml_GetAttibuteValue(pXmlKeys->m_strCtrlValKey, oNode, m_strCtrlVal);
	return 0;
}

long CTcpEdgePkgData_CtrlCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strDataReferKey, oElement, m_strDataRefer);
	xml_SetAttributeValue(pXmlKeys->m_strCtrlTypeKey, oElement, m_strCtrlType);
	xml_SetAttributeValue(pXmlKeys->m_strCtrlValKey, oElement, m_strCtrlVal);
	return 0;
}

long CTcpEdgePkgData_CtrlCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataRefer);
		BinarySerializeCalLen(oBinaryBuffer, m_strCtrlType);
		BinarySerializeCalLen(oBinaryBuffer, m_strCtrlVal);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strDataRefer);
		BinarySerializeRead(oBinaryBuffer, m_strCtrlType);
		BinarySerializeRead(oBinaryBuffer, m_strCtrlVal);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strDataRefer);
		BinarySerializeWrite(oBinaryBuffer, m_strCtrlType);
		BinarySerializeWrite(oBinaryBuffer, m_strCtrlVal);
	}
	return 0;
}

void CTcpEdgePkgData_CtrlCmd::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_CtrlCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_CtrlCmd *p = (CTcpEdgePkgData_CtrlCmd*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strDataRefer != p->m_strDataRefer)
	{
		return FALSE;
	}

	if(m_strCtrlType != p->m_strCtrlType)
	{
		return FALSE;
	}

	if(m_strCtrlVal != p->m_strCtrlVal)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_CtrlCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_CtrlCmd *p = (CTcpEdgePkgData_CtrlCmd*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strDataRefer = m_strDataRefer;
	p->m_strCtrlType = m_strCtrlType;
	p->m_strCtrlVal = m_strCtrlVal;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_CtrlCmd::Clone()
{
	CTcpEdgePkgData_CtrlCmd *p = new CTcpEdgePkgData_CtrlCmd();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_CtrlCmd::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("DataRefer"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("CtrlType"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("CtrlVal"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_CtrlCmd::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strDataRefer);
	pListCtrl->SetItemText(lItemIndex, 3, m_strCtrlType);
	pListCtrl->SetItemText(lItemIndex, 4, m_strCtrlVal);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_CtrlCmd::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_CtrlCmd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_CtrlCmd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_CtrlCmd::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->GetFieldValue(pXmlKeys->m_strCtrlTypeKey, m_strCtrlType);
	pRecordset->GetFieldValue(pXmlKeys->m_strCtrlValKey, m_strCtrlVal);
	return 0;
}

long CTcpEdgePkgData_CtrlCmd::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->SetFieldValue(pXmlKeys->m_strCtrlTypeKey, m_strCtrlType);
	pRecordset->SetFieldValue(pXmlKeys->m_strCtrlValKey, m_strCtrlVal);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_CtrlCmd::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DeviceID);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DataRefer);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_CtrlType);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_CtrlVal);

	return pDataset;
}