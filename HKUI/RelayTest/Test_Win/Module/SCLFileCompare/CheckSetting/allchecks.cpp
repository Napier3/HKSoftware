//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//allchecks.cpp  allchecks


#include "stdafx.h"
#include "allchecks.h"

allchecks::allchecks()
{
	//初始化属性

	//初始化成员变量
}

allchecks::~allchecks()
{
}

long allchecks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long allchecks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long allchecks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void allchecks::InitAfterRead()
{
}

BOOL allchecks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	allchecks *p = (allchecks*)pObj;

	return TRUE;
}

BOOL allchecks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	allchecks *p = (allchecks*)pDest;

	return TRUE;
}

CBaseObject* allchecks::Clone()
{
	allchecks *p = new allchecks();
	Copy(p);
	return p;
}

long allchecks::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long allchecks::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL allchecks::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CHECKPATHS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_DLT860CHECKS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_PROJAPPCHECKS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_SCHEMACHECKS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_VIRLOOPCHECKS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* allchecks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSCLCheckSettingMngrXmlRWKeys *pXmlKeys = (CSCLCheckSettingMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strcheckPathsKey)
	{
		pNew = new checkPaths();
	}
	else if (strClassID == pXmlKeys->m_strDLT860checksKey)
	{
		pNew = new DLT860checks();
	}
	else if (strClassID == pXmlKeys->m_strProjAppchecksKey)
	{
		pNew = new ProjAppchecks();
	}
	else if (strClassID == pXmlKeys->m_strSchemachecksKey)
	{
		pNew = new Schemachecks();
	}
	else if (strClassID == pXmlKeys->m_strVirloopchecksKey)
	{
		pNew = new Virloopchecks();
	}

	return pNew;
}

CExBaseObject* allchecks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CHECKPATHS)
	{
		pNew = new checkPaths();
	}
	else if (nClassID == MNGRCLASSID_DLT860CHECKS)
	{
		pNew = new DLT860checks();
	}
	else if (nClassID == MNGRCLASSID_PROJAPPCHECKS)
	{
		pNew = new ProjAppchecks();
	}
	else if (nClassID == MNGRCLASSID_SCHEMACHECKS)
	{
		pNew = new Schemachecks();
	}
	else if (nClassID == MNGRCLASSID_VIRLOOPCHECKS)
	{
		pNew = new Virloopchecks();
	}

	return pNew;
}
