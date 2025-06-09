//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetTopFileResp_File.cpp  CPkg_GetTopFileResp_File


#include "stdafx.h"
#include "Pkg_GetTopFileResp_File.h"

CPkg_GetTopFileResp_File::CPkg_GetTopFileResp_File()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetTopFileResp_File::~CPkg_GetTopFileResp_File()
{
}

BOOL CPkg_GetTopFileResp_File::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString("【错误】【必需项缺失】GetHisDataResp：[%1]=>[%2$%3]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_FileList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】GetHisDataResp：[%1]=>[%2$%3]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_FileList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_GetTopFileResp_File::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModifyTimeKey, oNode, m_strModifyTime);
	xml_GetAttibuteValue(pXmlKeys->m_strFullPathFileNameKey, oNode, m_strFullPathFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strFileCrcKey, oNode, m_strFileCrc);

	m_strErrorInfo += CheckTimeFormat(_T("GetTopoFileResp"), PkgData_Node_FileList, PkgData_Node_ModifyTime, 
		_T(""), _T(""), m_strModifyTime);
	m_strRangeOut += CheckTimeFormat(_T("GetTopoFileResp"), PkgData_Node_FileList, PkgData_Node_ModifyTime, 
		_T(""), _T(""), m_strModifyTime);

	return 0;
}

long CPkg_GetTopFileResp_File::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strModifyTimeKey, oElement, m_strModifyTime);
	xml_SetAttributeValue(pXmlKeys->m_strFullPathFileNameKey, oElement, m_strFullPathFileName);
	xml_SetAttributeValue(pXmlKeys->m_strFileCrcKey, oElement, m_strFileCrc);
	return 0;
}

long CPkg_GetTopFileResp_File::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strModifyTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileCrc);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strModifyTime);
		BinarySerializeRead(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeRead(oBinaryBuffer, m_strFileCrc);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strModifyTime);
		BinarySerializeWrite(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strFileCrc);
	}
	return 0;
}

void CPkg_GetTopFileResp_File::InitAfterRead()
{
}

BOOL CPkg_GetTopFileResp_File::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetTopFileResp_File *p = (CPkg_GetTopFileResp_File*)pObj;

	if(m_strModifyTime != p->m_strModifyTime)
	{
		return FALSE;
	}

	if(m_strFullPathFileName != p->m_strFullPathFileName)
	{
		return FALSE;
	}

	if(m_strFileCrc != p->m_strFileCrc)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetTopFileResp_File::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetTopFileResp_File *p = (CPkg_GetTopFileResp_File*)pDest;

	p->m_strModifyTime = m_strModifyTime;
	p->m_strFullPathFileName = m_strFullPathFileName;
	p->m_strFileCrc = m_strFileCrc;
	return TRUE;
}

CBaseObject* CPkg_GetTopFileResp_File::Clone()
{
	CPkg_GetTopFileResp_File *p = new CPkg_GetTopFileResp_File();
	Copy(p);
	return p;
}

long CPkg_GetTopFileResp_File::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ModifyTime"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("FullPathFileName"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("FileCrc"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetTopFileResp_File::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strModifyTime);
	pListCtrl->SetItemText(lItemIndex, 2, m_strFullPathFileName);
	pListCtrl->SetItemText(lItemIndex, 3, m_strFileCrc);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetTopFileResp_File::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetTopFileResp_File::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetTopFileResp_File::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetTopFileResp_File::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	return 0;
}

long CPkg_GetTopFileResp_File::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	return 0;
}

