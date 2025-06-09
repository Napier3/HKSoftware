#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "CapDevice\CapDeviceBase.h"

#define CAPDEVICEGRID_COLS   6
#define CAPDEVICEGRID_INDEX     0
#define CAPDEVICEGRID_TYPE      1
#define CAPDEVICEGRID_CHCOUNT   2
#define CAPDEVICEGRID_DESTMAC   3
#define CAPDEVICEGRID_MAC       4
#define CAPDEVICEGRID_APPID     5


class CCapDeviceGrid :	public CExBaseListGrid
{
private:

public:
	CCapDeviceGrid();
	virtual ~CCapDeviceGrid(void);

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pStData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void Show_Mac(CExBaseObject *pStData, const int& nRow, const int& nCol, BYTE *pMac);
	virtual void Show_61850Type(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nType);

	void AddCapDevice(CExBaseObject *pCapDevice);
	void SelectRecordDevice(long nRowIndex, BOOL bSel);

};

