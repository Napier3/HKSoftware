//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_DevUpdate_Devs.cpp  CPkg_DevUpdate_Devs


#include "stdafx.h"
#include "Pkg_DevUpdate_Devs.h"

CPkg_DevUpdate_Devs::CPkg_DevUpdate_Devs()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPkg_DevUpdate_Devs::~CPkg_DevUpdate_Devs()
{
}

long CPkg_DevUpdate_Devs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DevUpdate_Devs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPkg_DevUpdate_Devs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DevUpdate_Devs::InitAfterRead()
{
}

BOOL CPkg_DevUpdate_Devs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DevUpdate_Devs *p = (CPkg_DevUpdate_Devs*)pObj;

	return TRUE;
}

BOOL CPkg_DevUpdate_Devs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DevUpdate_Devs *p = (CPkg_DevUpdate_Devs*)pDest;

	return TRUE;
}

CBaseObject* CPkg_DevUpdate_Devs::Clone()
{
	CPkg_DevUpdate_Devs *p = new CPkg_DevUpdate_Devs();
	Copy(p);
	return p;
}

long CPkg_DevUpdate_Devs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("���"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DevUpdate_Devs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DevUpdate_Devs::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DevUpdate_Devs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DevUpdate_Devs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CDvmDatasetGroup *CPkg_DevUpdate_Devs::ToDataset()
{
	CDvmDatasetGroup* pDataset = new CDvmDatasetGroup;
	pDataset->m_strID = PkgData_Node_Devices;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;

	//20230920��lmy���
	pDataset->m_dwReserved = 1;

	return pDataset;
}