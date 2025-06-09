#pragma once
#include "..\..\..\..\module\gridbase\exbaselistgrid.h"
#define PTSETTING_MAP_GRID_COLS            8

#define IDC_GRID_PTSETTING_MAP_CTRL   21011

class CPTSettingMapGrid :public CExBaseListGrid
{
public:
	CPTSettingMapGrid(void);
	virtual ~CPTSettingMapGrid(void);

	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual BOOL UpdateData(CExBaseObject *pData);
	//÷ÿ‘ÿ∫Ø ˝
protected: 
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};
