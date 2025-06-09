//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_ParaSet.cpp  CTcpEdgePkgData_ParaSet


#include "stdafx.h"
#include "TcpEdgePkgData_ParaSet.h"
#include "Pkg_ParaSet_ParaList.h"
#include "Pkg_ParaSet_ParaLists.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CTcpEdgePkgData_ParaSet::CTcpEdgePkgData_ParaSet()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_ParaSet::~CTcpEdgePkgData_ParaSet()
{
}

long CTcpEdgePkgData_ParaSet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strSetIdKey, oNode, m_strSetId);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, "ParaList");
	if (pDatasJson)
	{
		CPkg_ParaSet_ParaLists* pDatas = new CPkg_ParaSet_ParaLists;
		pDatas->m_strID = pDatas->m_strName = "ParaList";
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_ParaSet_ParaList* pObj = new CPkg_ParaSet_ParaList;
			pObj->m_strID = pDatasChild->child->string;
			pObj->m_strValue = pDatasChild->child->valuestring;
			pDatas->AddNewChild(pObj);
			pDatasChild = pDatasChild->next;
		}
	}
	return 0;
}

long CTcpEdgePkgData_ParaSet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strSetIdKey, oElement, m_strSetId);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_ParaSet_ParaLists* pDatas = (CPkg_ParaSet_ParaLists*)FindByID("ParaList");
	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_ParaSet_ParaList* pString = (CPkg_ParaSet_ParaList*)pDatas->GetNext(pos);
		CJSON* pObj = CJSON_CreateObject();
		CJSON* pStringJson = CJSON_CreateString(pString->m_strValue.GetString());
		CJSON_AddItemToObject(pObj, pString->m_strID.GetString(), pStringJson);
		CJSON_AddItemToArray(pDatasJson, pObj);
	}
	CJSON_AddItemToObject(pJson, "ParaList", pDatasJson);

	DeleteByID("ParaList");
	return 0;
}

long CTcpEdgePkgData_ParaSet::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strSetId);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strSetId);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strSetId);
	}
	return 0;
}

void CTcpEdgePkgData_ParaSet::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_ParaSet::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ParaSet *p = (CTcpEdgePkgData_ParaSet*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strSetId != p->m_strSetId)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_ParaSet::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ParaSet *p = (CTcpEdgePkgData_ParaSet*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strSetId = m_strSetId;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ParaSet::Clone()
{
	CTcpEdgePkgData_ParaSet *p = new CTcpEdgePkgData_ParaSet();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_ParaSet::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("SetId"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_ParaSet::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strSetId);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_ParaSet::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ParaSet::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ParaSet::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_ParaSet::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strSetIdKey, m_strSetId);
	return 0;
}

long CTcpEdgePkgData_ParaSet::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strSetIdKey, m_strSetId);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_ParaSet::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DeviceID);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_SetId);

// 	CDvmDatasetGroup* pDatasetArray = new CDvmDatasetGroup;
// 	pDatasetArray->m_strDataType = PkgData_Type_Array;
// 	pDatasetArray->m_strID = PkgData_Node_ParaList;
// 	pDatasetArray->m_dwItemData = 1;
// 	pDataset->AddNewChild(pDatasetArray);
	CTcpEdgePkgData::AddNewDatas(pDataset, PkgData_Node_ParaList);

	return pDataset;
}