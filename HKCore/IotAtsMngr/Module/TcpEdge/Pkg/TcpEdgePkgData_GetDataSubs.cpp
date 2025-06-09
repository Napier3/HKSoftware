//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_GetDataSubs.cpp  CTcpEdgePkgData_GetDataSubs


#include "stdafx.h"
#include "TcpEdgePkgData_GetDataSubs.h"
#include "Pkg_GetDataSubs_Sub.h"
#include "Pkg_GetDataSubs_Subs.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CTcpEdgePkgData_GetDataSubs::CTcpEdgePkgData_GetDataSubs()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_GetDataSubs::~CTcpEdgePkgData_GetDataSubs()
{
}

long CTcpEdgePkgData_GetDataSubs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Subs);
	if (pDatasJson)
	{
		CPkg_GetDataSubs_Subs* pDatas = new CPkg_GetDataSubs_Subs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Subs;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_GetDataSubs_Sub* pData = new CPkg_GetDataSubs_Sub;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			delete pTempJsonNode;
			pDatas->AddNewChild(pData);
			pDatasChild = pDatasChild->next;
		}
	}
	return 0;
}

long CTcpEdgePkgData_GetDataSubs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_GetDataSubs_Subs* pDatas = (CPkg_GetDataSubs_Subs*)FindByID(PkgData_Node_Subs);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_GetDataSubs_Sub* pData = (CPkg_GetDataSubs_Sub*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_Subs, pDatasJson);

	DeleteByID(PkgData_Node_Subs);
	return 0;
}

long CTcpEdgePkgData_GetDataSubs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgData_GetDataSubs::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_GetDataSubs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_GetDataSubs *p = (CTcpEdgePkgData_GetDataSubs*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_GetDataSubs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_GetDataSubs *p = (CTcpEdgePkgData_GetDataSubs*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_GetDataSubs::Clone()
{
	CTcpEdgePkgData_GetDataSubs *p = new CTcpEdgePkgData_GetDataSubs();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_GetDataSubs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_GetDataSubs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_GetDataSubs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_GetDataSubs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_GetDataSubs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDataset* CTcpEdgePkgData_GetDataSubs::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, CPkg_GetDataSubs_Subs::ToDataset());

	return pDataset;
}

BOOL CTcpEdgePkgData_GetDataSubs::NewData(CDvmDatasetGroup* pArray)
{
	CPkg_GetDataSubs_Sub* pObj = new CPkg_GetDataSubs_Sub;
	AddNewChild(pObj);

	CDvmDataset* pDataset = CPkg_GetDataSubs_Sub::ToDataset();
	pDataset->m_strID = "";
	pDataset->m_dwReserved = (DWORD)pObj;
	pArray->AddNewChild(pDataset);

	return TRUE;
}
