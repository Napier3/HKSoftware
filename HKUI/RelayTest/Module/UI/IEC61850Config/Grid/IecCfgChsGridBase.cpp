#include "IecCfgChsGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Ch.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../Module/ScrollCtrl/ScrollComboBox.h"
#include <QApplication>

//////////////////////////////////////////////////////////////////////////

QIecCfgChsComBoxDelegBase::QIecCfgChsComBoxDelegBase(QObject *parent)
: QExBaseListComBoxDelegBase(parent)
{
	m_bEditable= TRUE;
	m_bFirstClicked = TRUE;
}

QIecCfgChsComBoxDelegBase::~QIecCfgChsComBoxDelegBase()
{

}
QWidget *QIecCfgChsComBoxDelegBase::createEditor(QWidget *parent, const QStyleOptionViewItem &, 
												  const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return NULL;
	}

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if (pCurItem == NULL)
	{
		return NULL;
	}

	if (pCurItem->lParam == 0)
	{
		return NULL;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCurItem->lParam;
	CDataType* pDataType = (CDataType*)pVCellData->pExBaseList;

	if (pDataType != NULL)
	{
		QScrollComboBox *pComboBox = new QScrollComboBox(parent,FALSE);
#ifdef _PSX_QT_LINUX_//linux下需要特殊处理下
		pComboBox->SetIgnoreFirstHidePopup(true);
#endif
		return pComboBox;
	} 
	else
	{
		return new QLineEdit(parent);
	}
}
CIecCfgChsGridBase::CIecCfgChsGridBase(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_bRunning = FALSE;
	installEventFilter(this);
}

CIecCfgChsGridBase::~CIecCfgChsGridBase()
{

}

void CIecCfgChsGridBase::InitGrid()
{
	InitGridTitle();
	m_pChType_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(1,m_pChType_DelegBase);
	m_pChMap_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(2,m_pChMap_DelegBase);
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
//	AutoAdjColWidth();
	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgChsGridBase::InitGridTitle()
{
//	QExBaseListGridBase::InitGridTitle();
}

void CIecCfgChsGridBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
//	QExBaseListGridBase::ShowData(pData,nRow,bInsertRow);
}

CDataType* CIecCfgChsGridBase::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CIecCfgChsGridBase::slot_doubleClicked( int nRow,int nCol )
{
	GridDoubleClicked_ShowKeyBoard(nRow,nCol);
}

void CIecCfgChsGridBase::GridDoubleClicked_ShowKeyBoard(int nRow,int nCol)
{
	if (nCol != 0)
	{
		return;
	}

	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	QString strValue = pItem->text();
	GetEngWidgetBoard_DigitData(strValue, parentWidget()->parentWidget());
	pItem->setText(strValue);
}

void CIecCfgChsGridBase::UpdateSelectedState()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	DisConnectAll_SigSlot();
	CIecCfgDataChBase *pIecCfgCh = NULL;
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行

	while (pos != NULL)
	{
		pIecCfgCh = (CIecCfgDataChBase*)m_pDatas->GetNext(pos);
		Show_Check(pIecCfgCh,nRowIndex,0,&pIecCfgCh->m_nUseFlag);
		nRowIndex++;
	}

	ConnectAll_SigSlot();
}
bool CIecCfgChsGridBase::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent * pMouseEvent = (QMouseEvent*) event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent*)pMouseEvent);
		m_bRunning = FALSE;
		return true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);
}

// void CIecCfgChsGridBase::mousePressEvent(QMouseEvent *event)
// {
// 	if (m_bRunning)
// 	{
// 		QExBaseListGridBase::mousePressEvent(event);
// 		return;
// 	}
// 
// 	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
// 	QApplication::postEvent(this,pEvent);
// 	QExBaseListGridBase::mousePressEvent(event);
// }

void CIecCfgChsGridBase::OnDataSelChanged(int nRow, int nCol)
{
	QExBaseListGridBase::OnDataSelChanged(nRow,nCol);
}

void CIecCfgChsGridBase::UpdateChLength(CExBaseObject *pData, int& nRow, long nChLength, BOOL bInsertRow)
{
	//	QExBaseListGridBase::ShowData(pData,nRow,bInsertRow);
}

void CIecCfgChsGridBase::UpdateChLengths(CExBaseList *pDatas, long nChLength, BOOL bResetScrollBars)
{
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(0);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;		
	POS pos = pDatas->GetHeadPosition();
	DisConnectAll_SigSlot();
	int nRowIndex = 0;
	long nCalRows = GetDatasCount();
	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		UpdateChLength(pObj, nRowIndex, nChLength, FALSE);
	}
	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}
void CIecCfgChsGridBase::mouseReleaseEvent(QMouseEvent *event)
{
#ifdef _PSX_QT_LINUX_
	if (!IsScrollMoving())
#endif
	{
		QMouseEvent *pEvent0 = new QMouseEvent(QEvent::MouseButtonDblClick, event->pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
		QApplication::postEvent(this, pEvent0);
	}

	QExBaseListGridBase::mouseReleaseEvent(event);
}
