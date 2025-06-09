#pragma once
#include "..\gridbase\ExBaseListGrid.h"
// #include "XMatchToolBase.h"
// #include "XMatchRefObjectSelDlg.h"
// #include "XMatchDatasetSelDlg.h"
#include "XMatchEditDvmSelDlgsBase.h"

#define WM_DVMMAPEDIT_KEY_CHANGED  (WM_USER+1015)

#define XMATCH_GRID_COLS   3
#define XMATCH_GRID_ID_SRC  1
#define XMATCH_GRID_ID_DST  2

class CXMatchEditGridCtrlBase :	public CExBaseListGrid, public CXMatchEditDvmSelDlgsBase
{
public:
	CXMatchEditGridCtrlBase(void);
	virtual ~CXMatchEditGridCtrlBase(void);

public:
	virtual void ShowMatch(CXMatchToolBase *pXMatchTool);

	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void SetMatchRefData(CExBaseObject *pRefObject);
	void SetShowID(BOOL bShowID)				{	m_bShowID = bShowID;				}
	void SetDataSelChangeMsgRcvWnd(CWnd  *pWnd)	{	m_pDataSelChangeMsgRcvWnd = pWnd;	}
	void SetXMatchRefClassID(UINT nXMatchRefClassID) {	m_nXMatchRefClassID = nXMatchRefClassID;	}
// 	CExBaseObject* GetPopSelectData();
	CXMatchObject* GetSelectMatchObject();

protected:
// 	CXMatchToolBase *m_pXMatchTool;
// 
// 	static CXMatchRefObjectSelDlg *m_pMatchedDatasDlg;
// 	static long m_nMatchedDatasDlgRef;
// 
// 	static CXMatchDatasetSelDlg *m_pAllDatasDlg;
// 	static long g_nAllDatasDlgRef;
// 
// 	long m_nShowDataMode;
// 	BOOL m_bShowID;
// 	CWnd *m_pDataSelChangeMsgRcvWnd;
// 	UINT m_nXMatchRefClassID;
// 	BOOL m_bShowMatchDataChanged;

	void Show_XMatchSrc(CXMatchObject *pXMatchObj, const int &nRow, const int &nCol);
	void Show_XMatchDst(CXMatchObject *pXMatchObj, const int &nRow, const int &nCol);


protected:
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	virtual BOOL OnCellRButtonUp(const CCellID &idCell);
	virtual BOOL OnCellKeyDelete(const CCellID &idCell);

// 	virtual void CreateMatchedDatasDlg();
// 	virtual void CreateAllDatasDlg();
// 
// 	virtual void ShowAllDatasToDlg();
// 	virtual void ShowMatchedDatasToDlg();

	virtual void SetMatchRefData(CExBaseObject *pRefObject, const CCellID &idCell);

};
