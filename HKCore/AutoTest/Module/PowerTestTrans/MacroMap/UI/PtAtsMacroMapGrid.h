#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"

#define WM_OPEN_MACROMAPOBJ  (WM_USER + 2115)

class CPtAtsMacroMapGrid : public CExBaseListGrid
{
public:
	CPtAtsMacroMapGrid();
	virtual ~CPtAtsMacroMapGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	void AttachMsgRcvWnd(CWnd *pWnd)			{	m_pMsgRcvWnd = pWnd;	}

protected:
	CWnd *m_pMsgRcvWnd;

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual BOOL UpdateData(CExBaseObject *pData);
	virtual void OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
};


