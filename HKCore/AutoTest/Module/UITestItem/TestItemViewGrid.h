#pragma once
#include "../GuideBook/GuideBookInterface.h"

#define WM_SELECT_TESTITEM  (WM_USER + 1909)

class CTestItemViewGrid :	public CListCtrl
{
		DECLARE_DYNAMIC(CTestItemViewGrid)

public:
	CTestItemViewGrid(void);
	~CTestItemViewGrid(void);

	void CreateGrid(CWnd *pParent, CRect rcWnd, UINT nID, CWnd *pMainFrame);
	void ShowItems(CExBaseList *pList);

	BOOL AddItem(CExBaseObject *pItem);
	BOOL RemoveItem(CExBaseObject *pItem);

protected:
	CExBaseList m_listInlegibleItem;
	CWnd *m_pMainFrame;

	void ShowItem(CExBaseObject *pItem, long nIndex);

	void UpdateItem(CMacroTest *pMacroTest, long nIndex);
	void UpdateItem(CCommCmd *pCommCmd, long nIndex);
	void UpdateItem(CSafety *pSafety, long nIndex);

	void GetReportText(CReport *pReport, CShortDatas *pDatas, CString &strText);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};
