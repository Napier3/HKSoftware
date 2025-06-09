#pragma once

#include "..\..\..\..\Module\GridBase\ExBaseListGrid.h"

class CLocalScan_TestAppGrid : public CExBaseListGrid
{
public:
	CLocalScan_TestAppGrid();
	virtual ~CLocalScan_TestAppGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

	//重载函数
protected: 
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};
