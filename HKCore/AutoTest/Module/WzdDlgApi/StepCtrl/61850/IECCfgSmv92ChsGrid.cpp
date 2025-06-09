#include "StdAfx.h"
#include "IECCfgSmv92ChsGrid.h"

#include "../../../../../61850/Module/UI/Dlg92DataQuality.h"
#include "../../../../../61850/Module/XLanguageResourceIec.h"

//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

#define IECCFG_CHS_COLS 5

CIECCfgSmv92ChsGrid::CIECCfgSmv92ChsGrid()
{

}


CIECCfgSmv92ChsGrid::~CIECCfgSmv92ChsGrid(void)
{
	
}

void CIECCfgSmv92ChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_CHS_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIECCfgSmv92ChsGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_CHS_COLS]={
		_T("SMV通道"),
		_T("描述"),
		_T("通道类型"),
		_T("测试仪通道"),
		_T("品质")
	};

	int iWidth[IECCFG_CHS_COLS]={60, 50, 60, 60, 90};

	CIECCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_CHS_COLS);
}


void CIECCfgSmv92ChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG92CH);

	if (nClassID != CFGCLASSID_CIECCFG92CH)
	{
		return;
	}

	CIecCfg92Ch *p92Ch = (CIecCfg92Ch*)pData;

	if (CCfgDataMngrConstGlobal::IsViewOnlyUsedInChs())
	{
		if (p92Ch->m_nIndexExternal == -1)
		{
			return;
		}
	}

	CIECCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

	CString strName = p92Ch->m_strDescExternal;
	strName = strName.Mid(0, strName.Find('-'));
	Show_String(pData, nRow, IECCFG_COL_ID_92CH_DESC, &strName, EndEditCellDesc );
	ShowCfgCh_Type(pData, nRow, IECCFG_COL_ID_92CH_CHTYPE, &p92Ch->m_strChType, iecfg_Smv92ChDataType);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_92CH_APPCH, &p92Ch->m_strAppChID, iecfg_SmvAppChDataType);
	Show_Hex(pData, nRow, IECCFG_COL_ID_92CH_QUALITY, &p92Ch->m_nQuality, 4,FALSE);

	nRow++;
}

void CIECCfgSmv92ChsGrid::UpdateQuality(CExBaseObject *pData, const int& nRow)
{
	CIecCfg92Ch *p92Ch = (CIecCfg92Ch*)pData;
		
	Show_Hex(pData, nRow, IECCFG_COL_ID_92CH_QUALITY, &p92Ch->m_nQuality, 4,FALSE);
	RedrawCell(nRow, IECCFG_COL_ID_92CH_QUALITY);
}

void CIECCfgSmv92ChsGrid::UpdateQuality()
{
	CExBaseObject *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 1;

	while (pos != NULL)
	{
		pObj = m_pDatas->GetNext(pos);
		UpdateQuality(pObj, nRowIndex);
		nRowIndex++;
	}
}

BOOL CIECCfgSmv92ChsGrid::OnCellRButtonUpEx(UINT nFlags, CPoint point)
{
	CCellID rightClickDownCell = GetCellFromPt(point);
	OnLButtonDown(nFlags, point);
	SetQualityValue(rightClickDownCell.row, rightClickDownCell.col);
	return TRUE;
}

void CIECCfgSmv92ChsGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	SetQualityValue(nRow,nCol);
	CExBaseListGrid::OnEditCellLBDblClk(nRow, nCol, nChar);
}

void CIECCfgSmv92ChsGrid::EndEditCellDesc(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	CIecCfg92Ch* pCh = (CIecCfg92Ch*)pVCellData->pObj;
	CString strHead = pCh->m_strDescExternal.Mid(0, pCh->m_strDescExternal.Find('-'));
	CString strBody = pCh->m_strDescExternal.Mid(pCh->m_strDescExternal.Find('-'));

	if (strHead != pCell->szText)
	{
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		pCh->m_strDescExternal = pCell->szText + strBody;
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}
}

BOOL CIECCfgSmv92ChsGrid::SetQualityValue(int nRow, int nCol)
{
	if (nCol != IECCFG_COL_ID_92CH_QUALITY)
	{
		return FALSE;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)GetItemData(nRow, nCol);
	CIecCfg92Ch *p92Ch = (CIecCfg92Ch*)pVCellData->pObj;

	ASSERT (p92Ch != NULL);
	ASSERT (p92Ch->GetClassID() == CFGCLASSID_CIECCFG92CH);

	CWnd *pWnd = AfxGetMainWnd();
	pWnd->SetFocus();
	CDlg92DataQuality dlg(pWnd);

	if (dlg.m_bHasShowDlg == TRUE)
	{
		return FALSE;
	} 
	else
	{
		dlg.m_bHasShowDlg = TRUE;
	}


	dlg.m_dwQuality = p92Ch->m_nQuality;

	if (dlg.DoModal() == IDCANCEL)
	{
		dlg.m_bHasShowDlg = FALSE;
		return TRUE;
	}

	dlg.m_bHasShowDlg = FALSE;

	if (dlg.m_bEditAll)
	{
		CIecCfgChsBase *pCfgChs = (CIecCfgChsBase*)p92Ch->GetParent();
		POS pos = pCfgChs->GetHeadPosition();

		while (pos != NULL)
		{
			p92Ch = (CIecCfg92Ch *)pCfgChs->GetNext(pos);
			p92Ch->m_nQuality = dlg.m_dwQuality;
		}

		UpdateQuality();
	}
	else
	{
		p92Ch->m_nQuality = dlg.m_dwQuality;
		UpdateQuality(p92Ch,nRow);
	}

	iecfg_SetModified(p92Ch);
	return TRUE;
}