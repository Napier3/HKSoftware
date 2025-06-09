//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpCfgOptrsMngr.cpp  CPpCfgOptrsMngr


#include "stdafx.h"
#include "PpCfgOptrsMngr.h"

CPpCfgOptrsMngr::CPpCfgOptrsMngr()
{
	//初始化属性
	m_strName = _T("规约工程操作定义");

	//初始化成员变量
}

CPpCfgOptrsMngr::~CPpCfgOptrsMngr()
{
}

long CPpCfgOptrsMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpCfgOptrsMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpCfgOptrsMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPpCfgOptrsMngr::InitAfterRead()
{
}

BOOL CPpCfgOptrsMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPpCfgOptrsMngr *p = (CPpCfgOptrsMngr*)pObj;

	return TRUE;
}

BOOL CPpCfgOptrsMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPpCfgOptrsMngr *p = (CPpCfgOptrsMngr*)pDest;

	return TRUE;
}

CBaseObject* CPpCfgOptrsMngr::Clone()
{
	CPpCfgOptrsMngr *p = new CPpCfgOptrsMngr();
	Copy(p);
	return p;
}

long CPpCfgOptrsMngr::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPpCfgOptrsMngr::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
    pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CPpCfgOptrsMngr::CanPaste(UINT nClassID)
{
	if (nClassID == POCLASSID_CPPCFGOPTRS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpCfgOptrsMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpCfgOptrsKey)
	{
		pNew = new CPpCfgOptrs();
	}

	return pNew;
}

CExBaseObject* CPpCfgOptrsMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == POCLASSID_CPPCFGOPTRS)
	{
		pNew = new CPpCfgOptrs();
	}

	return pNew;
}


void CPpCfgOptrsMngr::SerializeTrigerScript(long &nScriptIndex, CExBaseList &listTrigerScript, const CString &strID)
{
	CPpCfgOptrs *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CPpCfgOptrs *)GetNext(pos);
		p->SerializeTrigerScript(nScriptIndex, listTrigerScript, strID);
	}
}

