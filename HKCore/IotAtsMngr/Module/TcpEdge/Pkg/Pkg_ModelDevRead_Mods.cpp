//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_ModelDevRead_Mods.cpp  CPkg_ModelDevRead_Mods


#include "stdafx.h"
#include "Pkg_ModelDevRead_Mods.h"

CPkg_ModelDevRead_Mods::CPkg_ModelDevRead_Mods()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPkg_ModelDevRead_Mods::~CPkg_ModelDevRead_Mods()
{
}

long CPkg_ModelDevRead_Mods::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ModelDevRead_Mods::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_ModelDevRead_Mods::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_ModelDevRead_Mods::InitAfterRead()
{
}

BOOL CPkg_ModelDevRead_Mods::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ModelDevRead_Mods *p = (CPkg_ModelDevRead_Mods*)pObj;

	return TRUE;
}

BOOL CPkg_ModelDevRead_Mods::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ModelDevRead_Mods *p = (CPkg_ModelDevRead_Mods*)pDest;

	return TRUE;
}

CBaseObject* CPkg_ModelDevRead_Mods::Clone()
{
	CPkg_ModelDevRead_Mods *p = new CPkg_ModelDevRead_Mods();
	Copy(p);
	return p;
}

long CPkg_ModelDevRead_Mods::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("���"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_ModelDevRead_Mods::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_ModelDevRead_Mods::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ModelDevRead_Mods::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ModelDevRead_Mods::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
//CDvmDatasetGroup* CPkg_ModelDevRead_Mods::ToDataSet()
//{
//
//}