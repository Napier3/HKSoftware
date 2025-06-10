#include "QSttTestCtrlStartPrgsSvr.h"


QDBusConnection *m_connection;


QSttTestCtrlStartPrgsSvr::QSttTestCtrlStartPrgsSvr()
{
	m_pInforWidget = new QSttStartInfoWidget();
	m_pInforWidget->hide();
	m_connection = QDBusConnection::sessionBus();

	//��session bus��ע����Ϊcom.stt.test�ķ���
	if(! m_connection.registerService("com.stt.test"))
	{
		qDebug()<<m_connection.lastError().message();
	}

	m_connection.registerObject("/home/stt", m_pInforWidget, QDBusConnection::ExportAllSlots);
}

QSttTestCtrlStartPrgsSvr::~QSttTestCtrlStartPrgsSvr()
{
	delete m_pInforWidget;
}


long QSttTestCtrlStartPrgsSvr::g_nSttTestCtrlStartPrgsSvr = 0;
QSttTestCtrlStartPrgsSvr* QSttTestCtrlStartPrgsSvr::g_pQSttTestCtrlStartPrgsSvr = NULL;
	
void QSttTestCtrlStartPrgsSvr::Create()
{
	g_nSttTestCtrlStartPrgsSvr++;

	if (g_nSttTestCtrlStartPrgsSvr == 1)
	{
		g_pQSttTestCtrlStartPrgsSvr = new QSttTestCtrlStartPrgsSvr();
	}
}

void QSttTestCtrlStartPrgsSvr::Release()
{
	g_nSttTestCtrlStartPrgsSvr--;

	if (g_nSttTestCtrlStartPrgsSvr == 0)
	{
		delete g_pQSttTestCtrlStartPrgsSvr;
	}
}

