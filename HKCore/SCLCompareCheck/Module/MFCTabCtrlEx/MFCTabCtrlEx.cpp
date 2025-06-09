// MFCTabCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCTabCtrlEx.h"


// CMFCTabCtrlEx

IMPLEMENT_DYNAMIC(CMFCTabCtrlEx, CMFCTabCtrl)

CMFCTabCtrlEx::CMFCTabCtrlEx()
{

}

CMFCTabCtrlEx::~CMFCTabCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CMFCTabCtrlEx, CMFCTabCtrl)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMFCTabCtrlEx 消息处理程序



void CMFCTabCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值  
    CMFCTabCtrl::OnLButtonDown(nFlags, point);

    // 获取Tab的数量
    int n = GetTabsNum();

    if (n == 0) return;

    CRect rc;

    // 获取整个Tab区域
    CalcRectEdit(rc);
    GetTabsRect(rc);
    // 获取当前选项卡窗口的指针
    CWnd *pTabWnd = GetActiveWnd();
    pTabWnd->GetClientRect(rc);

    int sel;

    // 获取当前选择的Tab
    sel = GetActiveTab();

    // 获取单个Tab区域
    GetTabRect(sel, rc);

    // 获取单个Tab的最大宽度
    int nWidth = GetTabMaxWidth();

    // 获取关闭按钮的区域
    CRect rcCloseBtn;
    rcCloseBtn = GetTabCloseButton();

    if (rcCloseBtn.PtInRect(point))
    {
        if(MessageBox(_T("确认关闭该标签页？"), _T("关闭提示"), MB_YESNO) == IDYES)
        {
            // 关闭Tab页关联窗口        
            pTabWnd->SendMessage(WM_CLOSE);  
            // 删除Tab  
            RemoveTab(sel);
        }
    }
           
    

}


