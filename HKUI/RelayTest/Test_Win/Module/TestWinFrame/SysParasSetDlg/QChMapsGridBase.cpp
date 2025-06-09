#include "QChMapsGridBase.h"

#include <QHeaderView>


QChMapsGridBase::QChMapsGridBase(QWidget* pparent):QTableWidget(pparent),m_pDatas(NULL)
{
	m_pCurrData = NULL;
	m_pDatas = NULL;
	m_bEditable = TRUE;
}

QChMapsGridBase::~QChMapsGridBase()
{
}

void QChMapsGridBase::Show_StaticString(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		pItem = new QGV_ITEM(*pString);
	}
	else
	{
		pItem->setText(*pString);
	}

	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags((Qt::ItemIsEnabled));
	setItem(nRow,nCol,pItem);
}

void QChMapsGridBase::Show_String(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);
	
	if (pItem == NULL)
	{
		pItem = new QGV_ITEM(*pString);
	}
	else
	{
		pItem->setText(*pString);
	}

	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags((Qt::ItemIsEditable|Qt::ItemIsEnabled));

//	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pString, pData,NULL, pFunc);
	pItem->lParam = (LPARAM)pVCellData;

	if (pFunc != NULL)
	{
		pItem->m_pEditFunc = pFunc;
		pVCellData->pFunc = pFunc;
	}
	else
	{
		pItem->m_pEditFunc = EndEditCell_String;
		pVCellData->pFunc = EndEditCell_String;
	}

	setItem(nRow,nCol,pItem);
}

void QChMapsGridBase::EndEditCell_String (int nRow, int nCol, QGV_ITEM *pCell, QChMapsGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (*pVCellData->pString != pCell->text())
	{
		*pVCellData->pString = pCell->text();
//		((QChMapsGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}
}


QGV_ITEM* QChMapsGridBase::GetCell(int nRow, int nCol) const
{
	if (nRow < 0 || nRow >= rowCount() || nCol < 0 || nCol >= columnCount()) return NULL;

	return (QGV_ITEM*)item(nRow,nCol);
}

void QChMapsGridBase::FreeExBaseCellData(long nRow, long nCol)
{
	QGV_ITEM *pCell = GetCell(nRow, nCol);

	if (pCell == NULL)
	{
		return;
	}

	if (pCell->lParam == 0)
	{
		return;
	}

	m_listVCellData.Delete((PEXBASECELLDATA)pCell->lParam);
	pCell->lParam = 0;
}

void QChMapsGridBase::FreeListVCellData()
{
	m_listVCellData.DeleteAll();
	int nMaxRow = rowCount(), nMaxCol = columnCount();
	QGV_ITEM *pItem = NULL; 

	for (int nRow = 0;nRow<nMaxRow;nRow++)
	{
		for (int nCol = 0;nCol<nMaxCol;nCol++)
		{
			pItem = GetCell(nRow,nCol);

			if (pItem != NULL)
			{
				pItem->lParam = 0;
			}
		}
	}
}

void QChMapsGridBase::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
// 	m_idCurrentCell.col = -1;
// 	m_idCurrentCell.row = -1;
 	ClearSelect();
	FreeListVCellData();
// 	CTLinkList <_ExBaseCellData> listVCellData;
// 	BackListCellData(listVCellData);
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(1);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

long QChMapsGridBase::GetDatasCount()
{
	ASSERT (m_pDatas != NULL);

	if (m_pDatas == NULL)
	{
		return 0;
	}
	else
	{
		return m_pDatas->GetCount();
	}
}

BOOL QChMapsGridBase::SetRowCount(int nRows, BOOL bResetScrollBars)
{
	setRowCount(nRows);
	return TRUE;
}

void QChMapsGridBase::InitGridTitle(const CString *pStrTitles, const int *pnWidth, int nCols)
{
	QHeaderView* pHeadTop =horizontalHeader();
	pHeadTop->setClickable(false);
	pHeadTop->setMovable(false);
	QHeaderView* pHeadLeft = verticalHeader();
//	pHeadLeft->setDefaultSectionSize(25);

	horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	QStringList headers;
//	headers<<tr("描述")<<tr("数据类型")<<tr("映射")<<tr("数值")<<tr("取反");
	setColumnCount(nCols);

	for (int nIndex = 0;nIndex<nCols;nIndex++)
	{
		headers<<pStrTitles[nIndex];
		setColumnWidth(nIndex,pnWidth[nIndex]);
	}

	setHorizontalHeaderLabels(headers);


// 	GV_ITEM Item;
// 	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
// 	Item.row = 0;
// 	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
// 
// 	for (int iCol=0;iCol<nCols;iCol++)
// 	{
// 		Item.col = iCol+0;
// 		SetColumnType(iCol,GVET_NOEDIT);
// 		SetColumnWidth(iCol,pnWidth[iCol]);
// 		Item.szText=pStrTitles[iCol];
// 		Item.lParam=0;//iCol;
// 		SetItem(&Item);
// 	}	
// 
// 	SetRowHeight(0,EXBASEGRID_ROWHEIGHT);
// 	SetFont(g_pGlobalFont16);   //shaolei  2021.03.13
}

void QChMapsGridBase::AfterShowDatas(long nBeginRow, BOOL bResetScrollBars)
{
	if (m_bEditable)
	{
		setEditTriggers(QAbstractItemView::DoubleClicked);
		connect(this,SIGNAL(cellChanged( int,int)),SLOT(slot_CellChanged( int , int )));
	}
	else
	{
		setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
// 	long nRowIndex = nBeginRow;
// 
// 	for (; nRowIndex<m_nRows; nRowIndex++)
// 	{
// 		SetRowHeight(nRowIndex, m_nRowHeight);
// 	}
// 
// 	AdjustAllCols(bResetScrollBars);
// 
// 	if (bResetScrollBars)
// 	{
// 		ResetScrollBars();
// 	}
// 
// 	Invalidate(FALSE);
}

void QChMapsGridBase::ClearSelect()
{
	disconnect(SIGNAL(cellChanged( int,int)),this,SLOT(slot_CellChanged( int , int )));
}

void QChMapsGridBase::slot_CellChanged(int nrow,int ncol)
{
	QGV_ITEM* pitem = (QGV_ITEM*)item(nrow,ncol);

	if(pitem == NULL)
	{
		return;
	}

	if (pitem->m_pEditFunc != NULL)
	{
		pitem->m_pEditFunc(nrow,ncol,pitem,this);
	}

//	OnChanDataChanged(pitem);
}