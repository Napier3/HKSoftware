#pragma once

#include "CapCycleMemBuffer.h"
#include "CapCycleMemBufferMngr.h"

// CEpCapVirtualListCtrl

class CEpCapVirtualListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CEpCapVirtualListCtrl)

public:
	CEpCapVirtualListCtrl();
	virtual ~CEpCapVirtualListCtrl();

	void AddItem(CCapCycleMemBuffer *pBuffer);
	void AddItems(CCapCycleMemBufferMngr *pBufferMngr);
	void DeleteAllItems();
	BOOL GetItemText(int iRow, int iCol, CString &strText);

	BOOL CreateVirtualList(CRect rcWnd, CWnd *pParent, UINT nID);

public:
	virtual BOOL GetItemText(CCapCycleMemBuffer *pBuffer, int iCol, CString &strText);
	virtual BOOL InitVirtualListTitle();
	virtual CCapCycleMemBuffer* GetItemDataPtr(long nItemIndex);

private:
	DWORD *m_pListBuffer;
	long m_nCount;
	long m_nMaxItems;
	long m_nOrignSize;

	void ExpandBuffer();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnGetDispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


