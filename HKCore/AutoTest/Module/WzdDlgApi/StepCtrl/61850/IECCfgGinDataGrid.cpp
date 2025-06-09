#include "StdAfx.h"
#include "IECCfgGinDataGrid.h"
#include "../../../../../61850/Module/XLanguageResourceIec.h"//20161014
#include "IECCfgOtherSettingGrid.h"

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

#define IECCFG_GIN_DATA 6

CIECCfgGinDataGrid::CIECCfgGinDataGrid(long nUseType)
{
	m_nUseType = nUseType;
}


CIECCfgGinDataGrid::~CIECCfgGinDataGrid(void)
{
	
}

void CIECCfgGinDataGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_GIN_DATA);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIECCfgGinDataGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_GIN_DATA]={
		_T("序号"),
		_T("选择"),
		_T("控制块描述"),
		_T("测试标记"),
		_T("输入光口"), 
		_T("APPID")
		};

	int iWidth[IECCFG_GIN_DATA]={60, 60, 200, 80, 90, 80};
	CIECCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_GIN_DATA);
}


void CIECCfgGinDataGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFGGINDATA)
	{
		return;
	}

	CIECCfgDataGridBase::ShowData(pData, nRow, bInsertRow);
	CIecCfgGinData *pIecCfgGinData = (CIecCfgGinData*)pData;

	CString strTmp;
	Show_Check(pData, nRow, 1, &pIecCfgGinData->m_nUseFlag);
	Show_StaticString(pData, nRow, 2, &pIecCfgGinData->m_strIedRefDesc);
	Show_DataType_Val(pData, nRow, 3, g_strAppTestSetDataType, &pIecCfgGinData->m_bTest, EndEditCell_DTest);
	Show_Fiber(pData, nRow, 4, &pIecCfgGinData->m_nFiberIndex, EndEditCell_Fiber_Gin);
	strTmp.Format(_T("0X%04X"),pIecCfgGinData->m_dwAppID);
	Show_StaticString(pData, nRow, 5, strTmp);

	nRow++;
}

void CIECCfgGinDataGrid::UpdateRefChsGrid(CXGridCtrlBase *pGrid)
{
	if(((CIECCfgGinDataGrid*)pGrid)->GetRefChsGridClassID() == "CIECCfgOtherSettingGrid")
	{
		CIECCfgOtherSettingGrid* pChs = (CIECCfgOtherSettingGrid*)((CIECCfgGinDataGrid*)pGrid)->m_pRefChsGrid;
		pChs->UpdateData();
	}
}

void CIECCfgGinDataGrid::EndEditCell_DTest (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CIECCfgDataGridBase::EndEditCell_Check(nRow, nCol, pCell, pGrid);
	UpdateRefChsGrid(pGrid);
}

void CIECCfgGinDataGrid::EndEditCell_Fiber_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIECCfgDataGridBase *pIecCfgDataGrid = (CIECCfgDataGridBase*)pGrid;

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;
	CIecCfgDatasBase *pIecCfgDatas = (CIecCfgDatasBase*)pIecCfgData->GetParent();
	long nFiberIndex = pIecCfgData->m_nFiberIndex;
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
	CExBaseList oListUseDatas;

	if (nFiberIndex == pIecCfgData->m_nFiberIndex)
	{
		return;
	}

	pIecCfgDatas->GetUseDatas(oListUseDatas);

	if (pIecCfgData->ValidateFiberIndex())
	{
		oListUseDatas.RemoveAll();
	}
	else
	{
		pIecCfgData->m_nFiberIndex = nFiberIndex;
		pIecCfgDataGrid->FreeExBaseCellData(nRow, nCol);
		pIecCfgDataGrid->Show_Fiber(pIecCfgData, nRow, nCol, &pIecCfgData->m_nFiberIndex);

		oListUseDatas.RemoveAll();
	}

	UpdateRefChsGrid(pGrid);
}