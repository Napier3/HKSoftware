//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSubsResp_SubSvcDev.cpp  CPkg_DataSubsResp_SubSvcDev


#include "stdafx.h"
#include "Pkg_DataSubsResp_SubSvcDev.h"

CPkg_DataSubsResp_SubSvcDev::CPkg_DataSubsResp_SubSvcDev()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_DeviceId;
	m_arrayNotMust[1] = PkgData_Node_Status;
	m_arrayNotMust[2] = PkgData_Node_Note;

}

CPkg_DataSubsResp_SubSvcDev::~CPkg_DataSubsResp_SubSvcDev()
{
}


BOOL CPkg_DataSubsResp_SubSvcDev::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString("【错误】【必需项缺失】DataSubsResp：[%1]=>[%2$%3$%4$%5]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_DeviceList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】DataSubsResp：[%1]=>[%2$%3$%4$%5]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_DeviceList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	if(strAttrName == L"Status")
	{
		if(strAttrVal == "0")
		{
			m_arrayNotMust[3] = PkgData_Node_ErrorCode;
		}
	}

	if(strAttrName == L"Note")
	{
		if(m_strStatus != _T("0"))
		{
			if(m_strStatus == _T("1"))
			{
				strTemp = QString(_T("【数据订阅设备执行失败】DataSubsResp报文, 错误代码: [%1]; Note: [%2]; \n")).arg(m_strErrorCode).arg(m_strNote);
				m_strErrorInfo += strTemp;
				m_strReturnFalse += strTemp;
			}
			else
			{
				strTemp = QString(_T("【错误】【超过范围】DataSubsResp：[%1]=>[%2$%3$%4$Status]字段超出范围, 无法判断执行状态;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_DeviceList);
				m_strErrorInfo += strTemp;
				m_strRangeOut += strTemp;
			}
		}
	}
	return bRet;
}

long CPkg_DataSubsResp_SubSvcDev::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorCodeKey, oNode, m_strErrorCode);
	xml_GetAttibuteValue(pXmlKeys->m_strNoteKey, oNode, m_strNote);
	return 0;
}

long CPkg_DataSubsResp_SubSvcDev::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	xml_SetAttributeValue(pXmlKeys->m_strErrorCodeKey, oElement, m_strErrorCode);
	xml_SetAttributeValue(pXmlKeys->m_strNoteKey, oElement, m_strNote);
	return 0;
}

long CPkg_DataSubsResp_SubSvcDev::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrorCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
		BinarySerializeRead(oBinaryBuffer, m_strErrorCode);
		BinarySerializeRead(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strErrorCode);
		BinarySerializeWrite(oBinaryBuffer, m_strNote);
	}
	return 0;
}

void CPkg_DataSubsResp_SubSvcDev::InitAfterRead()
{
}

BOOL CPkg_DataSubsResp_SubSvcDev::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSubsResp_SubSvcDev *p = (CPkg_DataSubsResp_SubSvcDev*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
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

BOOL CPkg_DataSubsResp_SubSvcDev::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSubsResp_SubSvcDev *p = (CPkg_DataSubsResp_SubSvcDev*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strStatus = m_strStatus;
	p->m_strErrorCode = m_strErrorCode;
	p->m_strNote = m_strNote;
	return TRUE;
}

CBaseObject* CPkg_DataSubsResp_SubSvcDev::Clone()
{
	CPkg_DataSubsResp_SubSvcDev *p = new CPkg_DataSubsResp_SubSvcDev();
	Copy(p);
	return p;
}

long CPkg_DataSubsResp_SubSvcDev::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Status"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("ErrorCode"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Note"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSubsResp_SubSvcDev::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strStatus);
	pListCtrl->SetItemText(lItemIndex, 3, m_strErrorCode);
	pListCtrl->SetItemText(lItemIndex, 4, m_strNote);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSubsResp_SubSvcDev::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSubsResp_SubSvcDev::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSubsResp_SubSvcDev::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_DataSubsResp_SubSvcDev::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

long CPkg_DataSubsResp_SubSvcDev::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

