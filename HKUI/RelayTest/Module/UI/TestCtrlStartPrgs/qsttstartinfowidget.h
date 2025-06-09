#ifndef QSTTSTARTINFOWIDGET_H
#define QSTTSTARTINFOWIDGET_H

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusError>

#include "QSttTestCtrlStartPrgsDefine.h"
#include <QWidget>

namespace Ui {
class QSttStartInfoWidget;
}

class QSttStartInfoWidget : public QWidget
{
    Q_OBJECT
	Q_CLASSINFO("D-Bus Interface", "com.stt.test.showinfor")
	Q_CLASSINFO("D-Bus Interface",   "com.stt.test.setsteps")
	Q_CLASSINFO("D-Bus Interface",   "com.stt.test.step")

public:
    explicit QSttStartInfoWidget(QWidget *parent = 0);
    ~QSttStartInfoWidget();

signals:
	void sig_ShowInfor(QString);

public slots:
	void slot_ShowInfor(QString strInfor);
	void slot_SetSteps(long nSteps);
	void slot_Steps(long nStep);
	void slot_Finish(long nStep);

};


#endif // QSTTSTARTINFOWIDGET_H
