//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataReadDevSvc.cpp  CPkg_DataReadDevSvc


#include "stdafx.h"
#include "Pkg_DataReadDevSvc.h"
#include "Pkg_DataReadDevSvcDL.h"
#include "Pkg_DataReadDevSvcDLs.h"
#include "../../../Module/xml/JSON/CJSON.h"
#include "../../../Module/xml/JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CPkg_DataReadDevSvc::CPkg_DataReadDevSvc()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataReadDevSvc::~CPkg_DataReadDevSvc()
{
}

long CPkg_DataReadDevSvc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strServiceIdKey, oNode, m_strServiceId);
	xml_GetAttibuteValue(pXmlKeys->m_strDataAllKey, oNode, m_strDataAll);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_DataList);
	if (pDatasJson)
	{
		CPkg_DataReadDevSvcDLs* pDatas = new CPkg_DataReadDevSvcDLs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_DataList;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_DataReadDevSvcDL* pString = new CPkg_DataReadDevSvcDL;
			pString->m_strValue = pDatasChild->valuestring;
			pDatas->AddNewChild(pString);
			pDatasChild = pDatasChild->next;
		}
	}
	return 0;
}

long CPkg_DataReadDevSvc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strServiceIdKey, oElement, m_strServiceId);
	xml_SetAttributeValue(pXmlKeys->m_strDataAllKey, oElement, m_strDataAll);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_DataReadDevSvcDLs* pDatas = (CPkg_DataReadDevSvcDLs*)FindByID(PkgData_Node_DataList);
	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_DataReadDevSvcDL* pString = (CPkg_DataReadDevSvcDL*)pDatas->GetNext(pos);
		CJSON* pStringJson = CJSON_CreateString(pString->m_strValue.GetString());
		CJSON_AddItemToArray(pDatasJson, pStringJson);
	}
	CJSON_AddItemToObject(pJson, PkgData_Node_DataList, pDatasJson);

	DeleteByID(PkgData_Node_DataList);
	return 0;
}

long CPkg_DataReadDevSvc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strServiceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataAll);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strServiceId);
		BinarySerializeRead(oBinaryBuffer, m_strDataAll);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strServiceId);
		BinarySerializeWrite(oBinaryBuffer, m_strDataAll);
	}
	return 0;
}

void CPkg_DataReadDevSvc::InitAfterRead()
{
}

BOOL CPkg_DataReadDevSvc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataReadDevSvc *p = (CPkg_DataReadDevSvc*)pObj;

	if(m_strServiceId != p->m_strServiceId)
	{
		return FALSE;
	}

	if(m_strDataAll != p->m_strDataAll)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_DataReadDevSvc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataReadDevSvc *p = (CPkg_DataReadDevSvc*)pDest;

	p->m_strServiceId = m_strServiceId;
	p->m_strDataAll = m_strDataAll;
	return TRUE;
}

CBaseObject* CPkg_DataReadDevSvc::Clone()
{
	CPkg_DataReadDevSvc *p = new CPkg_DataReadDevSvc();
	Copy(p);
	return p;
}

long CPkg_DataReadDevSvc::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ServiceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("DataAll"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataReadDevSvc::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strServiceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strDataAll);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataReadDevSvc::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataReadDevSvc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataReadDevSvc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_DataReadDevSvc::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataAllKey, m_strDataAll);
	return 0;
}

long CPkg_DataReadDevSvc::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataAllKey, m_strDataAll);
	return 0;
}

CDvmDataset* CPkg_DataReadDevSvc::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Services;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ServiceId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DataAll);
	CTcpEdgePkgData::AddNewDatas(pDataset, PkgData_Node_DataList);

	return pDataset;
}