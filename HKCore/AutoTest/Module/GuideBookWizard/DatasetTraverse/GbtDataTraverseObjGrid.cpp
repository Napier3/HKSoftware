#include "StdAfx.h"
#include "GbtDataTraverseObjGrid.h"
#include "..\..\..\..\Module\API\GlobalApi.h"
#include "..\..\XLanguageResourceAts.h"
#define GBTDATATRAVE_GRID_COLS         5
#define GBTDATATRAVE_GRID_ID_INEX      0
#define GBTDATATRAVE_GRID_ID_NAME      1
#define GBTDATATRAVE_GRID_ID_MODELTYPE 2
#define GBTDATATRAVE_GRID_ID_BEGINVAL  3
#define GBTDATATRAVE_GRID_ID_STEP      4


CGbtDataTraverseObjGrid::CGbtDataTraverseObjGrid(void)
{
	m_pBatchDatasetTraverse = NULL;
}

CGbtDataTraverseObjGrid::~CGbtDataTraverseObjGrid(void)
{

}

void CGbtDataTraverseObjGrid::ShowGbtDataTraverse(CGbtBatchDatasetTraverse *pGbtBatchDatasetTraverse)
{
	ASSERT(pGbtBatchDatasetTraverse != NULL);

	m_pBatchDatasetTraverse = pGbtBatchDatasetTraverse;
	POS pos = m_pBatchDatasetTraverse->GetHeadPosition();
	CGbtDataTraverseObj *pGbtData = NULL;
	int nRowIndex = 1;

	while (pos != NULL)
	{
		pGbtData = (CGbtDataTraverseObj *)m_pBatchDatasetTraverse->GetNext(pos);
		ShowGbtDataTraverseObj(pGbtData, nRowIndex);
	}

// 	AutoSizeColumn(GBTDATATRAVE_GRID_ID_NAME);
// 	AutoSizeColumn(GBTDATATRAVE_GRID_ID_MODELTYPE);

	ResetScrollBars();
	Invalidate(FALSE);
}

void CGbtDataTraverseObjGrid::InitExGrid()
{
	SetListMode(FALSE);
	SetRowCount(1);
	SetColumnCount(GBTDATATRAVE_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CGbtDataTraverseObjGrid::InitGridTitle()
{
	CString cTempStr[GBTDATATRAVE_GRID_COLS]={/*_T("编号")*/g_sLangTxt_Index, /*_T("数据接口名称")*/g_sLangTxt_DataInterfaceName, /*_T("处理模式")*/g_sLangTxt_DealMode, /*_T("起始值")*/g_sLangTxt_StartValue, /*_T("步长")*/g_sLangTxt_Step};
	int iWidth[GBTDATATRAVE_GRID_COLS]={60,160,100, 80, 80};

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	SetRowCount(1);
	SetColumnCount(GBTDATATRAVE_GRID_COLS);

	for (int iCol=0;iCol<GBTDATATRAVE_GRID_COLS;iCol++)
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

void CGbtDataTraverseObjGrid::ShowGbtDataTraverseObj(CGbtDataTraverseObj *pGbtDataTraverseObj, int &nRowIndex)
{
	InsertRow(_T(""));
	UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRowIndex);

	SetRowHeight(nRowIndex,20);
	nRowIndex++;
}

void CGbtDataTraverseObjGrid::UpdateGbtDataTraverseObj(CGbtDataTraverseObj *pGbtDataTraverseObj, int &nRowIndex)
{
	GV_ITEM Item;

	Item.mask = GVIF_PARAM | GVIF_TEXT | GVIF_DATATYPE | GVIF_FORMAT | GVIF_FUNC;
	Item.row = nRowIndex;
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = GVET_NOEDIT;
	Item.lParam = (LPARAM)pGbtDataTraverseObj;
	Item.pEditFunc = NULL;
	
	//index
	Item.col = GBTDATATRAVE_GRID_ID_INEX;
	Item.szText.Format(_T("%d"), nRowIndex);;
	SetItem(&Item);

	Item.col = GBTDATATRAVE_GRID_ID_NAME;
	Item.szText = pGbtDataTraverseObj->m_pDataRef->m_strName;
	SetItem(&Item);

	Item.col = GBTDATATRAVE_GRID_ID_MODELTYPE;
	Item.szText = pGbtDataTraverseObj->GetModelTypeName();
	Item.pEditFunc = EndEdit_ModelType;
	Item.nDataType = GVET_COMBOBOX;
	SetItem(&Item);
	
	if (pGbtDataTraverseObj->IsModelTypeDataset())
	{
		Item.pEditFunc = NULL;
		Item.nDataType = GVET_NOEDIT;
		Item.szText.Empty();
	
		Item.col = GBTDATATRAVE_GRID_ID_BEGINVAL;
		SetItem(&Item);

		Item.col = GBTDATATRAVE_GRID_ID_STEP;
		SetItem(&Item);
	}
	else
	{
		Item.nDataType = GVET_EDITBOX;
	
		Item.col = GBTDATATRAVE_GRID_ID_BEGINVAL;
		Item.szText.Format(_T("%f"), pGbtDataTraverseObj->m_dBeginVal);
		Item.pEditFunc = EndEdit_BeginVal;
		ChopFloatString(Item.szText, -1);
		SetItem(&Item);

		Item.col = GBTDATATRAVE_GRID_ID_STEP;
		Item.szText.Format(_T("%f"), pGbtDataTraverseObj->m_dStep);
		Item.pEditFunc = EndEdit_Step;
		ChopFloatString(Item.szText, -1);
		SetItem(&Item);
	}

}

//填充comboList cell
void CGbtDataTraverseObjGrid::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)
{
	if (nCol != GBTDATATRAVE_GRID_ID_MODELTYPE)
	{
		return;
	}

	CComboBox *pCombBox = (CComboBox*)cltWnd;

	ASSERT (::IsWindow(pCombBox->m_hWnd));
	long nIndex = pCombBox->AddString(/*GBTDATATRAVERSE_MODE_DATASET_NAME*/g_sLangTxt_DatasetTraverse);
	pCombBox->SetItemData(nIndex, GBTDATATRAVERSE_MODE_DATASET_INDEX);
	nIndex = pCombBox->AddString(/*GBTDATATRAVERSE_MODE_VALRAMP_NAME*/g_sLangTxt_NumberArithmetic);
	pCombBox->SetItemData(nIndex, GBTDATATRAVERSE_MODE_VALRAMP_INDEX);
}

void  CGbtDataTraverseObjGrid::EndEdit_ModelType(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataTraverseObj *pGbtDataTraverseObj = (CGbtDataTraverseObj*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);

	pGbtDataTraverseObj->SetModeType(pCell->dwValue);

	CGbtDataTraverseObjGrid *pThis = (CGbtDataTraverseObjGrid*)pGrid;
	pThis->UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
	pThis->Invalidate(FALSE);
}


void  CGbtDataTraverseObjGrid::EndEdit_BeginVal(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataTraverseObj *pGbtDataTraverseObj = (CGbtDataTraverseObj*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);

	pGbtDataTraverseObj->m_dBeginVal =CString_To_double (pCell->szText);
	CGbtDataTraverseObjGrid *pThis = (CGbtDataTraverseObjGrid*)pGrid;
	pThis->UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
}


void  CGbtDataTraverseObjGrid::EndEdit_Step(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CGbtDataTraverseObj *pGbtDataTraverseObj = (CGbtDataTraverseObj*)pCell->lParam;
	ASSERT( pGbtDataTraverseObj != NULL);

	pGbtDataTraverseObj->m_dStep = CString_To_double(pCell->szText);

	CGbtDataTraverseObjGrid *pThis = (CGbtDataTraverseObjGrid*)pGrid;
	pThis->UpdateGbtDataTraverseObj(pGbtDataTraverseObj, nRow);
}
