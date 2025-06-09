#include "StdAfx.h"
#include "MyGridCtrl.h"

CMyGridCtrl::CMyGridCtrl()
{
	CGridDataType *pDataType = NULL;
	long nValueID = 0;
	unsigned short nDataTypeID = 1;

	nValueID = 0;
	nDataTypeID++;
	pDataType = m_oDataTypes.AddNew(_T("ChannelID"), _T("CHID"), GVET_CreateDataTyp(GVET_COMBOBOX, nDataTypeID) );
	pDataType->AddNew(_T("A相"), _T("A"), nValueID++);
	pDataType->AddNew(_T("B相"), _T("B"), nValueID++);
	pDataType->AddNew(_T("C相"), _T("C"), nValueID++);
	pDataType->AddNew(_T("AB相"), _T("AB"), nValueID++);
	pDataType->AddNew(_T("BC相"), _T("BC"), nValueID++);
	pDataType->AddNew(_T("CA相"), _T("CA"), nValueID++);

	nValueID = 0;
	nDataTypeID++;
	pDataType = m_oDataTypes.AddNew(_T("URange"), _T("URange"), GVET_CreateDataTyp(GVET_COMBOBOX, nDataTypeID));
	pDataType->AddNew(_T("500 V"), _T("U500"), nValueID++);
	pDataType->AddNew(_T("200 V"), _T("U200"), nValueID++);
	pDataType->AddNew(_T("100 V"), _T("U100"), nValueID++);
	pDataType->AddNew(_T("50 V"), _T("U50"), nValueID++);
	pDataType->AddNew(_T("10 V"), _T("U10"), nValueID++);
	pDataType->AddNew(_T("5 V"), _T("U5"), nValueID++);
	SetBkColor(RGB(255, 255, 255));

	SetListMode(TRUE);
}

CMyGridCtrl::~CMyGridCtrl()
{

}


void CMyGridCtrl::InitGrid(int iRows)
{
	//SetEditable(TRUE);
	//SetListMode(TRUE);
	EnableDragAndDrop(TRUE);
	SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
	DeleteAllItems();
	SetRowCount(iRows+1);
	SetColumnCount(6);

#ifdef GRID_FIXROW_TWO
	SetFixedRowCount(2);
#else
	SetFixedRowCount(1);
#endif
	SetFixedColumnCount(0);
	InitGridTitle();

	//#ifdef GRID_FIXROW_TWO
	//	CGridCellRange oRange = GetSelectedCellRange();
	//	oRange.Set(0, 0, 0, 1);
	//	oRange.Merge(TRUE);
	//
	//	oRange.Set(0, 2, 0, 5);
	//	oRange.Merge(TRUE);
	//#endif

	SetFixedColumnCount(0);
	CGridCellRange oRange1 = GetSelectedCellRange();
	oRange1.Set(0, 0, 1, 0);
	oRange1.Merge(TRUE);

	oRange1.Set(0, 1, 0, 5);
	oRange1.Merge(TRUE);

	//InitGridData();
	ResetScrollBars();
}

void CMyGridCtrl::InitGridTitle()
{
	int iNum=6;
	char cTempStr[6][24]={"参数名称","参数变量","数据类型","缺省值","单位","结果数据"};
	int  iColType[6]={GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT};
	int iWidth[6]={160,120,80,60,60,80};
	//int iWidth[6]={120,120,120,120,120,120};
	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	for (int iCol=0;iCol<iNum;iCol++)
	{
		Item.col = iCol+0;
		SetColumnType(iCol,iColType[iCol]);
		SetColumnWidth(iCol,iWidth[iCol]);
		Item.szText=cTempStr[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
	}	
	SetRowHeight(0,20);

#ifdef GRID_FIXROW_TWO
	Item.row = 1;
	for (iCol=0;iCol<iNum;iCol++)
	{
		Item.col = iCol;
		SetColumnType(iCol,iColType[iCol]);
		SetColumnWidth(iCol,iWidth[iCol]);
		Item.szText=cTempStr[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
	}	
	SetRowHeight(1,20);
#endif

}

void CMyGridCtrl::InitData()
{
	GV_ITEM Item;
	//Item.mask=GVIF_FORMAT|GVIF_FGCLR  | GVIF_PARAM|GVIF_TEXT ;//| GVIF_BKCLR;
	Item.mask=GVIF_FORMAT|GVIF_PARAM|GVIF_TEXT | GVIF_FGCLR|GVIF_BKCLR | GVIF_DATATYPE;	
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = 0;

	long nRows = GetRowCount()-1;
	for (int nRow = 2;nRow <= nRows;nRow++)
	{
		Item.lParam = nRow;
		Item.row = nRow;

		Item.crBkClr=RGB(241,249,98);
		Item.crBkClr=RGB(200, 251, 196);
		SetTextColor(RGB(120,120,255));
		Item.crFgClr=RGB(0,0,255);

		Item.col = 0;

		if (nRow % 3 == 0)
		{
			Item.nDataType = GVET_CHECKBOX;
		}
		else
		{
			Item.nDataType = GVET_NOEDIT;
		}
		Item.szText.Format(_T("%d, %d"), Item.row, Item.col);
		// SetItem(&Item);	

		Item.col++;
		Item.nDataType = 0;
		Item.szText.Format(_T("%d, %d"), Item.row, Item.col);
		SetItem(&Item);	

		Item.col++;
		Item.nDataType = GVET_CreateDataTyp(GVET_COMBOBOX, 1);
		Item.szText.Format(_T("%d, %d"), Item.row, Item.col);
		SetItem(&Item);	

		Item.nDataType = 0;
		Item.col++;
		Item.szText.Format(_T("%d, %d"), Item.row, Item.col);
		SetItem(&Item);	

		Item.col++;
		Item.szText.Format(_T("%d, %d"), Item.row, Item.col);
		SetItem(&Item);	

		Item.nDataType = GVET_CreateDataTyp(GVET_EDITBOX, 0);
		Item.col++;
		Item.szText.Format(_T("%d, %d"), Item.row, Item.col);
		SetItem(&Item);	

		SetRowHeight(nRow,20);	
	}
	ResetScrollBars();
}

void CMyGridCtrl::FillComboBoxItems(int nCol, LPARAM cltWnd)
{
	CGridDataTypeValue *pValue = NULL;
	CGridDataType *pDataType = m_oDataTypes[0];
	int nCount = pDataType->GetSize();
	int nIndex = 0;
	CComboBox *pCmbBox = (CComboBox*)cltWnd;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pValue = pDataType->GetAt(nIndex);
		pCmbBox->AddString(pValue->m_strName);
		pCmbBox->SetItemDataPtr(nIndex, pValue);
	}

}

