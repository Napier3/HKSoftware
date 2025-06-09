//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_GetHisDataResp_DevSvcDLs.cpp  CPkg_GetHisDataResp_DevSvcDLs


#include "stdafx.h"
#include "Pkg_GetHisDataResp_DevSvcDLs.h"

CPkg_GetHisDataResp_DevSvcDLs::CPkg_GetHisDataResp_DevSvcDLs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_GetHisDataResp_DevSvcDLs::~CPkg_GetHisDataResp_DevSvcDLs()
{
}

long CPkg_GetHisDataResp_DevSvcDLs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetHisDataResp_DevSvcDLs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetHisDataResp_DevSvcDLs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_GetHisDataResp_DevSvcDLs::InitAfterRead()
{
}

BOOL CPkg_GetHisDataResp_DevSvcDLs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetHisDataResp_DevSvcDLs *p = (CPkg_GetHisDataResp_DevSvcDLs*)pObj;

	return TRUE;
}

BOOL CPkg_GetHisDataResp_DevSvcDLs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetHisDataResp_DevSvcDLs *p = (CPkg_GetHisDataResp_DevSvcDLs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_GetHisDataResp_DevSvcDLs::Clone()
{
	CPkg_GetHisDataResp_DevSvcDLs *p = new CPkg_GetHisDataResp_DevSvcDLs();
	Copy(p);
	return p;
}

long CPkg_GetHisDataResp_DevSvcDLs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetHisDataResp_DevSvcDLs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetHisDataResp_DevSvcDLs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetHisDataResp_DevSvcDLs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetHisDataResp_DevSvcDLs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
