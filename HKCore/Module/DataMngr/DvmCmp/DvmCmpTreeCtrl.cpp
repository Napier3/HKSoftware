// D:\WorkLiJQ\Source\AutoTest\Module\UITestItem\DvmCmpTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "DvmCmpTreeCtrl.h"
#include "..\..\API\GloblaDrawFunctions.h"

long g_nRefOptrCount = 0;
// CDvmCmpTreeCtrl

IMPLEMENT_DYNAMIC(CDvmCmpTreeCtrl, CTreeCtrl)

CDvmCmpTreeCtrl::CDvmCmpTreeCtrl()
{
	m_bShowStand = FALSE;
	m_pDvmCmpTool = NULL;
	m_pMsgRcvWnd = NULL;

	m_crWindow = RGB(255,255,255);

}

CDvmCmpTreeCtrl::~CDvmCmpTreeCtrl()
{
}

void CDvmCmpTreeCtrl::ShowDvmStand(CDvmCmpTool *pDvmCmpTool)
{
	m_pDvmCmpTool = pDvmCmpTool;
	m_bShowStand = TRUE;
	ShowDvmCmp();
}

void CDvmCmpTreeCtrl::ShowDvmDestCmp(CDvmCmpTool *pDvmCmpTool)
{
	m_pDvmCmpTool = pDvmCmpTool;
	m_bShowStand = FALSE;
	ShowDvmCmp();
}

void CDvmCmpTreeCtrl::ShowDvmCmp()
{
	DeleteAllItems();
	POS pos = m_pDvmCmpTool->GetHeadPosition();
	CDvmCmpObj *p = NULL;
	HTREEITEM hItem = NULL;


	if (m_bShowStand)
	{
		hItem = InsertItem(m_pDvmCmpTool->m_pStand->m_strName);
		m_pDvmCmpTool->m_hStand = hItem;
	}
	else
	{
		hItem = InsertItem(m_pDvmCmpTool->m_pDestCmp->m_strName);
		m_pDvmCmpTool->m_hDestCmp = hItem;
	}

	SetItemData(hItem, (DWORD)m_pDvmCmpTool);

	while (pos != NULL)
	{
		p = (CDvmCmpObj*)m_pDvmCmpTool->GetNext(pos);
		ShowDvmCmpObj(p, hItem);
	}
}

void CDvmCmpTreeCtrl::ShowDvmCmpObj(CDvmCmpObj *pDvmObj, HTREEITEM hParent)
{
	BOOL bCanInsertChild = TRUE;

	if (pDvmObj->m_pStand != NULL)
	{
		if (pDvmObj->m_pStand->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			bCanInsertChild = FALSE;
		}
	}

	if (pDvmObj->m_pDestCmp != NULL)
	{
		if (pDvmObj->m_pDestCmp->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			bCanInsertChild = FALSE;
		}
	}

	POS pos = pDvmObj->GetHeadPosition();
	CDvmCmpObj *p = NULL;
	HTREEITEM hItem = NULL;

	if (m_bShowStand)
	{
		if (pDvmObj->m_pStand != NULL)
		{
			hItem = InsertItem(pDvmObj->m_pStand->m_strName, 0, 0, hParent);
		}
		else
		{
			hItem = InsertItem(_T("------------"), 0, 0, hParent);
		}

		pDvmObj->m_hStand = hItem;
	}
	else
	{
		if (pDvmObj->m_pDestCmp != NULL)
		{
			hItem = InsertItem(pDvmObj->m_pDestCmp->m_strName, 0, 0, hParent);
		}
		else
		{
			hItem = InsertItem(_T("------------"), 0, 0, hParent);
		}

		pDvmObj->m_hDestCmp = hItem;
	}

	SetItemData(hItem, (DWORD)pDvmObj);

	if (!bCanInsertChild)
	{
		return;
	}

	while (pos != NULL)
	{
		p = (CDvmCmpObj*)pDvmObj->GetNext(pos);
		ShowDvmCmpObj(p, hItem);
	}
}

BEGIN_MESSAGE_MAP(CDvmCmpTreeCtrl, CTreeCtrl)
ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDvmCmpTreeCtrl::OnTvnSelchanged)
ON_NOTIFY_REFLECT(TVN_SINGLEEXPAND, &CDvmCmpTreeCtrl::OnTvnSingleExpand)
ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, &CDvmCmpTreeCtrl::OnTvnItemexpanded)
ON_WM_VSCROLL()
ON_WM_MOUSEWHEEL()
ON_NOTIFY_REFLECT(NM_DBLCLK, &CDvmCmpTreeCtrl::OnNMDblclk)
ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CDvmCmpTreeCtrl::OnCustomdraw)
END_MESSAGE_MAP()

void CDvmCmpTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	 HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	if (hItem == NULL)
	{
		return;
	}

	CExBaseObject *pSel = (CExBaseObject *)GetItemData(hItem);

	if (pSel == NULL)
	{
		return;
	}

	if (pSel->GetClassID() == DVMCMP_CLASSID_TOOL)
	{
		if (m_bShowStand)
		{
			m_pDvmCmpTreeCtrlRef->SelectItem(m_pDvmCmpTool->m_hDestCmp);
		}
		else
		{
			m_pDvmCmpTreeCtrlRef->SelectItem(m_pDvmCmpTool->m_hStand);
		}
	}
	else
	{
		CDvmCmpObj *pCDvmCmpObj = (CDvmCmpObj*)pSel;

		if (m_bShowStand)
		{
			m_pDvmCmpTreeCtrlRef->SelectItem(pCDvmCmpObj->m_hDestCmp);
		}
		else
		{
			m_pDvmCmpTreeCtrlRef->SelectItem(pCDvmCmpObj->m_hStand);
		}
	}

	*pResult = 0;
}

void CDvmCmpTreeCtrl::OnTvnSingleExpand(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

HTREEITEM CDvmCmpTreeCtrl::GetRefItem(HTREEITEM hItem)
{
	CExBaseObject *pSel = (CExBaseObject *)GetItemData(hItem);
	ASSERT (pSel != NULL);
	
	return GetRefItem(pSel);
}

HTREEITEM CDvmCmpTreeCtrl::GetRefItem(CExBaseObject *pSel)
{
	if (pSel->GetClassID() == DVMCMP_CLASSID_TOOL)
	{
		if (m_bShowStand)
		{
			return m_pDvmCmpTool->m_hDestCmp;
		}
		else
		{
			return m_pDvmCmpTool->m_hStand;
		}
	}
	else
	{
		CDvmCmpObj *pCDvmCmpObj = (CDvmCmpObj*)pSel;

		if (m_bShowStand)
		{
			return pCDvmCmpObj->m_hDestCmp;
		}
		else
		{
			return pCDvmCmpObj->m_hStand;
		}
	}
}

void CDvmCmpTreeCtrl::OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;//GetSelectedItem();

	if (hItem == NULL)
	{
		return;
	}

	UINT nCode = 0;
	UINT nCurrState = GetItemState(hItem, TVIS_EXPANDED);

	if ((TVIS_EXPANDED & nCurrState) == TVIS_EXPANDED)
	{
		nCode = TVE_EXPAND;
	}
	else
	{
		nCode = TVE_COLLAPSE;
	}

	HTREEITEM hItemExpand = GetRefItem(hItem);

	UINT nState = m_pDvmCmpTreeCtrlRef->GetItemState(hItemExpand, TVIS_EXPANDED);

	if (nState == nCurrState)
	{
		return;
	}

	m_pDvmCmpTreeCtrlRef->LockWindowUpdate();
	m_pDvmCmpTreeCtrlRef->Expand(hItemExpand, nCode);
	m_pDvmCmpTreeCtrlRef->UnlockWindowUpdate();

	*pResult = 0;
}


int CDvmCmpTreeCtrl::GetScrollPos32(int nBar, BOOL bGetTrackPos /* = FALSE */)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);

	if (bGetTrackPos)
	{
		if (GetScrollInfo(nBar, &si, SIF_TRACKPOS))
			return si.nTrackPos;
	}
	else 
	{
		if (GetScrollInfo(nBar, &si, SIF_POS))
			return si.nPos;
	}

	return 0;
}

BOOL CDvmCmpTreeCtrl::SetScrollPos32(int nBar, int nPos, BOOL bRedraw /* = TRUE */)
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask  = SIF_POS;
	si.nPos   = nPos;
	return SetScrollInfo(nBar, &si, bRedraw);
}

void CDvmCmpTreeCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

	g_nRefOptrCount++;

	if (g_nRefOptrCount > 1)
	{
		g_nRefOptrCount = 0;
		return;
	}

	CScrollBar *pBar = NULL;

	if (pScrollBar != NULL)
	{
		CScrollBar *pBar = m_pDvmCmpTreeCtrlRef->GetScrollBarCtrl(SB_VERT);
	}

	int scrollPos1 = GetScrollPos32(SB_VERT);
	int scrollPos2 = m_pDvmCmpTreeCtrlRef->GetScrollPos32(SB_VERT);

	if (scrollPos1 == scrollPos2)
	{	
		g_nRefOptrCount = 0;
	}
	else
	{
		m_pDvmCmpTreeCtrlRef->SetScrollPos32(SB_VERT, scrollPos1, TRUE);
		m_pDvmCmpTreeCtrlRef->OnVScroll(nSBCode, nPos, pBar);
	}

	return;

	long nCurrPos = GetScrollPos(SB_VERT);
	long nCurrPosRef = m_pDvmCmpTreeCtrlRef->GetScrollPos(SB_VERT);

	if (nCurrPos != nCurrPosRef)
	{
		m_pDvmCmpTreeCtrlRef->OnVScroll(nSBCode, nPos, pBar);
		//m_pDvmCmpTreeCtrlRef->SetScrollPos(SB_VERT, nCurrPos,TRUE);
		//m_pDvmCmpTreeCtrlRef->ScrollWindow()
	}
	else
	{
		g_nRefOptrCount = 0;
	}
}

BOOL CDvmCmpTreeCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL bRet = CTreeCtrl::OnMouseWheel(nFlags, zDelta, pt);

	g_nRefOptrCount++;

	if (g_nRefOptrCount > 1)
	{
		g_nRefOptrCount = 0;
		return bRet;
	}

	int scrollPos1 = GetScrollPos32(SB_VERT);
	int scrollPos2 = m_pDvmCmpTreeCtrlRef->GetScrollPos32(SB_VERT);
	m_pDvmCmpTreeCtrlRef->OnMouseWheel(nFlags, zDelta, pt);

	return bRet;

	if (scrollPos1 == scrollPos2)
	{	
		g_nRefOptrCount = 0;
	}
	else
	{
		//m_pDvmCmpTreeCtrlRef->SetScrollPos32(SB_VERT, scrollPos1, TRUE);
		m_pDvmCmpTreeCtrlRef->OnMouseWheel(nFlags, zDelta, pt);
	}

	return bRet;
}

void CDvmCmpTreeCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	HTREEITEM hItem = GetSelectedItem();


	if (hItem == NULL)
	{
		return;
	}

	CExBaseObject *pSel = (CExBaseObject*)GetItemData(hItem);

	if(pSel == NULL)
	{
		return;
	}
	
	if (pSel->GetClassID() != DVMCMP_CLASSID_CMPOBJ)
	{
		return;
	}

	CDvmCmpObj *pDvmCmp = (CDvmCmpObj*)pSel;

	ASSERT (m_pMsgRcvWnd != NULL);

	if (m_pMsgRcvWnd == NULL)
	{
		return;
	}

	m_pMsgRcvWnd->PostMessage(WM_OPEN_DVMCMPOBJ, (WPARAM)pDvmCmp, (LPARAM)pDvmCmp);
}

void CDvmCmpTreeCtrl::OnCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTVCUSTOMDRAW* pCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);
	CDC* pDC = CDC::FromHandle(pCD->nmcd.hdc);
	HTREEITEM hItem = reinterpret_cast<HTREEITEM> (pCD->nmcd.dwItemSpec);
	*pResult = CDRF_DODEFAULT;

	LPNMHDR pNmhdr = (LPNMHDR)pNMHDR;          
	LPNMTVCUSTOMDRAW pCustomDraw = (LPNMTVCUSTOMDRAW)pNMHDR;

	if(m_pDvmCmpTool == NULL)
	{
		return ;
	}
	
	_DrawItem((long)pCD->nmcd.hdc
		,(long)hItem
		,pCD->nmcd.dwDrawStage
		,pResult);
}


CDvmCmpObj* CDvmCmpTreeCtrl::GetTestItemByTreeItem(long hTreeItem)
{
	if(m_pDvmCmpTool == NULL)
	{
		return NULL;
	}

	CExBaseObject *p = (CExBaseObject*)GetItemData((HTREEITEM)hTreeItem);

	if (p == NULL)
	{
		return NULL;
	}

	return NULL;
}

CString CDvmCmpTreeCtrl::GetDrawText(CExBaseObject *p)
{
	if (p->GetClassID() == DVMCMP_CLASSID_TOOL)
	{
		if (m_bShowStand)
		{
			return m_pDvmCmpTool->m_pStand->m_strName;
		}
		else
		{
			return m_pDvmCmpTool->m_pDestCmp->m_strName;
		}
	}
	else
	{
		CDvmCmpObj *pDvmObj = (CDvmCmpObj*)p;

		if (m_bShowStand)
		{
			if (pDvmObj->m_pStand != NULL)
			{
				return pDvmObj->m_pStand->m_strName;
			}
			else
			{
				return _T("------------");
			}
		}
		else
		{
			if (pDvmObj->m_pDestCmp != NULL)
			{
				return pDvmObj->m_pDestCmp->m_strName;
			}
			else
			{
				return _T("------------");
			}
		}
	}
}

long CDvmCmpTreeCtrl::GetCmpErrorCount(CExBaseObject *p)
{
	if (p->GetClassID() == DVMCMP_CLASSID_TOOL)
	{
		return 0;
	}
	else
	{
		CDvmCmpObj *pDvmObj = (CDvmCmpObj*)p;
		return pDvmObj->m_nChildCmp;

		if (pDvmObj->IsDvmDatasetCmpObj())
		{
			return pDvmObj->m_nChildCmp;
		}
		else
		{
			return 0;
		}
	}
}

COLORREF CDvmCmpTreeCtrl::GetItemTextColor(CExBaseObject *p)
{
	if (GetCmpErrorCount(p) == 0)
	{
		return RGB(0, 0, 0);
	}
	else
	{
		return RGB(255, 0, 0);
	}
}

long CDvmCmpTreeCtrl::_DrawItem(OLE_HANDLE hDC,OLE_HANDLE hItem,DWORD dwDrawStage,LRESULT* pResult)
{
	CDC dc;
	dc.Attach((HDC)hDC);
	HTREEITEM hCurrItem = (HTREEITEM)hItem;
	*pResult = CDRF_DODEFAULT;

	//=========================================================================
	if (dwDrawStage == CDDS_PREPAINT)	// before the painting cycle begins
	{
		*pResult = CDRF_NOTIFYITEMDRAW /*| CDRF_NOTIFYPOSTPAINT*/;
	}
	else if (dwDrawStage == CDDS_ITEMPREPAINT)	// before an item is drawn
	{
		if (hCurrItem)
		{
			CRect rectItem1;
			GetItemRect(hCurrItem, &rectItem1, FALSE);	// get rect for item
			
			if (!IsBadRect(rectItem1))
			{
				CBrush brush(m_crWindow);
				dc.FillRect(&rectItem1, &brush);		// erase entire background
			}
		}

		*pResult = CDRF_NOTIFYPOSTPAINT | CDRF_NEWFONT;
	}
	else if (dwDrawStage == CDDS_ITEMPOSTPAINT)	// after an item has been drawn
	{
		CExBaseObject* pTestItem = (CExBaseObject*)GetItemData((HTREEITEM)hItem);

		if(pTestItem != NULL)
		{
			HTREEITEM hSelItem = GetSelectedItem();
		
			//绘制项目名称
			BOOL bSelected = FALSE;

			if(hSelItem == hCurrItem)
				bSelected = TRUE;

			BOOL bChangeFont = FALSE;
			CFont *pOldFont = NULL;
			CFont fontChange;
			COLORREF clrTextSave,clrBkSave;

			CRect rectItem;
			GetItemRect(hCurrItem, &rectItem, FALSE);		// get rect for entire item
			CRect rectText;
			GetItemRect(hCurrItem, &rectText, TRUE);		// get rect for text
			rectText.right = rectItem.right;

			dc.FillSolidRect(&rectText, m_crWindow);

			CRect rectTitle = rectText;
			clrTextSave = dc.SetTextColor(GetItemTextColor(pTestItem));

			//绘制选择的Item的底色
			if (bSelected)
			{
				clrBkSave = dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
				dc.FillRect(rectTitle, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
			}
			else
			{
				dc.FillRect(rectTitle, &CBrush(::GetSysColor(COLOR_WINDOW)));
			}

			CString strName ;
			strName = GetDrawText(pTestItem);

			long nErrorCount = GetCmpErrorCount(pTestItem);

			if (nErrorCount > 0)
			{
				CRect rcError = rectTitle;
				dc.DrawText(strName,rectTitle,DT_SINGLELINE /*| DT_NOPREFIX | DT_NOCLIP */| DT_VCENTER);
				strName.Format(_T("%d/%d"), nErrorCount, ((CExBaseList*)pTestItem)->GetCount());
				dc.DrawText(strName,rectTitle,DT_SINGLELINE /*| DT_NOPREFIX | DT_NOCLIP */| DT_VCENTER | DT_RIGHT);
			}
			else
			{
				dc.DrawText(strName,rectTitle,DT_SINGLELINE /*| DT_NOPREFIX | DT_NOCLIP */| DT_VCENTER);
			}


			dc.SetTextColor(clrTextSave);

			if (bSelected)
			{
				dc.SetBkColor(clrBkSave);
			}
		}
	}

	dc.Detach();

	return S_OK;	
}
