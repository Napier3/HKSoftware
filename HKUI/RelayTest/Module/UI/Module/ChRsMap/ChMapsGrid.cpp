#include "ChMapsGrid.h"
#include "../../../../Module/SttCmd/SttChMap.h"
#include "../../SttTestCntrFrameBase.h"
#include <QApplication>

#define CHMAPS_GRID_COL_INDEX_NAME                    0
//#define CHMAPS_GRID_COL_INDEX_ID                      1
#define CHMAPS_GRID_COL_INDEX_ANALOG                  1
#define CHMAPS_GRID_COL_INDEX_DIGITAL                 2
#define CHMAPS_GRID_COL_INDEX_WEAK                    3


CChMapsGrid::CChMapsGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_bRunning = FALSE;
	installEventFilter(this);
}

CChMapsGrid::~CChMapsGrid()
{

}

void CChMapsGrid::InitGrid()
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

	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_clicked(int,int)),Qt::UniqueConnection);
}

void CChMapsGrid::InitGridTitle()
{
	CString strName,strAnalog,strDigital,strWeek;

	xlang_GetLangStrByFile(strName,"sName");
	xlang_GetLangStrByFile(strAnalog,"ChMaps_AnalogCh");
	xlang_GetLangStrByFile(strDigital,"ChMaps_DigitalCh");
	xlang_GetLangStrByFile(strWeek,"ChMaps_WeekCh");

	CString astrGridTitle[CHMAPS_GRID_COLS] = {strName,strAnalog,strDigital,strWeek};
	int  iColType[CHMAPS_GRID_COLS]={QT_GVET_NOEDIT, /*QT_GVET_NOEDIT,*/QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[CHMAPS_GRID_COLS]={130,/* 100,*/ 130, 130, 130};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CHMAPS_GRID_COLS);
//	SetFont(g_pGlobalFont11);
}

void CChMapsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->m_strID.Find("Bin") >= 0)
	{
		return;
	}
	else if (pData->m_strID.Find("Bout") >= 0)
	{
		return;
	}

	ASSERT(pData);
	CSttChMap *pChMap = (CSttChMap *)pData;
	Show_String(pData,nRow,0,&pChMap->m_strName,EndEditCell_String); 
//	Show_StaticString(pData,nRow,1,&pChMap->m_strID); 
	CString strAnalogString,strDigString,strWeakString;
	strAnalogString = pChMap->GetHdChsString(STT_MODULETYPE_ID_ANALOG);
	strDigString = pChMap->GetHdChsString(STT_MODULETYPE_ID_DIGITAL);
	strWeakString = pChMap->GetHdChsString(STT_MODULETYPE_ID_WEEK);

	Show_String(pData,nRow,1,&strAnalogString,EndEditCell_ChMapsString); 
	Show_String(pData,nRow,2,&strDigString,EndEditCell_ChMapsString); 
	Show_String(pData,nRow,3,&strWeakString,EndEditCell_ChMapsString); 
 	nRow++;
}

void CChMapsGrid::EndEditCell_ChMapsString (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CSttChMap *pChMap = (CSttChMap*)pVCellData->pObj;
	CString strText = pCell->text();

	if (nCol == CHMAPS_GRID_COL_INDEX_ANALOG)
	{
		pChMap->InitHdChs_ByString(strText,STT_MODULETYPE_ID_ANALOG);
	}
	else if (nCol == CHMAPS_GRID_COL_INDEX_DIGITAL)
	{
		pChMap->InitHdChs_ByString(strText,STT_MODULETYPE_ID_DIGITAL);
	}
	else if (nCol == CHMAPS_GRID_COL_INDEX_WEAK)
	{
		pChMap->InitHdChs_ByString(strText,STT_MODULETYPE_ID_WEEK);
	}

	pCell->setText(strText);
}

void CChMapsGrid::slot_clicked( int nRow,int nCol )
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

bool CChMapsGrid::eventFilter(QObject *obj, QEvent *event)
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

void CChMapsGrid::mousePressEvent(QMouseEvent *event)
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

