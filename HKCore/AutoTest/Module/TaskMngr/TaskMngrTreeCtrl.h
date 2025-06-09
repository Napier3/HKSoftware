#pragma once

// CTaskMngrTreeCtrl

#include "../TestControl/TctrlCntrBaseApp.h"

class CTaskMngrTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTaskMngrTreeCtrl)

public:
	CTaskMngrTreeCtrl();
	virtual ~CTaskMngrTreeCtrl();
	
//公共接口
public:
	BOOL InitShowTaskTree(CTestProject* pTestProject = NULL);

protected:
	void PopUpContextMenu(CWnd* pWnd, CPoint point,UINT nClassID);
	BOOL IsProjectOpen(CTestProject* pTestProject);
	void InsertTaskTreeItem(CExBaseObject* pObj,HTREEITEM hParent);
	void InsertChildrenTaskItem(CExBaseObject* pObj,HTREEITEM hParent);

//属性
private:
	//界面相关
	LOGFONT m_lfFont;
	CFont m_SSerif8Font;

	BOOL m_bInUpdateItemsState;
	COLORREF m_crWindow;	// = RGB(0,0,255);
	long m_xSelCheckBox;			//选择框的位置
	long m_xItemTypeIcon;		//测试项目类型图标位置
	long m_xItemTitle;					//测试项目标题的位置

	CTestProject* m_pCurrTestProject;
	CExBaseObject* m_pItemSelected;

//操作
private:
	//界面相关
	BOOL IsBadRect(CRect &r)
	{
		return ( r.IsRectEmpty() || (r.Height() <= 0) || (r.Width() <= 0) );
	}
	virtual long _DrawItem(OLE_HANDLE hDC,OLE_HANDLE hItem,DWORD dwDrawStage,LRESULT* pResult);
	COLORREF GetStateColor(CExBaseObject* pObj);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnNewTestTask();
	afx_msg void OnNewTestProject();
	afx_msg void OnDeleteTestTask();
	afx_msg void OnDeleteTestProject();
	afx_msg void OnFileTestTask();
	afx_msg void OnFileTestProject();
	afx_msg void OnOpenProject();
	afx_msg void OnCloseProject();
};