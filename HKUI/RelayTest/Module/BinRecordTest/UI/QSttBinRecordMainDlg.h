#ifndef QSTTBINRECORDMAINDIALOG_H
#define QSTTBINRECORDMAINDIALOG_H

#include <QDialog>
#include "ui_QSttBinRecordMainDlg.h"
#include "QSttBinRecordDlg.h"
#include "QSttBinRecordCbWidget.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"

class QSttBinRecordMainDlg : public QDialog
{
	Q_OBJECT

public:
    QSttBinRecordMainDlg(QWidget *parent = 0);
    virtual ~QSttBinRecordMainDlg();

	QSttBinRecordDlg *m_pBinRecordConfigWidget;//参数设置窗口
	QSttBinRecordCbWidget *m_pBinRecordCbWdiget;//数据显示窗口
	virtual void closeEvent(QCloseEvent *event);

	void UpdateCapDevice(CCapDeviceBase *pCapDevice);
	void ShowBinConfigWindow();
	void ShowBinRecordCbWindow();

signals:
	void sig_ShowBinConfigWindow();
	void sig_ShowBinRecordCbWindow();

	public slots:
	void on_ShowBinConfigWindow();
	void on_ShowBinRecordCbWindow();


private:
    Ui::QSttBinRecordMainDlg ui;
};
extern QSttBinRecordMainDlg *g_theSttBinRecordMainWidget;
#endif // QSTTBINRECORDMAINDIALOG_H
