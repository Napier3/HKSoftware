//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataMngrFolder.cpp  CDataMngrFolder


#include "stdafx.h"
#include "DataMngrFolder.h"

CDataMngrFolder::CDataMngrFolder()
{
	//初始化属性

	//初始化成员变量
}

CDataMngrFolder::~CDataMngrFolder()
{
}

long CDataMngrFolder::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDataMngrFolder::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDataMngrFolder::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CDataMngrFolder::InitAfterRead()
{
}

BOOL CDataMngrFolder::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDataMngrFolder *p = (CDataMngrFolder*)pObj;

	return TRUE;
}

BOOL CDataMngrFolder::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDataMngrFolder *p = (CDataMngrFolder*)pDest;

	return TRUE;
}

CBaseObject* CDataMngrFolder::Clone()
{
	CDataMngrFolder *p = new CDataMngrFolder();
	Copy(p);
	return p;
}

long CDataMngrFolder::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CDataMngrFolder::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

CExBaseObject* CDataMngrFolder::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCShortDataKey)
	{
		pNew = new CShortData();
	}
	else if (strClassID == pXmlKeys->m_strCDataMngrFolderKey)
	{
		pNew = new CDataMngrFolder();
	}

	return pNew;
}

CExBaseObject* CDataMngrFolder::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DTMCLASSID_CSHORTDATA)
	{
		pNew = new CShortData();
	}
	else if (nClassID == DTMCLASSID_CDATAMNGRFOLDER)
	{
		pNew = new CDataMngrFolder();
	}

	return pNew;
}

void  CDataMngrFolder::AppendValues( CValues *pValues)
{
	CShortData *pData = NULL;
	POS pos = GetHeadPosition();
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pData = (CShortData*)GetNext(pos);
		pValues->AddValue(pData->m_strID, pData->m_strValue);
	}
}

CValues* CDataMngrFolder::GetValues()
{
	CValues *pValues = new CValues();
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)GetNext(pos);
		pValues->AddNew(pData->m_strID, pData->m_strValue);
	}

	return pValues;
}

CShortData* CDataMngrFolder::AddNew2(const CString &strName,const CString &strID, const CString &strUnit, const CString &strDataTypeID
								 , const CString &strValue, LONG nReserved,const CString &strFormat,const CString &strRemark)
{
	CShortData *pData = new CShortData();
	pData->SetParent(this);
	pData->m_strName = strName;
	pData->m_strID = strID;
	pData->m_strUnit = strUnit;
	pData->m_strDataTypeID = strDataTypeID;
	pData->m_strValue = strValue;
	pData->m_strFormat = strFormat;
	pData->m_strRemark = strRemark;
	pData->m_nReserved = nReserved;
	AddTail(pData);
	return pData;
}

void CDataMngrFolder::ResetDatas()
{
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)GetNext(pos);
		pData->ResetData();
	}

}
// 
// BSTR CDataMngrFolder::GetXml()
// {
// 	return CBaseObject::GetXml(CDataMngrXmlRWKeys::g_pXmlKeys);
// }
// 
// void CDataMngrFolder::SetXml(BSTR strXml)
// {
// 	CBaseObject::SetXml(strXml,  CDataMngrXmlRWKeys::CDataMngrFolderKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
// }
// 
