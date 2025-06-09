//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetDataSubs_SubSvc.cpp  CPkg_GetDataSubs_SubSvc


#include "stdafx.h"
#include "Pkg_GetDataSubs_SubSvc.h"
#include "Pkg_GetDataSubs_SubSvcDev.h"
#include "Pkg_GetDataSubs_SubSvcDevs.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"


CPkg_GetDataSubs_SubSvc::CPkg_GetDataSubs_SubSvc()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetDataSubs_SubSvc::~CPkg_GetDataSubs_SubSvc()
{
}

long CPkg_GetDataSubs_SubSvc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strServiceIdKey, oNode, m_strServiceId);
	xml_GetAttibuteValue(pXmlKeys->m_strAllDevKey, oNode, m_strAllDev);


	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_DeviceList);
	if (pDatasJson)
	{
		CPkg_GetDataSubs_SubSvcDevs* pDatas = new CPkg_GetDataSubs_SubSvcDevs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_DeviceList;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_GetDataSubs_SubSvcDev* pString = new CPkg_GetDataSubs_SubSvcDev;
			pString->m_strValue = pDatasChild->valuestring;
			pDatas->AddNewChild(pString);
			pDatasChild = pDatasChild->next;
		}
	}
	return 0;
}

long CPkg_GetDataSubs_SubSvc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strServiceIdKey, oElement, m_strServiceId);
	xml_SetAttributeValue(pXmlKeys->m_strAllDevKey, oElement, m_strAllDev);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_GetDataSubs_SubSvcDevs* pDatas = (CPkg_GetDataSubs_SubSvcDevs*)FindByID(PkgData_Node_DeviceList);
	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_GetDataSubs_SubSvcDev* pString = (CPkg_GetDataSubs_SubSvcDev*)pDatas->GetNext(pos);
		CJSON* pStringJson = CJSON_CreateString(pString->m_strValue.GetString());
		CJSON_AddItemToArray(pDatasJson, pStringJson);
	}
	CJSON_AddItemToObject(pJson, PkgData_Node_DeviceList, pDatasJson);

	DeleteByID(PkgData_Node_DeviceList);
	return 0;
}

long CPkg_GetDataSubs_SubSvc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strServiceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strAllDev);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strServiceId);
		BinarySerializeRead(oBinaryBuffer, m_strAllDev);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strServiceId);
		BinarySerializeWrite(oBinaryBuffer, m_strAllDev);
	}
	return 0;
}

void CPkg_GetDataSubs_SubSvc::InitAfterRead()
{
}

BOOL CPkg_GetDataSubs_SubSvc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetDataSubs_SubSvc *p = (CPkg_GetDataSubs_SubSvc*)pObj;

	if(m_strServiceId != p->m_strServiceId)
	{
		return FALSE;
	}

	if(m_strAllDev != p->m_strAllDev)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetDataSubs_SubSvc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetDataSubs_SubSvc *p = (CPkg_GetDataSubs_SubSvc*)pDest;

	p->m_strServiceId = m_strServiceId;
	p->m_strAllDev = m_strAllDev;
	return TRUE;
}

CBaseObject* CPkg_GetDataSubs_SubSvc::Clone()
{
	CPkg_GetDataSubs_SubSvc *p = new CPkg_GetDataSubs_SubSvc();
	Copy(p);
	return p;
}

long CPkg_GetDataSubs_SubSvc::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ServiceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("AllDev"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetDataSubs_SubSvc::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strServiceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strAllDev);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetDataSubs_SubSvc::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetDataSubs_SubSvc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetDataSubs_SubSvc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetDataSubs_SubSvc::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strAllDevKey, m_strAllDev);
	return 0;
}

long CPkg_GetDataSubs_SubSvc::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strAllDevKey, m_strAllDev);
	return 0;
}

CDvmDataset* CPkg_GetDataSubs_SubSvc::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Services;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ServiceId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_AllDev);
	CTcpEdgePkgData::AddNewDatas(pDataset, PkgData_Node_DeviceList);


	return pDataset;
}