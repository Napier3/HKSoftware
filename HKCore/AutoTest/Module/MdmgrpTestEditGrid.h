#pragma once


#include "..\..\Module\GridBase\ExBaseListGrid.h"

class CMdmgrpTestTaskEditGrid :	public CExBaseListGrid
{
public:
	CMdmgrpTestTaskEditGrid(void);
	virtual ~CMdmgrpTestTaskEditGrid(void);

	virtual void InitGridTitle();
	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);

	CDvmDataset *m_pExpandDatas;
	CDvmDataset *m_pDeviceAttrsDefine;

	virtual void InitGridTitle_Task();
	virtual void InitGridTitle_DeviceAttr();
	virtual void InitGridTitle_CmmConfig();

	virtual void UpdateData_TestTask(CTestTask *pTestTask, long nRow);
	virtual void UpdateData_CommConfig(CTestTask *pTestTask, long nRow);
	virtual long UpdateData_TestTask(CExBaseObject *pObj);
	virtual long UpdateData_DeviceAttr(CExBaseObject *pObj);
	virtual void UpdateData_Expand(CExBaseObject *pObj);
	virtual void UpdateData_DeviceAttr(CExBaseObject *pObj, long nRow);
	virtual void AutoAdjust_DeviceAttrCols();
	virtual void UpdateXpingState(CExBaseObject *pObj, BOOL bXping);
	virtual void XpingState(CExBaseObject *pObj);

protected:
	long m_nDeviceAttr_BeginCol;
	long m_nDeviceAttr_Cols;
	long m_nCmmConfig_BeginCol;
	long m_nCmmConfig_Cols;

	long m_nTcpServerCol;
	long m_nTcpClientCol;
	long m_nUdpServerCol;
	long m_nUdpClientCol;
	long m_nSerialCol;
	long m_nMmsCol;

public:
	virtual BOOL EndEditCell(int nRow, int nCol, DWORD dwItemData=0);

protected:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	long InitCmmCfgColIndex();
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
	static void EndEditCell_String_NameAndIDEx (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
};

//////////////////////////////////////////////////////////////////////////
//CMdmgrpProjectSelGrid
class CMdmgrpProjectSelGrid :	public CExBaseListGrid
{
public:
	CMdmgrpProjectSelGrid(void);
	virtual ~CMdmgrpProjectSelGrid(void);

	CDvmDataset *m_pExpandDatas;

	virtual void InitGridTitle();
	virtual void InitGrid();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);

private:
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	CExBaseList m_listTask;

};

//////////////////////////////////////////////////////////////////////////
//CFacBatchTestGrid
class CFacBatchTestGrid : public CMdmgrpTestTaskEditGrid
{
public:
	CFacBatchTestGrid();
	virtual ~CFacBatchTestGrid();
	//virtual void InitGridTitle_CmmConfig()	{};

public:
	virtual void UpdateData_TestTask(CTestTask *pTestTask, long nRow);
	virtual long UpdateData_TestTask(CExBaseObject *pObj);
	virtual void InitGridTitle_Task();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateData_TestTasks(CTestTasks *pTestTasks);
	void UpdateData_BySelect(CExBaseList &listProject);
};