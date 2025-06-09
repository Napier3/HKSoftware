// ListBoxEx.cpp : 实现文件
//

#include "stdafx.h"
//#include "TestDialogSpliter.h"
#include "ListBoxEx.h"
#include "../../../iSmartTestWzd/Resource.h"

// CListBoxEx


IMPLEMENT_DYNAMIC(CListBoxEx, CListBox)

CListBoxEx::CListBoxEx()
{

}

CListBoxEx::~CListBoxEx()
{
}


BEGIN_MESSAGE_MAP(CListBoxEx, CListBox)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()
// CListBoxEx 消息处理程序
int CListBoxEx::AddString(LPCTSTR lpszItem, COLORREF itemColor)
{
	int nIndex = CListBox::AddString(lpszItem);
	ListBoxInfo *pInfo = new ListBoxInfo();
	pInfo->strText = lpszItem;
	pInfo->itemTextColor = itemColor;
	if (nIndex >= 0)
	{
		SetItemDataPtr(nIndex, pInfo);
	}

	return nIndex;
}

int CListBoxEx::InsertString(int nIndex,LPCTSTR lpszItem,COLORREF itemColor)
{
	if(nIndex < 0)
	{
		return -1;
	}
	ListBoxInfo *pInfo = new ListBoxInfo();
	pInfo->strText = lpszItem;
	pInfo->itemTextColor = itemColor;
	CListBox::InsertString(nIndex,lpszItem);
	SetItemDataPtr(nIndex, pInfo);

	return nIndex;
}

void CListBoxEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->itemID == -1)
	{
		DrawFocusRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem);
		return;
	}

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	COLORREF clrOld;

	ListBoxInfo* pInfo = (ListBoxInfo*)GetItemDataPtr(lpDrawItemStruct->itemID);

	// item selected ?
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		//CBrush brush(::GetSysColor(COLOR_HIGHLIGHT));
		CBrush brush(COLOR_SELECT_BK);
		pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);
	}

	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&    
		(lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		CBrush brush(::GetSysColor(COLOR_WINDOW));
		pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);
	}         

	int nBkMode = pDC->SetBkMode(TRANSPARENT);

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		clrOld = pDC->SetTextColor(COLOR_SELECT_TEXT);
		//clrOld = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else 
	{
		if (lpDrawItemStruct->itemState & ODS_DISABLED)
		{
			clrOld = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
		}
		else
		{
			clrOld = pDC->SetTextColor(pInfo->itemTextColor/*clrNew*/);
		}
	}

	CRect rect = lpDrawItemStruct->rcItem;
	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
	if (GetStyle() & LBS_USETABSTOPS)
	{
		nFormat |= DT_EXPANDTABS;
	}
	pDC->DrawText(pInfo->strText, -1, &rect, nFormat);

	pDC->SetTextColor(clrOld); 
	pDC->SetBkMode(nBkMode);
}

void CListBoxEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 25;//::GetSystemMetrics(SM_CYMENUCHECK);
}

void CListBoxEx::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	POINT   pt;
	GetCursorPos(&pt);
	int nCount = GetCount();
	ScreenToClient(&pt);
	//实现右键点击选中目标
	//for (int i =0; i<nCount; i++)

	int nItem = GetCurSel();
	if(nItem < 0 && nItem >= nCount)
	{
		return;
	}

	{
		CRect rc;
		GetItemRect(nItem, &rc);
		if(rc.PtInRect(pt))
		{
			CMenu menu;
			menu.LoadMenu(IDR_TEST_ITEM_MENU);
			CMenu* pSubMenu = menu.GetSubMenu(2);
			ClientToScreen(&pt);
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,GetParent());
		}
	}

	CListBox::OnRButtonDown(nFlags, point);
}
