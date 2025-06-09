#include "stdafx.h"
#include "TestControl/TestControlMdvMgrp.h"
#include "TestControl/TestControlWnd.h"
#include "TCtrlCntrWorkSpace.h"
#include "TestControl/TCtrlCntrBaseApp.h"
#include "GuideBook\Script\GbScript_GlobalDefine.h"
#include "..\..\Module\KeyDb\XMatchToolBase.h"
#include <math.h>

#include "XRecorderDlg.h"
#include "..\..\Module\EpotoInterface\EpotoInterface.h"
#include "..\..\Module\DataMngr\DatasetValid\DsvViewResultDialog.h"

#include "XLanguageResourceAts.h"
#include "MdmgrpTestEditGrid.h"
#include "TaskMngr\TestTask.h"
#include "XLanguageResourceAts_AutoTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////////

#define MDMGRPTEST_GRID_COL_INDEX    0
#define MDMGRPTEST_GRID_COL_NAME     1
#define MDMGRPTEST_GRID_COL_PPFILE   2
#define MDMGRPTEST_GRID_COL_DVMFILE  3
#define MDMGRPTEST_GRID_COL_MGRP       4
#define MDMGRPTEST_GRID_COLS         5

CMdmgrpTestTaskEditGrid::CMdmgrpTestTaskEditGrid(void)
{
	m_nAdjustBeginCol = 0;
	m_pExpandDatas = NULL;
	m_pDeviceAttrsDefine = NULL;

	m_nTcpServerCol = -1;
	m_nTcpClientCol = -1;
	m_nUdpServerCol = -1;
	m_nUdpClientCol = -1;
	m_nSerialCol = -1;
	m_nMmsCol = -1;
}

CMdmgrpTestTaskEditGrid::~CMdmgrpTestTaskEditGrid(void)
{
}

void CMdmgrpTestTaskEditGrid::InitGrid()
{
	SetListMode(TRUE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(2);
	SetColumnCount(MDMGRPTEST_GRID_COLS);
	SetFixedRowCount(2);
	SetFixedColumnCount(1);

	InitGridTitle();

	ResetScrollBars();
}

void CMdmgrpTestTaskEditGrid::InitGridTitle()
{
	InitGridTitle_Task();

	m_nDeviceAttr_BeginCol = MDMGRPTEST_GRID_COLS;
	m_nDeviceAttr_Cols = 0;
	m_nCmmConfig_BeginCol = MDMGRPTEST_GRID_COLS;
	m_nCmmConfig_Cols = 0;

	for (long nCol=0; nCol<MDMGRPTEST_GRID_COLS; nCol++)
	{
		Merge(0, nCol, 1, nCol);
	}
	SetRowHeight(0, EXBASEGRID_ROWHEIGHT-5);
	SetRowHeight(1, EXBASEGRID_ROWHEIGHT-5);
}

void CMdmgrpTestTaskEditGrid::InitGridTitle_Task()
{
	CString cTempStr[MDMGRPTEST_GRID_COLS]={g_sLangTxt_SerNumber/*_T("序号")*/
		,g_sLangTxt_Name/*_T("名称")*/
		,g_sLangTxt_PrtcTempFile
		,g_sLangTxt_ModelFile/*_T("模型文件")*/
		,g_sLangTxt_SettingsChoose/*_T("模型文件")*/
	};
	int iWidth[MDMGRPTEST_GRID_COLS]={60,120, 200, 100, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, MDMGRPTEST_GRID_COLS);
}

void CMdmgrpTestTaskEditGrid::InitGridTitle_DeviceAttr()
{
	SetRowCount(2);
	SetColumnCount(MDMGRPTEST_GRID_COLS);
	ClearSelect();
	FreeListVCellData();

	if (m_pDeviceAttrsDefine == NULL)
	{
		return;
	}

	POS pos = m_pDeviceAttrsDefine->GetHeadPosition();
	CDvmData *pData = NULL;

	GV_ITEM Item;
	Item.lParam = 0;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	int nCol = m_nDeviceAttr_BeginCol;
	m_nDeviceAttr_Cols = m_pDeviceAttrsDefine->GetCount();
	SetColumnCount(m_nDeviceAttr_BeginCol + m_nDeviceAttr_Cols);

	while (pos != NULL)
	{
		Item.col = nCol;
		pData = (CDvmData *)m_pDeviceAttrsDefine->GetNext(pos);
		SetColumnType(nCol,GVET_NOEDIT);
		SetColumnWidth(nCol, 80);
		Item.szText=pData->m_strName;
		SetItem(&Item);
		Merge(0, nCol, 1, nCol);
		nCol++;
	}

	m_nCmmConfig_BeginCol = nCol;
}

void CMdmgrpTestTaskEditGrid::InitGridTitle_CmmConfig()
{
	InitCmmCfgColIndex();
}

long CMdmgrpTestTaskEditGrid::UpdateData_DeviceAttr(CExBaseObject *pObj)
{
	long nRow = GetDataRowEx(pObj, 2, 1);

	UpdateData_DeviceAttr(pObj, nRow);

	return nRow;
}

long CMdmgrpTestTaskEditGrid::UpdateData_TestTask(CExBaseObject *pObj)
{
	long nRow = GetDataRowEx(pObj, 2, 1);

	UpdateData_TestTask((CTestTask*)pObj, nRow);

	Invalidate(FALSE);
	return nRow;
}

void CMdmgrpTestTaskEditGrid::UpdateData_Expand(CExBaseObject *pObj)
{
	long nRow = GetDataRowEx(pObj, 2, 1);

	CTestTask *pTestTask = (CTestTask*)pObj;
	CDvmData *pMaxID = (CDvmData*)m_pExpandDatas->FindByID(pTestTask->m_strMaxMgrpID);

	if (pMaxID == NULL)
	{
		return;
	}

	SetItemText(nRow, MDMGRPTEST_GRID_COL_MGRP, pMaxID->m_strName);
}

void CMdmgrpTestTaskEditGrid::XpingState(CExBaseObject *pObj)
{
	long nRow = GetDataRowEx(pObj, 2, 1);
	long nCol = 1;

	for (nCol=1; nCol<m_nCols; nCol++)
	{
		SetItemBkColour(nRow, nCol, RGB(255, 255, 128));
	}

	Invalidate(FALSE);
}

void CMdmgrpTestTaskEditGrid::UpdateXpingState(CExBaseObject *pObj, BOOL bXping)
{
	long nRow = GetDataRowEx(pObj, 2, 1);

	CTestTask *pTestTask = (CTestTask*)pObj;
	long nCol = 1;
	COLORREF crXping = RGB(0, 255, 0);

	if (!bXping)
	{
		crXping = RGB(255, 128, 128);
	}

	for (nCol=1; nCol<m_nCols; nCol++)
	{
		SetItemBkColour(nRow, nCol, crXping);
	}

	Invalidate(FALSE);
}

void CMdmgrpTestTaskEditGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_pDatas = pDatas;
	InitGridTitle_CmmConfig();

	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 2;
	SetRowCount(pDatas->GetCount() + 2);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);

	for (nRowIndex=2; nRowIndex<m_nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, EXBASEGRID_ROWHEIGHT);
	}

	AdjustAllCols(bResetScrollBars);

	if (bResetScrollBars)
	{
		ResetScrollBars();
	}

	Invalidate(FALSE);
}

// 
// void CMdmgrpTestTaskEditGrid::ShowTask(CTestTask *pTask)
// {
// 	m_pDataset = pDatas;
// 
// 	CDvmData * pShortData = NULL;
// 	long nIndex = 0;
// 	long nRows = 0;
// 	long nCount = m_pDataset->GetCount();
// 	SetRowCount(nCount + 1);
// 
// 	for (nIndex=0;nIndex<nCount;nIndex++)
// 	{
// 		pShortData = (CDvmData*)m_pDataset->GetAtIndex(nIndex);
// 		nRows++;
// 		ShowOneParaObject(pShortData,nRows);
// 	}
// }

void CMdmgrpTestTaskEditGrid::UpdateData_DeviceAttr(CExBaseObject *pData, long nRow)
{
	CTestTask *pTestTask = (CTestTask*)pData;
	long nCol = m_nDeviceAttr_BeginCol;
	CDvmDataset *pDataset = pTestTask->GetDeviceAttr();
	CDvmData *pDvmData = NULL;

	for (nCol=0; nCol < m_nDeviceAttr_Cols; nCol++)
	{
		pDvmData = (CDvmData *)pDataset->GetAtIndex(nCol);

		if (pData == NULL)
		{
			break;
		}

		Show_String(pDvmData, nRow, nCol+m_nDeviceAttr_BeginCol, &pDvmData->m_strValue);
	}
}

void CMdmgrpTestTaskEditGrid::AutoAdjust_DeviceAttrCols()
{
	for (long nCol=0; nCol < m_nDeviceAttr_Cols; nCol++)
	{
		this->AutoSizeColumn(nCol + m_nDeviceAttr_BeginCol);
	}

	Invalidate(FALSE);
}

void CMdmgrpTestTaskEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CLASSID_TESTTASK)
	{
		return;
	}

	CTestTask *pTestTask = (CTestTask*)pData;

	//TestTask的属性
	UpdateData_TestTask(pTestTask, nRow);

	//装置属性
	UpdateData_DeviceAttr(pData, nRow);

	//通讯配置
	UpdateData_CommConfig(pTestTask, nRow);

	nRow++;
}

void CMdmgrpTestTaskEditGrid::UpdateData_TestTask(CTestTask *pTestTask, long nRow)
{
	Show_IndexEx(pTestTask, nRow, MDMGRPTEST_GRID_COL_INDEX, nRow-1);
	Show_String(pTestTask, nRow, MDMGRPTEST_GRID_COL_NAME, &pTestTask->m_strID, EndEditCell_String_NameAndIDEx);
	ASSERT (m_pExpandDatas != NULL);

	if (m_pExpandDatas != NULL)
	{
		Show_ComboBox(pTestTask, m_pExpandDatas, nRow, MDMGRPTEST_GRID_COL_MGRP, &pTestTask->m_strMaxMgrpID, EndEditCell_Mgrp);
	}

	CString strTemp = GetPathFileNameFromFilePathName(pTestTask->m_strDeviceFile);
	Show_StaticString(pTestTask, nRow, MDMGRPTEST_GRID_COL_DVMFILE, strTemp);
	SetItemFgColour(nRow, MDMGRPTEST_GRID_COL_DVMFILE, RGB(128,128, 128));

	if (pTestTask->m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		Show_StaticString(pTestTask, nRow, MDMGRPTEST_GRID_COL_PPFILE, &pTestTask->m_strPpEngineProgID);
	}
	else	if (pTestTask->m_strPpEngineProgID == g_strPpEngineProgID)
	{
		strTemp = pTestTask->tsk_GetPpxmlFile(FALSE);//GetPathFileNameFromFilePathName(pTestTask->m_strPpTemplateFile);

		if (strTemp.GetLength() == 0)
		{
			strTemp = pTestTask->tsk_GetPpxmlFile(FALSE);//pTestTask->m_strPpTemplateFile;
		}

		Show_StaticString(pTestTask, nRow, MDMGRPTEST_GRID_COL_PPFILE, strTemp);
	}
	else// (pTestTask->m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		Show_StaticString(pTestTask, nRow, MDMGRPTEST_GRID_COL_PPFILE, &pTestTask->m_strPpEngineProgID);
	}

	SetItemFgColour(nRow, MDMGRPTEST_GRID_COL_PPFILE, RGB(128,128, 128));
}

void CMdmgrpTestTaskEditGrid::UpdateData_CommConfig(CTestTask *pTestTask, long nRow)
{
	POS pos = pTestTask->m_listCmmCfg.GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pTestTask->m_listCmmCfg.GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DMCLASSID_CMM_UDP_SERVER_CONFIG)
		{
			ShowData_UdpServer((CCmmUdpServerConfig*)p, nRow);
		}
		else if( nClassID == DMCLASSID_CMM_UDP_CLIENT_CONFIG)
		{
			ShowData_UdpClient((CCmmUdpClientConfig*)p, nRow);
		}
		else if( nClassID == DMCLASSID_CMM_TCP_CLIENT_CONFIG)
		{
			ShowData_TcpClient((CCmmTcpClientConfig*)p, nRow);
		}
		else if(nClassID == DMCLASSID_CMM_TCP_SERVER_CONFIG)
		{
			ShowData_TcpServer((CCmmTcpServerConfig*)p, nRow);
		}
		else if(nClassID == DMCLASSID_CMM_SERIAL_CONFIG)
		{
			ShowData_Serial((CCmmSerialConfig*)p, nRow);
		}
		else if(nClassID == DMCLASSID_CMM_MMS_CONFIG)
		{
			ShowData_MMS((CCmmMmsConfig*)p, nRow);
		}
	}
}

BOOL CMdmgrpTestTaskEditGrid::EndEditCell(int nRow, int nCol, DWORD dwItemData)
{
	return CExBaseListGrid::EndEditCell(nRow, nCol, dwItemData);;
}

#define width_ip_col     120
#define width_port_col  60
#define width_key_col  120
#define width_psw_col  120

long CMdmgrpTestTaskEditGrid::InitCmmCfgColIndex_TcpServer(long &nColIndex, GV_ITEM &Item)
{
	if (m_nTcpServerCol != -1)
	{
		return m_nTcpServerCol+2;
	}

	m_nTcpServerCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("TCP Server");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+1);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Port");
	SetItem(&Item);

	return nColIndex;
}

long CMdmgrpTestTaskEditGrid::InitCmmCfgColIndex_TcpClient(long &nColIndex, GV_ITEM &Item)
{
	if (m_nTcpClientCol != -1)
	{
		return m_nTcpClientCol+4;
	}

	m_nTcpClientCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("TCP Client");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+3);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Local IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Local Port");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Remote IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Remote Port");
	SetItem(&Item);

	return nColIndex;
}

long CMdmgrpTestTaskEditGrid::InitCmmCfgColIndex_UdpServer(long &nColIndex, GV_ITEM &Item)
{
	if (m_nUdpServerCol != -1)
	{
		return m_nUdpServerCol+2;
	}

	m_nUdpServerCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("Udp Server");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+1);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Port");
	SetItem(&Item);

	return nColIndex;
}

long CMdmgrpTestTaskEditGrid::InitCmmCfgColIndex_UdpClient(long &nColIndex, GV_ITEM &Item)
{
	if (m_nUdpClientCol != -1)
	{
		return m_nUdpClientCol+4;
	}

	m_nUdpClientCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("Udp Client");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+3);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Local IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Local Port");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Remote IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Remote Port");
	SetItem(&Item);

	return nColIndex;
}

long CMdmgrpTestTaskEditGrid::InitCmmCfgColIndex_Serial(long &nColIndex, GV_ITEM &Item)
{
	if (m_nSerialCol != -1)
	{
		return m_nSerialCol+5;
	}

	m_nSerialCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("Serial");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+4);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("Port");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Baund Rate");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Data Bit");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Parity");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_port_col);
	Item.col = nColIndex++;
	Item.szText = _T("Stop Bit");
	SetItem(&Item);

	return nColIndex;
}


long CMdmgrpTestTaskEditGrid::InitCmmCfgColIndex_MMS(long &nColIndex, GV_ITEM &Item)
{
	if (m_nMmsCol != -1)
	{
		return m_nMmsCol+3;
	}

	m_nMmsCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	Item.row = 0;
	Item.col = nColIndex;
	Item.szText = _T("MMS");
	SetItem(&Item);
	Merge(0, nColIndex, 0, nColIndex+2);

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_key_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("KEY");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_psw_col);
	Item.row = 1;
	Item.col = nColIndex++;
	Item.szText = _T("PSW");
	SetItem(&Item);

	return nColIndex;
}

long CMdmgrpTestTaskEditGrid::InitCmmCfgColIndex()
{
	CTestTasks *pTestTasks = (CTestTasks*)m_pDatas;
	CExBaseList *pList = &pTestTasks->m_listCmmCfgChannel;

	POS pos  = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	BOOL bTcpServerCol = FALSE;
	BOOL bTcpClientCol = FALSE;
	BOOL bUdpServerCol = FALSE;
	BOOL bUdpClientCol = FALSE;
	BOOL bSerialCol = FALSE;
	BOOL bMmsCol = FALSE;
	long nColIndex = m_nCmmConfig_BeginCol;

	 while (pos != NULL)
	 {
		p = (CExBaseObject *)pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DMCLASSID_CMM_UDP_SERVER_CONFIG)
		{
			bUdpServerCol = TRUE;
		}
		else if( nClassID == DMCLASSID_CMM_UDP_CLIENT_CONFIG)
		{
			bUdpClientCol = TRUE;
		}
		else if( nClassID == DMCLASSID_CMM_TCP_CLIENT_CONFIG)
		{
			bTcpClientCol = TRUE;
		}
		else if(nClassID == DMCLASSID_CMM_TCP_SERVER_CONFIG)
		{
			bTcpServerCol = TRUE;
		}
		else if(nClassID == DMCLASSID_CMM_SERIAL_CONFIG)
		{
			bSerialCol = TRUE;
		}
		else if(nClassID == DMCLASSID_CMM_MMS_CONFIG)
		{
			bMmsCol = TRUE;
		}
	 }

	 GV_ITEM Item;
	 Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	 Item.row = 0;
	 Item.lParam = 0;
	 Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	 if (bTcpServerCol)
	 {
		 InitCmmCfgColIndex_TcpServer(nColIndex, Item);
	 }

	if (bTcpClientCol)
	{
		InitCmmCfgColIndex_TcpClient(nColIndex, Item);
	}

	if (bUdpServerCol)
	{
		InitCmmCfgColIndex_UdpServer(nColIndex, Item);
	}

	if (bUdpClientCol)
	{
		InitCmmCfgColIndex_UdpServer(nColIndex, Item);
	}

	if (bSerialCol)
	{
		InitCmmCfgColIndex_Serial(nColIndex, Item);
	}

	if (bMmsCol)
	{
		InitCmmCfgColIndex_MMS(nColIndex, Item);
	}

// 	if (bMmsCol || bUdpClientCol || bTcpClientCol)
// 	{
// 		m_crDataTextBkColor = RGB(33, 159, 195);
// 	}

	 return nColIndex;
}

void CMdmgrpTestTaskEditGrid::ShowData_TcpServer(CCmmTcpServerConfig *pCmmConfig, long nRow)
{
	//使用m_dwItemData记录当前的数据列编号
	pCmmConfig->m_dwItemData = m_nTcpServerCol;
	Show_String(pCmmConfig, nRow, m_nTcpServerCol, &pCmmConfig->m_strLocalIP);
	Show_Long(pCmmConfig, nRow, m_nTcpServerCol+1, &pCmmConfig->m_nLocalPort);
}

void CMdmgrpTestTaskEditGrid::ShowData_TcpClient(CCmmTcpClientConfig *pCmmConfig, long nRow)
{
	//使用m_dwItemData记录当前的数据列编号
	pCmmConfig->m_dwItemData = m_nTcpClientCol;
	Show_String(pCmmConfig, nRow, m_nTcpClientCol, &pCmmConfig->m_strLocalIP);
	Show_Long(pCmmConfig, nRow, m_nTcpClientCol+1, &pCmmConfig->m_nLocalPort);
	Show_String(pCmmConfig, nRow, m_nTcpClientCol+2, &pCmmConfig->m_strRemoteIP);
	Show_Long(pCmmConfig, nRow, m_nTcpClientCol+3, &pCmmConfig->m_nRemotePort);
}

void CMdmgrpTestTaskEditGrid::ShowData_UdpServer(CCmmUdpServerConfig *pCmmConfig, long nRow)
{

}

void CMdmgrpTestTaskEditGrid::ShowData_UdpClient(CCmmUdpClientConfig *pCmmConfig, long nRow)
{

}

void CMdmgrpTestTaskEditGrid::ShowData_Serial(CCmmSerialConfig *pCmmConfig, long nRow)
{
	pCmmConfig->m_dwItemData = m_nSerialCol;
	Show_Long(pCmmConfig, nRow, m_nSerialCol,     &pCmmConfig->m_nPortNum);
	Show_Long(pCmmConfig, nRow, m_nSerialCol+1, &pCmmConfig->m_nBaudRate);
 	Show_Long(pCmmConfig, nRow, m_nSerialCol+2, &pCmmConfig->m_nDataBit);
	Show_Long(pCmmConfig, nRow, m_nSerialCol+3, &pCmmConfig->m_nParity);
	Show_Float(pCmmConfig, nRow, m_nSerialCol+4, &pCmmConfig->m_fStopBit);
}

void CMdmgrpTestTaskEditGrid::ShowData_MMS(CCmmMmsConfig *pCmmConfig, long nRow)
{
	pCmmConfig->m_dwItemData = m_nMmsCol;
	Show_String(pCmmConfig, nRow, m_nMmsCol,     &pCmmConfig->m_strRemoteIP);
	Show_String(pCmmConfig, nRow, m_nMmsCol+1,     &pCmmConfig->m_strKey);
	Show_String(pCmmConfig, nRow, m_nMmsCol+2,     &pCmmConfig->m_strPSW);
}


void CMdmgrpTestTaskEditGrid::EndEditCell_Mgrp (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CExBaseListGrid::EndEditCell_ComboBox(nRow, nCol, pCell, pGrid);
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	
	CMdmgrpTestTaskEditGrid *pMdmgrpGrid = (CMdmgrpTestTaskEditGrid*)pGrid;
	CTestTasks *pTestTasks = (CTestTasks*)pMdmgrpGrid->m_pDatas;
	CTestTask *pTask = (CTestTask*)pMdmgrpGrid->GetDataRow(nRow, nCol);
	pTask->SetCommCmdManyConfigValue(pTask->m_strMaxMgrpID);
	pTestTasks->InitProjectByCommCmdManyConfig(pTask);
}


void CMdmgrpTestTaskEditGrid::EndEditCell_String_NameAndIDEx (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	EndEditCell_String_NameAndID(nRow, nCol, pCell, pGrid);
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;

	CTestTask *pTestTask = (CTestTask*)pVCellData->pObj;
	pTestTask->m_strLocalID = pTestTask->m_strID;
}

//////////////////////////////////////////////////////////////////////////
//
CMdmgrpProjectSelGrid::CMdmgrpProjectSelGrid(void)
{
	m_pExpandDatas = NULL;
}

CMdmgrpProjectSelGrid::~CMdmgrpProjectSelGrid(void)
{
	m_listTask.RemoveAll();
}

void CMdmgrpProjectSelGrid::InitGridTitle()
{
	CString cTempStr[2]={g_sLangTxt_SerNumber/*_T("序号")*/
		,g_sLangTxt_Name/*_T("名称")*/
	};
	int iWidth[2]={60,120};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 2);

	SetRowHeight(0, EXBASEGRID_ROWHEIGHT);
}

void CMdmgrpProjectSelGrid::InitGrid()
{
	SetListMode(TRUE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(2);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);

	InitGridTitle();

	ResetScrollBars();
}

void CMdmgrpProjectSelGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	CTestTasks *pTestTasks = (CTestTasks*)pDatas;
	pTestTasks->SelectAllTestTask(m_listTask);
	long nColsAdd = m_pExpandDatas->GetCount();
	long nCol = 0;
	CString strText;

	SetColumnCount(nColsAdd + 2);

	for (nCol=0; nCol < nColsAdd; nCol++)
	{
		strText.Format(_T("%d"), nCol + 1);
		SetItemText(0, nCol + 2, strText);
		SetColumnWidth(nCol + 2, 40);
	}
	
	CExBaseListGrid::ShowDatas(&m_listTask);
}

void CMdmgrpProjectSelGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CTestTask *pTestTask = (CTestTask*)pData;
	CExBaseList listProject;
	pTestTask->SelectAllTestProject(listProject);
	POS pos = listProject.GetHeadPosition();
	CTestProject *pProject = NULL;
	long nCol = 2;

	Show_Index(pData, nRow, 0);
	Show_StaticString(pData, nRow, 1, pTestTask->m_strID);

	while (pos != NULL)
	{
		pProject = (CTestProject *)listProject.GetNext(pos);
		Show_Check(pProject, nRow, nCol, &pProject->m_nSelect);
		nCol++;
	}

	listProject.RemoveAll();
	nRow++;
}

//////////////////////////////////////////////////////////////////////////
//CFacBatchTestGrid
CFacBatchTestGrid::CFacBatchTestGrid()
{

}

CFacBatchTestGrid::~CFacBatchTestGrid()
{

}


void CFacBatchTestGrid::InitGridTitle_Task()
{
	CString cTempStr[MDMGRPTEST_GRID_COLS]={g_sLangTxt_SerNumber/*_T("序号")*/
		,_T("名称")
		,_T("装置编号")
		,_T("测试结论")
		,_T("测试状态")
	};
	int iWidth[MDMGRPTEST_GRID_COLS]={60,120, 200, 100, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, MDMGRPTEST_GRID_COLS);
}

void CFacBatchTestGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CMdmgrpTestTaskEditGrid::ShowData(pData, nRow, bInsertRow);
}

void CFacBatchTestGrid::UpdateData_TestTask(CTestTask *pTestTask, long nRow)
{
	CTestProject *pFind = pTestTask->GetTestProjectAtIndex(0);
	Show_IndexEx(pTestTask, nRow, 0, nRow-1);
	Show_String(pTestTask, nRow, 1, &pTestTask->m_strName, EndEditCell_String_NameAndIDEx);
	//ASSERT (m_pExpandDatas != NULL);

	//_T("装置编号")
	Show_StaticString(pTestTask, nRow, 2, &pTestTask->m_strID);

	//_T("测试结论")
	Show_StaticString(pTestTask, nRow, 3, pFind->m_strTestRsltJdg);

	//_T("测试状态")
	//if (pFind->IsTestState_Finish())
	{
		Show_StaticString(pTestTask, nRow, 4, pFind->GetTestStateDesc());
	}
}

long CFacBatchTestGrid::UpdateData_TestTask(CExBaseObject *pObj)
{
	return CMdmgrpTestTaskEditGrid::UpdateData_TestTask(pObj);
}

void CFacBatchTestGrid::UpdateData_TestTasks(CTestTasks *pTestTasks)
{
	POS pos = pTestTasks->GetHeadPosition();
	CExBaseObject *p = NULL;
	long nRow = 2;

	while (pos != NULL)
	{
		p =pTestTasks->GetNext(pos);

		if (p->GetClassID() == CLASSID_TESTTASK)
		{
			UpdateData_TestTask( (CTestTask *)p, nRow);
			nRow++;
		}
	}
}

void CFacBatchTestGrid::UpdateData_BySelect(CExBaseList &listProject)
{
	long nRow = 1, nCol = 1;
	CTestProject *pProject = NULL;
 	GV_ITEM oItem;
 	oItem.mask = GVIF_BKCLR|GVIF_FGCLR | GVIF_DATATYPE;
	oItem.crBkClr = RGB(232, 232, 232);
	oItem.crFgClr = RGB(192, 192, 192);
	//oItem.nDataType = 
	CGridCell *pCell = NULL;

	for (nRow=2; nRow<m_nRows; nRow++)
	{
		pProject = (CTestProject*)listProject.GetAtIndex(nRow-2);;
		oItem.row = nRow;

		if (pProject->m_nSelect == 1)
		{
			for (nCol=1; nCol<m_nCols; nCol++)
			{
				pCell = GetCell(nRow, nCol);
				pCell->SetReadOnly(FALSE);
			}
		}
		else
		{
			for (nCol=1; nCol<m_nCols; nCol++)
			{
				pCell = GetCell(nRow, nCol);
				pCell->SetReadOnly(TRUE);
			}
		}

	}

	Invalidate(TRUE);
}
