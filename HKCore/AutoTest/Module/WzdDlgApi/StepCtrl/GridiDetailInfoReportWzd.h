#pragma once
#include "../../../Module/GridBase/ExBaseListGrid.h"
#include "../../../Module/XfileMngrBase/XFile.h"
#include "WzdDlgStyleGrid.h"

#define	RECORD_TABLE_COLS		2

class CGridiDetailInfoReportWzd : public CWzdDlgStyleGrid
{
public:
	CGridiDetailInfoReportWzd(void);
	~CGridiDetailInfoReportWzd(void);

	virtual void InitGrid();
	virtual void InitGridTitle();

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowDatas(CExBaseList *pDataList,BOOL bInsertRow=TRUE);
};
