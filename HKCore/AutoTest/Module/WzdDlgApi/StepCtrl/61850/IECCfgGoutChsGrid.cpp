#include "StdAfx.h"
#include "IECCfgGoutChsGrid.h"

#include "../../../../../61850/Module/XLanguageResourceIec.h"


//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

#define IECCFG_GOUT_CH 4

CIECCfgGoutDataChsGrid::CIECCfgGoutDataChsGrid()
{

}


CIECCfgGoutDataChsGrid::~CIECCfgGoutDataChsGrid(void)
{
	
}

void CIECCfgGoutDataChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_GOUT_CH);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIECCfgGoutDataChsGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_GOUT_CH]={
		_T("通道"),
		_T("描述"),
		_T("通道类型"),
		_T("开出量映射")
	};
	int iWidth[IECCFG_GOUT_CH]={60,160, 160,80};

	CIECCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_GOUT_CH);
}

void CIECCfgGoutDataChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
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
				return;
		}
	}

	CIECCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

	Show_String(pData, nRow, IECCFG_COL_ID_GOUTCH_DESC, &pGoutCh->m_strName, EndEditCell_String_NameAndID );
	Show_DataType_Val(pData, nRow, IECCFG_COL_ID_GOUTCH_CHTYPE, iecfg_GooseChDataType, &pGoutCh->m_strDataType, EndEditCell_ChDataType_Gout);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_GOUTCH_APPCH, &pGoutCh->m_strAppChID, iecfg_GoutAppChDataType);

	nRow++;
}

void  CIECCfgGoutDataChsGrid::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
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
		*pstrAppCh = _T("UTCTime");
		CIECCfgDataChsGridBase::Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Float)		//_T("float")
	{
		*pstrAppCh = _T("0.0");
		CIECCfgDataChsGridBase::Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
	else if (pGoutCh->m_strDataType == g_strGooseChType_Struct)		//_T("struct")
	{
		*pstrAppCh = _T("1000000000000");
		CIECCfgDataChsGridBase::Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
	else
	{
		*pstrAppCh = _T("---");
		CIECCfgDataChsGridBase::Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
}

void CIECCfgGoutDataChsGrid::EndEditCell_ChDataType_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
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

	CIECCfgGoutDataChsGrid *pExBaseGrid = (CIECCfgGoutDataChsGrid*)pGrid;

	pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GOUTCH_APPCH);
	pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GOUTCH_VALUE);
	pExBaseGrid->ShowCfgCh_AppCh(pGoutCh, nRow, IECCFG_COL_ID_GOUTCH_APPCH, &pGoutCh->m_strAppChID, iecfg_GoutAppChDataType);
	pExBaseGrid->ShowCfgCh_DefValue(pGoutCh, nRow, IECCFG_COL_ID_GOUTCH_VALUE, &pGoutCh->m_strDefaultValue);
}

void CIECCfgGoutDataChsGrid::ShowCfgCh_DefValue(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue)
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
	else
	{
		CIECCfgDataChsGridBase::Show_String(pData, nRow, nCol, pstrValue,EndEditCell_AppCh_GoutDefaultValue);
	}
}

void CIECCfgGoutDataChsGrid::EndEditCell_AppCh_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
	CIECCfgGoutDataChsGrid *pExBaseGrid = (CIECCfgGoutDataChsGrid*)pGrid;

	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)pVellData->pObj;
	ASSERT (pGoutCh != NULL);
	pGoutCh->m_strDevChID = pGoutCh->m_strAppChID;
	pGoutCh->m_strDevChID.Replace(_T("bout"),_T("bin"));//zhouhj 20200105 对于界面没有开入映射的,将开入与开出映射保持一致
}

void CIECCfgGoutDataChsGrid::EndEditCell_AppCh_GoutDefaultValue (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
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