//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ParaSet_ParaLists.cpp  CPkg_ParaSet_ParaLists


#include "stdafx.h"
#include "Pkg_ParaSet_ParaLists.h"

CPkg_ParaSet_ParaLists::CPkg_ParaSet_ParaLists()
{
	//初始化属性

	//初始化成员变量
}

CPkg_ParaSet_ParaLists::~CPkg_ParaSet_ParaLists()
{
}

long CPkg_ParaSet_ParaLists::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ParaSet_ParaLists::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ParaSet_ParaLists::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_ParaSet_ParaLists::InitAfterRead()
{
}

BOOL CPkg_ParaSet_ParaLists::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ParaSet_ParaLists *p = (CPkg_ParaSet_ParaLists*)pObj;

	return TRUE;
}

BOOL CPkg_ParaSet_ParaLists::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ParaSet_ParaLists *p = (CPkg_ParaSet_ParaLists*)pDest;

	return TRUE;
}

CBaseObject* CPkg_ParaSet_ParaLists::Clone()
{
	CPkg_ParaSet_ParaLists *p = new CPkg_ParaSet_ParaLists();
	Copy(p);
	return p;
}

long CPkg_ParaSet_ParaLists::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_ParaSet_ParaLists::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_ParaSet_ParaLists::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ParaSet_ParaLists::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ParaSet_ParaLists::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
