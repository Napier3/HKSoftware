#include "StdAfx.h"
#include "CapDeviceChGrid.h"

#define MATCH_COLOR_NONE			RGB(0,0,0)
#define MATCH_COLOR_SUCCESS			RGB(0,0,255)		
#define MATCH_COLOR_SURPLUS			RGB(255,0,0)  
#define MATCH_COLOR_MISS			RGB(128,128,128)

void ShowColorRow(CExBaseListGrid* pGridCtrl, int nMatchState, int nRow, int nCols)
{
	if(pGridCtrl == NULL)
	{
		return;
	}

	COLORREF crMatchColor = RGB(0,0,0);

	switch (nMatchState)
	{
	case MATCH_STATE_NONE:
		crMatchColor = MATCH_COLOR_NONE;
		break;
	case MATCH_STATE_SUCCESS:
		crMatchColor = MATCH_COLOR_SUCCESS;
		break;
	case MATCH_STATE_SURPLUS:
		crMatchColor = MATCH_COLOR_SURPLUS;
		break;
	case MATCH_STATE_MISS:
		crMatchColor = MATCH_COLOR_MISS;
		break;
	}

	for (int iCol=0;iCol<nCols;iCol++)
	{
		pGridCtrl->SetItemFgColour(nRow, iCol, crMatchColor);
	}
}

//////////////////////////////////////////////////////////////////////////
//CCapDeviceChGrid

CCapDeviceChGrid::CCapDeviceChGrid()
{

}


CCapDeviceChGrid::~CCapDeviceChGrid(void)
{
	
}

void CCapDeviceChGrid::InitGrid(CExBaseList* pStData)
{
	if (pStData == NULL)
	{
		return;
	}

	DeleteAllItems();
	SetRowCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle(pStData);
	ResetScrollBars();
}

void CCapDeviceChGrid::InitGridTitle(CExBaseList* pStData)
{
	UINT nClassD = pStData->GetClassID();
	if(nClassD == CPDCLASSID_DEVICEGOOSE)
	{
		SetColumnCount(CAPDEVICE_GSGRID_COLS);
		CString cTempStr[CAPDEVICE_GSGRID_COLS]={_T("编号"),_T("通道描述"),_T("通道地址"),_T("通道类型")/*,_T("通道值")*/};
		int iWidth[CAPDEVICE_GSGRID_COLS]={40, 150, 100, 80/*, 100*/};
		CExBaseListGrid::InitGridTitle(cTempStr, iWidth, CAPDEVICE_GSGRID_COLS);
	}
	else 
	{
		SetColumnCount(CAPDEVICECHGRID_COLS);
		CString cTempStr[CAPDEVICECHGRID_COLS]={_T("编号"),_T("通道描述"),_T("通道地址"),_T("通道类型"),_T("比例")/*,_T("计算值")*/};
		int iWidth[CAPDEVICECHGRID_COLS]={40, 150, 100, 80, 80/*, 100*/};
		CExBaseListGrid::InitGridTitle(cTempStr, iWidth, CAPDEVICECHGRID_COLS);
	}
}

//显示数据
void CCapDeviceChGrid::ShowDatas(CExBaseList *pStData)
{
	InitGrid(pStData);
	CExBaseListGrid::ShowDatas(pStData);

//	UINT nClassID = pStData->GetClassID();

//	if (nClassID == CPDCLASSID_DEVICEGOOSE)
	{
//		SetItemText(0, CAPDEVICECHGRID_COL_SET, _T("类型"));
//		SetItemText(0, CAPDEVICECHGRID_COL_DESC, _T("描述"));
	}
//	else
	{
//		SetItemText(0, CAPDEVICECHGRID_COL_SET, _T("类型"));
//		SetItemText(0, CAPDEVICECHGRID_COL_DESC, _T("比例"));
	}
}

void CCapDeviceChGrid::ShowData(CExBaseObject *pStData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pStData->GetClassID();

	if (bInsertRow)
	{
		InsertRow(NULL);
	}

	if (nClassID == CPDCLASSID_GOOSECH)
	{
		ShowData_GOOSE(pStData, nRow);
	}
	else
	{
		ShowData_SMV(pStData, nRow);
	}

	nRow++;
}

void CCapDeviceChGrid::ShowData_SMV(CExBaseObject *pStData, int& nRow)
{
	CCapDeviceChBase *pCh = (CCapDeviceChBase*)pStData;

	Show_Index(pStData, nRow, CAPDEVICECHGRID_COL_INDEX);
	Show_StaticString(pStData, nRow, CAPDEVICECHGRID_COL_DESC, pCh->m_strName);
	Show_StaticString(pStData, nRow, CAPDEVICECHGRID_COL_ADDR, pCh->m_strID);
	Show_StaticString(pStData, nRow, CAPDEVICECHGRID_COL_TYPE, ((CCapDeviceSmvCh*)pCh)->GetChType());
	Show_Double(pStData, nRow, CAPDEVICECHGRID_COL_RATE, &((CCapDeviceSmvCh*)pCh)->m_fChRate,FALSE);
//	Show_Float(pStData, nRow, CAPDEVICECHGRID_COL_VALUE, &((CCapDeviceSmvCh*)pCh)->m_fValue, FALSE);		//显示计算值

	ShowColorRow(this, pCh->m_nMatchState,nRow,CAPDEVICECHGRID_COLS);
/*
	if ( ((CCapDeviceBase*)m_pDatas)->m_bSelect )
	{
		Show_Check(pStData, nRow, CAPDEVICECHGRID_COL_SELECT, &pCh->m_nSelect, EndEditCell_Select);
	}
	else
	{
		Show_StaticString(pStData, nRow, CAPDEVICECHGRID_COL_SELECT, m_strEmptyString);
	}

	Show_ChType(pStData, nRow, CAPDEVICECHGRID_COL_SET);
	Show_ChRate(pStData, nRow, CAPDEVICECHGRID_COL_DESC);
*/
}

void CCapDeviceChGrid::ShowData_GOOSE(CExBaseObject *pStData, int& nRow)
{
	CCapDeviceChBase *pCh = (CCapDeviceChBase*)pStData;

	Show_Index(pStData, nRow, CAPDEVICE_GSGRID_COL_INDEX);
	Show_StaticString(pStData, nRow, CAPDEVICE_GSGRID_COL_DESC, pCh->m_strName);
	Show_StaticString(pStData, nRow, CAPDEVICE_GSGRID_COL_ADDR, pCh->m_strID);
	Show_StaticString(pStData, nRow, CAPDEVICE_GSGRID_COL_TYPE, st_GetGooseChType(pCh->m_nChType, pCh->m_nLength));
//	Show_StaticString(pStData, nRow, CAPDEVICE_GSGRID_COL_VALUE, ((CCapDeviceGooseCh*)pCh)->m_oVar.ToString());

	ShowColorRow(this, pCh->m_nMatchState,nRow,CAPDEVICE_GSGRID_COLS);
/*
	Show_StaticString(pStData, nRow, CAPDEVICECHGRID_COL_SELECT, m_strEmptyString);
	Show_GsChType(pStData, nRow, CAPDEVICECHGRID_COL_SET);
	Show_ChType(pStData, nRow, CAPDEVICECHGRID_COL_DESC);
*/
}

void CCapDeviceChGrid::EndEditCell_Select (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CCapDeviceChBase *pCh = (CCapDeviceChBase*)pCell->lParam;
	ASSERT (pCh != NULL);
	pCh->m_nSelect = pCell->dwValue;

	AfxGetMainWnd()->PostMessage(WM_CAPDEVICECH_SELCHANGED, (WPARAM)pCh, (LPARAM)pCell->dwValue);
}

void CCapDeviceChGrid::EndEditCell_ChRate (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh*)pCell->lParam;
	ASSERT (pSmvCh != NULL);
	pSmvCh->SetChRateString(pCell->szText);
	pCell->szText = st_GetCapDeviceChRateString(pSmvCh->m_nChRateIndex);
	pGrid->InvalidateGrid(FALSE);

	AfxGetMainWnd()->PostMessage(WM_CAPDEVICECH_DATACHANGED, (WPARAM)pSmvCh, (LPARAM)pSmvCh);
}

void CCapDeviceChGrid::EndEditCell_ChType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh*)pCell->lParam;
	pSmvCh->SetChType(pCell->szText);
	pCell->szText = pSmvCh->GetChType();
	pGrid->InvalidateGrid(FALSE);

	AfxGetMainWnd()->PostMessage(WM_CAPDEVICECH_DATACHANGED, (WPARAM)pSmvCh, (LPARAM)pSmvCh);
}

void CCapDeviceChGrid::Show_ChRate(CExBaseObject *pStData, const int& nRow, const int& nCol)
{
	CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh*)pStData;
	GV_ITEM Item;
	InitDataCellItem(Item, pStData);
	Item.nDataType = GVET_COMBOBOX;
	Item.lParam = (LPARAM)pSmvCh;
	Item.szText = st_GetCapDeviceChRateString(pSmvCh->m_nChRateIndex);
	Item.row = nRow;
	Item.col = nCol;
	Item.pEditFunc = EndEditCell_ChRate;
	Item.mask |= GVIF_FUNC | GVIF_PARAM;

	SetItem(&Item);	
}

void CCapDeviceChGrid::Show_ChType(CExBaseObject *pStData, const int& nRow, const int& nCol)
{
	CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh*)pStData;
	GV_ITEM Item;
	InitDataCellItem(Item, pStData);
	Item.nDataType = GVET_COMBOBOX;
	Item.lParam = (LPARAM)pSmvCh;
	Item.pEditFunc = EndEditCell_ChType;
	Item.mask |= GVIF_FUNC | GVIF_PARAM;
	Item.szText = pSmvCh->GetChType();
	Item.row = nRow;
	Item.col = nCol;

	SetItem(&Item);	
}


void CCapDeviceChGrid::Show_GsChType(CExBaseObject *pStData, const int& nRow, const int& nCol)
{
	CCapDeviceGooseCh *pGooseCh = (CCapDeviceGooseCh*)pStData;
	GV_ITEM Item;
	InitDataCellItem(Item, pStData);
	Item.nDataType = GVET_NOEDIT;
	Item.lParam = (LPARAM)pGooseCh;
	Item.szText = st_GetGooseChType(pGooseCh->m_nChType, pGooseCh->m_nLength);
	Item.row = nRow;
	Item.col = nCol;
	Item.mask |= GVIF_FUNC | GVIF_PARAM;

	SetItem(&Item);	
}

void CCapDeviceChGrid::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)//填充comboList cell
{
	if (nCol == CAPDEVICECHGRID_COL_SET)
	{
		FillComboBoxItems_ChType(nRow, nCol, cltWnd);
	}
	else if (nCol == CAPDEVICECHGRID_COL_DESC)
	{
		FillComboBoxItems_ChRate(nRow, nCol, cltWnd);
	}
}


void CCapDeviceChGrid::FillComboBoxItems_ChRate(int nRow, int nCol, LPARAM cltWnd)//填充comboList cell
{
	CGridCell *pCell = GetCell(nRow, nCol);
	CComboBox *pComboBox = (CComboBox *)cltWnd;
	ASSERT(pComboBox != NULL);

	pComboBox->ResetContent();
	st_AddCapDeviceChRateTo(pComboBox);
}


void CCapDeviceChGrid::FillComboBoxItems_ChType(int nRow, int nCol, LPARAM cltWnd)//填充comboList cell
{
	CGridCell *pCell = GetCell(nRow, nCol);
	CComboBox *pComboBox = (CComboBox *)cltWnd;
	ASSERT(pComboBox != NULL);

	pComboBox->ResetContent();
	pComboBox->AddString(_T("电压"));
	pComboBox->AddString(_T("电流"));
}
