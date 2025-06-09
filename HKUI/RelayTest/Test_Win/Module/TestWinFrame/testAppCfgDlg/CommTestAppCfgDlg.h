#ifndef _CommTestAppCfgDlg_H_
#define _CommTestAppCfgDlg_H_

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>


class CCommTestAppCfgDlg : public QDialog
{
	Q_OBJECT

public:
	CCommTestAppCfgDlg(QWidget *pParent = 0);
	~CCommTestAppCfgDlg();

private:
	QLabel *m_plb1;
	QLabel *m_plb2;
	QLineEdit *m_pedtIP;
	QLineEdit *m_pedtPort;
	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;

private:
	void initUI();
	void initSignalSlots();
	void keyPressEvent(QKeyEvent *event);

signals:
	void sig_CommCfgOK(QString &strIP,long nPort);

private slots:
	void slot_OKClicked();
	void slot_CancelClicked();

public:
	void InitParas(const QString &strIP,long nPort);
};


#endif