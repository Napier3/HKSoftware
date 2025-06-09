#include "StdAfx.h"
#include "IecCfgGoutDataChsGrid.h"

#include "..\XLanguageResourceIec.h"


//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase


CIecCfgGoutDataChsGrid::CIecCfgGoutDataChsGrid(BOOL bHasDevCh)
{
	m_bHasDevCh = bHasDevCh;
}


CIecCfgGoutDataChsGrid::~CIecCfgGoutDataChsGrid(void)
{
	
}

void CIecCfgGoutDataChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	long nCols = IECCFG_COLS_GOUTCH;

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

void CIecCfgGoutDataChsGrid::InitGridTitle()
{
	if (m_bHasDevCh)
	{
		if (m_nViewChsPath)
		{
			CString cTempStr[IECCFG_COLS_GOUTCH+1]={
				//_T("通道"),_T("名称"),_T("通道类型"),_T("测试仪通道"),_T("初始值"),_T("输入端-名称"), _T("输入端-路径")
				_T("通道")/*g_sLangTxt_Channel*/
				,g_sLangTxt_Name
				,g_sLtxt_ChannelType
				,_T("开出映射")/*g_sLtxt_TestDeviceChannel*/,
				_T("开入映射"),
				g_sLtxt_InitialValue
				,g_sLtxt_InputName
				,g_sLtxt_InputPath
			};
			int iWidth[IECCFG_COLS_GOUTCH+1]={60,160, 80,90,90,90, 90, 90};

			CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GOUTCH+1);
		} 
		else
		{
			CString cTempStr[IECCFG_COLS_GOUTCH]={
				//_T("通道"),_T("名称"),_T("通道类型"),_T("测试仪通道"),_T("初始值"),_T("输入端-名称"), _T("输入端-路径")
				_T("通道")/*g_sLangTxt_Channel*/
				,g_sLangTxt_Name
				,g_sLtxt_ChannelType
				,_T("开出映射")/*g_sLtxt_TestDeviceChannel*/,
				_T("开入映射"),
				g_sLtxt_InitialValue
				,g_sLtxt_InputName
			};
			int iWidth[IECCFG_COLS_GOUTCH]={60,160, 80,90,90,90, 90};

			CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GOUTCH);
		}
	} 
	else
	{
		if (m_nViewChsPath)
		{
			CString cTempStr[IECCFG_COLS_GOUTCH]={
				//_T("通道"),_T("名称"),_T("通道类型"),_T("测试仪通道"),_T("初始值"),_T("输入端-名称"), _T("输入端-路径")
				_T("通道")/*g_sLangTxt_Channel*/
				,g_sLangTxt_Name
				,g_sLtxt_ChannelType
				,g_sLtxt_TestDeviceChannel,
				g_sLtxt_InitialValue
				,g_sLtxt_InputName
				,g_sLtxt_InputPath
			};
			int iWidth[IECCFG_COLS_GOUTCH]={60,160, 80,90,90, 90, 90};

			CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GOUTCH);
		} 
		else
		{
			CString cTempStr[IECCFG_COLS_GOUTCH-1]={
				//_T("通道"),_T("名称"),_T("通道类型"),_T("测试仪通道"),_T("初始值"),_T("输入端-名称"), _T("输入端-路径")
				_T("通道")/*g_sLangTxt_Channel*/
				,g_sLangTxt_Name
				,g_sLtxt_ChannelType
				,g_sLtxt_TestDeviceChannel,
				g_sLtxt_InitialValue
				,g_sLtxt_InputName
			};
			int iWidth[IECCFG_COLS_GOUTCH-1]={60,160, 80,90,90, 90};

			CIecCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GOUTCH-1);
		}
	}
}

void CIecCfgGoutDataChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFGGOUTCH);

	if (nClassID != CFGCLASSID_CIECCFGGOUTCH)
	{
		return;
	}

	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pData;

	if (CCfgDataMngrConstGlobal::IsViewOnlyUsedInChs())
	{
		if (pGoutCh->m_nIndexExternal == -1)
		{
			//if (pGoutCh->m_strAddrExternal.GetLength() == 0)
			{
				return;
			}
		}
	}

	CIecCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

#ifdef USE_IECFG_ChsGrid_Desc_Not_Editable
	Show_StaticString(pData, nRow, IECCFG_COL_ID_GOUTCH_DESC, &pGoutCh->m_strName );
#else
	Show_String(pData, nRow, IECCFG_COL_ID_GOUTCH_DESC, &pGoutCh->m_strName, EndEditCell_String_NameAndID );
#endif
	Show_DataType_Val(pData, nRow, IECCFG_COL_ID_GOUTCH_CHTYPE, iecfg_GooseChDataType, &pGoutCh->m_strDataType, EndEditCell_ChDataType_Gout);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_GOUTCH_APPCH, &pGoutCh->m_strAppChID, iecfg_GoutAppChDataType);
	long nOffSet = 0;

	if (m_bHasDevCh)
	{
		nOffSet = 1;
		ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_GOUTCH_APPCH+nOffSet, &pGoutCh->m_strDevChID, iecfg_GinAppChDataType);
	}

	ShowCfgCh_DefValue(pData, nRow, IECCFG_COL_ID_GOUTCH_VALUE+nOffSet, &pGoutCh->m_strDefaultValue);
	//根据m_strDataType来显示
	//Show_Hex(pData, nRow, IECCFG_COL_ID_GOUTCH_VALUE, &pGOUTCh->m_dwDefaultValue, 4);
	Show_StaticString(pData, nRow, IECCFG_COL_ID_GOUTCH_DESCEXTERNAL+nOffSet, &pGoutCh->m_strDescExternal);

	if (m_nViewChsPath)
	{
		Show_StaticString(pData, nRow, IECCFG_COL_ID_GOUTCH_ADDREXTERNAL+nOffSet, &pGoutCh->m_strAddrExternal);
	}

	//编号改变
	if (CCfgDataMngrConstGlobal::IsViewOnlyUsedInChs())
	{
		if (pGoutCh->m_nIndexExternal != 65535)
		{
			CString strIndex;
			long nIndex=m_pDatas->FindIndex(pData);
			strIndex.Format(_T("%d / %d"), pGoutCh->m_nIndexExternal+1, nIndex+1);
			SetItemText(nRow, 0, strIndex);
		}
	}

	nRow++;
}

void  CIecCfgGoutDataChsGrid::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
{
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pData;
	
	if (pGoutCh->m_strDataType == g_strGooseChType_Single)
	{
		if (strDataType == iecfg_GinAppChDataType)//zhouhj 20200106 因为增加了开入通道映射,如果为开入映射按正常逻辑走,如果是开出通道映射,用EndEditCell_AppCh_Gout函数指针
		{
			Show_DataType_Val(pData, nRow, nCol, iecfg_GinAppChDataType, pstrAppCh, EndEditCell_AppCh);
		}
		else
		{
			Show_DataType_Val(pData, nRow, nCol, g_strGsChDtID_goose_out_ch_single, pstrAppCh, EndEditCell_AppCh_Gout);
		}
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Double)
	{
		if (strDataType == iecfg_GinAppChDataType)
		{
			Show_DataType_Val(pData, nRow, nCol, iecfg_GinAppChDataType, pstrAppCh, EndEditCell_AppCh);
		}
		else
		{
			Show_DataType_Val(pData, nRow, nCol, g_strGsChDtID_goose_out_ch_double, pstrAppCh, EndEditCell_AppCh_Gout);
		}
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Time)		//_T("UTCTime")
	{
// 		Show_DataType_Val(pData, nRow, nCol, g_strGsChDtID_goose_out_ch_double, pstrAppCh, EndEditCell_AppCh);
		*pstrAppCh = _T("UTCTime");
		CIecCfgDataChsGridBase::Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Float)		//_T("float")
	{
		*pstrAppCh = _T("0.0");
		CIecCfgDataChsGridBase::Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Struct)		//_T("struct")
	{
		*pstrAppCh = _T("1000000000000");
		CIecCfgDataChsGridBase::Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
	else
	{
		*pstrAppCh = _T("---");
		CIecCfgDataChsGridBase::Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
}

void CIecCfgGoutDataChsGrid::EndEditCell_ChDataType_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVellData->pObj;
	ASSERT (pGoutCh != NULL);

	CString strOldType = pGoutCh->m_strDataType;

	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

	if (strOldType == pGoutCh->m_strDataType)
	{
		return;
	}

	CIecCfgGoutDataChsGrid *pExBaseGrid = (CIecCfgGoutDataChsGrid*)pGrid;

	if (pExBaseGrid->m_bHasDevCh)
	{
		pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GOUTCH_APPCH);
		pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GOUTCH_APPCH+1);
		pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GOUTCH_VALUE+1);
		pExBaseGrid->ShowCfgCh_AppCh(pGoutCh, nRow, IECCFG_COL_ID_GOUTCH_APPCH, &pGoutCh->m_strAppChID, iecfg_GoutAppChDataType);
		pExBaseGrid->ShowCfgCh_AppCh(pGoutCh, nRow, IECCFG_COL_ID_GOUTCH_APPCH+1, &pGoutCh->m_strDevChID, iecfg_GinAppChDataType);
		pExBaseGrid->ShowCfgCh_DefValue(pGoutCh, nRow, IECCFG_COL_ID_GOUTCH_VALUE+1, &pGoutCh->m_strDefaultValue);
	} 
	else
	{
		pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GOUTCH_APPCH);
		pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GOUTCH_VALUE);
		pExBaseGrid->ShowCfgCh_AppCh(pGoutCh, nRow, IECCFG_COL_ID_GOUTCH_APPCH, &pGoutCh->m_strAppChID, iecfg_GoutAppChDataType);
		pExBaseGrid->ShowCfgCh_DefValue(pGoutCh, nRow, IECCFG_COL_ID_GOUTCH_VALUE, &pGoutCh->m_strDefaultValue);
	}
}

void CIecCfgGoutDataChsGrid::ShowCfgCh_DefValue(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue)
{
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pData;
	pGoutCh->CheckDefautValue();

	if (pGoutCh->m_strDataType == g_strGooseChType_Single)
	{
		Show_DataType_Val(pData, nRow, nCol, g_strGsChDtID_goose_out_ch_single_def_value, pstrValue/*,EndEditCell_AppCh_GoutDefaultValueSingle*/);
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Double)
	{
		Show_DataType_Val(pData, nRow, nCol, g_strGsChDtID_goose_out_ch_double_def_value, pstrValue/*,EndEditCell_AppCh_GoutDefaultValueDbpos*/);
	}
//  	else if (pGoutCh->m_strDataType == g_strGooseChType_Quality)
//  	{
// 		Show_HexString(pData, nRow, nCol,    pstrValue, 4);
//  //		CIecCfgDataChsGridBase::Show_String(pData, nRow, nCol, pstrValue);
//  	}
//  	else if (pGoutCh->m_strDataType == g_strGooseChType_Float)
//  	{
//  		CIecCfgDataChsGridBase::Show_String(pData, nRow, nCol, pstrValue);
//  	}
//  	else if (pGoutCh->m_strDataType == g_strGooseChType_String)
//  	{
//  		CIecCfgDataChsGridBase::Show_String(pData, nRow, nCol, pstrValue);
//  	}
//  	else if (pGoutCh->m_strDataType == g_strGooseChType_Integer)
//  	{
//  		CIecCfgDataChsGridBase::Show_String(pData, nRow, nCol, pstrValue);
//  	}
//  	else if (pGoutCh->m_strDataType == g_strGooseChType_UInteger)
//  	{
//  		CIecCfgDataChsGridBase::Show_String(pData, nRow, nCol, pstrValue);
//  	}
	else
	{
//		*pstrValue = _T("");  //zhouhj 20210912  在非单点、双点的情况下,可以人员设置初始值
		CIecCfgDataChsGridBase::Show_String(pData, nRow, nCol, pstrValue,EndEditCell_AppCh_GoutDefaultValue);
	}
}

void CIecCfgGoutDataChsGrid::EndEditCell_AppCh_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
	CIecCfgGoutDataChsGrid *pExBaseGrid = (CIecCfgGoutDataChsGrid*)pGrid;

	if (!pExBaseGrid->m_bHasDevCh)
	{
		PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
		ASSERT (pVellData != NULL);
		CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVellData->pObj;
		ASSERT (pGoutCh != NULL);
		pGoutCh->m_strDevChID = pGoutCh->m_strAppChID;
		pGoutCh->m_strDevChID.Replace(_T("bout"),_T("bin"));//zhouhj 20200105 对于界面没有开入映射的,将开入与开出映射保持一致
	}
}

void CIecCfgGoutDataChsGrid::EndEditCell_AppCh_GoutDefaultValue (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVellData->pObj;
	ASSERT (pGoutCh != NULL);
	pGoutCh->m_strDefaultValue = pCell->szText;
	pGoutCh->CheckDefautValue();

	if (pCell->szText != pGoutCh->m_strDefaultValue)
	{
		pCell->szText = pGoutCh->m_strDefaultValue;
	}
}

// void CIecCfgGoutDataChsGrid::EndEditCell_AppCh_GoutDefaultValueSingle (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
// {
// 	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
// 	ASSERT (pVellData != NULL);
// 	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVellData->pObj;
// 	ASSERT (pGoutCh != NULL);
// 	pGoutCh->m_strDefaultValue = pCell->szText;
// 
// 	if (pGoutCh->m_strAppChID.Find("bout") == -1)
// 	{
// 		if (pGoutCh->m_strDefaultValue == _T("FALSE"))
// 		{
// 			pGoutCh->m_strAppChID = _T("v0");
// 		} 
// 		else if (pGoutCh->m_strDefaultValue == _T("TRUE"))
// 		{
// 			pGoutCh->m_strAppChID = _T("v1");
// 		}
// 	}
// }
// 
// void CIecCfgGoutDataChsGrid::EndEditCell_AppCh_GoutDefaultValueDbpos (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
// {
// 	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
// 	ASSERT (pVellData != NULL);
// 	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVellData->pObj;
// 	ASSERT (pGoutCh != NULL);
// 	pGoutCh->m_strDefaultValue = pCell->szText;
// 
// 	if (pGoutCh->m_strAppChID.Find(_T("bout")) == -1)
// 	{
// 		if (pGoutCh->m_strDefaultValue == _T("[00]"))
// 		{
// 			pGoutCh->m_strAppChID = _T("v00");
// 		} 
// 		else if (pGoutCh->m_strDefaultValue == _T("[01]"))
// 		{
// 			pGoutCh->m_strAppChID = _T("v01");
// 		}
// 		else if (pGoutCh->m_strDefaultValue == _T("[10]"))
// 		{
// 			pGoutCh->m_strAppChID = _T("v10");
// 		}
// 		else if (pGoutCh->m_strDefaultValue == _T("[11]"))
// 		{
// 			pGoutCh->m_strAppChID = _T("v11");
// 		}
// 	}
// }
