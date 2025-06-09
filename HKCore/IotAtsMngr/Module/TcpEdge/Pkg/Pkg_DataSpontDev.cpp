//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSpontDev.cpp  CPkg_DataSpontDev


#include "stdafx.h"
#include "Pkg_DataSpontDev.h"
#include "Pkg_DataSpontDevSvc.h"
#include "Pkg_DataSpontDevSvcs.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CPkg_DataSpontDev::CPkg_DataSpontDev()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataSpontDev::~CPkg_DataSpontDev()
{
}

BOOL CPkg_DataSpontDev::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】DataSpont：[%1]=>[%2$%3]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】DataSpont：[%1]=>[%2$%3]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_DataSpontDev::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strTransCotKey, oNode, m_strTransCot);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Services);
	if (pDatasJson)
	{
		CPkg_DataSpontDevSvcs* pDatas = new CPkg_DataSpontDevSvcs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Services;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_DataSpontDevSvc* pData = new CPkg_DataSpontDevSvc;

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
		strTemp = QString("【错误】【必需项缺失】DataSpont：[%1]=>[%2$%3] 必需字段array缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Services);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}

	//lmy,20230915修改
	if(m_strTransCot != _T("peroid") && m_strTransCot != _T("spont"))
	//if(m_strTransCot != _T("peroid") || m_strTransCot != _T("spont"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetDataSubsResp：[%1]=>[%2$%3]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_Devices).arg(PkgData_Node_TransCot);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CPkg_DataSpontDev::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strTransCotKey, oElement, m_strTransCot);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_DataSpontDevSvcs* pDatas = (CPkg_DataSpontDevSvcs*)FindByID(PkgData_Node_Services);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_DataSpontDevSvc* pData = (CPkg_DataSpontDevSvc*)pDatas->GetNext(pos);
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

long CPkg_DataSpontDev::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strTransCot);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strTransCot);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strTransCot);
	}
	return 0;
}

void CPkg_DataSpontDev::InitAfterRead()
{
}

BOOL CPkg_DataSpontDev::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSpontDev *p = (CPkg_DataSpontDev*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strTransCot != p->m_strTransCot)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_DataSpontDev::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSpontDev *p = (CPkg_DataSpontDev*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strTransCot = m_strTransCot;
	return TRUE;
}

CBaseObject* CPkg_DataSpontDev::Clone()
{
	CPkg_DataSpontDev *p = new CPkg_DataSpontDev();
	Copy(p);
	return p;
}

long CPkg_DataSpontDev::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("TransCot"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSpontDev::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strTransCot);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSpontDev::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSpontDev::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSpontDev::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_DataSpontDev::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strTransCotKey, m_strTransCot);
	return 0;
}

long CPkg_DataSpontDev::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strTransCotKey, m_strTransCot);
	return 0;
}

CDvmDataset* CPkg_DataSpontDev::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Devices;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DeviceID);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_TransCot);
	CTcpEdgePkgData::AddNewData(pDataset, CPkg_DataSpontDevSvcs::ToDataset());

	return pDataset;
}