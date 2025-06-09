#pragma once

#include "..\GridBase\ExBaseListGrid.h"
#include "TempFuncGlobal.h"

class CXtfTempGrid : public CExBaseListGrid
{
public:
	CXtfTempGrid();
	virtual ~CXtfTempGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

protected:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};