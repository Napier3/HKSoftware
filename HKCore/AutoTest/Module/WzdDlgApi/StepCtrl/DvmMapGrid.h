#pragma once
#include "WzdDlgStyleGrid.h"
#include "../../../../Module/DataMngr/DvmCmp/DvmDeviceMap.h"

class CDvmMapGrid : public CWzdDlgStyleGrid
{
public:
	CDvmMapGrid();
	virtual ~CDvmMapGrid() {}

	void InitGrid();
	void InitGridTitle();

	void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow =TRUE);
	virtual void Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString);
	virtual void LButtonDblClk(UINT nFlags, CPoint point);
	virtual void RButtonUp(UINT nFlags, CPoint point);
	virtual void RButtonDown(UINT nFlags, CPoint point);

	CDvmDatasetMap* AddDatasetMap(CDvmDataset *pDestDataset, BOOL bNewStandDataset = FALSE);
};