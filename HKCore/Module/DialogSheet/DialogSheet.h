#pragma once

#include "DialogPage.h"
#include "..\BaseClass\TLinkList.h"
// DialogSheet
typedef CTLinkList<CDialogPage> CDialogPages;
class CDialogSheet : public CTabCtrl,public CTLinkList<CDialogPage>
{
	DECLARE_DYNAMIC(CDialogSheet)

public:
	CDialogSheet();
	virtual ~CDialogSheet();

public:
	//添加方法
	CDialogPage *GetActivePage()const;
	int GetActiveIndex()const;
	CDialogPage *GetPage(int nPage)const;
	int GetPageIndex(CDialogPage *pPage);
	BOOL SetActivePage(int nPage);
	BOOL SetActivePage(CDialogPage *pPage);
	void SetTitle(const CString &strTitle, long nPage); 
	void SetTitle(const CString &strTitle, CDialogPage *pPage); 
	void AddPage(CDialogPage *pPage);
	void DeletePage(int nPage);
	void DeletePage(CDialogPage *pPage);
	void InsertBefore(CDialogPage *pInsertPage,CDialogPage *pPage);
	void InsertBefore(CDialogPage *pPage,int nIndex);
	void InsertAfter(CDialogPage *pInsertPage,CDialogPage *pPage);
	void InsertAfter(CDialogPage *pPage,int nIndex);
	void DeleteAll();
	
	
public:
	friend class CDialogPage;
	CDialogPages m_listPages; //Pages链表

private:
	CDialogPage *m_pActivePage; //当前页指针

protected:
	DECLARE_MESSAGE_MAP()

	//{{AFX_MSG(DialogSheet)
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

private:
	BOOL AddTab(CDialogPage *pDialog,int nIndex);
	BOOL DeleteTab(int nIndex);
	void SetPagePostion(CDialogPage *pPage);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


