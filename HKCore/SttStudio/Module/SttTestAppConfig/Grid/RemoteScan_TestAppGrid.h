#pragma once

#include "..\..\..\..\Module\GridBase\ExBaseListGrid.h"

class CRemoteScan_TestAppGrid : public CExBaseListGrid
{
public:
	CRemoteScan_TestAppGrid();
	virtual ~CRemoteScan_TestAppGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

	//÷ÿ‘ÿ∫Ø ˝
protected: 
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};
