#pragma once
#include "..\..\..\..\Module\GridCtrl\GridCtrl.h"
#include "GbtDataBatchSclChMap.h"
#include "..\..\..\..\Module\KeyDb\XMatchRefObjectSelDlg.h"
#include "..\..\..\..\Module\KeyDb\XMatchDatasetSelDlg.h"
#include "..\..\..\..\Module\GridBase\ExBaseListGrid.h"

#define WM_MAPEDIT_OBJ_CHANGED  (WM_USER+1015)

class CGbtDataBatchSclChMapGrid :	public CExBaseListGrid, public CXMatchRefObjectSelEdit
{
public:
	CGbtDataBatchSclChMapGrid(void);
	virtual ~CGbtDataBatchSclChMapGrid(void);

	virtual void SetMatchRefData(CExBaseObject *pRefObject);
	void SetXMatchRefClassID(UINT nXMatchRefClassID) {	m_nXMatchRefClassID = nXMatchRefClassID;	}
	void SetDataSelChangeMsgRcvWnd(CWnd  *pWnd)	{	m_pDataSelChangeMsgRcvWnd = pWnd;	}

public:
	virtual void ShowGbtDataBatchSclChMap(CGbtDataBatchSclChMapGen *pGbtDataBatchSclChMapGen);
	virtual void ShowData(CExBaseObject *pExData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	virtual BOOL OnCellRButtonUp(const CCellID &idCell);
	virtual BOOL OnCellKeyDelete(const CCellID &idCell);

	virtual void InitGrid();
	virtual void InitGridTitle();
	CXMatchToolBase* GetMatchTool()	{	return m_pXMatchTool;	}
	void ShowXMatchRefObjectSelDlgDatas(long nRowIndex);

protected:
	CGbtDataBatchSclChMapGen *m_pGbtDataBatchSclChMapGen;
	void ShowGbtDataTraverseObj(CGbtDataBatchSclChMap *pGbtDataTraverseObj, int &nRowIndex);
	void UpdateGbtDataTraverseObj(CGbtDataBatchSclChMap *pGbtDataTraverseObj, int &nRowIndex);

	static void EndEdit_ModelType(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEdit_BeginVal(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEdit_Step(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	virtual void SetMatchRefData(CExBaseObject *pRefObject, const CCellID &idCell);

	virtual void SetMatchRefData(CExBaseObject *pRefObject, int nRowIndex, int nDataIndex);

protected:
	static CXMatchRefObjectSelDlg *m_pXMatchRefObjectSelDlg;
	static long m_nXMatchRefObjectSelDlgRef;

	static CXMatchDatasetSelDlg *m_pXMatchDatasetSelDlg;
	static long g_nXMatchDatasetSelDlgRef;
	UINT m_nXMatchRefClassID;
	CXMatchToolBase *m_pXMatchTool;
	CWnd *m_pDataSelChangeMsgRcvWnd;

	void ShowXMatchRefObjectSelDlgDatas(CGbtDataBatchSclChMap *pSclChMap);
	void ShowXMatchRefObjectSelDlgDataset();
	void GetMapDvmDataNameString(CGbtDataBatchSclChMap *pGbtDataTraverseObj, CString &strText);
};
