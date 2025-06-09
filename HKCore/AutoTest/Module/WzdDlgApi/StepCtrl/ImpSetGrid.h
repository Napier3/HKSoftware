#pragma once

#include "WzdDlgStyleGrid.h"
#include "../../GuideBook/DataSet.h"

class CImpSetGrid : public CWzdDlgStyleGrid
{
public:
	CDataSet* m_pDataset;
	CDvmDataset *m_pDvmDataset;

public:
	CImpSetGrid();
	virtual ~CImpSetGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void CalMD5(CString& strMD5);
	static void EndEditCell_String(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
};