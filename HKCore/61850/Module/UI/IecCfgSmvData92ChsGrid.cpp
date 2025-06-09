#include "StdAfx.h"
#include "IecCfgSmvData92ChsGrid.h"

#include "..\UI\Dlg92DataQuality.h"
#include "..\XLanguageResourceIec.h"

//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

CIecCfgSmvData92ChsGrid::CIecCfgSmvData92ChsGrid()
{

}


CIecCfgSmvData92ChsGrid::~CIecCfgSmvData92ChsGrid(void)
{
	
}

void CIecCfgSmvData92ChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);

	if (m_nViewChsPath)
	{
		SetColumnCount(IECCFG_COLS_92CH);
	} 
	else
	{
		SetColumnCount(IECCFG_COLS_92CH-1);
	}

	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgSmvData92ChsGrid::InitGridTitle()
{
	if (m_nViewChsPath)
	{
		CString cTempStr[IECCFG_COLS_92CH]={g_sLtxt_SMVChannel,g_sLtxt_Description,g_sLtxt_ChannelType,
			g_sLtxt_TestDeviceChannel,g_sLtxt_Quality,g_sLtxt_InputName,
			_T("输入端-路径")/*g_sLtxt_InputMap,*///_T("SMV通道"),_T("描述"),_T("通道类型"),_T("测试仪通道"),_T("品质"),_T("输入端-名称"), _T("输入端-路径")
		};
		int iWidth[IECCFG_COLS_92CH]={60,160, 80,90,90, 90, 90};

		CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_92CH);
	} 
	else
	{
		CString cTempStr[IECCFG_COLS_92CH-1]={g_sLtxt_SMVChannel,g_sLtxt_Description,g_sLtxt_ChannelType,
			g_sLtxt_TestDeviceChannel,g_sLtxt_Quality,g_sLtxt_InputName
			/*g_sLtxt_InputMap,*///_T("SMV通道"),_T("描述"),_T("通道类型"),_T("测试仪通道"),_T("品质"),_T("输入端-名称"), _T("输入端-路径")
		};

		int iWidth[IECCFG_COLS_92CH-1]={60,160, 80,90,90, 90};
		CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_92CH-1);
	}
}


void CIecCfgSmvData92ChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
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
			//if (p92Ch->m_strAddrExternal.GetLength() == 0)
			{
				return;
			}
		}
	}

	CIecCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

#ifdef USE_IECFG_ChsGrid_Desc_Not_Editable
	Show_StaticString(pData, nRow, IECCFG_COL_ID_92CH_DESC, &p92Ch->m_strName);
#else
	Show_String(pData, nRow, IECCFG_COL_ID_92CH_DESC, &p92Ch->m_strName, EndEditCell_String_NameAndID );
#endif

	ShowCfgCh_Type(pData, nRow, IECCFG_COL_ID_92CH_CHTYPE, &p92Ch->m_strChType, iecfg_Smv92ChDataType);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_92CH_APPCH, &p92Ch->m_strAppChID, iecfg_SmvAppChDataType);
	Show_Hex(pData, nRow, IECCFG_COL_ID_92CH_QUALITY, &p92Ch->m_nQuality, 4,FALSE);

	Show_StaticString(pData, nRow, IECCFG_COL_ID_92CH_DESCEXTERNAL, &p92Ch->m_strDescExternal);

	if (m_nViewChsPath)
	{
		Show_StaticString(pData, nRow, IECCFG_COL_ID_92CH_ADDREXTERNAL, &p92Ch->m_strAddrExternal);
	}

	//编号改变
	if (CCfgDataMngrConstGlobal::IsViewOnlyUsedInChs())
	{
		if (p92Ch->m_nIndexExternal != 65535)
		{
			CString strIndex;
			long nIndex=m_pDatas->FindIndex(pData);
			strIndex.Format(_T("%d / %d"), p92Ch->m_nIndexExternal+1, nIndex+1);
			SetItemText(nRow, 0, strIndex);
		}
	}

	nRow++;
}

void CIecCfgSmvData92ChsGrid::UpdateQuality(CExBaseObject *pData, const int& nRow)
{
	CIecCfg92Ch *p92Ch = (CIecCfg92Ch*)pData;
		
	Show_Hex(pData, nRow, IECCFG_COL_ID_92CH_QUALITY, &p92Ch->m_nQuality, 4,FALSE);
	RedrawCell(nRow, IECCFG_COL_ID_92CH_QUALITY);
}

void CIecCfgSmvData92ChsGrid::UpdateQuality()
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

BOOL CIecCfgSmvData92ChsGrid::OnCellRButtonUpEx(UINT nFlags, CPoint point)
{
	CCellID rightClickDownCell = GetCellFromPt(point);

// 	if (rightClickDownCell.col != IECCFG_COL_ID_92CH_QUALITY)
// 	{
// 		return FALSE;
// 	}

	OnLButtonDown(nFlags, point);
	SetQualityValue(rightClickDownCell.row, rightClickDownCell.col);

// 	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)GetItemData(rightClickDownCell.row, rightClickDownCell.col);
// 	CIecCfg92Ch *p92Ch = (CIecCfg92Ch*)pVCellData->pObj;
// 
// 	ASSERT (p92Ch != NULL);
// 	ASSERT (p92Ch->GetClassID() == CFGCLASSID_CIECCFG92CH);
// 
// 	CWnd *pWnd = AfxGetMainWnd();
// 	pWnd->SetFocus();
// 	CDlg92DataQuality dlg(pWnd);
// 
// 	if (dlg.m_bHasShowDlg == TRUE)
// 	{
// 		return FALSE;
// 	} 
// 	else
// 	{
// 		dlg.m_bHasShowDlg = TRUE;
// 	}
// 
// 
// 	dlg.m_dwQuality = p92Ch->m_nQuality;
// 
// 	if (dlg.DoModal() == IDCANCEL)
// 	{
// 		dlg.m_bHasShowDlg = FALSE;
// 		return TRUE;
// 	}
// 
// 	dlg.m_bHasShowDlg = FALSE;
// 
// 	if (dlg.m_bEditAll)
// 	{
// 		CIecCfgChsBase *pCfgChs = (CIecCfgChsBase*)p92Ch->GetParent();
// 		POS pos = pCfgChs->GetHeadPosition();
// 
// 		while (pos != NULL)
// 		{
// 			p92Ch = (CIecCfg92Ch *)pCfgChs->GetNext(pos);
// 			p92Ch->m_nQuality = dlg.m_dwQuality;
// 		}
// 
// 		UpdateQuality();
// 	}
// 	else
// 	{
// 		p92Ch->m_nQuality = dlg.m_dwQuality;
// 		UpdateQuality(p92Ch, rightClickDownCell.row);
// 	}
// 
// 	iecfg_SetModified(p92Ch);
	return TRUE;
}

void CIecCfgSmvData92ChsGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	SetQualityValue(nRow,nCol);
	CExBaseListGrid::OnEditCellLBDblClk(nRow, nCol, nChar);
}

BOOL CIecCfgSmvData92ChsGrid::SetQualityValue(int nRow, int nCol)
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