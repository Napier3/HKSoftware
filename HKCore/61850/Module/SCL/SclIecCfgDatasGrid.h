#pragma once

#include "SclIecCfgDatas.h"
#include "..\..\..\Module\GridBase\ExBaseListGrid.h"

#define IDC_GRID_SCLIECCFG_CTRL   21010
#define IDC_GRID_SCLIECCFG_CHN    21011

class CSclIecCfgGridBase : public CExBaseListGrid
{
public:
	CSclIecCfgGridBase();
	virtual ~CSclIecCfgGridBase();

public:
	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pDatas);

protected:
	UINT m_nOldSclIecCfgClassID;

};

class CSclIecCfgCtrlGrid : public CSclIecCfgGridBase
{
public:
	CSclIecCfgCtrlGrid();
	virtual ~CSclIecCfgCtrlGrid();

	CWnd *m_pMsgRcvWnd;//zhouhj 20211027 在勾选后,向外部发送消息

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void UpdateCheck();
public:
	void ShowData_GooseInput(CSclCtrlGsIn *pGsIn,int nRow);
	void ShowData_GooseOutput(CSclCtrlGsOut *pGsOut,int nRow);
	void ShowData_SMVInput(CSclCtrlSmvIn *pSmvIn,int nRow);
	void ShowData_SMVOutput(CSclCtrlSmvOut *pSmvOut,int nRow);

	static void EndEditCell_CheckChanged(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);//zhouhj 20211027 处理勾选改变
};

class CCSclIecCfgCtrlChnGrid : public CSclIecCfgGridBase
{
public:
	CCSclIecCfgCtrlChnGrid();
	virtual ~CCSclIecCfgCtrlChnGrid();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	void ShowData_GooseInputChn(CSclChGsIn *pChn,int nRow);
	void ShowData_GooseOutputChn(CSclChGsOut *pChn,int nRow);
	void ShowData_SMVInputChn(CSclChSmvIn *pChn,int nRow);
	void ShowData_SMVOutputChn(CSclChSmvOut *pChn,int nRow);

};

