//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ModelDevReadResp_ModDevs.cpp  CPkg_ModelDevReadResp_ModDevs


#include "stdafx.h"
#include "Pkg_ModelDevReadResp_ModDevs.h"

CPkg_ModelDevReadResp_ModDevs::CPkg_ModelDevReadResp_ModDevs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_ModelDevReadResp_ModDevs::~CPkg_ModelDevReadResp_ModDevs()
{
}

long CPkg_ModelDevReadResp_ModDevs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ModelDevReadResp_ModDevs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ModelDevReadResp_ModDevs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_ModelDevReadResp_ModDevs::InitAfterRead()
{
}

BOOL CPkg_ModelDevReadResp_ModDevs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ModelDevReadResp_ModDevs *p = (CPkg_ModelDevReadResp_ModDevs*)pObj;

	return TRUE;
}

BOOL CPkg_ModelDevReadResp_ModDevs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ModelDevReadResp_ModDevs *p = (CPkg_ModelDevReadResp_ModDevs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_ModelDevReadResp_ModDevs::Clone()
{
	CPkg_ModelDevReadResp_ModDevs *p = new CPkg_ModelDevReadResp_ModDevs();
	Copy(p);
	return p;
}

long CPkg_ModelDevReadResp_ModDevs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_ModelDevReadResp_ModDevs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_ModelDevReadResp_ModDevs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ModelDevReadResp_ModDevs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ModelDevReadResp_ModDevs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
