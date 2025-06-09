#pragma once
#include "IECCfgDataGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"

#define IECCFG_COL_ID_92DATA_CTRLREF	  3
#define IECCFG_COL_ID_92DATA_DEST_MAC     4
#define IECCFG_COL_ID_92DATA_SRC_MAC      5
#define IECCFG_COL_ID_92DATA_APPID        6
#define IECCFG_COL_ID_92DATA_CHNUM        7
#define IECCFG_COL_ID_92DATA_PRIO         8
#define IECCFG_COL_ID_92DATA_VID		  9
#define IECCFG_COL_ID_92DATA_PORT		  10
#define IECCFG_COL_ID_92DATA_VERS		  11
#define IECCFG_COL_ID_92DATA_SMPDELAY	  12
// #define IECCFG_COL_ID_92DATA_NETDELAY	  11
#define IECCFG_COL_ID_92DATA_SYN		  13
#define IECCFG_COL_ID_92DATA_SVID		  14
#define IECCFG_COL_ID_92DATA_DATASET	  15

#define IECCFG_COLS_92DATA                16
#define IECCFG_COLS_92DATA_AT02D          17
#define IECCFG_COLS_92DATA_ISmartTest     16

class CIECCfgSmv92DataGrid : public CIECCfgDataGridBase
{
public:
	CIECCfgSmv92DataGrid(long nUseType = IEC_CFG_DEVICE_USE_TYPE_NORMAL);
	virtual ~CIECCfgSmv92DataGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CString GetGridClassID() { return "CIECCfgSmv92DataGrid"; }

	static void UpdateRefChsGrid(CXGridCtrlBase *pGrid);
	static void EndEditCell_Fiber(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Delay(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

private:

	long m_nUseType;//zhouhj 20201204 应用类型 0代表普通模式   1代表AT02D模式具有两个光口选择
};

