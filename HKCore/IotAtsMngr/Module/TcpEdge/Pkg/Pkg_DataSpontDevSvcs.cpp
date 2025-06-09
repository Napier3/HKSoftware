//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSpontDevSvcs.cpp  CPkg_DataSpontDevSvcs


#include "stdafx.h"
#include "Pkg_DataSpontDevSvcs.h"

CPkg_DataSpontDevSvcs::CPkg_DataSpontDevSvcs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataSpontDevSvcs::~CPkg_DataSpontDevSvcs()
{
}

long CPkg_DataSpontDevSvcs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSpontDevSvcs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSpontDevSvcs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DataSpontDevSvcs::InitAfterRead()
{
}

BOOL CPkg_DataSpontDevSvcs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSpontDevSvcs *p = (CPkg_DataSpontDevSvcs*)pObj;

	return TRUE;
}

BOOL CPkg_DataSpontDevSvcs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSpontDevSvcs *p = (CPkg_DataSpontDevSvcs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DataSpontDevSvcs::Clone()
{
	CPkg_DataSpontDevSvcs *p = new CPkg_DataSpontDevSvcs();
	Copy(p);
	return p;
}

long CPkg_DataSpontDevSvcs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSpontDevSvcs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSpontDevSvcs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSpontDevSvcs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSpontDevSvcs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDatasetGroup* CPkg_DataSpontDevSvcs::ToDataset()
{
	CDvmDatasetGroup* pDatasetArray = new CDvmDatasetGroup;
	pDatasetArray->m_strDataType = PkgData_Type_Array;
	pDatasetArray->m_strID = PkgData_Node_Services;
	pDatasetArray->m_dwItemData = 1;

	//20230920，lmy添加
	pDatasetArray->m_dwReserved = 1;

	return pDatasetArray;
}