#pragma once
#include "IECCfgDataGridBase.h"

#define IECCFG_COL_ID_GOUTDATA_DEST_MAC     2
#define IECCFG_COL_ID_GOUTDATA_PORT			3
#define IECCFG_COL_ID_GOUTDATA_APPID        4
#define IECCFG_COL_ID_GOUTDATA_DESC			5
#define IECCFG_COL_ID_GOUTDATA_CHNUM        6
#define IECCFG_COL_ID_GOUTDATA_TEST			7


class CIECCfgGoutDataGrid : public CIECCfgDataGridBase
{
public:
	CIECCfgGoutDataGrid(long nUseType = IEC_CFG_DEVICE_USE_TYPE_NORMAL);
	virtual ~CIECCfgGoutDataGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CString GetGridClassID() { return "CIECCfgGoutDataGrid"; }

	static void UpdateRefChsGrid(CXGridCtrlBase *pGrid);
	static void EndEditCell_GoutLongTime(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);//zhouhj 20211030  用于Gout时间相关限制
	static void EndEditCell_DTest(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Fiber_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

private:
	long m_nUseType;//zhouhj 20201204 应用类型 0代表普通模式   1代表AT02D模式具有两个光口选择
};

