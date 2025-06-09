#include "StdAfx.h"
#include "DvmCmpGrid.h"


//////////////////////////////////////////////////////////////////////////
//CDsvScriptEditGrid

#define COLOR_NO_MATCH  RGB(255, 170, 170)
#define COLOR_MATCH      RGB(255, 255, 255)

long CDvmCmpGridBase::g_nDvmCmpGridOptrRefCount = 0;

CDvmCmpGridBase::CDvmCmpGridBase()
{
	m_nAdjustBeginCol = 0;
	m_pDvmCmpTool = NULL;
	m_pDvmCmpRef = NULL;
}


CDvmCmpGridBase::~CDvmCmpGridBase(void)
{
	
}


void CDvmCmpGridBase::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DVMCMPOBJ_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDvmCmpGridBase::ShowDatas(CExBaseList *pExDataList)
{
	m_pDvmCmpTool = (CDvmCmpTool*)pExDataList;

	CExBaseListGrid::ShowDatas(pExDataList);

// 	AutoSizeColumn(DVMCMPOBJ_COL_INDEX);
// 	AutoSizeColumn(DVMCMPOBJ_COL_NAME);
// 	AutoSizeColumn(DVMCMPOBJ_COL_ID);
// 	AutoSizeColumn(DVMCMPOBJ_COL_MINOCC);
// 	AutoSizeColumn(DVMCMPOBJ_COL_MAXOCC);
}

void CDvmCmpGridBase::InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	CExBaseListGrid::InsertData(pData, bInvalidate);

// 	AutoSizeColumn(DVMCMPOBJ_COL_NAME);
// 	AutoSizeColumn(DVMCMPOBJ_COL_ID);
// 	AutoSizeColumn(DVMCMPOBJ_COL_MINOCC);
// 	AutoSizeColumn(DVMCMPOBJ_COL_MAXOCC);

	Invalidate(FALSE);
}

void  CDvmCmpGridBase::OnEditCell(int nRow, int nCol, UINT nChar)
{
// 	g_nDvmCmpGridOptrRefCount++;
// 
// 	if (g_nDvmCmpGridOptrRefCount > 1)
// 	{
// 		g_nDvmCmpGridOptrRefCount = 0;
// 		return;
// 	}

	CExBaseListGrid::OnEditCell(nRow, nCol, nChar);

	if (nCol > 0)
	{
		m_pDvmCmpRef->SetFocusCell(-1, -1);
		m_pDvmCmpRef->SelectRow(nRow);
	}
}

void CDvmCmpGridBase::InitGridTitle()
{
	CString cTempStr[DVMCMPOBJ_COLS]={_T("序号"),_T("名称"),_T("ID"),_T("类型"),_T("最小值"),_T("最大值"), _T("步长")};
	int iWidth[DVMCMPOBJ_COLS]={60,120, 120,100, 100, 100, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DVMCMPOBJ_COLS);
}	


void CDvmCmpGridBase::AfterOnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	g_nDvmCmpGridOptrRefCount++;

	if (g_nDvmCmpGridOptrRefCount > 1)
	{
		g_nDvmCmpGridOptrRefCount = 0;
		return;
	}
	
	int scrollPos1 = GetScrollPos32(SB_VERT);
	int scrollPos2 = m_pDvmCmpRef->GetScrollPos32(SB_VERT);

	if (scrollPos1 == scrollPos2)
	{	
		g_nDvmCmpGridOptrRefCount = 0;
	}
	else
	{
		if (nSBCode == SB_THUMBTRACK)
		{
			m_pDvmCmpRef->SetScrollPos32(SB_VERT, scrollPos1, TRUE);
		}

		m_pDvmCmpRef->OnVScroll(nSBCode, nPos, pScrollBar);
	}
}

void CDvmCmpGridBase::AfterOnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

}


void CDvmCmpGridBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (DVMCMP_CLASSID_CMPOBJ == nClassID);
	CDvmCmpObj *DvmCmpObj = (CDvmCmpObj *)pData;

	long nIndex = m_pDatas->FindIndex(pData) + 1;
	//Show_Index(pData, nIndex, DVMCMPOBJ_COL_INDEX);
	CString strIndex;
	strIndex.Format(_T("%d"), nIndex);
	SetItemText(nRow, DVMCMPOBJ_COL_INDEX, strIndex);


	nRow++;

	ShowDataValues(pData, nRow);
}

void CDvmCmpGridBase::ShowDataValues(CExBaseObject *pData, int& nRow)
{
	long nDataRow = nRow;
	CExBaseList *pList = (CExBaseList*)pData;
	long nRows = pList->GetCount();

	if (nRows == 0)
	{
		return;
	}

	long nIndex = 0;
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pValue = NULL;
	SetRowCount(nRows+m_nRows);

	while (pos != NULL)
	{
		pValue = pList->GetNext(pos);
		ShowDataValue(pValue, nRow);
		nRow++;
	}

	Merge(nDataRow-1, 0, nRow-1, 0);
	Merge(nDataRow,   1, nRow-1, 1);
}

void CDvmCmpGridBase::ShowDataValue(CExBaseObject *pData, int& nRow)
{
	
}

BOOL CDvmCmpGridBase::PostDvmCmpSelMsg(UINT nMsg, const CCellID &idCell)
{
	CExBaseObject *pSel = GetDataRow(idCell.row, 1);

	if (pSel == NULL)
	{
		return FALSE;
	}

	GetParent()->PostMessage(nMsg, (WPARAM)pSel, idCell.row);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
CDvmCmpGridStand::CDvmCmpGridStand()
{

}

CDvmCmpGridStand::~CDvmCmpGridStand()
{

}


void CDvmCmpGridStand::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (DVMCMP_CLASSID_CMPOBJ == nClassID);
	CDvmCmpObj *DvmCmpObj = (CDvmCmpObj *)pData;

	DvmCmpObj->StringCmp();
	CStringCmpBlocks *pStrCmpBlcksName = DvmCmpObj->GetNameCmp_Stand();
	CStringCmpBlocks *pStrCmpBlcksID = DvmCmpObj->GetIDCmp_Stand();

	if (DvmCmpObj->m_pStand != NULL)
	{
		CDvmData *pDvmData = (CDvmData*)DvmCmpObj->m_pStand;

		if (pStrCmpBlcksName != NULL)
		{
			Show_StringCmp(pData, nRow, DVMCMPOBJ_COL_NAME, pStrCmpBlcksName);
		}
		else
		{
			Show_StaticString(pData, nRow, DVMCMPOBJ_COL_NAME, &pDvmData->m_strName);
		}

		if (pStrCmpBlcksID != NULL)
		{
			Show_StringCmp(pData, nRow, DVMCMPOBJ_COL_ID, pStrCmpBlcksID);
		}
		else
		{
			Show_StaticString(pData, nRow, DVMCMPOBJ_COL_ID, &pDvmData->m_strID);
		}

		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_DATATYPE, &pDvmData->m_strDataType);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MINOCC, &pDvmData->m_strMin);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MAXOCC, &pDvmData->m_strMax);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_STEP, &pDvmData->m_strStep);

		if (DvmCmpObj->IsNameCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_NAME, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsIdCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_ID, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsDataTypeCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_DATATYPE, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsMaxCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_MAXOCC, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsMinCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_MINOCC, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsStepCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_STEP, RGB(255, 0, 0));
		}

		if (DvmCmpObj->m_pDestCmp == NULL)
		{
			SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_NO_MATCH);
		}
		else
		{
			SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_MATCH);
		}
	}
	else
	{
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_NAME, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_ID, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_DATATYPE, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MINOCC, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MAXOCC, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_STEP, m_strEmptyString);

		SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_NO_MATCH);
	}

	CDvmCmpGridBase::ShowData(pData, nRow, bInsertRow);
}

void CDvmCmpGridStand::ShowDataValue(CExBaseObject *pData, int& nRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (DVMCMP_CLASSID_CMPOBJ == nClassID);
	CDvmCmpObj *DvmCmpObj = (CDvmCmpObj *)pData;
	DvmCmpObj->StringCmp();
	CStringCmpBlocks *pStrCmpBlcksID = DvmCmpObj->GetIDCmp_Stand();

	if (DvmCmpObj->m_pStand != NULL)
	{
		CDvmValue *pDvmValue = (CDvmValue*)DvmCmpObj->m_pStand;

		if (pStrCmpBlcksID != NULL)
		{
			Show_StringCmp(pData, nRow, DVMCMPOBJ_COL_ID, pStrCmpBlcksID);
		}
		else
		{
			Show_StaticString(pData, nRow, DVMCMPOBJ_COL_ID, &pDvmValue->m_strID);
		}

		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_DATATYPE, &pDvmValue->m_strDataType);

		if (DvmCmpObj->IsIdCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_ID, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsDataTypeCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_DATATYPE, RGB(255, 0, 0));
		}

		if (DvmCmpObj->m_pDestCmp == NULL)
		{
			SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_NO_MATCH);
		}
		else
		{
			SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_MATCH);
		}
	}
	else
	{
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_NAME, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_ID, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_DATATYPE, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MINOCC, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MAXOCC, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_STEP, m_strEmptyString);

		SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_NO_MATCH);
	}
}

BOOL CDvmCmpGridStand::OnCellRButtonUp(const CCellID &idCell)
{
	if (PostDvmCmpSelMsg(WM_DVMCMPGRIDSTAND_POPDEST, idCell))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void CDvmCmpGridStand::UpdateDvmCmbObj(CExBaseObject *pDvmCmpObj)
{
	
}


void  CDvmCmpGridStand::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	CCellID idCell(nRow, nCol);

	PostDvmCmpSelMsg(WM_DVMCMPGRIDSTAND_SELDEST, idCell);
}

//////////////////////////////////////////////////////////////////////////
CDvmCmpGridDest::CDvmCmpGridDest()
{

}

CDvmCmpGridDest::~CDvmCmpGridDest()
{

}


void CDvmCmpGridDest::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (DVMCMP_CLASSID_CMPOBJ == nClassID);
	CDvmCmpObj *DvmCmpObj = (CDvmCmpObj *)pData;
	CStringCmpBlocks *pStrCmpBlcksName = DvmCmpObj->GetNameCmp_Dest();
	CStringCmpBlocks *pStrCmpBlcksID = DvmCmpObj->GetIDCmp_Dest();

	if (DvmCmpObj->m_pDestCmp != NULL)
	{
		CDvmData *pDvmData = (CDvmData*)DvmCmpObj->m_pDestCmp;

		if (pStrCmpBlcksName != NULL)
		{
			Show_StringCmp(pData, nRow, DVMCMPOBJ_COL_NAME, pStrCmpBlcksName);
		}
		else
		{
			Show_StaticString(pData, nRow, DVMCMPOBJ_COL_NAME, &pDvmData->m_strName);
		}

		if (pStrCmpBlcksID != NULL)
		{
			Show_StringCmp(pData, nRow, DVMCMPOBJ_COL_ID, pStrCmpBlcksID);
		}
		else
		{
			Show_StaticString(pData, nRow, DVMCMPOBJ_COL_ID, &pDvmData->m_strID);
		}

		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_DATATYPE, &pDvmData->m_strDataType);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MINOCC, &pDvmData->m_strMin);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MAXOCC, &pDvmData->m_strMax);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_STEP, &pDvmData->m_strStep);

		if (DvmCmpObj->IsNameCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_NAME, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsIdCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_ID, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsDataTypeCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_DATATYPE, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsMaxCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_MAXOCC, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsMinCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_MINOCC, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsStepCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_STEP, RGB(255, 0, 0));
		}

		if (DvmCmpObj->m_pStand == NULL)
		{
			SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_NO_MATCH);
		}
		else
		{
			SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_MATCH);
		}
	}
	else
	{
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_NAME, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_ID, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_DATATYPE,m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MINOCC, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MAXOCC, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_STEP, m_strEmptyString);

		SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_NO_MATCH);
	}

	long nCurr = nRow;
	CDvmCmpGridBase::ShowData(pData, nRow, bInsertRow);

	long nIndex = m_pDatas->FindIndex(pData);
	CString strIndex;

	if (DvmCmpObj->m_nDestIndex <  0)
	{
		strIndex.Empty();
	}
	else
	{
		strIndex.Format(_T("%d"), DvmCmpObj->m_nDestIndex+1);
	}

	SetItemText(nCurr, DVMCMPOBJ_COL_INDEX, strIndex);

	if (nIndex != DvmCmpObj->m_nDestIndex)
	{
		SetItemBkColour(nCurr, DVMCMPOBJ_COL_INDEX, COLOR_NO_MATCH);
	}
}


void CDvmCmpGridDest::ShowDataValue(CExBaseObject *pData, int& nRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (DVMCMP_CLASSID_CMPOBJ == nClassID);
	CDvmCmpObj *DvmCmpObj = (CDvmCmpObj *)pData;
	DvmCmpObj->StringCmp();
	CStringCmpBlocks *pStrCmpBlcksID = DvmCmpObj->GetIDCmp_Dest();

	if (DvmCmpObj->m_pDestCmp != NULL)
	{
		CDvmValue *pDvmValue = (CDvmValue*)DvmCmpObj->m_pDestCmp;
		//Show_StaticString(pData, nRow, DVMCMPOBJ_COL_NAME, &DvmCmpObj->m_pDestCmp->m_strName);
		if (pStrCmpBlcksID != NULL)
		{
			Show_StringCmp(pData, nRow, DVMCMPOBJ_COL_ID, pStrCmpBlcksID);
		}
		else
		{
			Show_StaticString(pData, nRow, DVMCMPOBJ_COL_ID, &pDvmValue->m_strID);
		}

		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_DATATYPE, &pDvmValue->m_strDataType);

		if (DvmCmpObj->IsIdCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_ID, RGB(255, 0, 0));
		}

		if (DvmCmpObj->IsDataTypeCmpError())
		{
			SetItemFgColour(nRow, DVMCMPOBJ_COL_DATATYPE, RGB(255, 0, 0));
		}

		if (DvmCmpObj->m_pStand == NULL)
		{
			SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_NO_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_NO_MATCH);
		}
		else
		{
			SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_MATCH);
			SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_MATCH);
		}
	}
	else
	{
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_NAME, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_ID, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_DATATYPE, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MINOCC, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_MAXOCC, m_strEmptyString);
		Show_StaticString(pData, nRow, DVMCMPOBJ_COL_STEP, m_strEmptyString);

		SetItemBkColour(nRow, DVMCMPOBJ_COL_NAME, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_ID, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_DATATYPE, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_MINOCC, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_MAXOCC, COLOR_NO_MATCH);
		SetItemBkColour(nRow, DVMCMPOBJ_COL_STEP, COLOR_NO_MATCH);
	}
}

BOOL CDvmCmpGridDest::OnCellRButtonUp(const CCellID &idCell)
{
	if (PostDvmCmpSelMsg(WM_DVMCMPGRIDDEST_POPSTAND, idCell))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void  CDvmCmpGridDest::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	CCellID idCell(nRow, nCol);

	PostDvmCmpSelMsg(WM_DVMCMPGRIDDEST_SELSTAND, idCell);
}


void CDvmCmpGridDest::UpdateDvmCmbObj(CExBaseObject *pDvmCmpObj)
{

}