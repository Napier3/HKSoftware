//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSubsResp_SubSvc.cpp  CPkg_DataSubsResp_SubSvc


#include "stdafx.h"
#include "Pkg_DataSubsResp_SubSvc.h"
#include "Pkg_DataSubsResp_SubSvcDev.h"
#include "Pkg_DataSubsResp_SubSvcDevs.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CPkg_DataSubsResp_SubSvc::CPkg_DataSubsResp_SubSvc()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_Note;
	m_arrayNotMust[1] = PkgData_Node_ErrorCode;
}

CPkg_DataSubsResp_SubSvc::~CPkg_DataSubsResp_SubSvc()
{
}


BOOL CPkg_DataSubsResp_SubSvc::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString("【错误】【必需项缺失】DataSubsResp：[%1]=>[%2$%3$%4]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】DataSubsResp：[%1]=>[%2$%3$%4]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

// 	if(strAttrName == L"Status")
// 	{
// 		if(strAttrVal == "0")
// 		{
// 			m_arrayNotMust[1] = PkgData_Node_ErrorCode;
// 		}
// 	}

	if(strAttrName == L"ErrorCode")
	{
		if(m_strStatus != _T("0"))
		{
			if(m_strStatus == _T("1"))
			{
				strTemp = QString(_T("【数据订阅服务执行失败】DataSubsResp报文, 错误代码: [%1]; Note: [%2]; \n")).arg(m_strErrorCode).arg(m_strNote);
				m_strErrorInfo += strTemp;
				m_strReturnFalse += strTemp;

			}
			else
			{
				strTemp = QString(_T("【错误】【超过范围】DataSubsResp：[%1]=>[%2$%3$Status]字段超出范围;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services);
				m_strErrorInfo += strTemp;
				m_strRangeOut += strTemp;
			}
		}
	}

	return bRet;
}

long CPkg_DataSubsResp_SubSvc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strServiceIdKey, oNode, m_strServiceId);
	xml_GetAttibuteValue(pXmlKeys->m_strNoteKey, oNode, m_strNote);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorCodeKey, oNode, m_strErrorCode);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_DeviceList);
	if (pDatasJson)
	{
		CPkg_DataSubsResp_SubSvcDevs* pDatas = new CPkg_DataSubsResp_SubSvcDevs;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_DeviceList;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_DataSubsResp_SubSvcDev* pData = new CPkg_DataSubsResp_SubSvcDev;

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
		strTemp = QString("【错误】【必需项缺失】DataSubsResp：[%1]=>[%2$%3$%4] 必需字段array缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_DeviceList);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;

	}
	return 0;
}

long CPkg_DataSubsResp_SubSvc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strServiceIdKey, oElement, m_strServiceId);
	xml_SetAttributeValue(pXmlKeys->m_strNoteKey, oElement, m_strNote);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	xml_SetAttributeValue(pXmlKeys->m_strErrorCodeKey, oElement, m_strErrorCode);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_DataSubsResp_SubSvcDevs* pDatas = (CPkg_DataSubsResp_SubSvcDevs*)FindByID(PkgData_Node_DeviceList);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_DataSubsResp_SubSvcDev* pData = (CPkg_DataSubsResp_SubSvcDev*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_DeviceList, pDatasJson);

	DeleteByID(PkgData_Node_DeviceList);
	return 0;
}

long CPkg_DataSubsResp_SubSvc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strServiceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strNote);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrorCode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strServiceId);
		BinarySerializeRead(oBinaryBuffer, m_strNote);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
		BinarySerializeRead(oBinaryBuffer, m_strErrorCode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strServiceId);
		BinarySerializeWrite(oBinaryBuffer, m_strNote);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strErrorCode);
	}
	return 0;
}

void CPkg_DataSubsResp_SubSvc::InitAfterRead()
{
}

BOOL CPkg_DataSubsResp_SubSvc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSubsResp_SubSvc *p = (CPkg_DataSubsResp_SubSvc*)pObj;

	if(m_strServiceId != p->m_strServiceId)
	{
		return FALSE;
	}

	if(m_strNote != p->m_strNote)
	{
		return FALSE;
	}

	if(m_strStatus != p->m_strStatus)
	{
		return FALSE;
	}

	if(m_strErrorCode != p->m_strErrorCode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_DataSubsResp_SubSvc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSubsResp_SubSvc *p = (CPkg_DataSubsResp_SubSvc*)pDest;

	p->m_strServiceId = m_strServiceId;
	p->m_strNote = m_strNote;
	p->m_strStatus = m_strStatus;
	p->m_strErrorCode = m_strErrorCode;
	return TRUE;
}

CBaseObject* CPkg_DataSubsResp_SubSvc::Clone()
{
	CPkg_DataSubsResp_SubSvc *p = new CPkg_DataSubsResp_SubSvc();
	Copy(p);
	return p;
}

long CPkg_DataSubsResp_SubSvc::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ServiceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Note"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Status"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("ErrorCode"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSubsResp_SubSvc::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strServiceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strNote);
	pListCtrl->SetItemText(lItemIndex, 3, m_strStatus);
	pListCtrl->SetItemText(lItemIndex, 4, m_strErrorCode);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSubsResp_SubSvc::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSubsResp_SubSvc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSubsResp_SubSvc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_DataSubsResp_SubSvc::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	return 0;
}

long CPkg_DataSubsResp_SubSvc::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strServiceIdKey, m_strServiceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	return 0;
}

