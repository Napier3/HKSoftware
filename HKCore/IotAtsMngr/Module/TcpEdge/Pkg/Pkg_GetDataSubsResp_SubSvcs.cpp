//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_GetDataSubsResp_SubSvcs.cpp  CPkg_GetDataSubsResp_SubSvcs


#include "stdafx.h"
#include "Pkg_GetDataSubsResp_SubSvcs.h"

CPkg_GetDataSubsResp_SubSvcs::CPkg_GetDataSubsResp_SubSvcs()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPkg_GetDataSubsResp_SubSvcs::~CPkg_GetDataSubsResp_SubSvcs()
{
}

long CPkg_GetDataSubsResp_SubSvcs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetDataSubsResp_SubSvcs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_GetDataSubsResp_SubSvcs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_GetDataSubsResp_SubSvcs::InitAfterRead()
{
}

BOOL CPkg_GetDataSubsResp_SubSvcs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_GetDataSubsResp_SubSvcs *p = (CPkg_GetDataSubsResp_SubSvcs*)pObj;

	return TRUE;
}

BOOL CPkg_GetDataSubsResp_SubSvcs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_GetDataSubsResp_SubSvcs *p = (CPkg_GetDataSubsResp_SubSvcs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_GetDataSubsResp_SubSvcs::Clone()
{
	CPkg_GetDataSubsResp_SubSvcs *p = new CPkg_GetDataSubsResp_SubSvcs();
	Copy(p);
	return p;
}

long CPkg_GetDataSubsResp_SubSvcs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("���"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_GetDataSubsResp_SubSvcs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_GetDataSubsResp_SubSvcs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_GetDataSubsResp_SubSvcs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_GetDataSubsResp_SubSvcs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
