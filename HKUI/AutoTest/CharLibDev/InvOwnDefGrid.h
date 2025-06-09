#pragma once

#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "..\Module\Characteristic\CharElementPoint.h"

class CInvOwnDefGrid : public CExBaseListGrid
{
public:
	CInvOwnDefGrid();
	virtual ~CInvOwnDefGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();

	//重载函数
protected: 
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};
