#ifndef _CDcSetDlg_H_
#define _CDcSetDlg_H_

#include "../Module/TestWinFrame/channelparaset/paratab.h"
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDataStream>


class CDcSetDlg : public QDialog
{
	Q_OBJECT

public:
	CDcSetDlg(QWidget *pParent = 0);
	~CDcSetDlg();

private:
	ParaTab* m_pParaTab;
	QParaSetBase* m_pSyncParaSet; //同步资源表
	QLabel *m_plbDcValue;
	QLineEdit *m_pedtDcValue;
	QPushButton *m_pbtnDCStart;
	QPushButton *m_pbtnDCEnd;
	QPushButton *m_pbtnACStart;
	QPushButton *m_pbtnACEnd;

	QVBoxLayout *m_pMainLayout;

	bool m_bDCStarted;
	bool m_bACStarted;

private:
	void initUI();
	void initSignalSlots();
	void keyPressEvent(QKeyEvent *event);

signals:
	void sig_DCStartClicked();
	void sig_DCEndClicked();
	void sig_ACStartClicked();
	void sig_ACEndClicked();

public slots:
	void slot_DCStartClicked();
	void slot_DCEndClicked();
	void slot_ACStartClicked();
	void slot_ACEndClicked();

public:
	void setData(bool bACStarted,bool bDCStarted);
	void setAusDCOutputState(bool bACStarted,bool bDCStarted);
};

#endif