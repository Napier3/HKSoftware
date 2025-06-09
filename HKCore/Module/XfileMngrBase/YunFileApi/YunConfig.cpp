//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//YunConfig.cpp  CYunConfig


#include "stdafx.h"
#include "YunConfig.h"

CYunConfig::CYunConfig()
{
	//初始化属性

	//初始化成员变量
}

CYunConfig::~CYunConfig()
{
}

long CYunConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CYunConfigXmlRWKeys *pXmlKeys = (CYunConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetElementText(pXmlKeys->m_strProgIDKey, oNode, m_strProgID);

	return 0;
}

long CYunConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CYunConfigXmlRWKeys *pXmlKeys = (CYunConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strProgIDKey, oXMLDoc, oElement, m_strProgID);

	return 0;
}

void CYunConfig::InitAfterRead()
{
}

BOOL CYunConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CYunConfig *p = (CYunConfig*)pObj;

	if(m_strProgID != p->m_strProgID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CYunConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CYunConfig *p = (CYunConfig*)pDest;

	p->m_strProgID = m_strProgID;
	return TRUE;
}

CBaseObject* CYunConfig::Clone()
{
	CYunConfig *p = new CYunConfig();
	Copy(p);
	return p;
}

long CYunConfig::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("ProgID"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CYunConfig::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strProgID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

