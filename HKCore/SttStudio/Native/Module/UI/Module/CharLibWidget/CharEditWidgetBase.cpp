#include "CharEditWidgetBase.h"
#include <QApplication>

QCharEditGridBase::QCharEditGridBase(QWidget* pParent) : QExBaseListGridBase(pParent)
{
	m_bRunning = FALSE;
	installEventFilter(this);
}

QCharEditGridBase::~QCharEditGridBase()
{
	m_oTestDataTypes.DeleteAll();
}

void QCharEditGridBase::InitGrid()
{
	InitGridTitle();
	InitDataTypes();
}

void QCharEditGridBase::InitGridTitle()
{

}

void QCharEditGridBase::InitDataTypes()
{

}

void QCharEditGridBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

}

void QCharEditGridBase::EmitCharChanged()
{
	emit sig_CharChanged(NULL);
}

void QCharEditGridBase::EndEditCell_String(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	if(*(pVCellData->pString) != pCell->text())
	{
		*(pVCellData->pString) = pCell->text();
		((QCharEditGridBase*)pGrid)->EmitCharChanged();
	}
}

void QCharEditGridBase::EndEditCell_Double(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	if(*(pVCellData->pdValue) != CString_To_double(pCell->text()))
	{
		*(pVCellData->pdValue) = CString_To_double(pCell->text());
		((QCharEditGridBase*)pGrid)->EmitCharChanged();
	}
}

void QCharEditGridBase::EndEditCell_Long(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pObj != NULL);
	if(*(pVCellData->pnValue) != CString_To_long(pCell->text()))
	{
		*(pVCellData->pnValue) = CString_To_long(pCell->text());
		((QCharEditGridBase*)pGrid)->EmitCharChanged();
	}
}

CDataType* QCharEditGridBase::FindTestDataType(const CString& strDataTypeID)
{
	CDataType *pDataType = NULL;
	pDataType = (CDataType*)m_oTestDataTypes.FindByID(strDataTypeID);
	return pDataType;
}

CDataType* QCharEditGridBase::FindDataType(const CString &strDataType)
{
	return FindTestDataType(strDataType);
}

bool QCharEditGridBase::eventFilter(QObject *obj, QEvent *event)
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

void QCharEditGridBase::mousePressEvent(QMouseEvent * event)
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



QCharEditWidgetBase::QCharEditWidgetBase()
{
	m_pCharEditWidget = NULL;
}

QCharEditWidgetBase::~QCharEditWidgetBase()
{
	
}

void QCharEditWidgetBase::DeleteCharEditWidget()
{
	if (m_pCharEditWidget != NULL)
	{
		delete m_pCharEditWidget;
		m_pCharEditWidget = NULL;
	}

	delete this;
}

void QCharEditWidgetBase::UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas)
{

}

