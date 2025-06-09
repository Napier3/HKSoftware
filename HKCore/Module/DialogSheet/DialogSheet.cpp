// DialogSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogSheet.h"
#define  MAX_PAGES 24
// CDialogSheet

IMPLEMENT_DYNAMIC(CDialogSheet, CTabCtrl)

CDialogSheet::CDialogSheet()
{
	m_pActivePage = NULL;
}

CDialogSheet::~CDialogSheet()
{
	m_listPages.DeleteAll();
}


BEGIN_MESSAGE_MAP(CDialogSheet, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CDialogSheet 消息处理程序


BOOL CDialogSheet::AddTab(CDialogPage *pDialog,int nIndex) 
{
	//创建Page对象
	pDialog->CreatePage(this);
	pDialog->ShowWindow(SW_HIDE);
	//m_listPages.AddTail(pDialog);

	//添加Page界面
	TCITEM item;
	item.mask = TCIF_TEXT|TCIF_PARAM|TCIF_IMAGE;
	item.lParam = (LPARAM) pDialog;
#ifdef UNICODE
	item.pszText = pDialog->m_strCaption.AllocSysString();
#else
	//item.pszText = pDialog->m_strCaption;
#endif
	
	InsertItem(nIndex, &item);	
	SetPagePostion(pDialog);

// 	if (m_pActivePage != NULL)
// 	{
// 		m_pActivePage->OnSetActive();
// 		m_pActivePage->ShowWindow(SW_SHOW);
// 	}
// 	else
// 	{
// 		m_pActivePage = GetPage(0);
// 
// 		if (m_pActivePage != NULL)
// 		{
// 			m_pActivePage->OnSetActive();
// 			m_pActivePage->ShowWindow(SW_SHOW);
// 		}
// 	}

	Invalidate(FALSE);
	return TRUE;
}

BOOL CDialogSheet::DeleteTab(int nIndex)
{
	long nItemCount = GetItemCount();
	ASSERT(nIndex < nItemCount);

	if (nIndex >= nItemCount)
	{
		return FALSE;
	}

	long nActivePageIndex = GetActiveIndex();

	//当前页为删除页
	if (nActivePageIndex == nIndex)
	{
		//删除当前Page页面
		m_pActivePage->ShowWindow(SW_HIDE);
		m_pActivePage->OnKillActive();
		DeleteItem(nIndex);

		//删除Page对象
		m_listPages.DeleteAt(nIndex);

		//重新设置当前页
		nActivePageIndex--;

		if (nActivePageIndex >= 0)
		{
			m_pActivePage = GetPage(nActivePageIndex);
			ASSERT(m_pActivePage != NULL);
			m_pActivePage->OnSetActive();
			m_pActivePage->ShowWindow(SW_SHOW);
			SetCurSel(nActivePageIndex);
		}
		else
		{
			m_pActivePage = GetPage(0);

			if (m_pActivePage == NULL)
			{
				return FALSE;
			}
			else
			{
				m_pActivePage->OnSetActive();
				m_pActivePage->ShowWindow(SW_SHOW);
				SetCurSel(0);
			}
		}
	}
	else//当前页不是删除页，直接删除
	{
		DeleteItem(nIndex);
		m_listPages.DeleteAt(nIndex);
		Invalidate(FALSE);
	}

	return TRUE;
}

void CDialogSheet::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT (m_pActivePage != NULL);

	if (m_pActivePage != NULL)
	{
		m_pActivePage->ShowWindow(SW_HIDE);
		m_pActivePage->OnKillActive();
	}

	//显示当前选中页面
	int nIndex = GetCurSel();
	TCITEM item;
    item.mask = TCIF_PARAM;
	GetItem(nIndex, &item);
	
	m_pActivePage = (CDialogPage*)item.lParam;
	ASSERT (m_pActivePage != NULL);

	if (m_pActivePage != NULL)
	{
		m_pActivePage->ShowWindow(SW_SHOW);
		m_pActivePage->OnSetActive();
	}

	*pResult = 0;
}

 CDialogPage *CDialogSheet::GetActivePage()const
{
	ASSERT_VALID(this);

	ASSERT (m_pActivePage != NULL);
	
	return m_pActivePage;
	
}
 int CDialogSheet::GetActiveIndex()const
 {
	 return GetCurSel();
 }

 CDialogPage *CDialogSheet::GetPage(int nPage)const
 {
	 CDialogPage *pPage = m_listPages.GetAt(nPage);
	 return pPage;
 }

 int CDialogSheet::GetPageIndex(CDialogPage *pPage)
 {
	 POS pos = m_listPages.Find(pPage);
	 long nIndex = m_listPages.FindIndex(pos);

	 return nIndex;
 }

 BOOL CDialogSheet::SetActivePage(int nPage)
 {
	 long nItemCount = GetItemCount() ;
	 long nCount = m_listPages.GetCount();

	 ASSERT (nItemCount == nCount);

	 if (nCount == 0)
	 {
		 return FALSE;
	 }

	 if (nCount <= nPage)
	 {
		 return FALSE;
	 }

	 CDialogPage *pPage = m_listPages.GetAtIndex(nPage);

	 if (m_pActivePage == pPage)
	 {
		 m_pActivePage->OnSetActive();
		 m_pActivePage->ShowWindow(SW_SHOW);
		 return TRUE;
	 }
	 else 
	 {
		 if (m_pActivePage != NULL)
		 {
			 SetCurSel(nPage);
			 m_pActivePage->OnKillActive();
			 m_pActivePage->ShowWindow(SW_HIDE);

			 m_pActivePage = pPage;
			 m_pActivePage->OnSetActive();
			 m_pActivePage->ShowWindow(SW_SHOW);
		 }
		 else
		 {
			 m_pActivePage = pPage;
			 m_pActivePage->OnSetActive();
			 pPage->ShowWindow(SW_SHOW);
		 }
	 }

	return TRUE;
 }

 BOOL CDialogSheet::SetActivePage(CDialogPage *pPage)
 {
	 if(pPage == NULL)
		 return FALSE;

	 int nIndex = GetPageIndex(pPage);
	 SetActivePage(nIndex);

	 return TRUE;

 }

 void CDialogSheet::AddPage(CDialogPage *pPage)
 {
	 AddTab(pPage, GetItemCount());
	 m_listPages.AddTail(pPage);
 }

 void CDialogSheet::DeletePage(int nPage)
 {	
	 DeleteTab(nPage); 
	 //m_listPages.DeleteAt(nPage);
 }

 void CDialogSheet::DeletePage(CDialogPage *pPage)
 {
	 int nPage = GetPageIndex(pPage);
	 ASSERT(nPage >= 0);

	 DeletePage(nPage);
 }

 void CDialogSheet::InsertBefore(CDialogPage *pInsertPage,CDialogPage *pPage)
 {
	 long nIndex = 0;
	 nIndex = GetPageIndex(pPage);
	 InsertBefore(pInsertPage, nIndex);
 }

 void CDialogSheet::InsertBefore(CDialogPage *pPage, int nIndex)
 {
	 POS pos = m_listPages.FindIndex(nIndex);
	 m_listPages.InsertBefore(pos, pPage);
	 AddTab(pPage, nIndex);
 }

 void CDialogSheet::InsertAfter(CDialogPage *pPage,int nIndex)
 {
	 POS pos = m_listPages.FindIndex(nIndex);
	 m_listPages.InsertAfter(pos,pPage);
	 AddTab(pPage,nIndex + 1);
 }

 void CDialogSheet::InsertAfter(CDialogPage *pInsertPage,CDialogPage *pPage)
 {
	 long nIndex = GetPageIndex(pPage);
	 InsertAfter(pInsertPage,nIndex);
 }

 void CDialogSheet::SetTitle(const CString &strTitle, long nPage)
 {
	 CDialogPage *pPage = m_listPages.GetAt(nPage);
	 TCITEM item;
	
	 item.mask = TCIF_TEXT;
#ifdef UNICODE
	 item.pszText = strTitle.AllocSysString();
#else
	// item.pszText = strTitle.AllocSysString();
#endif
	 SetItem(nPage, &item);
	 pPage->m_strCaption = strTitle;
 }

 void CDialogSheet::SetTitle(const CString &strTitle, CDialogPage *pPage)
 {
	 long nIndex = GetPageIndex(pPage);
	 TCITEM item;
	 
	 item.mask = TCIF_TEXT;
#ifdef UNICODE
	 item.pszText = strTitle.AllocSysString();
#else
	// item.pszText = strTitle.AllocSysString();
#endif
	 SetItem(nIndex,&item);
	 pPage->m_strCaption = strTitle;
 }

 void CDialogSheet::SetPagePostion(CDialogPage *pPage)
 {
	 /*CRect rc;
	 pPage->GetWindowRect(&rc);
	 CRect rcPage(0, 0, rc.Width(), rc.Height());
	 CRect rcItem;
	 GetItemRect(0, &rcItem);
	 int nHeight = ::GetSystemMetrics(SM_CYFRAME  );
	 rcPage.OffsetRect(2, rcItem.Height()+nHeight);
	 pPage->MoveWindow(rcPage, FALSE);*/
	 CRect rectTab, rectItem;
	 int nLeft, nTop, nWidth, nHeight;

	 GetClientRect(&rectTab);
	 GetItemRect(0, &rectItem);
	 nLeft=rectItem.left;
	 nTop=rectItem.bottom+1;
	 nWidth=rectTab.right-nLeft-2;
	 nHeight=rectTab.bottom-nTop-2;
	 pPage->SetWindowPos(&wndTop, nLeft, nTop, nWidth, nHeight, SWP_HIDEWINDOW);
 }
 void CDialogSheet::DeleteAll()
 {
	 m_listPages.DeleteAll();
	 DeleteAllItems();
	 m_pActivePage = NULL;
 }
 void CDialogSheet::OnSize(UINT nType, int cx, int cy)
 {
	 __super::OnSize(nType, cx, cy);

	 if (!::IsWindow(m_hWnd))
	 {
		 return;
	 }

	 CDialogPage *pPage = NULL;

	 POS pos = m_listPages.GetHeadPosition();

	 while (pos != NULL)
	 {
		pPage = (CDialogPage *)m_listPages.GetNext(pos);
		ASSERT(pPage != NULL);

		if (::IsWindow(pPage->m_hWnd))
		{
			SetPagePostion(pPage);
		}
	 }
 }
