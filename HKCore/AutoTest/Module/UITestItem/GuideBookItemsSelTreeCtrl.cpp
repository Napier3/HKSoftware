#include "stdafx.h"
#include "GuideBookItemsSelTreeCtrl.h"
#include "../../../Module/api/GloblaDrawFunctions.h"
#include "../TCtrlCntrDefine.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CGuideBookItemsSel::CGuideBookItemsSel()
{
	m_nItemsRef = 0;
	m_pItemsRef = NULL;
}

CGuideBookItemsSel::~CGuideBookItemsSel()
{
	m_pItemsRef = NULL;
}

void CGuideBookItemsSel::BuildItems(CGuideBook *pGuideBook)
{
	CDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pDevice->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_ITEMS)
		{
			BuildItemsSel((CItems*)p);
		}
	}

	BuildItemsSel();
	BuildItemsSel_Del();
}

void CGuideBookItemsSel::BuildItemsSel(CItems *pItems)
{
	CGuideBookItemsSel *pNew = new CGuideBookItemsSel();
	pNew->m_pItemsRef = pItems;
	AddNewChild(pNew);

	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pItems->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_ITEMS)
		{
			pNew->BuildItemsSel((CItems*)p);
		}
	}
}

long CGuideBookItemsSel::BuildItemsSel()
{
	POS pos = GetHeadPosition();
	CGuideBookItemsSel *p = NULL;

	if (m_pItemsRef != NULL)
	{
		if (m_pItemsRef->IsTypeRootNode())
		{
			m_nItemsRef = 1;
		}
		else
		{
			m_nItemsRef = 0;
		}
	}
	else
	{
		m_nItemsRef = 0;
	}

	while (pos != NULL)
	{
		p = (CGuideBookItemsSel*)GetNext(pos);
		m_nItemsRef += p->BuildItemsSel();
	}

	return m_nItemsRef;
}

void CGuideBookItemsSel::BuildItemsSel_Del()
{
	POS pos = GetHeadPosition();
	CGuideBookItemsSel *p = NULL;
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CGuideBookItemsSel*)GetNext(pos);
		
		if (p->m_nItemsRef == 0)
		{
			DeleteAt(posPrev);
		}
		else
		{
			p->BuildItemsSel_Del();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CGuideBookItemsSelTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CGuideBookItemsSelTreeCtrl::OnCustomdraw)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(WM_EXPAND_ALL_CHILDREN,OnExpandAllChildren)
	ON_WM_CREATE()
END_MESSAGE_MAP()

#define GAP_TESTITEMFLAG 1

CGuideBookItemsSelTreeCtrl::CGuideBookItemsSelTreeCtrl()
{
	m_nTimerIDEvent = 2;
	m_bShowOnlySelTestItems = false;

	m_crWindow = RGB(255,255,255);

	CSize sizeCheck;
	GetCheckBoxSize(sizeCheck);

	//选择框的位置
	m_xSelCheckBox = GAP_TESTITEMFLAG;
	m_xSelCheckBox += sizeCheck.cx / 2;
	m_xItemTypeIcon = GAP_TESTITEMFLAG + sizeCheck.cx;

	//测试项目类型图标位置
	m_xItemTitle = GAP_TESTITEMFLAG * 2 + 16/*ICON*/ + sizeCheck.cx;
	m_bInUpdateItemsState = FALSE;

	m_pCurrSelTestItem = NULL;
	m_nCurrSelTestItemIndex = -1;
	m_hCurrSelTestItem = NULL;
	m_bInTestItemInitState = FALSE;

	m_pGuideBook = NULL;
	m_pImageList = NULL;
}

CGuideBookItemsSelTreeCtrl::~CGuideBookItemsSelTreeCtrl()
{

}

void CGuideBookItemsSelTreeCtrl::InitGuideBook(CGuideBook* pGuideBook)
{
	m_pGuideBook = pGuideBook;
	m_oGuideBookItemsSel.BuildItems(pGuideBook);

	if(m_pGuideBook != NULL)
	{
		m_bInTestItemInitState = TRUE;
		DeleteAllItems();

		InsertGbItemChildrenToTreeCtrl(&m_oGuideBookItemsSel,NULL);

		m_bInTestItemInitState = FALSE;
	}
}	

long CGuideBookItemsSelTreeCtrl::_DrawItem(OLE_HANDLE hDC,OLE_HANDLE hItem,DWORD dwDrawStage,LRESULT* pResult)
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
	else if (dwDrawStage == CDDS_ITEMPOSTPAINT && !m_bInUpdateItemsState)	// after an item has been drawn
	{
		CGbItemBase* pTestItem = GetTestItemByTreeItem((long)hCurrItem);

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

			if(pTestItem->m_nState == TEST_STATE_TESTING)
			{
				bChangeFont = TRUE;
				pOldFont = dc.SelectObject(g_pGlobalFont12);
			}

			//绘制checkbox
			BOOL bEnable = TRUE;

			CRect rectItem;
			GetItemRect(hCurrItem, &rectItem, FALSE);		// get rect for entire item
			CRect rectText;
			GetItemRect(hCurrItem, &rectText, TRUE);		// get rect for text
			rectText.right = rectItem.right;

			dc.FillSolidRect(&rectText, m_crWindow);

			long yItemCenter = rectItem.CenterPoint().y;
			DrawCheckBoxRect(rectText.left + m_xSelCheckBox, yItemCenter,pTestItem->GetSelect(), &dc, bEnable);

			//绘制图标，未完成
			long nImageID = pTestItem->GetClassID() & 0x000000FF;

			if (m_pImageList != NULL)
			{
				ImageList_DrawEx(m_pImageList->m_hImageList, nImageID,
					dc.m_hDC,rectText.left + m_xItemTypeIcon,yItemCenter -8, 16, 16,
					RGB(255,0,0), RGB(255,255,255), ILD_TRANSPARENT);
			}

			CRect rectTitle = rectText;
			rectTitle.left = rectText.left + m_xItemTitle;

			//绘制选择的Item的底色
			if (bSelected)
			{
				clrTextSave = dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
				clrBkSave = dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
				dc.FillRect(rectTitle, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
			}
			else
			{
				clrTextSave = dc.SetTextColor(GetItemStateColor(pTestItem));
				dc.FillRect(rectTitle, &CBrush(::GetSysColor(COLOR_WINDOW)));
			}

			CString strName ;
			strName = pTestItem->GetName();

			if(pTestItem->m_nState == TEST_STATE_TESTING)
			{
				strName = L">>" + strName;
			}

			dc.DrawText(strName,rectTitle,DT_SINGLELINE /*| DT_NOPREFIX | DT_NOCLIP */| DT_VCENTER);

			dc.SetTextColor(clrTextSave);

			if (bSelected)
			{
				dc.SetBkColor(clrBkSave);
			}

			if (bChangeFont)
			{
				dc.SelectObject(pOldFont);
				fontChange.DeleteObject();
			}
		}
	}

	dc.Detach();
	return S_OK;	
}

long CGuideBookItemsSelTreeCtrl::_OnLButtonDown(long xPoint,long yPoint)
{
	CPoint point(xPoint,yPoint);
	HTREEITEM hSelItem = GetSelectedItem();
	if(hSelItem == NULL || m_bInUpdateItemsState)
	{
		return FALSE;
	}

	CGbItemBase* pItem = GetTestItemByTreeItem((long)hSelItem);
	if(pItem != NULL)
	{
		CRect rectText;
		GetItemRect(hSelItem, &rectText, TRUE);
		CRect rectCheck;
		GetCheckBoxRect(rectText, rectCheck);
		BOOL bInCheck = rectCheck.PtInRect(point);

		if (bInCheck)
		{
			//改变测试项目的Select状态
			SetTestItemSelectedState(pItem, pItem->GetSelect());

			Invalidate(FALSE);
		}
	}

	return 0;
}

long CGuideBookItemsSelTreeCtrl::_OnRButtonDown(long xPoint,long yPoint)
{
	return 0;
}

long CGuideBookItemsSelTreeCtrl::_OnLButtonDblClk(long xPoint,long yPoint)
{
	HTREEITEM hSelItem = GetSelectedItem();
	if(hSelItem == NULL || m_bInUpdateItemsState)
	{
		return FALSE;
	}

	return 0;
}

void CGuideBookItemsSelTreeCtrl::_SetShowOnlySelTestItems(long nShow)
{
}

long CGuideBookItemsSelTreeCtrl::OnItemExpandStateChanged(OLE_HANDLE hItem,long nAction)
{
	return 0;
}

void CGuideBookItemsSelTreeCtrl::GetCheckBoxRect(CRect &rcText,CRect &rcCheck)
{
	CSize sizeCheck;
	GetCheckBoxSize(sizeCheck);

	//选择框的位置
	rcCheck = rcText;
	rcCheck.left += GAP_TESTITEMFLAG;
	rcCheck.right = rcCheck.left + sizeCheck.cx;
	rcCheck.top = rcText.CenterPoint().y - sizeCheck.cy / 2;
	rcCheck.bottom  =rcCheck.top + sizeCheck.cy;
}

CGbItemBase* CGuideBookItemsSelTreeCtrl::GetTestItemByTreeItem(long hTreeItem)
{
	if(m_pGuideBook != NULL)
	{
		return (CGbItemBase*)GetItemData((HTREEITEM)hTreeItem);
	}
	
	return NULL;
}

void CGuideBookItemsSelTreeCtrl::SetTestItemSelectedState(CGbItemBase *pItem,long nSelect)
{
	if (nSelect == 0)
	{
		nSelect = 1;
	}
	else
	{
		nSelect = 0;
	}

	Gb_SetTestItemSelectedState(pItem, nSelect);
}

//更新选择树形控件时的显示效果
//nSelect = 0 表示未选中,nSelect = 1表示选中,nSelect = 2表示子节点中既包含选中也包含未选中的测试项目(中间状态)
void CGuideBookItemsSelTreeCtrl::UpdateItemSelectedState(CGbItemBase* pItem)
{
	Gb_UpdateItemSelectedState(pItem);
}

void CGuideBookItemsSelTreeCtrl::InsertGbItemToTreeCtrl(CGuideBookItemsSel *pItemsSel, HTREEITEM htiParent)
{
	ASSERT(m_pGuideBook != NULL);

	DWORD dwItemData = 0;
	HTREEITEM hTreeItem = NULL;

	hTreeItem = InsertItem(pItemsSel->m_pItemsRef->m_strName,0,0,htiParent);
	pItemsSel->m_pItemsRef->m_dwItemData = (DWORD)hTreeItem;
	SetItemData(hTreeItem, (DWORD)pItemsSel->m_pItemsRef);
	
	InsertGbItemChildrenToTreeCtrl(pItemsSel, hTreeItem);

	Expand(hTreeItem,TVE_EXPAND);
}

void CGuideBookItemsSelTreeCtrl::InsertGbItemChildrenToTreeCtrl(CGuideBookItemsSel *pItemsSel,HTREEITEM htiParent)
{
	POS pos = pItemsSel->GetHeadPosition();
	CGuideBookItemsSel *p = NULL;

	while(pos != NULL)
	{
		p = (CGuideBookItemsSel*)pItemsSel->GetNext(pos);
		InsertGbItemToTreeCtrl(p, htiParent);
	}
}

//CGuideBookItemsSelTreeCtrl 消息响应
void CGuideBookItemsSelTreeCtrl::OnCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTVCUSTOMDRAW* pCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);
	CDC* pDC = CDC::FromHandle(pCD->nmcd.hdc);
	HTREEITEM hItem = reinterpret_cast<HTREEITEM> (pCD->nmcd.dwItemSpec);
	*pResult = CDRF_DODEFAULT;

	LPNMHDR pNmhdr = (LPNMHDR)pNMHDR;          
	LPNMTVCUSTOMDRAW pCustomDraw = (LPNMTVCUSTOMDRAW)pNMHDR;

	if(m_pGuideBook == NULL)
	{
		return ;
	}
	else 
	{
		_DrawItem((long)pCD->nmcd.hdc
			,(long)hItem
			,pCD->nmcd.dwDrawStage
			,pResult);
	}
}

void CGuideBookItemsSelTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point,&uFlags);
	HTREEITEM hItemSelected = GetSelectedItem();

	if(hItem != hItemSelected)
	{
		this->SelectItem(hItem);
	}

	_OnLButtonDown(point.x,point.y);
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CGuideBookItemsSelTreeCtrl::SelectTopItem(CGbItemBase* pCurrItem)
{
	long nVisibleCount = 0;
	long nCurrItemIndex = 0;

	SelectItem((HTREEITEM)pCurrItem->m_dwItemData);
	GetVisibleItemCount(nVisibleCount, nCurrItemIndex, pCurrItem, m_pGuideBook);
	nCurrItemIndex -= 7;

	if (nCurrItemIndex <= 1)
	{
		nCurrItemIndex = 0;
	}
}

long CGuideBookItemsSelTreeCtrl::GetVisibleItemCount(long &nVisibleCount, long &nCurrItemIndex, CGbItemBase *pCurrItem, CGbItemBase *pParent)
{
	CGbItemBase *pTestItem = NULL;

	POS pos = pParent->GetHeadPosition();

	while (pos != NULL)
	{
		pTestItem = (CGbItemBase*)pParent->GetNext(pos);

		if(pTestItem->m_nShow == 1)
		{
			nVisibleCount ++;
		}

		if (pTestItem == pCurrItem)
		{
			nCurrItemIndex = nVisibleCount;
		}

		//父对象展开
		if(!Gb_IsItemBaseClassID(pTestItem->GetClassID()) && pTestItem->m_nExpandState == 1)
		{
			GetVisibleItemCount(nVisibleCount,nCurrItemIndex,pCurrItem,pTestItem);
		}
	}

	return 0;
}


void CGuideBookItemsSelTreeCtrl::OnExpandAllChildren()
{
	HTREEITEM hSel = GetSelectedItem();
	UI_ExpandAllChildren(this, hSel);
}

int CGuideBookItemsSelTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}
