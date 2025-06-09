#pragma once

#include "IECCfgSmvDataChsGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"

#define IECCFG_COL_ID_92CH_DESC     1
#define IECCFG_COL_ID_92CH_CHTYPE   2
#define IECCFG_COL_ID_92CH_APPCH    3
#define IECCFG_COL_ID_92CH_QUALITY  4
#define IECCFG_COL_ID_92CH_DESCEXTERNAL  5
#define IECCFG_COL_ID_92CH_ADDREXTERNAL  6

#define IECCFG_COLS_92CH            7

class CIECCfgSmv92ChsGrid : public CIECCfgSmvDataChsGridBase
{
public:
	CIECCfgSmv92ChsGrid();
	virtual ~CIECCfgSmv92ChsGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void UpdateQuality(CExBaseObject *pData, const int& nRow);
	void UpdateQuality();
	virtual long GetAppChColIndex()	{	return IECCFG_COL_ID_92CH_APPCH;	}

public:
	virtual BOOL OnCellRButtonUpEx(UINT nFlags, CPoint point);
	virtual void OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	static void EndEditCellDesc(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

private:
	BOOL SetQualityValue(int nRow, int nCol);
};

