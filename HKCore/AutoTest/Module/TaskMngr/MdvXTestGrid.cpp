//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.cpp  CStationTestListCtrl


#include "stdafx.h"
#include "MdvXTestGrid.h"
#include "..\..\..\System\Module\XAtsSysSvrClient.h"
#include "..\XLanguageResourceAts_AutoTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CMdvXTaskInforGrid
CMdvXTaskInforGrid::CMdvXTaskInforGrid()
{
	m_nAdjustBeginCol = 0;
}

CMdvXTaskInforGrid::~CMdvXTaskInforGrid()
{
	
}


void CMdvXTaskInforGrid::InitGrid()
{
	SetListMode(FALSE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(2);
	SetColumnCount(5);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);

	InitGridTitle();

	ResetScrollBars();
}


void CMdvXTaskInforGrid::InitGridTitle()
{
	CString cTempStr[5]={
		 CXLanguageResourceAts_AutoTest::g_sLangTxt_TaskName
		, CXLanguageResourceAtsBase::g_sLangTxt_Path
		, CXLanguageResourceAtsBase::g_sLangTxt_TestTemplateFile
		,CXLanguageResourceAtsBase::g_sLangTxt_PrtcTempFile
		,CXLanguageResourceAtsBase::g_sLangTxt_ModelFile/*_T("模型文件")*/
	};

	int iWidth[5]={200, 200, 200, 200, 200};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 5);

	SetRowHeight(0, EXBASEGRID_ROWHEIGHT);
	SetRowHeight(1, EXBASEGRID_ROWHEIGHT);
}

void CMdvXTaskInforGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_pDatas = pDatas;
	CTestTasks *pTestTasks = (CTestTasks*)pDatas;

	if (pTestTasks->m_strName.GetLength() == 0)
	{
		Show_StaticString(pTestTasks, 1, 0, _T("请配置测试任务信息"));
		SetItemFgColour(1, 0, RGB(255, 0, 0));
	}
	else
	{
		Show_StaticString(pTestTasks, 1, 0, &pTestTasks->m_strName);
		SetItemFgColour(1, 0, RGB(0, 0, 0));
	}

	Show_StaticString(pTestTasks, 1, 1, pTestTasks->m_strTasksParentPath);

// 	CString strPath;
// 	strPath = _P_GetTemplatePath();
	Show_StaticString(pTestTasks, 1, 2, pTestTasks->tsk_GetGbxmlFile(FALSE));

	if (pTestTasks->m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		Show_StaticString(pTestTasks, 1, 3, _T("61850 MMS"));
	}
	else
	{
		Show_StaticString(pTestTasks, 1, 3, pTestTasks->tsk_GetPpxmlFile(FALSE));
	}

	Show_StaticString(pTestTasks, 1, 4, pTestTasks->m_strDeviceFile);
	AdjustAllCols();
// 	SetItemBkColour(1, 2, m_crFixedBkColour);
// 	SetItemBkColour(1, 3, m_crFixedBkColour);
// 	SetItemBkColour(1, 4, m_crFixedBkColour);
}

void CMdvXTaskInforGrid::UpdateTestTasks()
{
	CTestTasks *pTestTasks = (CTestTasks*)m_pDatas;
	SetItemText(1, 0, pTestTasks->m_strName);
	SetItemText(1, 1, pTestTasks->m_strTasksParentPath);
	AutoSizeColumn(0);
	AutoSizeColumn(1);

	if (pTestTasks->m_strName.GetLength() == 0)
	{
		SetItemFgColour(1, 0, RGB(255, 0, 0));
	}
	else
	{
		SetItemFgColour(1, 0, RGB(0, 0, 0));
	}
}

void CMdvXTaskInforGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

}

//////////////////////////////////////////////////////////////////////////
//CMdvXTestGrid
CMdvXTestGrid::CMdvXTestGrid(void)
{
	m_nAdjustBeginCol = 0;
	m_pExpandDatas = NULL;
	m_pDeviceAttrsDefine = NULL;

	m_nDeviceAttr_BeginCol = 0;
	m_nDeviceAttr_Cols = 0;
	m_nCmmConfig_BeginCol = 0;
	m_nCmmConfig_Cols = 0;
	m_mShowDatasBeginRow = 1;
}

CMdvXTestGrid::~CMdvXTestGrid(void)
{
}

void CMdvXTestGrid::InitGrid()
{
	SetListMode(TRUE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(m_mShowDatasBeginRow);
	SetColumnCount(MDVXTEST_GRID_COLS);
	SetFixedRowCount(m_mShowDatasBeginRow);
	SetFixedColumnCount(1);

	InitGridTitle();

	ResetScrollBars();
}

void CMdvXTestGrid::InitGridTitle_DeviceAttr()
{
	SetRowCount(m_mShowDatasBeginRow);
	SetColumnCount(MDVXTEST_GRID_COLS);
	ClearSelect();
	FreeListVCellData();

	if (m_pDeviceAttrsDefine == NULL)
	{
		return;
	}

	POS pos = m_pDeviceAttrsDefine->GetHeadPosition();
	CDvmData *pData = NULL;

	GV_ITEM Item;
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
		Item.lParam=nCol;
		SetItem(&Item);

		if (m_mShowDatasBeginRow == 2)
		{
			Merge(0, nCol, 1, nCol);
		}

		nCol++;
	}

	m_nCmmConfig_BeginCol = nCol;
}

void CMdvXTestGrid::InitGridTitle_CmmConfig()
{
	InitCmmCfgColIndex();
}

void CMdvXTestGrid::UpdateData_DeviceAttr(CExBaseObject *pObj)
{
	long nRow = GetDataRowEx(pObj, m_mShowDatasBeginRow, 1);

	UpdateData_DeviceAttr(pObj, nRow);
}

void CMdvXTestGrid::UpdateData_Expand(CExBaseObject *pObj)
{
	long nRow = GetDataRowEx(pObj, m_mShowDatasBeginRow, 1);

	CTestTask *pTestTask = (CTestTask*)pObj;
	CDvmData *pMaxID = (CDvmData*)m_pExpandDatas->FindByID(pTestTask->m_strMaxMgrpID);

	if (pMaxID == NULL)
	{
		return;
	}

	SetItemText(nRow, MDVXTEST_GRID_COL_MGRP, pMaxID->m_strName);
}

void CMdvXTestGrid::XpingState(CExBaseObject *pObj)
{
	long nRow = GetDataRowEx(pObj, m_mShowDatasBeginRow, 1);
	long nCol = 1;

	for (nCol=1; nCol<m_nCols; nCol++)
	{
		SetItemBkColour(nRow, nCol, RGB(255, 255, 128));
	}

	Invalidate(FALSE);
}

void CMdvXTestGrid::SetTestTasks(CTestTasks *pTestTasks)
{
	m_pTestTasks = pTestTasks;
	m_pDatas = pTestTasks;
}

void CMdvXTestGrid::UpdateXpingState(CExBaseObject *pObj, BOOL bXping)
{
	long nRow = GetDataRowEx(pObj, m_mShowDatasBeginRow, 1);

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

void CMdvXTestGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_pDatas = pDatas;
	//InitGridTitle_CmmConfig();

	CExBaseList listTask;
	m_pTestTasks->SelectAllTestTask(listTask);
	CExBaseObject *pObj = NULL;	
	POS pos = listTask.GetHeadPosition();
	int nRowIndex = m_mShowDatasBeginRow;
	SetRowCount(listTask.GetCount() + m_mShowDatasBeginRow);

	while (pos != NULL)
	{
		pObj = listTask.GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	listTask.RemoveAll();
	SetRowCount(nRowIndex, bResetScrollBars);

	for (nRowIndex=m_mShowDatasBeginRow; nRowIndex<m_nRows; nRowIndex++)
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

void CMdvXTestGrid::UpdateData_DeviceAttr(CExBaseObject *pData, long nRow)
{
	CTestTask *pTestTask = (CTestTask*)pData;
	long nCol = m_nDeviceAttr_BeginCol;
	CDvmDataset *pDataset = pTestTask->GetDeviceAttr();
	CDvmData *pDvmData = NULL;
	CDvmData *pDef = NULL;

	for (nCol=0; nCol < m_nDeviceAttr_Cols; nCol++)
	{
		pDef = (CDvmData *)m_pDeviceAttrsDefine->GetAtIndex(nCol);

		if (pDef == NULL)
		{
			break;
		}

		pDvmData = (CDvmData *)pDataset->FindByID(pDef->m_strID);

		if (pDvmData != NULL)
		{
			Show_String(pDvmData, nRow, nCol+m_nDeviceAttr_BeginCol, &pDvmData->m_strValue);
		}
	}
}

void CMdvXTestGrid::AutoAdjust_DeviceAttrCols()
{
	for (long nCol=0; nCol < m_nDeviceAttr_Cols; nCol++)
	{
		this->AutoSizeColumn(nCol + m_nDeviceAttr_BeginCol);
	}

	Invalidate(FALSE);
}

void CMdvXTestGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CLASSID_TESTTASK)
	{
		return;
	}

	CTestTask *pTestTask = (CTestTask*)pData;

	//TestTask的属性
	Show_IndexEx(pData, nRow, MDVXTEST_GRID_COL_INDEX, nRow-1);
	Show_String(pData, nRow, MDVXTEST_GRID_COL_NAME, &pTestTask->m_strID, EndEditCell_String_NameAndID_Task);
	ASSERT (m_pExpandDatas != NULL);

	if (m_pExpandDatas != NULL)
	{
		Show_ComboBox(pData, m_pExpandDatas, nRow, MDVXTEST_GRID_COL_MGRP, &pTestTask->m_strMaxMgrpID, EndEditCell_Mgrp);
	}

	CString strTemp = GetPathFileNameFromFilePathName(pTestTask->m_strDeviceFile);
	Show_StaticString(pData, nRow, MDVXTEST_GRID_COL_DVMFILE, strTemp);
	SetItemFgColour(nRow, MDVXTEST_GRID_COL_DVMFILE, RGB(128,128, 128));

	if (pTestTask->m_strPpEngineProgID == g_strPpEngineProgIDMms)
	{
		Show_StaticString(pData, nRow, MDVXTEST_GRID_COL_PPFILE, &pTestTask->m_strPpEngineProgID);
	}
	else
	{
		strTemp = GetPathFileNameFromFilePathName(pTestTask->tsk_GetPpxmlFile(FALSE));
		Show_StaticString(pData, nRow, MDVXTEST_GRID_COL_PPFILE, strTemp);
	}

	SetItemFgColour(nRow, MDVXTEST_GRID_COL_PPFILE, RGB(128,128, 128));

	UpdateDvmState(nRow, pTestTask);
	UpdateProtocolState(nRow, pTestTask);

	//装置属性
	UpdateData_DeviceAttr(pData, nRow);

	//通讯配置
	ShowData_CmmConfig(pTestTask, nRow);

	nRow++;
}

void CMdvXTestGrid::UpdateDvmState(CTestTask *pTestTask)
{
	long nRow = GetDataRowEx(pTestTask, 1, MDVXTEST_GRID_COL_DVMTEST);
	UpdateDvmState(nRow, pTestTask);
	Invalidate(FALSE);
}

void CMdvXTestGrid::UpdateDvmState(long nRow, CTestTask *pTestTask)
{
	CString strText;
	COLORREF crBack = RGB(255, 255, 255);
	strText = atssys_GetTestState(pTestTask->m_strDvmTestState, crBack);
	Show_StaticString(pTestTask, nRow, MDVXTEST_GRID_COL_DVMTEST, strText);
	SetItemBkColour(nRow, MDVXTEST_GRID_COL_DVMTEST, crBack);
}

void CMdvXTestGrid::UpdateProtocolState(CTestTask *pTestTask)
{
	long nRow = GetDataRowEx(pTestTask, 1, MDVXTEST_GRID_COL_PROTOCOLTEST);
	UpdateDvmState(nRow, pTestTask);
	Invalidate(FALSE);
}

void CMdvXTestGrid::UpdateProtocolState(long nRow, CTestTask *pTestTask)
{
	Show_StaticString(pTestTask, nRow, MDVXTEST_GRID_COL_PROTOCOLTEST, _T("---"));

// 	CString strText;
// 	COLORREF crBack = RGB(255, 255, 255);
// 	strText = atssys_GetTestState(pTestTask->m_strProtocolTestState, crBack);
// 	Show_StaticString(pTestTask, nRow, MDVXTEST_GRID_COL_PROTOCOLTEST, strText);
// 	SetItemBkColour(nRow, MDVXTEST_GRID_COL_PROTOCOLTEST, crBack);
}

BOOL CMdvXTestGrid::EndEditCell(int nRow, int nCol, DWORD dwItemData)
{
	return CExBaseListGrid::EndEditCell(nRow, nCol, dwItemData);;
}

#define width_ip_col     120
#define width_port_col  60
#define width_key_col  120
#define width_psw_col  120

//////////////////////////////////////////////////////////////////////////
//CMdvXTestGrid_MmsEngine
CMdvXTestGrid_MmsEngine::CMdvXTestGrid_MmsEngine()
{

}

CMdvXTestGrid_MmsEngine::~CMdvXTestGrid_MmsEngine()
{

}

void CMdvXTestGrid_MmsEngine::InitGridTitle()
{
	CString cTempStr[MDVXTEST_GRID_COLS]={CXLanguageResourceAts_AutoTest::g_sLangTxt_SerNumber/*_T("序号")*/
		,CXLanguageResourceAts_AutoTest::g_sLangTxt_Name/*_T("名称")*/
		,CXLanguageResourceAts_AutoTest::g_sLangTxt_PrtcTempFile
		,CXLanguageResourceAts_AutoTest::g_sLangTxt_ModelFile/*_T("模型文件")*/
		,CXLanguageResourceAts_AutoTest::g_sLangTxt_SettingsChoose/*_T("模型文件")*/
		,CXLanguageResourceBase::g_sLangTxt_ModelTest//            = _T("模型测试");
		,CXLanguageResourceBase::g_sLangTxt_ProtocolTest//            = _T("模型测试");
	};

	int iWidth[MDVXTEST_GRID_COLS]={60,120, 200, 100, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, MDVXTEST_GRID_COLS);

	m_nDeviceAttr_BeginCol = MDVXTEST_GRID_COLS;
	m_nDeviceAttr_Cols = 0;
	m_nCmmConfig_BeginCol = MDVXTEST_GRID_COLS;
	m_nCmmConfig_Cols = 0;

	InitGridTitle_DeviceAttr();
	InitGridTitle_CmmConfig();

	SetRowHeight(0, EXBASEGRID_ROWHEIGHT);
}

void CMdvXTestGrid_MmsEngine::ShowData_CmmConfig(CTestTask *pTestTask, long nRow)
{
	POS pos = pTestTask->m_listCmmCfg.GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pTestTask->m_listCmmCfg.GetNext(pos);
		nClassID = p->GetClassID();

		if(nClassID == DMCLASSID_CMM_MMS_CONFIG)
		{
			ShowData_MMS((CCmmMmsConfig*)p, nRow);
		}
		else
		{
			ASSERT (FALSE);
		}
	}

}

long CMdvXTestGrid_MmsEngine::InitCmmCfgColIndex_MMS(long &nColIndex, GV_ITEM &Item)
{
	m_nMmsCol = nColIndex;
	InsertColumn(_T(""));
	InsertColumn(_T(""));
	InsertColumn(_T(""));

	SetColumnWidth(nColIndex, width_ip_col);
	Item.row = 0;
	Item.col = nColIndex++;
	Item.szText = _T("IP");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_key_col);
	Item.row = 0;
	Item.col = nColIndex++;
	Item.szText = _T("KEY");
	SetItem(&Item);

	SetColumnWidth(nColIndex, width_psw_col);
	Item.row = 0;
	Item.col = nColIndex++;
	Item.szText = _T("PSW");
	SetItem(&Item);

	return nColIndex;
}

long CMdvXTestGrid_MmsEngine::InitCmmCfgColIndex()
{
	long nColIndex = m_nCmmConfig_BeginCol;

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	InitCmmCfgColIndex_MMS(nColIndex, Item);

	return nColIndex;
}

void CMdvXTestGrid_MmsEngine::ShowData_MMS(CCmmMmsConfig *pCmmConfig, long nRow)
{
	pCmmConfig->m_dwItemData = m_nMmsCol;
	Show_String(pCmmConfig, nRow, m_nMmsCol,     &pCmmConfig->m_strRemoteIP);
	Show_String(pCmmConfig, nRow, m_nMmsCol+1,     &pCmmConfig->m_strKey);
	Show_String(pCmmConfig, nRow, m_nMmsCol+2,     &pCmmConfig->m_strPSW);
}

//////////////////////////////////////////////////////////////////////////
//CMdvXTestGrid_PpEngine
CMdvXTestGrid_PpEngine::CMdvXTestGrid_PpEngine()
{
	m_mShowDatasBeginRow = 2;
}

CMdvXTestGrid_PpEngine::~CMdvXTestGrid_PpEngine()
{

}


void CMdvXTestGrid_PpEngine::InitGridTitle()
{
	CString cTempStr[MDVXTEST_GRID_COLS]={CXLanguageResourceAts_AutoTest::g_sLangTxt_SerNumber/*_T("序号")*/
		,CXLanguageResourceAts_AutoTest::g_sLangTxt_Name/*_T("名称")*/
		,CXLanguageResourceAts_AutoTest::g_sLangTxt_PrtcTempFile
		,CXLanguageResourceAts_AutoTest::g_sLangTxt_ModelFile/*_T("模型文件")*/
		,CXLanguageResourceAts_AutoTest::g_sLangTxt_SettingsChoose/*_T("模型文件")*/
	};

	int iWidth[MDVXTEST_GRID_COLS]={60,120, 200, 100, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, MDVXTEST_GRID_COLS);

	m_nDeviceAttr_BeginCol = MDVXTEST_GRID_COLS;
	m_nDeviceAttr_Cols = 0;
	m_nCmmConfig_BeginCol = MDVXTEST_GRID_COLS;
	m_nCmmConfig_Cols = 0;

	for (long nCol=0; nCol<MDVXTEST_GRID_COLS; nCol++)
	{
		Merge(0, nCol, 1, nCol);
	}

	SetRowHeight(0, EXBASEGRID_ROWHEIGHT-5);
	SetRowHeight(1, EXBASEGRID_ROWHEIGHT-5);
}

void CMdvXTestGrid_PpEngine::ShowData_CmmConfig(CTestTask *pTestTask, long nRow)
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
			ASSERT (FALSE);
		}
	}

}

long CMdvXTestGrid_PpEngine::InitCmmCfgColIndex()
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
	long nColIndex = m_nCmmConfig_BeginCol;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DMCLASSID_CMM_UDP_SERVER_CONFIG)
		{
			bTcpServerCol = TRUE;
		}
		else if( nClassID == DMCLASSID_CMM_UDP_CLIENT_CONFIG)
		{
			bTcpServerCol = TRUE;
		}
		else if( nClassID == DMCLASSID_CMM_TCP_CLIENT_CONFIG)
		{
			bTcpServerCol = TRUE;
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
			ASSERT (FALSE);
		}
	}

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
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

	return 0;
}


long CMdvXTestGrid_PpEngine::InitCmmCfgColIndex_TcpServer(long &nColIndex, GV_ITEM &Item)
{
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

long CMdvXTestGrid_PpEngine::InitCmmCfgColIndex_TcpClient(long &nColIndex, GV_ITEM &Item)
{
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

long CMdvXTestGrid_PpEngine::InitCmmCfgColIndex_UdpServer(long &nColIndex, GV_ITEM &Item)
{
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

long CMdvXTestGrid_PpEngine::InitCmmCfgColIndex_UdpClient(long &nColIndex, GV_ITEM &Item)
{
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

long CMdvXTestGrid_PpEngine::InitCmmCfgColIndex_Serial(long &nColIndex, GV_ITEM &Item)
{
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


void CMdvXTestGrid_PpEngine::ShowData_TcpServer(CCmmTcpServerConfig *pCmmConfig, long nRow)
{
	//使用m_dwItemData记录当前的数据列编号
	pCmmConfig->m_dwItemData = m_nTcpServerCol;
	Show_String(pCmmConfig, nRow, m_nTcpServerCol, &pCmmConfig->m_strLocalIP);
	Show_Long(pCmmConfig, nRow, m_nTcpServerCol+1, &pCmmConfig->m_nLocalPort);
}

void CMdvXTestGrid_PpEngine::ShowData_TcpClient(CCmmTcpClientConfig *pCmmConfig, long nRow)
{

}

void CMdvXTestGrid_PpEngine::ShowData_UdpServer(CCmmUdpServerConfig *pCmmConfig, long nRow)
{

}

void CMdvXTestGrid_PpEngine::ShowData_UdpClient(CCmmUdpClientConfig *pCmmConfig, long nRow)
{

}

void CMdvXTestGrid_PpEngine::ShowData_Serial(CCmmSerialConfig *pCmmConfig, long nRow)
{
	pCmmConfig->m_dwItemData = m_nSerialCol;
	Show_Long(pCmmConfig, nRow, m_nSerialCol,     &pCmmConfig->m_nPortNum);
	Show_Long(pCmmConfig, nRow, m_nSerialCol+1, &pCmmConfig->m_nBaudRate);
 	Show_Long(pCmmConfig, nRow, m_nSerialCol+2, &pCmmConfig->m_nDataBit);
	Show_Long(pCmmConfig, nRow, m_nSerialCol+3, &pCmmConfig->m_nParity);
	Show_Float(pCmmConfig, nRow, m_nSerialCol+4, &pCmmConfig->m_fStopBit);
}


void CMdvXTestGrid::EndEditCell_Mgrp (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CExBaseListGrid::EndEditCell_ComboBox(nRow, nCol, pCell, pGrid);
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	
	CMdvXTestGrid *pMdmgrpGrid = (CMdvXTestGrid*)pGrid;
	CTestTasks *pTestTasks = (CTestTasks*)pMdmgrpGrid->m_pDatas;
	CTestTask *pTask = (CTestTask*)pMdmgrpGrid->GetDataRow(nRow, nCol);
	pTask->SetCommCmdManyConfigValue(pTask->m_strMaxMgrpID);
	pTestTasks->InitProjectByCommCmdManyConfig(pTask);
}

void CMdvXTestGrid::EndEditCell_String_NameAndID_Task (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);
	CTestTask *pTestTask = (CTestTask*)pVCellData->pObj;

	if (*pVCellData->pString == pCell->szText)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)pVCellData->pObj->GetParent();

	if (pParent == NULL)
	{
		return;
	}

	if (pParent->FindByName(pCell->szText) != NULL)
	{
		pCell->szText = pVCellData->pObj->m_strName;
		pGrid->InvalidateGrid(FALSE);
		return;
	}

	CString strOld = pTestTask->m_strID;
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	pTestTask->m_strName = pCell->szText;
	pTestTask->m_strID = pCell->szText;
	pTestTask->m_strLocalID = pCell->szText;
	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);

	CExBaseList listProject;
	pTestTask->SelectAllTestProject(listProject);
	POS pos = listProject.GetHeadPosition();
	CTestProject *pProject = NULL;
	CString strLocation;

	while (pos != NULL)
	{
		pProject = (CTestProject *)listProject.GetNext(pos);
		pProject->m_strName.Replace(strOld, pTestTask->m_strID);
		pProject->m_strID = pProject->m_strName;
		pProject->m_strLocalID = pProject->m_strName;
		strLocation = pProject->GetLocation();
		strLocation.Replace(strOld, pTestTask->m_strID);
		pProject->SetLocation(strLocation);
	}

	listProject.RemoveAll();

	pGrid->AutoSizeColumn(nCol);
	pGrid->ResetScrollBars();
	pGrid->InvalidateGrid(FALSE);
}

