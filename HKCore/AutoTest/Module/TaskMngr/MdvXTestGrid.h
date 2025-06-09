//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.h  CStationTestListCtrl

#pragma once

#include "..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "TestTask.h"

#define MDVXTEST_GRID_COL_INDEX    0
#define MDVXTEST_GRID_COL_NAME     1
#define MDVXTEST_GRID_COL_PPFILE   2
#define MDVXTEST_GRID_COL_DVMFILE  3
#define MDVXTEST_GRID_COL_MGRP       4
#define MDVXTEST_GRID_COL_DVMTEST       5
#define MDVXTEST_GRID_COL_PROTOCOLTEST       6

#define MDVXTEST_GRID_COLS         7

//////////////////////////////////////////////////////////////////////////
//CMdvXTaskInforGrid
class CMdvXTaskInforGrid :	public CExBaseListGrid
{
public:
	CMdvXTaskInforGrid(void);
	virtual ~CMdvXTaskInforGrid(void);

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void UpdateTestTasks();
};


//////////////////////////////////////////////////////////////////////////
//CMdvXTestGrid
class CMdvXTestGrid :	public CExBaseListGrid
{
public:
	CMdvXTestGrid(void);
	virtual ~CMdvXTestGrid(void);

	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);

	CDvmDataset *m_pExpandDatas;
	CDvmDataset *m_pDeviceAttrsDefine;
	CTestTasks *m_pTestTasks;

	void InitGridTitle_DeviceAttr();

	void UpdateData_DeviceAttr(CExBaseObject *pObj);
	void UpdateData_Expand(CExBaseObject *pObj);
	void UpdateData_DeviceAttr(CExBaseObject *pObj, long nRow);
	void AutoAdjust_DeviceAttrCols();
	void UpdateXpingState(CExBaseObject *pObj, BOOL bXping);
	void XpingState(CExBaseObject *pObj);
	void SetTestTasks(CTestTasks *pTestTasks);

	void UpdateDvmState(CTestTask *pTestTask);
	void UpdateDvmState(long nRow, CTestTask *pTestTask);
	void UpdateProtocolState(CTestTask *pTestTask);
	void UpdateProtocolState(long nRow, CTestTask *pTestTask);

protected:
	long m_mShowDatasBeginRow;
	long m_nDeviceAttr_BeginCol;
	long m_nDeviceAttr_Cols;
	long m_nCmmConfig_BeginCol;
	long m_nCmmConfig_Cols;

public:
	virtual BOOL EndEditCell(int nRow, int nCol, DWORD dwItemData=0);

protected:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void ShowData_CmmConfig(CTestTask *pTestTask, long nRow) = 0;
	virtual void InitGridTitle_CmmConfig();
	virtual long InitCmmCfgColIndex() = 0;

	long InitCmmCfgColIndex_TcpServer(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_TcpClient(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_UdpServer(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_UdpClient(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_Serial(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_MMS(long &nColIndex, GV_ITEM &Item);

	void ShowData_TcpServer(CCmmTcpServerConfig *pCmmConfig, long nRow);
	void ShowData_TcpClient(CCmmTcpClientConfig *pCmmConfig, long nRow);
	void ShowData_UdpServer(CCmmUdpServerConfig *pCmmConfig, long nRow);
	void ShowData_UdpClient(CCmmUdpClientConfig *pCmmConfig, long nRow);
	void ShowData_Serial(CCmmSerialConfig *pCmmConfig, long nRow);
	void ShowData_MMS(CCmmMmsConfig *pCmmConfig, long nRow);

	static void EndEditCell_Mgrp(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_String_NameAndID_Task (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

//////////////////////////////////////////////////////////////////////////
//CMdvXTestGrid_MmsEngine
class CMdvXTestGrid_MmsEngine : public CMdvXTestGrid
{
public:
	CMdvXTestGrid_MmsEngine();
	virtual ~CMdvXTestGrid_MmsEngine();

	virtual void InitGridTitle();

protected:
	long m_nMmsCol;

	virtual void ShowData_CmmConfig(CTestTask *pTestTask, long nRow) ;
	virtual long InitCmmCfgColIndex();

	long InitCmmCfgColIndex_MMS(long &nColIndex, GV_ITEM &Item);
	void ShowData_MMS(CCmmMmsConfig *pCmmConfig, long nRow);
};

//////////////////////////////////////////////////////////////////////////
//CMdvXTestGrid_PpEngine
class CMdvXTestGrid_PpEngine : public CMdvXTestGrid
{
public:
	CMdvXTestGrid_PpEngine();
	virtual ~CMdvXTestGrid_PpEngine();

	virtual void InitGridTitle();

protected:
	long m_nTcpServerCol;
	long m_nTcpClientCol;
	long m_nUdpServerCol;
	long m_nUdpClientCol;
	long m_nSerialCol;

	virtual void ShowData_CmmConfig(CTestTask *pTestTask, long nRow) ;
	virtual long InitCmmCfgColIndex();

	long InitCmmCfgColIndex_TcpServer(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_TcpClient(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_UdpServer(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_UdpClient(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_Serial(long &nColIndex, GV_ITEM &Item);

	void ShowData_TcpServer(CCmmTcpServerConfig *pCmmConfig, long nRow);
	void ShowData_TcpClient(CCmmTcpClientConfig *pCmmConfig, long nRow);
	void ShowData_UdpServer(CCmmUdpServerConfig *pCmmConfig, long nRow);
	void ShowData_UdpClient(CCmmUdpClientConfig *pCmmConfig, long nRow);
	void ShowData_Serial(CCmmSerialConfig *pCmmConfig, long nRow);
};

