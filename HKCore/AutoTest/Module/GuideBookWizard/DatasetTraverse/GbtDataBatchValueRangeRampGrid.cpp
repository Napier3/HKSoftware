#include "StdAfx.h"
#include "GbtDataBatchValueRangeRampGrid.h"
#include "..\..\..\..\Module\API\GlobalApi.h"
#include "..\..\XLanguageResourceAts.h"
#define GBTDATARAMP_GRID_COLS         5
#define GBTDATARAMP_GRID_ID_INEX      0
#define GBTDATARAMP_GRID_ID_NAME      1
#define GBTDATARAMP_GRID_ID_BEGINVAL  2
#define GBTDATARAMP_GRID_ID_STEP      3
#define GBTDATARAMP_GRID_ID_STEPS     4


CGbtDataBatchValueRangeRampGrid::CGbtDataBatchValueRangeRampGrid(void)
{
	m_pGbtDataBatchValueRangeRamp = NULL;
}

CGbtDataBatchValueRangeRampGrid::~CGbtDataBatchValueRangeRampGrid(void)
{

}

void CGbtDataBatchValueRangeRampGrid::ShowGbtDataBatchValueRangeRamp(CGbtDataBatchValueRangeRamp *pGbtDataBatchValueRangeRamp)
{
	ASSERT(pGbtDataBatchValueRangeRamp != NULL);

	m_pGbtDataBatchValueRangeRamp = pGbtDataBatchValueRangeRamp;
	POS pos = m_pGbtDataBatchValueRangeRamp->GetHeadPosition();
	CGbtDataTraverseObj *pGbtData = NULL;
	int nRowIndex = 1;

	while (pos != NULL)
	{
		pGbtData = (CGbtDataTraverseObj *)m_pGbtDataBatchValueRangeRamp->GetNext(pos);
		ShowGbtDataTraverseObj(pGbtData, nRowIndex);
	}

	ResetScrollBars();
	Invalidate(FALSE);
}

void CGbtDataBatchValueRangeRampGrid::InitExGrid()
{
	SetListMode(FALSE);
	SetRowCount(1);
	SetColumnCount(GBTDATARAMP_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CGbtDataBatchValueRangeRampGrid::InitGridTitle()
{
	CString cTempStr[GBTDATARAMP_GRID_COLS]={/*_T("编号")*/g_sLangTxt_Index, /*_T("数据接口名称")*/g_sLangTxt_DataInterfaceName, /*_T("起始值")*/g_sLangTxt_StartValue, /*_T("步长")*/g_sLangTxt_Step, /*_T("步数")*/g_sLangTxt_StepNumber};
	int iWidth[GBTDATARAMP_GRID_COLS]={60,160,100, 80, 80};

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	SetRowCount(1);
	SetColumnCount(GBTDATARAMP_GRID_COLS);

	for (int iCol=0;iCol<GBTDATARAMP_GRID_COLS;iCol++)
	{
		Item.col = iCol + 0;
		SetColumnType(iCol,GVET_NOEDIT);
		SetColumnWidth(iCol,iWidth[iCol]);
		Item.szText=cTempStr[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
	}	

	SetRowHeight(0,20);
}

void CGbtDataBatchValueRangeRampGrid::ShowGbtDataTraverseObj(CGbtDataTraverseObj *pGbtDataTraverseObj, int &nRowIndex)
{
	InsertRow(_T(""));
	UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRowIndex);

	SetRowHeight(nRowIndex,20);
	nRowIndex++;
}

void CGbtDataBatchValueRangeRampGrid::UpdateGbtDataTraverseObj(CGbtDataTraverseObj *pGbtDataTraverseObj, int &nRowIndex)
{
	GV_ITEM Item;

	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT | GVIF_FUNC;
	Item.row = nRowIndex;
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = GVET_NOEDIT;
	Item.lParam = (LPARAM)pGbtDataTraverseObj;
	Item.pEditFunc = NULL;
	
	//index
	Item.col = GBTDATARAMP_GRID_ID_INEX;
	Item.szText.Format(_T("%d"), nRowIndex);;
	SetItem(&Item);

	Item.col = GBTDATARAMP_GRID_ID_NAME;
	Item.szText = pGbtDataTraverseObj->m_pDataRef->m_strName;
	SetItem(&Item);


	Item.nDataType = GVET_EDITBOX;

	Item.col = GBTDATARAMP_GRID_ID_BEGINVAL;
	Item.szText.Format(_T("%f"), pGbtDataTraverseObj->m_dBeginVal);
	Item.pEditFunc = EndEdit_BeginVal;
	ChopFloatString(Item.szText, -1);
	SetItem(&Item);

	Item.col = GBTDATARAMP_GRID_ID_STEP;
	Item.szText.Format(_T("%f"), pGbtDataTraverseObj->m_dStep);
	Item.pEditFunc = EndEdit_Step;
	ChopFloatString(Item.szText, -1);
	SetItem(&Item);
	
	Item.col = GBTDATARAMP_GRID_ID_STEPS;
	Item.szText.Format(_T("%d"), pGbtDataTraverseObj->m_nSteps);
	Item.pEditFunc = EndEdit_Steps;
	ChopFloatString(Item.szText, -1);
	SetItem(&Item);


}

void  CGbtDataBatchValueRangeRampGrid::EndEdit_ModelType(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataTraverseObj *pGbtDataTraverseObj = (CGbtDataTraverseObj*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);

	pGbtDataTraverseObj->SetModeType(pCell->dwValue);

	CGbtDataBatchValueRangeRampGrid *pThis = (CGbtDataBatchValueRangeRampGrid*)pGrid;
	pThis->UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
	pThis->Invalidate(FALSE);
}


void  CGbtDataBatchValueRangeRampGrid::EndEdit_BeginVal(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataTraverseObj *pGbtDataTraverseObj = (CGbtDataTraverseObj*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);

	pGbtDataTraverseObj->m_dBeginVal = CString_To_double(pCell->szText);
	CGbtDataBatchValueRangeRampGrid *pThis = (CGbtDataBatchValueRangeRampGrid*)pGrid;
	pThis->UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
}


void  CGbtDataBatchValueRangeRampGrid::EndEdit_Step(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataTraverseObj *pGbtDataTraverseObj = (CGbtDataTraverseObj*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);

	pGbtDataTraverseObj->m_dStep = CString_To_double(pCell->szText);
	CGbtDataBatchValueRangeRampGrid *pThis = (CGbtDataBatchValueRangeRampGrid*)pGrid;
	pThis->UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
}

void  CGbtDataBatchValueRangeRampGrid::EndEdit_Steps(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataTraverseObj *pGbtDataTraverseObj = (CGbtDataTraverseObj*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);
	CGbtDataBatchValueRangeRampGrid *pThis = (CGbtDataBatchValueRangeRampGrid*)pGrid;

	long nSteps = CString_To_long(pCell->szText);
	pThis->SetSteps(nSteps);
}

void CGbtDataBatchValueRangeRampGrid::SetSteps(long nSteps)
{
	CGbtDataTraverseObj *pGbtDataTraverseObj = NULL;
	POS pos = m_pGbtDataBatchValueRangeRamp->GetHeadPosition();
	int nRowIndex = 1;

	while (pos != NULL)
	{
		pGbtDataTraverseObj = (CGbtDataTraverseObj *)m_pGbtDataBatchValueRangeRamp->GetNext(pos);
		pGbtDataTraverseObj->m_nSteps = nSteps;
		UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRowIndex);
		nRowIndex++;
	}

	Invalidate(FALSE);
}

