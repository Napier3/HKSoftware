//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_DevUpdate.cpp  CTcpEdgePkgData_DevUpdate


#include "stdafx.h"
#include "TcpEdgePkgData_DevUpdate.h"
#include "Pkg_DevUpdate_Dev.h"
#include "Pkg_DevUpdate_Devs.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CTcpEdgePkgData_DevUpdate::CTcpEdgePkgData_DevUpdate()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_DevUpdate::~CTcpEdgePkgData_DevUpdate()
{
}

long CTcpEdgePkgData_DevUpdate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Devices);
	if (pDatasJson)
	{
		CPkg_DevUpdate_Devs* pDatas = new CPkg_DevUpdate_Devs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Devices;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_DevUpdate_Dev* pData = new CPkg_DevUpdate_Dev;

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
		strTemp = QString("【错误】【必需项缺失】DevUpdate：[%1]=>[%2] 必需字段array缺失;\n").arg(strID).arg(PkgData_Node_Devices);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}


	return 0;
}

long CTcpEdgePkgData_DevUpdate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_DevUpdate_Devs* pDatas = (CPkg_DevUpdate_Devs*)FindByID(PkgData_Node_Devices);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_DevUpdate_Dev* pData = (CPkg_DevUpdate_Dev*)pDatas->GetNext(pos);
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

long CTcpEdgePkgData_DevUpdate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgData_DevUpdate::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_DevUpdate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DevUpdate *p = (CTcpEdgePkgData_DevUpdate*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkgData_DevUpdate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_DevUpdate *p = (CTcpEdgePkgData_DevUpdate*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DevUpdate::Clone()
{
	CTcpEdgePkgData_DevUpdate *p = new CTcpEdgePkgData_DevUpdate();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_DevUpdate::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_DevUpdate::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_DevUpdate::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DevUpdate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DevUpdate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

//CDvmDataset* CTcpEdgePkgData_DevUpdate::ToDataset()
//{
//	CDvmDataset* pDataset = new CDvmDataset;
//	pDataset->m_strID = PkgData_Node_Data;
//	pDataset->m_strDataType = PkgData_Type_Object;
//
//	CDvmDatasetGroup* pChildDataset = CPkg_DevUpdate_Devs::ToDataset();
//	pChildDataset->m_dwItemData = 1;
//	pDataset->AddNewChild(pChildDataset);
//
//	return pDataset;
//}