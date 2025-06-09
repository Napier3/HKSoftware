#include "stdafx.h"
#include "UISftRsltWndDsGrid.h"
#include "UISftRsltWndInterface.h"
#include "../../../Module/api/GlobalApi.h"
#include "../GuideBook/GbDataTypeMngr.h"

#include "..\XLanguageResourceAts.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUISftRsltWndDsGrid::CUISftRsltWndDsGrid()
{
	m_pCurDataSet = NULL;
}

void CUISftRsltWndDsGrid::CreateGsGrid(CShortData *pData, UINT nID, CWnd *pParent)
{
	Create(CRect(0, 0, 0, 0),pParent,nID);
	
	m_strDvmDsPath = pData->m_strFormat;
	m_pData = pData;
	InitGrid();
	UpdateVariables_Dataset();
}


void CUISftRsltWndDsGrid::InitGrid()
{
	SetListMode(TRUE);
	//	EnableDragAndDrop(TRUE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	//	m_oColumns.DeleteAll();
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(5);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);

	InitGridTitle();

	ResetScrollBars();
}

void CUISftRsltWndDsGrid::InitGridTitle()
{
	int iNum=5;
	CString cTempStr[5]={g_sLangTxt_Index/*"编号"*/,g_sLangTxt_Name/*"名称"*/,g_sLangTxt_Id/*"ID"*/,g_sLangTxt_Unit/*"单位"*/,g_sLangTxt_DataType/*"数据类型"*/};
	int  iColType[6]={GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT, GVET_NOEDIT};
	int nColWidth[5] = {60, 200, 100, 60, 100};

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	for (int iCol=0;iCol<iNum;iCol++)
	{
		Item.col = iCol+0;
		SetColumnType(iCol,iColType[iCol]);
		Item.szText=cTempStr[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
		SetColumnWidth(iCol, nColWidth[iCol]);
	}	

	SetRowHeight(0,20);
}

CUISftRsltWndDsGrid::~CUISftRsltWndDsGrid()
{

}

void CUISftRsltWndDsGrid::UpdateVariables_Dataset()
{
	CDevice *pDevice = (CDevice*)m_pData->GetAncestor(GBCLASSID_DEVICE);
	ASSERT (pDevice != NULL);

	CExBaseList oListDataset;
	pDevice->SelectDataSetList(m_strDvmDsPath, oListDataset, 0);

	if (oListDataset.GetCount() > 0)
	{
		m_pCurDataSet = (CDataSet *)oListDataset.GetHead();
	}

	oListDataset.RemoveAll();

	if (m_pCurDataSet == NULL)
	{
		SetRowCount( 1 );
		return;
	}

	CDataObj* pData = NULL;
	long nRows = 0;
	CValue * pValue = NULL;
	long nCount = m_pCurDataSet->GetCount();
	SetRowCount(nCount + 1);
	CString strID;

	for(long nIndex=0;nIndex<nCount;nIndex++)
	{
		pData = (CDataObj*)m_pCurDataSet->GetAtIndex(nIndex);
		nRows++;
		ShowOneData(pData, nRows/*,pValue->m_strValue*/);
	}

	AutoSizeColumn(0);
	AutoSizeColumn(1);
	AutoSizeColumn(2);
	AutoSizeColumn(3);
	AutoSizeColumn(4);
}

void CUISftRsltWndDsGrid::InitGvItem(GV_ITEM &Item)
{
	Item.mask=GVIF_FORMAT|GVIF_PARAM|GVIF_TEXT | GVIF_FGCLR|GVIF_BKCLR | GVIF_DATATYPE;	
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = 0;
	Item.crBkClr=RGB(200, 251, 196);
	Item.crFgClr=RGB(0,0,255);

}

void CUISftRsltWndDsGrid::ShowOneData(CDataObj* pData,long nRow/*,_bstr_t strValue*/)
{
	GV_ITEM Item;
	InitGvItem(Item);
	Item.lParam = nRow;
	Item.row = nRow;	
	Item.col = 0;

	Item.szText.Format(_T("%d"), nRow);
	SetItem(&Item);	

	Item.col++;
	Item.szText = pData->m_strName;
	SetItem(&Item);	

	Item.col++;
	Item.szText = pData->m_strID;
	SetItem(&Item);

	Item.col++;
	Item.szText = pData->m_strUnit;
	SetItem(&Item);

	InitGvItem(Item);
	Item.col++;
	Item.szText = pData->m_strDataType;
	SetItem(&Item);

	SetRowHeight(nRow,20);
}

