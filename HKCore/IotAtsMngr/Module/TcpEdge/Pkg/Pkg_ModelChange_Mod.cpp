//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ModelChange_Mod.cpp  CPkg_ModelChange_Mod


#include "stdafx.h"
#include "Pkg_ModelChange_Mod.h"

CPkg_ModelChange_Mod::CPkg_ModelChange_Mod()
{
	//初始化属性

	//初始化成员变量
}

CPkg_ModelChange_Mod::~CPkg_ModelChange_Mod()
{
}

BOOL CPkg_ModelChange_Mod::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】ModelChange：[%1]=>[%2$%3]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Models).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】ModelChange：[%1]=>[%2$%3]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Models).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_ModelChange_Mod::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModelNameKey, oNode, m_strModelName);
	xml_GetAttibuteValue(pXmlKeys->m_strModifyTimeKey, oNode, m_strModifyTime);
	xml_GetAttibuteValue(pXmlKeys->m_strFullPathFileNameKey, oNode, m_strFullPathFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strChangeTypeKey, oNode, m_strChangeType);
	xml_GetAttibuteValue(pXmlKeys->m_strFileCrcKey, oNode, m_strFileCrc);

	m_strErrorInfo += CheckTimeFormat(_T("ModelChange"), PkgData_Node_Models, PkgData_Node_ModifyTime, _T(""), _T(""), m_strModifyTime);
	m_strRangeOut += CheckTimeFormat(_T("ModelChange"), PkgData_Node_Models, PkgData_Node_ModifyTime, _T(""), _T(""), m_strModifyTime);

	//lmy,20230918修改
	//if(m_strChangeType == _T("1") || m_strChangeType == _T("2"))
	if(m_strChangeType != _T("1") && m_strChangeType != _T("2"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】ModelChange：[%1]=>[%2$%3]字段超出范围;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_Models).arg(PkgData_Node_ChangeType);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CPkg_ModelChange_Mod::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strModelNameKey, oElement, m_strModelName);
	xml_SetAttributeValue(pXmlKeys->m_strModifyTimeKey, oElement, m_strModifyTime);
	xml_SetAttributeValue(pXmlKeys->m_strFullPathFileNameKey, oElement, m_strFullPathFileName);
	xml_SetAttributeValue(pXmlKeys->m_strChangeTypeKey, oElement, m_strChangeType);
	xml_SetAttributeValue(pXmlKeys->m_strFileCrcKey, oElement, m_strFileCrc);
	return 0;
}

long CPkg_ModelChange_Mod::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strModelName);
		BinarySerializeCalLen(oBinaryBuffer, m_strModifyTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strChangeType);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileCrc);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strModelName);
		BinarySerializeRead(oBinaryBuffer, m_strModifyTime);
		BinarySerializeRead(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeRead(oBinaryBuffer, m_strChangeType);
		BinarySerializeRead(oBinaryBuffer, m_strFileCrc);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strModelName);
		BinarySerializeWrite(oBinaryBuffer, m_strModifyTime);
		BinarySerializeWrite(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strChangeType);
		BinarySerializeWrite(oBinaryBuffer, m_strFileCrc);
	}
	return 0;
}

void CPkg_ModelChange_Mod::InitAfterRead()
{
}

BOOL CPkg_ModelChange_Mod::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ModelChange_Mod *p = (CPkg_ModelChange_Mod*)pObj;

	if(m_strModelName != p->m_strModelName)
	{
		return FALSE;
	}

	if(m_strModifyTime != p->m_strModifyTime)
	{
		return FALSE;
	}

	if(m_strFullPathFileName != p->m_strFullPathFileName)
	{
		return FALSE;
	}

	if(m_strChangeType != p->m_strChangeType)
	{
		return FALSE;
	}

	if(m_strFileCrc != p->m_strFileCrc)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_ModelChange_Mod::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ModelChange_Mod *p = (CPkg_ModelChange_Mod*)pDest;

	p->m_strModelName = m_strModelName;
	p->m_strModifyTime = m_strModifyTime;
	p->m_strFullPathFileName = m_strFullPathFileName;
	p->m_strChangeType = m_strChangeType;
	p->m_strFileCrc = m_strFileCrc;
	return TRUE;
}

CBaseObject* CPkg_ModelChange_Mod::Clone()
{
	CPkg_ModelChange_Mod *p = new CPkg_ModelChange_Mod();
	Copy(p);
	return p;
}

long CPkg_ModelChange_Mod::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ModelName"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ModifyTime"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("FullPathFileName"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("ChangeType"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("FileCrc"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_ModelChange_Mod::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strModelName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strModifyTime);
	pListCtrl->SetItemText(lItemIndex, 3, m_strFullPathFileName);
	pListCtrl->SetItemText(lItemIndex, 4, m_strChangeType);
	pListCtrl->SetItemText(lItemIndex, 5, m_strFileCrc);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_ModelChange_Mod::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ModelChange_Mod::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ModelChange_Mod::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_ModelChange_Mod::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strModelNameKey, m_strModelName);
	pRecordset->GetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strChangeTypeKey, m_strChangeType);
	pRecordset->GetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	return 0;
}

long CPkg_ModelChange_Mod::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strModelNameKey, m_strModelName);
	pRecordset->SetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strChangeTypeKey, m_strChangeType);
	pRecordset->SetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	return 0;
}

CDvmDataset *CPkg_ModelChange_Mod::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Model;
	pDataset->m_strDataType = PkgData_Type_Object;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ModelName);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ModifyTime);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FullPathFileName);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FileCrc);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ChangeType);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ModelName);

	return pDataset;
}

