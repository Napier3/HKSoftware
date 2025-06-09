#include "StdAfx.h"
#include "ExBaseListGrid.h"
#include "..\XLanguage\XLanguageResource.h"
#include "..\API\MathApi.h"
#include "..\API\GloblaDrawFunctions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
void exgrid_get_SYSTEMTIME_string(CString &strText, SYSTEMTIME &tm, UINT nFormat)
{
	switch (nFormat)
	{
	case VCD_TIME_FORMAT_SHORT:
		strText.Format(_T("%d-%d-%d"), tm.wYear, tm.wMonth, tm.wDay);
		break;

	case VCD_TIME_FORMAT_SHORT_CHN:
		strText.Format(_T("%d年%d月%d日"), tm.wYear, tm.wMonth, tm.wDay);
		break;

	case VCD_TIME_FORMAT_LONG:
		strText.Format(_T("%d-%d-%d %d:%d:%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
		break;

	case VCD_TIME_FORMAT_LONG_CHN:
		strText.Format(_T("%d年%d月%d日 %d时%d分%d秒"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
		break;

	default:
		strText.Format(_T("%d-%d-%d"), tm.wYear, tm.wMonth, tm.wDay);
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
//CExBaseListGrid
const CString CExBaseListGrid::m_strEmptyString = _T("");

BOOL CExBaseListGrid::Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	InsertData(pData, bInvalidate);

	return TRUE;
}

BOOL CExBaseListGrid::Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate)
{
	UpdateData(pData);

	return TRUE;
}

BOOL CExBaseListGrid::Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther, BOOL bInvalidate)
{
	long nRow = GetDataRow(pData, 0);

	if (nRow < 0)
	{
		return FALSE;
	}
	else
	{
		DeleteRow(nRow);
		return TRUE;
	}
}

BOOL CExBaseListGrid::Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate)
{
	long nRow = GetDataRow(pData, 0);

	if (nRow < 0)
	{
		return FALSE;
	}
	else
	{
		SelectRow(nRow);
		return TRUE;
	}
}


CExBaseListGrid::CExBaseListGrid()
{
	m_crBkColor = RGB(255, 255, 255);
	m_crTextColor = RGB(0, 0, 0);
	m_crTitleTextBkColor = RGB(192, 192, 192);
	m_crDataTextBkColor = RGB(255, 255, 255);

	m_pCurrData = NULL;
	m_pDatas = NULL;

	SetListMode(TRUE);
	m_Logfont.lfHeight = 12;
	m_pDataViewOptrInterface = NULL;
	SetBkColor(RGB(255, 255, 255));
	m_nAdjustBeginCol = -1;
	m_nRowHeight = EXBASEGRID_ROWHEIGHT;
}


CExBaseListGrid::~CExBaseListGrid(void)
{
	m_listVCellData.DeleteAll();
}

void  CExBaseListGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
	OnDataSelChanged(nRow, nCol);;
	CGridCtrl::OnEditCell(nRow, nCol, nChar);
}

void CExBaseListGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	if (m_pDataViewOptrInterface != NULL)
	{
		if (m_pDataViewOptrInterface->OnEditCellLBDblClk(this, nRow, nCol, nChar))
		{
			return;
		}
	}

	CGridCtrl::OnEditCellLBDblClk(nRow, nCol, nChar);
}

void CExBaseListGrid::OnDataSelChanged(int nRow, int nCol)
{
	if (nRow == -1 || nCol == -1)
	{
		return;
	}

	if (m_pDataViewOptrInterface != NULL)
	{
		m_pDataViewOptrInterface->OnDataSelChanged(this, nRow, nCol);
	}
}

void CExBaseListGrid::DataViewOptr_DataChanged(int nRow, int nCol)
{
	DataViewOptr_DataChanged(this, nRow, nCol);
}

void CExBaseListGrid::DataViewOptr_DataChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if (m_pDataViewOptrInterface != NULL)
	{
		m_pDataViewOptrInterface->OnDataEditChanged(pGridCtrl, nRow, nCol);
	}
}

void CExBaseListGrid::FreeExBaseCellData(long nRow, long nCol)
{
	CGridCell *pCell = GetCell(nRow, nCol);

	if (pCell == NULL)
	{
		return;
	}

	if (pCell->lParam == 0)
	{
		return;
	}

	m_listVCellData.Delete((PEXBASECELLDATA)pCell->lParam);
	pCell->lParam = 0;
}

void CExBaseListGrid::MoveUp()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(1);

	long nRow = GetDataRow(pSel);//m_pDatas->FindIndex(pSel);

	if (nRow <= 1)
	{
		return;
	}

	CExBaseObject *p1 = GetData(nRow-1);
	CExBaseObject *p2 = GetData(nRow);
	ClearSelect();
	m_pDatas->ChangePosition(p1, p2);
	ChangeRowPosition(nRow-1, nRow);
	UpdateDataIndex();
	SelectRow(nRow-1);
	SetModifiedFlag(m_pDatas);
}

void CExBaseListGrid::MoveDown()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(1);

	long nRow = GetDataRow(pSel);//m_pDatas->FindIndex(pSel);

	if (nRow >= GetRowCount() - 1)
	{
		return;
	}

	CExBaseObject *p1 = GetData(nRow+1);
	CExBaseObject *p2 = GetData(nRow);
	ClearSelect();
	m_pDatas->ChangePosition(p1, p2);
	ChangeRowPosition(nRow, nRow+1);
	UpdateDataIndex();
	SelectRow(nRow+1);
	SetModifiedFlag(m_pDatas);

}

void CExBaseListGrid::DeleteSelRows(BOOL bDeleteData, int nStateForCol)
{
	CExBaseList oList;
	GetCurrSelDatas(oList, nStateForCol);
	long nRow = 1;
	long nCount = GetRowCount();
	CExBaseObject* p =  NULL;

	POS pos = oList.GetHeadPosition();
	
	while (pos != NULL)
	{
		p = (CExBaseObject*)oList.GetNext(pos);
		ASSERT(p != NULL);

		nRow = GetDataRow(p);

		if (nRow > 0)
		{
			DeleteRow(nRow);
		}

		if (bDeleteData)
		{
			m_pDatas->Delete(p);
		}
	}

	ClearSelect();
	oList.RemoveAll();

	Invalidate(TRUE);
}

void CExBaseListGrid::DeleteSelRow(BOOL bDeleteDate)
{
	if (!IsValid(m_idCurrentCell))
	{
		return;
	}

	CExBaseObject *pData = GetCurrSelData(m_idCurrentCell.col);

	if (pData != NULL && bDeleteDate)
	{
		CExBaseList *pParent = (CExBaseList*)pData->GetParent();
		pParent->Delete(pData);
		SetModifiedFlag(pParent, TRUE);
	}

	DeleteRow(m_idCurrentCell.row);
	ResetScrollBars();
	Invalidate(FALSE);
}

long CExBaseListGrid::DeleteDataRow(CExBaseObject *pData, BOOL bDeleteData)
{
	long nRow = GetDataRow(pData, 1);

	if (nRow <= 0)
	{
		return -1;
	}

	if (bDeleteData)
	{
		CExBaseList *pParent = (CExBaseList*)pData->GetParent();
		pParent->Delete(pData);
		SetModifiedFlag(pParent, TRUE);
	}

	DeleteRow(nRow);
	ResetScrollBars();
	Invalidate(FALSE);

	return nRow;
}

void CExBaseListGrid::FreeExBaseCellData(long nRow)
{
	long nCols = GetColumnCount();
	long nCol = 0;

	for (nCol=0; nCol<nCols; nCol++)
	{
		FreeExBaseCellData(nRow, nCol);
	}
}

void CExBaseListGrid::InitGridTitle(const CString *pStrTitles, const int *pnWidth, int nCols)
{
	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	for (int iCol=0;iCol<nCols;iCol++)
	{
		Item.col = iCol+0;
		SetColumnType(iCol,GVET_NOEDIT);
		SetColumnWidth(iCol,pnWidth[iCol]);
		Item.szText=pStrTitles[iCol];
		Item.lParam=0;//iCol;
		SetItem(&Item);
	}	

	SetRowHeight(0,EXBASEGRID_ROWHEIGHT);
	SetFont(g_pGlobalFont16);   //shaolei  2021.03.13
}


BOOL CExBaseListGrid::UpdateData(CExBaseObject *pData)
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
		ShowData(pData, nRow, FALSE);
		AdjustAllCols(TRUE);
		Invalidate(FALSE);
	}
	else
	{
	}

	return TRUE;
}

BOOL CExBaseListGrid::UpdateDataIndex(long nRowBegin, long nIndexCol)
{
	long nRow = nRowBegin;
	CString strText;

	for (nRow = nRowBegin; nRow<m_nRows; nRow++)
	{
		strText.Format(_T("%d"), nRow);
		SetItemText(nRow, nIndexCol, strText);
	}

	Invalidate(FALSE);

	return TRUE;
}

CExBaseObject* CExBaseListGrid::GetCurrCellData()
{
	if (!IsValid(m_idCurrentCell))
	{
		return NULL;
	}

	PEXBASECELLDATA pCellData = (PEXBASECELLDATA)GetItemData(m_idCurrentCell.row, m_idCurrentCell.col);

	if (pCellData != NULL)
	{
		return pCellData->pObj;
	}

	return NULL;
}

CExBaseObject* CExBaseListGrid::GetData(int nRow, long nCol)
{
	PEXBASECELLDATA pCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol);
	//ASSERT (pCellData != NULL);

	if (pCellData != NULL)
	{
		return pCellData->pObj;
	}

	return NULL;
}

CExBaseObject* CExBaseListGrid::GetCurrSelData(long nStateForCol)
{
	CExBaseObject *pSelData = NULL;

	if (IsValid(m_idCurrentCell))
	{
		pSelData = GetDataRow(m_idCurrentCell.row);

		if (pSelData != NULL)
		{
			return pSelData;
		}
	}

	if (m_nRows <= 1)
	{
		return NULL;
	}

	long nRow = 1;
	long nCount = 0;
	UINT nState = 0;

	for (nRow=1; nRow < m_nRows; nRow++)
	{
		nState = GetItemState(nRow, nStateForCol);

		if ( (nState & GVIS_SELECTED) == GVIS_SELECTED
			|| (nState & GVIS_FOCUSED) == GVIS_FOCUSED)
		{
			pSelData = GetDataRow(nRow);
			nCount++;
		}
	}

	if (nCount > 1)
	{
		return NULL;
	}
	else
	{
		return pSelData;
	}
}

long CExBaseListGrid::GetCurrSelRow(long nStateForCol)
{
	CExBaseObject *pSelData = NULL;

	if (IsValid(m_idCurrentCell))
	{
		return m_idCurrentCell.row;
	}

	if (m_nRows <= 1)
	{
		return -1;
	}

	long nRow = 1;
	UINT nState = 0;

	for (nRow=1; nRow < m_nRows; nRow++)
	{
		nState = GetItemState(nRow, nStateForCol);

		if ( (nState & GVIS_SELECTED) == GVIS_SELECTED
			|| (nState & GVIS_FOCUSED) == GVIS_FOCUSED)
		{
			return nRow;
		}
	}

	return -1;
}

long CExBaseListGrid::GetCurrSelDatas(CExBaseList &listDatas, long nStateForCol)
{
	long nRow = 1;
	UINT nState = 0;
	CExBaseObject *pSelData = NULL;
	listDatas.RemoveAll();

	for (nRow=1; nRow < m_nRows; nRow++)
	{
		nState = GetItemState(nRow, nStateForCol);

		if ( (nState & GVIS_SELECTED) == GVIS_SELECTED
			|| (nState & GVIS_FOCUSED) == GVIS_FOCUSED)
		{
			pSelData = GetDataRow(nRow);
			listDatas.AddTail(pSelData);
		}
	}

	return listDatas.GetCount();
}

long CExBaseListGrid::GetDataRowEx(CExBaseObject *pData, long nFromRow, long nCol)
{
	if (pData == NULL)
	{
		return -1;
	}

	long nIndex = -1;
	long nRows = GetRowCount();
	long nRow = nFromRow;

	for (; nRow<nRows; nRow++)
	{
		PEXBASECELLDATA pCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol);
		ASSERT (pCellData != NULL);

		if (pCellData != NULL)
		{
			if (pCellData->pObj == pData)
			{
				nIndex = nRow;
				break;
			}
		}
	}

	return nIndex;
}

long CExBaseListGrid::GetDataRow(CExBaseObject *pData, long nCol)
{
	return GetDataRowEx(pData, 1, nCol);
}

CExBaseObject* CExBaseListGrid::GetDataRow(long nRow, long nCol)
{
	if (m_nRows <= nRow)
	{
		return NULL;
	}

	PEXBASECELLDATA pCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol);

	if (pCellData == NULL)
	{
		return NULL;
	}

	return pCellData->pObj;
}


void CExBaseListGrid::GetAllSelectDatas(CExBaseList *pList, long nStateForCol)
{
	long nCount = GetRowCount();
	long nRow = 1;
	UINT nState = 0;

	for (nRow=1; nRow<nCount; nRow++)
	{
		nState = GetItemState(nRow, nStateForCol);

		if ( (nState & GVIS_SELECTED) == GVIS_SELECTED
			|| (nState & GVIS_FOCUSED) == GVIS_FOCUSED)
		{
			pList->AddTail(GetDataRow(nRow));
		}
	}
}

void CExBaseListGrid::ClearSelect()
{
	CGridCtrl::ClearSelect();
}

void CExBaseListGrid::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)//填充comboList cell
{
	CGridCell *pCell = GetCell(nRow, nCol);
	ASSERT(pCell != NULL);
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA )pCell->lParam;
	ASSERT(pVCellData != NULL);
	CExBaseList *pExBaseList = pVCellData->pExBaseList;

	if (pExBaseList != NULL)
	{
		CComboBox *pComboBox = (CComboBox *)cltWnd;
		ASSERT(pComboBox != NULL);

		pComboBox->ResetContent();

		if (is_exgrid_cmb_set_add_empty(pExBaseList))
		{
			pComboBox->AddString(_T(""));
			pComboBox->SetItemDataPtr(0, NULL);
		}

		pExBaseList->InsertChildreComboBox(pComboBox);
	}
}

BOOL CExBaseListGrid::EndEditCell(int nRow, int nCol, DWORD dwItemData)//保存编辑
{
	CGridCell *pCell = GetCell(nRow, nCol);

	if (pCell == NULL)
	{
		return FALSE;
	}

	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;

	if (pVCellData == NULL)
	{
		return FALSE;
	}

	if (pVCellData->pFunc != NULL)
	{
		pVCellData->pFunc(nRow, nCol, pCell, this);
		return TRUE;
	}

	if (pCell->pEditFunc != NULL)
	{
		pCell->pEditFunc(nRow, nCol, pCell, this);
		return TRUE;
	}

	switch (pVCellData->nVt)
	{
	case VCD_LONG:
		if (*(pVCellData->pnValue) != pCell->dwValue)
		{
			*(pVCellData->pnValue) = pCell->dwValue;
		}
		break;

	case VCD_DWORD:
		if (*(pVCellData->pdwValue) != pCell->dwValue)
		{
			*(pVCellData->pdwValue) = pCell->dwValue;
		}
		break;

	case VCD_DOUBLE:
		//*(pVCellData->pdValue) = _wtof(pCell->szText);
		break;

	case VCD_STRING:
		if (*(pVCellData->pString) != pCell->szText)
		{
			*(pVCellData->pString) = pCell->szText;
		}

		break;
	}

	return TRUE;
}

 void CExBaseListGrid::InsertData(CExBaseObject *pData, BOOL bInvalidate)
 {
	 int nRow = m_nRows;
	 SetRowCount(m_nRows + 1);
	 ShowData(pData, nRow, FALSE);

	 SetRowHeight(m_nRows-1, EXBASEGRID_ROWHEIGHT);
	 AdjustAllCols();

	 if (bInvalidate)
	 {
		 Invalidate(FALSE);
	 }
 }

 long CExBaseListGrid::GetDatasCount()
 {
	 ASSERT (m_pDatas != NULL);

	 if (m_pDatas == NULL)
	 {
		 return 0;
	 }
	 else
	 {
		 return m_pDatas->GetCount();
	 }
 }

void CExBaseListGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_idCurrentCell.col = -1;
	m_idCurrentCell.row = -1;
	ClearSelect();
	CTLinkList <_ExBaseCellData> listVCellData;
	BackListCellData(listVCellData);
	//m_listVCellData.DeleteAll();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(1);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 1;
	long nCalRows = GetDatasCount() + 1;//pDatas->GetCount() + 1;
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

void CExBaseListGrid::AfterShowDatas(long nBeginRow, BOOL bResetScrollBars)
{
	long nRowIndex = nBeginRow;

	for (; nRowIndex<m_nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, m_nRowHeight);
	}

	AdjustAllCols(bResetScrollBars);

	if (bResetScrollBars)
	{
		ResetScrollBars();
	}

	Invalidate(FALSE);
}

void CExBaseListGrid::UpdateDatas()
{
	CTLinkList <_ExBaseCellData> listVCellData;
	BackListCellData(listVCellData);
//	m_listVCellData.DeleteAll();
	m_pCurrData = NULL;
	ASSERT(m_pDatas != NULL);

	if (m_pDatas == NULL)
	{
		return;
	}

	CExBaseObject *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 1;
	long nCalRows = m_pDatas->GetCount() + 1;
	SetRowCount(nCalRows);

	while (pos != NULL)
	{
		pObj = m_pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex);
	AdjustAllCols();
	ResetScrollBars();
	Invalidate(FALSE);
}

void CExBaseListGrid::AdjustAllCols(BOOL bResetScrollBars)
{
	if (m_nAdjustBeginCol < 0)
	{
		return;
	}

	long nCols = GetColumnCount();
	long nCol = m_nAdjustBeginCol;

	for (nCol=m_nAdjustBeginCol; nCol<nCols; nCol++)
	{
		AutoSizeColumn(nCol, bResetScrollBars);
	}
}

CExBaseObject* CExBaseListGrid::GetVCellData(CGridCell *pCell)
{
	if (pCell->lParam == 0)
	{
		return NULL;
	}

	return ((PEXBASECELLDATA)pCell->lParam)->pObj;
}

CExBaseObject* CExBaseListGrid::GetVCellData(const CCellID &oCellID)
{
	if (!IsValid(oCellID))
	{
		return NULL;
	}

	PEXBASECELLDATA p = (PEXBASECELLDATA)GetItemData(oCellID.row, oCellID.col);

	if (p == NULL)
	{
		return NULL;
	}

	return p->pObj;
}

void CExBaseListGrid::Show_Index(CExBaseObject *pData, const int& nRow, const int& nCol)
{
	FreeExBaseCellData(nRow, nCol);

	GV_ITEM Item;
	Item.row = nRow;
	Item.col = nCol;
	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_FORMAT;
	Item.nDataType = GVET_NOEDIT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(&(pData->m_strID), pData, NULL, NULL);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(_T("%d"), Item.row);

	Item.pEditFunc = NULL;

	SetItem(&Item);
}

void CExBaseListGrid::Show_IndexEx(CExBaseObject *pData, const int& nRow, const int& nCol, long nIndex)
{
	GV_ITEM Item;

	Item.row = nRow;
	Item.col = nCol;
	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_FORMAT;
	Item.nDataType = GVET_NOEDIT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(&(pData->m_strID), pData, NULL, NULL);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(_T("%d"), nIndex);

	Item.pEditFunc = NULL;

	SetItem(&Item);
}
void CExBaseListGrid::Show_IndexSingle(CExBaseObject *pData, const int& nRow, const int& nCol)
{
	GV_ITEM Item;

	Item.row = nRow;
	Item.col = nCol;
	Item.mask = GVIF_TEXT | GVIF_FORMAT;
	Item.nDataType = GVET_NOEDIT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.szText.Format(_T("%d"), Item.row);

	SetItem(&Item);
}

void CExBaseListGrid::Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData);

	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_STRBLOCKS;
	Item.row = nRow;
	Item.col = nCol;
	Item.nDataType = GVET_NOEDIT;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pString, pData,NULL, NULL);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText = *pString;
	Item.pStrCmpBlocks = NULL;

	Item.pEditFunc = NULL;

	SetItem(&Item);
}

void CExBaseListGrid::Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strString)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData);

	Item.mask |= GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE  | GVIF_STRBLOCKS;
	Item.row = nRow;
	Item.col = nCol;
	Item.nDataType = GVET_NOEDIT;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData((CString*)NULL, pData,NULL, NULL);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText = strString;
	Item.pEditFunc = NULL;
	Item.pStrCmpBlocks = NULL;

	SetItem(&Item);
}

void CExBaseListGrid::Show_StringCmp(CExBaseObject *pData, const int& nRow, const int& nCol, CStringCmpBlocks *pStrCmpBlks)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData);

	Item.mask = GVIF_PARAM | GVIF_STRBLOCKS | GVIF_DATATYPE | GVIF_STRBLOCKS;
	Item.row = nRow;
	Item.col = nCol;
	Item.nDataType = GVET_NOEDIT;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pStrCmpBlks, pData,NULL, NULL);
	Item.lParam = (LPARAM)pVCellData;
	Item.pStrCmpBlocks = pStrCmpBlks;
	Item.pEditFunc = NULL;

	SetItem(&Item);
}

void CExBaseListGrid::Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData);

	Item.row = nRow;
	Item.col = nCol;
	Item.mask |= GVIF_FUNC;
	Item.mask |= GVIF_PARAM;
	Item.mask |= GVIF_STRBLOCKS;
	Item.nDataType = GVET_EDITBOX;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pString, pData,NULL, pFunc);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText = *pString;

	if (pFunc != NULL)
	{
		Item.pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		Item.pEditFunc = EndEditCell_String;
		pVCellData->pFunc = EndEditCell_String;
	}
// 	if (pVCellData->pFunc == NULL)
// 	{
// 		pVCellData->pFunc = EndEditCell_String;
// 	}

	SetItem(&Item);
}

void CExBaseListGrid::Show_Time(CExBaseObject *pData, const int& nRow, const int& nCol, SYSTEMTIME *ptmTime, UINT nTimeFormat, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData);

	Item.row = nRow;
	Item.col = nCol;
	Item.mask |= GVIF_FUNC;
	Item.mask |= GVIF_PARAM;
	Item.mask |= GVIF_STRBLOCKS;
	Item.nDataType = bCanEdit ? GVET_DATECTRL : GVET_NOEDIT;

	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(ptmTime, nTimeFormat, pData,NULL, pFunc);
	Item.lParam = (LPARAM)pVCellData;
	exgrid_get_SYSTEMTIME_string(Item.szText, *ptmTime, nTimeFormat);

	if (pFunc != NULL)
	{
		Item.pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		Item.pEditFunc = EndEditCell_Time;
		pVCellData->pFunc = EndEditCell_Time;
	}

	SetItem(&Item);
}

void CExBaseListGrid::Show_WString(CExBaseObject *pData, const int& nRow, const int& nCol, wchar_t *pString, GRID_CELL_EDIT_FUNC pFunc)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData);

	Item.row = nRow;
	Item.col = nCol;
	Item.mask |= GVIF_FUNC;
	Item.mask |= GVIF_PARAM;
	Item.mask |= GVIF_STRBLOCKS;
	Item.nDataType = GVET_EDITBOX;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pString, pData,NULL, pFunc);
	Item.lParam = (LPARAM)pVCellData;

	Item.szText = pString;

	if (pFunc != NULL)
	{
		Item.pEditFunc = pFunc;
	}
	else
	{
		Item.pEditFunc = EndEditCell_WString;
	}
// 	if (pVCellData->pFunc == NULL)
// 	{
// 		pVCellData->pFunc = EndEditCell_String;
// 	}

	SetItem(&Item);
}

void CExBaseListGrid::InitDataCellItem(GV_ITEM& Item, CExBaseObject *pObj)
{
	InitGirdItem(Item);
	Item.crFgClr = m_crTextColor;
	Item.crBkClr = m_crDataTextBkColor;

}

void CExBaseListGrid::InitDataCellItem(GV_ITEM& Item, CExBaseObject *pObj, const int& nRow, const int& nCol, BOOL bSetColor)
{
	InitGirdItem(Item);
	Item.crFgClr = m_crTextColor;
	Item.crBkClr = m_crDataTextBkColor;
	Item.row = nRow;
	Item.col = nCol;

	Item.mask |= GVIF_PARAM;
	Item.mask |= GVIF_FUNC;
	Item.mask |= GVIF_STRBLOCKS;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	if (!bSetColor)
	{
		Item.mask &= ~GVIF_FGCLR;
		Item.mask &= ~GVIF_BKCLR;
	}
}

void CExBaseListGrid::EndEditCell_String (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_STRING);

	if (*pVCellData->pString != pCell->szText)
	{
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		*pVCellData->pString = pCell->szText;
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}

	if (((CExBaseListGrid*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListGrid::EndEditCell_Time (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_SYSTEMTIME);

// 	if (*pVCellData->pString != pCell->szText)
// 	{
// 		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
// 		*pVCellData->pString = pCell->szText;
// 		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
// 	}
// 
// 	if (((CExBaseListGrid*)pGrid)->m_nAdjustBeginCol >= 0)
// 	{
// 		pGrid->AutoSizeColumn(nCol);
// 		pGrid->ResetScrollBars();
// 		pGrid->InvalidateGrid(FALSE);
// 	}
}

void CExBaseListGrid::EndEditCell_WString (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_WSTRING);

#ifdef _UNICODE
	if (wcscmp(pVCellData->pWString,pCell->szText) != 0)
#else
	BSTR bstrText = pCell->szText.AllocSysString();
	if (wcscmp(pVCellData->pWString,bstrText) != 0)
#endif
	{
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
#ifdef _UNICODE
		wcscpy(pVCellData->pWString, pCell->szText);
#else
		wcscpy(pVCellData->pWString, bstrText);
#endif
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}

#ifdef _UNICODE
	
#else
	::SysFreeString(bstrText);
#endif
	if (((CExBaseListGrid*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListGrid::EndEditCell_String_NameAndID (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_STRING);

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
		
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	pVCellData->pObj->m_strName = pCell->szText;
	pVCellData->pObj->m_strID = pCell->szText;
	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);

	if (((CExBaseListGrid*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListGrid::EndEditCell_String_Name (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_STRING);

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

	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	pVCellData->pObj->m_strName = pCell->szText;
	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);

	if (((CExBaseListGrid*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListGrid::EndEditCell_String_ID (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_STRING);

	if (*pVCellData->pString == pCell->szText)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)pVCellData->pObj->GetParent();

	if (pParent == NULL)
	{
		return;
	}

	if (pParent->FindByID(pCell->szText) != NULL)
	{
		pCell->szText = pVCellData->pObj->m_strID;
		pGrid->InvalidateGrid(FALSE);
		return;
	}

	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	pVCellData->pObj->m_strID = pCell->szText;
	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);

	if (((CExBaseListGrid*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListGrid::EndEditCell_Datas(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData!=NULL && pCell!=NULL && pGrid!=NULL);
	CExBaseListGrid *pChildrenGrid = (CExBaseListGrid *)pGrid;
	CExBaseObject *pObj = (CExBaseObject *)pVCellData->pObj;
	ASSERT(pObj != NULL);

	if (pCell->szText.IsEmpty())
	{
		if (pVCellData->nVt == VCD_STRING)
		{
			if (pVCellData->pString != NULL)
			{
				pVCellData->pString->Empty();
				pChildrenGrid->SetModified(TRUE);
			}
		}

		return;
	}

	CExBaseList *pDatas = pVCellData->pExBaseList;

	if (pDatas != NULL)
	{
		CExBaseObject *pType = pDatas->FindByName(pCell->szText);
		if (pType != NULL && *(pVCellData->pString) != pType->m_strID)
		{
			*(pVCellData->pString) = pType->m_strID;
			pChildrenGrid->SetModified(TRUE);
		}
		else
		{
			pChildrenGrid->UpdateData(pVCellData->pObj);
		}
	}
}

CExBaseObject* CExBaseListGrid::GetFocusObject(int nRow,int Col)
{
	CGridCell* pCell = GetCell(nRow,Col);

	if(pCell == NULL)
	{
		return NULL;
	}

	PEXBASECELLDATA pExBaseCellData = (PEXBASECELLDATA)pCell->lParam;

	if (pExBaseCellData == NULL)
	{
		return NULL;
	}

	return pExBaseCellData->pObj;
}

CExBaseObject* CExBaseListGrid::GetPreObject(int nRow,int nCol)
{
	if(nRow < this->GetFixedRowCount() + 1)
	{
		return NULL;
	}


	CGridCell* pCell = this->GetCell(nRow-1,0);
	PEXBASECELLDATA pExBaseCellData = (PEXBASECELLDATA)pCell->lParam;

	if (pExBaseCellData == NULL)
	{
		return NULL;
	}

	return pExBaseCellData->pObj;
}

void  CExBaseListGrid::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strText, PEXBASECELLDATA pVCellData)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol);
	Item.nDataType = GVET_COMBOBOX;
	Item.lParam = (LPARAM)pVCellData;
	Item.szText =strText;

	if (pVCellData->pFunc == NULL)
	{
		pVCellData->pFunc = EndEditCell_DataType_Val;
	}

	SetItem(&Item);
}


void  CExBaseListGrid::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataTypeValue *pValue = NULL;
	
	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByID( *pstrValue );

		if (pValue == NULL)
		{
			pValue = (CDataTypeValue*)pDataType->GetHead();

			if (pValue != NULL)
			{
				*pstrValue = pValue->m_strID;
			}
		}
	}

	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pstrValue, pData, NULL, pFunc);
	pVCellData->pExBaseList = pDataType;
	
	if (pValue == NULL)
	{
		Show_DataType_Val(pData, nRow, nCol, *pstrValue, pVCellData);
	}
	else
	{
		Show_DataType_Val(pData, nRow, nCol, pValue->m_strName, pVCellData);
	}
}

void  CExBaseListGrid::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataType *pDataType = FindDataType(strDataType);
	Show_DataType_Val(pData, nRow, nCol, pDataType, pstrValue, pFunc);
}

void  CExBaseListGrid::Show_DataType_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue)
{
	CDataType *pDataType = FindDataType(strDataType);
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByIndex( *pstrValue );
	}

	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pstrValue, pData, NULL, NULL);
	pVCellData->pExBaseList = pDataType;

	if (pValue == NULL)
	{
		Show_StaticString(pData, nRow, nCol, *pstrValue);
	}
	else
	{
		Show_StaticString(pData, nRow, nCol, pValue->m_strName);
	}
}

void  CExBaseListGrid::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataTypeValue *pValue = NULL;
	
	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByIndex( *pnValue );
	}

	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pnValue, pData, NULL, pFunc);
	pVCellData->pExBaseList = pDataType;

	if (pValue == NULL)
	{
		CString strText;
		strText.Format(_T("%d"), *pnValue);
		Show_DataType_Val(pData, nRow, nCol, strText, pVCellData);
	}
	else
	{
		Show_DataType_Val(pData, nRow, nCol, pValue->m_strName, pVCellData);
	}
}

void  CExBaseListGrid::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataType *pDataType = FindDataType(strDataType);
	Show_DataType_Val(pData, nRow, nCol, pDataType, pnValue, pFunc);
}



void CExBaseListGrid::EndEditCell_DataType_Val (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);
//	ASSERT (pVCellData->pExBaseList != NULL);

	if (pVCellData->pExBaseList == NULL)
	{
#ifdef NOT_USE_XLANGUAGE
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Row=%d  Col=%d  数据类型对象不存在"), nRow, nCol);
#else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_DataTypeUnExist/* _T("Row=%d  Col=%d  数据类型对象不存在")*/, nRow, nCol);
#endif
		return;
	}

	CDataType *pDataType = (CDataType*)pVCellData->pExBaseList;
	ASSERT (pDataType != NULL);

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByName(pCell->szText);

	if (pValue == NULL)
	{
		//pGrid->SetItemText(nRow, nCol, *(pVCellData->pString));
	}
	else
	{
		if (pVCellData->nVt == VCD_STRING)
		{
			*(pVCellData->pString) = pValue->m_strID;
		}
		else if (pVCellData->nVt == VCD_LONG)
		{
			*(pVCellData->pnValue) = pValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_DOUBLE)
		{
			*(pVCellData->pdValue) = pValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_FLOAT)
		{
			*(pVCellData->pfValue) = pValue->GetIndex();
		}
		else if (pVCellData->nVt == VCD_DWORD)
		{
			*(pVCellData->pdwValue) = pValue->GetIndex();
		}

		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}

	if (((CExBaseListGrid*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListGrid::Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol);
	Item.nDataType = bCanEdit ? GVET_EDITBOX : GVET_NOEDIT;

	PEXBASECELLDATA pVCellData = NULL;
	FreeExBaseCellData(nRow, nCol);
	
	if (pFunc == NULL)
	{
		Item.pEditFunc = EndEditCell_Value;
		pVCellData = CreateExBaseCellData(pfValue, pData, NULL, EndEditCell_Value);
	}
	else
	{
		Item.pEditFunc = pFunc;
		pVCellData = CreateExBaseCellData(pfValue, pData, NULL, pFunc);
	}

	CString strFormat;
	strFormat.Format(_T("%%.%df"), nPrecision);
	Item.mask |= GVIF_VALUE;
	Item.lParam = (LPARAM)pVCellData;
	Item.dwValue =( nPrecision << 16) + bUnitConversion;
	Item.szText.Format(strFormat, *pfValue);

	SetItem(&Item);
}

void CExBaseListGrid::Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, double *pfValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol);
	Item.nDataType = bCanEdit ? GVET_EDITBOX : GVET_NOEDIT;

	PEXBASECELLDATA pVCellData = NULL;
	FreeExBaseCellData(nRow, nCol);

	if (pFunc == NULL)
	{
		Item.pEditFunc = EndEditCell_Value;
		pVCellData = CreateExBaseCellData(pfValue, pData, NULL, EndEditCell_Value);
	}
	else
	{
		Item.pEditFunc = pFunc;
		pVCellData = CreateExBaseCellData(pfValue, pData, NULL, pFunc);
	}

	CString strFormat;
	strFormat.Format(_T("%%.%df"), nPrecision);
	Item.mask |= GVIF_VALUE;
	Item.lParam = (LPARAM)pVCellData;
	Item.dwValue =( nPrecision << 16) + bUnitConversion;
	Item.szText.Format(strFormat, *pfValue);

	SetItem(&Item);
}

void CExBaseListGrid::Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, float *pfValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol);
	Item.nDataType = bCanEdit ? GVET_EDITBOX : GVET_NOEDIT;

	PEXBASECELLDATA pVCellData = NULL;
	FreeExBaseCellData(nRow, nCol);

	if (pFunc == NULL)
	{
		Item.pEditFunc = EndEditCell_Value;
		pVCellData = CreateExBaseCellData(pfValue, pData, NULL, EndEditCell_Value);
	}
	else
	{
		Item.pEditFunc = pFunc;
		pVCellData = CreateExBaseCellData(pfValue, pData, NULL, pFunc);
	}

	Item.mask |= GVIF_VALUE;
	Item.lParam = (LPARAM)pVCellData;
	Item.dwValue = bUnitConversion;
	math_GetStringFromValue(Item.szText, *pfValue, strUnit, bUnitConversion);

	SetItem(&Item);
}

void CExBaseListGrid::Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, double *pfValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc, BOOL bUnitConversion)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol);
	Item.nDataType = bCanEdit ? GVET_EDITBOX : GVET_NOEDIT;

	PEXBASECELLDATA pVCellData = NULL;
	FreeExBaseCellData(nRow, nCol);

	if (pFunc == NULL)
	{
		Item.pEditFunc = EndEditCell_Value;
		pVCellData = CreateExBaseCellData(pfValue, pData, NULL, EndEditCell_Value);
	}
	else
	{
		Item.pEditFunc = pFunc;
		pVCellData = CreateExBaseCellData(pfValue, pData, NULL, pFunc);
	}

	Item.mask |= GVIF_VALUE;
	Item.lParam = (LPARAM)pVCellData;
	Item.dwValue = bUnitConversion;
	math_GetStringFromValue(Item.szText, *pfValue, strUnit, bUnitConversion);

	SetItem(&Item);
}

void CExBaseListGrid::Show_Long(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol);
	Item.nDataType = bCanEdit ? GVET_EDITBOX : GVET_NOEDIT;
	Item.mask |= GVIF_FUNC;

	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pnValue, pData, NULL, EndEditCell_Value);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(_T("%d"), *pnValue);

	if (pFunc != NULL)
	{
		pVCellData->pFunc = pFunc;
		Item.pEditFunc = pFunc;
	}
	else
	{
		Item.pEditFunc = EndEditCell_Value;
	}


	SetItem(&Item);
}

void CExBaseListGrid::Show_DWORD(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol);
	Item.nDataType = bCanEdit ? GVET_EDITBOX : GVET_NOEDIT;

	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pnValue, pData, NULL, EndEditCell_Value);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(_T("%d"), *pnValue);

	if (pFunc != NULL)
	{
		pVCellData->pFunc = pFunc;
		Item.pEditFunc = pFunc;
	}
	else
	{
		Item.pEditFunc = EndEditCell_Value;
	}

	SetItem(&Item);
}

void CExBaseListGrid::Show_DWORD_Check(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pnValue, long nBits, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol);
	Item.nDataType = GVET_COMBO_CHECKBOX;//bCanEdit ? GVET_EDITBOX : GVET_NOEDIT;
	Item.bReadOnly = !bCanEdit;
	Item.nFormat = nBits;
	Item.mask |= GVIF_VALUE | GVIF_FUNC;

	PEXBASECELLDATA pVCellData = NULL;
	FreeExBaseCellData(nRow, nCol);
	
	if (pFunc != NULL)
	{
		Item.pEditFunc = pFunc;
		pVCellData = CreateExBaseCellData(pnValue, pData, NULL, pFunc);
	}
	else
	{
		Item.pEditFunc = EndEditCell_Value;
		pVCellData = CreateExBaseCellData(pnValue, pData, NULL, EndEditCell_Value);
	}

	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(_T("%d"), *pnValue);
	Item.dwValue = *pnValue;
	
	SetItem(&Item);
}

void CExBaseListGrid::FreeExBaseCell(long nRow, long nCol)
{
	if (!IsValid(nRow, nCol))
	{
		return;
	}

	CGridCell *pCell = GetCell(nRow, nCol);

	if (pCell->lParam == 0)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	pCell->lParam = 0;
	m_listVCellData.Delete(pVCellData);
}

void CExBaseListGrid::SetModifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	if (pData != NULL)
	{
		pData->SetModifiedFlag(bModified);
	}
	else
	{
		SetModified(bModified);
	}
}


void CExBaseListGrid::EndEditCell_Value(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	if (pVCellData->nVt == VCD_DOUBLE)
	{
		double fValue = math_GetValueFromString(pCell->szText);

		if (fabs(fValue-*(pVCellData->pfValue) ) > 0.00001)
		{
			*(pVCellData->pdValue) = math_GetValueFromString(pCell->szText);
			math_GetStringFromValue(pCell->szText, *(pVCellData->pdValue), _T(""), pCell->dwValue);
			pGrid->RedrawCell(nRow, nCol);
			((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
			((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
		}
	}
	else if (pVCellData->nVt == VCD_FLOAT)
	{
		float fValue = math_GetValueFromString(pCell->szText);

		if (fabs(fValue-*(pVCellData->pfValue) ) > 0.00001)
		{
			*(pVCellData->pfValue) = math_GetValueFromString(pCell->szText);
			long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;
			
			if (nPrecision > 0 )
			{
				CString strFormat;
				strFormat.Format(_T("%%.%df"), nPrecision);
				pCell->szText.Format(strFormat, *(pVCellData->pfValue));
			}
			else
			{
				math_GetStringFromValue(pCell->szText, *(pVCellData->pfValue), _T(""), pCell->dwValue);
			}

			pGrid->RedrawCell(nRow, nCol);
			((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
			((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
		}
	}
	else if (pVCellData->nVt == VCD_LONG)
	{
		long nValue =  CString_To_long(pCell->szText);

		if (nValue != *(pVCellData->pnValue))
		{
			*(pVCellData->pnValue) = nValue;
			pCell->szText.Format(_T("%d"), *(pVCellData->pnValue));
			pGrid->RedrawCell(nRow, nCol);
			((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
			((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
		}
	}
	else if (pVCellData->nVt == VCD_DWORD)
	{
		if (*(pVCellData->pnValue) != pCell->dwValue)
		{
			*(pVCellData->pnValue) = pCell->dwValue;
			((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
			((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
		}
	}

	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void CExBaseListGrid::Show_DataType_Val_Long(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol);
	Item.nDataType = GVET_COMBOBOX;

	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByIndex( *pnValue );
	}

	PEXBASECELLDATA pVCellData = NULL;
	FreeExBaseCellData(nRow, nCol);
	
	if (pFunc == NULL)
	{
		Item.pEditFunc = EndEditCell_DataType_Val;
		pVCellData = CreateExBaseCellData(pnValue, pData, NULL, EndEditCell_DataType_Val);
	}
	else
	{
		Item.pEditFunc = pFunc;
		pVCellData = CreateExBaseCellData(pnValue, pData, NULL, pFunc);
	}

	pVCellData->pExBaseList = pDataType;
	Item.lParam = (LPARAM)pVCellData;

	if (pValue == NULL)
	{
		Item.szText.Format(_T("%d"),  *pnValue);
	}
	else
	{
		Item.szText = pValue->m_strName;
	}

	SetItem(&Item);
}



void CExBaseListGrid::Show_Mac(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrMac, BOOL bSetColor)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol, bSetColor);

	Item.nDataType = GVET_MACEDIT;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pstrMac, pData, NULL, EndEditCell_Mac);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText = *pstrMac;

	Item.pEditFunc = EndEditCell_Mac;

	SetItem(&Item);
}


void CExBaseListGrid::EndEditCell_Mac (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	EndEditCell_String(nRow, nCol, pCell, pGrid);
}


void CExBaseListGrid::Show_Hex(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pdwValue, int iMaxLen,BOOL bCanEdit, BOOL bSetColor)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol, bSetColor);

	Item.nDataType = bCanEdit ? GVET_HEXEDIT : GVET_NOEDIT;
	Item.iMaxLen = iMaxLen;
	Item.mask |= GVIF_MAXLEN;

	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pdwValue, pData, NULL, EndEditCell_Hex);
	Item.lParam = (LPARAM)pVCellData;
	CString strFormat;
	strFormat.Format(_T("0X%%0%dX"), iMaxLen*2);
	Item.szText.Format(strFormat, *pdwValue);

	Item.pEditFunc = EndEditCell_Hex;

	SetItem(&Item);
}

void CExBaseListGrid::EndEditCell_Hex (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pdwValue != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_DWORD);

	DWORD dwValue = 0;
	HexToDWORD(pCell->szText, dwValue);

	if (*(pVCellData->pdwValue) != dwValue)
	{
		*(pVCellData->pdwValue) = dwValue;
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}
}

void  CExBaseListGrid::Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnCheck, GRID_CELL_EDIT_FUNC pFunc, BOOL bSetColor)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol, bSetColor);

	Item.mask |= GVIF_VALUE;
	Item.nDataType = GVET_CHECKBOX;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pnCheck, pData, NULL, pFunc);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(_T("%d"), *pnCheck);
	Item.dwValue = *pnCheck;

	if (pFunc == NULL)
	{
		Item.pEditFunc = EndEditCell_Check;
		pVCellData->pFunc = EndEditCell_Check;
	}
	else
	{
		Item.pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}

	SetItem(&Item);
}

void  CExBaseListGrid::EndEditCell_Check (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pnValue != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_LONG);

	if( *(pVCellData->pnValue) != pCell->dwValue )
	{
		*(pVCellData->pnValue) = pCell->dwValue;
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}
}

void  CExBaseListGrid::Show_ComboBox(CExBaseList *pData, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc, BOOL bSetColor)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol, bSetColor);

	Item.mask |= GVIF_VALUE;
	Item.nDataType = GVET_COMBOBOX;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pstrValue, pData, NULL, pFunc);
	Item.lParam = (LPARAM)pVCellData;
	pVCellData->pExBaseList = pData;

	CExBaseObject *pFind = pData->FindByID(*pstrValue);

	if (pFind == NULL)
	{
		Item.szText = *pstrValue;
	}
	else
	{
		Item.szText = pFind->m_strName;
	}

	if (pFunc == NULL)
	{
		pVCellData->pFunc = EndEditCell_ComboBox;
	}
	else
	{
		pVCellData->pFunc = pFunc;
	}

	SetItem(&Item);
}


void  CExBaseListGrid::Show_ComboBox(CExBaseObject *pData, CExBaseList *pListSrc, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc, BOOL bSetColor)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol, bSetColor);

	Item.mask |= GVIF_VALUE;
	Item.nDataType = GVET_COMBOBOX;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pstrValue, pData, NULL, pFunc);
	Item.lParam = (LPARAM)pVCellData;
	pVCellData->pExBaseList = pListSrc;

	CExBaseObject *pFind = pListSrc->FindByIDEx(*pstrValue);

	if (pFind == NULL)
	{
		Item.szText = *pstrValue;
	}
	else
	{
		Item.szText = pFind->m_strName;
	}

	if (pFunc == NULL)
	{
		pVCellData->pFunc = EndEditCell_ComboBox;
	}
	else
	{
		pVCellData->pFunc = pFunc;
	}

	SetItem(&Item);
}

void  CExBaseListGrid::Show_ComboBox(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc, BOOL bSetColor)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol, bSetColor);

	Item.mask |= GVIF_VALUE;
	Item.nDataType = GVET_COMBOBOX;
	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pstrValue, pData, NULL, pFunc);
	Item.lParam = (LPARAM)pVCellData;
	pVCellData->pExBaseList = NULL;

	Item.szText = *pstrValue;

	if (pFunc == NULL)
	{
		pVCellData->pFunc = EndEditCell_ComboBox;
	}
	else
	{
		pVCellData->pFunc = pFunc;
	}

	SetItem(&Item);
}


void CExBaseListGrid::EndEditCell_ComboBox (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	if (pVCellData->pExBaseList == NULL)
	{
#ifdef NOT_USE_XLANGUAGE
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Row=%d  Col=%d  数据类型对象不存在"), nRow, nCol);
#else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DataTypeUnExist/*_T("Row=%d  Col=%d  数据类型对象不存在")*/, nRow, nCol);
#endif
		return;
	}

	CExBaseList *pList = (CDataType*)pVCellData->pExBaseList;

	CExBaseObject *pFind = pList->FindByName(pCell->szText);

	if (pFind == NULL)
	{
		if (pVCellData->nVt == VCD_STRING)
		{
			if (pVCellData->pString != NULL)
			{
				pVCellData->pString->Empty();
				pGrid->SetModified(TRUE);
			}
		}
	}
	else
	{
		if (pVCellData->nVt == VCD_STRING)
		{
			*(pVCellData->pString) = pFind->m_strID;
		}
		
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}

	if (((CExBaseListGrid*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}
