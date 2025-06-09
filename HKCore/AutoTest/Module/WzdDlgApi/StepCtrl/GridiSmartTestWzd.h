#pragma once
#include "../../../Module/GridBase/ExBaseListGrid.h"
#include "../../../Module/XfileMngrBase/XFile.h"

#define	RECORD_TABLE_COLS		4
#define	SORT_TABLE_COLS			3

class CGridiSmartTestWzd :	public CExBaseListGrid
{
public:
	CGridiSmartTestWzd(void);
	~CGridiSmartTestWzd(void);

	virtual void InitGrid();
	virtual void InitGridTitle();

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDatas(CExBaseList *pDataList,BOOL bInsertRow=TRUE);
};
