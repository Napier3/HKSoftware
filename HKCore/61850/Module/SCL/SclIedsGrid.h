#pragma once
#include "..\..\..\Module\GridBase\ExBaseListGrid.h"


class CSclIedsGrid : public CExBaseListGrid
{
public:
	CSclIedsGrid();
	virtual ~CSclIedsGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDatas(CExBaseList *pDatas);
	void ShowData_Ied(CExBaseObject *pSinglePath,int &nRow);
	CGridCell *GetSelectCell(int nRow);
	static void EndEditCell_Check_IedSelect(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
};