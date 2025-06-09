//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StationTest.cpp  CStationTestListCtrl


#include "stdafx.h"
#include "XTestDbGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXTestDbGrid
CXTestDbGrid::CXTestDbGrid(void)
{
	m_nAdjustBeginCol = 0;
	m_pTestTasksMngr = NULL;
	m_pFirstDvmAttr = NULL;
	m_nDeviceAttrEndCol = 0;
	m_bSingleSel = FALSE;
}

CXTestDbGrid::~CXTestDbGrid(void)
{
	m_listAllDatas.RemoveAll();
}

void CXTestDbGrid::InitGrid()
{
	SetListMode(TRUE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);

	InitGridTitle();

	ResetScrollBars();
}

void CXTestDbGrid::InitGridTitle()
{
	if (m_pFirstDvmAttr == NULL)
	{
		return;
	}

	m_nDeviceAttrEndCol = m_pFirstDvmAttr->GetCount() + 1;
	SetRowCount(m_pTestTasksMngr->GetCount());
	SetColumnCount(m_nDeviceAttrEndCol + 2);
	ClearSelect();
	FreeListVCellData();

	POS pos = m_pFirstDvmAttr->GetHeadPosition();
	CDvmData *pData = NULL;

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	//
	SetColumnType(1,GVET_CHECKBOX);
	SetColumnWidth(1, 80);
	Item.szText=_T("选择");
	Item.lParam=1;
	Item.col = 1;
	SetItem(&Item);

	int nCol = 2;

	while (pos != NULL)
	{
		Item.col = nCol;
		pData = (CDvmData *)m_pFirstDvmAttr->GetNext(pos);
		SetColumnType(nCol,GVET_NOEDIT);
		SetColumnWidth(nCol, 80);
		Item.szText=pData->m_strName;
		Item.lParam=nCol;
		SetItem(&Item);

		nCol++;
	}

	//
	Item.col = nCol;
	SetColumnWidth(nCol, 80);
	Item.szText=_T("测试状态");
	Item.lParam=nCol;
	SetItem(&Item);
}

void CXTestDbGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_pDatas = pDatas;
	m_pTestTasksMngr = (CTestTasksMngr *)pDatas;
	//m_pTestTasksMngr->SelectAllDeviceAttrs(m_listDeviceAttrs);

	m_pFirstDvmAttr = (CDvmDataset *)m_pTestTasksMngr->m_listDeviceAttrs.GetHead();
	InitGridTitle();

	UpdateDatasEx(TRUE);
}

void CXTestDbGrid::ShowDatas_List(CExBaseList &listDatas, int &nRowIndex, const CString &strState)
{
	CExBaseObject *pObj = NULL;	
	POS pos = listDatas.GetHeadPosition();

	while (pos != NULL)
	{
		pObj = listDatas.GetNext(pos);
		ShowDataState(pObj, nRowIndex, strState, FALSE);
		m_listAllDatas.AddTail(pObj);
	}
}

void CXTestDbGrid::ShowDataState(CExBaseObject *pData, int& nRow, const CString &strState, BOOL bInsertRow)
{
	if (pData->GetClassID() != DVMCLASSID_CDVMDATASET)
	{
		return;
	}

	CDvmDataset *pDataset = (CDvmDataset*)pData;
	long nCol = 0;

	//TestTask的属性
	Show_Index(pDataset, nRow, nCol);

	if (m_bSingleSel)
	{
		Show_Check(pDataset, nRow, nCol+1, &pDataset->m_nIndex,EndEditCell_XTestCheck);
	} 
	else
	{
		Show_Check(pDataset, nRow, nCol+1, &pDataset->m_nIndex,EndEditCell_Check);
	}

	POS pos = pDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	nCol = 2;
	COLORREF crText = RGB(0, 0, 0);

	if ((pDataset->m_nWriteMode == XTEST_FUNCTEST_STATE_GOING)||(pDataset->m_nWriteMode == XTEST_FUNCTEST_STATE_STOP)
		||(pDataset->m_nWriteMode == XTEST_FUNCTEST_STATE_ERROR))
	{
		crText = RGB(0, 0, 255);
	}
	else if (pDataset->m_nWriteMode == XTEST_FUNCTEST_STATE_FINISH)
	{
		crText = RGB(128, 128, 128);
	}

	while (pos != NULL)
	{
		pDvmData = (CDvmData *)pDataset->GetNext(pos);
		Show_StaticString(pDvmData, nRow, nCol, pDvmData->m_strValue);
		SetItemFgColour(nRow, nCol, crText);
		nCol++;
	}

	if (pDataset->m_nWriteMode == XTEST_FUNCTEST_STATE_GOING)
	{
		Show_StaticString(pDvmData, nRow, nCol, _T("测试中"));
	}
	else if (pDataset->m_nWriteMode == XTEST_FUNCTEST_STATE_FINISH)
	{
		Show_StaticString(pDvmData, nRow, nCol, _T("测试完成"));
	}
	else if (pDataset->m_nWriteMode == XTEST_FUNCTEST_STATE_STOP)
	{
		Show_StaticString(pDvmData, nRow, nCol, _T("测试中途停止"));
	}
	else if (pDataset->m_nWriteMode == XTEST_FUNCTEST_STATE_ERROR)
	{
		Show_StaticString(pDvmData, nRow, nCol, _T("测试出现不合格项"));
	}
	else
	{
		Show_StaticString(pDvmData, nRow, nCol, strState);
	}

	SetItemFgColour(nRow, nCol, crText);

	nRow++;
}

void CXTestDbGrid::UpdateDatasEx(BOOL bClearSelect)
{
	if (bClearSelect)
	{
		ClearSelect();
	}

	m_listAllDatas.RemoveAll();
	//long nRows = m_pTestTasksMngr->m_listFinish.GetCount() + m_pTestTasksMngr->m_listDeviceAttrs.GetCount();
	long nRows = m_pTestTasksMngr->m_listDeviceAttrs.GetCount();
	int nRowIndex = 1;

	SetRowCount(nRows + 1);
	//ShowDatas_List(m_pTestTasksMngr->m_listFinish, nRowIndex, _T("测试完成"));
	ShowDatas_List(m_pTestTasksMngr->m_listDeviceAttrs, nRowIndex, _T(""));

	SetRowCount(nRowIndex);
	AdjustAllCols(TRUE);
	ResetScrollBars();

	Invalidate(FALSE);
}

BOOL CXTestDbGrid::UpdateData(CExBaseObject *pData)
{
	//验证更新节点是当前grid所指节点的子节点
	if ((CExBaseList *)pData->GetParent() != m_pDatas)
	{
		return FALSE;
	}

	//获取验证更新节点在当前grid节点的序号
	int nRow = GetDataRow(pData);

	if (nRow != -1)
	{
		ShowDataState(pData, nRow, _T(""), FALSE);
		AdjustAllCols(TRUE);
		Invalidate(FALSE);
	}
	else
	{
	}

	return TRUE;
}

void  CXTestDbGrid::EndEditCell_XTestCheck (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pnValue != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_LONG);
#ifdef USE_IN_XTESTDB_XTU_
	CTestTasksMngr *pTaskMngr = (CTestTasksMngr*)pVCellData->pObj->GetParent();

	if (pTaskMngr != NULL)
	{
		long nCount = pTaskMngr->GetSelDeviceAttrsCount();

		if ((nCount >1)||((nCount==1)&&(pCell->dwValue == 1)))
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("只能选择一个设备进行测试."));
			*(pVCellData->pnValue) = 0;
			pCell->dwValue = 0;
		}
	}
#endif

	if( *(pVCellData->pnValue) != pCell->dwValue )
	{
		*(pVCellData->pnValue) = pCell->dwValue;
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}
}

void CXTestDbGrid::ClearAllDatasCheck()
{
	POS pos = m_listAllDatas.GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	long nRow = 1;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)m_listAllDatas.GetNext(pos);
		pDataset->m_nIndex = 0;
		//Show_Check(pDataset, nRow, 1, &pDataset->m_nIndex);
	}
}

void CXTestDbGrid::UpdateAllCheck()
{
	POS pos = m_listAllDatas.GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	long nRow = 1;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)m_listAllDatas.GetNext(pos);

		if (m_bSingleSel)
		{
			Show_Check(pDataset, nRow, 1, &pDataset->m_nIndex,EndEditCell_XTestCheck);
		} 
		else
		{
			Show_Check(pDataset, nRow, 1, &pDataset->m_nIndex,EndEditCell_Check);
		}

		nRow++;
	}

	AdjustAllCols(TRUE);
	Invalidate(FALSE);
}

// 
// void CXTestDbGrid::UpdateDvmState(CTestTask *pTestTask)
// {
// 	long nRow = GetDataRowEx(pTestTask, 1, MDVXTEST_GRID_COL_DVMTEST);
// 	UpdateDvmState(nRow, pTestTask);
// 	Invalidate(FALSE);
// }
// 
// void CXTestDbGrid::UpdateDvmState(long nRow, CTestTask *pTestTask)
// {
// 	CString strText;
// 	COLORREF crBack = RGB(255, 255, 255);
// 	strText = atssys_GetTestState(pTestTask->m_strDvmTestState, crBack);
// 	Show_StaticString(pTestTask, nRow, MDVXTEST_GRID_COL_DVMTEST, strText);
// 	SetItemBkColour(nRow, MDVXTEST_GRID_COL_DVMTEST, crBack);
// }
// 
// void CXTestDbGrid::UpdateProtocolState(CTestTask *pTestTask)
// {
// 	long nRow = GetDataRowEx(pTestTask, 1, MDVXTEST_GRID_COL_PROTOCOLTEST);
// 	UpdateDvmState(nRow, pTestTask);
// 	Invalidate(FALSE);
// }
// 
// void CXTestDbGrid::UpdateProtocolState(long nRow, CTestTask *pTestTask)
// {
// 	Show_StaticString(pTestTask, nRow, MDVXTEST_GRID_COL_PROTOCOLTEST, _T("---"));
// 
// // 	CString strText;
// // 	COLORREF crBack = RGB(255, 255, 255);
// // 	strText = atssys_GetTestState(pTestTask->m_strProtocolTestState, crBack);
// // 	Show_StaticString(pTestTask, nRow, MDVXTEST_GRID_COL_PROTOCOLTEST, strText);
// // 	SetItemBkColour(nRow, MDVXTEST_GRID_COL_PROTOCOLTEST, crBack);
// }
// 
// BOOL CXTestDbGrid::EndEditCell(int nRow, int nCol, DWORD dwItemData)
// {
// 	return CExBaseListGrid::EndEditCell(nRow, nCol, dwItemData);;
// }
BEGIN_MESSAGE_MAP(CXTestDbGrid, CExBaseListGrid)
// 	ON_WM_CONTEXTMENU()
// 	ON_COMMAND(XTestDb_SEL_GRID_SEL_ALL, &CXTestDbGrid::OnSelectAll_MenuOpr)
// 	ON_COMMAND(XTestDb_SEL_GRID_CANCEL_ALL, &CXTestDbGrid::OnCancelAll_MenuOpr)
// 	ON_COMMAND(XTestDb_SEL_GRID_INVERSE_ALL, &CXTestDbGrid::OnInverseAll_MenuOpr)
END_MESSAGE_MAP()

void CXTestDbGrid::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	if (m_nRows < 1)
	{
		return;
	}

	CRect rect;
	GetWindowRect(rect);

	point.x -= rect.left;
	point.y -= rect.top;

	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();

	SetFocus();
	menu.AppendMenu(MF_STRING,XTestDb_SEL_GRID_SEL_ALL,_T("全部选择"));
	menu.AppendMenu(MF_STRING,XTestDb_SEL_GRID_CANCEL_ALL,_T("全部取消"));
	menu.AppendMenu(MF_STRING,XTestDb_SEL_GRID_INVERSE_ALL,_T("全部反选"));

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y, this);
	//资源回收
	//CUIWndThread::Attach_Wnd_WM_COMMAND(NULL);
	HMENU hmenu=menu.Detach();			
	menu.DestroyMenu();	
}

void CXTestDbGrid::OnSelectAll_MenuOpr()
{
	ASSERT(m_pDatas);
	POS pos = m_pDatas->GetHeadPosition();
	CDvmDataset *pCurDataset = NULL;

	while(pos)
	{
		pCurDataset = (CDvmDataset *)m_pDatas->GetNext(pos);

		if (pCurDataset->GetClassID() != DVMCLASSID_CDVMDATASET)
		{
			continue;
		}

		pCurDataset->m_nIndex = 1;
	}

	UpdateAllCheck();
}

void CXTestDbGrid::OnCancelAll_MenuOpr()
{
	ASSERT(m_pDatas);
	POS pos = m_pDatas->GetHeadPosition();
	CDvmDataset *pCurDataset = NULL;

	while(pos)
	{
		pCurDataset = (CDvmDataset *)m_pDatas->GetNext(pos);

		if (pCurDataset->GetClassID() != DVMCLASSID_CDVMDATASET)
		{
			continue;
		}

		pCurDataset->m_nIndex = 0;
	}

	UpdateAllCheck();
}

void CXTestDbGrid::OnInverseAll_MenuOpr()
{
	ASSERT(m_pDatas);
	POS pos = m_pDatas->GetHeadPosition();
	CDvmDataset *pCurDataset = NULL;

	while(pos)
	{
		pCurDataset = (CDvmDataset *)m_pDatas->GetNext(pos);

		if (pCurDataset->GetClassID() != DVMCLASSID_CDVMDATASET)
		{
			continue;
		}

		pCurDataset->m_nIndex = (!pCurDataset->m_nIndex);
	}

	UpdateAllCheck();
}