//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_GetHisData.cpp  CTcpEdgePkgData_GetHisData


#include "stdafx.h"
#include "TcpEdgePkgData_GetHisData.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"
#include "Pkg_GetHisData_Dev.h"
#include "Pkg_GetHisData_Devs.h"

CTcpEdgePkgData_GetHisData::CTcpEdgePkgData_GetHisData()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_GetHisData::~CTcpEdgePkgData_GetHisData()
{
}

long CTcpEdgePkgData_GetHisData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Devices);
	if (pDatasJson)
	{
		CPkg_GetHisData_Devs* pDatas = new CPkg_GetHisData_Devs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Devices;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_GetHisData_Dev* pData = new CPkg_GetHisData_Dev;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			delete pTempJsonNode;
			pDatas->AddNewChild(pData);
			pDatasChild = pDatasChild->next;
		}
	}
	return 0;
}

long CTcpEdgePkgData_GetHisData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_GetHisData_Devs* pDatas = (CPkg_GetHisData_Devs*)FindByID(PkgData_Node_Devices);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_GetHisData_Dev* pData = (CPkg_GetHisData_Dev*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_Devices, pDatasJson);

	DeleteByID(PkgData_Node_Devices);
	return 0;
}

long CTcpEdgePkgData_GetHisData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CTcpEdgePkgData_GetHisData::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_GetHisData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_GetHisData *p = (CTcpEdgePkgData_GetHisData*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_GetHisData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_GetHisData *p = (CTcpEdgePkgData_GetHisData*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_GetHisData::Clone()
{
	CTcpEdgePkgData_GetHisData *p = new CTcpEdgePkgData_GetHisData();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_GetHisData::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_GetHisData::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_GetHisData::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_GetHisData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_GetHisData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDataset* CTcpEdgePkgData_GetHisData::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewDatas(pDataset, CPkg_GetHisData_Devs::ToDataset(),PkgData_Node_Devices);

	return pDataset;
}

BOOL CTcpEdgePkgData_GetHisData::NewData(CDvmDatasetGroup* pArray)
{
	CPkg_GetHisData_Dev* pObj = new CPkg_GetHisData_Dev;
	AddNewChild(pObj);

	CDvmDataset* pDataset = CPkg_GetHisData_Dev::ToDataset();
	pDataset->m_strID = "";
	pDataset->m_dwReserved = (DWORD)pObj;
	pArray->AddNewChild(pDataset);

	return TRUE;
}
