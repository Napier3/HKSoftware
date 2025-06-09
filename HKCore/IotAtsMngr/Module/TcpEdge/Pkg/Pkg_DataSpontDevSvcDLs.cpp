//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSpontDevSvcDLs.cpp  CPkg_DataSpontDevSvcDLs


#include "stdafx.h"
#include "Pkg_DataSpontDevSvcDLs.h"

CPkg_DataSpontDevSvcDLs::CPkg_DataSpontDevSvcDLs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DataSpontDevSvcDLs::~CPkg_DataSpontDevSvcDLs()
{
}

long CPkg_DataSpontDevSvcDLs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSpontDevSvcDLs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSpontDevSvcDLs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DataSpontDevSvcDLs::InitAfterRead()
{
}

BOOL CPkg_DataSpontDevSvcDLs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSpontDevSvcDLs *p = (CPkg_DataSpontDevSvcDLs*)pObj;

	return TRUE;
}

BOOL CPkg_DataSpontDevSvcDLs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSpontDevSvcDLs *p = (CPkg_DataSpontDevSvcDLs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DataSpontDevSvcDLs::Clone()
{
	CPkg_DataSpontDevSvcDLs *p = new CPkg_DataSpontDevSvcDLs();
	Copy(p);
	return p;
}

long CPkg_DataSpontDevSvcDLs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSpontDevSvcDLs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSpontDevSvcDLs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSpontDevSvcDLs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSpontDevSvcDLs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDatasetGroup* CPkg_DataSpontDevSvcDLs::ToDataset()
{
	CDvmDatasetGroup* pDatasetArray = new CDvmDatasetGroup;
	pDatasetArray->m_strDataType = PkgData_Type_Array;
	pDatasetArray->m_strID = PkgData_Node_DataList;
	pDatasetArray->m_dwItemData = 1;
	//20230920，lmy添加
	pDatasetArray->m_dwReserved = 1;

	return pDatasetArray;
}
