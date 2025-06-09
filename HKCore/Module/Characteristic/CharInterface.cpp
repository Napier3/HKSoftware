//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharInterface.cpp  CCharInterface


#include "stdafx.h"
#include "CharInterface.h"

CCharInterface::CCharInterface()
{
	//初始化属性

	//初始化成员变量
}

CCharInterface::~CCharInterface()
{
}

long CCharInterface::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharInterface::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CCharInterface::InitAfterRead()
{
}

BOOL CCharInterface::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharInterface *p = (CCharInterface*)pObj;

	return TRUE;
}

BOOL CCharInterface::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharInterface *p = (CCharInterface*)pDest;

	return TRUE;
}

CBaseObject* CCharInterface::Clone()
{
	CCharInterface *p = new CCharInterface();
	Copy(p);
	return p;
}

CExBaseObject* CCharInterface::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharInterfaceVariableKey)
	{
		pNew = new CCharInterfaceVariable();
	}

	return pNew;
}

CExBaseObject* CCharInterface::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARINTERFACEVARIABLE)
	{
		pNew = new CCharInterfaceVariable();
	}

	return pNew;
}
BOOL CCharInterface::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARINTERFACEVARIABLE)
	{
		return TRUE;
	}

	return FALSE;
}

long CCharInterface::InsertToListCtrl(CListCtrl *pListCtrl)
{
	CString strVariableIndex;
	CCharInterfaceVariable *pObj;
	long lItemIndex = 0;

	pListCtrl->DeleteAllItems();

	POS pos = GetHeadPosition();
	while(pos)
	{
		pObj =(CCharInterfaceVariable *)GetNext(pos);
		strVariableIndex.Format(_T("%d"), lItemIndex+1);
		pListCtrl->InsertItem( lItemIndex,strVariableIndex );
		pListCtrl->SetItemText(lItemIndex, 1, pObj->m_strID);
		pListCtrl->SetItemText(lItemIndex, 2, pObj->m_strName);
		pListCtrl->SetItemText(lItemIndex, 3, pObj->m_strValue);
		pListCtrl->SetItemData(lItemIndex, (DWORD)pObj);  //绑定数据
		lItemIndex ++;
	}
	return lItemIndex;
}


long CCharInterface::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("Num"));
	pListCtrl->SetColumnWidth(0, 58);
	pListCtrl->InsertColumn(1, _T("ID"));
	pListCtrl->SetColumnWidth(1, 58);
	pListCtrl->InsertColumn(2, _T("Name"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Value"));
	pListCtrl->SetColumnWidth(3, 120);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}