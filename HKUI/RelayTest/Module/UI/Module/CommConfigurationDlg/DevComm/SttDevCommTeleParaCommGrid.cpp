#include "SttDevCommTeleParaCommGrid.h"
#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../../Module/API/StringConvertApi.h"
#include <QApplication>

extern void Global_SetComCfgTableHeight(QTableWidget *pGrid);
extern CFont *g_pSttGlobalFont;

SttCDevCommParaCommGrid::SttCDevCommParaCommGrid (QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_bRunning = FALSE;
	//horizontalHeader()->setFont(/*oFont*/*g_pSttGlobalFont);
	setFont(*g_pSttGlobalFont);
}

SttCDevCommParaCommGrid::~SttCDevCommParaCommGrid ()
{

}

void SttCDevCommParaCommGrid::InitGrid()
{
 	InitGridTitle();
	//SetEditable(FALSE);
	//this->columnCount();
	for (int i=0; i<columnCount(); i++)
	{
		horizontalHeaderItem(i)->setFont(*g_pSttGlobalFont);
	}
}

void SttCDevCommParaCommGrid::InitGridTitle()
{
	CString astrGridTitle[STTCDEVCOMMPARACOMMGRID_COLS] = { CString("参数名称"), CString("地址"), CString("数据值"), /*_T("数据类型")*/g_sLangTxt_DataType};
	int  iColType[STTCDEVCOMMPARACOMMGRID_COLS] = {QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT};
	int iGridWidth[STTCDEVCOMMPARACOMMGRID_COLS] = {200, 100, 100, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTCDEVCOMMPARACOMMGRID_COLS);
}

void SttCDevCommParaCommGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
 	CDvmData *pDvmData = (CDvmData *)pData;
	
 	Show_StaticString(pData, nRow, 0, &pDvmData->m_strName); 
	//Show_Hex(pData,nRow,1,&pDvmData->m_nIndex);
	Show_Hex(pData, nRow, 1, (DWORD*)(&pDvmData->m_nIndex), 2,false); 

	//Show_StaticString(pData, nRow, 2, &pDvmData->m_strValue);
	CString strTmp1;
	utf8_to_gbk(pDvmData->m_strValue,strTmp1);

	if ((strTmp1 != pDvmData->m_strValue)&&(!strTmp1.IsEmpty()))//zhouhj 2024.1.17此处处理方式有问题,后续应该在PpEngine里读取数据后,转换为GBK ?????
	{
		pDvmData->m_strValue = strTmp1;
	} 

	Show_String(pData, nRow, 2, &pDvmData->m_strValue, EndEditCell_CmdDataValue);
	Show_StaticString(pData, nRow, 3, &pDvmData->m_strDataType); 

 	nRow++;

	Global_SetComCfgTableHeight(this);
}

void SttCDevCommParaCommGrid::SelectRow(int nRow)
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


void SttCDevCommParaCommGrid::EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
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
		pGrid->SetItemFgColour(nRow, 2, 255, 0, 0);
	}
}


bool SttCDevCommParaCommGrid::eventFilter(QObject *obj, QEvent *event)
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

void SttCDevCommParaCommGrid::mousePressEvent(QMouseEvent * event)
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
