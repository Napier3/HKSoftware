#pragma once

#include "..\CfgDataMngr\IecCfg6044Data.h"
#include "IecCfgSmvDataChsGridBase.h"


#define IECCFG_COL_ID_6044CH_DESC     1
#define IECCFG_COL_ID_6044CH_CHTYPE   2
#define IECCFG_COL_ID_6044CH_APPCH    3

#define IECCFG_COLS_6044CH            4

class CIecCfgSmvData6044ChsGrid : public CIecCfgSmvDataChsGridBase
{
public:
	CIecCfgSmvData6044ChsGrid();
	virtual ~CIecCfgSmvData6044ChsGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual long GetAppChColIndex()	{	return IECCFG_COL_ID_6044CH_APPCH;	}

};

