//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetDataSubs_Sub.cpp  CPkg_GetDataSubs_Sub


#include "stdafx.h"
#include "Pkg_GetDataSubs_Sub.h"
#include "Pkg_GetDataSubs_SubSvc.h"
#include "Pkg_GetDataSubs_SubSvcs.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CPkg_GetDataSubs_Sub::CPkg_GetDataSubs_Sub()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetDataSubs_Sub::~CPkg_GetDataSubs_Sub()
{
}

long CPkg_GetDataSubs_Sub::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModelKey, oNode, m_strModel);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Services);
	if (pDatasJson)
	{
		CPkg_GetDataSubs_SubSvcs* pDatas = new CPkg_GetDataSubs_SubSvcs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Services;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_GetDataSubs_SubSvc* pData = new CPkg_GetDataSubs_SubSvc;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			delete pTempJsonNode;
			pDatas->AddNewChild(pData);
			pDatasChild = pDatasChild->next;
		}
	}

	return 0;
}

long CPkg_GetDataSubs_Sub::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strModelKey, oElement, m_strModel);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_GetDataSubs_SubSvcs* pDatas = (CPkg_GetDataSubs_SubSvcs*)FindByID(PkgData_Node_Services);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_GetDataSubs_SubSvc* pData = (CPkg_GetDataSubs_SubSvc*)pDatas->GetNext(pos);
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

long CPkg_GetDataSubs_Sub::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strModel);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strModel);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strModel);
	}
	return 0;
}

void CPkg_GetDataSubs_Sub::InitAfterRead()
{
}

BOOL CPkg_GetDataSubs_Sub::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetDataSubs_Sub *p = (CPkg_GetDataSubs_Sub*)pObj;

	if(m_strModel != p->m_strModel)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetDataSubs_Sub::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetDataSubs_Sub *p = (CPkg_GetDataSubs_Sub*)pDest;

	p->m_strModel = m_strModel;
	return TRUE;
}

CBaseObject* CPkg_GetDataSubs_Sub::Clone()
{
	CPkg_GetDataSubs_Sub *p = new CPkg_GetDataSubs_Sub();
	Copy(p);
	return p;
}

long CPkg_GetDataSubs_Sub::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Model"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetDataSubs_Sub::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strModel);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetDataSubs_Sub::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetDataSubs_Sub::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetDataSubs_Sub::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetDataSubs_Sub::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strModelKey, m_strModel);
	return 0;
}

long CPkg_GetDataSubs_Sub::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strModelKey, m_strModel);
	return 0;
}

CDvmDataset* CPkg_GetDataSubs_Sub::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Subs;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Model);
	CTcpEdgePkgData::AddNewData(pDataset, CPkg_GetDataSubs_SubSvcs::ToDataset());

	return pDataset;
}

BOOL CPkg_GetDataSubs_Sub::NewData(CDvmDatasetGroup* pArray)
{
	CPkg_GetDataSubs_SubSvc* pObj = new CPkg_GetDataSubs_SubSvc;
	AddNewChild(pObj);

	CDvmDataset* pDataset = CPkg_GetDataSubs_SubSvc::ToDataset();
	pDataset->m_strID = "";
	pDataset->m_dwReserved = (DWORD)pObj;
	pArray->AddNewChild(pDataset);

	return TRUE;
}
