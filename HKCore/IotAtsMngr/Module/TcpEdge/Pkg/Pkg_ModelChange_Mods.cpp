//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ModelChange_Mods.cpp  CPkg_ModelChange_Mods


#include "stdafx.h"
#include "Pkg_ModelChange_Mods.h"

CPkg_ModelChange_Mods::CPkg_ModelChange_Mods()
{
	//初始化属性

	//初始化成员变量
}

CPkg_ModelChange_Mods::~CPkg_ModelChange_Mods()
{
}

long CPkg_ModelChange_Mods::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ModelChange_Mods::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ModelChange_Mods::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_ModelChange_Mods::InitAfterRead()
{
}

BOOL CPkg_ModelChange_Mods::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ModelChange_Mods *p = (CPkg_ModelChange_Mods*)pObj;

	return TRUE;
}

BOOL CPkg_ModelChange_Mods::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ModelChange_Mods *p = (CPkg_ModelChange_Mods*)pDest;

	return TRUE;
}

CBaseObject* CPkg_ModelChange_Mods::Clone()
{
	CPkg_ModelChange_Mods *p = new CPkg_ModelChange_Mods();
	Copy(p);
	return p;
}

long CPkg_ModelChange_Mods::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_ModelChange_Mods::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_ModelChange_Mods::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ModelChange_Mods::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ModelChange_Mods::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDatasetGroup *CPkg_ModelChange_Mods::ToDataset()
{
	CDvmDatasetGroup* pDataset = new CDvmDatasetGroup;
	pDataset->m_strID = PkgData_Node_Models;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;

	//20230920，lmy添加
	pDataset->m_dwReserved = 1;

	return pDataset;
}