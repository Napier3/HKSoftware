#include "StdAfx.h"
#include "XMatchEditGridCtrlBase.h"
#include "..\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CXMatchDatasetSelDlg* CXMatchEditGridCtrlBase::m_pAllDatasDlg = NULL;
// long CXMatchEditGridCtrlBase::g_nAllDatasDlgRef = 0;
// 
// 
// CXMatchRefObjectSelDlg* CXMatchEditGridCtrlBase::m_pMatchedDatasDlg = NULL;
// long CXMatchEditGridCtrlBase::m_nMatchedDatasDlgRef = 0;

CXMatchEditGridCtrlBase::CXMatchEditGridCtrlBase(void)
{
// 	m_pXMatchTool = NULL;
// 	m_pMatchedDatasDlg = NULL;
// 	m_pDataSelChangeMsgRcvWnd = NULL;
// 
// 	m_nMatchedDatasDlgRef++;
// 	m_nShowDataMode = 1;
// 	g_nAllDatasDlgRef++;
// 	m_bShowMatchDataChanged = FALSE;
	m_pDlgsParentWnd = this;
}

CXMatchEditGridCtrlBase::~CXMatchEditGridCtrlBase(void)
{
// 	m_nMatchedDatasDlgRef--;
// 
// 	if (m_nMatchedDatasDlgRef == 0)
// 	{
// 		if (m_pMatchedDatasDlg != NULL)
// 		{
// 			m_pMatchedDatasDlg->DestroyWindow();
// 			delete m_pMatchedDatasDlg;
// 			m_pMatchedDatasDlg = NULL;
// 		}
// 	}
// 
// 	g_nAllDatasDlgRef--;
// 
// 	if (g_nAllDatasDlgRef == 0)
// 	{
// 		if (m_pAllDatasDlg != NULL)
// 		{
// 			m_pAllDatasDlg->DestroyWindow();
// 			delete m_pAllDatasDlg;
// 			m_pAllDatasDlg = NULL;
// 		}
// 	}
}


void CXMatchEditGridCtrlBase::ShowMatch(CXMatchToolBase *pXMatchTool)
{
	if (m_pAllDatasDlg != NULL)
	{
		m_pAllDatasDlg->ShowWindow(SW_HIDE);
	}

	if (m_pMatchedDatasDlg != NULL)
	{
		m_pMatchedDatasDlg->ShowWindow(SW_HIDE);
	}

	m_bShowMatchDataChanged = TRUE;
	ASSERT(pXMatchTool != NULL);

	m_pXMatchTool = pXMatchTool;
	CXMatchList *pDstXMatchList = pXMatchTool->GetDstMatchList();
	ShowDatas(pDstXMatchList);
	AutoSizeColumn(XMATCH_GRID_ID_SRC);
	AutoSizeColumn(XMATCH_GRID_ID_DST);
	ResetScrollBars();
	Invalidate(FALSE);
}


void CXMatchEditGridCtrlBase::InitGrid()
{
	SetListMode(FALSE);
	SetRowCount(1);
	SetColumnCount(XMATCH_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CXMatchEditGridCtrlBase::InitGridTitle()
{
	CString cTempStr[XMATCH_GRID_COLS]={g_sLangTxt_Index/*_T("编号")*/, g_sLangTxt_SourceDataObject/*_T("源数据对象")*/,g_sLangTxt_MatchDataObject/* _T("匹配数据对象")*/};
	int iWidth[XMATCH_GRID_COLS]={60,120,120};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, XMATCH_GRID_COLS);
}

void CXMatchEditGridCtrlBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);
	ASSERT ( pData->GetClassID() == KDBCLASSID_CXMATCHOBJECT);

	if (bInsertRow)
	{
		InsertRow(NULL);
	}

	Show_Index(pData, nRow, EXBASEGRID_COL_ID_INDEX);
	Show_XMatchSrc((CXMatchObject*)pData, nRow, XMATCH_GRID_ID_SRC);
	Show_XMatchDst((CXMatchObject*)pData, nRow, XMATCH_GRID_ID_DST);

	nRow++;
}


void CXMatchEditGridCtrlBase::Show_XMatchSrc(CXMatchObject *pXMatchObj, const int &nRow, const int &nCol)
{
	Show_StaticString(pXMatchObj->m_pRefObject, nRow, nCol, &pXMatchObj->m_pRefObject->m_strName);
}

void CXMatchEditGridCtrlBase::Show_XMatchDst(CXMatchObject *pXMatchObj, const int &nRow, const int &nCol)
{
	CExBaseList *pListMatchRef = &pXMatchObj->m_listMacthRefObject;
	long nCount = pListMatchRef->GetCount();
	CExBaseObject *pRefObj = NULL;
	CString strDataName;

	if (nCount == 0)
	{
		Show_StaticString(pListMatchRef, nRow, nCol, _T(""));
	}
	else if (nCount == 1)
	{
		pRefObj = pXMatchObj->GetMatchRef();

		if (m_bShowID)
		{
			strDataName.Format(_T("%s[%s]"), pRefObj->m_strName, pRefObj->m_strID);
			Show_StaticString(pRefObj, nRow, nCol, &strDataName);
		}
		else
		{
			Show_StaticString(pRefObj, nRow, nCol, &pRefObj->m_strName);
		}
	}
	else
	{
		CString strText;
		POS pos = pListMatchRef->GetHeadPosition();

		while (pos != NULL)
		{
			pRefObj = pListMatchRef->GetNext(pos);

			if (m_bShowID)
			{
				strDataName.Format(_T("%s[%s]"), pRefObj->m_strName, pRefObj->m_strID);
				strText.AppendFormat(_T("【%s】"), strDataName);
			}
			else
			{
				strText.AppendFormat(_T("【%s】"), pRefObj->m_strName);
			}
		}

		Show_StaticString(pRefObj, nRow, nCol, &strText);
	}

	SetItemFormat(nRow, nCol, DT_LEFT);
}

// void CXMatchEditGridCtrlBase::CreateMatchedDatasDlg()
// {
// 	if (m_pMatchedDatasDlg == NULL)
// 	{
// 		m_pMatchedDatasDlg = new CXMatchRefObjectSelDlg(this, this);
// 		m_pMatchedDatasDlg->SetWindowTitle(g_sLangTxt_SelMatchDataObject/*_T("选择匹配的数据对象")*/);
// 		m_pMatchedDatasDlg->SetUseModeless();
// 		m_pMatchedDatasDlg->DoModal();
// 	}
// 	else
// 	{
// 		m_pMatchedDatasDlg->ShowWindow(SW_SHOW);
// 	}
// }
// 
// void CXMatchEditGridCtrlBase::CreateAllDatasDlg()
// {
// 	if (m_pAllDatasDlg == NULL)
// 	{
// 		m_pAllDatasDlg = new CXMatchDatasetSelDlg(this);
// 		m_pAllDatasDlg->SetWindowTitle(g_sLangTxt_SelMatchDataObject/*_T("选择匹配的数据对象")*/);
// 		m_pAllDatasDlg->SetUseModeless();
// 		m_pAllDatasDlg->DoModal();
// 	}
// 	else
// 	{
// 		if (!m_pAllDatasDlg->IsWindowVisible())
// 		{
// 			m_pAllDatasDlg->ShowWindow(SW_SHOW);
// 		}
// 
// 		m_pAllDatasDlg->BringWindowToTop();
// 	}
// 
// 	m_pAllDatasDlg->m_pEdit = this;
// }

void  CXMatchEditGridCtrlBase::OnEditCell(int nRow, int nCol, UINT nChar)
{
	if (nRow == -1)
	{
		return;
	}

	if (nCol != XMATCH_GRID_ID_DST)
	{
		return CGridCtrl::OnEditCell(nRow, nCol, nChar);
	}

	CreateAllDatasDlg();
	ShowAllDatasToDlg();
}
// 
// void CXMatchEditGridCtrlBase::ShowAllDatasToDlg()
// {
// 	if (m_pMatchedDatasDlg != NULL)
// 	{
// 		if (m_pMatchedDatasDlg->IsWindowVisible())
// 		{
// 			m_pMatchedDatasDlg->ShowWindow(SW_HIDE);
// 		}
// 	}
// 
// 	if (m_bShowMatchDataChanged)
// 	{
// 		m_pAllDatasDlg->ResetDatasetList();
// 		m_pAllDatasDlg->AddDataset(m_pXMatchTool->GetSrcRefList());
// 		m_pAllDatasDlg->ShowDatasetTree();
// 		m_bShowMatchDataChanged = FALSE;
// 	}
// 
// 	if (!m_pAllDatasDlg->IsWindowVisible())
// 	{
// 		m_pAllDatasDlg->ShowWindow(SW_SHOW);
// 	}
// 
// 	m_pAllDatasDlg->BringWindowToTop();
// }
// 
// void CXMatchEditGridCtrlBase::ShowMatchedDatasToDlg()
// {
// 	if (m_pAllDatasDlg != NULL)
// 	{
// 		if (m_pAllDatasDlg->IsWindowVisible())
// 		{
// 			m_pAllDatasDlg->ShowWindow(SW_HIDE);
// 		}
// 	}
// 
// 	if (!m_pMatchedDatasDlg->IsWindowVisible())
// 	{
// 		m_pMatchedDatasDlg->ShowWindow(SW_SHOW);
// 	}
// 
// 
// 	m_pMatchedDatasDlg->BringWindowToTop();
// 
// 	CXMatchList *pXMatchList = m_pXMatchTool->GetDstMatchList();
// 	CXMatchObject *pXMatchObject = (CXMatchObject*)pXMatchList->GetAtIndex(m_idCurrentCell.row-1);
// 	ASSERT(pXMatchObject!= NULL);
// 	CExBaseList *pListMatchRef = &pXMatchObject->m_listMacthRefObject;
// 	m_pMatchedDatasDlg->ShowExBaseList(pListMatchRef, TRUE);
// }

BOOL CXMatchEditGridCtrlBase::OnCellRButtonUp(const CCellID &idCell)
{
	if (!idCell.IsValid())
	{
		return FALSE;
	}

	if (idCell.row == -1)
	{
		return FALSE;
	}

	if (idCell.col != XMATCH_GRID_ID_DST)
	{
		return FALSE;
	}

	SetFocusCell(-1,-1);
	SetFocusCell(idCell.row,idCell.col);
	m_LeftClickDownCell = idCell;
	m_idCurrentCell = idCell;

	CXMatchList *pXMatchList = m_pXMatchTool->GetDstMatchList();
	CXMatchObject *pXMatchObject = (CXMatchObject*)pXMatchList->GetAtIndex(m_idCurrentCell.row-1);
	ASSERT(pXMatchObject!= NULL);

	if (pXMatchObject == NULL)
	{
		return FALSE;
	}

	CreateMatchedDatasDlg();
	ShowMatchedDatasToDlg(m_idCurrentCell.row-1);	

	return TRUE;
}


void CXMatchEditGridCtrlBase::SetMatchRefData(CExBaseObject *pRefObject)
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

	CXMatchList *pXMatchList = m_pXMatchTool->GetDstMatchList();
	CXMatchObject *pXMatchObject = (CXMatchObject*)pXMatchList->GetAtIndex(m_idCurrentCell.row-1);
	ASSERT(pXMatchObject!= NULL);

	pXMatchObject->SetMacthRefObj(pRefObject);
	int nRow = m_idCurrentCell.row;
	ShowData(pXMatchObject, nRow, FALSE);
	Invalidate(FALSE);

	if (m_pDataSelChangeMsgRcvWnd)
	{
		m_pDataSelChangeMsgRcvWnd->PostMessage(WM_DVMMAPEDIT_KEY_CHANGED, 0, 0);
	}
}
// 
// CExBaseObject* CXMatchEditGridCtrlBase::GetPopSelectData()
// {
// 	if (m_pAllDatasDlg == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	if (!m_pAllDatasDlg->IsWindowVisible())
// 	{
// 		return NULL;
// 	}
// 
// 	return m_pAllDatasDlg->GetSelectDataObject();
// }

CXMatchObject* CXMatchEditGridCtrlBase::GetSelectMatchObject()
{
	if (m_idCurrentCell.row == 0 || m_idCurrentCell.row >= m_nRows)
	{
		return NULL; 
	}

	if (m_pXMatchTool == NULL)
	{
		return NULL;
	}

	CXMatchList *pXMatchList = m_pXMatchTool->GetDstMatchList();
	CXMatchObject *pXMatchObject = (CXMatchObject*)pXMatchList->GetAtIndex(m_idCurrentCell.row-1);
	return pXMatchObject;
}

BOOL CXMatchEditGridCtrlBase::OnCellKeyDelete(const CCellID &idCell)
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


void CXMatchEditGridCtrlBase::SetMatchRefData(CExBaseObject *pRefObject, const CCellID &idCell)
{
	if (idCell.row == 0 || idCell.row >= m_nRows)
	{
		return;
	}

	if (idCell.col != XMATCH_GRID_ID_DST)
	{
		return;
	}

	CXMatchList *pXMatchList = m_pXMatchTool->GetDstMatchList();
	CXMatchObject *pXMatchObject = (CXMatchObject*)pXMatchList->GetAtIndex(idCell.row-1);
	ASSERT(pXMatchObject!= NULL);

	if (pXMatchObject == NULL)
	{
		return;
	}

	pXMatchObject->SetMacthRefObj(pRefObject);
	Show_XMatchDst((CXMatchObject*)pXMatchObject, idCell.row, XMATCH_GRID_ID_DST);

	AutoSizeColumn(XMATCH_GRID_ID_DST);
	Invalidate(FALSE);

	if (m_pDataSelChangeMsgRcvWnd)
	{
		m_pDataSelChangeMsgRcvWnd->PostMessage(WM_DVMMAPEDIT_KEY_CHANGED, 0, 0);
	}
}
