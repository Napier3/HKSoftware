//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_GetDataSubsResp_SubSvcDLs.cpp  CPkg_GetDataSubsResp_SubSvcDLs


#include "stdafx.h"
#include "Pkg_GetDataSubsResp_SubSvcDLs.h"

CPkg_GetDataSubsResp_SubSvcDLs::CPkg_GetDataSubsResp_SubSvcDLs()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPkg_GetDataSubsResp_SubSvcDLs::~CPkg_GetDataSubsResp_SubSvcDLs()
{
}

long CPkg_GetDataSubsResp_SubSvcDLs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetDataSubsResp_SubSvcDLs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetDataSubsResp_SubSvcDLs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_GetDataSubsResp_SubSvcDLs::InitAfterRead()
{
}

BOOL CPkg_GetDataSubsResp_SubSvcDLs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetDataSubsResp_SubSvcDLs *p = (CPkg_GetDataSubsResp_SubSvcDLs*)pObj;

	return TRUE;
}

BOOL CPkg_GetDataSubsResp_SubSvcDLs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetDataSubsResp_SubSvcDLs *p = (CPkg_GetDataSubsResp_SubSvcDLs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_GetDataSubsResp_SubSvcDLs::Clone()
{
	CPkg_GetDataSubsResp_SubSvcDLs *p = new CPkg_GetDataSubsResp_SubSvcDLs();
	Copy(p);
	return p;
}

long CPkg_GetDataSubsResp_SubSvcDLs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("���"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetDataSubsResp_SubSvcDLs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetDataSubsResp_SubSvcDLs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetDataSubsResp_SubSvcDLs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetDataSubsResp_SubSvcDLs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
