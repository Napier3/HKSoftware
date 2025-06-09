#include "StdAfx.h"
#include "GbtBatchItemGroupEditGrid.h"
#include "..\..\XLanguageResourceAts.h"
//////////////////////////////////////////////////////////////////////////
CGbtBatchItemGroupEditGrid::CGbtBatchItemGroupEditGrid(void)
{
	m_pTool = NULL;
	m_pGbtBatchItemGroups = NULL;
	m_pDevice = NULL;
}

CGbtBatchItemGroupEditGrid::~CGbtBatchItemGroupEditGrid(void)
{
	
}

void CGbtBatchItemGroupEditGrid::InitExGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(2);
	SetFixedRowCount(1);
	SetFixedColumnCount(2);
	InitGridTitle();
}

void CGbtBatchItemGroupEditGrid::InitGridTitle()
{
	CString cTempStr[2]={/*_T("测试项目")*/g_sLangTxt_TestItem, /*_T("数据")*/g_sLangTxt_Data};
	int iWidth[2]={140,200};

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	SetRowCount(1);
	SetColumnCount(2);

	for (int iCol=0;iCol<2;iCol++)
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

CGbtBatchItemRef* CGbtBatchItemGroupEditGrid::GetSelBatchItemRef()
{
	CCellID idCell = GetFocusCell();

	if (idCell.row < 0 || idCell.col < 2)
	{
		return NULL;
	}

	CExBaseObject *pObj = (CExBaseObject*)GetItemData(idCell.row, idCell.col);
	CGbtBatchItemRef *pBatchItemRef = NULL;

	if (pObj != NULL)
	{
		pBatchItemRef = (CGbtBatchItemRef *)pObj->GetAncestor(GBTWZDCLASSID_BATCHITEMREF);
	}	

	return pBatchItemRef;
}

CGbtBatchItemRefValue* CGbtBatchItemGroupEditGrid::GetSelBatchItemRefValue()
{
	CCellID idCell = GetFocusCell();

	if (idCell.row < 0 || idCell.col < 2)
	{
		return NULL;
	}

	CExBaseObject *pObj = (CExBaseObject*)GetItemData(idCell.row, idCell.col);

	return (CGbtBatchItemRefValue*)pObj;
}


void CGbtBatchItemGroupEditGrid::ResetGroupEditGrid()
{
	SetColumnCount(2);
}


CGbtBatchItemGroup* CGbtBatchItemGroupEditGrid::GetSelBatchItemGroup()
{
	CCellID idCell = GetFocusCell();

	if (idCell.row < 0 || idCell.col < 2)
	{
		return NULL;
	}

	CGbtBatchItemGroup *pSelGroup = (CGbtBatchItemGroup*)m_pGbtBatchItemGroups->GetAtIndex(idCell.col - 2);
	return pSelGroup;
}

void CGbtBatchItemGroupEditGrid::DeleteGroup(long nGroupIndex)
{
	DeleteColumn(nGroupIndex+2);
	CString strText;

	for (nGroupIndex=2; nGroupIndex<m_nCols; nGroupIndex++)
	{
		strText.Format(/*_T("第%d组")*/g_sLangTxt_NumberGroup, nGroupIndex-1);
		SetItemText(0, nGroupIndex, strText);
	}
}

void CGbtBatchItemGroupEditGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
// 	if (nRow < 0 || nCol < 2)
// 	{
// 		return CGridCtrl::OnEditCell(nRow, nCol, nChar);
// 	}

	GetParent()->PostMessage(WM_BATCHITEM_GRID_CELL_SEL_CHANGED, nRow,nCol);
	
	return CGridCtrl::OnEditCell(nRow, nCol, nChar);
}

BOOL CGbtBatchItemGroupEditGrid::OnCellRButtonUp(const CCellID &idCell)
{
	if (!idCell.IsValid())
	{
		return FALSE;
	}


	if (idCell.row <= 0 || idCell.col <= 0)
	{
		return FALSE;
	}

	if (idCell.col < 1)
	{
		return FALSE;
	}

	SetFocusCell(-1,-1);
	SetFocusCell(idCell.row,idCell.col);
	m_LeftClickDownCell = idCell;
	m_idCurrentCell = idCell;

	GetParent()->PostMessage(WM_BATCHITEM_GRID_CELL_SEL_CHANGED, idCell.row,idCell.col);

	CExBaseObject *pObj = (CExBaseObject*)GetItemData(idCell.row, 1);
	CGbtBatchItemRef *pBatchItemRef = NULL;

	if (pObj == NULL)
	{
		return TRUE;
	}	

	pBatchItemRef = (CGbtBatchItemRef *)pObj->GetAncestor(GBTWZDCLASSID_BATCHITEMREF);

	if (pBatchItemRef == NULL)
	{
		return TRUE;
	}

	long nBatchRefIndex = m_pGbtBatchItemGroups->m_pGbtBatchItemGroupRef->FindIndex(pBatchItemRef);	

	if (nBatchRefIndex < 0)
	{
		return TRUE;
	}

	CGbtBatchItemRefValue *pValue = NULL;
	pValue = (CGbtBatchItemRefValue*)GetItemData(idCell.row,1);

	if (pValue == NULL)
	{
		return TRUE;
	}

	CExBaseObject *p = pValue;

	m_pGbtBatchItemGroups->ChangeBatchItemRefValueSel(nBatchRefIndex, pValue);
	COLORREF cr = GetCGbtBatchItemRefValueColor(pValue);

	for (long nIndex=2; nIndex<m_nCols; nIndex++)
	{
		SetItemBkColour(idCell.row, nIndex, cr);
	}

	CString strCellText;
	strCellText = GetItemText(idCell.row, 1);
	strCellText = strCellText.Mid(1);

	if (pValue->m_nUse == 1)
	{
		strCellText = _T("■") + strCellText;
	}
	else
	{
		strCellText = _T("□") + strCellText;
	}

	SetItemText(idCell.row, 1, strCellText);

	Invalidate(FALSE);
	
	return TRUE;
}


void CGbtBatchItemGroupEditGrid::ShowBatchItemGroups(CGbInsertStxmlFileTool *pTool)
{
	ASSERT(pTool != NULL);

	m_pTool = pTool;
	m_pGbtBatchItemGroups = m_pTool->m_pGbtBatchItemGroups;
	m_pDevice =  pTool->m_pGbStxml->GetDevice();;
	
	ShowBatchItemGroupsFixRows();
}

void CGbtBatchItemGroupEditGrid::InsertBatchItemGroup(CGbtBatchItemGroup *pGroup, long nColIndex)
{
	if (nColIndex == -1)
	{
		nColIndex = m_pGbtBatchItemGroups->GetCount();
	}

	CString strTemp;
	
	strTemp.Format(/*_T("第%d组")*/g_sLangTxt_NumberGroup, nColIndex);
	InsertColumn(strTemp);
	nColIndex += 1;
	//SetItemText(0, nColIndex, strTemp);
	//SetColumnWidth(nColIndex, 100);

	ShowBatchItemGroup(pGroup, nColIndex, FALSE);
	AutoSizeColumn(nColIndex);
	Invalidate(FALSE);
}

void CGbtBatchItemGroupEditGrid::ShowBatchItemGroupsFixRows()
{
	long nRows = m_pGbtBatchItemGroups->m_pGbtBatchItemGroupRef->GetValuesCount();
	nRows += 3;
	SetRowCount(nRows);

	long nRowIndex = 1;

	for (nRowIndex=1; nRowIndex<nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, 20);
	}

	nRowIndex = 1;
	Show_StaticString(nRowIndex, 0, /*_T("项目分类名称")*/g_sLangTxt_ItemClassName, 0);
	Merge(nRowIndex, 0, nRowIndex, 1);

	nRowIndex++;
	Show_StaticString(nRowIndex, 0, /*_T("项目分类ID")*/g_sLangTxt_ItemClassId, 0);
	Merge(nRowIndex, 0, nRowIndex, 1);

	ShowBatchItemGroup(m_pGbtBatchItemGroups->m_pGbtBatchItemGroupRef, 1, TRUE);
	
	AutoSizeColumn(0);
	AutoSizeColumn(1);

}

void CGbtBatchItemGroupEditGrid::ShowBatchItemGroup(CGbtBatchItemGroup *pGroup, long nGroupColIndex, BOOL bIsTitle)
{
	POS pos = pGroup->GetHeadPosition();
	CGbtBatchItemRef *pItemRef = NULL;

	if (!bIsTitle)
	{
		Show_BatchItemGroupName(1, nGroupColIndex, pGroup);
		Show_BatchItemGroupID(2, nGroupColIndex, pGroup);
	}

	long nRowIndex = 3;

	while (pos != NULL)
	{
		pItemRef = (CGbtBatchItemRef *)pGroup->GetNext(pos);

		if (bIsTitle)
		{
			ShowBatchItemRefTitle(pItemRef, nRowIndex);
		}
		else
		{
			ShowBatchItemRef(pItemRef, nGroupColIndex, nRowIndex);
		}
	}
}

void CGbtBatchItemGroupEditGrid::ShowBatchItemRefTitle(CGbtBatchItemRef *pItemRef, long &nRowIndex)
{
 	long nBeginIndex = nRowIndex;
	POS pos = pItemRef->GetHeadPosition();
	CGbtBatchItemRefValue *pValue = NULL;

	Show_StaticString(nRowIndex, 0, pItemRef->m_strName, 0);
	CString strName;
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pValue = (CGbtBatchItemRefValue*)pItemRef->GetNext(pos);
		pData = m_pDevice->FindDataObjByID(pValue->m_strID,-1);

		if (pData == NULL)
		{
			strName = pValue->m_strID;
		}
		else
		{
			strName = pData->m_strName;
		}

		if (pValue->m_nUse == 1)
		{
			strName = _T("■") + strName;
		}
		else
		{
			strName = _T("□") + strName;
		}

		Show_StaticString(nRowIndex, 1, strName);
		SetItemData(nRowIndex, 1, (LPARAM)pValue);
		nRowIndex++;
	}

	if (nRowIndex > nBeginIndex)
	{
		Merge(nBeginIndex, 0, nRowIndex-1, 0);
	}
}

void CGbtBatchItemGroupEditGrid::ShowBatchItemRef(CGbtBatchItemRef *pItemRef, long nGroupColIndex, long &nRowIndex)
{
	long nBeginIndex = nRowIndex;
	POS pos = pItemRef->GetHeadPosition();
	CGbtBatchItemRefValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CGbtBatchItemRefValue*)pItemRef->GetNext(pos);
		Show_BatchItemValue(nRowIndex, nGroupColIndex, pValue);

		nRowIndex++;
	}
}
void CGbtBatchItemGroupEditGrid::DeleteBatchItemGroup(long nGroupColIndex)
{
	DeleteColumn(nGroupColIndex);
	ResetScrollBars();
	Invalidate(FALSE);
}
// 
// void  CGbtBatchItemGroupEditGrid::OnEditCell(int nRow, int nCol, UINT nChar)
// {
// 	if (nRow == -1)
// 	{
// 		return;
// 	}
// 
// 	if (nCol != BATCHITEMEDIT_GRID_ID_DATAREF)
// 	{
// 		return CGridCtrl::OnEditCell(nRow, nCol, nChar);
// 	}
// 
// 	if (m_pXMatchRefObjectSelDlg == NULL)
// 	{
// 		m_pXMatchRefObjectSelDlg = new CXMatchRefObjectSelDlg(this);
// 		m_pXMatchRefObjectSelDlg->SetWindowTitle(_T("选择匹配的数据对象"));
// 		m_pXMatchRefObjectSelDlg->SetUseModeless();
// 		m_pXMatchRefObjectSelDlg->DoModal();
// 	}
// 	else
// 	{
// 		if (!m_pXMatchRefObjectSelDlg->IsWindowVisible())
// 		{
// 			m_pXMatchRefObjectSelDlg->ShowWindow(SW_SHOW);
// 		}
// 
// 		m_pXMatchRefObjectSelDlg->BringWindowToTop();
// 	}
// 
// 	if (m_pTool->IsDatasChanged())
// 	{
// 		m_pXMatchRefObjectSelDlg->ShowExBaseList(m_pTool->GetRefDatas(), TRUE);
// 		m_pTool->SetDataChanged(FALSE);
// 	}
// }

void CGbtBatchItemGroupEditGrid::Show_StaticString(const int& nRow, const int& nCol, const CString &strText, LPARAM lParam)
{
	GV_ITEM Item;

	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT;
	Item.row = nRow;
	Item.col = nCol;
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = GVET_NOEDIT;
	Item.lParam = lParam;
	Item.szText = strText;

	SetItem(&Item);
}

void CGbtBatchItemGroupEditGrid::Show_BatchItemGroupName(int nRow, int nCol,CGbtBatchItemGroup *pGroup)
{
	GV_ITEM Item;

	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT | GVIF_FUNC;
	Item.row = nRow;
	Item.col = nCol;
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = GVET_EDITBOX;
	Item.lParam = (LPARAM)pGroup;
	Item.szText = pGroup->m_strName;
	Item.pEditFunc = EndEdit_BatchItemGroupName;

	SetItem(&Item);
}

void CGbtBatchItemGroupEditGrid::Show_BatchItemGroupID(int nRow, int nCol,CGbtBatchItemGroup *pGroup)
{
	GV_ITEM Item;

	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT | GVIF_FUNC;
	Item.row = nRow;
	Item.col = nCol;
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = GVET_EDITBOX;
	Item.lParam = (LPARAM)pGroup;
	Item.szText = pGroup->m_strID;
	Item.pEditFunc = EndEdit_BatchItemGroupID;

	SetItem(&Item);
}

COLORREF CGbtBatchItemGroupEditGrid::GetCGbtBatchItemRefValueColor(CGbtBatchItemRefValue *pValue)
{
	if (pValue->m_nUse == 1)
	{
		return RGB(100,230,230);
	}
	else
	{
		return RGB(255,255,255);
	}
}

void CGbtBatchItemGroupEditGrid::Show_BatchItemValue(int nRow, int nCol,CGbtBatchItemRefValue *pValue)
{
	GV_ITEM Item;

	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT | GVIF_FUNC | GVIF_BKCLR;
	Item.row = nRow;
	Item.col = nCol;
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = GVET_EDITBOX;
	Item.lParam = (LPARAM)pValue;
	Item.szText = pValue->m_strValue;
	Item.pEditFunc = EndEdit_BatchItemValue;
	Item.crBkClr = GetCGbtBatchItemRefValueColor(pValue);

	SetItem(&Item);
}

void CGbtBatchItemGroupEditGrid::EndEdit_BatchItemGroupName(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtBatchItemGroupEditGrid *pEditGrid = (CGbtBatchItemGroupEditGrid*)pGrid;
	CGbtBatchItemGroup *pGroup = (CGbtBatchItemGroup*)pCell->lParam;
	pCell->szText.Trim();

	if (pCell->szText.GetLength() == 0)
	{
		pGrid->SetItemText(nRow, nCol, pGroup->m_strName);
	}
	else
	{
		CGbtBatchItemGroup *pFind = (CGbtBatchItemGroup*)pEditGrid->m_pGbtBatchItemGroups->FindByID(pCell->szText);

		if (pFind != NULL)
		{
			if (pFind != pGroup)
			{
				pGrid->SetItemText(nRow, nCol, pGroup->m_strName);
			}
		}
		else
		{
			pGroup->m_strName = pCell->szText;
		}
	}
}

void CGbtBatchItemGroupEditGrid::EndEdit_BatchItemGroupID(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtBatchItemGroupEditGrid *pEditGrid = (CGbtBatchItemGroupEditGrid*)pGrid;
	CGbtBatchItemGroup *pGroup = (CGbtBatchItemGroup*)pCell->lParam;
	pCell->szText.Trim();

	if (pCell->szText.GetLength() == 0)
	{
		pGrid->SetItemText(nRow, nCol, pGroup->m_strID);
	}
	else
	{
		CGbtBatchItemGroup *pFind = (CGbtBatchItemGroup*)pEditGrid->m_pGbtBatchItemGroups->FindByID(pCell->szText);
		
		if (pFind != NULL)
		{
			if (pFind != pGroup)
			{
				pGrid->SetItemText(nRow, nCol, pGroup->m_strID);
			}
		}
		else
		{
			pGroup->m_strID = pCell->szText;
		}
	}
}

void CGbtBatchItemGroupEditGrid::EndEdit_BatchItemValue(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtBatchItemRefValue *pValue = (CGbtBatchItemRefValue*)pCell->lParam;

	if (pValue != NULL)
	{
		pValue->m_strValue = pCell->szText;
	}
}


//////////////////////////////////////////////////////////////////////////
CGbtBatchGbtDataGroupEditGrid::CGbtBatchGbtDataGroupEditGrid(void)
{
	m_pTool = NULL;
	m_pGbtBatchItemGroups = NULL;
	m_pDevice = NULL;
}

CGbtBatchGbtDataGroupEditGrid::~CGbtBatchGbtDataGroupEditGrid(void)
{

}

void CGbtBatchGbtDataGroupEditGrid::InitExGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CGbtBatchGbtDataGroupEditGrid::InitGridTitle()
{
	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	SetRowCount(1);
	SetColumnCount(1);

	Item.col =  0;
	SetColumnType(0,GVET_NOEDIT);
	SetColumnWidth(0,200);
	Item.szText=_T("数据");
	Item.lParam=0;
	SetItem(&Item);

	SetRowHeight(0,20);
}

CGbtBatchGbtDataRef* CGbtBatchGbtDataGroupEditGrid::GetSelBatchGbtDataRef()
{
	CCellID idCell = GetFocusCell();

	if (idCell.row < 0 || idCell.col < 1)
	{
		return NULL;
	}

	CExBaseObject *pObj = (CExBaseObject*)GetItemData(idCell.row, idCell.col);

	return (CGbtBatchGbtDataRef*)pObj;
}

CGbtBatchGbtDataGroup* CGbtBatchGbtDataGroupEditGrid::GetSelBatchGbtDataGroup()
{
	CCellID idCell = GetFocusCell();

	if (idCell.row < 0 || idCell.col < 1)
	{
		return NULL;
	}

	CGbtBatchGbtDataGroup *pSelGroup = (CGbtBatchGbtDataGroup*)m_pGbtBatchItemGroups->GetAtIndex(idCell.col - 1);
	return pSelGroup;
}

void CGbtBatchGbtDataGroupEditGrid::DeleteGroup(long nGroupIndex)
{
	DeleteColumn(nGroupIndex+1);
	CString strText;

	for (nGroupIndex=1; nGroupIndex<m_nCols; nGroupIndex++)
	{
		strText.Format(/*_T("第%d组")*/g_sLangTxt_NumberGroup, nGroupIndex-1);
		SetItemText(0, nGroupIndex, strText);
	}
}


CGbtBatchItemGroup* CGbtBatchGbtDataGroupEditGrid::GetSelBatchItemGroup()
{
	CCellID idCell = GetFocusCell();

	if (idCell.row < 0 || idCell.col < 1)
	{
		return NULL;
	}

	CGbtBatchItemGroup *pSelGroup = (CGbtBatchItemGroup*)m_pGbtBatchItemGroups->GetAtIndex(idCell.col - 1);

	return pSelGroup;
}

void CGbtBatchGbtDataGroupEditGrid::ResetGroupEditGrid()
{
	SetColumnCount(1);
}

void CGbtBatchGbtDataGroupEditGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
	// 	if (nRow < 0 || nCol < 2)
	// 	{
	// 		return CGridCtrl::OnEditCell(nRow, nCol, nChar);
	// 	}

	GetParent()->PostMessage(WM_BATCHITEM_GRID_CELL_SEL_CHANGED, nRow,nCol);

	return CGridCtrl::OnEditCell(nRow, nCol, nChar);
}

BOOL CGbtBatchGbtDataGroupEditGrid::OnCellRButtonUp(const CCellID &idCell)
{
	return TRUE;
}


void CGbtBatchGbtDataGroupEditGrid::InsertBatchItemGroup(CGbtBatchItemGroup *pGroup, long nColIndex)
{
	if (nColIndex == -1)
	{
		nColIndex = m_pGbtBatchItemGroups->GetCount();
	}

	CString strTemp;

	strTemp.Format(/*_T("第%d组")*/g_sLangTxt_NumberGroup, nColIndex);
	InsertColumn(strTemp);

	ShowBatchItemGroup(pGroup, nColIndex, FALSE);
	AutoSizeColumn(nColIndex);
	Invalidate(FALSE);
}

void CGbtBatchGbtDataGroupEditGrid::ShowBatchItemGroupsFixRows()
{
	long nRows = m_pGbtBatchItemGroups->m_pGbtBatchItemGroupRef->GetValuesCount();
	nRows += 3;
	SetRowCount(nRows);

	long nRowIndex = 1;

	for (nRowIndex=1; nRowIndex<nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, 20);
	}

	nRowIndex = 1;
	Show_StaticString(nRowIndex, 0, /*_T("项目分类名称")*/g_sLangTxt_ItemClassName, 0);
	//Merge(nRowIndex, 0, nRowIndex, 1);

	nRowIndex++;
	Show_StaticString(nRowIndex, 0, /*_T("项目分类ID")*/g_sLangTxt_ItemClassId, 0);
	//Merge(nRowIndex, 0, nRowIndex, 1);

	ShowBatchItemGroup(m_pGbtBatchItemGroups->m_pGbtBatchItemGroupRef, 1, TRUE);

	AutoSizeColumn(0);
	//AutoSizeColumn(1);

}

void CGbtBatchGbtDataGroupEditGrid::ShowBatchItemGroup(CGbtBatchItemGroup *pGroup, long nGroupColIndex, BOOL bIsTitle)
{
	POS pos = pGroup->GetHeadPosition();
	CGbtBatchGbtDataRef *pItemRef = NULL;

	if (!bIsTitle)
	{
		Show_BatchItemGroupName(1, nGroupColIndex, pGroup);
		Show_BatchItemGroupID(2, nGroupColIndex, pGroup);
	}

	long nRowIndex = 3;

	while (pos != NULL)
	{
		pItemRef = (CGbtBatchGbtDataRef *)pGroup->GetNext(pos);

		if (bIsTitle)
		{
			ShowBatchGbtDataRefTitle(pItemRef, nRowIndex);
		}
		else
		{
			ShowBatchGbtDataRef(pItemRef, nGroupColIndex, nRowIndex);
		}

		nRowIndex++;
	}
}

void CGbtBatchGbtDataGroupEditGrid::ShowBatchGbtDataRefTitle(CGbtBatchGbtDataRef *pItemRef, long &nRowIndex)
{
	long nBeginIndex = nRowIndex;

	Show_StaticString(nRowIndex, 0, pItemRef->m_strName, 0);
}

void CGbtBatchGbtDataGroupEditGrid::ShowBatchGbtDataRef(CGbtBatchGbtDataRef *pItemRef, long nGroupColIndex, long &nRowIndex)
{
	GV_ITEM Item;

	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT | GVIF_FUNC | GVIF_BKCLR;
	Item.row = nRowIndex;
	Item.col = nGroupColIndex;
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = GVET_EDITBOX;
	Item.lParam = (LPARAM)pItemRef;
	Item.szText = pItemRef->m_strGbtDataValue;
	Item.pEditFunc = EndEdit_BatchGbtDataValue;
	Item.crBkClr = RGB(255, 255, 255);

	SetItem(&Item);
}
// 
// void CGbtBatchGbtDataGroupEditGrid::DeleteBatchGbtDataGroup(long nGroupColIndex)
// {
// 	DeleteColumn(nGroupColIndex);
// 	ResetScrollBars();
// 	Invalidate(FALSE);
// }
// 
// void  CGbtBatchGbtDataGroupEditGrid::OnEditCell(int nRow, int nCol, UINT nChar)
// {
// 	if (nRow == -1)
// 	{
// 		return;
// 	}
// 
// 	if (nCol != BATCHITEMEDIT_GRID_ID_DATAREF)
// 	{
// 		return CGridCtrl::OnEditCell(nRow, nCol, nChar);
// 	}
// 
// 	if (m_pXMatchRefObjectSelDlg == NULL)
// 	{
// 		m_pXMatchRefObjectSelDlg = new CXMatchRefObjectSelDlg(this);
// 		m_pXMatchRefObjectSelDlg->SetWindowTitle(_T("选择匹配的数据对象"));
// 		m_pXMatchRefObjectSelDlg->SetUseModeless();
// 		m_pXMatchRefObjectSelDlg->DoModal();
// 	}
// 	else
// 	{
// 		if (!m_pXMatchRefObjectSelDlg->IsWindowVisible())
// 		{
// 			m_pXMatchRefObjectSelDlg->ShowWindow(SW_SHOW);
// 		}
// 
// 		m_pXMatchRefObjectSelDlg->BringWindowToTop();
// 	}
// 
// 	if (m_pTool->IsDatasChanged())
// 	{
// 		m_pXMatchRefObjectSelDlg->ShowExBaseList(m_pTool->GetRefDatas(), TRUE);
// 		m_pTool->SetDataChanged(FALSE);
// 	}
// }
// 
// void CGbtBatchGbtDataGroupEditGrid::Show_StaticString(const int& nRow, const int& nCol, const CString &strText, LPARAM lParam)
// {
// 	GV_ITEM Item;
// 
// 	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT;
// 	Item.row = nRow;
// 	Item.col = nCol;
// 	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
// 	Item.nDataType = GVET_NOEDIT;
// 	Item.lParam = lParam;
// 	Item.szText = strText;
// 
// 	SetItem(&Item);
// }
// 
// void CGbtBatchGbtDataGroupEditGrid::Show_BatchGbtDataGroupName(int nRow, int nCol,CGbtBatchGbtDataGroup *pGroup)
// {
// 	GV_ITEM Item;
// 
// 	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT | GVIF_FUNC;
// 	Item.row = nRow;
// 	Item.col = nCol;
// 	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
// 	Item.nDataType = GVET_EDITBOX;
// 	Item.lParam = (LPARAM)pGroup;
// 	Item.szText = pGroup->m_strName;
// 	Item.pEditFunc = EndEdit_BatchItemGroupName;
// 
// 	SetItem(&Item);
// }
// 
// void CGbtBatchGbtDataGroupEditGrid::Show_BatchGbtDataGroupID(int nRow, int nCol,CGbtBatchGbtDataGroup *pGroup)
// {
// 	GV_ITEM Item;
// 
// 	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT | GVIF_FUNC;
// 	Item.row = nRow;
// 	Item.col = nCol;
// 	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
// 	Item.nDataType = GVET_EDITBOX;
// 	Item.lParam = (LPARAM)pGroup;
// 	Item.szText = pGroup->m_strID;
// 	Item.pEditFunc = EndEdit_BatchItemGroupID;
// 
// 	SetItem(&Item);
// }

void CGbtBatchGbtDataGroupEditGrid::EndEdit_BatchGbtDataValue(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtBatchGbtDataRef *pValue = (CGbtBatchGbtDataRef*)pCell->lParam;

	if (pValue != NULL)
	{
		pValue->m_strGbtDataValue = pCell->szText;
	}
}

