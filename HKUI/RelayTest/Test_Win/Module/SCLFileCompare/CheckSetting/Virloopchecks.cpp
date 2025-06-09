//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Virloopchecks.cpp  Virloopchecks


#include "stdafx.h"
#include "Virloopchecks.h"

Virloopchecks::Virloopchecks()
{
	//初始化属性

	//初始化成员变量
}

Virloopchecks::~Virloopchecks()
{
}

long Virloopchecks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long Virloopchecks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long Virloopchecks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void Virloopchecks::InitAfterRead()
{
}

BOOL Virloopchecks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	Virloopchecks *p = (Virloopchecks*)pObj;

	return TRUE;
}

BOOL Virloopchecks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	Virloopchecks *p = (Virloopchecks*)pDest;

	return TRUE;
}

CBaseObject* Virloopchecks::Clone()
{
	Virloopchecks *p = new Virloopchecks();
	Copy(p);
	return p;
}

long Virloopchecks::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long Virloopchecks::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL Virloopchecks::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_MANNUALCHECK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* Virloopchecks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strMannualcheckKey)
	{
		pNew = new Mannualcheck();
	}

	return pNew;
}

CExBaseObject* Virloopchecks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_MANNUALCHECK)
	{
		pNew = new Mannualcheck();
	}

	return pNew;
}
