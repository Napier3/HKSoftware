//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ProjAppchecks.cpp  ProjAppchecks


#include "stdafx.h"
#include "ProjAppchecks.h"

ProjAppchecks::ProjAppchecks()
{
	//初始化属性

	//初始化成员变量
}

ProjAppchecks::~ProjAppchecks()
{
}

long ProjAppchecks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long ProjAppchecks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long ProjAppchecks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void ProjAppchecks::InitAfterRead()
{
}

BOOL ProjAppchecks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	ProjAppchecks *p = (ProjAppchecks*)pObj;

	return TRUE;
}

BOOL ProjAppchecks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	ProjAppchecks *p = (ProjAppchecks*)pDest;

	return TRUE;
}

CBaseObject* ProjAppchecks::Clone()
{
	ProjAppchecks *p = new ProjAppchecks();
	Copy(p);
	return p;
}

long ProjAppchecks::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long ProjAppchecks::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL ProjAppchecks::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_MANNUALCHECK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* ProjAppchecks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strMannualcheckKey)
	{
		pNew = new Mannualcheck();
	}

	return pNew;
}

CExBaseObject* ProjAppchecks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_MANNUALCHECK)
	{
		pNew = new Mannualcheck();
	}

	return pNew;
}
