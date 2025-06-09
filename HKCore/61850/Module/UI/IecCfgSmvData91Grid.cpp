#include "StdAfx.h"
#include "IecCfgSmvData91Grid.h"


//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIecCfgSmvData91Grid::CIecCfgSmvData91Grid()
{

}


CIecCfgSmvData91Grid::~CIecCfgSmvData91Grid(void)
{
	
}

void CIecCfgSmvData91Grid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_91DATA);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgSmvData91Grid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_91DATA]={_T("序号"),_T("选择"),_T("目标MAC"),_T("源MAC"),_T("APPID"), _T("TCI Priority"), _T("TCI VID")
		, _T("输出口选择"), _T("版本号"),  _T("DataSetName"),_T("LDName"), _T("LNName"), _T("状态字"), _T("状态数据集")};

	int iWidth[IECCFG_COLS_91DATA]={60,60, 160,160,90, 100, 80, 80, 80, 80, 80, 80, 80, 80};

	CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_91DATA);
}


void CIecCfgSmvData91Grid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFG91DATA)
	{
		return;
	}

	CIecCfgDataGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg91Data *pIecCfg91Data = (CIecCfg91Data*)pData;

	Show_Mac(pData, nRow, IECCFG_COL_ID_91DATA_DEST_MAC, &pIecCfg91Data->m_strDestAddress);
	Show_Mac(pData, nRow, IECCFG_COL_ID_91DATA_SRC_MAC,  &pIecCfg91Data->m_strSrcAddress);
	Show_Hex(pData, nRow, IECCFG_COL_ID_91DATA_APPID,    &pIecCfg91Data->m_dwAppID, 2);

	nRow++;
}
