//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSubs_SubsSvc.cpp  CPkg_DataSubs_SubsSvc


#include "stdafx.h"
#include "Pkg_DataSubs_SubsSvc.h"
#include "Pkg_DataSubs_SubsSvcDev.h"
#include "Pkg_DataSubs_SubsSvcDevs.h"
#include "Pkg_DataSubs_SubsSvcDL.h"
#include "Pkg_DataSubs_SubsSvcDLs.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"

CPkg_DataSubs_SubsSvc::CPkg_DataSubs_SubsSvc()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataSubs_SubsSvc::~CPkg_DataSubs_SubsSvc()
{
}

long CPkg_DataSubs_SubsSvc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strServiceIdKey, oNode, m_strServiceId);
	xml_GetAttibuteValue(pXmlKeys->m_strAllDevKey, oNode, m_strAllDev);
	xml_GetAttibuteValue(pXmlKeys->m_strPeriodKey, oNode, m_strPeriod);
	xml_GetAttibuteValue(pXmlKeys->m_strSpontKey, oNode, m_strSpont);
	xml_GetAttibuteValue(pXmlKeys->m_strAllDataKey, oNode, m_strAllData);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_DeviceList);
	if (pDatasJson)
	{
		CPkg_DataSubs_SubsSvcDevs* pDatas = new CPkg_DataSubs_SubsSvcDevs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_DeviceList;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_DataSubs_SubsSvcDev* pString = new CPkg_DataSubs_SubsSvcDev;
			pString->m_strValue = pDatasChild->valuestring;
			pDatas->AddNewChild(pString);
			pDatasChild = pDatasChild->next;
		}
	}

	CJSON* pJson2 = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson2 = CJSON_GetObjectItem(pJson2, PkgData_Node_DataList);
	if (pDatasJson2)
	{
		CPkg_DataSubs_SubsSvcDLs* pDatas = new CPkg_DataSubs_SubsSvcDLs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_DataList;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson2->child;
		while (pDatasChild)
		{
			CPkg_DataSubs_SubsSvcDL* pData = new CPkg_DataSubs_SubsSvcDL;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			delete pTempJsonNode;
			pDatas->AddNewChild(pData);
			pDatasChild = pDatasChild->next;
		}
	}
	return 0;
}

long CPkg_DataSubs_SubsSvc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strServiceIdKey, oElement, m_strServiceId);
	xml_SetAttributeValue(pXmlKeys->m_strAllDevKey, oElement, m_strAllDev);
	xml_SetAttributeValue(pXmlKeys->m_strPeriodKey, oElement, m_strPeriod);
	xml_SetAttributeValue(pXmlKeys->m_strSpontKey, oElement, m_strSpont);
	xml_SetAttributeValue(pXmlKeys->m_strAllDataKey, oElement, m_strAllData);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_DataSubs_SubsSvcDevs* pDatas = (CPkg_DataSubs_SubsSvcDevs*)FindByID(PkgData_Node_DeviceList);
	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_DataSubs_SubsSvcDev* pString = (CPkg_DataSubs_SubsSvcDev*)pDatas->GetNext(pos);
		CJSON* pStringJson = CJSON_CreateString(pString->m_strValue.GetString());
		CJSON_AddItemToArray(pDatasJson, pStringJson);
	}
	CJSON_AddItemToObject(pJson, PkgData_Node_DeviceList, pDatasJson);

	DeleteByID(PkgData_Node_DeviceList);

	CJSON* pJson2 = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_DataSubs_SubsSvcDLs* pDatas2 = (CPkg_DataSubs_SubsSvcDLs*)FindByID(PkgData_Node_DataList);
	CJSON* pDatasJson2 = CJSON_CreateArray();
	POS pos2 = pDatas2->GetHeadPosition();
	while (pos2)
	{
		CPkg_DataSubs_SubsSvcDL* pData = (CPkg_DataSubs_SubsSvcDL*)pDatas2->GetNext(pos2);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson2, pDataJson);
	}
	CJSON_AddItemToObject(pJson2, PkgData_Node_DataList, pDatasJson2);

	DeleteByID(PkgData_Node_DataList);

	return 0;
}

long CPkg_DataSubs_SubsSvc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strServiceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strAllDev);
		BinarySerializeCalLen(oBinaryBuffer, m_strPeriod);
		BinarySerializeCalLen(oBinaryBuffer, m_strSpont);
		BinarySerializeCalLen(oBinaryBuffer, m_strAllData);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strServiceId);
		BinarySerializeRead(oBinaryBuffer, m_strAllDev);
		BinarySerializeRead(oBinaryBuffer, m_strPeriod);
		BinarySerializeRead(oBinaryBuffer, m_strSpont);
		BinarySerializeRead(oBinaryBuffer, m_strAllData);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strServiceId);
		BinarySerializeWrite(oBinaryBuffer, m_strAllDev);
		BinarySerializeWrite(oBinaryBuffer, m_strPeriod);
		BinarySerializeWrite(oBinaryBuffer, m_strSpont);
		BinarySerializeWrite(oBinaryBuffer, m_strAllData);
	}
	return 0;
}

void CPkg_DataSubs_SubsSvc::InitAfterRead()
{
}

BOOL CPkg_DataSubs_SubsSvc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSubs_SubsSvc *p = (CPkg_DataSubs_SubsSvc*)pObj;

	if(m_strServiceId != p->m_strServiceId)
	{
		return FALSE;
	}

	if(m_strAllDev != p->m_strAllDev)
	{
		return FALSE;
	}

	if(m_strPeriod != p->m_strPeriod)
	{
		return FALSE;
	}

	if(m_strSpont != p->m_strSpont)
	{
		return FALSE;
	}

	if(m_strAllData != p->m_strAllData)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_DataSubs_SubsSvc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSubs_SubsSvc *p = (CPkg_DataSubs_SubsSvc*)pDest;

	p->m_strServiceId = m_strServiceId;
	p->m_strAllDev = m_strAllDev;
	p->m_strPeriod = m_strPeriod;
	p->m_strSpont = m_strSpont;
	p->m_strAllData = m_strAllData;
	return TRUE;
}

CBaseObject* CPkg_DataSubs_SubsSvc::Clone()
{
	CPkg_DataSubs_SubsSvc *p = new CPkg_DataSubs_SubsSvc();
	Copy(p);
	return p;
}

long CPkg_DataSubs_SubsSvc::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ServiceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("AllDev"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Period"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Spont"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("AllData"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSubs_SubsSvc::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strServiceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strAllDev);
	pListCtrl->SetItemText(lItemIndex, 3, m_strPeriod);
	pListCtrl->SetItemText(lItemIndex, 4, m_strSpont);
	pListCtrl->SetItemText(lItemIndex, 5, m_strAllData);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSubs_SubsSvc::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSubs_SubsSvc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSubs_SubsSvc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_DataSubs_SubsSvc::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strAllDevKey, m_strAllDev);
	pRecordset->GetFieldValue(pXmlKeys->m_strPeriodKey, m_strPeriod);
	pRecordset->GetFieldValue(pXmlKeys->m_strSpontKey, m_strSpont);
	pRecordset->GetFieldValue(pXmlKeys->m_strAllDataKey, m_strAllData);
	return 0;
}

long CPkg_DataSubs_SubsSvc::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strAllDevKey, m_strAllDev);
	pRecordset->SetFieldValue(pXmlKeys->m_strPeriodKey, m_strPeriod);
	pRecordset->SetFieldValue(pXmlKeys->m_strSpontKey, m_strSpont);
	pRecordset->SetFieldValue(pXmlKeys->m_strAllDataKey, m_strAllData);
	return 0;
}

CDvmDataset* CPkg_DataSubs_SubsSvc::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Services;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ServiceId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Spont);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Period);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_AllDev);

	CTcpEdgePkgData::AddNewDatas(pDataset, PkgData_Node_DeviceList);

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_AllData);

	CTcpEdgePkgData::AddNewData(pDataset, CPkg_DataSubs_SubsSvcDLs::ToDataset());

	return pDataset;
}

BOOL CPkg_DataSubs_SubsSvc::NewData(CDvmDatasetGroup* pArray)
{
	if(pArray->m_strID == PkgData_Node_DeviceList)
	{
		return FALSE;
	}
	else if(pArray->m_strID == PkgData_Node_DataList)
	{
		CPkg_DataSubs_SubsSvcDL* pObj = new CPkg_DataSubs_SubsSvcDL;
		AddNewChild(pObj);

		CDvmDataset* pDataset = CPkg_DataSubs_SubsSvcDL::ToDataset();
		pDataset->m_strID = "";
		pDataset->m_dwReserved = (DWORD)pObj;
		pArray->AddNewChild(pDataset);
	}
	return TRUE;
}

