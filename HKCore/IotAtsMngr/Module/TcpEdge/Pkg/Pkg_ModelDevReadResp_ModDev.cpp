//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ModelDevReadResp_ModDev.cpp  CPkg_ModelDevReadResp_ModDev


#include "stdafx.h"
#include "Pkg_ModelDevReadResp_ModDev.h"

CPkg_ModelDevReadResp_ModDev::CPkg_ModelDevReadResp_ModDev()
{
	//初始化属性

	//初始化成员变量
}

CPkg_ModelDevReadResp_ModDev::~CPkg_ModelDevReadResp_ModDev()
{
}

BOOL CPkg_ModelDevReadResp_ModDev::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】ModelDevReadResp：[%1]=>[%2$%3$%4]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Models).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】ModelDevReadResp：[%1]=>[%2$%3$%4]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Models).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_ModelDevReadResp_ModDev::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceDescKey, oNode, m_strDeviceDesc);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);

	//lmy, 20230915, Status只能是online/offline, 为其他值时超出范围
	if(m_strStatus != _T("online") && m_strStatus != _T("offline"))
	//if(m_strStatus == _T("online") || m_strStatus == _T("offline"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】ModelDevReadResp：[%1]=>[%2$%3$%4]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_Models).arg(PkgData_Node_Devices).arg(PkgData_Node_Status);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CPkg_ModelDevReadResp_ModDev::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceDescKey, oElement, m_strDeviceDesc);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	return 0;
}

long CPkg_ModelDevReadResp_ModDev::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceDesc);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceDesc);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceDesc);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
	}
	return 0;
}

void CPkg_ModelDevReadResp_ModDev::InitAfterRead()
{
}

BOOL CPkg_ModelDevReadResp_ModDev::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ModelDevReadResp_ModDev *p = (CPkg_ModelDevReadResp_ModDev*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strDeviceDesc != p->m_strDeviceDesc)
	{
		return FALSE;
	}

	if(m_strStatus != p->m_strStatus)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_ModelDevReadResp_ModDev::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ModelDevReadResp_ModDev *p = (CPkg_ModelDevReadResp_ModDev*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strDeviceDesc = m_strDeviceDesc;
	p->m_strStatus = m_strStatus;
	return TRUE;
}

CBaseObject* CPkg_ModelDevReadResp_ModDev::Clone()
{
	CPkg_ModelDevReadResp_ModDev *p = new CPkg_ModelDevReadResp_ModDev();
	Copy(p);
	return p;
}

long CPkg_ModelDevReadResp_ModDev::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("DeviceDesc"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Status"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_ModelDevReadResp_ModDev::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strDeviceDesc);
	pListCtrl->SetItemText(lItemIndex, 3, m_strStatus);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_ModelDevReadResp_ModDev::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ModelDevReadResp_ModDev::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ModelDevReadResp_ModDev::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_ModelDevReadResp_ModDev::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceDescKey, m_strDeviceDesc);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	return 0;
}

long CPkg_ModelDevReadResp_ModDev::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceDescKey, m_strDeviceDesc);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	return 0;
}

