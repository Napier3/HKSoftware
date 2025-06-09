//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_ParaRead.cpp  CTcpEdgePkgData_ParaRead


#include "stdafx.h"
#include "TcpEdgePkgData_ParaRead.h"
#include "Pkg_ParaReadSvcs.h"
#include "Pkg_ParaReadSvc.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CTcpEdgePkgData_ParaRead::CTcpEdgePkgData_ParaRead()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_ParaRead::~CTcpEdgePkgData_ParaRead()
{
}

long CTcpEdgePkgData_ParaRead::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Services);
	if (pDatasJson)
	{
		CPkg_ParaReadSvcs* pDatas = new CPkg_ParaReadSvcs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Services;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_ParaReadSvc* pData = new CPkg_ParaReadSvc;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			delete pTempJsonNode;
			pDatas->AddNewChild(pData);
			pDatasChild = pDatasChild->next;
		}
	}

	return 0;
}

long CTcpEdgePkgData_ParaRead::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_ParaReadSvcs* pDatas = (CPkg_ParaReadSvcs*)FindByID(PkgData_Node_Services);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_ParaReadSvc* pData = (CPkg_ParaReadSvc*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_Services, pDatasJson);

	DeleteByID(PkgData_Node_Services);
	return 0;
}

long CTcpEdgePkgData_ParaRead::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
	}
	return 0;
}

void CTcpEdgePkgData_ParaRead::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_ParaRead::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ParaRead *p = (CTcpEdgePkgData_ParaRead*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_ParaRead::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ParaRead *p = (CTcpEdgePkgData_ParaRead*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ParaRead::Clone()
{
	CTcpEdgePkgData_ParaRead *p = new CTcpEdgePkgData_ParaRead();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_ParaRead::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_ParaRead::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_ParaRead::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ParaRead::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ParaRead::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_ParaRead::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	return 0;
}

long CTcpEdgePkgData_ParaRead::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_ParaRead::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DeviceID);
	CTcpEdgePkgData::AddNewData(pDataset, CPkg_ParaReadSvcs::ToDataset());

	return pDataset;
}

BOOL CTcpEdgePkgData_ParaRead::NewData(CDvmDatasetGroup* pArray)
{
	CPkg_ParaReadSvc* pObj = new CPkg_ParaReadSvc;
	AddNewChild(pObj);

	CDvmDataset* pDataset = CPkg_ParaReadSvc::ToDataset();
	pDataset->m_strID = "";
	pDataset->m_dwReserved = (DWORD)pObj;
	pArray->AddNewChild(pDataset);

	return TRUE;
}
