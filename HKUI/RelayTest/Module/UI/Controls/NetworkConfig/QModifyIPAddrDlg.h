#ifndef _QModifyIPAddrDlg_H_
#define _QModifyIPAddrDlg_H_

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>

class QModifyIPAddrDlg : public QDialog
{
	Q_OBJECT

public:
	QModifyIPAddrDlg(QWidget *pParent = 0);
	~QModifyIPAddrDlg();

private:
	QLabel *m_plbTesterModel;
	QLabel *m_plbTesterSN;
	QLabel *m_plbServerIP;
	QLabel *m_plbSubNetMask;
	QLineEdit *m_pedtTesterModel;
	QLineEdit *m_pedtTesterSN;
	QLineEdit *m_pedtIP;
	QLineEdit *m_pedtSubNetMask;
	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;

private:
	void initUI();
	void initSignalSlots();
	void keyPressEvent(QKeyEvent *event);

signals:
	void sig_ModifyTesterIP_OK(QString &strIP,const QString &strSubNetMask);

private slots:
	void slot_OKClicked();
	void slot_CancelClicked();

public:
	void InitParas(const QString &strModel,const QString &strSN,const QString &strIP,const QString &strSubNetMask = ("255.255.255.0"));
};


#endif