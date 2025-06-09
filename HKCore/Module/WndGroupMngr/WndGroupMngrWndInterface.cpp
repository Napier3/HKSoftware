#include "StdAfx.h"
#include "WndGroupMngrWndInterface.h"

CWndGroupMngrWndInterface::CWndGroupMngrWndInterface(void)
{
	m_pOwnWnd = NULL;
	m_nItemData = 0;
}

CWndGroupMngrWndInterface::~CWndGroupMngrWndInterface(void)
{
	DeleteAll();
}

CWndGroup* CWndGroupMngrWndInterface::AddNewGroup(CWndGroupFrame* pFrame, const CString &strTitle, long nGroupID)
{
	CWndGroup *pGroup = new CWndGroup(pFrame, strTitle, nGroupID);
	AddTail(pGroup);
	return pGroup;
}

//调整参数对话框组的位置
CSize CWndGroupMngrWndInterface::AdjustAllWndGroup(long nGroupID, BOOL bExpand)
{
	POS pos = GetHeadPosition();
	CWndGroup *pGroup = NULL;
	CWndGroup *pFind = NULL;
	void*      posBegin = NULL;
	CSize sz;

	pos = FindIndex(nGroupID);
	if (pos != NULL)
	{
		pGroup = (CWndGroup*)GetAt(pos);
		pFind = pGroup;
		sz = pGroup->SetExpandFlag(bExpand);
	}

	//sz等于0的情况:改变大小的
	if (sz.cx == 0 && sz.cy == 0)
	{
		return sz;
	}

	//调整分组下面的分组窗口位置
	if (pFind != NULL)
	{
		long nXOffset = 0;
		long nYOffset = 0;

		if (bExpand)
		{
			nXOffset = 0;//sz.cx;
			nYOffset = sz.cy;
		}
		else
		{
			nXOffset = 0;//-sz.cx;
			nYOffset = -sz.cy;
		}

		long nIndex = 0;
		long nCount = GetCount();

		for (nIndex=nGroupID+1; nIndex<nCount; nIndex++)
		{
			pos = FindIndex(nIndex);
			pGroup = (CWndGroup*)GetAt(pos);
			pGroup->Move(nXOffset, nYOffset);
		}
	}
	m_pOwnWnd->Invalidate(TRUE);
	return sz;
}

//调整参数对话框组的位置
CSize CWndGroupMngrWndInterface::AdjustAllWndGroup(CWndGroupMngrWndInterface *pSynMacroDlg)
{
	CSize sz(0,0);

	long nIndex = 0;
	long nCount = pSynMacroDlg->GetCount();
	CWndGroup *pSrc = NULL;
	CWndGroup *pDst = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pSrc = pSynMacroDlg->GetAt(nIndex);
		pDst = GetAt(nIndex);
		AdjustAllWndGroup(pSrc->m_nGroupID, pSrc->IsExpand());
	}

	return sz;
}


CSize CWndGroupMngrWndInterface::Move(long nXOffset, long nYOffset)
{
	ASSERT (m_pOwnWnd != NULL);

	CSize sz;
	CRect rc;
	GetMngrWndRect(rc);
	sz.cx = rc.Width();
	sz.cy = rc.Height();
	rc.top = nYOffset;
	rc.left = nXOffset;
	rc.right = rc.left + sz.cx;
	rc.bottom = rc.top + sz.cy;
	m_pOwnWnd->MoveWindow(rc, TRUE);
	Show();

	return sz;
}

CSize CWndGroupMngrWndInterface::CalSize(long nXOffset, long nYOffset)
{
	ASSERT (m_pOwnWnd != NULL);

	CSize sz;
	CRect rc;
	GetMngrWndRect(rc);
	sz.cx = rc.Width();
	sz.cy = rc.Height();
	//	rc.top = nYOffset;
	//	rc.left = nXOffset;
	//	rc.right = rc.left + sz.cx;
	//	rc.bottom = rc.top + sz.cy;
	//	m_pOwnWnd->MoveWindow(rc, TRUE);
	//	Show();

	return sz;
}

void CWndGroupMngrWndInterface::GetMngrWndRect(CRect &rc)
{
	ASSERT (m_pOwnWnd != NULL);

	long nIndex = 0;
	long nCount = GetCount();
	CWndGroup *pGroup = NULL;
	POS      pos = NULL;
	long nHeight = 0;
	m_pOwnWnd->GetWindowRect(&rc);
	CRect rcGroup;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pos = FindIndex(nIndex);
		pGroup = (CWndGroup*)GetAt(pos);

		rcGroup = pGroup->GetWndGroupRect();

		if (pGroup->IsExpand())
		{
			nHeight = max(nHeight, rcGroup.bottom);
		}
		else
		{
			nHeight = max(nHeight, rcGroup.bottom - pGroup->GetFrameGap());
		}
	}

	rc.bottom = rc.top + nHeight + 6;
}
