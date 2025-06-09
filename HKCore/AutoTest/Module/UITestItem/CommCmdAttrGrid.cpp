#include "StdAfx.h"
#include "CommCmdAttrGrid.h"

#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNAMIC(CCommCmdAttrGrid, CListCtrl)


CCommCmdAttrGrid::CCommCmdAttrGrid(void)
{
	
}

CCommCmdAttrGrid::~CCommCmdAttrGrid(void)
{
}

void CCommCmdAttrGrid::CreateGrid(CWnd *pParent, CRect rcWnd, UINT nID)
{
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS;
	BOOL bTrue = Create(dwStyle, rcWnd, pParent, nID);

	ModifyStyle(LVS_SORTASCENDING | LVS_SORTDESCENDING, NULL);
	SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	InsertColumn(0,g_sLangTxt_Name/*_T("名称")*/,LVCFMT_LEFT,150);
	InsertColumn(1,g_sLangTxt_Values/*_T("值")*/,LVCFMT_LEFT,200);

	for (m_nCurrRowIndex=0; m_nCurrRowIndex<10; m_nCurrRowIndex++)
	{
		InsertItem(m_nCurrRowIndex, _T(""));
	}
}

void CCommCmdAttrGrid::ShowCommCmdAttr(CExBaseObject *pItem)
{
	m_pCurrItem = pItem;
	CCommCmd *pCommCmd = (CCommCmd*)pItem;
	CCmd *pCmd = pCommCmd->GetCmd();

	CDevice *pDevice = (CDevice *)pItem->GetAncestor(GBCLASSID_DEVICE);
	CSysParas *pSysParas = NULL;
	CDataObj *pData = NULL;
	
	if (pDevice != NULL)
	{
		pSysParas = pDevice->m_pSysParas;
	}

	//DeleteAllItems();
	m_nCurrRowIndex = 0;
	ShowAttr(g_sLangTxt_Name/*_T("名称")*/, pCommCmd->m_strName);
	ShowAttr(g_sLangTxt_ComictnComm/*_T("通讯命令")*/, pCommCmd->m_strCommCmdID);
	ShowAttr(_T("CPU"), pCmd->m_strDatasetPath);

	if (IsStringNumber(pCmd->m_strDelayBeforeCmd))
	{
		ShowAttr(g_sLangTxt_ComictnFront/*_T("通讯前延时")*/, pCmd->m_strDelayBeforeCmd);
	}
	else
	{
		pData = (CDataObj *)pSysParas->FindByID(pCmd->m_strDelayBeforeCmd);

		if (pData != NULL)
		{
			ShowAttr(g_sLangTxt_ComictnFront/*_T("通讯前延时")*/, pData->m_strValue + _T(" ms"));
		}
		else
		{
			ShowAttr(g_sLangTxt_ComictnFront/*_T("通讯前延时")*/, pCmd->m_strDelayBeforeCmd);
		}
	}

	if (IsStringNumber(pCmd->m_strDelayAfterCmd))
	{
		ShowAttr(g_sLangTxt_ComictnLater/*_T("通讯后延时")*/, pCmd->m_strDelayAfterCmd);
	}
	else
	{
		pData = (CDataObj *)pSysParas->FindByID(pCmd->m_strDelayAfterCmd);

		if (pData != NULL)
		{
			ShowAttr(g_sLangTxt_ComictnLater/*_T("通讯后延时")*/, pData->m_strValue + _T(" ms"));
		}
		else
		{
			ShowAttr(g_sLangTxt_ComictnLater/*_T("通讯后延时")*/, pCmd->m_strDelayAfterCmd);
		}
	}

	ShowAttr(g_sLangTxt_ComputMode/*_T("计算模式")*/, pCmd->m_strCalMode);
	ShowAttr(g_sLangTxt_ComictnTime/*_T("通讯次数")*/, pCmd->m_nRepeatTimes);
}

void CCommCmdAttrGrid::ShowAttr(const CString &strName,const CString &strValue, long nAttrIndex)
{
	if (nAttrIndex >= 0)
	{
		SetItemText(nAttrIndex, 0, strName);
		SetItemText(nAttrIndex, 1, strValue);
	}
	else
	{
		SetItemText(m_nCurrRowIndex, 0, strName);
		SetItemText(m_nCurrRowIndex, 1, strValue);
		m_nCurrRowIndex++;
	}
}

void CCommCmdAttrGrid::ShowAttr(const CString &strName,long nValue, long nAttrIndex)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	ShowAttr(strName, strValue, nAttrIndex);
}

void CCommCmdAttrGrid::ShowAttr(const CString &strName,float fValue, long nAttrIndex)
{
	CString strValue;
	strValue.Format(_T("%.f"), fValue);
	ShowAttr(strName, strValue, nAttrIndex);
}

void CCommCmdAttrGrid::ShowAttr(const CString &strName,double dValue, long nAttrIndex)
{
	CString strValue;
	strValue.Format(_T("%.f"), dValue);
	ShowAttr(strName, strValue, nAttrIndex);
}

