//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_ModelChangeResp.cpp  CTcpEdgePkgData_ModelChangeResp


#include "stdafx.h"
#include "TcpEdgePkgData_ModelChangeResp.h"
#include "Pkg_ModelChangeResp_Mod.h"
#include "Pkg_ModelChangeResp_Mods.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CTcpEdgePkgData_ModelChangeResp::CTcpEdgePkgData_ModelChangeResp()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_ModelChangeResp::~CTcpEdgePkgData_ModelChangeResp()
{
}

long CTcpEdgePkgData_ModelChangeResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Models);
	if (pDatasJson)
	{
		CPkg_ModelChangeResp_Mods* pDatas = new CPkg_ModelChangeResp_Mods;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Models;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_ModelChangeResp_Mod* pData = new CPkg_ModelChangeResp_Mod;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			delete pTempJsonNode;
			pDatas->AddNewChild(pData);
			pDatasChild = pDatasChild->next;
		}
	}
	return 0;
}

long CTcpEdgePkgData_ModelChangeResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_ModelChangeResp_Mods* pDatas = (CPkg_ModelChangeResp_Mods*)FindByID(PkgData_Node_Models);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_ModelChangeResp_Mod* pData = (CPkg_ModelChangeResp_Mod*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_Models, pDatasJson);

	DeleteByID(PkgData_Node_Models);
	return 0;
}

long CTcpEdgePkgData_ModelChangeResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgData_ModelChangeResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_ModelChangeResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ModelChangeResp *p = (CTcpEdgePkgData_ModelChangeResp*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_ModelChangeResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ModelChangeResp *p = (CTcpEdgePkgData_ModelChangeResp*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ModelChangeResp::Clone()
{
	CTcpEdgePkgData_ModelChangeResp *p = new CTcpEdgePkgData_ModelChangeResp();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_ModelChangeResp::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_ModelChangeResp::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_ModelChangeResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ModelChangeResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ModelChangeResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
