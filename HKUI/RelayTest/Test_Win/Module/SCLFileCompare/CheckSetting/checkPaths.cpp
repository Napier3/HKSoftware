//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//checkPaths.cpp  checkPaths


#include "stdafx.h"
#include "checkPaths.h"

checkPaths::checkPaths()
{
	//初始化属性

	//初始化成员变量
}

checkPaths::~checkPaths()
{
}

long checkPaths::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long checkPaths::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long checkPaths::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void checkPaths::InitAfterRead()
{
}

BOOL checkPaths::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	checkPaths *p = (checkPaths*)pObj;

	return TRUE;
}

BOOL checkPaths::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	checkPaths *p = (checkPaths*)pDest;

	return TRUE;
}

CBaseObject* checkPaths::Clone()
{
	checkPaths *p = new checkPaths();
	Copy(p);
	return p;
}

long checkPaths::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long checkPaths::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL checkPaths::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_SINGLEPATH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* checkPaths::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strSinglePathKey)
	{
		pNew = new SinglePath();
	}

	return pNew;
}

CExBaseObject* checkPaths::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_SINGLEPATH)
	{
		pNew = new SinglePath();
	}

	return pNew;
}
