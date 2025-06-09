#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "PtAtsParaMapGrid.h"

#define WM_MAP_PTATSPARA  (WM_USER + 1124)

//class CPtAtsMacroMapView;
class CPtAtsVmParaGrid : public CExBaseListGrid
{
public:
	CPtAtsVmParaGrid();
	virtual ~CPtAtsVmParaGrid();

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

public:

};


