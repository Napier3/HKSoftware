#pragma once
#include "..\..\..\..\Module\GridCtrl\GridCtrl.h"
#include "GbtDataBatchValueRangeRamp.h"

class CGbtDataBatchValueRangeRampGrid :	public CGridCtrl
{
public:
	CGbtDataBatchValueRangeRampGrid(void);
	virtual ~CGbtDataBatchValueRangeRampGrid(void);


public:
	virtual void ShowGbtDataBatchValueRangeRamp(CGbtDataBatchValueRangeRamp *pGbtDataBatchValueRangeRamp);

	virtual void InitExGrid();
	virtual void InitGridTitle();

protected:
	CGbtDataBatchValueRangeRamp *m_pGbtDataBatchValueRangeRamp;
	void ShowGbtDataTraverseObj(CGbtDataTraverseObj *pGbtDataTraverseObj, int &nRowIndex);
	void UpdateGbtDataTraverseObj(CGbtDataTraverseObj *pGbtDataTraverseObj, int &nRowIndex);

	static void EndEdit_ModelType(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEdit_BeginVal(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEdit_Step(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEdit_Steps(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	void SetSteps(long nSteps);
};
