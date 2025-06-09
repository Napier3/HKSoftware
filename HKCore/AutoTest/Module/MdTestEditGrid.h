#pragma once


#include "..\..\Module\GridBase\ExBaseListGrid.h"


class CMdTestEditGrid :	public CExBaseListGrid
{
public:
	CMdTestEditGrid(void);
	~CMdTestEditGrid(void);

	virtual void InitGridTitle();
	virtual void InitGrid();

// 	void ShowTask(CTestTask *pTask);

public:
	virtual BOOL EndEditCell(int nRow, int nCol, DWORD dwItemData=0);

private:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};