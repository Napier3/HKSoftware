#pragma once
#include "IecCfgDataGridBase.h"

#include "..\CfgDataMngr\IecCfg6044Data.h"

#define IECCFG_COL_ID_6044DATA_LDNAME         2
#define IECCFG_COL_ID_6044DATA_LNNAME         3
#define IECCFG_COL_ID_6044DATA_DATASETNAME    4
#define IECCFG_COL_ID_6044DATA_DELAYTIME      5

#define IECCFG_COLS_6044DATA                  11

class CIecCfgSmvData6044Grid : public CIecCfgDataGridBase
{
public:
	CIecCfgSmvData6044Grid();
	virtual ~CIecCfgSmvData6044Grid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);



};

