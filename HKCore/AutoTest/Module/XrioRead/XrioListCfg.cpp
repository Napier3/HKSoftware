//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XrioListCfg.cpp

#include "stdafx.h"
#include "XrioObjectCfg.h"
#include "XrioListCfg.h"

// CXrioEnumList

CXrioEnumList::CXrioEnumList()
{
}

CXrioEnumList::~CXrioEnumList()
{
}

long CXrioEnumList::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	
	return 0;
}

long CXrioEnumList::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	
	return 0;
}

long CXrioEnumList::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXrioEnumList::InitAfterRead()
{
}

BOOL CXrioEnumList::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioEnumList *p = (CXrioEnumList*)pObj;

	return TRUE;
}

BOOL CXrioEnumList::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioEnumList *p = (CXrioEnumList*)pDest;

	return TRUE;
}

CBaseObject* CXrioEnumList::Clone()
{
	CXrioEnumList *p = new CXrioEnumList();
	Copy(p);
	return p;
}

long CXrioEnumList::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CXrioEnumList::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CXrioEnumList::CanPaste(UINT nClassID)
{
	if (nClassID == XRIOCLASSID_ENUMVALUE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXrioEnumList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strEnumValueKey)
	{
		pNew = new CXrioEnumValue();
	}

	return pNew;
}

CExBaseObject* CXrioEnumList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XRIOCLASSID_ENUMVALUE)
	{
		pNew = new CXrioEnumValue();
	}

	return pNew;
}

// CXrioEnabledRefList

CXrioEnabledRefList::CXrioEnabledRefList()
{

}

CXrioEnabledRefList::~CXrioEnabledRefList()
{
}

long CXrioEnabledRefList::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	
	return 0;
}

long CXrioEnabledRefList::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	
	return 0;
}

long CXrioEnabledRefList::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXrioEnabledRefList::InitAfterRead()
{
}

BOOL CXrioEnabledRefList::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioEnabledRefList *p = (CXrioEnabledRefList*)pObj;
	
	return TRUE;
}

BOOL CXrioEnabledRefList::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioEnabledRefList *p = (CXrioEnabledRefList*)pDest;
	
	return TRUE;
}

CBaseObject* CXrioEnabledRefList::Clone()
{
	CXrioEnabledRefList *p = new CXrioEnabledRefList();
	Copy(p);
	return p;
}

long CXrioEnabledRefList::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CXrioEnabledRefList::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CXrioEnabledRefList::CanPaste(UINT nClassID)
{
	if (nClassID == XRIOCLASSID_REFPARAM || nClassID == XRIOCLASSID_REFENUM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXrioEnabledRefList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strRefParamKey)
	{
		pNew = new CXrioRefParam();
	}
	else if(strClassID == pXmlKeys->m_strRefEnumKey)
	{
		pNew = new CXrioRefEnum();
	}

	return pNew;
}

CExBaseObject* CXrioEnabledRefList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XRIOCLASSID_REFPARAM)
	{
		pNew = new CXrioRefParam();
	}
	else if (nClassID == XRIOCLASSID_REFENUM)
	{
		pNew = new CXrioRefEnum();
	}

	return pNew;
}

// CXrioValueRefList

CXrioValueRefList::CXrioValueRefList()
{

}

CXrioValueRefList::~CXrioValueRefList()
{
}

long CXrioValueRefList::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	
	return 0;
}

long CXrioValueRefList::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	
	return 0;
}

long CXrioValueRefList::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXrioValueRefList::InitAfterRead()
{
}

BOOL CXrioValueRefList::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioValueRefList *p = (CXrioValueRefList*)pObj;

	return TRUE;
}

BOOL CXrioValueRefList::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioValueRefList *p = (CXrioValueRefList*)pDest;
	
	return TRUE;
}

CBaseObject* CXrioValueRefList::Clone()
{
	CXrioValueRefList *p = new CXrioValueRefList();
	Copy(p);
	return p;
}

long CXrioValueRefList::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CXrioValueRefList::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CXrioValueRefList::CanPaste(UINT nClassID)
{
	if (nClassID == XRIOCLASSID_REFPARAM || nClassID == XRIOCLASSID_REFENUM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXrioValueRefList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strRefParamKey)
	{
		pNew = new CXrioRefParam();
	}
	else if(strClassID == pXmlKeys->m_strRefEnumKey)
	{
		pNew = new CXrioRefEnum();
	}

	return pNew;
}

CExBaseObject* CXrioValueRefList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XRIOCLASSID_REFPARAM)
	{
		pNew = new CXrioRefParam();
	}
	else if (nClassID == XRIOCLASSID_REFENUM)
	{
		pNew = new CXrioRefEnum();
	}

	return pNew;
}


