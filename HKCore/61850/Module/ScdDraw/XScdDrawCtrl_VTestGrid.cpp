//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl__VTestGridChs.cpp  CXScdDrawCtrl__VTestGridChs


#include "stdafx.h"
#include "XScdDrawCtrl_VTestGrid.h"


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VTestGridTitleBase
CXScdDrawCtrl_VTestGridTitleBase::CXScdDrawCtrl_VTestGridTitleBase()
{
	m_nAdjustBeginCol = -1;
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_VTestGridTitleBase::~CXScdDrawCtrl_VTestGridTitleBase()
{
}


void CXScdDrawCtrl_VTestGridTitleBase::InitGrid()
{
	SetListMode(FALSE);
	SetRowCount(1);
	SetColumnCount(4);
	SetFixedRowCount(0);
	SetFixedColumnCount(0);
	InitGridTitle();
}

void CXScdDrawCtrl_VTestGridTitleBase::InitGridTitle()
{
	SetColumnWidth(0, 20);
	SetColumnWidth(1, 40);
	SetColumnWidth(2, 60);
	SetColumnWidth(3, 80);
}

void CXScdDrawCtrl_VTestGridTitleBase::ShowDatas(CExBaseList *pDatas)
{
	ClearSelect();
	CTLinkList <_ExBaseCellData> listVCellData;
	BackListCellData(listVCellData);
	m_pCurrData = NULL;
	m_pDatas = pDatas;
	SetRowCount(1);

	if (pDatas == NULL)
	{
		return;
	}

	ShowTitle(pDatas);
	SetRowHeight(0, EXBASEGRID_ROWHEIGHT);
	ResetScrollBars();
	InvalidateGrid(FALSE);
}

void CXScdDrawCtrl_VTestGridTitleBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

}


CDataType* CXScdDrawCtrl_VTestGridTitleBase::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}


//////////////////////////////////////////////////////////////////////////
//CXScdDrawCtrl_VTestGridChsBase
CXScdDrawCtrl_VTestGridChsBase::CXScdDrawCtrl_VTestGridChsBase()
{
	m_nAdjustBeginCol = 0;
	//初始化属性

	//初始化成员变量
}

CXScdDrawCtrl_VTestGridChsBase::~CXScdDrawCtrl_VTestGridChsBase()
{

}


void CXScdDrawCtrl_VTestGridChsBase::InitGrid()
{
	SetListMode(FALSE);
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(0);
	SetFixedColumnCount(0);
	InitGridTitle();
}

void CXScdDrawCtrl_VTestGridChsBase::InitGridTitle()
{

}


void CXScdDrawCtrl_VTestGridChsBase::ShowDatas(CExBaseList *pDatas)
{
	ClearSelect();
	CTLinkList <_ExBaseCellData> listVCellData;
	BackListCellData(listVCellData);
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(1);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 0;
	long nCalRows = pDatas->GetCount();
	SetRowCount(nCalRows);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex);

	for (nRowIndex=1; nRowIndex<m_nRows; nRowIndex++)
	{
		SetRowHeight(nRowIndex, EXBASEGRID_ROWHEIGHT);
	}

	AdjustAllCols();
	ResetScrollBars();
	InvalidateGrid(FALSE);
}

void CXScdDrawCtrl_VTestGridChsBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	
}

void  CXScdDrawCtrl_VTestGridChsBase::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
{
	CIecCfgDataSmvChBase *pSmvCh = (CIecCfgDataSmvChBase*)pData;

	if (iecfg_IsCurrSmvChType(pSmvCh->m_strChType))
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_I, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_IsVolSmvChType(pSmvCh->m_strChType))
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_U, pstrAppCh, EndEditCell_AppCh);
	}
	else if (iecfg_IsUTCTimeSmvChType(pSmvCh->m_strChType))
	{
		// 		Show_String(pData, nRow, nCol, pstrAppCh);
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_T, pstrAppCh, EndEditCell_AppCh);
	}
	else
	{
		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_U, pstrAppCh, EndEditCell_AppCh);
	}
}


void CXScdDrawCtrl_VTestGridChsBase::EndEditCell_AppCh (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
}


CDataType* CXScdDrawCtrl_VTestGridChsBase::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}
// 
// void  CXScdDrawCtrl_VTestGridChsBase::Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc)
// {
// 	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
// 	CString strDataType = GetAppPortDataType();
// 
// 	if (pFunc != NULL)
// 	{
// 		Show_DataType_Val(pData, nRow, nCol, strDataType, pnFiber, pFunc);
// 	}
// 	else
// 	{
// 		Show_DataType_Val(pData, nRow, nCol, strDataType, pnFiber, EndEditCell_Fiber);
// 	}
// }
// 
// void CXScdDrawCtrl_VTestGridChsBase::EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
// {
// 	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
// 	ASSERT (pVellData != NULL);
// 	CIecCfgDataGridBase *pIecCfgDataGrid = (CIecCfgDataGridBase*)pGrid;
// 
// 	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;
// 	long nFiberIndex = pIecCfgData->m_nFiberIndex;
// 	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
// 
// 	if (nFiberIndex == pIecCfgData->m_nFiberIndex)
// 	{
// 		return;
// 	}
// 
// 	if (pIecCfgDataGrid->ValidateIecCfgDatFiberIndex(pIecCfgData))
// 	{
// 		return;
// 	}
// 
// 	pIecCfgData->m_nFiberIndex = nFiberIndex;
// 	pIecCfgDataGrid->FreeExBaseCellData(nRow, nCol);
// 	pIecCfgDataGrid->Show_Fiber(pIecCfgData, nRow, nCol, &pIecCfgData->m_nFiberIndex);
// }