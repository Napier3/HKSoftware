#pragma once
#include "IECCfgDataGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGinData.h"

class CIECCfgGinDataGrid : public CIECCfgDataGridBase
{
public:
	CIECCfgGinDataGrid(long nUseType = IEC_CFG_DEVICE_USE_TYPE_NORMAL);
	virtual ~CIECCfgGinDataGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CString GetGridClassID() { return "CIECCfgGinDataGrid"; }

	static void UpdateRefChsGrid(CXGridCtrlBase *pGrid);
	static void EndEditCell_DTest(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_Fiber_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
private:
	long m_nUseType;
};

