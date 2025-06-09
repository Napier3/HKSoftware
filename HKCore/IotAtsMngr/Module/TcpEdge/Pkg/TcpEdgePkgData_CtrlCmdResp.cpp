//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_CtrlCmdResp.cpp  CTcpEdgePkgData_CtrlCmdResp


#include "stdafx.h"
#include "TcpEdgePkgData_CtrlCmdResp.h"

CTcpEdgePkgData_CtrlCmdResp::CTcpEdgePkgData_CtrlCmdResp()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_Note;
	m_arrayNotMust[1] = PkgData_Node_ErrorCode;
}

CTcpEdgePkgData_CtrlCmdResp::~CTcpEdgePkgData_CtrlCmdResp()
{
}


BOOL CTcpEdgePkgData_CtrlCmdResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString("【错误】【必需项缺失】CtrlCmdResp：[%1]=>[%2]必需字段缺失;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】CtrlCmdResp：[%s]=>[%s]字段类型错误;\n").arg(strID).arg(strAttr);
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

	return bRet;
}
long CTcpEdgePkgData_CtrlCmdResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strDataReferKey, oNode, m_strDataRefer);
	xml_GetAttibuteValue(pXmlKeys->m_strCtrlTypeKey, oNode, m_strCtrlType);
	xml_GetAttibuteValue(pXmlKeys->m_strCtrlValKey, oNode, m_strCtrlVal);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorCodeKey, oNode, m_strErrorCode);
	xml_GetAttibuteValue(pXmlKeys->m_strNoteKey, oNode, m_strNote);
	return 0;
}

long CTcpEdgePkgData_CtrlCmdResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strDataReferKey, oElement, m_strDataRefer);
	xml_SetAttributeValue(pXmlKeys->m_strCtrlTypeKey, oElement, m_strCtrlType);
	xml_SetAttributeValue(pXmlKeys->m_strCtrlValKey, oElement, m_strCtrlVal);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	xml_SetAttributeValue(pXmlKeys->m_strErrorCodeKey, oElement, m_strErrorCode);
	xml_SetAttributeValue(pXmlKeys->m_strNoteKey, oElement, m_strNote);
	return 0;
}

long CTcpEdgePkgData_CtrlCmdResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataRefer);
		BinarySerializeCalLen(oBinaryBuffer, m_strCtrlType);
		BinarySerializeCalLen(oBinaryBuffer, m_strCtrlVal);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrorCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strDataRefer);
		BinarySerializeRead(oBinaryBuffer, m_strCtrlType);
		BinarySerializeRead(oBinaryBuffer, m_strCtrlVal);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
		BinarySerializeRead(oBinaryBuffer, m_strErrorCode);
		BinarySerializeRead(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strDataRefer);
		BinarySerializeWrite(oBinaryBuffer, m_strCtrlType);
		BinarySerializeWrite(oBinaryBuffer, m_strCtrlVal);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strErrorCode);
		BinarySerializeWrite(oBinaryBuffer, m_strNote);
	}
	return 0;
}

void CTcpEdgePkgData_CtrlCmdResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_CtrlCmdResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_CtrlCmdResp *p = (CTcpEdgePkgData_CtrlCmdResp*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strDataRefer != p->m_strDataRefer)
	{
		return FALSE;
	}

	if(m_strCtrlType != p->m_strCtrlType)
	{
		return FALSE;
	}

	if(m_strCtrlVal != p->m_strCtrlVal)
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

	if(m_strNote != p->m_strNote)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_CtrlCmdResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_CtrlCmdResp *p = (CTcpEdgePkgData_CtrlCmdResp*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strDataRefer = m_strDataRefer;
	p->m_strCtrlType = m_strCtrlType;
	p->m_strCtrlVal = m_strCtrlVal;
	p->m_strStatus = m_strStatus;
	p->m_strErrorCode = m_strErrorCode;
	p->m_strNote = m_strNote;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_CtrlCmdResp::Clone()
{
	CTcpEdgePkgData_CtrlCmdResp *p = new CTcpEdgePkgData_CtrlCmdResp();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_CtrlCmdResp::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("DataRefer"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("CtrlType"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("CtrlVal"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("Status"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->InsertColumn(6, _T("ErrorCode"));
	pListCtrl->SetColumnWidth(6, 80);
	pListCtrl->InsertColumn(7, _T("Note"));
	pListCtrl->SetColumnWidth(7, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_CtrlCmdResp::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strDataRefer);
	pListCtrl->SetItemText(lItemIndex, 3, m_strCtrlType);
	pListCtrl->SetItemText(lItemIndex, 4, m_strCtrlVal);
	pListCtrl->SetItemText(lItemIndex, 5, m_strStatus);
	pListCtrl->SetItemText(lItemIndex, 6, m_strErrorCode);
	pListCtrl->SetItemText(lItemIndex, 7, m_strNote);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_CtrlCmdResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_CtrlCmdResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_CtrlCmdResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_CtrlCmdResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->GetFieldValue(pXmlKeys->m_strCtrlTypeKey, m_strCtrlType);
	pRecordset->GetFieldValue(pXmlKeys->m_strCtrlValKey, m_strCtrlVal);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

long CTcpEdgePkgData_CtrlCmdResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->SetFieldValue(pXmlKeys->m_strCtrlTypeKey, m_strCtrlType);
	pRecordset->SetFieldValue(pXmlKeys->m_strCtrlValKey, m_strCtrlVal);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

