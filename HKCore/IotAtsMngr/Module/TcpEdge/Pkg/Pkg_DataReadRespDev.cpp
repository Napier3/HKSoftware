//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataReadRespDev.cpp  CPkg_DataReadRespDev


#include "stdafx.h"
#include "Pkg_DataReadRespDev.h"
#include "Pkg_DataReadRespDevSvc.h"
#include "Pkg_DataReadRespDevSvcs.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CPkg_DataReadRespDev::CPkg_DataReadRespDev()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataReadRespDev::~CPkg_DataReadRespDev()
{
}

BOOL CPkg_DataReadRespDev::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
	//CString strID(GetXmlElementKey());
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
		strTemp = QString("【错误】【必需项缺失】DataReadResp：[%1]=>[%2$%3]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】DataReadResp：[%1]=>[%2$%3]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_DataReadRespDev::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_Services);
	if (pDatasJson)
	{
		CPkg_DataReadRespDevSvcs* pDatas = new CPkg_DataReadRespDevSvcs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_Services;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_DataReadRespDevSvc* pData = new CPkg_DataReadRespDevSvc;

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
		CString strTemp;
		CString strID(GetXmlElementKey());
		strTemp = QString("【错误】【必需项缺失】DataReadResp：[%1]=>[%2$%3] 必需字段array缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Services);

		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;

	}
	return 0;
}

long CPkg_DataReadRespDev::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_DataReadRespDevSvcs* pDatas = (CPkg_DataReadRespDevSvcs*)FindByID(PkgData_Node_Services);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_DataReadRespDevSvc* pData = (CPkg_DataReadRespDevSvc*)pDatas->GetNext(pos);
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

long CPkg_DataReadRespDev::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
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

void CPkg_DataReadRespDev::InitAfterRead()
{
}

BOOL CPkg_DataReadRespDev::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataReadRespDev *p = (CPkg_DataReadRespDev*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_DataReadRespDev::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataReadRespDev *p = (CPkg_DataReadRespDev*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	return TRUE;
}

CBaseObject* CPkg_DataReadRespDev::Clone()
{
	CPkg_DataReadRespDev *p = new CPkg_DataReadRespDev();
	Copy(p);
	return p;
}

long CPkg_DataReadRespDev::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataReadRespDev::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataReadRespDev::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataReadRespDev::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataReadRespDev::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_DataReadRespDev::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	return 0;
}

long CPkg_DataReadRespDev::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	return 0;
}

