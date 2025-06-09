#include "StdAfx.h"
#include "ExBaseListXGridCtrlBase.h"
#include "..\..\Module\XLanguage\XLanguageResource.h"
#include "..\..\Module\API\MathApi.h"

//////////////////////////////////////////////////////////////////////////
//CExBaseListXGridCtrlBase
const CString CExBaseListXGridCtrlBase::m_strEmptyString = _T("");

CExBaseListXGridCtrlBase::CExBaseListXGridCtrlBase()
{
	m_crBkColor = RGB(255, 255, 255);
	m_crTextColor = RGB(0, 0, 0);
	m_crTitleTextBkColor = RGB(192, 192, 192);
	m_crDataTextBkColor = RGB(255, 255, 255);

	m_pCurrData = NULL;
	m_pDatas = NULL;

	SetListMode(TRUE);
// 	m_Logfont.lfHeight = 12;
	m_pDataViewOptrInterface = NULL;
	SetBkColor(RGB(255, 255, 255));
	m_nAdjustBeginCol = -1;
}


CExBaseListXGridCtrlBase::~CExBaseListXGridCtrlBase(void)
{
	m_listVCellData.DeleteAll();
}

void  CExBaseListXGridCtrlBase::OnEditCell(int nRow, int nCol, UINT nChar)
{
	CXGridCtrlBase::OnEditCell(nRow, nCol, nChar);

	OnDataSelChanged(nRow, nCol);;
}

void CExBaseListXGridCtrlBase::OnDataSelChanged(int nRow, int nCol)
{
	if (m_pDataViewOptrInterface != NULL)
	{
		m_pDataViewOptrInterface->OnDataSelChanged(this, nRow, nCol);
	}
}

void CExBaseListXGridCtrlBase::FreeExBaseCellData(long nRow, long nCol)
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

void CExBaseListXGridCtrlBase::MoveUp()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(1);

	long nRow = m_pDatas->FindIndex(pSel);

	if (nRow == 0)
	{
		return;
	}

	CExBaseObject *p1 = GetData(nRow+1);
	CExBaseObject *p2 = GetData(nRow);
	ClearSelect();
	ChangeRowPosition(nRow+1, nRow);
	m_pDatas->ChangePosition(p1, p2);
	UpdateDataIndex();
	SelectRow(nRow);
	SetMidifiedFlag(m_pDatas);
}

void CExBaseListXGridCtrlBase::MoveDown()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(1);

	long nRow = m_pDatas->FindIndex(pSel);

	if (nRow == GetRowCount() - 2)
	{
		return;
	}

	CExBaseObject *p1 = GetData(nRow+1);
	CExBaseObject *p2 = GetData(nRow+2);
	ClearSelect();
	ChangeRowPosition(nRow+1, nRow+2);
	m_pDatas->ChangePosition(p1, p2);
	UpdateDataIndex();
	SelectRow(nRow+2);
	SetMidifiedFlag(m_pDatas);

}

void CExBaseListXGridCtrlBase::FreeExBaseCellData(long nRow)
{
	long nCols = GetColumnCount();
	long nCol = 0;

	for (nCol=0; nCol<nCols; nCol++)
	{
		FreeExBaseCellData(nRow, nCol);
	}
}

void CExBaseListXGridCtrlBase::InitGridTitle(const CString *pStrTitles, const int *pnWidth, int nCols)
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
		Item.lParam=iCol;
		SetItem(&Item);
	}	

	SetRowHeight(0,EXBASEGRID_ROWHEIGHT);
}


BOOL CExBaseListXGridCtrlBase::UpdateData(CExBaseObject *pData)
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
		InvalidateGrid(FALSE);
	}
	else
	{
	}

	return TRUE;
}

BOOL CExBaseListXGridCtrlBase::UpdateDataIndex(long nRowBegin, long nIndexCol)
{
	long nRow = nRowBegin;
	CString strText;

	for (nRow = nRowBegin; nRow<m_nRows; nRow++)
	{
		strText.Format(_T("%d"), nRow);
		SetItemText(nRow, nIndexCol, strText);
	}

	InvalidateGrid(FALSE);

	return TRUE;
}

CExBaseObject* CExBaseListXGridCtrlBase::GetCurrCellData()
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

CExBaseObject* CExBaseListXGridCtrlBase::GetData(int nRow)
{
	PEXBASECELLDATA pCellData = (PEXBASECELLDATA)GetItemData(nRow, 0);
	//ASSERT (pCellData != NULL);

	if (pCellData != NULL)
	{
		return pCellData->pObj;
	}

	return NULL;
}

CExBaseObject* CExBaseListXGridCtrlBase::GetCurrSelData(long nStateForCol)
{
	long nRow = 1;
	long nCount = 0;
	UINT nState = 0;
	CExBaseObject *pSelData = NULL;

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

long CExBaseListXGridCtrlBase::GetCurrSelDatas(CExBaseList &listDatas, long nStateForCol)
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

long CExBaseListXGridCtrlBase::GetDataRow(CExBaseObject *pData)
{
	if (pData == NULL)
	{
		return -1;
	}

	long nIndex = -1;
	long nRows = GetRowCount();
	long nRow = 1;

	for (; nRow<nRows; nRow++)
	{
		PEXBASECELLDATA pCellData = (PEXBASECELLDATA)GetItemData(nRow, 0);
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

CExBaseObject* CExBaseListXGridCtrlBase::GetDataRow(long nRow, long nCol)
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


void CExBaseListXGridCtrlBase::GetAllSelectDatas(CExBaseList *pList, long nStateForCol)
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

void CExBaseListXGridCtrlBase::ClearSelect()
{
	CXGridCtrlBase::ClearSelect();
}

void CExBaseListXGridCtrlBase::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)//填充comboList cell
{
	CGridCell *pCell = GetCell(nRow, nCol);
	ASSERT(pCell != NULL);
	PEXBASECELLDATA pVellData = (PEXBASECELLDATA )pCell->lParam;
	ASSERT(pVellData != NULL);
	CExBaseList *pExBaseList = pVellData->pExBaseList;

	if (pExBaseList != NULL)
	{
		CComboBox *pComboBox = (CComboBox *)cltWnd;
		ASSERT(pComboBox != NULL);

		pComboBox->ResetContent();
		pExBaseList->InsertChildreComboBox(pComboBox);
	}
}

BOOL CExBaseListXGridCtrlBase::EndEditCell(int nRow, int nCol, DWORD dwItemData)//保存编辑
{
	CGridCell *pCell = GetCell(nRow, nCol);

	if (pCell == NULL)
	{
		return FALSE;
	}

	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;

	if (pVellData == NULL)
	{
		return FALSE;
	}

	if (pVellData->pFunc != NULL)
	{
		pVellData->pFunc(nRow, nCol, pCell, this);
		return TRUE;
	}

	switch (pVellData->nVt)
	{
	case VCD_LONG:
		if (*(pVellData->pnValue) != pCell->dwValue)
		{
			*(pVellData->pnValue) = pCell->dwValue;
		}
		break;

	case VCD_DWORD:
		if (*(pVellData->pdwValue) != pCell->dwValue)
		{
			*(pVellData->pdwValue) = pCell->dwValue;
		}
		break;

	case VCD_DOUBLE:
		//*(pVellData->pdValue) = _wtof(pCell->szText);
		break;

	case VCD_STRING:
		if (*(pVellData->pString) != pCell->szText)
		{
			*(pVellData->pString) = pCell->szText;
		}

		break;
	}

	return TRUE;
}

 void CExBaseListXGridCtrlBase::InsertData(CExBaseObject *pData, BOOL bInvalidate)
 {
	 int nRow = m_nRows;
	 SetRowCount(m_nRows + 1);
	 ShowData(pData, nRow, FALSE);

	 SetRowHeight(m_nRows-1, EXBASEGRID_ROWHEIGHT);
	 AdjustAllCols();

	 if (bInvalidate)
	 {
		 InvalidateGrid(FALSE);
	 }
 }

void CExBaseListXGridCtrlBase::ShowDatas(CExBaseList *pDatas)
{
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
	long nCalRows = pDatas->GetCount() + 1;
	SetRowCount(nCalRows);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex);

	for (nRowIndex=1; nRowIndex<m_nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, EXBASEGRID_ROWHEIGHT);
	}

	AdjustAllCols();
	ResetScrollBars();
	InvalidateGrid(FALSE);
}

void CExBaseListXGridCtrlBase::UpdateDatas()
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
	InvalidateGrid(FALSE);
}

void CExBaseListXGridCtrlBase::AdjustAllCols()
{
	if (m_nAdjustBeginCol < 0)
	{
		return;
	}

	long nCols = GetColumnCount();
	long nCol = m_nAdjustBeginCol;

	for (nCol=m_nAdjustBeginCol; nCol<nCols; nCol++)
	{
		AutoSizeColumn(nCol);
	}
}

CExBaseObject* CExBaseListXGridCtrlBase::GetVCellData(CGridCell *pCell)
{
	if (pCell->lParam == 0)
	{
		return NULL;
	}

	return ((PEXBASECELLDATA)pCell->lParam)->pObj;
}

CExBaseObject* CExBaseListXGridCtrlBase::GetVCellData(const CCellID &oCellID)
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

void CExBaseListXGridCtrlBase::Show_Index(CExBaseObject *pData, const int& nRow, const int& nCol, long nAddVal)
{
	GV_ITEM Item;

	Item.row = nRow;
	Item.col = nCol;
	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_FORMAT;
	Item.nDataType = GVET_NOEDIT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(&(pData->m_strID), pData, NULL, NULL);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(_T("%d"), Item.row + nAddVal);

	Item.pEditFunc = NULL;

	SetItem(&Item);
}

void CExBaseListXGridCtrlBase::Show_IndexSingle(CExBaseObject *pData, const int& nRow, const int& nCol)
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

void CExBaseListXGridCtrlBase::Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString)
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

void CExBaseListXGridCtrlBase::Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strString)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData);

	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE  | GVIF_STRBLOCKS;
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

void CExBaseListXGridCtrlBase::Show_StringCmp(CExBaseObject *pData, const int& nRow, const int& nCol, CStringCmpBlocks *pStrCmpBlks)
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

void CExBaseListXGridCtrlBase::Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData);

	Item.row = nRow;
	Item.col = nCol;
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
	}
	else
	{
		Item.pEditFunc = EndEditCell_String;
	}
// 	if (pVCellData->pFunc == NULL)
// 	{
// 		pVCellData->pFunc = EndEditCell_String;
// 	}

	SetItem(&Item);
}

void CExBaseListXGridCtrlBase::InitDataCellItem(GV_ITEM& Item, CExBaseObject *pObj)
{
	InitGirdItem(Item);
	Item.crFgClr = m_crTextColor;
	Item.crBkClr = m_crDataTextBkColor;

}

void CExBaseListXGridCtrlBase::InitDataCellItem(GV_ITEM& Item, CExBaseObject *pObj, const int& nRow, const int& nCol, BOOL bSetColor)
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

void CExBaseListXGridCtrlBase::EndEditCell_String (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);

	if (*pVCellData->pString != pCell->szText)
	{
		((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVCellData->pObj);
		*pVCellData->pString = pCell->szText;
	}

	if (((CExBaseListXGridCtrlBase*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListXGridCtrlBase::EndEditCell_String_NameAndID (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);

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
		
	((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVCellData->pObj);
	pVCellData->pObj->m_strName = pCell->szText;
	pVCellData->pObj->m_strID = pCell->szText;

	if (((CExBaseListXGridCtrlBase*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListXGridCtrlBase::EndEditCell_String_Name (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);

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

	((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVCellData->pObj);
	pVCellData->pObj->m_strName = pCell->szText;

	if (((CExBaseListXGridCtrlBase*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListXGridCtrlBase::EndEditCell_String_ID (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);

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

	((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVCellData->pObj);
	pVCellData->pObj->m_strID = pCell->szText;

	if (((CExBaseListXGridCtrlBase*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListXGridCtrlBase::EndEditCell_Datas(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData!=NULL && pCell!=NULL && pGrid!=NULL);
	CExBaseListXGridCtrlBase *pChildrenGrid = (CExBaseListXGridCtrlBase *)pGrid;
	CExBaseObject *pObj = (CExBaseObject *)pVCellData->pObj;
	ASSERT(pObj != NULL);

	if (pCell->szText.IsEmpty())
	{
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

CExBaseObject* CExBaseListXGridCtrlBase::GetFocusObject(int nRow,int Col)
{
	CGridCell* pCell = GetCell(nRow,0);

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

CExBaseObject* CExBaseListXGridCtrlBase::GetPreObject(int nRow,int nCol)
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

void  CExBaseListXGridCtrlBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strText, PEXBASECELLDATA pVCellData)
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


void  CExBaseListXGridCtrlBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
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

void  CExBaseListXGridCtrlBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataType *pDataType = FindDataType(strDataType);
	Show_DataType_Val(pData, nRow, nCol, pDataType, pstrValue, pFunc);
}

void  CExBaseListXGridCtrlBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc)
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

void  CExBaseListXGridCtrlBase::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataType *pDataType = FindDataType(strDataType);
	Show_DataType_Val(pData, nRow, nCol, pDataType, pnValue, pFunc);
}



void CExBaseListXGridCtrlBase::EndEditCell_DataType_Val (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pString != NULL);
//	ASSERT (pVellData->pExBaseList != NULL);

	if (pVellData->pExBaseList == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_DataTypeUnExist /*_T("Row=%d  Col=%d  数据类型对象不存在")*/, nRow, nCol);
		return;
	}

	CDataType *pDataType = (CDataType*)pVellData->pExBaseList;
	ASSERT (pDataType != NULL);

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByName(pCell->szText);

	if (pValue == NULL)
	{
		//pGrid->SetItemText(nRow, nCol, *(pVellData->pString));
	}
	else
	{
		if (pVellData->nVt == VCD_STRING)
		{
			*(pVellData->pString) = pValue->m_strID;
		}
		else if (pVellData->nVt == VCD_LONG)
		{
			*(pVellData->pnValue) = pValue->GetIndex();
		}
		else if (pVellData->nVt == VCD_DOUBLE)
		{
			*(pVellData->pdValue) = pValue->GetIndex();
		}
		else if (pVellData->nVt == VCD_FLOAT)
		{
			*(pVellData->pfValue) = pValue->GetIndex();
		}
		else if (pVellData->nVt == VCD_DWORD)
		{
			*(pVellData->pdwValue) = pValue->GetIndex();
		}

		((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVellData->pObj);
	}

	if (((CExBaseListXGridCtrlBase*)pGrid)->m_nAdjustBeginCol >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}
}

void CExBaseListXGridCtrlBase::Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, long nPrecision, float *pfValue, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc)
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
	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(strFormat, *pfValue);

	SetItem(&Item);
}

void CExBaseListXGridCtrlBase::Show_Float(CExBaseObject *pData, const int& nRow, const int& nCol, float *pfValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
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

	Item.lParam = (LPARAM)pVCellData;
	math_GetStringFromValue(Item.szText, *pfValue, strUnit);

	SetItem(&Item);
}

void CExBaseListXGridCtrlBase::Show_Double(CExBaseObject *pData, const int& nRow, const int& nCol, double *pfValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
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

	Item.lParam = (LPARAM)pVCellData;
	math_GetStringFromValue(Item.szText, *pfValue, strUnit);

	SetItem(&Item);
}

void CExBaseListXGridCtrlBase::Show_Long(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
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
		Item.pEditFunc = pFunc;
	}
	else
	{
		Item.pEditFunc = EndEditCell_Value;
	}


	SetItem(&Item);
}

void CExBaseListXGridCtrlBase::Show_DWORD(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pnValue, BOOL bCanEdit, const CString &strUnit, GRID_CELL_EDIT_FUNC pFunc)
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
		Item.pEditFunc = pFunc;
	}
	else
	{
		Item.pEditFunc = EndEditCell_Value;
	}

	SetItem(&Item);
}

void CExBaseListXGridCtrlBase::Show_DWORD_Check(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pnValue, long nBits, BOOL bCanEdit, GRID_CELL_EDIT_FUNC pFunc)
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

void CExBaseListXGridCtrlBase::FreeExBaseCell(long nRow, long nCol)
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

	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	pCell->lParam = 0;
	m_listVCellData.Delete(pVellData);
}

void CExBaseListXGridCtrlBase::EndEditCell_Value(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pString != NULL);

	if (pVellData->nVt == VCD_DOUBLE)
	{
		double fValue = math_GetValueFromString(pCell->szText);

		if (fabs(fValue-*(pVellData->pfValue) ) > 0.00001)
		{
			*(pVellData->pdValue) = math_GetValueFromString(pCell->szText);
			math_GetStringFromValue(pCell->szText, *(pVellData->pdValue), _T(""));
			pGrid->RedrawCell(nRow, nCol);
			((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVellData->pObj);
		}
	}
	else if (pVellData->nVt == VCD_FLOAT)
	{
		float fValue = math_GetValueFromString(pCell->szText);

		if (fabs(fValue-*(pVellData->pfValue) ) > 0.00001)
		{
			*(pVellData->pfValue) = math_GetValueFromString(pCell->szText);
			math_GetStringFromValue(pCell->szText, *(pVellData->pfValue), _T(""));
			pGrid->RedrawCell(nRow, nCol);
			((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVellData->pObj);
		}
	}
	else if (pVellData->nVt == VCD_LONG)
	{
		long nValue =  CString_To_long(pCell->szText);

		if (nValue != *(pVellData->pnValue))
		{
			*(pVellData->pnValue) = nValue;
			pCell->szText.Format(_T("%d"), *(pVellData->pnValue));
			pGrid->RedrawCell(nRow, nCol);
			((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVellData->pObj);
		}
	}

	((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVellData->pObj);
}

void CExBaseListXGridCtrlBase::Show_DataType_Val_Long(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, long *pnValue, GRID_CELL_EDIT_FUNC pFunc)
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



void CExBaseListXGridCtrlBase::Show_Mac(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrMac, BOOL bSetColor)
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


void CExBaseListXGridCtrlBase::EndEditCell_Mac (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	EndEditCell_String(nRow, nCol, pCell, pGrid);
}


void CExBaseListXGridCtrlBase::Show_Hex(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pdwValue, int iMaxLen,BOOL bCanEdit, BOOL bSetColor)
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

void CExBaseListXGridCtrlBase::EndEditCell_Hex (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pdwValue != NULL);
	ASSERT (pVellData->nVt == VCD_DWORD);

	DWORD dwValue = 0;
	HexToDWORD(pCell->szText, dwValue);

	if (*(pVellData->pdwValue) != dwValue)
	{
		((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVellData->pObj);
		*(pVellData->pdwValue) = dwValue;
		((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVellData->pObj);
	}
}

void  CExBaseListXGridCtrlBase::Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnCheck, GRID_CELL_EDIT_FUNC pFunc, BOOL bSetColor)
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
	}
	else
	{
		Item.pEditFunc = pFunc;
	}

	SetItem(&Item);
}

void  CExBaseListXGridCtrlBase::EndEditCell_Check (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pnValue != NULL);
	ASSERT (pVellData->nVt == VCD_LONG);

	((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVellData->pObj);

	if( *(pVellData->pnValue) != pCell->dwValue )
	{
		*(pVellData->pnValue) = pCell->dwValue;
		((CExBaseListXGridCtrlBase*)pGrid)->SetMidifiedFlag(pVellData->pObj);
	}
}

