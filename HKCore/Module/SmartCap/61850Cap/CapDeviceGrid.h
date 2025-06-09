#pragma once

#include "../../../Module/GridBase/ExBaseListGrid.h"
#include "CapDevice/CapDeviceBase.h"

#define CAPDEVICEGRID_COLS			6

#define CAPDEVICEGRID_INDEX			0
#define CAPDEVICEGRID_TYPE			1
#define CAPDEVICEGRID_DESTMAC		2
//#define CAPDEVICEGRID_SRCMAC		3
#define CAPDEVICEGRID_CHCOUNT		3
//#define CAPDEVICEGRID_CTRLBLOCK	5
#define CAPDEVICEGRID_APPID			4
#define CAPDEVICEGRID_FIBER			5

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
	virtual void Show_Fiber(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nFiberIndex);

	void AddCapDevice(CExBaseObject *pCapDevice);
	void SelectRecordDevice(CExBaseObject *pStData, BOOL bSel);

	virtual BOOL UpdateData(CExBaseObject *pData);

	void UpdateCapDeviceLinkState();
};

