#ifndef COMMONVALUEDIALOGOFSTATUS_H
#define COMMONVALUEDIALOGOFSTATUS_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QStringList>
#include "..\..\..\..\Module\SttTest\Common\tmt_state_test.h"
#include "..\..\Define.h"
#include "ui_CommonValueDialogOfStatus.h"
class CommonValueDialogOfStatus : public QDialog
{
	Q_OBJECT

public:
	CommonValueDialogOfStatus(tmt_StateParas* pSateParas,QWidget *parent = 0);
	~CommonValueDialogOfStatus();
	
	void keyPressEvent(QKeyEvent *event);
	
	void closeEvent(QCloseEvent *event);
	int m_nIsOK;//判断点击的是OK还是取消

signals:
	void sig_CommonValueOkClicked();

private slots:
	void slot_OkClicked();
	void slot_CancelClicked();
	
	void slot_lne_TouChanged();
	void slot_lne_RepeatTimeChanged();
	void slot_cmb_DCOFFSETChanged(int index);
	
private:
	void initConnections();
        void InitLanguage();
	void initPara();
	void init();
	QStringList m_JudgeConditionList;
	QStringList m_DCOFFSETList;

	Ui::CommonValueDialogOfStatus ui;
public:
	AppType m_nTypeApp;
	tmt_StateParas* m_pSateParas;	
};

#endif // COMMONVALUEDIALOG_H
