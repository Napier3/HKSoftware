#ifndef _Stt_Aux_IP_SetDlg_H_
#define _Stt_Aux_IP_SetDlg_H_

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include "../../Controls/SttLineEdit.h"


class QSttAuxIPSetDlg : public QDialog
{
	Q_OBJECT

public:
	QSttAuxIPSetDlg(QWidget *pParent = 0);
	~QSttAuxIPSetDlg();
	QString GetCurrIP();

private:
	QLabel *m_pIP_QLabel;
	QSttLineEdit *m_pIP_QLineEdit;
	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;

private:
	void initUI();
	void initSignalSlots();
	void keyPressEvent(QKeyEvent *event);

signals:
//	void sig_CommCfgOK(QString &strIP,long nPort);

private slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_IP_Changed();

public:
	void InitParas(const QString &strIP);
};


#endif