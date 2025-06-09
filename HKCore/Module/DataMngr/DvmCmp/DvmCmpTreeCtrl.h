#pragma once


// CDvmCmpTreeCtrl
#include "DvmCmpTool.h"

class CDvmCmpTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CDvmCmpTreeCtrl)

public:
	CDvmCmpTreeCtrl();
	virtual ~CDvmCmpTreeCtrl();

	void ShowDvmStand(CDvmCmpTool *pDvmCmpTool);
	void ShowDvmDestCmp(CDvmCmpTool *pDvmCmpTool);

	void AttachRef(CDvmCmpTreeCtrl *pTreeCtrl)	{	m_pDvmCmpTreeCtrlRef = pTreeCtrl;	}
	void AttachMsgRcvWnd(CWnd *pWnd)			{	m_pMsgRcvWnd = pWnd;	}

protected:
	BOOL m_bShowStand;
	CDvmCmpTool *m_pDvmCmpTool;
	CDvmCmpTreeCtrl *m_pDvmCmpTreeCtrlRef;
	CWnd *m_pMsgRcvWnd;

	void ShowDvmCmp();
	void ShowDvmCmpObj(CDvmCmpObj *pDvmObj, HTREEITEM hParent);
	HTREEITEM GetRefItem(CExBaseObject *pSel);
	HTREEITEM GetRefItem(HTREEITEM hItem);

	int  GetScrollPos32(int nBar, BOOL bGetTrackPos = FALSE);
	BOOL SetScrollPos32(int nBar, int nPos, BOOL bRedraw = TRUE);

	virtual long _DrawItem(OLE_HANDLE hDC,OLE_HANDLE hItem,DWORD dwDrawStage,LRESULT* pResult);
	CDvmCmpObj* GetTestItemByTreeItem(long hTreeItem);

	BOOL IsBadRect(CRect &r)
	{
		return ( r.IsRectEmpty() || (r.Height() <= 0) || (r.Width() <= 0) );
	}

	COLORREF m_crWindow;	// = RGB(0,0,255);
	CString GetDrawText(CExBaseObject *p);
	CString GetDvmCmpName(CDvmCmpObj *pDvmCmpObj);
	long GetCmpErrorCount(CExBaseObject *p);
	COLORREF GetItemTextColor(CExBaseObject *p);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSingleExpand(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


