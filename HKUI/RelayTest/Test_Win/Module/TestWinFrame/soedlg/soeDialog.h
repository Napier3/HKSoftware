#ifndef SOEDIALOG_H
#define SOEDIALOG_H

#include <QDialog>
#include <QAction>
#include <QToolBar>
#include <QTimer>
#include "ui_soeDialog.h"
#include "../../Module/SttTest/Common/tmt_soe_test.h"

#define STARTTYPE_IMMED		0		//开始实触发  
#define STARTTYPE_GPS		1		//GPS触发

class SoeDialog : public QDialog
{
	Q_OBJECT

public:
	SoeDialog();
	~SoeDialog();

	void initUI();
	void setData(tmt_SoeParas* pSoeParas);

	bool eventFilter(QObject *,QEvent *);

private:
	Ui::SoeDialog ui;
	
	QIntValidator* validator;
	QIntValidator* validatorCount;

	QAction *m_startAct;
	QAction *m_stopAct;
	QAction *m_saveAct;
	QToolBar *m_headerToolBar;

	QTimer *m_pTimer;
	bool    m_bInit;

signals:
	void sig_SoeStartClicked();
	void sig_SoeStopClicked();	//停止测试或超时
	void sig_SoeParasSave();

public:
	tmt_SoeParas*  m_pSoeParas;

	bool isGPSTrig();
	bool isImmedTrig();

	void OnViewStartState(bool bStart);
	void OnViewStopState(bool bStop);

	int getCurrentIndex(unsigned int nHoldTime);
	int getCurrentHoldTime(int nTimeIdx);
        void InitLanguage();
public slots:
	void startTest();
	void stopTest();
	void saveConfig();
	void changeTestType(int nType);
	void savecheckSate(int nState);
	void changeHoldTime(int nTimeIdx);
};

#endif