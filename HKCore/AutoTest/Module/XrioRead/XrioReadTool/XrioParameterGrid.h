#pragma once
#include "..\..\..\module\gridbase\exbaselistgrid.h"

#define XRIO_PARAMETER_GRID_COLS            6

#define IDC_GRID_XRIO_PARAMETER_CTRL   21010

class CXrioParameterGrid : public CExBaseListGrid
{
public:
	CXrioParameterGrid(void);
	virtual ~CXrioParameterGrid(void);

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
};
