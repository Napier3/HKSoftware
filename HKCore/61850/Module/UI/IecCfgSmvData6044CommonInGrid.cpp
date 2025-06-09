#include "StdAfx.h"
#include "IecCfgSmvData6044CommonInGrid.h"


//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIecCfgSmvData6044CommonInGrid::CIecCfgSmvData6044CommonInGrid()
{

}


CIecCfgSmvData6044CommonInGrid::~CIecCfgSmvData6044CommonInGrid(void)
{
	
}

void CIecCfgSmvData6044CommonInGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_COLS_6044COMMONINDATA);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgSmvData6044CommonInGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_COLS_6044COMMONINDATA]={_T("���"),_T("ѡ��"), _T("�����ѡ��"), _T("ͨ������"), _T("����λ��"), _T("������ʽ"), _T("���ʱ")};
	int iWidth[IECCFG_COLS_6044COMMONINDATA]={60,60, 100,100,90, 100, 80};

	CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_6044COMMONINDATA);
}


void CIecCfgSmvData6044CommonInGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFG6044COMMONINDATA)
	{
		return;
	}

	CIecCfgDataGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg6044CommonData *pIecCfg6044Data = (CIecCfg6044CommonData*)pData;

 	Show_Fiber(pData, nRow, IECCFG_COL_ID_6044DATAIN_COMMON_PORT,    &pIecCfg6044Data->m_nFiberIndex);
	Show_ChNum(pData, nRow, IECCFG_COL_ID_6044DATAIN_COMMON_CHNUM,  &pIecCfg6044Data->m_nChannelNum);
 	Show_SmpByteNum(pData, nRow, IECCFG_COL_ID_6044DATAIN_COMMON_SMPBYTENUM,    &pIecCfg6044Data->m_nSmpDataLen);
	Show_SmpCntType(pData, nRow, IECCFG_COL_ID_6044DATAIN_COMMON_SMPCNTTYPE,    &pIecCfg6044Data->m_nSmpCntType);
	Show_Long(pData, nRow, IECCFG_COL_ID_6044DATAIN_COMMON_DELAYTIME,    &pIecCfg6044Data->m_nDelayTime);

	nRow++;
}

void  CIecCfgSmvData6044CommonInGrid::Show_SmpByteNum(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnSmpDataLen, GRID_CELL_EDIT_FUNC pFunc)
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	CString strDataType = g_strAppPortDataType_SmpByteNum;
	Show_DataType_Val(pData, nRow, nCol, strDataType, pnSmpDataLen, pFunc);

// 	if (pFunc != NULL)
// 	{
// 		Show_DataType_Val(pData, nRow, nCol, strDataType, pnSmpDataLen, pFunc);
// 	}
// 	else
// 	{
// 		Show_DataType_Val(pData, nRow, nCol, strDataType, pnSmpDataLen, EndEditCell_Fiber);
// 	}
}

void  CIecCfgSmvData6044CommonInGrid::Show_SmpCntType(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnSmpCntType, GRID_CELL_EDIT_FUNC pFunc)
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	CString strDataType = g_strAppPortDataType_SmpCntType;
	Show_DataType_Val(pData, nRow, nCol, strDataType, pnSmpCntType, pFunc);

// 	if (pFunc != NULL)
// 	{
// 	}
// 	else
// 	{
// 		Show_DataType_Val(pData, nRow, nCol, strDataType, pnSmpCntType, EndEditCell_Fiber);
// 	}
}

