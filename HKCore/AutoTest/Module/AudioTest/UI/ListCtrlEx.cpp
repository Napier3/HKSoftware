// ListCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
//#include "AudioTest.h"
#include "ListCtrlEx.h"


// CListCtrlEx

//IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx()
{

}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,OnNMCustomdraw)
END_MESSAGE_MAP()

// CListCtrlEx 消息处理程序

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
			if(GetItemState(nItemIndex,LVIS_SELECTED) == LVIS_SELECTED)
			{
				nIsSelect = 1;
				SetItemState(nItemIndex,0,LVIS_SELECTED);
				pNMCD->clrText = RGB(0,0,0);
				pNMCD->clrTextBk = RGB(0,120,215);
				*pResult |= CDRF_NOTIFYPOSTPAINT;
				
			}
			/*else
			{
				nIsSelect = 0;
				//SetItemState(nItemIndex,LVIS_SELECTED,LVIS_SELECTED);
				//pNMCD->clrText = RGB(0,0,0);
				//pNMCD->clrTextBk = RGB(255,255,255);
			}*/
		}
		break;

	case CDDS_ITEMPOSTPAINT:
		if(nIsSelect = 1)
		{
			SetItemState(nItemIndex,LVIS_SELECTED,LVIS_SELECTED);
		}
		break;
		
	default:
		break;
	}

	//*pResult |= CDRF_NOTIFYPOSTPAINT;
	//*pResult |= CDRF_NOTIFYITEMDRAW;
}
