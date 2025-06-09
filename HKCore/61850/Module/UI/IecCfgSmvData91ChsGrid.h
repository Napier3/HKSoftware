#pragma once

#include "..\CfgDataMngr\IecCfg91Data.h"
#include "IecCfgSmvDataChsGridBase.h"


#define IECCFG_COL_ID_91CH_DESC     1
#define IECCFG_COL_ID_91CH_CHTYPE   2
#define IECCFG_COL_ID_91CH_APPCH    3

#define IECCFG_COLS_91CH            4

class CIecCfgSmvData91ChsGrid : public CIecCfgSmvDataChsGridBase
{
public:
	CIecCfgSmvData91ChsGrid();
	virtual ~CIecCfgSmvData91ChsGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void UpdateType(CExBaseObject *pData, const int& nRow);
	void UpdateType();
	virtual long GetAppChColIndex()	{	return IECCFG_COL_ID_91CH_APPCH;	}

};

