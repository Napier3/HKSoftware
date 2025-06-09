#pragma once
#include "IecCfgDataGridBase.h"

#include "..\CfgDataMngr\IecCfgGOUTData.h"

#define IECCFG_COL_ID_GOUTDATA_CTRLREF		2
#define IECCFG_COL_ID_GOUTDATA_DEST_MAC     3
#define IECCFG_COL_ID_GOUTDATA_SRC_MAC      4
#define IECCFG_COL_ID_GOUTDATA_APPID        5
#define IECCFG_COL_ID_GOUTDATA_PRIO			6
#define IECCFG_COL_ID_GOUTDATA_VID			7
#define IECCFG_COL_ID_GOUTDATA_PORT			8
#define IECCFG_COL_ID_GOUTDATA_DESC			9
#define IECCFG_COL_ID_GOUTDATA_CHNUM        10
#define IECCFG_COL_ID_GOUTDATA_VERS			11
#define IECCFG_COL_ID_GOUTDATA_TEST			12
#define IECCFG_COL_ID_GOUTDATA_GCREF		13
#define IECCFG_COL_ID_GOUTDATA_DTSET		14
#define IECCFG_COL_ID_GOUTDATA_GOID			15
#define IECCFG_COL_ID_GOUTDATA_NDS			16
#define IECCFG_COL_ID_GOUTDATA_T1			17
#define IECCFG_COL_ID_GOUTDATA_T0			18
#define IECCFG_COL_ID_GOUTDATA_T2			19
#define IECCFG_COL_ID_GOUTDATA_TQ			20
#define IECCFG_COL_ID_GOUTDATA_OTHER		21

#define IECCFG_COLS_GOUTDATA                22
#define IECCFG_COLS_GOUTDATA_AT02D          23
#define IECCFG_COLS_GOUTDATA_ISmartTest     22

class CIecCfgGoutDataGrid : public CIecCfgDataGridBase
{
public:
	CIecCfgGoutDataGrid(long nUseType = IEC_CFG_DEVICE_USE_TYPE_NORMAL);
	virtual ~CIecCfgGoutDataGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_GoutLongTime(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);//zhouhj 20211030  用于Gout时间相关限制

private:
	long m_nUseType;//zhouhj 20201204 应用类型 0代表普通模式   1代表AT02D模式具有两个光口选择
};

