// D:\WorkLIJQ\Source\AutoTest\Module\GuideBookWizard\WzdCmdListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "WzdCmdListCtrl.h"
#include "..\XLanguageResourceAts.h"

// CWzdCmdListCtrl

IMPLEMENT_DYNAMIC(CWzdCmdListCtrl, CExBaseListListCtrl)

CWzdCmdListCtrl::CWzdCmdListCtrl()
{

}

CWzdCmdListCtrl::~CWzdCmdListCtrl()
{
}


BEGIN_MESSAGE_MAP(CWzdCmdListCtrl, CExBaseListListCtrl)
END_MESSAGE_MAP()



// CWzdCmdListCtrl 消息处理程序

void CWzdCmdListCtrl::InitColumns()
{
	InsertColumn(0, /*_T("编号")*/g_sLangTxt_Index);
	SetColumnWidth(0, 40);
	InsertColumn(1, /*_T("状态")*/g_sLangTxt_Status);
	SetColumnWidth(1, 40);
	InsertColumn(2, /*_T("说明信息")*/g_sLangTxt_InstrutionInfo);
	SetColumnWidth(2, 400);
	SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
}

CGbWzdCmd* CWzdCmdListCtrl::GetCurrCmd()
{
	long nCount = GetSelectedCount();

	if (nCount != 1)
	{
		return NULL;
	}

	CGbWzdCmd *pCurr = NULL;
	POSITION pos = GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		return NULL;
	}

	int nIndex = GetNextSelectedItem(pos);
	pCurr = (CGbWzdCmd*)GetItemData(nIndex);
	
	return pCurr;
}

void CWzdCmdListCtrl::UpdateIndex()
{
	long nCount = GetItemCount();
	CString strTemp;
	long nIndex = 0;

	for (nIndex=0; nIndex< nCount; nIndex++)
	{
		strTemp.Format(_T("%d"), nIndex+1);
		SetItemText(nIndex, 0, strTemp);
	}
}

