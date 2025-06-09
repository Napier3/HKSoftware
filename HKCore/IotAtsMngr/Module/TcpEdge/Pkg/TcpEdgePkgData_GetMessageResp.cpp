//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_GetMessageResp.cpp  CTcpEdgePkgData_GetMessageResp


#include "stdafx.h"
#include "TcpEdgePkgData_GetMessageResp.h"
#include "Pkg_GetMessageResp_File.h"
#include "Pkg_GetMessageResp_Files.h"
#include "..\..\..\Module\xml\JSON\CJSON.h"
#include "..\..\..\Module\xml\JsonRW.h"
#include "TcpEdgePkgGlobal.h"

CTcpEdgePkgData_GetMessageResp::CTcpEdgePkgData_GetMessageResp()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_GetMessageResp::~CTcpEdgePkgData_GetMessageResp()
{
}


BOOL CTcpEdgePkgData_GetMessageResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString("【错误】【必需项缺失】GetMessageResp：[%1]=>[%2]必需字段缺失;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】GetMessageResp：[%1]=>[%2]字段类型错误;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_GetMessageResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContinueKey, oNode, m_strContinue);

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	CJSON* pDatasJson = CJSON_GetObjectItem(pJson, PkgData_Node_FileList);
	if (pDatasJson)
	{
		CPkg_GetMessageResp_Files* pDatas = new CPkg_GetMessageResp_Files;
		pDatas->m_strID = pDatas->m_strName = PkgData_Node_FileList;
		AddNewChild(pDatas);
		CJSON* pDatasChild = pDatasJson->child;
		while (pDatasChild)
		{
			CPkg_GetMessageResp_File* pData = new CPkg_GetMessageResp_File;

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
		strTemp = QString("【错误】【必需项缺失】GetMessageResp：[%1]=>[%2] 必需字段array缺失;\n").arg(strID).arg(PkgData_Node_FileList);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;

	}

	//lmy,20230915修改
	if(m_strContinue != _T("0") && m_strContinue != _T("1"))
	//if(m_strContinue != _T("0") || m_strContinue != _T("1"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetMessageResp：[%1]=>[%2]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_Continue);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CTcpEdgePkgData_GetMessageResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContinueKey, oElement, m_strContinue);

	CJSON* pJson = ((CJsonNode*)&oElement)->m_pJsonNode;
	CPkg_GetMessageResp_Files* pDatas = (CPkg_GetMessageResp_Files*)FindByID(PkgData_Node_FileList);

	CJSON* pDatasJson = CJSON_CreateArray();
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CPkg_GetMessageResp_File* pData = (CPkg_GetMessageResp_File*)pDatas->GetNext(pos);
		CJSON* pDataJson = CJSON_CreateObject();
		CJsonNode* pTempJsonNode = new CJsonNode(pDataJson);
		pData->XmlWriteOwn(oXMLDoc, *(CXmlRWElementBase*)pTempJsonNode, pXmlRWKeys);
		delete pTempJsonNode;

		CJSON_AddItemToArray(pDatasJson, pDataJson);
	}

	CJSON_AddItemToObject(pJson, PkgData_Node_FileList, pDatasJson);

	DeleteByID(PkgData_Node_FileList);
	return 0;
}

long CTcpEdgePkgData_GetMessageResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContinue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContinue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContinue);
	}
	return 0;
}

void CTcpEdgePkgData_GetMessageResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_GetMessageResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_GetMessageResp *p = (CTcpEdgePkgData_GetMessageResp*)pObj;

	if(m_strContinue != p->m_strContinue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_GetMessageResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_GetMessageResp *p = (CTcpEdgePkgData_GetMessageResp*)pDest;

	p->m_strContinue = m_strContinue;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_GetMessageResp::Clone()
{
	CTcpEdgePkgData_GetMessageResp *p = new CTcpEdgePkgData_GetMessageResp();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_GetMessageResp::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Continue"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_GetMessageResp::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strContinue);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_GetMessageResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_GetMessageResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_GetMessageResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_GetMessageResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContinueKey, m_strContinue);
	return 0;
}

long CTcpEdgePkgData_GetMessageResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContinueKey, m_strContinue);
	return 0;
}

