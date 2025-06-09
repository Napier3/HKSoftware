#pragma once

#include "..\CfgDataMngr\IecCfg92Data.h"
#include "IecCfgSmvDataChsGridBase.h"


#define IECCFG_COL_ID_92CH_DESC     1
#define IECCFG_COL_ID_92CH_CHTYPE   2
#define IECCFG_COL_ID_92CH_APPCH    3
#define IECCFG_COL_ID_92CH_QUALITY  4
#define IECCFG_COL_ID_92CH_DESCEXTERNAL  5
#define IECCFG_COL_ID_92CH_ADDREXTERNAL  6

#define IECCFG_COLS_92CH            7

class CIecCfgSmvData92ChsGrid : public CIecCfgSmvDataChsGridBase
{
public:
	CIecCfgSmvData92ChsGrid();
	virtual ~CIecCfgSmvData92ChsGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void UpdateQuality(CExBaseObject *pData, const int& nRow);
	void UpdateQuality();
	virtual long GetAppChColIndex()	{	return IECCFG_COL_ID_92CH_APPCH;	}

public:
	virtual BOOL OnCellRButtonUpEx(UINT nFlags, CPoint point);
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);

private:
	BOOL SetQualityValue(int nRow, int nCol);
};

