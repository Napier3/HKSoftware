#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "CapDevice\CapDeviceBase.h"
#include "CapDevice\CapDeviceSmvCh.h"
#include "CapDevice\CapDeviceGooseCh.h"

#define CAPDEVICECHGRID_COLS   4
#define CAPDEVICECHGRID_COL_INDEX     0
#define CAPDEVICECHGRID_COL_SELECT    1
#define CAPDEVICECHGRID_COL_SET       2
#define CAPDEVICECHGRID_COL_DESC      3


class CCapDeviceChGrid : public CExBaseListGrid
{
public:
	CCapDeviceChGrid();
	virtual ~CCapDeviceChGrid(void);

	//ÏÔÊ¾Êý¾Ý
	virtual void ShowDatas(CExBaseList *pStData);

	virtual void InitGrid();
	virtual void InitGridTitle();
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

