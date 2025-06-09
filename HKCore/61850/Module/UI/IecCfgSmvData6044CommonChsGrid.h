#pragma once

#include "..\CfgDataMngr\IecCfg6044CommonData.h"
#include "IecCfgSmvDataChsGridBase.h"


#define IECCFG_COL_ID_6044CH_COMMON_DESC     1
#define IECCFG_COL_ID_6044CH_COMMON_CHTYPE   2
#define IECCFG_COL_ID_6044CH_COMMON_APPCH    3
#define IECCFG_COL_ID_6044CH_COMMON_BYTELEN  4
#define IECCFG_COL_ID_6044CH_COMMON_VALUE    5

#define IECCFG_COLS_COMMON_6044CH            6

class CIecCfgSmvData6044CommonChsGrid : public CIecCfgSmvDataChsGridBase
{
public:
	CIecCfgSmvData6044CommonChsGrid();
	virtual ~CIecCfgSmvData6044CommonChsGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual long GetAppChColIndex()	{	return IECCFG_COL_ID_6044CH_COMMON_APPCH;	}

	virtual BOOL OnCellRButtonUpEx(UINT nFlags, CPoint point);//增加用于设置FT3订阅功能zhouhj 20211014

};

