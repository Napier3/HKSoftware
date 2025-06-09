#include "StdAfx.h"
#include "IecCfgSmvData6044Grid.h"


//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIecCfgSmvData6044Grid::CIecCfgSmvData6044Grid()
{

}


CIecCfgSmvData6044Grid::~CIecCfgSmvData6044Grid(void)
{
	
}

void CIecCfgSmvData6044Grid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_6044DATA);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgSmvData6044Grid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_6044DATA]={_T("序号"),_T("选择"),_T("LDName"),_T("LNName"),_T("DataSetName"), _T("DelayTime"), _T("TransSpeed")
		, _T("输出口选择"), _T("CheckSum"), _T("Polarity"), _T("StateWord")};
	int iWidth[IECCFG_COLS_6044DATA]={60,60, 160,160,90, 100, 80, 80, 80, 80, 80};

	CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_6044DATA);
}


void CIecCfgSmvData6044Grid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFG6044DATA)
	{
		return;
	}

	CIecCfgDataGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg6044Data *pIecCfg6044Data = (CIecCfg6044Data*)pData;

	Show_Hex(pData, nRow, IECCFG_COL_ID_6044DATA_LDNAME,    &pIecCfg6044Data->m_dwLDName, 4);
	Show_Hex(pData, nRow, IECCFG_COL_ID_6044DATA_LNNAME,    &pIecCfg6044Data->m_dwLNName, 4);
	Show_Hex(pData, nRow, IECCFG_COL_ID_6044DATA_DATASETNAME,    &pIecCfg6044Data->m_dwDataSetName, 4);
	Show_Long(pData, nRow, IECCFG_COL_ID_6044DATA_DELAYTIME,    &pIecCfg6044Data->m_dwDelayTime);

	nRow++;
}
