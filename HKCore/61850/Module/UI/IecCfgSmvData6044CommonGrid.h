#pragma once
#include "IecCfgDataGridBase.h"

#include "..\CfgDataMngr\IecCfg6044CommonData.h"

#define IECCFG_COL_ID_6044DATA_COMMON_PORT          2
#define IECCFG_COL_ID_6044DATA_COMMON_CHNUM         3
#define IECCFG_COL_ID_6044DATA_COMMON_SMPBYTENUM    4
#define IECCFG_COL_ID_6044DATA_COMMON_SMPCNTTYPE    5
#define IECCFG_COL_ID_6044DATA_COMMON_DELAYTIME     6

#define IECCFG_COLS_6044COMMONDATA                  7

class CIecCfgSmvData6044CommonGrid : public CIecCfgDataGridBase
{
public:
	CIecCfgSmvData6044CommonGrid();
	virtual ~CIecCfgSmvData6044CommonGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void  Show_SmpByteNum(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnSmpDataLen, GRID_CELL_EDIT_FUNC pFunc=NULL);//设置采样位宽
	virtual void  Show_SmpCntType(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnSmpCntType, GRID_CELL_EDIT_FUNC pFunc=NULL);//设置采样方式
};

