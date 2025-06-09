#pragma once
#include "..\..\..\Module\GridBase\ExBaseListGrid.h"

#include "..\CfgDataMngr\IecCfgSmvRates.h"

#define IECCFG_COL_ID_SMVRATE_NAME     1
#define IECCFG_COL_ID_SMVRATE_RATE     2

#define IECCFG_COLS_SMVRATE            3

class CSmvRateGrid : public CExBaseListGrid
{
public:
	CSmvRateGrid();
	virtual ~CSmvRateGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_Value_Precision(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

