#include "StdAfx.h"
#include "IecCfgGinDataChsGrid.h"

#include "..\XLanguageResourceIec.h"


//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

CIecCfgGinDataChsGrid::CIecCfgGinDataChsGrid(BOOL bHasDevCh)
{
	m_bHasDevCh = bHasDevCh;
}


CIecCfgGinDataChsGrid::~CIecCfgGinDataChsGrid(void)
{
	
}

void CIecCfgGinDataChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	long nCols = IECCFG_COLS_GINCH;

	if (m_bHasDevCh)
	{
		nCols++;
	} 

	if (m_nViewChsPath == 0)
	{
		nCols--;
	}

	SetColumnCount(nCols);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgGinDataChsGrid::InitGridTitle()
{
	if (m_bHasDevCh)
	{
		if (m_nViewChsPath)
		{
			CString cTempStr[IECCFG_COLS_GINCH+1]={
				_T("通道")/*g_sLangTxt_Channel*/,g_sLtxt_Description,_T("路径"),
				g_sLtxt_ChannelType,g_sLtxt_InputMap,_T("开出量映射")//_T("通道"),_T("描述"),_T("通道类型"),_T("开入量映射")
			};
			int iWidth[IECCFG_COLS_GINCH+1]={60,160, 160,80,90,90};

			CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GINCH+1);
		} 
		else
		{
			CString cTempStr[IECCFG_COLS_GINCH]={
				_T("通道")/*g_sLangTxt_Channel*/,g_sLtxt_Description,
				g_sLtxt_ChannelType,g_sLtxt_InputMap,_T("开出量映射")//_T("通道"),_T("描述"),_T("通道类型"),_T("开入量映射")
			};
			int iWidth[IECCFG_COLS_GINCH]={60,160,80,90,90};

			CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GINCH);
		}
	} 
	else
	{
		if (m_nViewChsPath)
		{
			CString cTempStr[IECCFG_COLS_GINCH]={
				_T("通道")/*g_sLangTxt_Channel*/,g_sLtxt_Description,_T("路径"),
				g_sLtxt_ChannelType,g_sLtxt_InputMap//_T("通道"),_T("描述"),_T("通道类型"),_T("开入量映射")
			};
			int iWidth[IECCFG_COLS_GINCH]={60,160, 160,80,90};

			CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GINCH);
		} 
		else
		{
			CString cTempStr[IECCFG_COLS_GINCH-1]={
				_T("通道")/*g_sLangTxt_Channel*/,g_sLtxt_Description,
				g_sLtxt_ChannelType,g_sLtxt_InputMap//_T("通道"),_T("描述"),_T("通道类型"),_T("开入量映射")
			};

			int iWidth[IECCFG_COLS_GINCH-1]={60,160, 80,90};
			CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GINCH-1);
		}
	}
}


void CIecCfgGinDataChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFGGINCH);

	if (nClassID != CFGCLASSID_CIECCFGGINCH)
	{
		return;
	}

	CIecCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pData;
	pGinCh->InitAppIDText();

#ifdef USE_IECFG_ChsGrid_Desc_Not_Editable
	Show_StaticString(pData, nRow, IECCFG_COL_ID_GINCH_DESC, &pGinCh->m_strName );
#else
	Show_String(pData, nRow, IECCFG_COL_ID_GINCH_DESC, &pGinCh->m_strName, EndEditCell_String_Name );
#endif
	long nOffset = 1;

	if (m_nViewChsPath)
	{
		nOffset = 0;
		Show_String(pData, nRow, IECCFG_COL_ID_GINCH_PATH, &pGinCh->m_strID, EndEditCell_String_ID );
	}

	Show_DataType_Val(pData, nRow, IECCFG_COL_ID_GINCH_CHTYPE-nOffset, iecfg_GooseChDataType, &pGinCh->m_strDataType, EndEditCell_ChDataType_Gin);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_GINCH_APPCH-nOffset, &pGinCh->m_strAppChIDText, iecfg_GinAppChDataType);

	if (m_bHasDevCh)
	{
		ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_GINCH_APPCH+1-nOffset, &pGinCh->m_strDevChID, iecfg_GoutAppChDataType);
	}

	nRow++;
}


void CIecCfgGinDataChsGrid::EndEditCell_ChDataType_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGoutCh *pInCh = (CIecCfgGoutCh*)pVellData->pObj;
	ASSERT (pInCh != NULL);

	CString strOldType = pInCh->m_strDataType;

	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

	if (strOldType == pInCh->m_strDataType)
	{
		return;
	}

	CIecCfgGinDataChsGrid *pExBaseGrid = (CIecCfgGinDataChsGrid*)pGrid;

	long nOffset = 1;

	if (pExBaseGrid->m_nViewChsPath)
	{
		nOffset = 0;
	}

	if (pExBaseGrid->m_bHasDevCh)
	{
		pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GINCH_APPCH-nOffset);
		pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GINCH_APPCH+1-nOffset);
		pExBaseGrid->ShowCfgCh_AppCh(pInCh, nRow, IECCFG_COL_ID_GINCH_APPCH-nOffset, &pInCh->m_strDefaultValue/*pInCh->m_strAppChID*/, iecfg_GinAppChDataType);//zhouhj  20200619
		pExBaseGrid->ShowCfgCh_AppCh(pInCh, nRow, IECCFG_COL_ID_GINCH_APPCH+1-nOffset, &pInCh->m_strDefaultValue/*pInCh->m_strAppChID*/, iecfg_GoutAppChDataType);//zhouhj  20200619
	} 
	else
	{
		pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GINCH_APPCH-nOffset);
		pExBaseGrid->ShowCfgCh_AppCh(pInCh, nRow, IECCFG_COL_ID_GINCH_APPCH-nOffset, &pInCh->m_strDefaultValue/*pInCh->m_strAppChID*/, iecfg_GinAppChDataType);//zhouhj  20200619
	}
}


void  CIecCfgGinDataChsGrid::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
{
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pData;

	if (pGinCh->m_strDataType == g_strGooseChType_Single || pGinCh->m_strDataType == g_strGooseChType_Double)
	{
		if (strDataType == iecfg_GoutAppChDataType)//如果是开出通道映射,按开出通道映射逻辑走,否则按开入通道映射逻辑走
		{
			Show_DataType_Val(pData, nRow, nCol, g_strGsChDtID_goose_out_ch_single, pstrAppCh, EndEditCell_AppCh);
		} 
		else
		{
			PEXBASECELLDATA pVCellData = CreateExBaseCellData(pstrAppCh, pData, NULL, EndEditCell_AppCh_Gin);
			pVCellData->pExBaseList = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GinAppChDataType);
			Show_DataType_Val(pData, nRow, nCol, *pstrAppCh, pVCellData);
		}

		//Show_DataType_Val(pData, nRow, nCol, iecfg_GinAppChDataType, pstrAppCh, EndEditCell_AppCh_Gin);
		//Show_DWORD_Check(pData, nRow, nCol, &pGinCh->m_dwAppChID,8, TRUE,  EndEditCell_AppCh_Gin);
	}
	else
	{
		*pstrAppCh = _T("---");
		Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
}


void CIecCfgGinDataChsGrid::EndEditCell_AppCh_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGinCh *pInCh = (CIecCfgGinCh*)pVellData->pObj;
	ASSERT (pInCh != NULL);

	//
	CDataType *pDataType = (CDataType*)pVellData->pExBaseList;
	ASSERT (pDataType != NULL);

	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(pCell->dwValue);

	if (pValue == NULL)
	{
		return;
	}

	CIecCfgGinDatas *pIecCfgGinDatas = (CIecCfgGinDatas*)pInCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);

	if (pIecCfgGinDatas != NULL)
	{
		CIecCfgGinAppChMaps* pIecCfgGinAppChMaps = pIecCfgGinDatas->GetIecCfgGinAppChMaps();
		CIecCfgGinAppChMap *pIecCfgGinAppChMap = (CIecCfgGinAppChMap*)pIecCfgGinAppChMaps->FindByID(pValue->m_strID);

		if (pIecCfgGinAppChMap != NULL)
		{
			if (pIecCfgGinAppChMap->m_pIecCfgGinCh != NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("【%s】与【%s】使用相同的开入【%s】.")
					, pIecCfgGinAppChMap->m_pIecCfgGinCh->m_strName,  pInCh->m_strName, pValue->m_strID);
				pValue = (CDataTypeValue*)pDataType->FindByID(pInCh->m_strAppChID);

				if (pValue == NULL)
				{
					pValue = (CDataTypeValue*)pDataType->GetHead();
				}

				pCell->dwValue = pValue->GetIndex();
				pCell->szText = pInCh->m_strAppChIDText;
				return;
			}
		}
	}
	
	//pInCh->AddBinString(pValue->m_strID);
	pInCh->SetBinString(pValue->m_strID);
	pInCh->InitAppIDText();
	pCell->szText = pInCh->m_strAppChIDText;
	pGrid->AutoSizeColumn(nCol);
	pGrid->InvalidateGrid(FALSE);
	CIecCfgGinDataChsGrid *pExBaseGrid = (CIecCfgGinDataChsGrid*)pGrid;

	if (!pExBaseGrid->m_bHasDevCh)//如果表格显示不包含设备通道,则将设备通道映射为AppCh
	{
		long nTmpIndex = pInCh->m_strAppChID.Find(_T(";"));

		if ((nTmpIndex <= 0)||(pInCh->m_strAppChID == _T("none;")))
		{
			pInCh->m_strDevChID = _T("v0");
		}
		else
		{
			pInCh->m_strDevChID = pInCh->m_strAppChID.Left(nTmpIndex);
			pInCh->m_strDevChID.Replace(_T("bin"),_T("bout"));
		}
	}

	CIecCfgGinDatas *pGinDatas = (CIecCfgGinDatas*)pInCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);
	CIecCfgGinAppChMaps *pMaps = pGinDatas->GetIecCfgGinAppChMaps();
	CIecCfgGinAppChMap *pMap =pMaps->Bind(pValue->m_strID, pInCh);

	CWnd *pParentWnd = pGrid->GetParentWnd();
	pParentWnd->SendMessage(WM_GIN_CH_APPID_CHANGED, (WPARAM)pMap, (LPARAM)pMap);

// 	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
// 
// 	if (pInCh->m_strAppChID == g_strAppChID_None)
// 	{
// 		return;
// 	}
// 
// 	CIecCfgDataBase *pGinData = NULL;
// 	CIecCfgDatasBase *pDatas = (CIecCfgDatasBase*)pInCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);
// 	ASSERT (pDatas != NULL);
// 
// 	CExBaseList oListDatas;
// 	pDatas->GetIecCfgDatas(oListDatas);
// 	POS posData = oListDatas.GetHeadPosition();
// 	CIecCfgChsBase *pChs = NULL;
// 	POS posCH = NULL;
// 	CIecCfgGinCh *pCh = NULL;
// 	CString strMsg;
// 	strMsg.Empty();
// 
// 	while (posData != NULL)
// 	{
// 		pGinData = (CIecCfgDataBase *)oListDatas.GetNext(posData);
// 		pChs = pGinData->m_pCfgChs;
// 		posCH = pChs->GetHeadPosition();
// 
// 		while (posCH != NULL)
// 		{
// 			pCh = (CIecCfgGinCh *)pChs->GetNext(posCH);
// 
// 			if (pCh == pInCh)
// 			{
// 				continue;
// 			}
// 
// 			if (pCh->m_strAppChID == pInCh->m_strAppChID)
// 			{
// 				strMsg.AppendFormat(_T("【%s ： %s】"), pGinData->GetCfgDataShortName(), pCh->m_strName);
// 			}
// 		}
// 	}
// 
// 	if (strMsg.GetLength() > 0)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s与当前通道设置相同"), strMsg);
// 	}
// 
// 	oListDatas.RemoveAll();
}

/*
void CIecCfgGinDataChsGrid::EndEditCell_AppCh_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGinCh *pInCh = (CIecCfgGinCh*)pVellData->pObj;
	ASSERT (pInCh != NULL);

	//EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
	iecfg_SetModified(pInCh);

	if (pCell->dwValue == 0)
	{
	}

	if (pCell->dwValue < pInCh->m_dwAppChID)
	{
		pInCh->m_dwAppChID = pCell->dwValue;
		iecfg_GetBinID(pInCh->m_dwAppChID, pInCh->m_strAppChID);
		return;
	}

	long nIndex = iecfg_GetBinChangeIndex(pInCh->m_dwAppChID, pCell->dwValue);

	if (nIndex < 0)
	{
		pCell->dwValue = pInCh->m_dwAppChID;
		CCellID idCell;
		pCell->GetCellID(idCell.row, idCell.col);
		pGrid->RedrawCell(idCell);
		return;
	}

	CString strBin = iecfg_GetBinID(nIndex);
	
	CIecCfgDataBase *pGinData = NULL;
	CIecCfgDatasBase *pDatas = (CIecCfgDatasBase*)pInCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);
	ASSERT (pDatas != NULL);

	CExBaseList oListDatas;
	pDatas->GetIecCfgDatas(oListDatas);
	POS posData = oListDatas.GetHeadPosition();
	CIecCfgChsBase *pChs = NULL;
	POS posCH = NULL;
	CIecCfgGinCh *pCh = NULL;
	CString strMsg;
	strMsg.Empty();

	while (posData != NULL)
	{
		pGinData = (CIecCfgDataBase *)oListDatas.GetNext(posData);
		pChs = pGinData->m_pCfgChs;
		posCH = pChs->GetHeadPosition();

		while (posCH != NULL)
		{
			pCh = (CIecCfgGinCh *)pChs->GetNext(posCH);

			if (pCh == pInCh)
			{
				continue;
			}

			if (pCh->m_strAppChID.Find(strBin) >= 0)
			{
				strMsg.AppendFormat(_T("【%s ： %s】"), pGinData->GetCfgDataShortName(), pCh->m_strName);
			}
		}
	}

	if (strMsg.GetLength() > 0)
	{
		pCell->dwValue = pInCh->m_dwAppChID;
		CCellID idCell;
		pCell->GetCellID(idCell.row, idCell.col);
		pGrid->RedrawCell(idCell);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s与当前通道设置相同"), strMsg);
	}
	else
	{
		iecfg_GetBinID(pCell->dwValue, pInCh->m_strAppChID);
		pInCh->m_dwAppChID = pCell->dwValue;
	}

	oListDatas.RemoveAll();
}
*/
