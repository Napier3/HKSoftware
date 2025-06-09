#pragma once
#include "..\..\..\..\Module\GridCtrl\GridCtrl.h"
#include "GbtBatchDatasetTraverse.h"

class CGbtDataTraverseObjGrid :	public CGridCtrl
{
public:
	CGbtDataTraverseObjGrid(void);
	virtual ~CGbtDataTraverseObjGrid(void);

public:
	virtual void ShowGbtDataTraverse(CGbtBatchDatasetTraverse *pGbtBatchDatasetTraverse);

	virtual void InitExGrid();
	virtual void InitGridTitle();

protected:
	CGbInsertStxmlFile *m_pGbInsertStxmlFile;
	CGbtBatchDatasetTraverse *m_pBatchDatasetTraverse;
	long m_nShowDataMode;
	CWnd *m_pDataSelChangeMsgRcvWnd;

	void ShowGbtDataTraverseObj(CGbtDataTraverseObj *pGbtDataTraverseObj, int &nRowIndex);
	void UpdateGbtDataTraverseObj(CGbtDataTraverseObj *pGbtDataTraverseObj, int &nRowIndex);

	static void EndEdit_ModelType(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEdit_BeginVal(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEdit_Step(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	//Ìî³äcomboList cell
	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);

};
