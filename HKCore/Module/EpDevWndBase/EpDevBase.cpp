#include "stdafx.h"
#include "EpDevBase.h"


//UINT  CEpDevBase::g_nWindowID = 5000;

CEpDevBase::CEpDevBase()
{
	m_pData = NULL;		
	m_pWindow = NULL;

	m_bExpand = TRUE;
	m_nShow = EPDES_SHOW;
	m_nTop = 0;
	m_nLeft = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nDataClassID = 0;
}

CEpDevBase::~CEpDevBase()
{
	
}

long CEpDevBase::AdjustPos(long nLeft,long nTop)
{
	AdjustChildrenPos(nLeft, nTop);
	AdjustOwnPos(nLeft, nTop);

	return 0;
}

long CEpDevBase::AdjustOwnPos(long nLeft,long nTop)
{
	return 0;
}

void CEpDevBase::Show(UINT nShow)
{
	ASSERT(m_pWindow != NULL);
	m_nShow = nShow;	

	if(m_nShow == EPDES_SHOW)
	{
			m_pWindow->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pWindow->ShowWindow(SW_HIDE);
	}

	ShowChildren(nShow);
}

BOOL CEpDevBase::UICreate(CWnd *pParent)
{
	UICreateOwn(pParent);
	InitPpPos();
	UICreateOwnAttr(pParent);
	ShowData(m_pData);
	UICreateChildren(pParent);

	return TRUE;
}

BOOL CEpDevBase::UICreateOwnAttr(CWnd *pParent)
{
	return TRUE;
}

BOOL CEpDevBase::UICreateOwn(CWnd *pParent)
{
	return TRUE;
}

BOOL CEpDevBase::Destroy()
{
	if (!DestroyChildren())
	{
		return FALSE;
	}

	if (!DestroyOwn())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpDevBase::DestroyOwn()
{
	if (m_pWindow != NULL)
	{
		m_pWindow->DestroyWindow();
	}

	m_pWindow = NULL;

	return TRUE;
}

BOOL CEpDevBase::IsDevWndCreated()
{
	if (m_pWindow == NULL)
	{
		return FALSE;
	}

	return ::IsWindow(m_pWindow->m_hWnd);
}

long CEpDevBase::Expand(long nExpand)
{
	return 0;
}

void CEpDevBase::InitPpPos()
{
	ASSERT(m_pWindow != NULL);

	CRect rcClient;
	m_pWindow->GetWindowRect(rcClient);
	CWnd* pParent = m_pWindow->GetParent();
	pParent->ScreenToClient(rcClient);
	m_nHeight = rcClient.Height();
	m_nWidth = rcClient.Width();
	m_nLeft = rcClient.left;
	m_nTop = rcClient.top;
}

