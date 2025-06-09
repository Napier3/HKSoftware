#pragma once
#include "IecCfgDataGridBase.h"

#include "..\CfgDataMngr\IecCfg92Data.h"

#define IECCFG_COL_ID_92DATA_CTRLREF	  2
#define IECCFG_COL_ID_92DATA_DEST_MAC     3
#define IECCFG_COL_ID_92DATA_SRC_MAC      4
#define IECCFG_COL_ID_92DATA_APPID        5
#define IECCFG_COL_ID_92DATA_CHNUM        6
#define IECCFG_COL_ID_92DATA_PRIO         7
#define IECCFG_COL_ID_92DATA_VID		  8
#define IECCFG_COL_ID_92DATA_PORT		  9
#define IECCFG_COL_ID_92DATA_VERS		  10
#define IECCFG_COL_ID_92DATA_SMPDELAY	  11
// #define IECCFG_COL_ID_92DATA_NETDELAY	  11
#define IECCFG_COL_ID_92DATA_SYN		  12
#define IECCFG_COL_ID_92DATA_SVID		  13
#define IECCFG_COL_ID_92DATA_DATASET	  14

#define IECCFG_COLS_92DATA                15
#define IECCFG_COLS_92DATA_AT02D          16
#define IECCFG_COLS_92DATA_ISmartTest     15

class CIecCfgSmvData92Grid : public CIecCfgDataGridBase
{
public:
	CIecCfgSmvData92Grid(long nUseType = IEC_CFG_DEVICE_USE_TYPE_NORMAL);
	virtual ~CIecCfgSmvData92Grid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

private:

	long m_nUseType;//zhouhj 20201204 应用类型 0代表普通模式   1代表AT02D模式具有两个光口选择
};

