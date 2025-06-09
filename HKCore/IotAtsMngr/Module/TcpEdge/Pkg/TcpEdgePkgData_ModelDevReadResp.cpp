//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_ModelDevReadResp.cpp  CTcpEdgePkgData_ModelDevReadResp


#include "stdafx.h"
#include "TcpEdgePkgData_ModelDevReadResp.h"
#include "Pkg_ModelDevReadResp_Mod.h"
#include "Pkg_ModelDevReadResp_Mods.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CTcpEdgePkgData_ModelDevReadResp::CTcpEdgePkgData_ModelDevReadResp()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_ModelDevReadResp::~CTcpEdgePkgData_ModelDevReadResp()
{
}

long CTcpEdgePkgData_ModelDevReadResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Models);
	if (pDatasJson)
	{
		CPkg_ModelDevReadResp_Mods* pDatas = new CPkg_ModelDevReadResp_Mods;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Models;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_ModelDevReadResp_Mod* pData = new CPkg_ModelDevReadResp_Mod;

			CJsonNode* pTempJsonNode = new CJsonNode(pDatasChild);
			pData->m_strErrorInfo = m_strErrorInfo;
			pData->m_strNecessityLack = m_strNecessityLack;
			pData->m_strNecessityErr = m_strNecessityErr;
			pData->m_strRangeOut = m_strRangeOut;
			pData->m_strReturnFalse = m_strReturnFalse;
			pData->XmlReadOwn(*(CXmlRWNodeBase*)pTempJsonNode, pXmlRWKeys);
			m_strErrorInfo = pData->m_strErrorInfo;
			m_strNecessityLack = pData->m_strNecessityLack;
			m_strNecessityErr = pData->m_strNecessityErr;
			m_strRangeOut = pData->m_strRangeOut;
			m_strReturnFalse = pData->m_strReturnFalse;

			delete pTempJsonNode;
			pDatas->AddNewChild(pData);
			pDatasChild = pDatasChild->next;
		}
	}
	else
	{
		QString strTemp;
		CString strID(GetXmlElementKey());
		strTemp = QString("【错误】【必需项缺失】ModelDevReadResp：[%1]=>[%2] 必需字段array缺失;\n").arg(strID).arg(PkgData_Node_Models);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_ModelDevReadResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_ModelDevReadResp_Mods* pDatas = (CPkg_ModelDevReadResp_Mods*)FindByID(PkgData_Node_Models);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_ModelDevReadResp_Mod* pData = (CPkg_ModelDevReadResp_Mod*)pDatas->GetNext(pos);
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

long CTcpEdgePkgData_ModelDevReadResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgData_ModelDevReadResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_ModelDevReadResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ModelDevReadResp *p = (CTcpEdgePkgData_ModelDevReadResp*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_ModelDevReadResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ModelDevReadResp *p = (CTcpEdgePkgData_ModelDevReadResp*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ModelDevReadResp::Clone()
{
	CTcpEdgePkgData_ModelDevReadResp *p = new CTcpEdgePkgData_ModelDevReadResp();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_ModelDevReadResp::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_ModelDevReadResp::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_ModelDevReadResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ModelDevReadResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ModelDevReadResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
