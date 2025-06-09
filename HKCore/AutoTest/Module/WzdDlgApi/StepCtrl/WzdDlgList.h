#pragma once
#include "WzdDlgButton.h"
#include "../StepDlg/WzdDlgBase.h"
#include "../../../iSmartTestWzd/Resource.h"
#include <vector>

class CWzdDlgList : public CWzdDlgBase
{
	DECLARE_DYNAMIC(CWzdDlgList)
private:
	std::vector<CWzdDlgButton*> m_listItems;

public:
	CWzdDlgList(CWnd* pParent = NULL);
	virtual ~CWzdDlgList();

	enum { IDD = IDD_STEP_LIST };

public:
	void CalItemsRect();
	CWzdDlgButton* AddNewItem(const CString& strText);
	void SetItemData(long nIndex, void* pData);
	void* GetItemData(long nIndex);
	void SetCurSel(long nIndex);
	long SetCurSel(CWnd* pWnd);
	CWzdDlgButton* FindBtnByID(const CString& strID);
	void EnableItem(long nIndex, BOOL bEnabled);
	void EnableItem(const CString& strID, BOOL bEnabled);
	void SetItemVisible(long nIndex, BOOL bVisible);
	void SetItemVisible(const CString& strID, BOOL bVisible);
	long GetVisibleCount();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void OnPaint();   
	DECLARE_MESSAGE_MAP()
};