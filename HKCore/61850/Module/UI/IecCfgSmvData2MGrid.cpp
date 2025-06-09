#include "StdAfx.h"
#include "IecCfgSmvData2MGrid.h"


CIecCfgSmvData2MGrid::CIecCfgSmvData2MGrid()
{

}


CIecCfgSmvData2MGrid::~CIecCfgSmvData2MGrid(void)
{
	
}

void CIecCfgSmvData2MGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_2M);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgSmvData2MGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_2M]={_T("序号"),_T("选择"), _T("输出口选择"), _T("通道个数"),/* _T("IDX值"),*/ _T("地址码值"), _T("报文类别"), _T("IDX值")};
	int iWidth[IECCFG_COLS_2M]={60,60, 100,100,/*100,*/100, 100, 80};

	CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_2M);
}

void CIecCfgSmvData2MGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if ((nClassID != CFGCLASSID_CIECCFG2MDATA)&&(nClassID != CFGCLASSID_CIECCFG2MINDATA))
	{
		return;
	}

	CIecCfgDataGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg6044CommonData *pIecCfg6044Data = (CIecCfg6044CommonData*)pData;

 	Show_Fiber(pData, nRow, IECCFG_COL_ID_6044DATA_COMMON_PORT,    &pIecCfg6044Data->m_nFiberIndex);
	Show_ChNum(pData, nRow, IECCFG_COL_ID_6044DATA_COMMON_CHNUM,  &pIecCfg6044Data->m_nChannelNum);
//	Show_DataType_Val(pData, nRow, 4, iecfg_BlockInx_2M, &pIecCfg6044Data->m_nSmpDataLen);//20220805 zhouhj 在南瑞2M中作为Idx 值范围0~21
	Show_Long(pData, nRow, 4,  &pIecCfg6044Data->m_nSmpCntType);//20220805 zhouhj 地址码值
	Show_DataType_Val(pData, nRow, 5, iecfg_PkgType_2M, &pIecCfg6044Data->m_nBlockType);//20220805 zhouhj  在南瑞2M中作为报文类别 0-数据报文、1-命令报文
	Show_DataType_Val(pData, nRow, 6, iecfg_BlockInx_2M, &pIecCfg6044Data->m_nDelayTime);//20220805 zhouhj 在南瑞2M中作为Idx 值范围0~21
//	Show_Long(pData, nRow, 6,    &pIecCfg6044Data->m_nDelayTime);

	nRow++;
}



