#ifndef _AuxModifyIPDlg_H_
#define _AuxModifyIPDlg_H_

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class QAuxModifyIPDlg: public QDialog
{
	Q_OBJECT

public:
	QAuxModifyIPDlg(QWidget *pParent = 0);
	virtual ~QAuxModifyIPDlg();

private:
	QLineEdit *m_pedtIP;
	QLineEdit *m_pedtSubNetMask;
	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;

private:
	void initUI();
	void initSignalSlots();

signals:
	void sig_ModifyTesterIP_OK(QString &strIP,const QString &strSubNetMask);

private slots:
	void slot_OKClicked();
	void slot_CancelClicked();

public:
	void InitParas(const QString &strIP,const QString &strSubNetMask = ("255.255.255.0"));
};


#endif