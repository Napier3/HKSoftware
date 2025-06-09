#include "StdAfx.h"
#include "SmvRateGrid.h"
#include "..\..\..\Module\API\MathApi.h"

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CSmvRateGrid::CSmvRateGrid()
{

}


CSmvRateGrid::~CSmvRateGrid(void)
{
	
}

void CSmvRateGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_SMVRATE);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSmvRateGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_SMVRATE]={_T("序号"),_T("名称"),_T("比例因子")};

	int iWidth[IECCFG_COLS_SMVRATE]={60,160,80};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_SMVRATE);
}


void CSmvRateGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFGSMVRATE)
	{
		return;
	}

	Show_Index(pData, nRow, 0);

	CIecCfgSmvRate *pSmvRate = (CIecCfgSmvRate*)pData;

	Show_StaticString(pData, nRow, IECCFG_COL_ID_SMVRATE_NAME, &pSmvRate->m_strName);
	Show_Float(pData, nRow, IECCFG_COL_ID_SMVRATE_RATE, 4,  &pSmvRate->m_fRate, TRUE, EndEditCell_Value_Precision);

	nRow++;
}

void CSmvRateGrid::EndEditCell_Value_Precision(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pString != NULL);
	ASSERT (pVellData->nVt == VCD_FLOAT);

	*(pVellData->pfValue) = math_GetValueFromString(pCell->szText);
	pCell->szText.Format(_T("%.4f"), *(pVellData->pfValue));
	pGrid->RedrawCell(nRow, nCol);
}
