#include "StdAfx.h"
#include "GbtDataInterfaceMapEditGrid.h"
#include "..\..\XLanguageResourceAts.h"
#define MAPEDIT_GRID_COLS   4
#define MAPEDIT_GRID_ID_INEX 0
#define MAPEDIT_GRID_ID_DATAINTERFACE  1
#define MAPEDIT_GRID_ID_DATASCRIPT     2
#define MAPEDIT_GRID_ID_DATAREF        3


CXMatchDatasetSelDlg* CGbtDataInterfaceMapEditGrid::m_pXMatchDatasetSelDlg = NULL;
long CGbtDataInterfaceMapEditGrid::g_nXMatchDatasetSelDlgRef = 0;


CXMatchRefObjectSelDlg* CGbtDataInterfaceMapEditGrid::m_pXMatchRefObjectSelDlg = NULL;
long CGbtDataInterfaceMapEditGrid::m_nXMatchRefObjectSelDlgRef = 0;

CGbtDataInterfaceMapEditGrid::CGbtDataInterfaceMapEditGrid(void)
{
	m_nXMatchRefObjectSelDlgRef++;
	m_pTool = NULL;
	m_nShowDataMode = 1;

	g_nXMatchDatasetSelDlgRef++;
}

CGbtDataInterfaceMapEditGrid::~CGbtDataInterfaceMapEditGrid(void)
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


// void CGbtDataInterfaceMapEditGrid::ShowTool(CGbInsertStxmlFileTool *pTool)
// {
// 	ASSERT(pTool != NULL);
// 
// 	m_pTool = pTool;
// 	POS pos = m_pTool->GetHeadPosition();
// 	CGbtDataInterfaceMap *pGbtDataInterfaceMap = NULL;
// 	int nRowIndex = 1;
// 
// 	while (pos != NULL)
// 	{
// 		pGbtDataInterfaceMap = (CGbtDataInterfaceMap *)m_pTool->GetNext(pos);
// 		ShowGbtDataInterfaceMap(pGbtDataInterfaceMap, nRowIndex);
// 	}
// // 	CXMatchList *pDstXMatchList = pXMatchTool->GetDstMatchList();
// // 	ShowDatas(pDstXMatchList);
// // 	AutoSizeColumn(MAPEDIT_GRID_ID_SRC);
// // 	AutoSizeColumn(MAPEDIT_GRID_ID_DST);
// // 	ResetScrollBars();
// // 	Invalidate(FALSE);
// 	AutoSizeColumn(MAPEDIT_GRID_ID_DATAINTERFACE);
// 	AutoSizeColumn(MAPEDIT_GRID_ID_DATASCRIPT);
// 
// 	ResetScrollBars();
// 	Invalidate(FALSE);
// }

void CGbtDataInterfaceMapEditGrid::ShowGbInsertStxmlFile(CGbInsertStxmlFile *pGbInsertStxmlFile)
{
	m_pGbInsertStxmlFile = pGbInsertStxmlFile;
	m_pTool = (CGbInsertStxmlFileTool *)m_pGbInsertStxmlFile->GetAncestor(GBTWZDCLASSID_GBTINSERTSTXMLFILETOOL);

	POS pos = m_pGbInsertStxmlFile->GetHeadPosition();
	CGbtDataInterfaceMap *pGbtDataInterfaceMap = NULL;
	int nRowIndex = 1;

	while (pos != NULL)
	{
		pGbtDataInterfaceMap = (CGbtDataInterfaceMap *)m_pGbInsertStxmlFile->GetNext(pos);
		ShowGbtDataInterfaceMap(pGbtDataInterfaceMap, nRowIndex);
	}
	
	AutoSizeColumn(MAPEDIT_GRID_ID_DATAINTERFACE);
	AutoSizeColumn(MAPEDIT_GRID_ID_DATASCRIPT);

	ResetScrollBars();
	Invalidate(FALSE);
}

void CGbtDataInterfaceMapEditGrid::UpdateMap()
{
	long nIndex = 0;
	long nRows = GetRowCount();
	CGbtDataScriptMap *pGbtScptMap = NULL;

	for (nIndex=1; nIndex<nRows; nIndex++)
	{
		pGbtScptMap = (CGbtDataScriptMap*)GetItemData(nIndex, MAPEDIT_GRID_ID_DATAREF);
		ASSERT(pGbtScptMap != NULL);
		Show_ScriptRefObjs(nIndex, pGbtScptMap);
	}

	AutoSizeColumn(MAPEDIT_GRID_ID_DATAREF);
	Invalidate(FALSE);
}

void CGbtDataInterfaceMapEditGrid::InitExGrid()
{
	SetListMode(FALSE);
	SetRowCount(1);
	SetColumnCount(MAPEDIT_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();

	if (m_pXMatchDatasetSelDlg == NULL)
	{
		m_pXMatchDatasetSelDlg = new CXMatchDatasetSelDlg(this, this);
		m_pXMatchDatasetSelDlg->SetWindowTitle(/*_T("选择匹配的数据对象")*/g_sLangTxt_SelMatchDataObject);
		m_pXMatchDatasetSelDlg->SetUseModeless();
		m_pXMatchDatasetSelDlg->DoModal();
		m_pXMatchDatasetSelDlg->ShowDatasetTree();
		m_pXMatchDatasetSelDlg->ShowWindow(SW_HIDE);
	}
}

void CGbtDataInterfaceMapEditGrid::InitGridTitle()
{
	CString cTempStr[MAPEDIT_GRID_COLS]={/*_T("编号")*/g_sLangTxt_Index, /*_T("数据接口")*/g_sLangTxt_DataItfc, /*_T("数据映射")*/g_sLangTxt_DataMap, /*_T("目标引用数据")*/g_sLangTxt_DestRefData};
	int iWidth[MAPEDIT_GRID_COLS]={60,120,120, 120};

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	SetRowCount(1);
	SetColumnCount(MAPEDIT_GRID_COLS);

	for (int iCol=0;iCol<MAPEDIT_GRID_COLS;iCol++)
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

void CGbtDataInterfaceMapEditGrid::ShowGbtDataInterfaceMap(CGbtDataInterfaceMap *pGbtDataInterfaceMap, int &nRowIndex)
{
	long nBeginIndex = nRowIndex;
	POS pos = pGbtDataInterfaceMap->GetHeadPosition();
	CGbtDataScriptMap *pScptDataMap = NULL;

	while (pos != NULL)
	{
		pScptDataMap = (CGbtDataScriptMap *)pGbtDataInterfaceMap->GetNext(pos);
		ShowGbtDataScript(pScptDataMap, nRowIndex);
	}

	if (nRowIndex > nBeginIndex)
	{
		Merge(nBeginIndex, MAPEDIT_GRID_ID_DATAINTERFACE, nRowIndex-1, MAPEDIT_GRID_ID_DATAINTERFACE);
		Show_StaticString(nBeginIndex, MAPEDIT_GRID_ID_DATAINTERFACE, pGbtDataInterfaceMap->m_pGbtDataInterface->m_strName);
	}
}

void CGbtDataInterfaceMapEditGrid::ShowGbtDataScript(CGbtDataScriptMap *pGbtScptMap, int &nRowIndex)
{
	InsertRow(_T(""));
	Show_Index(nRowIndex, MAPEDIT_GRID_ID_INEX);
	Show_StaticString(nRowIndex, MAPEDIT_GRID_ID_DATASCRIPT, pGbtScptMap->m_pGbtDataScript->m_strName);
	Show_ScriptRefObjs(nRowIndex, pGbtScptMap);
	SetRowHeight(nRowIndex,20);
	nRowIndex++;
}

void CGbtDataInterfaceMapEditGrid::Show_ScriptRefObjs(const int& nRow, CGbtDataScriptMap *pGbtScptMap)
{
	POS pos = pGbtScptMap->GetHeadPosition();
	CExBaseObject *p = NULL;
	CString strText;

	while (pos != NULL)
	{
		p = pGbtScptMap->GetNext(pos);
		strText.AppendFormat(_T("【%s】"), p->m_strName);
	}

	if (strText.GetLength() == 0)
	{
		if (pGbtScptMap->m_strDataValue.GetLength() > 0)
		{
			strText = pGbtScptMap->m_strDataValue;
		}
		else
		{
			CDevice *pDevice = (CDevice*)pGbtScptMap->m_pGbtDataScript->GetAncestor(GBCLASSID_DEVICE);
			CGbtDatas *pGbtDatas = pDevice->m_pGbtDataInterfaces->m_pGbtDatas;
			CGbtData *pData = (CGbtData*)pGbtDatas->FindByID(pGbtScptMap->m_pGbtDataScript->m_strID);

			if (pData != NULL)
			{
				strText = pData->m_strValue;
			}
			else
			{
				strText = _T("0");
			}
		}
	}

	Show_StaticString(nRow, MAPEDIT_GRID_ID_DATAREF, strText, (LPARAM)pGbtScptMap);
	AutoSizeColumn(MAPEDIT_GRID_ID_DATAREF);
}


void CGbtDataInterfaceMapEditGrid::ShowXMatchRefObjectSelDlgDatas(CExBaseList *pDatas)
{
	if (m_pXMatchDatasetSelDlg != NULL)
	{
		m_pXMatchDatasetSelDlg->ShowWindow(SW_HIDE);
	}

	if (m_pXMatchRefObjectSelDlg == NULL)
	{
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

	m_pXMatchRefObjectSelDlg->ShowExBaseList(pDatas, TRUE);
	m_pXMatchRefObjectSelDlg->m_pEdit = this;
}

void CGbtDataInterfaceMapEditGrid::ShowXMatchRefObjectSelDlgDataset()
{
	if (m_pXMatchRefObjectSelDlg != NULL)
	{
		m_pXMatchRefObjectSelDlg->ShowWindow(SW_HIDE);
	}

	if (m_pXMatchDatasetSelDlg == NULL)
	{
		m_pXMatchDatasetSelDlg = new CXMatchDatasetSelDlg(this, this);
		m_pXMatchDatasetSelDlg->SetWindowTitle(/*_T("选择匹配的数据对象")*/g_sLangTxt_SelMatchDataObject);
		m_pXMatchDatasetSelDlg->SetUseModeless();
		m_pXMatchDatasetSelDlg->DoModal();
	}
	else
	{
		if (!m_pXMatchDatasetSelDlg->IsWindowVisible())
		{
			m_pXMatchDatasetSelDlg->ShowWindow(SW_SHOW);
		}

		m_pXMatchDatasetSelDlg->BringWindowToTop();

		CGbtDataScriptMap *pGbtScptMap = NULL;
		pGbtScptMap = (CGbtDataScriptMap*)GetItemData(m_idCurrentCell.row, MAPEDIT_GRID_ID_DATAREF);

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

BOOL CGbtDataInterfaceMapEditGrid::OnCellRButtonUp(const CCellID &idCell)
{
	if (!idCell.IsValid())
	{
		return FALSE;
	}


	//if (idCell.row <= 0)
	if (idCell.row <= 0 || idCell.col <= 0)
	{
		return FALSE;
	}

	if (idCell.col != MAPEDIT_GRID_ID_DATAREF)
	{
		return FALSE;
	}

	SetFocusCell(-1,-1);
	SetFocusCell(idCell.row,idCell.col);
	m_LeftClickDownCell = idCell;
	m_idCurrentCell = idCell;
	
	m_nShowDataMode = 2;

	CGbtDataScriptMap *pGbtScptMap = NULL;
	pGbtScptMap = (CGbtDataScriptMap*)GetItemData(m_idCurrentCell.row, MAPEDIT_GRID_ID_DATAREF);
	
	ShowXMatchRefObjectSelDlgDatas(pGbtScptMap);

	return TRUE;
}

BOOL CGbtDataInterfaceMapEditGrid::OnCellKeyDelete(const CCellID &idCell)
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

	return TRUE;
}

void  CGbtDataInterfaceMapEditGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
	if (nRow == -1)
	{
		return;
	}

	if (nCol != MAPEDIT_GRID_ID_DATAREF)
	{
		return CGridCtrl::OnEditCell(nRow, nCol, nChar);
	}

	ShowXMatchRefObjectSelDlgDataset();
// 	if (m_nShowDataMode != 1)
// 	{
// 		ShowXMatchRefObjectSelDlgDatas(m_pTool->GetRefDatas());
// 		m_pTool->SetDataChanged(FALSE);
// 		m_nShowDataMode = 1;
// 	}
// 	else
// 	{
// 		ShowXMatchRefObjectSelDlgDataset();
// 		if (m_pTool->IsDatasChanged())
// 		{
// 			ShowXMatchRefObjectSelDlgDatas(m_pTool->GetRefDatas());
// 			m_pTool->SetDataChanged(FALSE);
// 		}
// 		else
// 		{
// 			m_pXMatchRefObjectSelDlg->ShowWindow(SW_SHOW);
// 			m_pXMatchRefObjectSelDlg->BringWindowToTop();
// 		}
//	}
}

void  CGbtDataInterfaceMapEditGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	if (nRow == -1)
	{
		return;
	}

	if (nCol != MAPEDIT_GRID_ID_DATAREF)
	{
		return CGridCtrl::OnEditCell(nRow, nCol, nChar);
	}

	if (m_pXMatchDatasetSelDlg != NULL)
	{
		m_pXMatchDatasetSelDlg->ShowWindow(SW_HIDE);
	}

	CGbtDataScriptMap *pGbtScptMap = NULL;
	pGbtScptMap = (CGbtDataScriptMap*)GetItemData(nRow, MAPEDIT_GRID_ID_DATAREF);
	
	//2018-5-1  南瑞科技修改需求，可以进行公式的编辑
	//如果是公式编辑
	CWnd *pParentWnd = GetParent();
	LRESULT nExprEdit = pParentWnd->SendMessage(WM_MAPEDIT_DATAVALUE_EXPR_EDIT, (WPARAM)pGbtScptMap, (LPARAM)pGbtScptMap);

	//点击了取消
	if (nExprEdit == WM_MAPEDIT_DATAVALUE_EXPR_RET_CANCEL)
	{
		return;
	}
	else if (nExprEdit == WM_MAPEDIT_DATAVALUE_EXPR_RET_EDIT)
	{//点击了保存
	}
	else if (nExprEdit == WM_MAPEDIT_DATAVALUE_EXPR_NONE)
	{
		CXMatchDataObjEditDlg dlg;
		dlg.m_strDataName = pGbtScptMap->m_strName;
		dlg.m_strValue = pGbtScptMap->GetGbtDataScriptValue();

		if (dlg.DoModal() == IDCANCEL)
		{
			return ;
		}

		pGbtScptMap->m_strDataValue = dlg.m_strValue;
	}

// 	pGbtScptMap->m_pRefObject = NULL;
// 	pGbtScptMap->RemoveAll();
	pGbtScptMap->SetRefObject(NULL);

	Show_ScriptRefObjs(nRow, pGbtScptMap);

	AutoSizeColumn(MAPEDIT_GRID_ID_DATAREF);
	Invalidate(FALSE);

	if (m_pDataSelChangeMsgRcvWnd)
	{
		m_pDataSelChangeMsgRcvWnd->PostMessage(WM_MAPEDIT_KEY_CHANGED, 0, 0);
	}

	return;	
}

void CGbtDataInterfaceMapEditGrid::SetMatchRefData(CExBaseObject *pRefObject, const CCellID &idCell)
{
	if (idCell.row == 0 || idCell.row >= m_nRows)
	{
		return;
	}

	if (idCell.col != MAPEDIT_GRID_ID_DATAREF)
	{
		return;
	}

	CGbtDataScriptMap *pGbtScptMap = NULL;
	pGbtScptMap = (CGbtDataScriptMap*)GetItemData(idCell.row, MAPEDIT_GRID_ID_DATAREF);
	pGbtScptMap->SetRefObject(pRefObject);
// 	pGbtScptMap->m_pRefObject = pRefObject;
// 	pGbtScptMap->RemoveAll();
// 
// 	if (pRefObject != NULL)
// 	{
// 		pGbtScptMap->AddTail(pRefObject);
// 	}

	Show_ScriptRefObjs(idCell.row, pGbtScptMap);

	AutoSizeColumn(MAPEDIT_GRID_ID_DATAREF);
	Invalidate(FALSE);

	if (m_pDataSelChangeMsgRcvWnd)
	{
		m_pDataSelChangeMsgRcvWnd->PostMessage(WM_MAPEDIT_KEY_CHANGED, 0, 0);
	}
}

void CGbtDataInterfaceMapEditGrid::SetMatchRefData(CExBaseObject *pRefObject)
{
	if (pRefObject != NULL)
	{
		if (pRefObject->GetClassID() != GBCLASSID_DATAOBJ)
		{
			return;
		}
	}

	SetMatchRefData(pRefObject, m_idCurrentCell);

// 	if (m_idCurrentCell.row == 0 || m_idCurrentCell.row >= m_nRows)
// 	{
// 		return;
// 	}
// 
// 	if (m_idCurrentCell.col != MAPEDIT_GRID_ID_DATAREF)
// 	{
// 		return;
// 	}
// 	
// 	CGbtDataScriptMap *pGbtScptMap = NULL;
// 	pGbtScptMap = (CGbtDataScriptMap*)GetItemData(m_idCurrentCell.row, MAPEDIT_GRID_ID_DATAREF);
// 	pGbtScptMap->m_pRefObject = pRefObject;
// 	pGbtScptMap->RemoveAll();
// 
// 	if (pRefObject != NULL)
// 	{
// 		pGbtScptMap->AddTail(pRefObject);
// 	}
// 
// 	Show_ScriptRefObjs(m_idCurrentCell.row, pGbtScptMap);
// 
// 	AutoSizeColumn(MAPEDIT_GRID_ID_DATAREF);
// 	Invalidate(FALSE);
// 	
// 	if (m_pDataSelChangeMsgRcvWnd)
// 	{
// 		m_pDataSelChangeMsgRcvWnd->PostMessage(WM_MAPEDIT_KEY_CHANGED, 0, 0);
// 	}
}


void CGbtDataInterfaceMapEditGrid::Show_StaticString(const int& nRow, const int& nCol, const CString &strText, LPARAM lParam)
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

void CGbtDataInterfaceMapEditGrid::Show_Index(const int& nRow, const int& nCol)
{
	CString strText;
	strText.Format(_T("%d"), nRow);
	Show_StaticString(nRow, nCol, strText);
}
