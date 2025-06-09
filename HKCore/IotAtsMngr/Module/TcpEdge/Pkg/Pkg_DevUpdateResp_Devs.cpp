//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DevUpdateResp_Devs.cpp  CPkg_DevUpdateResp_Devs


#include "stdafx.h"
#include "Pkg_DevUpdateResp_Devs.h"

CPkg_DevUpdateResp_Devs::CPkg_DevUpdateResp_Devs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_DevUpdateResp_Devs::~CPkg_DevUpdateResp_Devs()
{
}

long CPkg_DevUpdateResp_Devs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DevUpdateResp_Devs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DevUpdateResp_Devs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DevUpdateResp_Devs::InitAfterRead()
{
}

BOOL CPkg_DevUpdateResp_Devs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DevUpdateResp_Devs *p = (CPkg_DevUpdateResp_Devs*)pObj;

	return TRUE;
}

BOOL CPkg_DevUpdateResp_Devs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DevUpdateResp_Devs *p = (CPkg_DevUpdateResp_Devs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DevUpdateResp_Devs::Clone()
{
	CPkg_DevUpdateResp_Devs *p = new CPkg_DevUpdateResp_Devs();
	Copy(p);
	return p;
}

long CPkg_DevUpdateResp_Devs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DevUpdateResp_Devs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DevUpdateResp_Devs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DevUpdateResp_Devs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DevUpdateResp_Devs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
