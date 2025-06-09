//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DLT860checks.cpp  DLT860checks


#include "stdafx.h"
#include "DLT860checks.h"

DLT860checks::DLT860checks()
{
	//初始化属性

	//初始化成员变量
}

DLT860checks::~DLT860checks()
{
}

long DLT860checks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long DLT860checks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long DLT860checks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void DLT860checks::InitAfterRead()
{
}

BOOL DLT860checks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	DLT860checks *p = (DLT860checks*)pObj;

	return TRUE;
}

BOOL DLT860checks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	DLT860checks *p = (DLT860checks*)pDest;

	return TRUE;
}

CBaseObject* DLT860checks::Clone()
{
	DLT860checks *p = new DLT860checks();
	Copy(p);
	return p;
}

long DLT860checks::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long DLT860checks::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL DLT860checks::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_MANNUALCHECK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* DLT860checks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strMannualcheckKey)
	{
		pNew = new Mannualcheck();
	}

	return pNew;
}

CExBaseObject* DLT860checks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_MANNUALCHECK)
	{
		pNew = new Mannualcheck();
	}

	return pNew;
}
