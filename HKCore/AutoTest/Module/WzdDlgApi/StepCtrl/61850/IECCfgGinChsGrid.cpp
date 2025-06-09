#include "StdAfx.h"
#include "IECCfgGinChsGrid.h"
#include "../../../../../61850/Module/XLanguageResourceIec.h"

//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

#define IECCFG_GIN_CH 4

CIECCfgGinChsGrid::CIECCfgGinChsGrid()
{

}


CIECCfgGinChsGrid::~CIECCfgGinChsGrid(void)
{
	
}

void CIECCfgGinChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_GIN_CH);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIECCfgGinChsGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_GIN_CH]={
		_T("通道"),
		_T("描述"),
		_T("通道类型"),
		_T("开入量映射")
	};
	int iWidth[IECCFG_GIN_CH]={60,160, 160,80};

	CIECCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_GIN_CH);
}


void CIECCfgGinChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFGGINCH);

	if (nClassID != CFGCLASSID_CIECCFGGINCH)
	{
		return;
	}

	CIECCfgDataChsGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)pData;
	pGinCh->InitAppIDText();

	Show_String(pData, nRow, IECCFG_COL_ID_GINCH_DESC, &pGinCh->m_strName, EndEditCell_String_Name );
	Show_DataType_Val(pData, nRow, IECCFG_COL_ID_GINCH_CHTYPE, iecfg_GooseChDataType, &pGinCh->m_strDataType, EndEditCell_ChDataType_Gin);
	ShowCfgCh_AppCh(pData, nRow, IECCFG_COL_ID_GINCH_APPCH, &pGinCh->m_strAppChIDText, iecfg_GinAppChDataType);

	nRow++;
}


void CIECCfgGinChsGrid::EndEditCell_ChDataType_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
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

	CIECCfgGinChsGrid *pExBaseGrid = (CIECCfgGinChsGrid*)pGrid;
	pExBaseGrid->FreeExBaseCellData(nRow, IECCFG_COL_ID_GINCH_APPCH);
	pExBaseGrid->ShowCfgCh_AppCh(pInCh, nRow, IECCFG_COL_ID_GINCH_APPCH, &pInCh->m_strDefaultValue, iecfg_GinAppChDataType);
}


void  CIECCfgGinChsGrid::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
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
	}
	else
	{
		*pstrAppCh = _T("---");
		Show_StaticString(pData, nRow, nCol, pstrAppCh);
	}
}


void CIECCfgGinChsGrid::EndEditCell_AppCh_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgGinCh *pInCh = (CIecCfgGinCh*)pVellData->pObj;
	ASSERT (pInCh != NULL);

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

	pInCh->SetBinString(pValue->m_strID);
	pInCh->InitAppIDText();
	pCell->szText = pInCh->m_strAppChIDText;
	pGrid->AutoSizeColumn(nCol);
	pGrid->InvalidateGrid(FALSE);
	CIECCfgGinChsGrid *pExBaseGrid = (CIECCfgGinChsGrid*)pGrid;

	long nTmpIndex = pInCh->m_strAppChID.Find(_T(";"));
	if ((nTmpIndex <= 0)||(pInCh->m_strAppChID == _T("none;")))
	{
		pInCh->m_strAppChID.Replace(_T("none;"), _T("none"));
		pInCh->m_strDevChID = _T("v0");
	}
	else
	{
		pInCh->m_strDevChID = pInCh->m_strAppChID.Left(nTmpIndex);
		pInCh->m_strDevChID.Replace(_T("bin"),_T("bout"));
	}

	CIecCfgGinDatas *pGinDatas = (CIecCfgGinDatas*)pInCh->GetAncestor(CFGCLASSID_CIECCFGDATASGIN);
	CIecCfgGinAppChMaps *pMaps = pGinDatas->GetIecCfgGinAppChMaps();
	CIecCfgGinAppChMap *pMap =pMaps->Bind(pValue->m_strID, pInCh);

	CWnd *pParentWnd = pGrid->GetParentWnd();
	pParentWnd->SendMessage(WM_GIN_CH_APPID_CHANGED, (WPARAM)pMap, (LPARAM)pMap);
}