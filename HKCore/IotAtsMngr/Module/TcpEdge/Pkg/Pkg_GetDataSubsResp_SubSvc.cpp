//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetDataSubsResp_SubSvc.cpp  CPkg_GetDataSubsResp_SubSvc


#include "stdafx.h"
#include "Pkg_GetDataSubsResp_SubSvc.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"
#include "Pkg_GetDataSubsResp_SubSvcDev.h"
#include "Pkg_GetDataSubsResp_SubSvcDevs.h"
#include "Pkg_GetDataSubsResp_SubSvcDL.h"
#include "Pkg_GetDataSubsResp_SubSvcDLs.h"



CPkg_GetDataSubsResp_SubSvc::CPkg_GetDataSubsResp_SubSvc()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetDataSubsResp_SubSvc::~CPkg_GetDataSubsResp_SubSvc()
{
}

BOOL CPkg_GetDataSubsResp_SubSvc::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString("【错误】【必需项缺失】GetDataSubsResp：[%1]=>[%2$%3$%4]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】GetDataSubsResp：[%1]=>[%2$%3$%4]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}
long CPkg_GetDataSubsResp_SubSvc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strServiceIdKey, oNode, m_strServiceId);
	xml_GetAttibuteValue(pXmlKeys->m_strSpontKey, oNode, m_strSpont);
	xml_GetAttibuteValue(pXmlKeys->m_strPeriodKey, oNode, m_strPeriod);
	xml_GetAttibuteValue(pXmlKeys->m_strAllDevKey, oNode, m_strAllDev);
	xml_GetAttibuteValue(pXmlKeys->m_strAllDataKey, oNode, m_strAllData);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_DeviceList);
	if (pDatasJson)
	{
		CPkg_GetDataSubsResp_SubSvcDevs* pDatas = new CPkg_GetDataSubsResp_SubSvcDevs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_DeviceList;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_GetDataSubsResp_SubSvcDev* pString = new CPkg_GetDataSubsResp_SubSvcDev;
			pString->m_strValue = pDatasChild->valuestring;
			pDatas->AddNewChild(pString);
			pDatasChild = pDatasChild->next;
		}
	}
	else
	{
		QString strTemp;
		CString strID(GetXmlElementKey());
		strTemp = QString("【错误】【必需项缺失】GetDataSubsResp：[%1]=>[%2$%3%4] 必需字段array缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_DeviceList);

		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;

	}

	CJSON* pJson2 = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson2 = CJSON_GetObjectItem(pJson2, PkgData_Node_DataList);
	if (pDatasJson2)
	{
		CPkg_GetDataSubsResp_SubSvcDLs* pDatas = new CPkg_GetDataSubsResp_SubSvcDLs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_DataList;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson2->child;
		while (pDatasChild)
		{
			CPkg_GetDataSubsResp_SubSvcDL* pData = new CPkg_GetDataSubsResp_SubSvcDL;

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
		strTemp = QString("【错误】【必需项缺失】GetDataSubsResp：[%1]=>[%2$%3%4] 必需字段array缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_DataList);

		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;

	}

	//lmy,20230915修改
	//if(m_strServiceId != _T("analog") || m_strServiceId != _T("discrete") || m_strServiceId != _T("accumulator"))
	if(m_strServiceId != _T("analog") && m_strServiceId != _T("discrete") && m_strServiceId != _T("accumulator"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetDataSubsResp：[%1]=>[%2$%3$%4]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_ServiceId);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	//lmy,20230915修改
	/*if(m_strSpont != _T("0") || m_strSpont != _T("1"))*/
	if(m_strSpont != _T("0") && m_strSpont != _T("1"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetDataSubsResp：[%1]=>[%2$%3$%4]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_Spont);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	//lmy,20230915修改
	if(m_strAllData != _T("0") && m_strAllData != _T("1"))
	//if(m_strAllData != _T("0") || m_strAllData != _T("1"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetDataSubsResp：[%1]=>[%2$%3$%4]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_AllData);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CPkg_GetDataSubsResp_SubSvc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strServiceIdKey, oElement, m_strServiceId);
	xml_SetAttributeValue(pXmlKeys->m_strSpontKey, oElement, m_strSpont);
	xml_SetAttributeValue(pXmlKeys->m_strPeriodKey, oElement, m_strPeriod);
	xml_SetAttributeValue(pXmlKeys->m_strAllDevKey, oElement, m_strAllDev);
	xml_SetAttributeValue(pXmlKeys->m_strAllDataKey, oElement, m_strAllData);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_GetDataSubsResp_SubSvcDevs* pDatas = (CPkg_GetDataSubsResp_SubSvcDevs*)FindByID(PkgData_Node_DeviceList);
	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_GetDataSubsResp_SubSvcDev* pString = (CPkg_GetDataSubsResp_SubSvcDev*)pDatas->GetNext(pos);
		CJSON* pStringJson = CJSON_CreateString(pString->m_strValue.GetString());
		CJSON_AddItemToArray(pDatasJson, pStringJson);
	}
	CJSON_AddItemToObject(pJson, PkgData_Node_DeviceList, pDatasJson);

	DeleteByID(PkgData_Node_DeviceList);

	CJSON* pJson2 = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_GetDataSubsResp_SubSvcDLs* pDatas2 = (CPkg_GetDataSubsResp_SubSvcDLs*)FindByID(PkgData_Node_DataList);
	CJSON* pDatasJson2 = CJSON_CreateArray();
	POS pos2 = pDatas2->GetHeadPosition();
	while (pos2)
	{
		CPkg_GetDataSubsResp_SubSvcDL* pData = (CPkg_GetDataSubsResp_SubSvcDL*)pDatas2->GetNext(pos2);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}
	CJSON_AddItemToObject(pJson2, PkgData_Node_DataList, pDatasJson2);


	DeleteByID(PkgData_Node_DataList);
	return 0;
}

long CPkg_GetDataSubsResp_SubSvc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strServiceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strSpont);
		BinarySerializeCalLen(oBinaryBuffer, m_strPeriod);
		BinarySerializeCalLen(oBinaryBuffer, m_strAllDev);
		BinarySerializeCalLen(oBinaryBuffer, m_strAllData);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strServiceId);
		BinarySerializeRead(oBinaryBuffer, m_strSpont);
		BinarySerializeRead(oBinaryBuffer, m_strPeriod);
		BinarySerializeRead(oBinaryBuffer, m_strAllDev);
		BinarySerializeRead(oBinaryBuffer, m_strAllData);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strServiceId);
		BinarySerializeWrite(oBinaryBuffer, m_strSpont);
		BinarySerializeWrite(oBinaryBuffer, m_strPeriod);
		BinarySerializeWrite(oBinaryBuffer, m_strAllDev);
		BinarySerializeWrite(oBinaryBuffer, m_strAllData);
	}
	return 0;
}

void CPkg_GetDataSubsResp_SubSvc::InitAfterRead()
{
}

BOOL CPkg_GetDataSubsResp_SubSvc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetDataSubsResp_SubSvc *p = (CPkg_GetDataSubsResp_SubSvc*)pObj;

	if(m_strServiceId != p->m_strServiceId)
	{
		return FALSE;
	}

	if(m_strSpont != p->m_strSpont)
	{
		return FALSE;
	}

	if(m_strPeriod != p->m_strPeriod)
	{
		return FALSE;
	}

	if(m_strAllDev != p->m_strAllDev)
	{
		return FALSE;
	}

	if(m_strAllData != p->m_strAllData)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetDataSubsResp_SubSvc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetDataSubsResp_SubSvc *p = (CPkg_GetDataSubsResp_SubSvc*)pDest;

	p->m_strServiceId = m_strServiceId;
	p->m_strSpont = m_strSpont;
	p->m_strPeriod = m_strPeriod;
	p->m_strAllDev = m_strAllDev;
	p->m_strAllData = m_strAllData;
	return TRUE;
}

CBaseObject* CPkg_GetDataSubsResp_SubSvc::Clone()
{
	CPkg_GetDataSubsResp_SubSvc *p = new CPkg_GetDataSubsResp_SubSvc();
	Copy(p);
	return p;
}

long CPkg_GetDataSubsResp_SubSvc::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ServiceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Spont"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Period"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("AllDev"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("AllData"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetDataSubsResp_SubSvc::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strServiceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strSpont);
	pListCtrl->SetItemText(lItemIndex, 3, m_strPeriod);
	pListCtrl->SetItemText(lItemIndex, 4, m_strAllDev);
	pListCtrl->SetItemText(lItemIndex, 5, m_strAllData);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetDataSubsResp_SubSvc::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetDataSubsResp_SubSvc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetDataSubsResp_SubSvc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetDataSubsResp_SubSvc::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strSpontKey, m_strSpont);
	pRecordset->GetFieldValue(pXmlKeys->m_strPeriodKey, m_strPeriod);
	pRecordset->GetFieldValue(pXmlKeys->m_strAllDevKey, m_strAllDev);
	pRecordset->GetFieldValue(pXmlKeys->m_strAllDataKey, m_strAllData);
	return 0;
}

long CPkg_GetDataSubsResp_SubSvc::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strSpontKey, m_strSpont);
	pRecordset->SetFieldValue(pXmlKeys->m_strPeriodKey, m_strPeriod);
	pRecordset->SetFieldValue(pXmlKeys->m_strAllDevKey, m_strAllDev);
	pRecordset->SetFieldValue(pXmlKeys->m_strAllDataKey, m_strAllData);
	return 0;
}

