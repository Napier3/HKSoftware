//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpCfgOptrBatch.cpp  CPpCfgOptrBatch


#include "stdafx.h"
#include "PpCfgOptrBatch.h"

CPpCfgOptrBatch::CPpCfgOptrBatch()
{
	//初始化属性

	//初始化成员变量
}

CPpCfgOptrBatch::~CPpCfgOptrBatch()
{
}

long CPpCfgOptrBatch::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpCfgOptrBatch::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpCfgOptrBatch::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CPpCfgOptrBatch::InitAfterRead()
{
}

BOOL CPpCfgOptrBatch::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPpCfgOptrBatch *p = (CPpCfgOptrBatch*)pObj;

	return TRUE;
}

BOOL CPpCfgOptrBatch::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPpCfgOptrBatch *p = (CPpCfgOptrBatch*)pDest;

	return TRUE;
}

CBaseObject* CPpCfgOptrBatch::Clone()
{
	CPpCfgOptrBatch *p = new CPpCfgOptrBatch();
	Copy(p);
	return p;
}

long CPpCfgOptrBatch::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPpCfgOptrBatch::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
    pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CPpCfgOptrBatch::CanPaste(UINT nClassID)
{
	if (nClassID == POCLASSID_CPPCFGOPTRBATCHVAR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpCfgOptrBatch::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpCfgOptrBatchVarKey)
	{
		pNew = new CPpCfgOptrBatchVar();
	}

	return pNew;
}

CExBaseObject* CPpCfgOptrBatch::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == POCLASSID_CPPCFGOPTRBATCHVAR)
	{
		pNew = new CPpCfgOptrBatchVar();
	}

	return pNew;
}
