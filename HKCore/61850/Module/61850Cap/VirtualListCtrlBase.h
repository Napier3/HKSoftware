#pragma once

// CVirtualListCtrlBase
#include "..\BaseClass\ExBaseList.h"

class CVirtualListCtrlBase : public CListCtrl
{
	DECLARE_DYNAMIC(CVirtualListCtrlBase)

public:
	CVirtualListCtrlBase();
	virtual ~CVirtualListCtrlBase();

	void AddItem(CExBaseObject *pData);
	void AddItems(CExBaseList *pDatas);
	void DeleteAllItems();
	BOOL GetItemText(int iRow, int iCol, CString &strText);

	BOOL CreateVirtualList(CRect rcWnd, CWnd *pParent, UINT nID);
	void SetItemsLimit(UINT nLimit);

public:
	virtual BOOL GetItemText(CBaseObject *pData, int iCol, CString &strText);
	virtual BOOL InitVirtualListTitle();
	virtual CCapCycleMemBuffer* GetItemDataPtr(long nItemIndex);

private:
	DWORD *m_pListBuffer;
	long m_nCount;
	long m_nItemsLimit;


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnGetDispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


