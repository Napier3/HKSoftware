//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_DataSubs_SubsSvcDevs.cpp  CPkg_DataSubs_SubsSvcDevs


#include "stdafx.h"
#include "Pkg_DataSubs_SubsSvcDevs.h"

CPkg_DataSubs_SubsSvcDevs::CPkg_DataSubs_SubsSvcDevs()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPkg_DataSubs_SubsSvcDevs::~CPkg_DataSubs_SubsSvcDevs()
{
}

long CPkg_DataSubs_SubsSvcDevs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSubs_SubsSvcDevs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DataSubs_SubsSvcDevs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DataSubs_SubsSvcDevs::InitAfterRead()
{
}

BOOL CPkg_DataSubs_SubsSvcDevs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSubs_SubsSvcDevs *p = (CPkg_DataSubs_SubsSvcDevs*)pObj;

	return TRUE;
}

BOOL CPkg_DataSubs_SubsSvcDevs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSubs_SubsSvcDevs *p = (CPkg_DataSubs_SubsSvcDevs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DataSubs_SubsSvcDevs::Clone()
{
	CPkg_DataSubs_SubsSvcDevs *p = new CPkg_DataSubs_SubsSvcDevs();
	Copy(p);
	return p;
}

long CPkg_DataSubs_SubsSvcDevs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("���"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSubs_SubsSvcDevs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSubs_SubsSvcDevs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSubs_SubsSvcDevs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSubs_SubsSvcDevs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

