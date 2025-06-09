#include "qnetworkiptable.h"

#include <QApplication>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../SttGlobalDef.h"
#include "../../../../61850/Module/XLanguageResourcePp_Mms.h"


QNetworkIpTable::QNetworkIpTable(QWidget *parent)
	: QExBaseListGridBase(parent)
{
	m_bRunning = false;
	installEventFilter(this);

	InitGrid();

}

QNetworkIpTable::~QNetworkIpTable()
{
	
}

void QNetworkIpTable::InitGrid()
{
	InitGridTitle();
	SetDefaultRowHeight(50);
}


void QNetworkIpTable::InitGridTitle()
{
	CString astrGridTitle[2] = {g_sLangTxt_IpAddr,g_sLangTxt_SubNetwMask };
	int iWidth[2]={200, 200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iWidth, 2);
}

void QNetworkIpTable::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	CDataGroup *p = (CDataGroup *)pData;
	CString strVal = _T("");

	CDataGroup *pGroup = (CDataGroup *)p->FindByID(STT_SYS_DATA_ID_DeviceIP);

	if (pGroup != NULL)
	{
		stt_GetDataValueByID(pGroup, STT_SYS_DATA_ID_IP, strVal);
	}
	else
	{
		strVal = _T("");
	}

	Show_StaticString(p, nRow, 0, &strVal);

	if (pGroup != NULL)
	{
		stt_GetDataValueByID(pGroup, STT_SYS_DATA_ID_mask, strVal);
	}
	else
	{
		strVal = _T("");
	}
	Show_StaticString(p, nRow, 1, &strVal);	

	nRow++;
}

bool QNetworkIpTable::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = true;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = false;
		return  true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);

}

void QNetworkIpTable::mousePressEvent(QMouseEvent * event)
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
