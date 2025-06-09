#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"

#define WM_XRIOPARASET_DIALOG_OPEN  (WM_USER + 939)

class CTplSettingGrid : public CExBaseListGrid
{
public:
	CTplSettingGrid();
	virtual ~CTplSettingGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual BOOL UpdateData(CExBaseObject *pData);
	//÷ÿ‘ÿ∫Ø ˝
protected: 
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	static void EndEditCell_XrioPara(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	
public:
	void AttachMsgRcvWnd(CWnd *pWnd)			{	m_pMsgRcvWnd = pWnd;	}

protected:
	CWnd *m_pMsgRcvWnd;

	DECLARE_MESSAGE_MAP()

	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};


