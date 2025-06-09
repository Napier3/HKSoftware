//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpCfgOptrDevice.cpp  CPpCfgOptrDevice


#include "stdafx.h"
#include "PpCfgOptrDevice.h"

CPpCfgOptrDevice::CPpCfgOptrDevice()
{
	//初始化属性

	//初始化成员变量
}

CPpCfgOptrDevice::~CPpCfgOptrDevice()
{
}

long CPpCfgOptrDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpCfgOptrDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpCfgOptrDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CPpCfgOptrDevice::InitAfterRead()
{
}

BOOL CPpCfgOptrDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPpCfgOptrDevice *p = (CPpCfgOptrDevice*)pObj;

	return TRUE;
}

BOOL CPpCfgOptrDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CPpCfgOptrDevice *p = (CPpCfgOptrDevice*)pDest;

	return TRUE;
}

CBaseObject* CPpCfgOptrDevice::Clone()
{
	CPpCfgOptrDevice *p = new CPpCfgOptrDevice();
	Copy(p);
	return p;
}

long CPpCfgOptrDevice::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPpCfgOptrDevice::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
    pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CPpCfgOptrDevice::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPpCfgOptrDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDatasetKey)
	{
		pNew = new CDvmDataset();
	}

	return pNew;
}

CExBaseObject* CPpCfgOptrDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		pNew = new CDvmDataset();
	}

	return pNew;
}
