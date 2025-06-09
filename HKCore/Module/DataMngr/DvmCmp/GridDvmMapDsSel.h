#pragma once

#include "DvmDeviceMap.h"
#include "..\..\GridBase\ExBaseListGrid.h"


#define DVMDSMAPSEL_COL_INDEX       0
#define DVMDSMAPSEL_COL_SEL         1
#define DVMDSMAPSEL_COL_LDNAME      2
#define DVMDSMAPSEL_COL_LDMAPNAME   3
#define DVMDSMAPSEL_COL_DSNAME      4
#define DVMDSMAPSEL_COL_DSMAPNAME   5

#define DVMDSMAPSEL_COLS            6



class CGridDvmMapDsSel : public CExBaseListGrid
{
public:
	CGridDvmMapDsSel();
	virtual ~CGridDvmMapDsSel();

	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pExDataList);
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);

	virtual void InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE);
	virtual void DataViewOptr_DataChanged(int nRow, int nCol);

protected:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void UpdateRowBkColor(long nRow);
};
