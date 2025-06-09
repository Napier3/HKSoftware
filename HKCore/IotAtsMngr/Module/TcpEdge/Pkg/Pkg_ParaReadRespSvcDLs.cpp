//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ParaReadRespSvcDLs.cpp  CPkg_ParaReadRespSvcDLs


#include "stdafx.h"
#include "Pkg_ParaReadRespSvcDLs.h"

CPkg_ParaReadRespSvcDLs::CPkg_ParaReadRespSvcDLs()
{
	//初始化属性

	//初始化成员变量
}

CPkg_ParaReadRespSvcDLs::~CPkg_ParaReadRespSvcDLs()
{
}

long CPkg_ParaReadRespSvcDLs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ParaReadRespSvcDLs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ParaReadRespSvcDLs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_ParaReadRespSvcDLs::InitAfterRead()
{
}

BOOL CPkg_ParaReadRespSvcDLs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ParaReadRespSvcDLs *p = (CPkg_ParaReadRespSvcDLs*)pObj;

	return TRUE;
}

BOOL CPkg_ParaReadRespSvcDLs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ParaReadRespSvcDLs *p = (CPkg_ParaReadRespSvcDLs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_ParaReadRespSvcDLs::Clone()
{
	CPkg_ParaReadRespSvcDLs *p = new CPkg_ParaReadRespSvcDLs();
	Copy(p);
	return p;
}

long CPkg_ParaReadRespSvcDLs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_ParaReadRespSvcDLs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_ParaReadRespSvcDLs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ParaReadRespSvcDLs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ParaReadRespSvcDLs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
