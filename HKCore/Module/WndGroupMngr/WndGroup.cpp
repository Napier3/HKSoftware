#include "StdAfx.h"
#include "WndGroup.h"

//////////////////////////////////////////////////////////////////////////
//CWndGroup::CWndRef
CWndGroup::CWndRef::CWndRef(CWnd *pWnd)
{
	m_pWnd = pWnd;
	pWnd->GetWindowRect(m_rcOrigin);
	CWnd *pParent = pWnd->GetParent();
	pParent->ScreenToClient(&m_rcOrigin);
	m_rcCurr = m_rcOrigin;
	m_bShow = TRUE;
	
}

CWndGroup::CWndRef::~CWndRef()
{
	if (m_pWnd != NULL)
	{
		//m_pWnd->DestroyWindow();
		delete m_pWnd;
		m_pWnd = NULL;
	}
}

CRect CWndGroup::CWndRef::Resize(CRect rect)
{
	ASSERT(m_pWnd!=NULL);
	m_pWnd->MoveWindow(rect);
	m_pWnd->GetWindowRect(m_rcOrigin);
	CWnd *pParent = m_pWnd->GetParent();
	pParent->ScreenToClient(&m_rcOrigin);
	m_rcCurr = m_rcOrigin;
	m_bShow = TRUE;
	return rect;
}

void CWndGroup::CWndRef::Show(BOOL bShow)
{
	ASSERT (m_pWnd != NULL);
	m_bShow = bShow;

	if (m_bShow)
	{
		m_pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pWnd->ShowWindow(SW_HIDE);
	}
}

void CWndGroup::CWndRef::Move(long nXOffset, long nYOffset)
{
	ASSERT (m_pWnd != NULL);

	m_rcCurr = m_rcOrigin;
	//m_rcCurr.OffsetRect(nXOffset, nYOffset);
	m_pWnd->MoveWindow(m_rcCurr, TRUE);
}

//////////////////////////////////////////////////////////////////////////
//CWndGroup
CWndGroup::CWndGroup(CWndGroupFrame *pWnd, const CString &strTitle, long nGroupID)
{
	ASSERT(pWnd != NULL);
	m_strGroupTitle = strTitle;
	m_pWndFrame = pWnd;
	m_pWndFrame->m_strTitle = strTitle;
	m_nGroupID = nGroupID;

	m_bExpand = TRUE;
	m_bExpandChanged = FALSE;
	m_pWndFrame->m_nFrameIndex = nGroupID;

	m_rcCurWndRef.SetRect(0,0,0,0);
	m_nBtnWidth = 130;//按钮宽度
	m_nBtnHeight = 30;//按钮高度
	m_nBtnHGap = 20;//按钮横向间隔
	m_nBtnVGap = 10;//按钮纵向间隔
	InitWindowRect();

	m_nAddlength = 0;
	m_bResize = TRUE;
}

CWndGroup::~CWndGroup(void)
{
	DeleteAll();
}


CSize CWndGroup::SetExpandFlag(BOOL bExpand)
{
	ASSERT(m_pWndFrame != NULL);
	CSize sz(0,0);

	m_pWndFrame->m_bExpand = bExpand;

	if (m_bExpand != bExpand)
	{
		m_bExpand = bExpand;
		m_bExpandChanged = TRUE;
	}

	if (m_bExpandChanged)
	{
		CWndRef *pParaWnd = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pParaWnd = (CWndRef*)GetNext(pos);
			pParaWnd->Show(m_bExpand);
		}

		sz.cx = m_pWndFrame->m_rcFrame.Width();
		sz.cy = m_pWndFrame->m_rcOrigin.Height() - m_pWndFrame->m_rcFrame.Height();
		m_bExpandChanged = FALSE;
		//Modefied by hqy
		//保存最后一个group的矩形；
		CRect rect = m_pWndFrame->AdjustWndRect();
		m_rcCurr = rect;
	}
	

	return sz;
}

void CWndGroup::Move(long nXOffset, long nYOffset)
{
	ASSERT (m_pWndFrame != NULL);

	//m_rcCurr = m_rcOrigin;
	m_rcCurr.OffsetRect(nXOffset, nYOffset);
	m_pWndFrame->MoveWindow(m_rcCurr, TRUE);
	//m_pWndFrame->InitAll();
	//m_pWndFrame->Move(m_rcCurr, m_bExpand);
	//m_rcCurr = m_pWndFrame->GetFrameRect();

	TRACE("Move %d: rcCurr(%d,%d,%d,%d)\n", m_nGroupID, m_rcCurr.left, m_rcCurr.top, m_rcCurr.right, m_rcCurr.bottom);	

	//if (m_bExpand) //展开时，改变参数窗口的位置
	{
		CWndRef *pParaWnd = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pParaWnd = (CWndRef*)GetNext(pos);
			pParaWnd->Move(nXOffset, nYOffset);
			pParaWnd->m_pWnd->Invalidate(TRUE);
		}
	}
	m_pWndFrame->Invalidate(TRUE);
}

void CWndGroup::Move(const CRect &rcBorder)
{
	m_pWndFrame->MoveWindow(rcBorder, TRUE);
	InitWindowRect();
}

void CWndGroup::CreateParaWnd(CWnd *pWnd)
{
	CWndRef *pParaWnd = new CWndRef(pWnd);
	AddTail(pParaWnd);
}

void CWndGroup::GetParaWndGroupSize(CSize &size)
{
	ASSERT(m_pWndFrame != NULL);

	if (m_bExpand)
	{
		size.cx = m_pWndFrame->m_rcFrame.Width();
		size.cy = m_pWndFrame->m_rcFrame.Height();
	}
	else
	{
		size.cx = m_pWndFrame->m_rcOrigin.Width();
		size.cy = m_pWndFrame->m_rcOrigin.Height();		
	}
}

void CWndGroup::GetParaWndGroupSize(long &nWidth, long nHeight)
{
	ASSERT(m_pWndFrame != NULL);

	m_rcOrigin = m_pWndFrame->m_rcOrigin;

	if (m_bExpand)
	{
		nWidth = m_pWndFrame->m_rcFrame.Width();
		nHeight = m_pWndFrame->m_rcFrame.Height();
		m_rcCurr = m_pWndFrame->m_rcFrame;
	}
	else
	{
		nWidth = m_pWndFrame->m_rcOrigin.Width();
		nHeight = m_pWndFrame->m_rcOrigin.Height();		
		m_rcCurr = m_pWndFrame->m_rcOrigin;
	}
}

CRect CWndGroup::GetWndFrameRect()
{
	CRect rc;
	m_pWndFrame->GetWindowRect(rc);
	return rc;
}

void CWndGroup::ExpandY(long nHeightExpand)  
{  
	m_rcCurr.bottom += nHeightExpand; 
	Move(0,0);
}

void CWndGroup::InitWindowRect()
{
	CWnd *pParent = m_pWndFrame->GetParent();
	ASSERT(pParent != NULL);
	m_pWndFrame->GetWindowRect(m_rcOrigin);
	pParent->ScreenToClient(&m_rcOrigin);
	m_rcCurr = m_rcOrigin;
}

LONG CWndGroup::Resize(CRect rect)
{
	m_nAddlength = 0;
	BOOL bExpand = m_bExpand;
	SetExpandFlag(TRUE);
	m_pWndFrame->Resize(rect);
	m_bResize = TRUE;
	CWndRef* pWndRef = NULL;
	CRect rectRef ;
	for (int i=0;i<GetCount();i++)
	{
		pWndRef = (CWndRef*)GetAt(i);
		rectRef = GetnextWndRefRect();
		pWndRef->Resize(rectRef);
	}
	InitWindowRect();
	if (!bExpand)
	{
		SetExpandFlag(FALSE);
	}
	return m_nAddlength;
}

CRect CWndGroup::GetnextWndRefRect()
{
	CRect rcFrame;
	CWndGroupFrame* pGroupFrame = GetWndFrame();
	pGroupFrame->GetClientRect(&rcFrame);
	CRect rcWndRef = m_rcCurWndRef;

	if (m_bResize)
	{
		rcWndRef.left = pGroupFrame->GetLeftGap();
		rcWndRef.top = CWndGroupFrame::GetTitleHeight() + 12;
		rcWndRef.bottom = rcWndRef.top + m_nBtnHeight;
		rcWndRef.right = rcWndRef.left + m_nBtnWidth;
		m_bResize = FALSE;
	}
	else
	{
		rcWndRef.left = rcWndRef.right + m_nBtnHGap;
		rcWndRef.right = rcWndRef.left + m_nBtnWidth;
		if (rcWndRef.right>(rcFrame.right-pGroupFrame->GetLeftGap()))//横向超范围，需换行
		{
			rcWndRef.left = pGroupFrame->GetLeftGap();
			rcWndRef.top = rcWndRef.bottom + m_nBtnVGap;
			rcWndRef.bottom = rcWndRef.top + m_nBtnHeight;
			rcWndRef.right = rcWndRef.left + m_nBtnWidth;
			//判断是否超出Group范围，增加Group纵向高度。
			if (rcWndRef.bottom>(rcFrame.bottom - m_nBtnVGap))
			{
				AddGroupHeight();
			}
		}
	}
	m_rcCurWndRef = rcWndRef;
	return rcWndRef;
}

void CWndGroup::AddGroupHeight()
{
	m_nAddlength += (m_nBtnHeight + m_nBtnVGap);
}