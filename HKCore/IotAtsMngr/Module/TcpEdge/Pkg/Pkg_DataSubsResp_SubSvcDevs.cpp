//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_DataSubsResp_SubSvcDevs.cpp  CPkg_DataSubsResp_SubSvcDevs


#include "stdafx.h"
#include "Pkg_DataSubsResp_SubSvcDevs.h"

CPkg_DataSubsResp_SubSvcDevs::CPkg_DataSubsResp_SubSvcDevs()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPkg_DataSubsResp_SubSvcDevs::~CPkg_DataSubsResp_SubSvcDevs()
{
}

long CPkg_DataSubsResp_SubSvcDevs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSubsResp_SubSvcDevs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSubsResp_SubSvcDevs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DataSubsResp_SubSvcDevs::InitAfterRead()
{
}

BOOL CPkg_DataSubsResp_SubSvcDevs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSubsResp_SubSvcDevs *p = (CPkg_DataSubsResp_SubSvcDevs*)pObj;

	return TRUE;
}

BOOL CPkg_DataSubsResp_SubSvcDevs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSubsResp_SubSvcDevs *p = (CPkg_DataSubsResp_SubSvcDevs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DataSubsResp_SubSvcDevs::Clone()
{
	CPkg_DataSubsResp_SubSvcDevs *p = new CPkg_DataSubsResp_SubSvcDevs();
	Copy(p);
	return p;
}

long CPkg_DataSubsResp_SubSvcDevs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("���"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSubsResp_SubSvcDevs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSubsResp_SubSvcDevs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSubsResp_SubSvcDevs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSubsResp_SubSvcDevs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
