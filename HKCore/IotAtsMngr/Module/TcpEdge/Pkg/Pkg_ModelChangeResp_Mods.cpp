//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ModelChangeResp_Mods.cpp  CPkg_ModelChangeResp_Mods


#include "stdafx.h"
#include "Pkg_ModelChangeResp_Mods.h"

CPkg_ModelChangeResp_Mods::CPkg_ModelChangeResp_Mods()
{
	//初始化属性

	//初始化成员变量
}

CPkg_ModelChangeResp_Mods::~CPkg_ModelChangeResp_Mods()
{
}

long CPkg_ModelChangeResp_Mods::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ModelChangeResp_Mods::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ModelChangeResp_Mods::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_ModelChangeResp_Mods::InitAfterRead()
{
}

BOOL CPkg_ModelChangeResp_Mods::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ModelChangeResp_Mods *p = (CPkg_ModelChangeResp_Mods*)pObj;

	return TRUE;
}

BOOL CPkg_ModelChangeResp_Mods::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ModelChangeResp_Mods *p = (CPkg_ModelChangeResp_Mods*)pDest;

	return TRUE;
}

CBaseObject* CPkg_ModelChangeResp_Mods::Clone()
{
	CPkg_ModelChangeResp_Mods *p = new CPkg_ModelChangeResp_Mods();
	Copy(p);
	return p;
}

long CPkg_ModelChangeResp_Mods::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_ModelChangeResp_Mods::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_ModelChangeResp_Mods::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ModelChangeResp_Mods::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ModelChangeResp_Mods::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
