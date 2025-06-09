#pragma once

#include "../../../Module/GridBase/ExBaseListGrid.h"
#include "CapDevice/CapDeviceBase.h"
#include "CapDevice/CapDeviceSmvCh.h"
#include "CapDevice/CapDeviceGooseCh.h"

#define CAPDEVICECHGRID_COLS		5

#define CAPDEVICECHGRID_COL_INDEX	0
#define CAPDEVICECHGRID_COL_DESC	1
#define CAPDEVICECHGRID_COL_ADDR	2
#define CAPDEVICECHGRID_COL_TYPE	3
#define CAPDEVICECHGRID_COL_RATE	4
//#define CAPDEVICECHGRID_COL_VALUE	5
#define CAPDEVICECHGRID_COL_SET     6

#define CAPDEVICE_GSGRID_COLS		4

#define CAPDEVICE_GSGRID_COL_INDEX	0
#define CAPDEVICE_GSGRID_COL_DESC	1
#define CAPDEVICE_GSGRID_COL_ADDR	2
#define CAPDEVICE_GSGRID_COL_TYPE	3
//#define CAPDEVICE_GSGRID_COL_VALUE	4



void ShowColorRow(CExBaseListGrid* pGridCtrl, int nMatchState, int nRow, int nCols);

class CCapDeviceChGrid : public CExBaseListGrid
{
public:
	CCapDeviceChGrid();
	virtual ~CCapDeviceChGrid(void);

	//ÏÔÊ¾Êý¾Ý
	virtual void ShowDatas(CExBaseList *pStData);

	virtual void InitGridTitle(){};
	virtual void InitGrid(){};

	void InitGrid(CExBaseList* pStData);
	void InitGridTitle(CExBaseList* pStData);

	virtual void ShowData(CExBaseObject *pStData, int& nRow, BOOL bInsertRow=TRUE);
	
private:
	virtual void ShowData_SMV(CExBaseObject *pStData, int& nRow);
	virtual void ShowData_GOOSE(CExBaseObject *pStData, int& nRow);

	static void EndEditCell_Select (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	static void EndEditCell_ChRate (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	virtual void Show_ChRate(CExBaseObject *pStData, const int& nRow, const int& nCol);

	static void EndEditCell_ChType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	virtual void Show_ChType(CExBaseObject *pStData, const int& nRow, const int& nCol);
	virtual void Show_GsChType(CExBaseObject *pStData, const int& nRow, const int& nCol);

	//Ìî³äcomboList cell
	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);
	virtual void FillComboBoxItems_ChRate(int nRow, int nCol, LPARAM cltWnd);
	virtual void FillComboBoxItems_ChType(int nRow, int nCol, LPARAM cltWnd);

};

