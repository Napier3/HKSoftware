#include "StdAfx.h"
#include "IECCfgGoutDataGrid.h"
#include "IECCfgOtherSettingGrid.h"
#include "../../../../../61850/Module/XLanguageResourceIec.h"//20161014

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

#define IECCFG_GOUT_DATA 9

CIECCfgGoutDataGrid::CIECCfgGoutDataGrid(long nUseType)
{
	m_nUseType = nUseType;
}


CIECCfgGoutDataGrid::~CIECCfgGoutDataGrid(void)
{
	
}

void CIECCfgGoutDataGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_GOUT_DATA);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIECCfgGoutDataGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_GOUT_DATA]={
		_T("序号"),
		_T("选择"),
		_T("控制块描述"),
		_T("MAC"),
		_T("测试标记"),
		_T("AT02D光口"), 
		_T("APPID"),
		_T("描述"),
		_T("通道数")};

		int iWidth[IECCFG_GOUT_DATA]={60, 60, 200, 160, 80, 160, 90, 100, 80};
		CIECCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_GOUT_DATA);
}	


void CIECCfgGoutDataGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFGGOUTDATA)
	{
		return;
	}

	CIECCfgDataGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfgGoutData *pIecCfgGOUTData = (CIecCfgGoutData*)pData;

	CString strTmp;
	Show_Check(pData, nRow, 1, &pIecCfgGOUTData->m_nUseFlag);
	Show_StaticString(pData, nRow, 3, &pIecCfgGOUTData->m_strDestAddress);
	Show_DataType_Val(pData, nRow, 4, g_strAppTestSetDataType, &pIecCfgGOUTData->m_bTest, EndEditCell_DTest);
	Show_Fiber(pData, nRow, 5, &pIecCfgGOUTData->m_nFiberIndex, EndEditCell_Fiber_Gout);
	Show_Hex(pData, nRow, 6, &pIecCfgGOUTData->m_dwAppID, 2);
	Show_StaticString(pData, nRow, 7, &pIecCfgGOUTData->m_strIedRefDesc);
	strTmp.Format("%d", pIecCfgGOUTData->m_nChannelNum);
	Show_StaticString(pData, nRow, 8, strTmp);

	nRow++;
}

void CIECCfgGoutDataGrid::EndEditCell_GoutLongTime(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	long nValue =  CString_To_long(pCell->szText);

	if (nValue>500000)
	{
		nValue = 500000;
	}

	if (nValue<1)
	{
		nValue = 1;
	}

	*(pVCellData->pnValue) = nValue;
	pCell->szText.Format(_T("%d"), *(pVCellData->pnValue));
	pGrid->RedrawCell(nRow, nCol);
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void CIECCfgGoutDataGrid::UpdateRefChsGrid(CXGridCtrlBase *pGrid)
{
	if(((CIECCfgGoutDataGrid*)pGrid)->GetRefChsGridClassID() == "CIECCfgOtherSettingGrid")
	{
		CIECCfgOtherSettingGrid* pChs = (CIECCfgOtherSettingGrid*)((CIECCfgGoutDataGrid*)pGrid)->m_pRefChsGrid;
		pChs->UpdateData();
	}
}

void CIECCfgGoutDataGrid::EndEditCell_DTest (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CIECCfgDataGridBase::EndEditCell_Check(nRow, nCol, pCell, pGrid);
	UpdateRefChsGrid(pGrid);
}

void CIECCfgGoutDataGrid::EndEditCell_Fiber_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
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



