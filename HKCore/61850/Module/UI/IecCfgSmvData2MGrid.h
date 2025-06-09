#pragma once
#include "IecCfgSmvData6044CommonGrid.h"

#define IECCFG_COLS_2M                  7

class CIecCfgSmvData2MGrid : public CIecCfgSmvData6044CommonGrid
{
public:
	CIecCfgSmvData2MGrid();
	virtual ~CIecCfgSmvData2MGrid();
	virtual void InitGrid();
	virtual void InitGridTitle();
	
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

