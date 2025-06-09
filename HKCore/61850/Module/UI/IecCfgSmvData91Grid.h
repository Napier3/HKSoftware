#pragma once
#include "IecCfgDataGridBase.h"

#include "..\CfgDataMngr\IecCfg91Data.h"

#define IECCFG_COL_ID_91DATA_DEST_MAC     2
#define IECCFG_COL_ID_91DATA_SRC_MAC      3
#define IECCFG_COL_ID_91DATA_APPID        4

#define IECCFG_COLS_91DATA                14

class CIecCfgSmvData91Grid : public CIecCfgDataGridBase
{
public:
	CIecCfgSmvData91Grid();
	virtual ~CIecCfgSmvData91Grid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);



};

