#ifndef QSttTestCtrlStartPrgsSvr_H
#define QSttTestCtrlStartPrgsSvr_H

#include "qsttstartinfowidget.h"

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusError>

class QSttTestCtrlStartPrgsSvr
{
private:
	explicit QSttTestCtrlStartPrgsSvr();
	~QSttTestCtrlStartPrgsSvr();

	static long g_nSttTestCtrlStartPrgsSvr;
	static QSttTestCtrlStartPrgsSvr *g_pQSttTestCtrlStartPrgsSvr;
	
private:
	QDBusConnection m_connection;
	QSttStartInfoWidget *m_pInforWidget;

public:
	static void Create();
	static void Release();
};

#endif // QSttTestCtrlStartPrgsSvr_H
