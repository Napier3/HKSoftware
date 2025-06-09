#include "StdAfx.h"
#include "IecCfgSmvData6044CommonChsInGrid.h"
#include "..\XLanguageResourceIec.h"
#include "..\UI\DlgCommonFT3Sub.h"

//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

CIecCfgSmvData6044CommonChsInGrid::CIecCfgSmvData6044CommonChsInGrid()
{
	m_pGinAppChDataType = NULL;
	m_nAdjustBeginCol = -1;
}


CIecCfgSmvData6044CommonChsInGrid::~CIecCfgSmvData6044CommonChsInGrid(void)
{
	
}

void CIecCfgSmvData6044CommonChsInGrid::InitGrid()
{
//	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_COMMON_6044CHIN);
// 	SetFixedRowCount(1);
// 	SetFixedColumnCount(1);
	InitGridTitle();
	m_pGinAppChDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GinAppChDataType);
}

void CIecCfgSmvData6044CommonChsInGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_COMMON_6044CHIN]={
		_T("SMV通道"),_T("描述"),_T("通道类型"),_T("通道映射"),_T("字节长度"),_T("开入量映射")
	};
	int iWidth[IECCFG_COLS_COMMON_6044CH]={80,160, 80,100,80,200};

	CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_COMMON_6044CHIN);
}


void CIecCfgSmvData6044CommonChsInGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG6044COMMONCHIN);

	if (nClassID != CFGCLASSID_CIECCFG6044COMMONCHIN)
	{
		return;
	}

	CIecCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg6044CommonCh *p6044Ch = (CIecCfg6044CommonCh*)pData;

	Show_String(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_DESC, &p6044Ch->m_strName, EndEditCell_String_Name );
	ShowCfgCh_Type(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_CHTYPE, &p6044Ch->m_strChType, iecfg_SmvCommon6044ChInDataType);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_APPCH, &p6044Ch->m_strAppChID, iecfg_SmvAppChDataType);
 	Show_DataType_Val(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_BYTELEN, iecfg_SmvChByteLen, &p6044Ch->m_nChLenth);
// 	Show_DataType_Val(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_BINMAP, iecfg_GinAppChDataType, &p6044Ch->m_strDevChID);
//	Show_Long(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_BINMAP,    &p6044Ch->m_nValue);

	nRow++;
}

BOOL CIecCfgSmvData6044CommonChsInGrid::OnCellRButtonUpEx(UINT nFlags, CPoint point)
{
	CCellID rightClickDownCell = GetCellFromPt(point);

	if (rightClickDownCell.col != IECCFG_COL_ID_6044CHIN_COMMON_BINMAP)
	{
		return FALSE;
	}

	OnLButtonDown(nFlags, point);

	if (rightClickDownCell.col != IECCFG_COL_ID_6044CHIN_COMMON_BINMAP)
	{
		return FALSE;
	}

	return SetCommonBinMapByDlg(rightClickDownCell.row);
}

BOOL CIecCfgSmvData6044CommonChsInGrid::SetCommonBinMapByDlg(int nRow)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)GetItemData(nRow, IECCFG_COL_ID_6044CHIN_COMMON_BINMAP);
	CIecCfg6044CommonCh *p6044Ch = (CIecCfg6044CommonCh*)pVCellData->pObj;

	ASSERT (p6044Ch != NULL);
	ASSERT (p6044Ch->GetClassID() == CFGCLASSID_CIECCFG6044COMMONCHIN);

	if (p6044Ch->m_strChType != iecfg_SmvChDataType_Val_StateValue)
	{
		return FALSE;
	}

	CWnd *pWnd = AfxGetMainWnd();
	pWnd->SetFocus();

	CDlgCommonFT3Sub dlg(pWnd);

	if (dlg.m_bHasShowDlg == TRUE)
	{
		return FALSE;
	} 
	else
	{
		dlg.m_bHasShowDlg = TRUE;
	}

	dlg.m_pCfg6044CommonCh = p6044Ch;

	if (dlg.DoModal() == IDCANCEL)
	{
		dlg.m_bHasShowDlg = FALSE;
		return TRUE;
	}

	dlg.m_bHasShowDlg = FALSE;
	ShowCommonBinMap_StaticString(p6044Ch, nRow);
	RedrawCell(nRow, IECCFG_COL_ID_6044CHIN_COMMON_BINMAP);

	iecfg_SetModified(p6044Ch);
//	ExpandColumnsToFit();
	return TRUE;
}

void CIecCfgSmvData6044CommonChsInGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	CExBaseListGrid::OnEditCellLBDblClk(nRow, nCol, nChar);

	if (nCol != IECCFG_COL_ID_6044CHIN_COMMON_BINMAP)
	{
		return;
	}

	SetCommonBinMapByDlg(nRow);
}


void  CIecCfgSmvData6044CommonChsInGrid::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
{
	CIecCfgDataSmvChBase *pSmvCh = (CIecCfgDataSmvChBase*)pData;

// 	if (iecfg_IsStateValueChType(pSmvCh->m_strChType))//zhouhj 20211012 增加用于CommonFT3 Smv通道状态值
// 	{
// 		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_StateValue, pstrAppCh, EndEditCell_AppCh);
// 	}
	/*else*/ if (iecfg_IsOtherChType(pSmvCh->m_strChType))//zhouhj 20211012 增加用于CommonFT3 Smv通道其它
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_Other, pstrAppCh, EndEditCell_AppCh);
		Show_StaticString(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_BINMAP, _T("--"));
	}
	else
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_StateValue, pstrAppCh, EndEditCell_AppCh);
//		Show_DataType_Val(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_BINMAP, iecfg_GinAppChDataType, &pSmvCh->m_strDevChID);
		ShowCommonBinMap_StaticString(pData, nRow);
	}
}

void CIecCfgSmvData6044CommonChsInGrid::ShowCommonBinMap_StaticString(CExBaseObject *pData, int nRow)
{
	CIecCfgDataSmvChBase *pSmvCh = (CIecCfgDataSmvChBase*)pData;
	CString strShowString;
	strShowString = pSmvCh->m_strDevChID;

	if (m_pGinAppChDataType != NULL)
	{
		CEquationBuffer oEquationBuffer(pSmvCh->m_strDevChID);
		CString strBitID,strBinID;
		CExBaseObject *pDataTypeValue = NULL;
		strShowString = _T("");

		for (int nIndex = 0;nIndex<16;nIndex++)
		{
			strBinID = _T("");
			strBitID.Format(_T("bit%d"),nIndex);
			oEquationBuffer.ParseString(strBitID,strBinID);

			if (!strBinID.IsEmpty())
			{
				pDataTypeValue = m_pGinAppChDataType->FindByID(strBinID);

				if (pDataTypeValue != NULL)
				{
					strShowString.AppendFormat(_T("%s;"),pDataTypeValue->m_strName.GetString());
				}
			} 
		}

		if (strShowString.IsEmpty())
		{
			strShowString = _T("无");
		}
	}

	Show_StaticString(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_BINMAP,&strShowString);
}

