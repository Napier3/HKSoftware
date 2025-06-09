//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetDataSubsResp_SubSvcDL.cpp  CPkg_GetDataSubsResp_SubSvcDL


#include "stdafx.h"
#include "Pkg_GetDataSubsResp_SubSvcDL.h"

CPkg_GetDataSubsResp_SubSvcDL::CPkg_GetDataSubsResp_SubSvcDL()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetDataSubsResp_SubSvcDL::~CPkg_GetDataSubsResp_SubSvcDL()
{
}

BOOL CPkg_GetDataSubsResp_SubSvcDL::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString("【错误】【必需项缺失】GetDataSubsResp：[%1]=>[%2$%3$%4$%5]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】GetDataSubsResp：[%1]=>[%2$%3$%4$%5]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_GetDataSubsResp_SubSvcDL::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataReferKey, oNode, m_strDataRefer);
	xml_GetAttibuteValue(pXmlKeys->m_strDZTypeKey, oNode, m_strDZType);
	xml_GetAttibuteValue(pXmlKeys->m_strDZValKey, oNode, m_strDZVal);

	//lmy,20230915修改
	//if(m_strDZType != _T("0") || m_strDZType != _T("1"))
	if(m_strDZType != _T("0") && m_strDZType != _T("1"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetDataSubsResp：[%1]=>[%2$%3$%4$%5]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_Subs).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(PkgData_Node_DZType);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CPkg_GetDataSubsResp_SubSvcDL::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataReferKey, oElement, m_strDataRefer);
	xml_SetAttributeValue(pXmlKeys->m_strDZTypeKey, oElement, m_strDZType);
	xml_SetAttributeValue(pXmlKeys->m_strDZValKey, oElement, m_strDZVal);
	return 0;
}

long CPkg_GetDataSubsResp_SubSvcDL::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataRefer);
		BinarySerializeCalLen(oBinaryBuffer, m_strDZType);
		BinarySerializeCalLen(oBinaryBuffer, m_strDZVal);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataRefer);
		BinarySerializeRead(oBinaryBuffer, m_strDZType);
		BinarySerializeRead(oBinaryBuffer, m_strDZVal);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataRefer);
		BinarySerializeWrite(oBinaryBuffer, m_strDZType);
		BinarySerializeWrite(oBinaryBuffer, m_strDZVal);
	}
	return 0;
}

void CPkg_GetDataSubsResp_SubSvcDL::InitAfterRead()
{
}

BOOL CPkg_GetDataSubsResp_SubSvcDL::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetDataSubsResp_SubSvcDL *p = (CPkg_GetDataSubsResp_SubSvcDL*)pObj;

	if(m_strDataRefer != p->m_strDataRefer)
	{
		return FALSE;
	}

	if(m_strDZType != p->m_strDZType)
	{
		return FALSE;
	}

	if(m_strDZVal != p->m_strDZVal)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetDataSubsResp_SubSvcDL::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetDataSubsResp_SubSvcDL *p = (CPkg_GetDataSubsResp_SubSvcDL*)pDest;

	p->m_strDataRefer = m_strDataRefer;
	p->m_strDZType = m_strDZType;
	p->m_strDZVal = m_strDZVal;
	return TRUE;
}

CBaseObject* CPkg_GetDataSubsResp_SubSvcDL::Clone()
{
	CPkg_GetDataSubsResp_SubSvcDL *p = new CPkg_GetDataSubsResp_SubSvcDL();
	Copy(p);
	return p;
}

long CPkg_GetDataSubsResp_SubSvcDL::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DataRefer"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("DZType"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("DZVal"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetDataSubsResp_SubSvcDL::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDataRefer);
	pListCtrl->SetItemText(lItemIndex, 2, m_strDZType);
	pListCtrl->SetItemText(lItemIndex, 3, m_strDZVal);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetDataSubsResp_SubSvcDL::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetDataSubsResp_SubSvcDL::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetDataSubsResp_SubSvcDL::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetDataSubsResp_SubSvcDL::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->GetFieldValue(pXmlKeys->m_strDZTypeKey, m_strDZType);
	pRecordset->GetFieldValue(pXmlKeys->m_strDZValKey, m_strDZVal);
	return 0;
}

long CPkg_GetDataSubsResp_SubSvcDL::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->SetFieldValue(pXmlKeys->m_strDZTypeKey, m_strDZType);
	pRecordset->SetFieldValue(pXmlKeys->m_strDZValKey, m_strDZVal);
	return 0;
}

