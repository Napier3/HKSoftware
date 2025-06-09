//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_GetMessage.cpp  CTcpEdgePkgData_GetMessage


#include "stdafx.h"
#include "TcpEdgePkgData_GetMessage.h"

CTcpEdgePkgData_GetMessage::CTcpEdgePkgData_GetMessage()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_GetMessage::~CTcpEdgePkgData_GetMessage()
{
}

long CTcpEdgePkgData_GetMessage::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strStartTimeKey, oNode, m_strStartTime);
	xml_GetAttibuteValue(pXmlKeys->m_strEndTimeKey, oNode, m_strEndTime);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxNumberKey, oNode, m_strMaxNumber);
	return 0;
}

long CTcpEdgePkgData_GetMessage::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strStartTimeKey, oElement, m_strStartTime);
	xml_SetAttributeValue(pXmlKeys->m_strEndTimeKey, oElement, m_strEndTime);
	xml_SetAttributeValue(pXmlKeys->m_strMaxNumberKey, oElement, m_strMaxNumber);
	return 0;
}

long CTcpEdgePkgData_GetMessage::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strStartTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strEndTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strMaxNumber);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strStartTime);
		BinarySerializeRead(oBinaryBuffer, m_strEndTime);
		BinarySerializeRead(oBinaryBuffer, m_strMaxNumber);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strStartTime);
		BinarySerializeWrite(oBinaryBuffer, m_strEndTime);
		BinarySerializeWrite(oBinaryBuffer, m_strMaxNumber);
	}
	return 0;
}

void CTcpEdgePkgData_GetMessage::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_GetMessage::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_GetMessage *p = (CTcpEdgePkgData_GetMessage*)pObj;

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

BOOL CTcpEdgePkgData_GetMessage::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_GetMessage *p = (CTcpEdgePkgData_GetMessage*)pDest;

	p->m_strStartTime = m_strStartTime;
	p->m_strEndTime = m_strEndTime;
	p->m_strMaxNumber = m_strMaxNumber;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_GetMessage::Clone()
{
	CTcpEdgePkgData_GetMessage *p = new CTcpEdgePkgData_GetMessage();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_GetMessage::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("StartTime"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("EndTime"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("MaxNumber"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_GetMessage::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strStartTime);
	pListCtrl->SetItemText(lItemIndex, 2, m_strEndTime);
	pListCtrl->SetItemText(lItemIndex, 3, m_strMaxNumber);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_GetMessage::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_GetMessage::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_GetMessage::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_GetMessage::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strStartTimeKey, m_strStartTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strEndTimeKey, m_strEndTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strMaxNumberKey, m_strMaxNumber);
	return 0;
}

long CTcpEdgePkgData_GetMessage::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strStartTimeKey, m_strStartTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strEndTimeKey, m_strEndTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strMaxNumberKey, m_strMaxNumber);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_GetMessage::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_StartTime);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_EndTime);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_MaxNumber);


	return pDataset;
}