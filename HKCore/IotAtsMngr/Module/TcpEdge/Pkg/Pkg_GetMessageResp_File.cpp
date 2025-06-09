//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetMessageResp_File.cpp  CPkg_GetMessageResp_File


#include "stdafx.h"
#include "Pkg_GetMessageResp_File.h"

CPkg_GetMessageResp_File::CPkg_GetMessageResp_File()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetMessageResp_File::~CPkg_GetMessageResp_File()
{
}

BOOL CPkg_GetMessageResp_File::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString("【错误】【必需项缺失】GetMessageResp：[%1]=>[%2$%3]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_FileList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】GetMessageResp：[%1]=>[%2$%3]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_FileList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_GetMessageResp_File::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strZipTypeKey, oNode, m_strZipType);
	xml_GetAttibuteValue(pXmlKeys->m_strFileTypeKey, oNode, m_strFileType);
	xml_GetAttibuteValue(pXmlKeys->m_strFullPathFileNameKey, oNode, m_strFullPathFileName);

	//lmy, 20230915修改
	//if(m_strZipType != _T("1") || m_strZipType != _T("2") || m_strZipType != _T("3"))
	if(m_strZipType != _T("1") && m_strZipType != _T("2") && m_strZipType != _T("3"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetMessageResp：[%1]=>[%2$%3]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_FileList).arg(PkgData_Node_ZipType);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	//lmy, 20230915修改
	//if(m_strFileType != _T("1") || m_strFileType != _T("2"))
	if(m_strFileType != _T("1") && m_strFileType != _T("2"))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】GetMessageResp：[%1]=>[%2$%3]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_FileList).arg(PkgData_Node_FileType);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}


	return 0;
}

long CPkg_GetMessageResp_File::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strZipTypeKey, oElement, m_strZipType);
	xml_SetAttributeValue(pXmlKeys->m_strFileTypeKey, oElement, m_strFileType);
	xml_SetAttributeValue(pXmlKeys->m_strFullPathFileNameKey, oElement, m_strFullPathFileName);
	return 0;
}

long CPkg_GetMessageResp_File::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strZipType);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileType);
		BinarySerializeCalLen(oBinaryBuffer, m_strFullPathFileName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strZipType);
		BinarySerializeRead(oBinaryBuffer, m_strFileType);
		BinarySerializeRead(oBinaryBuffer, m_strFullPathFileName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strZipType);
		BinarySerializeWrite(oBinaryBuffer, m_strFileType);
		BinarySerializeWrite(oBinaryBuffer, m_strFullPathFileName);
	}
	return 0;
}

void CPkg_GetMessageResp_File::InitAfterRead()
{
}

BOOL CPkg_GetMessageResp_File::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetMessageResp_File *p = (CPkg_GetMessageResp_File*)pObj;

	if(m_strZipType != p->m_strZipType)
	{
		return FALSE;
	}

	if(m_strFileType != p->m_strFileType)
	{
		return FALSE;
	}

	if(m_strFullPathFileName != p->m_strFullPathFileName)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_GetMessageResp_File::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetMessageResp_File *p = (CPkg_GetMessageResp_File*)pDest;

	p->m_strZipType = m_strZipType;
	p->m_strFileType = m_strFileType;
	p->m_strFullPathFileName = m_strFullPathFileName;
	return TRUE;
}

CBaseObject* CPkg_GetMessageResp_File::Clone()
{
	CPkg_GetMessageResp_File *p = new CPkg_GetMessageResp_File();
	Copy(p);
	return p;
}

long CPkg_GetMessageResp_File::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ZipType"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("FileType"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("FullPathFileName"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetMessageResp_File::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strZipType);
	pListCtrl->SetItemText(lItemIndex, 2, m_strFileType);
	pListCtrl->SetItemText(lItemIndex, 3, m_strFullPathFileName);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetMessageResp_File::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetMessageResp_File::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetMessageResp_File::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_GetMessageResp_File::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strZipTypeKey, m_strZipType);
	pRecordset->GetFieldValue(pXmlKeys->m_strFileTypeKey, m_strFileType);
	pRecordset->GetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	return 0;
}

long CPkg_GetMessageResp_File::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strZipTypeKey, m_strZipType);
	pRecordset->SetFieldValue(pXmlKeys->m_strFileTypeKey, m_strFileType);
	pRecordset->SetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	return 0;
}

