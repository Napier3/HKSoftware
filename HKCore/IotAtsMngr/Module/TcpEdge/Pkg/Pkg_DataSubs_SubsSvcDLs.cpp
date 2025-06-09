//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSubs_SubsSvcDLs.cpp  CPkg_DataSubs_SubsSvcDLs


#include "stdafx.h"
#include "Pkg_DataSubs_SubsSvcDLs.h"
#include "Pkg_DataSubs_SubsSvcDL.h"

CPkg_DataSubs_SubsSvcDLs::CPkg_DataSubs_SubsSvcDLs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataSubs_SubsSvcDLs::~CPkg_DataSubs_SubsSvcDLs()
{
}

long CPkg_DataSubs_SubsSvcDLs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSubs_SubsSvcDLs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSubs_SubsSvcDLs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
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

void CPkg_DataSubs_SubsSvcDLs::InitAfterRead()
{
}

BOOL CPkg_DataSubs_SubsSvcDLs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSubs_SubsSvcDLs *p = (CPkg_DataSubs_SubsSvcDLs*)pObj;

	return TRUE;
}

BOOL CPkg_DataSubs_SubsSvcDLs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSubs_SubsSvcDLs *p = (CPkg_DataSubs_SubsSvcDLs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DataSubs_SubsSvcDLs::Clone()
{
	CPkg_DataSubs_SubsSvcDLs *p = new CPkg_DataSubs_SubsSvcDLs();
	Copy(p);
	return p;
}

long CPkg_DataSubs_SubsSvcDLs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSubs_SubsSvcDLs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSubs_SubsSvcDLs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSubs_SubsSvcDLs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSubs_SubsSvcDLs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDatasetGroup *CPkg_DataSubs_SubsSvcDLs::ToDataset()
{
	CDvmDatasetGroup* pDataset = new CDvmDatasetGroup;
	pDataset->m_strID = PkgData_Node_DataList;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;

	//20230920，lmy添加
	pDataset->m_dwReserved = 1;

	return pDataset;
}

