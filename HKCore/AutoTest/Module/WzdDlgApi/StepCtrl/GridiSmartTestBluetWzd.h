#pragma once
#include "../../../Module/GridBase/ExBaseListGrid.h"
#include "../../../Module/XfileMngrBase/XFile.h"
#include "../../../BlueTooth/Module/TestTool/OrderInfo0x92.h"
#define	BluetWzd_TABLE_COLS		12
#define	BluetWzd_SORT_TABLE_COLS			3

class CGridiSmartTestBluetWzd :	public CExBaseListGrid
{
public:
	CGridiSmartTestBluetWzd(void);
	~CGridiSmartTestBluetWzd(void);

	virtual void InitGrid();
	virtual void InitGridTitle();

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void ShowData(COrderInfo0x92 *pData,BOOL bInsertRow=TRUE);
	virtual void ShowDatas(CExBaseList *pDataList,BOOL bInsertRow=TRUE);
};
