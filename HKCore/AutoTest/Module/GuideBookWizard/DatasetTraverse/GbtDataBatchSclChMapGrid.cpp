#include "StdAfx.h"
#include "GbtDataBatchSclChMapGrid.h"
#include "..\..\..\..\Module\API\GlobalApi.h"
#include "..\..\XLanguageResourceAts.h"
#define GBTDATA_SCLCH_RAMP_GRID_COLS             6
#define GBTDATA_SCLCH_RAMP_GRID_ID_INEX          0
#define GBTDATA_SCLCH_RAMP_GRID_ID_SCLNAME       1
#define GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME       2
#define GBTDATA_SCLCH_RAMP_GRID_ID_SCLAPPID      3
#define GBTDATA_SCLCH_RAMP_GRID_ID_SCLCHINDEX    4
#define GBTDATA_SCLCH_RAMP_GRID_ID_DATATYPE      5

CXMatchDatasetSelDlg* CGbtDataBatchSclChMapGrid::m_pXMatchDatasetSelDlg = NULL;
long CGbtDataBatchSclChMapGrid::g_nXMatchDatasetSelDlgRef = 0;


CXMatchRefObjectSelDlg* CGbtDataBatchSclChMapGrid::m_pXMatchRefObjectSelDlg = NULL;
long CGbtDataBatchSclChMapGrid::m_nXMatchRefObjectSelDlgRef = 0;

CGbtDataBatchSclChMapGrid::CGbtDataBatchSclChMapGrid(void)
{
	m_pGbtDataBatchSclChMapGen = NULL;
	m_pXMatchTool = NULL;
	m_pDataSelChangeMsgRcvWnd = NULL;
	m_nXMatchRefClassID = GBCLASSID_DATAOBJ;
	m_nAdjustBeginCol = 1;
}

CGbtDataBatchSclChMapGrid::~CGbtDataBatchSclChMapGrid(void)
{
	m_nXMatchRefObjectSelDlgRef--;

	if (m_nXMatchRefObjectSelDlgRef == 0)
	{
		if (m_pXMatchRefObjectSelDlg != NULL)
		{
			m_pXMatchRefObjectSelDlg->DestroyWindow();
			delete m_pXMatchRefObjectSelDlg;
			m_pXMatchRefObjectSelDlg = NULL;
		}
	}

	g_nXMatchDatasetSelDlgRef--;

	if (g_nXMatchDatasetSelDlgRef == 0)
	{
		if (m_pXMatchDatasetSelDlg != NULL)
		{
			m_pXMatchDatasetSelDlg->DestroyWindow();
			delete m_pXMatchDatasetSelDlg;
			m_pXMatchDatasetSelDlg = NULL;
		}
	}
}

void CGbtDataBatchSclChMapGrid::ShowGbtDataBatchSclChMap(CGbtDataBatchSclChMapGen *pGbtDataBatchSclChMapGen)
{
	ASSERT(pGbtDataBatchSclChMapGen != NULL);

	m_pGbtDataBatchSclChMapGen = pGbtDataBatchSclChMapGen;
	m_pXMatchTool = pGbtDataBatchSclChMapGen->GetMatchTool();
	ShowDatas(pGbtDataBatchSclChMapGen);
	OnDataSelChanged();
}

void CGbtDataBatchSclChMapGrid::ShowData(CExBaseObject *pExData, int& nRow, BOOL bInsertRow)
{
	if (bInsertRow)
	{
		InsertRow(NULL);
	}

	CGbtDataBatchSclChMap *pGbtDataTraverseObj = (CGbtDataBatchSclChMap *)pExData;
	UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
	nRow++;
}

void CGbtDataBatchSclChMapGrid::InitGrid()
{
	SetListMode(FALSE);
	SetRowCount(1);
	SetColumnCount(GBTDATA_SCLCH_RAMP_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CGbtDataBatchSclChMapGrid::InitGridTitle()
{
	CString cTempStr[GBTDATA_SCLCH_RAMP_GRID_COLS]={/*_T("编号")*/g_sLangTxt_Index, /*_T("SCL通道名")*/g_sLangTxt_SCLChannelName, /*_T("数据名称")*/g_sLangTxt_DataName, _T("APPID"), /*_T("通道编号")*/g_sLangTxt_ChannelIndex, /*_T("数据类型")*/g_sLangTxt_DataType};
	int iWidth[GBTDATA_SCLCH_RAMP_GRID_COLS]={60,200,160, 80, 80, 80};

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	SetRowCount(1);
	SetColumnCount(GBTDATA_SCLCH_RAMP_GRID_COLS);

	for (int iCol=0;iCol<GBTDATA_SCLCH_RAMP_GRID_COLS;iCol++)
	{
		Item.col = iCol + 0;
		SetColumnType(iCol,GVET_NOEDIT);
		SetColumnWidth(iCol,iWidth[iCol]);
		Item.szText=cTempStr[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
	}	

	SetRowHeight(0,20);
}

void CGbtDataBatchSclChMapGrid::ShowGbtDataTraverseObj(CGbtDataBatchSclChMap *pGbtDataTraverseObj, int &nRowIndex)
{
	InsertRow(_T(""));
	UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRowIndex);

	SetRowHeight(nRowIndex,20);
	nRowIndex++;
}

void CGbtDataBatchSclChMapGrid::UpdateGbtDataTraverseObj(CGbtDataBatchSclChMap *pGbtDataTraverseObj, int &nRowIndex)
{
	Show_Index(pGbtDataTraverseObj, nRowIndex, GBTDATA_SCLCH_RAMP_GRID_ID_INEX);
	Show_StaticString(pGbtDataTraverseObj, nRowIndex, GBTDATA_SCLCH_RAMP_GRID_ID_SCLNAME, &pGbtDataTraverseObj->m_pSclGinCh->m_strName);
	Show_StaticString(pGbtDataTraverseObj, nRowIndex, GBTDATA_SCLCH_RAMP_GRID_ID_SCLAPPID, &pGbtDataTraverseObj->m_pSclGinCh->m_strAppID);
	Show_StaticString(pGbtDataTraverseObj, nRowIndex, GBTDATA_SCLCH_RAMP_GRID_ID_SCLCHINDEX, &pGbtDataTraverseObj->m_pSclGinCh->m_strGsChIndex);
	Show_StaticString(pGbtDataTraverseObj, nRowIndex, GBTDATA_SCLCH_RAMP_GRID_ID_DATATYPE, &pGbtDataTraverseObj->m_pSclGinCh->m_strDataType);

	CString strText;
	GetMapDvmDataNameString(pGbtDataTraverseObj, strText);
	Show_StaticString(pGbtDataTraverseObj, nRowIndex, GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME, &strText);
}

void  CGbtDataBatchSclChMapGrid::EndEdit_ModelType(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataBatchSclChMap *pGbtDataTraverseObj = (CGbtDataBatchSclChMap*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);

	CGbtDataBatchSclChMapGrid *pThis = (CGbtDataBatchSclChMapGrid*)pGrid;
	pThis->UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
	pThis->Invalidate(FALSE);
}


void  CGbtDataBatchSclChMapGrid::EndEdit_BeginVal(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataBatchSclChMap *pGbtDataTraverseObj = (CGbtDataBatchSclChMap*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);

//	pGbtDataTraverseObj->m_dBeginVal = _wtof(pCell->szText);
	CGbtDataBatchSclChMapGrid *pThis = (CGbtDataBatchSclChMapGrid*)pGrid;
	pThis->UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
}


void  CGbtDataBatchSclChMapGrid::EndEdit_Step(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataBatchSclChMap *pGbtDataTraverseObj = (CGbtDataBatchSclChMap*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);

//	pGbtDataTraverseObj->m_dStep = _wtof(pCell->szText);
	CGbtDataBatchSclChMapGrid *pThis = (CGbtDataBatchSclChMapGrid*)pGrid;
	pThis->UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
}

void CGbtDataBatchSclChMapGrid::ShowXMatchRefObjectSelDlgDatas(long nRowIndex)
{
	if (m_pXMatchRefObjectSelDlg == NULL)
	{
		return;
	}

	if (!m_pXMatchRefObjectSelDlg->IsWindowVisible())
	{
		return;
	}

	CGbtDataBatchSclChMap *pSclChMap = (CGbtDataBatchSclChMap*)GetDataRow(nRowIndex);
	ShowXMatchRefObjectSelDlgDatas(pSclChMap);
}

void CGbtDataBatchSclChMapGrid::ShowXMatchRefObjectSelDlgDatas(CGbtDataBatchSclChMap *pSclChMap)
{
	if (m_pXMatchDatasetSelDlg != NULL)
	{
		m_pXMatchDatasetSelDlg->ShowWindow(SW_HIDE);
	}

	if (m_pXMatchRefObjectSelDlg == NULL)
	{
		m_nXMatchRefObjectSelDlgRef++;
		m_pXMatchRefObjectSelDlg = new CXMatchRefObjectSelDlg(this, this);
		m_pXMatchRefObjectSelDlg->SetWindowTitle(/*_T("选择匹配的数据对象")*/g_sLangTxt_SelMatchDataObject);
		m_pXMatchRefObjectSelDlg->SetUseModeless();
		m_pXMatchRefObjectSelDlg->DoModal();
	}
	else
	{
		if (!m_pXMatchRefObjectSelDlg->IsWindowVisible())
		{
			m_pXMatchRefObjectSelDlg->ShowWindow(SW_SHOW);
		}

		m_pXMatchRefObjectSelDlg->BringWindowToTop();
	}

	CExBaseList *pDatas = m_pGbtDataBatchSclChMapGen->GetXMatchList(pSclChMap);
	m_pXMatchRefObjectSelDlg->ShowExBaseList(pDatas, TRUE);
	m_pXMatchRefObjectSelDlg->m_pEdit = this;
}

void CGbtDataBatchSclChMapGrid::ShowXMatchRefObjectSelDlgDataset()
{
	if (m_pXMatchRefObjectSelDlg != NULL)
	{
		m_pXMatchRefObjectSelDlg->ShowWindow(SW_HIDE);
	}

	if (m_pXMatchDatasetSelDlg == NULL)
	{
		g_nXMatchDatasetSelDlgRef++;
		m_pXMatchDatasetSelDlg = new CXMatchDatasetSelDlg(this, this);
		m_pXMatchDatasetSelDlg->SetWindowTitle(/*_T("选择匹配的数据对象")*/g_sLangTxt_SelMatchDataObject);
		m_pXMatchDatasetSelDlg->SetUseModeless();
		m_pXMatchDatasetSelDlg->DoModal();

		CExBaseList *pListDataset = m_pGbtDataBatchSclChMapGen->GetAllDataset();
		POS pos = pListDataset->GetHeadPosition();
		CExBaseList *p = NULL;

		while (pos != NULL)
		{
			p = (CExBaseList *)pListDataset->GetNext(pos);
			m_pXMatchDatasetSelDlg->AddDataset(p);
		}
	}
	else
	{
		if (!m_pXMatchDatasetSelDlg->IsWindowVisible())
		{
			m_pXMatchDatasetSelDlg->ShowWindow(SW_SHOW);
		}

		m_pXMatchDatasetSelDlg->BringWindowToTop();

		CGbtDataScriptMap *pGbtScptMap = NULL;
		pGbtScptMap = (CGbtDataScriptMap*)GetItemData(m_idCurrentCell.row, GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME);

		if (pGbtScptMap != NULL)
		{
			if (pGbtScptMap->GetCount() == 1)
			{
				m_pXMatchDatasetSelDlg->SelectData(pGbtScptMap->GetHead());
			}
		}
	}

	m_pXMatchDatasetSelDlg->m_pEdit = this;
}

void CGbtDataBatchSclChMapGrid::GetMapDvmDataNameString(CGbtDataBatchSclChMap *pGbtDataTraverseObj, CString &strText)
{
	if (pGbtDataTraverseObj->m_pDataObj != NULL)
	{
		strText = pGbtDataTraverseObj->m_pDataObj->m_strName;
	}
	else
	{
		CExBaseList *pListMatch = m_pGbtDataBatchSclChMapGen->GetXMatchList(pGbtDataTraverseObj);

		if (pListMatch == NULL)
		{
			strText.Empty();
		}
		else
		{
			if (pListMatch->GetCount() > 0)
			{
				CExBaseObject *pObj = pListMatch->GetHead();

				if (pListMatch->GetCount() > 1)
				{
					strText.Format(_T("【%s】【***】"), pObj->m_strName);
				}
				else
				{
					pGbtDataTraverseObj->m_pDataObj = (CDataObj*)pObj;
					strText = pObj->m_strName;
				}
			}
			else
			{
				strText.Empty();
			}
		}
	}
}

void CGbtDataBatchSclChMapGrid::SetMatchRefData(CExBaseObject *pRefObject)
{
	if (m_idCurrentCell.row == 0 || m_idCurrentCell.row >= m_nRows)
	{
		return;
	}

	if (pRefObject != NULL)
	{
		if (pRefObject->GetClassID() != m_nXMatchRefClassID)
		{
			return;
		}
	}
	else
	{
		CGbtDataBatchSclChMap *pSclChMap = NULL;
		pSclChMap = (CGbtDataBatchSclChMap*)GetDataRow(m_idCurrentCell.row, GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME);
		pSclChMap->m_pDataObj = NULL;
		CExBaseList *pListMatch = m_pGbtDataBatchSclChMapGen->GetXMatchList(pSclChMap);

		if (pListMatch != NULL)
		{
			pListMatch->RemoveAll();
		}

		UpdateGbtDataTraverseObj(pSclChMap, m_idCurrentCell.row);
		AutoSizeColumn(GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME);
		Invalidate(FALSE);
		OnDataSelChanged();
		return;
	}

	CExBaseList *pDataset = (CExBaseList*)pRefObject->GetParent();
	long nCurrIndex = pDataset->FindIndex(pRefObject);
	CGbtDataBatchSclChMap *pSclChMap = NULL;
	int nRowIndex = 0;

	if (m_SelectedCellMap.GetCount() > 0)
	{
		POSITION pos = NULL;
		long nIndex = 0;
		long nMinRow = 65536;
		DWORD key;
		CCellID cell;

		for (pos = m_SelectedCellMap.GetStartPosition(); pos != NULL; )
		{
			m_SelectedCellMap.GetNextAssoc(pos, key, (CCellID&)cell);

			if (!IsValid(cell)) 
			{
				continue;
			}

			nMinRow = min(nMinRow, cell.row);
		}

		for (pos = m_SelectedCellMap.GetStartPosition(); pos != NULL; )
		{
			m_SelectedCellMap.GetNextAssoc(pos, key, (CCellID&)cell);

			if (!IsValid(cell)) 
			{
				continue;
			}

			nRowIndex = cell.row;
			nIndex = nRowIndex - nMinRow + nCurrIndex;

			SetMatchRefData(pRefObject, nRowIndex, nIndex);
		}
	}
	else
	{
		nRowIndex = m_idCurrentCell.row;
		SetMatchRefData(pRefObject, nRowIndex, nCurrIndex);
	}
	
	AutoSizeColumn(GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME);
	Invalidate(FALSE);

	OnDataSelChanged();
}

void CGbtDataBatchSclChMapGrid::SetMatchRefData(CExBaseObject *pRefObject, int nRowIndex, int nDataIndex)
{
	if (nRowIndex <= 0 || nRowIndex >= m_nRows)
	{
		return;
	}

	CExBaseList *pDataset = (CExBaseList*)pRefObject->GetParent();
	CGbtDataBatchSclChMap *pSclChMap = NULL;
	pSclChMap = (CGbtDataBatchSclChMap*)GetDataRow(nRowIndex, GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME);
	pSclChMap->m_pDataObj = (CDataObj*)pDataset->GetAtIndex(nDataIndex);
	UpdateGbtDataTraverseObj(pSclChMap, nRowIndex);

	CExBaseList *pListMatch = m_pGbtDataBatchSclChMapGen->GetXMatchList(pSclChMap);

	if (pListMatch != NULL)
	{
		pListMatch->RemoveAll();
	}
}

void CGbtDataBatchSclChMapGrid::SetMatchRefData(CExBaseObject *pRefObject, const CCellID &idCell)
{
	if (idCell.row == 0 || idCell.row >= m_nRows)
	{
		return;
	}

	if (idCell.col != GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME)
	{
		return;
	}

	int nRowIndex = idCell.row;
	CGbtDataBatchSclChMap *pSclChMap = NULL;
	pSclChMap = (CGbtDataBatchSclChMap*)GetDataRow(nRowIndex, GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME);
	pSclChMap->m_pDataObj = (CDataObj*)pRefObject;

	CExBaseList *pListMatch = m_pGbtDataBatchSclChMapGen->GetXMatchList(pSclChMap);

	if (pListMatch != NULL)
	{
		pListMatch->RemoveAll();
	}

	UpdateGbtDataTraverseObj(pSclChMap, nRowIndex);

	AutoSizeColumn(GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME);
	Invalidate(FALSE);
}


BOOL CGbtDataBatchSclChMapGrid::OnCellRButtonUp(const CCellID &idCell)
{
	if (!idCell.IsValid())
	{
		return FALSE;
	}

	if (idCell.row <= 0 || idCell.col <= 0)
	{
		return FALSE;
	}

	if (idCell.col != GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME)
	{
		return FALSE;
	}

	SetFocusCell(-1,-1);
	SetFocusCell(idCell.row,idCell.col);
	m_LeftClickDownCell = idCell;
	m_idCurrentCell = idCell;

	CGbtDataBatchSclChMap *pSclChMap = NULL;
	pSclChMap = (CGbtDataBatchSclChMap*)GetDataRow(idCell.row, GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME);

	ShowXMatchRefObjectSelDlgDatas(pSclChMap);

	return TRUE;
}

BOOL CGbtDataBatchSclChMapGrid::OnCellKeyDelete(const CCellID &idCell)
{
	POSITION pos = NULL;

	for (pos = m_SelectedCellMap.GetStartPosition(); pos != NULL; )
	{
		DWORD key;
		CCellID cell;
		m_SelectedCellMap.GetNextAssoc(pos, key, (CCellID&)cell);

		if (IsValid(cell)) 
		{
			SetMatchRefData(NULL, cell);
		}
	}

	OnDataSelChanged();

	return TRUE;
}

void CGbtDataBatchSclChMapGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	if (nRow == -1)
	{
		return;
	}

	if (nCol != GBTDATA_SCLCH_RAMP_GRID_ID_DVMNAME)
	{
		return CGridCtrl::OnEditCell(nRow, nCol, nChar);
	}

	if (nChar == VK_LBUTTON)
	{
		ShowXMatchRefObjectSelDlgDataset();
	}
}


void  CGbtDataBatchSclChMapGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
	CGridCtrl::OnEditCell(nRow, nCol, nChar);
}