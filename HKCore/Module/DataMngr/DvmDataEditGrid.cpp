#include "StdAfx.h"
#include "DvmDataEditGrid.h"

#include "..\XLanguage\XLanguageResource.h"
//////////////////////////////////////////////////////////////////////////
//CDvmDataNodesEditGrid
CDvmDataNodesEditGrid::CDvmDataNodesEditGrid()
{
	m_nAdjustBeginCol = 1;
}

CDvmDataNodesEditGrid::~CDvmDataNodesEditGrid()
{

}


void CDvmDataNodesEditGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DVM_DATANODES_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDvmDataNodesEditGrid::SetModifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	dvm_SetModifiedFlag(pData, bModified);
}


void CDvmDataNodesEditGrid::InitGridTitle()
{
	CString cTempStr[DVM_DATANODES_COLS]={g_sLangTxt_Index/*_T("序号")*/,g_sLangTxt_Name/*_T("名称")*/,_T("ID"),g_sLangTxt_Number2/*_T("编号/条目号")*/};
	int iWidth[DVM_DATANODES_COLS]={60,250, 250, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DVM_DATANODES_COLS);
}

void CDvmDataNodesEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (DVMCLASSID_CDVMDATASET != nClassID && DVMCLASSID_CDVMLOGICDEVICE != nClassID)
	{
		return;
	}

	Show_Index(pData, nRow, DVM_DATA_COL_INDEX);
	Show_String(pData, nRow, DVM_DATA_COL_NAME, &pData->m_strName, EndEditCell_Name);
	Show_String(pData, nRow, DVM_DATA_COL_ID, &pData->m_strID, EndEditCell_ID);

	if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		CDvmDataset *pDvmDataset = (CDvmDataset *)pData;
		Show_Long(pDvmDataset, nRow, DVM_DATA_COL_DATATYPE, &pDvmDataset->m_nIndex);
	}
	else
	{
		CDvmLogicDevice *pDvmLdevice = (CDvmLogicDevice *)pData;
		Show_Long(pDvmLdevice, nRow, DVM_DATA_COL_DATATYPE, &pDvmLdevice->m_nIndex);
	}

	nRow++;
}


void CDvmDataNodesEditGrid::EndEditCell_Name (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CExBaseObject *pData = (CExBaseObject *)pVellData->pObj;
	ASSERT (pData != NULL);

	if (pCell->szText == pData->m_strName)
	{
		return;
	}

	CExBaseList *pDatas = ((CDvmDataNodesEditGrid*)pGrid)->m_pDatas;
	CExBaseObject *pFind = pDatas->FindByName(pCell->szText);

	if (pFind != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ALreadyExist/*_T("【%s】在【%s】已经存在")*/, pCell->szText, pDatas->m_strID);
		pGrid->SetItemText(nRow, nCol, pData->m_strName);
		return;
	}

	pData->m_strName = pCell->szText;
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pData);
	((CExBaseListGrid*)pGrid)->AutoSizeColumn(nCol);
	((CDvmDataNodesEditGrid*)pGrid)->DataViewOptr_DataChanged(pGrid, nRow, nCol);
	pGrid->InvalidateGrid(FALSE);
}

void CDvmDataNodesEditGrid::EndEditCell_ID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CExBaseObject *pData = (CExBaseObject *)pVellData->pObj;
	ASSERT (pData != NULL);

	if (pCell->szText == pData->m_strID)
	{
		return;
	}

	CExBaseList *pDatas = ((CDvmDataNodesEditGrid*)pGrid)->m_pDatas;
	CExBaseObject *pFind = pDatas->FindByID(pCell->szText);

	if (pFind != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ALreadyExist/*_T("【%s】在【%s】已经存在")*/, pCell->szText, pDatas->m_strID);
		pGrid->SetItemText(nRow, nCol, pData->m_strID);
		return;
	}

	pData->m_strID = pCell->szText;
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pData);
	((CExBaseListGrid*)pGrid)->AutoSizeColumn(nCol);
	((CDvmDataNodesEditGrid*)pGrid)->DataViewOptr_DataChanged(pGrid, nRow, nCol);
	pGrid->InvalidateGrid(FALSE);
}


//////////////////////////////////////////////////////////////////////////
//CDvmDataEditGrid

CDvmDataEditGrid::CDvmDataEditGrid()
{
	m_pAttrEditGrid = NULL;
	m_nAdjustBeginCol = 0;
	m_nAdjustBeginCol = -1;
	//m_pCopyDvmData = NULL;
}


CDvmDataEditGrid::~CDvmDataEditGrid(void)
{
	
}


void CDvmDataEditGrid::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DVM_DATA_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDvmDataEditGrid::InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	CExBaseListGrid::InsertData(pData, bInvalidate);

	Invalidate(FALSE);
}


void  CDvmDataEditGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
	if (m_pAttrEditGrid != NULL)
	{
		CDvmData *pDvmData = (CDvmData*)GetData(nRow);

		if (pDvmData != NULL)
		{
			m_pAttrEditGrid->ShowDatas(pDvmData);
		}
	}

	return CExBaseListGrid::OnEditCell(nRow, nCol, nChar);
}


BOOL CDvmDataEditGrid::OnCellRButtonUpEx(UINT nFlags, CPoint point)
{
	if (m_pDatas == NULL)
	{
		return FALSE;
	}

	CExBaseList listDatas;
	long nCount = GetCurrSelDatas(listDatas, 1);
	CDvmData *pData = (CDvmData*)GetCurrSelData(1);
	listDatas.RemoveAll();

	if (nCount == 0 && (m_listCopyDatas.GetCount() == 0))
	{
		return FALSE;
	}

	CCellID rightClickDownCell = GetCellFromPt(point);
	CDvmData *pCurr = (CDvmData*)GetDataRow(rightClickDownCell.row, 1);

	SetFocus();
	CMenu menu;		
	menu.CreatePopupMenu();
	// 添加菜单项

	menu.AppendMenu(MF_STRING,ID_DATA_OPTR_ADD,g_sLangTxt_MdtInsert/*_T("插入")*/);

	if (nCount > 0)
	{
		menu.AppendMenu(MF_STRING,ID_DATA_OPTR_COPY,g_sLangTxt_Copy/*_T("拷贝")*/);
		menu.AppendMenu(MF_STRING,ID_DATA_OPTR_DELETE,g_sLangTxt_Delete/*_T("删除")*/);
	}

	if (nCount == 1 && pCurr == pData)
	{
		menu.AppendMenu(MF_STRING,ID_DATA_OPTR_MOVEUP,g_sLangTxt_UpMove/*_T("上移")*/);
		menu.AppendMenu(MF_STRING,ID_DATA_OPTR_MOVEDOWN,g_sLangTxt_DownMove/*_T("下移")*/);
	}

	//确定弹出式菜单的位置
	CWnd *pParent = GetParent();
	ClientToScreen(&point);
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y, pParent);			

	//资源回收
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	

	return TRUE;
}

void CDvmDataEditGrid::InitGridTitle()
{
	CString cTempStr[DVM_DATA_COLS]={g_sLangTxt_SerNumber/*_T("序号")*/
		,g_sLangTxt_Name/*_T("名称")*/
		,_T("ID"),g_sLangTxt_Type/*_T("类型")*/
		,_T("Datatye-ID"),_T("item-index")
		,g_sLangTxt_MinValue/*_T("最小值")*/
		,g_sLangTxt_MaxValue/*_T("最大值")*/
		,g_sLangTxt_Unit/*_T("单位")*/
		,g_sLangTxt_Step/*_T("步长")*/
		, g_sLangTxt_Value
		, g_sLangTxt_Nonstandard/*_T("非标")*/};
	int iWidth[DVM_DATA_COLS]={60,160, 160, 80, 80, 80, 80, 80, 80, 80, 60, 60};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DVM_DATA_COLS);
}	


void CDvmDataEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (DVMCLASSID_CDVMDATA != nClassID)
	{
		return;
	}

	CDvmData *pDvmData = (CDvmData *)pData;

	Show_Index(pDvmData, nRow, DVM_DATA_COL_INDEX);
	Show_String(pDvmData, nRow, DVM_DATA_COL_NAME, &pDvmData->m_strName, EndEditCell_Name);
	Show_String(pDvmData, nRow, DVM_DATA_COL_ID, &pDvmData->m_strID, EndEditCell_ID);
	Show_String(pDvmData, nRow, DVM_DATA_COL_DATATYPE, &pDvmData->m_strDataType);
	Show_Long(pDvmData, nRow, DVM_DATA_COL_DATATYPEID, &pDvmData->m_nDataTypeID);
	Show_Long(pDvmData, nRow, DVM_DATA_COL_ITEMINDEX, &pDvmData->m_nIndex);
	Show_String(pDvmData, nRow, DVM_DATA_COL_MIN, &pDvmData->m_strMin);
	Show_String(pDvmData, nRow, DVM_DATA_COL_MAX, &pDvmData->m_strMax);
	Show_String(pDvmData, nRow, DVM_DATA_COL_UNIT, &pDvmData->m_strUnit);
	Show_String(pDvmData, nRow, DVM_DATA_COL_STEP, &pDvmData->m_strStep);
	Show_String(pDvmData, nRow, DVM_DATA_COL_VALUE, &pDvmData->m_strValue);
	Show_Check(pDvmData, nRow, DVM_DATA_COL_CHANGE, &pDvmData->m_nChange, EndEditCell_Check);

	nRow++;
}

void CDvmDataEditGrid::EndEditCell_Name (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CDvmData *pData = (CDvmData *)pVellData->pObj;
	ASSERT (pData != NULL);

	if (pCell->szText == pData->m_strName)
	{
		return;
	}

	CExBaseList *pDatas = ((CDvmDataEditGrid*)pGrid)->m_pDatas;
	CExBaseObject *pFind = pDatas->FindByName(pCell->szText);

	if (pFind != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ALreadyExist/*_T("【%s】在【%s】已经存在")*/, pCell->szText, pDatas->m_strID);
		pGrid->SetItemText(nRow, nCol, pData->m_strName);
		return;
	}

	pData->m_strName = pCell->szText;
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pData);
}

void CDvmDataEditGrid::EndEditCell_ID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CDvmData *pData = (CDvmData *)pVellData->pObj;
	ASSERT (pData != NULL);

	if (pCell->szText == pData->m_strID)
	{
		return;
	}

	CExBaseList *pDatas = ((CDvmDataEditGrid*)pGrid)->m_pDatas;
	CExBaseObject *pFind = pDatas->FindByID(pCell->szText);

	if (pFind != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ALreadyExist/*_T("【%s】在【%s】已经存在")*/, pCell->szText, pDatas->m_strID);
		pGrid->SetItemText(nRow, nCol, pData->m_strID);
		return;
	}

	pData->m_strID = pCell->szText;
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pData);
}

void CDvmDataEditGrid::EndEditCell_DataType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{

}

void CDvmDataEditGrid::EndEditCell_Min (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{

}

void CDvmDataEditGrid::EndEditCell_Max (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{

}

void CDvmDataEditGrid::EndEditCell_Step (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{

}

void CDvmDataEditGrid::EndEditCell_Unit (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{

}

void CDvmDataEditGrid::OnDataOptrDelete()
{
	CExBaseList listDatas;
	long nCount = GetCurrSelDatas(listDatas, 1);
	CDvmData *pData = NULL;
	POS pos = listDatas.GetHeadPosition();
	long nRow = 0;
	m_pAttrEditGrid->ShowDatas(NULL);

	while (pos != NULL)
	{
		pData = (CDvmData *)listDatas.GetNext(pos);
		nRow = m_pDatas->FindIndex(pData);
		DeleteRow(nRow+1);
		m_pDatas->Delete(pData);
	}

	listDatas.RemoveAll();
	ResetScrollBars();
	Invalidate(FALSE);
	SetModifiedFlag(m_pDatas);
}

void CDvmDataEditGrid::OnDataOptrCopy()
{
	CExBaseList listDatas;
	long nCount = GetCurrSelDatas(listDatas, 1);
	m_listCopyDatas.DeleteAll();

	if (nCount > 0)
	{
		m_listCopyDatas.AppendClone(listDatas);
	}
	//m_pCopyDvmData = pData;

	listDatas.RemoveAll();
}

void CDvmDataEditGrid::OnDataOptrAdd(CDvmData *pSrcData)
{
	if (pSrcData == NULL)
	{
		return;
	}

	int nRow = m_idCurrentCell.row;
	CString strIndex;
	long nPos = pSrcData->m_strID.GetLength() - 1;
	TCHAR ch;

	while (TRUE)
	{
		ch = pSrcData->m_strID.GetAt(nPos);

		if ('0' <= ch && ch <= '9')
		{
			strIndex = ch + strIndex;
		}
		else
		{
			break;
		}

		nPos--;
	}

	long nIndex = 1;
	CString strText;
	strText = pSrcData->m_strID;
	
	if (strIndex.GetLength() > 0)
	{
		nIndex = CString_To_long(strIndex);
		strIndex = pSrcData->m_strID.Left(nPos+1);
	}
	else
	{
		strIndex = strText;
	}

	while (TRUE)
	{
		if (m_pDatas->FindByID(strText) == NULL)
		{
			break;
		}

		strText.Format(_T("%s%d"), strIndex, nIndex);
		nIndex++;
	}

	CDvmData *pNew = (CDvmData*)pSrcData->Clone();
	pNew->m_strID = strText;
	POS pos = m_pDatas->Find(pSrcData);
	m_pDatas->InsertAfter(pos, pNew);

	pos = pNew->GetHeadPosition();
	CDvmValue *pValue = NULL;
	while (pos != NULL)
	{
		pValue = (CDvmValue *)pNew->GetNext(pos);
		pValue->m_strID.Replace(pSrcData->m_strID, pNew->m_strID);
	}

	if (nRow > 0)
	{
		nRow = nRow + 1;
	}
	else
	{
		nRow = m_nRows;
	}

	if (nRow == m_nRows)
	{
		InsertRow(NULL, -1);
	}
	else
	{
		InsertRow(NULL, nRow);
	}

	SetRowHeight(nRow, EXBASEGRID_ROWHEIGHT);
	ShowData(pNew, nRow, FALSE);
}

void CDvmDataEditGrid::OnDataOptrAdd()
{
	CDvmData *pData = NULL;

	if (m_listCopyDatas.GetCount() == 0)
	{
		pData = (CDvmData*)GetCurrSelData(1);
		OnDataOptrAdd(pData);
	}
	else
	{
		POS pos = m_listCopyDatas.GetHeadPosition();

		while (pos != NULL)
		{
			pData = (CDvmData *)m_listCopyDatas.GetNext(pos);
			OnDataOptrAdd(pData);
		}
	}
	
	UpdateDataIndex();
	ResetScrollBars();
	Invalidate(FALSE);
	SetModifiedFlag(m_pDatas);
}

void CDvmDataEditGrid::OnDataOptrMoveUp()
{
	MoveUp();
}

void CDvmDataEditGrid::OnDataOptrMoveDown()
{
	MoveDown();
}


void CDvmDataEditGrid::SetModifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	dvm_SetModifiedFlag(m_pDatas, TRUE);
}

//////////////////////////////////////////////////////////////////////////
//CDvmValueEditGrid

CDvmValueEditGrid::CDvmValueEditGrid()
{
	m_nAdjustBeginCol = -1;
}


CDvmValueEditGrid::~CDvmValueEditGrid(void)
{

}

void CDvmValueEditGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DVM_DATA_VALUE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDvmValueEditGrid::ShowDatas(CExBaseList *pExDataList)
{
	m_pDatas = pExDataList;

	CExBaseListGrid::ShowDatas(pExDataList);

}


void CDvmValueEditGrid::InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	CExBaseListGrid::InsertData(pData, bInvalidate);

	Invalidate(FALSE);
}

void CDvmValueEditGrid::InitGridTitle()
{
	CString cTempStr[DVM_DATA_VALUE_COLS]={g_sLangTxt_SerNumber/*_T("序号")*/,_T("ID"),g_sLangTxt_DataType/*_T("数据类型")*/};
	int iWidth[DVM_DATA_VALUE_COLS]={40,160, 70};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DVM_DATA_VALUE_COLS);
}	

void CDvmValueEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	ASSERT (DVMCLASSID_CDVMVALUE == nClassID);
	CDvmValue *pValue = (CDvmValue *)pData;

	Show_Index(pData, nRow, DVM_DATA_VALUE_COL_INDEX);
	Show_String(pData, nRow,   DVM_DATA_VALUE_COL_ID,  &pValue->m_strID, EndEditCell_ID);
	Show_String(pData, nRow,   DVM_DATA_VALUE_COL_DATATYPE, &pValue->m_strDataType);

	nRow++;
}


void CDvmValueEditGrid::EndEditCell_ID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CDvmValue *pValue = (CDvmValue *)pVellData->pObj;
	ASSERT (pValue != NULL);

	if (pVellData->nVt != VCD_STRING)
	{
		return;
	}

	if (pValue->m_strID == pCell->szText)
	{
		return;
	}

	CDvmValueEditGrid *pDvmValueGrid = (CDvmValueEditGrid*)pGrid;

	if (pDvmValueGrid->m_pDatas->FindByID(pCell->szText) != NULL)
	{
		return;
	}

	pValue->m_strID = pCell->szText;
	pDvmValueGrid->SetModifiedFlag(pDvmValueGrid->m_pDatas);
}


void CDvmValueEditGrid::EndEditCell_DataType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CDvmValue *pValue = (CDvmValue *)pVellData->pObj;
	ASSERT (pValue != NULL);

	if (pVellData->nVt == VCD_STRING)
	{
		pValue->m_strDataType = pCell->szText;
	}
}

void CDvmValueEditGrid::SetModifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	dvm_SetModifiedFlag(m_pDatas, TRUE);
}

