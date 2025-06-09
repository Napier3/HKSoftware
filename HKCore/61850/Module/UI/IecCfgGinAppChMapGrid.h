#pragma once

#include "..\CfgDataMngr\IecCfgGinAppChMaps.h"
#include "IecCfgDataGridBase.h"


#define IECCFG_COL_ID_GINCHMAP_BIN      0
#define IECCFG_COL_ID_GINCHMAP_MAC      1
#define IECCFG_COL_ID_GINCHMAP_APPID    2
#define IECCFG_COL_ID_GINCHMAP_CHNAME   3
// #define IECCFG_COL_ID_GINCHMAP_CHINDEX  4

#define IECCFG_COLS_GINCHMAP            4

#define WM_GET_CURR_SEL_GIN_CH        (WM_USER+1053)
#define WM_UPDATE_GIN_CH              (WM_USER+1054)

class CIecCfgGinAppChMapGrid : public CExBaseListGrid
{
public:
	CIecCfgGinAppChMapGrid();
	virtual ~CIecCfgGinAppChMapGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);


	static CString g_strGinAppChMapEmptyString;

public:
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
// 	virtual void  OnEditCellRBDblClk(int nRow, int nCol, UINT nChar);
	virtual BOOL OnCellKeyDelete(const CCellID &idCell);

private:
	CIecCfgGinCh* GetCurrSelGinCh();
	void UpdateGinCh(CIecCfgGinCh *pGinCh);
};

