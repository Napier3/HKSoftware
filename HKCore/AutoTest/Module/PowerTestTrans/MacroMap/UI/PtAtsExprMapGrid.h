#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "..\MacroMap.h"

#define WM_SHOW_EXPRCAL  (WM_USER + 1436)

class CPtAtsExprMapGrid : public CExBaseListGrid
{
public:
	CPtAtsExprMapGrid();
	virtual ~CPtAtsExprMapGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

	void AttachMsgRcvWnd(CWnd *pWnd)			{	m_pMsgRcvWnd = pWnd;	}

protected:
	CWnd *m_pMsgRcvWnd;

protected:

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual BOOL UpdateData(CExBaseObject *pData);
	virtual void SetMidifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};


