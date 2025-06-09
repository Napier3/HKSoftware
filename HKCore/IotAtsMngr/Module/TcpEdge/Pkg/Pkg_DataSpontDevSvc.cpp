//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSpontDevSvc.cpp  CPkg_DataSpontDevSvc


#include "stdafx.h"
#include "Pkg_DataSpontDevSvc.h"
#include "Pkg_DataSpontDevSvcDL.h"
#include "Pkg_DataSpontDevSvcDLs.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CPkg_DataSpontDevSvc::CPkg_DataSpontDevSvc()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataSpontDevSvc::~CPkg_DataSpontDevSvc()
{
}

BOOL CPkg_DataSpontDevSvc::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	if(!strAttrVal.GetLength())
	{
		//值不存在时检查是否必需
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString("【错误】【必需项缺失】DataSpont：[%1]=>[%2$%3$%4]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Services).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】DataSpont：[%1]=>[%2$%3$%4]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Services).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_DataSpontDevSvc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strServiceIdKey, oNode, m_strServiceId);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_DataList);
	if (pDatasJson)
	{
		CPkg_DataSpontDevSvcDLs* pDatas = new CPkg_DataSpontDevSvcDLs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_DataList;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_DataSpontDevSvcDL* pData = new CPkg_DataSpontDevSvcDL;

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
		strTemp = QString("【错误】【必需项缺失】DataSpont：[%1]=>[%2$%3$%4] 必需字段array缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Services).arg(PkgData_Node_DataList);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}

	//lmy,20230915修改
	//if(m_strServiceId != _T("analog") || m_strServiceId != _T("discrete") || m_strServiceId != _T("accumulator"))
	if(m_strServiceId != _T("analog") && m_strServiceId != _T("discrete") && m_strServiceId != _T("accumulator"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetDataSubsResp：[%1]=>[%2$%3$%4]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_Devices).arg(PkgData_Node_Services).arg(PkgData_Node_ServiceId);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CPkg_DataSpontDevSvc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strServiceIdKey, oElement, m_strServiceId);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_DataSpontDevSvcDLs* pDatas = (CPkg_DataSpontDevSvcDLs*)FindByID(PkgData_Node_DataList);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_DataSpontDevSvcDL* pData = (CPkg_DataSpontDevSvcDL*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_DataList, pDatasJson);

	DeleteByID(PkgData_Node_DataList);
	return 0;
}

long CPkg_DataSpontDevSvc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strServiceId);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strServiceId);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strServiceId);
	}
	return 0;
}

void CPkg_DataSpontDevSvc::InitAfterRead()
{
}

BOOL CPkg_DataSpontDevSvc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSpontDevSvc *p = (CPkg_DataSpontDevSvc*)pObj;

	if(m_strServiceId != p->m_strServiceId)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_DataSpontDevSvc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSpontDevSvc *p = (CPkg_DataSpontDevSvc*)pDest;

	p->m_strServiceId = m_strServiceId;
	return TRUE;
}

CBaseObject* CPkg_DataSpontDevSvc::Clone()
{
	CPkg_DataSpontDevSvc *p = new CPkg_DataSpontDevSvc();
	Copy(p);
	return p;
}

long CPkg_DataSpontDevSvc::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ServiceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSpontDevSvc::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strServiceId);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSpontDevSvc::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSpontDevSvc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSpontDevSvc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_DataSpontDevSvc::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	return 0;
}

long CPkg_DataSpontDevSvc::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	return 0;
}

CDvmDataset* CPkg_DataSpontDevSvc::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Services;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ServiceId);
	CTcpEdgePkgData::AddNewDatas(pDataset, CPkg_DataSpontDevSvcDLs::ToDataset(), PkgData_Node_DataList);

	return pDataset;
}
