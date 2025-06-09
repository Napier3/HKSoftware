#include "BinBoutMapsGrid.h"
#include "../../../../Module/SttCmd/SttChMap.h"
#include "../../SttTestCntrFrameBase.h"
#include <QApplication>


#define CHMAPS_GRID_COL_INDEX_ID	                  0
#define CHMAPS_GRID_COL_INDEX_NAME                    1


CBinBoutMapsGrid::CBinBoutMapsGrid(QWidget* pparent, int iType) :QExBaseListGridBase(pparent)
{
	m_bRunning = FALSE;
	installEventFilter(this);

	CString sName, str;
	m_oDataType.DeleteAll();
	if (iType == BINBOUT_MAPS_TYPE_BIN)
	{
		for (int i = 0; i < 8; i++)
		{
			sName = g_sLangTxt_Native_Bin + (char)(i + 65);
			m_oDataType.AddNewValue(sName, i);
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			str.Format(_T("%d"), i + 1);
			sName = g_sLangTxt_Native_Bout + str;
			m_oDataType.AddNewValue(sName, i);
		}
	}

	m_pDataTypeDelegBase = NULL;
}

CBinBoutMapsGrid::~CBinBoutMapsGrid()
{

}

void CBinBoutMapsGrid::InitGrid()
{
// 	SetListMode(TRUE);
// 	SetColumnCount(GROUPRIGHTS_TABLE_COLS);
// 	SetFixedRowCount(1);
// 	SetFixedColumnCount(1);
 	InitGridTitle();
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
//	AutoAdjColWidth();
	SetEditable(TRUE);

	setFont(*g_pSttGlobalFont);
	horizontalHeader()->setFont(*g_pSttGlobalFont);

	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_clicked(int,int)),Qt::UniqueConnection);
}

void CBinBoutMapsGrid::InitGridTitle()
{
	CString astrGridTitle[BINBOUTMAPS_GRID_COLS] = { g_sLangTxt_MappingRelation_Maps_TitleID, g_sLangTxt_MappingRelation_Maps_TitleName };
	int  iColType[BINBOUTMAPS_GRID_COLS] = { QT_GVET_NOEDIT, QT_GVET_EDITBOX };
	int iGridWidth[BINBOUTMAPS_GRID_COLS] = { 260, 260 };
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, BINBOUTMAPS_GRID_COLS);
	//	SetFont(g_pGlobalFont11);

	m_pDataTypeDelegBase = new QExBaseListEditComBoxDelegBase(this);
	setItemDelegateForColumn(CHMAPS_GRID_COL_INDEX_NAME, m_pDataTypeDelegBase);
	m_pDataTypeDelegBase->SetEditable(TRUE);
	m_pDataTypeDelegBase->SetUseEditCtrl(TRUE);
}

void CBinBoutMapsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	CSttChMap *pChMap = (CSttChMap *)pData;
	Show_StaticString(pData, nRow, CHMAPS_GRID_COL_INDEX_ID, &pChMap->m_strID);
	Show_DataType_Val(pData, nRow, CHMAPS_GRID_COL_INDEX_NAME, &m_oDataType, &(pChMap->m_strName), EndEditCell_ChMapsString);
	nRow++;
}

void  CBinBoutMapsGrid::Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByID(*pstrValue);
		if (pValue != NULL)
		{
			*pstrValue = pValue->m_strID;
		}
	}

	QGV_ITEM *pItem = NULL;
	BOOL bHasSetItem = FALSE;

	if (pValue == NULL)
	{
		pItem = AddItem(nRow, nCol, *pstrValue, bHasSetItem);
	}
	else
	{
		pItem = AddItem(nRow, nCol, pValue->m_strName, bHasSetItem);
	}

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, pstrValue, pData, NULL, pFunc);
	pVCellData->pExBaseList = pDataType;
	pVCellData->nVt = VCD_STRING;
	pItem->m_pEditFunc = pFunc;

	pItem->nDataType = QT_GVET_COMBOBOX;
	pItem->nReserved = QT_GRID_COMBOBOX_StringType_DataTypeID;
	pItem->lParam = (LPARAM)pVCellData;

	pItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	if (!(pItem->flags() & Qt::ItemIsEditable))
	{
		pItem->setFlags((pItem->flags() | Qt::ItemIsEditable));
	}

	if (!bHasSetItem)
	{
		setItem(nRow, nCol, pItem);
	}
}

void CBinBoutMapsGrid::EndEditCell_ChMapsString(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CSttChMap *pChMap = (CSttChMap*)pVCellData->pObj;
	CString strText = pCell->text();

	//20241011 huangliang 添加字符长度不能超过16字符
	if (strText.toLocal8Bit().length() >= 16)
	{
		strText = strText.Left(16);
	}

	pCell->setText(strText);
	pChMap->m_strName = strText;
	pChMap->m_strAlias = strText;
}

void CBinBoutMapsGrid::slot_clicked(int nRow, int nCol)
{
	QTableWidgetItem *pItem = this->item(nRow,nCol);
	if (pItem == NULL)
	{
		return;
	}
	
	QString strValue = pItem->text();
	GetEngWidgetBoard_DigitData(strValue, g_theTestCntrFrame);
	pItem->setText(strValue);

	/*
	WidgetKeyboard dlg(g_theTestCntrFrame);
	dlg.m_InputString = pItem->text();
	dlg.showToEdit();
	if (dlg.exec() == QDialog::Accepted)
	{
		pItem->setText(dlg.m_InputString);
	}
	*/
}

bool CBinBoutMapsGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent * pMouseEvent = (QMouseEvent*) event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);
}

void CBinBoutMapsGrid::mousePressEvent(QMouseEvent *event)
{
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QExBaseListGridBase::mousePressEvent(event);
}


