#pragma once

#include "..\..\..\..\Module\GridBase\ExBaseListGrid.h"

class CRemoteScan_TestAppGrid : public CExBaseListGrid
{
public:
	CRemoteScan_TestAppGrid();
	virtual ~CRemoteScan_TestAppGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

	//���غ���
protected: 
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};
