#include "StdAfx.h"
#include "IecCfgSmvData6044CommonChsGrid.h"
#include "..\XLanguageResourceIec.h"
#include "..\UI\DlgCommonFT3Pub.h"

//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

CIecCfgSmvData6044CommonChsGrid::CIecCfgSmvData6044CommonChsGrid()
{

}


CIecCfgSmvData6044CommonChsGrid::~CIecCfgSmvData6044CommonChsGrid(void)
{
	
}

void CIecCfgSmvData6044CommonChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_COMMON_6044CH);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgSmvData6044CommonChsGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_COMMON_6044CH]={
		_T("SMV通道"),_T("描述"),_T("通道类型"),_T("通道映射"),_T("字节长度"),_T("初始值")
	};
	int iWidth[IECCFG_COLS_COMMON_6044CH]={60,160, 80,150,80,80};

	CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_COMMON_6044CH);
}


void CIecCfgSmvData6044CommonChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG6044COMMONCH);

	if (nClassID != CFGCLASSID_CIECCFG6044COMMONCH)
	{
		return;
	}

	CIecCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg6044CommonCh *p6044Ch = (CIecCfg6044CommonCh*)pData;

	Show_String(pData, nRow, IECCFG_COL_ID_6044CH_COMMON_DESC, &p6044Ch->m_strName, EndEditCell_String_Name );
	ShowCfgCh_Type(pData, nRow, IECCFG_COL_ID_6044CH_COMMON_CHTYPE, &p6044Ch->m_strChType, iecfg_SmvCommon6044ChDataType);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_6044CH_COMMON_APPCH, &p6044Ch->m_strAppChID, iecfg_SmvAppChDataType);
	Show_DataType_Val(pData, nRow, IECCFG_COL_ID_6044CH_COMMON_BYTELEN, iecfg_SmvChByteLen, &p6044Ch->m_nChLenth);
	Show_Long(pData, nRow, IECCFG_COL_ID_6044CH_COMMON_VALUE,    &p6044Ch->m_nValue);

	nRow++;
}

BOOL CIecCfgSmvData6044CommonChsGrid::OnCellRButtonUpEx(UINT nFlags, CPoint point)
{
	CCellID rightClickDownCell = GetCellFromPt(point);

	if (rightClickDownCell.col != IECCFG_COL_ID_6044CH_COMMON_VALUE)
	{
		return FALSE;
	}

	OnLButtonDown(nFlags, point);

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)GetItemData(rightClickDownCell.row, rightClickDownCell.col);
	CIecCfg6044CommonCh *p6044Ch = (CIecCfg6044CommonCh*)pVCellData->pObj;

	ASSERT (p6044Ch != NULL);
	ASSERT (p6044Ch->GetClassID() == CFGCLASSID_CIECCFG6044COMMONCH);

	CWnd *pWnd = AfxGetMainWnd();
	pWnd->SetFocus();

 	CDlgCommonFT3Pub dlg(pWnd);

	if (dlg.m_bHasShowDlg == TRUE)
	{
		return FALSE;
	} 
	else
	{
		dlg.m_bHasShowDlg = TRUE;
	}

 	dlg.m_dwValue = p6044Ch->m_nValue;
 
 	if (dlg.DoModal() == IDCANCEL)
 	{
		dlg.m_bHasShowDlg = FALSE;
 		return TRUE;
 	}

	dlg.m_bHasShowDlg = FALSE;

	if (dlg.m_dwValue == p6044Ch->m_nValue)
	{
		return TRUE;
	}

	p6044Ch->m_nValue = dlg.m_dwValue;

	Show_Long(p6044Ch, rightClickDownCell.row, IECCFG_COL_ID_6044CH_COMMON_VALUE,    &p6044Ch->m_nValue);
	RedrawCell(rightClickDownCell.row, IECCFG_COL_ID_6044CH_COMMON_VALUE);

	iecfg_SetModified(p6044Ch);
	return TRUE;
}

