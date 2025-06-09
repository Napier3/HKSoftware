#pragma once
#include "..\..\..\Module\GridBase\ExBaseListGrid.h"

#define IDC_GRID_VIRLOOP_DLG_CTRL   41010

class CSclIEDGrid : public CExBaseListGrid
{
public:
	CSclIEDGrid();
	virtual ~CSclIEDGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas);
	void ShowData_Ied(CExBaseObject *pSinglePath,int nRow);
};