#pragma once
#include "IecCfgDataGridBase.h"

#include "..\CfgDataMngr\IecCfgGinData.h"

#define IECCFG_COL_ID_GINDATA_MAC          2
#define IECCFG_COL_ID_GINDATA_APPID        3
#define IECCFG_COL_ID_GINDATA_PORT	       4
#define IECCFG_COL_ID_GINDATA_DESC	       5
#define IECCFG_COL_ID_GINDATA_CHNUM        6
#define IECCFG_COL_ID_GINDATA_VERS	       7
#define IECCFG_COL_ID_GINDATA_TEST	       8
#define IECCFG_COL_ID_GINDATA_GCREF        9
#define IECCFG_COL_ID_GINDATA_DTSET        10
#define IECCFG_COL_ID_GINDATA_GOID	       11
#define IECCFG_COL_ID_GINDATA_NDS	       12
#define IECCFG_COL_ID_GINDATA_LIVE	       13
#define IECCFG_COL_ID_GINDATA_ANALY        14
#define IECCFG_COL_ID_GINDATA_CTRLREF      15

#define IECCFG_COLS_GINDATA                16
#define IECCFG_COLS_GINDATA_AT02D          17
#define IECCFG_COLS_GINDATA_ISmartTest     16


class CIecCfgGinDataGrid : public CIecCfgDataGridBase
{
public:
	CIecCfgGinDataGrid(long nUseType = IEC_CFG_DEVICE_USE_TYPE_NORMAL);
	virtual ~CIecCfgGinDataGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_ChDataType_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	static void EndEditCell_Fiber_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Fiber2_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

private:
	long m_nUseType;
};

