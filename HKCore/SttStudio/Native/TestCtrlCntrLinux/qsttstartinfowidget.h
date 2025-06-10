#ifndef QSTTSTARTINFOWIDGET_H
#define QSTTSTARTINFOWIDGET_H

#include <QWidget>
#include <QThread>

namespace Ui {
class QSttStartInfoWidget;
}

class QSttStartInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QSttStartInfoWidget(QWidget *parent = 0);
    ~QSttStartInfoWidget();

	void HideWidget();
	void SetInfor(const QString &strInfor);

private:
	QThread *m_pThread;

private:
    Ui::QSttStartInfoWidget *ui;

signals:
	void sig_ShowInfor(QString);

public slots:
	void slot_ShowInfor(QString strInfor);

};

class QSttStartInfoThread : public QThread
{
public:
	QSttStartInfoThread();
	virtual ~QSttStartInfoThread();

	bool m_bExitStart;
	QSttStartInfoWidget *m_pWidget;
protected:
	virtual void run();

};

#endif // QSTTSTARTINFOWIDGET_H
