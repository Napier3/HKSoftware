#pragma once
#include "..\..\..\..\Module\GridBase\ExBaseListGrid.h"
#include "DeviceCmmConfig.h"

class CGridDeviceComCfg :	public CExBaseListGrid
{
public:
	CGridDeviceComCfg(void);
	~CGridDeviceComCfg(void);

	virtual void InitGrid();
	virtual void InitGridTitle();

public:
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	
	void ShowData_TcpServer(CCmmTcpServerConfig *pCmmConfig, long nRow);
	void ShowData_TcpClient(CCmmTcpClientConfig *pCmmConfig, long nRow);
	void ShowData_UdpServer(CCmmUdpServerConfig *pCmmConfig, long nRow);
	void ShowData_UdpClient(CCmmUdpClientConfig *pCmmConfig, long nRow);
	void ShowData_Serial(CCmmSerialConfig *pCmmConfig, long nRow);

//各种通讯配置对象的起始列
private:
	long m_nTcpServerCol;
	long m_nTcpClientCol;
	long m_nUdpServerCol;
	long m_nUdpClientCol;
	long m_nSerialCol;

	long InitCmmCfgColIndex();
	long InitCmmCfgColIndex_TcpServer(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_TcpClient(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_UdpServer(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_UdpClient(long &nColIndex, GV_ITEM &Item);
	long InitCmmCfgColIndex_Serial(long &nColIndex, GV_ITEM &Item);
};
