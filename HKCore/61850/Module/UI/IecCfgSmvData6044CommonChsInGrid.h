#pragma once

#include "IecCfgSmvData6044CommonChsGrid.h"


#define IECCFG_COL_ID_6044CHIN_COMMON_DESC     1
#define IECCFG_COL_ID_6044CHIN_COMMON_CHTYPE   2
#define IECCFG_COL_ID_6044CHIN_COMMON_APPCH    3
#define IECCFG_COL_ID_6044CHIN_COMMON_BYTELEN  4
#define IECCFG_COL_ID_6044CHIN_COMMON_BINMAP   5

#define IECCFG_COLS_COMMON_6044CHIN            6

class CIecCfgSmvData6044CommonChsInGrid : public CIecCfgSmvData6044CommonChsGrid
{
public:
	CIecCfgSmvData6044CommonChsInGrid();
	virtual ~CIecCfgSmvData6044CommonChsInGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual long GetAppChColIndex()	{	return IECCFG_COL_ID_6044CHIN_COMMON_APPCH;	}

	virtual BOOL OnCellRButtonUpEx(UINT nFlags, CPoint point);//增加用于设置FT3订阅功能zhouhj 20211014
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);

	void ShowCommonBinMap_StaticString(CExBaseObject *pData, int nRow);

protected:
	BOOL SetCommonBinMapByDlg(int nRow);//弹出对话框显示设置开入映射界面
	CDataType* m_pGinAppChDataType;
};

