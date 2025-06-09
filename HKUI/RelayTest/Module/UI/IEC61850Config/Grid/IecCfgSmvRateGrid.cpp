#include "IecCfgSmvRateGrid.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSmvRate.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../SttTestCntrFrameBase.h"
#include <QApplication>

CIecCfgSmvRateGrid::CIecCfgSmvRateGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_bRunning = false;
	installEventFilter(this);
}

CIecCfgSmvRateGrid::~CIecCfgSmvRateGrid()
{

}

void CIecCfgSmvRateGrid::InitGrid()
{
 	InitGridTitle();
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif

//	AutoAdjColWidth();
	SetEditable(TRUE);

	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgSmvRateGrid::InitGridTitle()
{
	CString strName,strScaleFactor;
	xlang_GetLangStrByFile(strName,"sName");
	xlang_GetLangStrByFile(strScaleFactor,"IEC_ScaleFactor");

	CString astrGridTitle[IECCFGSMVRATE_GRID_COLS] = {strName,strScaleFactor};
	int iGridWidth[IECCFGSMVRATE_GRID_COLS]={150, 150};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMVRATE_GRID_COLS);
}

void CIecCfgSmvRateGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFGSMVRATE)
	{
		return;
	}

	CIecCfgSmvRate *pIecCfgSmvRate = (CIecCfgSmvRate*)pData;
	Show_StaticString(pData,nRow,0,&pIecCfgSmvRate->m_strName);
	Show_Float(pData,nRow,1,3,&pIecCfgSmvRate->m_fRate,1,EndEditCell_RateValue);
  	nRow++;
}


void CIecCfgSmvRateGrid::EndEditCell_RateValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)//cl20230906比列因子不能设置0
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	float fValue =  math_GetValueFromString(pCell->text());

	if (fValue!=0)
	{
		*(pVCellData->pfValue) = fValue;
	}
	/*else
	{
		*(pVCellData->pfValue) = m_fv;
	}

	m_fv = fValue;*/

	CString strTmp;
	strTmp.Format(_T("%.3f"), *(pVCellData->pfValue));								
	pCell->setText(strTmp);

	((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void CIecCfgSmvRateGrid::slot_doubleClicked( int nRow,int nCol )
{
// 	QTableWidgetItem *pItem = this->item(nRow,nCol);
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	if (nCol != 1)
	{
		return;
	}

	QString strValue = pItem->text();
	
	GetWidgetBoard_DigitData(4, strValue,pItem, g_theTestCntrFrame);
// 	pItem->setText(strValue);

	/*
	WidgetKeyboard dlg(this);
	dlg.m_InputString = pItem->text();
	dlg.showToEdit();
	if (dlg.exec() == QDialog::Accepted)
	{
		pItem->setText(dlg.m_InputString);
	}
	*/
}



bool CIecCfgSmvRateGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);

}

void CIecCfgSmvRateGrid::mousePressEvent(QMouseEvent * event)
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



