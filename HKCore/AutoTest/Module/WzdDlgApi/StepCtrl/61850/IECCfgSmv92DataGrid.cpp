#include "StdAfx.h"
#include "IECCfgSmv92DataGrid.h"
#include "IECCfgOtherSettingGrid.h"
#include "../../../../../61850/Module/XLanguageResourceIec.h"

#define IECFG_COL_WIDTH_INDEX   40
#define IECFG_COL_WIDTH_SELECT  40
#define IECFG_COL_WIDTH_MAC     110
#define IECFG_COL_WIDTH_HEX2    80
#define IECFG_COL_WIDTH_HEX4    100
#define IECFG_COL_WIDTH_HEX8    100

#define IECCFG_DATA_COLS	8

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIECCfgSmv92DataGrid::CIECCfgSmv92DataGrid(long nUseType)
{
	m_nUseType = nUseType;
}


CIECCfgSmv92DataGrid::~CIECCfgSmv92DataGrid(void)
{
	
}

void CIECCfgSmv92DataGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_DATA_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIECCfgSmv92DataGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_DATA_COLS]={
		_T("序号"),
		_T("选择"),
		_T("控制块描述"),
		_T("控制块所在IED"),
		_T("输出光口"),
		_T("采样延时"),
		_T("APPID"),
		_T("通道数")};

	int iWidth[IECCFG_DATA_COLS]={
		IECFG_COL_WIDTH_INDEX,
		IECFG_COL_WIDTH_SELECT,
		IECFG_COL_WIDTH_MAC,
		IECFG_COL_WIDTH_MAC,
		IECFG_COL_WIDTH_HEX2,
		IECFG_COL_WIDTH_MAC,
		IECFG_COL_WIDTH_HEX2,
		80};

	CIECCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_DATA_COLS);
}

void CIECCfgSmv92DataGrid::UpdateRefChsGrid(CXGridCtrlBase *pGrid)
{
	if(((CIECCfgSmv92DataGrid*)pGrid)->GetRefChsGridClassID() == "CIECCfgOtherSettingGrid")
	{
		CIECCfgOtherSettingGrid* pChs = (CIECCfgOtherSettingGrid*)((CIECCfgSmv92DataGrid*)pGrid)->m_pRefChsGrid;
		pChs->UpdateData();
	}
}

void CIECCfgSmv92DataGrid::EndEditCell_Delay(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CIECCfgDataGridBase::EndEditCell_Delay(nRow, nCol, pCell, pGrid);
	UpdateRefChsGrid(pGrid);
}

void CIECCfgSmv92DataGrid::EndEditCell_Fiber(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CIECCfgDataGridBase::EndEditCell_Fiber(nRow, nCol, pCell, pGrid);
	UpdateRefChsGrid(pGrid);
}

void CIECCfgSmv92DataGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFG92DATA)
	{
		return;
	}

	CIECCfgDataGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data*)pData;

	Show_Check(pData, nRow, 1, &pIecCfg92Data->m_nUseFlag);
	Show_StaticString(pData, nRow, 2, &pIecCfg92Data->m_pSclRef->m_strName);
	Show_StaticString(pData, nRow, 3, &pIecCfg92Data->m_strIedRefDesc);
	Show_Fiber(pData, nRow, 4, &pIecCfg92Data->m_nFiberIndex, EndEditCell_Fiber);
	Show_Long(pData, nRow, 5,    &pIecCfg92Data->m_nDelay,TRUE,_T(""), EndEditCell_Delay);
	CString strTmp;
	strTmp.Format(_T("0X%04X"),pIecCfg92Data->m_dwAppID);
	Show_StaticString(pData, nRow, 6, strTmp);
	CString strText;
	strText.Format("%d", pIecCfg92Data->m_nChannelNum);
	Show_StaticString(pData, nRow, 7, &strText);

	nRow++;
}
