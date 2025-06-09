//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_ModelDevRead.cpp  CTcpEdgePkgData_ModelDevRead


#include "stdafx.h"
#include "TcpEdgePkgData_ModelDevRead.h"
#include "Pkg_ModelDevRead_Mod.h"
#include "Pkg_ModelDevRead_Mods.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CTcpEdgePkgData_ModelDevRead::CTcpEdgePkgData_ModelDevRead()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_ModelDevRead::~CTcpEdgePkgData_ModelDevRead()
{
}

long CTcpEdgePkgData_ModelDevRead::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModelAllKey, oNode, m_strModelAll);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Models);
	if (pDatasJson)
	{
		CPkg_ModelDevRead_Mods* pDatas = new CPkg_ModelDevRead_Mods;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Models;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_ModelDevRead_Mod* pString = new CPkg_ModelDevRead_Mod;
			pString->m_strValue = pDatasChild->valuestring;
			pDatas->AddNewChild(pString);
			pDatasChild = pDatasChild->next;
		}
	}
	return 0;
}

long CTcpEdgePkgData_ModelDevRead::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strModelAllKey, oElement, m_strModelAll);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_ModelDevRead_Mods* pDatas = (CPkg_ModelDevRead_Mods*)FindByID(PkgData_Node_Models);
	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_ModelDevRead_Mod* pString = (CPkg_ModelDevRead_Mod*)pDatas->GetNext(pos);
		CJSON* pStringJson = CJSON_CreateString(pString->m_strValue.GetString());
		CJSON_AddItemToArray(pDatasJson, pStringJson);
	}
	CJSON_AddItemToObject(pJson, PkgData_Node_Models, pDatasJson);

	DeleteByID(PkgData_Node_Models);
	return 0;
}

long CTcpEdgePkgData_ModelDevRead::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strModelAll);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strModelAll);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strModelAll);
	}
	return 0;
}

void CTcpEdgePkgData_ModelDevRead::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_ModelDevRead::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ModelDevRead *p = (CTcpEdgePkgData_ModelDevRead*)pObj;

	if(m_strModelAll != p->m_strModelAll)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_ModelDevRead::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ModelDevRead *p = (CTcpEdgePkgData_ModelDevRead*)pDest;

	p->m_strModelAll = m_strModelAll;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ModelDevRead::Clone()
{
	CTcpEdgePkgData_ModelDevRead *p = new CTcpEdgePkgData_ModelDevRead();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_ModelDevRead::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ModelAll"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_ModelDevRead::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strModelAll);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_ModelDevRead::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ModelDevRead::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ModelDevRead::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_ModelDevRead::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strModelAllKey, m_strModelAll);
	return 0;
}

long CTcpEdgePkgData_ModelDevRead::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strModelAllKey, m_strModelAll);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_ModelDevRead::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ModelAll);
	CTcpEdgePkgData::AddNewDatas(pDataset, PkgData_Node_Models);

	return pDataset;
}