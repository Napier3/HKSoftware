#include "SttAuxIPSetGrid.h"
#include <QApplication>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../SttGlobalDef.h"
#include "../../../../61850/Module/XLanguageResourcePp_Mms.h"


QSttAuxIPSetGrid::QSttAuxIPSetGrid(QWidget *parent)
	: QExBaseListGridBase(parent)
{
	m_bRunning = false;
	installEventFilter(this);
	InitGrid();
}

QSttAuxIPSetGrid::~QSttAuxIPSetGrid()
{
	
}

void QSttAuxIPSetGrid::InitGrid()
{
	InitGridTitle();
	SetEditable(FALSE);
}


void QSttAuxIPSetGrid::InitGridTitle()
{
	CString astrGridTitle[2] = {_T("¸¨ÖúIPµØÖ·"),_T("×ÓÍøÑÚÂë") };
	int iWidth[2]={250, 250};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iWidth, 2);
}

void QSttAuxIPSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	CDataGroup *pDataGroup = (CDataGroup *)pData;

	if (pDataGroup == NULL)
	{
		return;
	}

	CString strVal = _T("");
	stt_GetDataValueByID(pDataGroup, STT_SYS_DATA_ID_IP, strVal);
	Show_StaticString(pDataGroup, nRow, 0, &strVal);

	stt_GetDataValueByID(pDataGroup, STT_SYS_DATA_ID_Mask, strVal);
	Show_StaticString(pDataGroup, nRow, 1, &strVal);	

	nRow++;
}


bool QSttAuxIPSetGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = true;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = false;
		return true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);
}

void QSttAuxIPSetGrid::mousePressEvent(QMouseEvent * event)
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

