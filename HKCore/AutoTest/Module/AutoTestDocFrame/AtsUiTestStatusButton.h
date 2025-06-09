#pragma once

#include "AtsTitleTipWnd.h"

/*
	ע�⣺������Ҫ�������� 2010-07-17
*/

#include "../TaskMngr/TestProject.h"
#include "../TestControl/TctrlCntrBaseApp.h"

class CAtsUiTestStatusButton : public CButton
{
	DECLARE_DYNAMIC(CAtsUiTestStatusButton)

public:
	CAtsUiTestStatusButton();
	virtual ~CAtsUiTestStatusButton();

public:
	void CreateTitleTip();
	void SetTestControl(CTestControl* pTestControl);

	void _OnLButtonDblClk(UINT nFlags, CPoint point);
	void _OnMouseMove(UINT nFlags, CPoint point);
	COLORREF GetTipColor(){ return m_clrTip;}
	void _OnSize();

private:
	//CTestProject* m_pTestProject;
	CTestControl* m_pTestControl;
	CGbItemBase* m_pCurrSelTestItem;		//��ǰѡ�еĲ�����Ŀ
	long m_nItemCount;
	CExBaseList m_oListMngr;

	CAtsTitleTipWnd m_TitleTip;
	CRect m_rectTitleTip;
	long m_nOldItemIndexShowTip;

	long m_nTopGap;
	long m_nTimerIDEvent;

	HWND m_hWndToolTip;
	TOOLINFO ti;
	BOOL m_bTipFlag;
	CString m_strOldSelected;
	COLORREF m_clrTip;

	BOOL m_bRePaint;
	CBitmap	*m_pBitmap;
	CBitmap	*m_pOldBitmap;
	CDC		*m_pMemDC;

	
private:
	long GetTestItemIndexAtPoint(CPoint point);
	CGbItemBase* GetTestItemAtPoint(CPoint point);

	//��ȡ���������Ĳ�����Ŀ�ĸ���
	long GetTestItemCount(CTestControl* pTestControl);
	long GetChildrenItemCount(CGbItemBase* pTestItem);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


