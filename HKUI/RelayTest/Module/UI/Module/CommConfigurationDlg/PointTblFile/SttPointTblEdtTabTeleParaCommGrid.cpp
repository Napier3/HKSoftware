#include "SttPointTblEdtTabTeleParaCommGrid.h"
#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../../Module/DataMngr/DvmLogicDevice.h"
#include <QApplication>

extern void Global_SetComCfgTableHeight(QTableWidget *pGrid);
extern CFont *g_pSttGlobalFont;

SttCPointTblEdtTabTeleParaCommGrid::SttCPointTblEdtTabTeleParaCommGrid (QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_bRunning = FALSE;
	//horizontalHeader()->setFont(/*oFont*/*g_pSttGlobalFont);
	setFont(*g_pSttGlobalFont);
}

SttCPointTblEdtTabTeleParaCommGrid::~SttCPointTblEdtTabTeleParaCommGrid ()
{

}

void SttCPointTblEdtTabTeleParaCommGrid::InitGrid()
{
 	InitGridTitle();
	//SetEditable(FALSE);
	//this->columnCount();
	for (int i=0; i<columnCount(); i++)
	{
		horizontalHeaderItem(i)->setFont(*g_pSttGlobalFont);
	}
}

void SttCPointTblEdtTabTeleParaCommGrid::InitGridTitle()
{
	CString astrGridTitle[STTCPOINTTBLEDTTABTELEPARACOMMGRID_COLS] = { _T("参数名称"),_T("地址"),/*_T("数据类型")*/g_sLangTxt_DataType};
	int  iColType[STTCPOINTTBLEDTTABTELEPARACOMMGRID_COLS] = {QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT};
	int iGridWidth[3] = {200, 100, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTCPOINTTBLEDTTABTELEPARACOMMGRID_COLS);
}

void SttCPointTblEdtTabTeleParaCommGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
	CDvmData *pDvmData = (CDvmData *)pData;
	Show_String(pData, nRow, 0, &pDvmData->m_strName); //第一列修改可编辑

	////Show_Hex(pData,nRow,1,(DWORD*)(&pDvmData->m_nIndex),2); 
	Show_Hex(pData, nRow, 1, (DWORD*)(&pDvmData->m_nIndex), 2, TRUE, TRUE, EndSttCommCfgEditCell_IndexValue); 

	////Show_Long(pData,nRow,1,&pDvmData->m_nIndex);
	Show_StaticString(pData, nRow, 2, &pDvmData->m_strDataType); 

 	nRow++;

	Global_SetComCfgTableHeight(this);
}

void SttCPointTblEdtTabTeleParaCommGrid::SelectRow(int nRow)
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


void SttCPointTblEdtTabTeleParaCommGrid::EndSttCommCfgEditCell_IndexValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	//qDebug()<<"EndSttCommCfgEditCell_AddrValue END test nrow:"<<nRow<<" ncol:"<<nCol;
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT(pVellData->pObj != NULL);

	CString crtVl = pCell->text();
	CDvmData *pDvmData = (CDvmData*)(pVellData->pObj);
	SttCPointTblEdtTabTeleParaCommGrid *pGridCrt =	(SttCPointTblEdtTabTeleParaCommGrid*)pGrid;

	CString strCellText = pCell->text();
	strCellText.MakeUpper();
	int nPos = strCellText.Find(CString("0X"));
	CString strTableAddr;
	long lLastRes = 0;
	if (nPos < 0) //非十六进制
	{	
		long lValue = CString_To_long(pCell->text());
		strTableAddr.Format(_T("0X%04X"),lValue);
		lLastRes = lValue;
		pDvmData->m_nIndex = lValue;


	}else{ //十六进制
		strTableAddr = pCell->text();
		CString strTmp = pCell->text();
		long nValue = 0;
		char *pzfTmp = NULL;
		CString_to_char(strTmp,&pzfTmp);
		HexToLong(pzfTmp,nValue);
		delete pzfTmp;
		lLastRes = nValue;
		//===========
		CString strValueMdy;
		strValueMdy.Format("%ld",nValue);
		//pDvmValue->m_strValue = strValueMdy;
		pDvmData->m_nIndex = nValue;
	}

	emit pGridCrt->sig_ChangedParaComIndex();

	////pCell->setText(strTableAddr);
}



bool SttCPointTblEdtTabTeleParaCommGrid::eventFilter(QObject *obj, QEvent *event)
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

void SttCPointTblEdtTabTeleParaCommGrid::mousePressEvent(QMouseEvent * event)
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


//
//bool SttCPointTblEdtTabTeleParaCommGrid::eventFilter(QObject *obj, QEvent *event)
//{
//	if (event->type() == QEvent::MouseButtonDblClick)
//	{
//		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
//		m_bRunning = TRUE;
//		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
//		m_bRunning = FALSE;
//		return  true;
//	}
//
//	return QTableWidget::eventFilter(obj,event);
//
//}
//
//void SttCPointTblEdtTabTeleParaCommGrid::mousePressEvent(QMouseEvent * event)
//{
//	if (m_bRunning)
//	{
//		QTableWidget::mousePressEvent(event);
//		return;
//	}
//
//	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
//	QApplication::postEvent(this,pEvent);
//	QTableWidget::mousePressEvent(event);
//
//}
