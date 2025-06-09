#include "stdafx.h"
#include "WzdDlgList.h"

IMPLEMENT_DYNAMIC(CWzdDlgList, CDialog)
BEGIN_MESSAGE_MAP(CWzdDlgList, CDialog)
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()
CWzdDlgList::CWzdDlgList(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CWzdDlgList::IDD, pParent)
{
	
}

CWzdDlgList::~CWzdDlgList()
{
	for (int i =0; i < m_listItems.size(); i++)
	{
		delete m_listItems[i];
	}
}

CWzdDlgButton* CWzdDlgList::AddNewItem(const CString& strText)
{
	CRect rcItem(0, 0, 0, 0);
	CWzdDlgButton* pBtn = new CWzdDlgButton;
	BOOL nRes = pBtn->Create(strText, WS_CHILD | WS_VISIBLE, rcItem, this, IDD + m_listItems.size() + 1);
	if(nRes)
	{
		m_listItems.push_back(pBtn);
	}
	else
	{
		delete pBtn;
		pBtn = NULL;
	}
	return pBtn;
}

void CWzdDlgList::SetItemData(long nIndex, void* pData)
{
	CWzdDlgButton* pBtn = m_listItems.at(nIndex);
	pBtn->SetItemData(pData);
}

void* CWzdDlgList::GetItemData(long nIndex)
{
	CWzdDlgButton* pBtn = m_listItems.at(nIndex);
	return pBtn->GetItemData();
}

void CWzdDlgList::CalItemsRect()
{
	CRect rc;
	GetClientRect(rc);

	long nVisible = GetVisibleCount();
	long nWidth = rc.Width();
	//long nHeight = rc.Height() / nVisible + 1;
	long nHeight = 60;
	
	nVisible = 0;
	for (int i = 0; i < m_listItems.size(); i++)
	{
		if(m_listItems[i]->IsVisible())
		{
			m_listItems[i]->SetWindowPos(NULL, 0, nHeight * nVisible, nWidth, nHeight, SWP_SHOWWINDOW);
			nVisible++;
		}
	}
}

void CWzdDlgList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CWzdDlgList::SetCurSel(long nIndex)
{
	if(nIndex < m_listItems.size() && nIndex >= 0)
	{
		for (int i = 0; i < m_listItems.size(); i++)
		{
			m_listItems[i]->SetHold(false);
		}

		m_listItems[nIndex]->SetHold(true);
	}

	RedrawWindow();
}

long CWzdDlgList::SetCurSel(CWnd* pWnd)
{
	long nIndex = 0;
	if(pWnd)
	{
		for (int i = 0; i < m_listItems.size(); i++)
		{
			if(m_listItems[i] == pWnd)
			{
				m_listItems[i]->SetHold(true);
				nIndex = i;
			}
			else
			{
				m_listItems[i]->SetHold(false);
			}
		}
		RedrawWindow();
	}
	return nIndex;
}

void CWzdDlgList::EnableItem(long nIndex, BOOL bEnabled)
{
	if(nIndex >=0 && nIndex < m_listItems.size())
	{
		m_listItems[nIndex]->SetEnabled(bEnabled);
		m_listItems[nIndex]->RedrawWindow();
	}
}

void CWzdDlgList::SetItemVisible(long nIndex, BOOL bVisible)
{
	if(nIndex >=0 && nIndex < m_listItems.size())
	{
		m_listItems[nIndex]->SetVisible(bVisible);
		m_listItems[nIndex]->ShowWindow(bVisible);
	}	
}

CWzdDlgButton* CWzdDlgList::FindBtnByID(const CString& strID)
{
	for (int i = 0; i < m_listItems.size(); i++)
	{
		if(m_listItems[i]->m_strID == strID)
		{
			return m_listItems[i];
		}
	}
	return 0;
}

void CWzdDlgList::EnableItem(const CString& strID, BOOL bEnabled)
{
	CWzdDlgButton* pBtn = FindBtnByID(strID);
	if(pBtn)
	{
		pBtn->SetEnabled(bEnabled);
		pBtn->RedrawWindow();
	}
}

void CWzdDlgList::SetItemVisible(const CString& strID, BOOL bVisible)
{
	CWzdDlgButton* pBtn = FindBtnByID(strID);
	if(pBtn)
	{
		pBtn->SetVisible(bVisible);
		pBtn->ShowWindow(bVisible);
	}
}

long CWzdDlgList::GetVisibleCount()
{
	long nCount = 0;
	for (int i = 0; i < m_listItems.size(); i++)
	{
		if(m_listItems[i]->IsVisible())
		{
			nCount++;
		}
	}
	return nCount;
}

BOOL CWzdDlgList::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	//点击切换的逻辑暂时还没有理清,主要是点击后面的界面时经过的多重判断
// 	if(message == WM_LBUTTONDOWN)
// 	{
// 		CWzdDlgButton* pBtn = (CWzdDlgButton*)pWnd;
// 		if(pBtn->IsEnabled())
// 		{
// 			SetCurSel(pWnd);
// 			m_pParentWnd->SendMessage(WM_STEPLIST_CHANGE, 0, (LPARAM)pWnd);
// 		}
// 	}
	return CWzdDlgBase::OnSetCursor(pWnd, nHitTest, message);
}

void CWzdDlgList::OnPaint()    
{  
	CRect rect;  
	CPaintDC dc(this);  
	GetClientRect(rect);  
	dc.FillSolidRect(rect,RGB(255,255,255));
	CDialog::OnPaint();  
}  