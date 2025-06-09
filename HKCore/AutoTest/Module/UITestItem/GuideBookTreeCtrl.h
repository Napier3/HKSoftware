#pragma  once

#include "../TaskMngr/TestProject.h"

/*
2010-07-27修改 符合最新的GuideBook设计（类方式实现）
by zah
*/

#include "../TestControl/TctrlCntrBaseApp.h"
#include "../GuideBook/GuideBook.h"
//#include "../../PAautoTest/TestItemReportDlg.h"

class CGuideBookTreeCtrl : public CTreeCtrl
{
public:
	CGuideBookTreeCtrl();
	virtual ~CGuideBookTreeCtrl();

	//属性
private:
	CWnd *m_pParent;
	CTestControlBase* m_pTestControl;
	CGbItemBase* m_pCurrSelTestItem;		//当前选中的测试项目
	HTREEITEM m_hCurrSelTestItem;
	UINT m_nCurrSelTestItemIndex;
	BOOL m_bInTestItemInitState;

	LOGFONT m_lfFont;
	CFont m_SSerif8Font;
	long m_nTimerIDEvent;
	CPoint m_ptSelTestIItem;
	BOOL m_bShowOnlySelTestItems;
	BOOL m_bInUpdateItemsState;

	COLORREF m_crWindow;	// = RGB(0,0,255);
	long m_xSelCheckBox;			//选择框的位置
	long m_xItemTypeIcon;		//测试项目类型图标位置
	long m_xItemTitle;					//测试项目标题的位置

	//测试项目报告查看对话框
	//CTestItemReportDlg* m_pTestItemReportDlg;
	
	//公共接口
public:
	void InitShowTestControl(CTestControl* pTestControl);
	void InitShowTestControl2(CTestControlBase* pTestControl);
	void CloseTestProject();
	CGbItemBase* GetCurrSelTestItem()			{		return m_pCurrSelTestItem;		}
	void SelectTopItem(CGbItemBase* pItem);
	void ShowReport(BOOL bCreate);
	void UpdateTestItem(CExBaseObject *pNewItem, CExBaseObject *pOldItem);
	void SetParentWnd(CWnd *pParent)	{	m_pParent = pParent;	}

protected:
	virtual void InsertGbItemToTreeCtrl(CGbItemBase*pItem,HTREEITEM htiParent);
	virtual void InsertGbItemChildrenToTreeCtrl(CGbItemBase* pItem,HTREEITEM htiParent);
	CGbItemBase* GetTestItemByTreeItem(long hTreeItem);
	void SetTestItemSelectedState(CGbItemBase *pItem,long nSelect);
	void UpdateItemSelectedState(CGbItemBase* pItem);
	void OnContextMenuEx_Testing(CWnd* pWnd, CPoint point);
	void OnContextMenuEx_Normal(CWnd* pWnd, CPoint point);

	//界面相关
	BOOL IsBadRect(CRect &r)
	{
		return ( r.IsRectEmpty() || (r.Height() <= 0) || (r.Width() <= 0) );
	}
	void GetCheckBoxRect(CRect &rcText,CRect &rcCheck);
	virtual void OnContextMenuEx(CWnd* pWnd, CPoint point);
	virtual long _DrawItem(OLE_HANDLE hDC,OLE_HANDLE hItem,DWORD dwDrawStage,LRESULT* pResult);
	virtual long _OnSelChange();
	virtual long _OnLButtonDown(long xPoint,long yPoint);
	virtual long _OnRButtonDown(long xPoint,long yPoint);
	virtual long _OnLButtonDblClk(long xPoint,long yPoint);
	virtual void _SetShowOnlySelTestItems(long nShow);
	virtual long OnItemExpandStateChanged(OLE_HANDLE hItem,long nAction);

	long GetVisibleItemCount(long &nVisibleCount, long &nCurrItemIndex, CGbItemBase *pCurrItem, CGbItemBase *pParent);
	//void CreateGuideBookTreeImageList(UINT nBitmapID,int cx ,int nGrow,COLORREF crMask);

public:
	void GB_InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	void GB_DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	void GB_InsertItemEx(CGbItemBase *pParentItem, CGbItemBase *pSubItem);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnViewDeviceSets();
	afx_msg void OnExpandAllChildren();
	afx_msg void OnTestPoint();
	afx_msg void OnTestAllInlegibleItems();
	afx_msg void OnTestPoint_MdOne();
	afx_msg void OnUpdateGbItem();
	afx_msg void OnUpdateGbItemToGb();
	afx_msg void OnTestBelow();
	afx_msg void OnEditItemPara();
	afx_msg void OnShowReport();
	afx_msg void OnQueryRecord();
	afx_msg void OnShowCharDraw();
	afx_msg void OnShowRecord();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnItemChanged(NMHDR *pNMHDR, LRESULT *pResult);

	//向项目树中插入项目
	LRESULT OnInsertItems(WPARAM wParam, LPARAM lParam);
	
};

CGbItemBase* gbui_GetActiveTestItem(CGbItemBase *pGbIem);
