//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DevAdd_Devs.cpp  CPkg_DevAdd_Devs


#include "stdafx.h"
#include "Pkg_DevAdd_Devs.h"

CPkg_DevAdd_Devs::CPkg_DevAdd_Devs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DevAdd_Devs::~CPkg_DevAdd_Devs()
{
}

long CPkg_DevAdd_Devs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DevAdd_Devs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DevAdd_Devs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DevAdd_Devs::InitAfterRead()
{
}

BOOL CPkg_DevAdd_Devs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DevAdd_Devs *p = (CPkg_DevAdd_Devs*)pObj;

	return TRUE;
}

BOOL CPkg_DevAdd_Devs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DevAdd_Devs *p = (CPkg_DevAdd_Devs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DevAdd_Devs::Clone()
{
	CPkg_DevAdd_Devs *p = new CPkg_DevAdd_Devs();
	Copy(p);
	return p;
}

long CPkg_DevAdd_Devs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DevAdd_Devs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DevAdd_Devs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DevAdd_Devs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DevAdd_Devs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
CDvmDatasetGroup *CPkg_DevAdd_Devs::ToDataset()
{
	CDvmDatasetGroup* pDataset = new CDvmDatasetGroup;
	pDataset->m_strID = PkgData_Node_Devices;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;

	//20230920，lmy添加
	pDataset->m_dwReserved = 1;

	return pDataset;
}