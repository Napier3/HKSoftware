//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DevUpdate_Dev.cpp  CPkg_DevUpdate_Dev


#include "stdafx.h"
#include "Pkg_DevUpdate_Dev.h"

CPkg_DevUpdate_Dev::CPkg_DevUpdate_Dev()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DevUpdate_Dev::~CPkg_DevUpdate_Dev()
{
}

BOOL CPkg_DevUpdate_Dev::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】DevUpdate：[%1]=>[%2$%3]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】DevUpdate：[%1]=>[%2$%3]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_DevUpdate_Dev::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strModelKey, oNode, m_strModel);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);

	//lmy, 20230915, Status只能是online/offline, 为其他值时超出范围
	if(m_strStatus != _T("online") && m_strStatus != _T("offline"))
	//if(m_strStatus == _T("online") || m_strStatus == _T("offline"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】DevUpdate：[%1]=>[%2$%3]字段超出范围;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Status);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CPkg_DevUpdate_Dev::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strModelKey, oElement, m_strModel);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	return 0;
}

long CPkg_DevUpdate_Dev::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strModel);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strModel);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strModel);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
	}
	return 0;
}

void CPkg_DevUpdate_Dev::InitAfterRead()
{
}

BOOL CPkg_DevUpdate_Dev::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DevUpdate_Dev *p = (CPkg_DevUpdate_Dev*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strModel != p->m_strModel)
	{
		return FALSE;
	}

	if(m_strStatus != p->m_strStatus)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_DevUpdate_Dev::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DevUpdate_Dev *p = (CPkg_DevUpdate_Dev*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strModel = m_strModel;
	p->m_strStatus = m_strStatus;
	return TRUE;
}

CBaseObject* CPkg_DevUpdate_Dev::Clone()
{
	CPkg_DevUpdate_Dev *p = new CPkg_DevUpdate_Dev();
	Copy(p);
	return p;
}

long CPkg_DevUpdate_Dev::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Model"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Status"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DevUpdate_Dev::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strModel);
	pListCtrl->SetItemText(lItemIndex, 3, m_strStatus);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DevUpdate_Dev::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DevUpdate_Dev::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DevUpdate_Dev::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

//CDvmDataset* CPkg_DevUpdate_Dev::ToDataset()
//{
//	CDvmDataset* pDataset = new CDvmDataset;
//	pDataset->m_strID = PkgData_Node_Device;
//	pDataset->m_strDataType = PkgData_Type_Object;
//
//	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DeviceID);
//	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Model);
//	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Status);
//
//	return pDataset;
//}