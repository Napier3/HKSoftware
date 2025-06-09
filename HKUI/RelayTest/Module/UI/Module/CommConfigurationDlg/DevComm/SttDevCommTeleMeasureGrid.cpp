#include "SttDevCommTeleMeasureGrid.h"

#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QApplication>

extern void Global_SetComCfgTableHeight(QTableWidget *pGrid);
extern CFont *g_pSttGlobalFont;

SttCDevCommTeleMeasureGrid::SttCDevCommTeleMeasureGrid (QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_bRunning = FALSE;
	//horizontalHeader()->setFont(/*oFont*/*g_pSttGlobalFont);
	setFont(*g_pSttGlobalFont);
}

SttCDevCommTeleMeasureGrid::~SttCDevCommTeleMeasureGrid ()
{

}

void SttCDevCommTeleMeasureGrid::InitGrid()
{
 	InitGridTitle();
	//SetEditable(FALSE);
	//this->columnCount();
	for (int i=0; i<columnCount(); i++)
	{
		horizontalHeaderItem(i)->setFont(*g_pSttGlobalFont);
	}
}

void SttCDevCommTeleMeasureGrid::InitGridTitle()
{
	///*_T("单位")*/g_sLangTxt_Unit
	CString astrGridTitle[STTCDEVCOMMTELEMEASUREGRID_COLS] = { CString("遥测名称"), CString("地址"), CString("系数"), CString("数据值"), /*_T("数据类型")*/g_sLangTxt_DataType};
	int  iColType[STTCDEVCOMMTELEMEASUREGRID_COLS] = {QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT};
	int iGridWidth[STTCDEVCOMMTELEMEASUREGRID_COLS] = {100, 100, 100, 100, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTCDEVCOMMTELEMEASUREGRID_COLS);
}

//该表格显示数据集
void SttCDevCommTeleMeasureGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = (CDvmData*)pData;

	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);
	//Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strID);
	Show_Hex(pData, nRow, 1, (DWORD*)(&pDvmData->m_nIndex), 2,false);

	CString strFormat = pDvmData->m_strFormat;
	if (strFormat.IsEmpty())
	{
		strFormat = "1";
	}
	Show_StaticString(pDvmData, nRow, 2, &strFormat); 
	//Show_StaticString(pDvmData, nRow, 3, &pDvmData->m_strValue);
	Show_String(pDvmData, nRow, 3, &pDvmData->m_strValue, EndEditCell_CmdDataValue);

	Show_StaticString(pDvmData, nRow, 4, &pDvmData->m_strDataType);

	nRow++;

	Global_SetComCfgTableHeight(this);
}

void SttCDevCommTeleMeasureGrid::SelectRow(int nRow)
{
// 	QGV_ITEM* pitem = (QGV_ITEM*)item(nRow,1);
// 
// 	if(pitem == NULL)
// 	{
// 		return;
// 	}
// 
// 	pitem->setSelected(true);
}


void SttCDevCommTeleMeasureGrid::EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	if (pVCellData->pString == NULL)
	{
		return;
	}

	if (*pVCellData->pString != pCell->text())
	{
		*pVCellData->pString = pCell->text();
		CDvmData *pData = (CDvmData*)pVCellData->pObj;
		pData->m_nChange = 1;
		pGrid->SetItemFgColour(nRow, 3, 255, 0, 0);
	}
}

bool SttCDevCommTeleMeasureGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}
#ifdef _PSX_QT_LINUX_
	return QScrollTableWidget::eventFilter(obj,event);
#else
	return QTableWidget::eventFilter(obj,event);
#endif
	return  true;

}

void SttCDevCommTeleMeasureGrid::mousePressEvent(QMouseEvent * event)
{

	if (m_bRunning)
	{
#ifdef _PSX_QT_LINUX_
		QScrollTableWidget::mousePressEvent(event);
#else
		QTableWidget::mousePressEvent(event);
#endif
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);

#ifdef _PSX_QT_LINUX_
	QScrollTableWidget::mousePressEvent(event);
#else
	QTableWidget::mousePressEvent(event);
#endif

}

