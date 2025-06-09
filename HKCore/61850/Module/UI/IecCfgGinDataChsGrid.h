#pragma once

#include "..\CfgDataMngr\IecCfgGinData.h"
#include "IecCfgDataGridBase.h"


#define IECCFG_COL_ID_GINCH_DESC     1
#define IECCFG_COL_ID_GINCH_PATH     2
#define IECCFG_COL_ID_GINCH_CHTYPE   3
#define IECCFG_COL_ID_GINCH_APPCH    4

#define IECCFG_COLS_GINCH            5


class CIecCfgGinDataChsGrid : public CIecCfgDataChsGridBase
{
public:
	CIecCfgGinDataChsGrid(BOOL bHasDevCh = FALSE);
	virtual ~CIecCfgGinDataChsGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_ChDataType_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);
	static void EndEditCell_AppCh_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

private:
	BOOL m_bHasDevCh;
};

