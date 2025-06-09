#pragma once
#include "IecCfgSmvData6044CommonGrid.h"

#define IECCFG_COL_ID_6044DATAIN_COMMON_PORT          2
#define IECCFG_COL_ID_6044DATAIN_COMMON_CHNUM         3
#define IECCFG_COL_ID_6044DATAIN_COMMON_SMPBYTENUM    4
#define IECCFG_COL_ID_6044DATAIN_COMMON_SMPCNTTYPE    5
#define IECCFG_COL_ID_6044DATAIN_COMMON_DELAYTIME     6

#define IECCFG_COLS_6044COMMONINDATA                  7

class CIecCfgSmvData6044CommonInGrid : public CIecCfgSmvData6044CommonGrid
{
public:
	CIecCfgSmvData6044CommonInGrid();
	virtual ~CIecCfgSmvData6044CommonInGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void  Show_SmpByteNum(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnSmpDataLen, GRID_CELL_EDIT_FUNC pFunc=NULL);//设置采样位宽
	virtual void  Show_SmpCntType(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnSmpCntType, GRID_CELL_EDIT_FUNC pFunc=NULL);//设置采样方式
};

