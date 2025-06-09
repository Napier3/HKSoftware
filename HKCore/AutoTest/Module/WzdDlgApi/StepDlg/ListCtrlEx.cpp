// ListCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "ListCtrlEx.h"


// CListCtrlEx

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx()
{
	m_bIsShowLine = false;
}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,OnNMCustomdraw)
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()

// CListCtrlEx 消息处理程序
int CListCtrlEx::GetListSelectRow()
{
	POSITION pos = GetFirstSelectedItemPosition();
	int nRow = GetNextSelectedItem(pos);
	if(nRow < 0)
	{
		return -1;
	}
	return nRow;
}

void CListCtrlEx::SetListSelectRow(int nRow,int nLastRow)
{
	int nRowCount = GetItemCount();
	SetItemState(nRow,LVIS_SELECTED, LVIS_SELECTED);
	//UINT nState = CListCtrl::GetItemState(nRow,LVIF_STATE); 
	//UINT nState = GetItemState(nRow,LVIS_SELECTED); 
	//nState &=! nState;
	if(nLastRow == -1)
	{
		for(int i = 0;i < nRowCount;i++)
		{
			if(i != nRow)
			{
				SetItemState(i,0,LVIS_SELECTED);
			}
		}	
	}
	else
	{
		SetItemState(nLastRow,0,LVIS_SELECTED);
	}
}

void CListCtrlEx::SetListRowState(int nRow)
{
	SetItemState(nRow,0, LVIS_SELECTED);
}

void CListCtrlEx::SetIsShowLine(bool bFlag)
{
	m_bIsShowLine = bFlag;
}

void CListCtrlEx::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW *pNMCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	int nItemIndex = static_cast<int>(pNMCD->nmcd.dwItemSpec);
	int   nIsSelect = -1;

	switch(pNMCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;
		}
	case CDDS_ITEMPREPAINT:
		{
			if((GetItemState(nItemIndex,LVIS_SELECTED) == LVIS_SELECTED))
			{
				nIsSelect = 1;
				SetItemState(nItemIndex,0,LVIS_SELECTED);
				pNMCD->clrText = RGB(0,0,0);
				pNMCD->clrTextBk = RGB(202,235,238);
				//*pResult = CDRF_NOTIFYITEMDRAW;
				*pResult = CDRF_NOTIFYPOSTPAINT;
				//*pResult = CDRF_NEWFONT
				//*pResult = CDRF_DODEFAULT;
			}
			else
			{
				if(m_bIsShowLine)
				{
					CDC* pDC = CDC::FromHandle(pNMCD->nmcd.hdc);
					CRect rect(0, 0, 0, 0);
					GetItemRect(nItemIndex,rect,0);
					rect.top = rect.top-1;
					rect.left = rect.left-1;
					rect.right = rect.right+1;
					rect.bottom = rect.bottom+1;

					CPen pen;
					pen.CreatePen(PS_SOLID, 1,RGB(242,248,248));
					CPen* pOldPen = pDC->SelectObject(&pen);
					pDC->Rectangle(&rect);
					pDC->SelectObject(pOldPen);
					pen.DeleteObject();
				}
				else
				{
					CItems* pItem = NULL;
					pItem = (CItems*)GetItemData(nItemIndex);
					if(pItem == NULL)
					{
						return;
					}
					if(pItem->GetState() == TEST_STATE_ELIGIBLE || pItem->GetState() == TEST_STATE_INLEGIBLE) //合格
					{
						pNMCD->clrText = RGB(156,160,183);
						pNMCD->clrTextBk = RGB(255,255,255);
						//*pResult = CDRF_NOTIFYPOSTPAINT;
					}
					else
					{
						//SetItemState(nItemIndex,LVIS_SELECTED,LVIS_SELECTED);
						//pNMCD->clrText = RGB(0,0,0);
						//pNMCD->clrTextBk = RGB(255,255,255);
					}
				}
			}
		}
		break;
		case CDDS_ITEMPOSTPAINT:
		if(nIsSelect = 1)
		{
			SetItemState(nItemIndex,LVIS_SELECTED,LVIS_SELECTED);
		}
		break;
	default:
		//*pResult = CDRF_DODEFAULT;
		break;
	}
}

void CListCtrlEx::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//lpMeasureItemStruct->itemHeight = 30;  
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
