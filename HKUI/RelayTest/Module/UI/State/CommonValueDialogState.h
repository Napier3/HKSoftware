#ifndef COMMONVALUEDIALOGSTATE_H
#define COMMONVALUEDIALOGSTATE_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QFrame>
#include "ui_CommonValueDialogState.h"
#include "../../Module/SttTest/Common/tmt_state_test.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "SttMacroParaEditViewState.h"

namespace Ui {
	class CommonValueDialogState;
}

class CommonValueDialogState : public QDialog
{
	Q_OBJECT

public:
	Ui::CommonValueDialogState *ui;

	CommonValueDialogState(tmt_StateParas* pSateParas,QWidget *parent = 0);
	~CommonValueDialogState();
	
	void closeEvent(QCloseEvent *event);
	
signals:
	void sig_CommonValueOkClicked();
	void sig_DcCoffsetStateChanged();

private slots:
	void slot_OkClicked();
	void slot_CancelClicked();
	
	void slot_lne_TouChanged();
	void slot_lne_TouKeyBoard();
	void slot_lne_RepeatTimeChanged();
	void slot_lne_RepeatTimeKeyBoard();
	void slot_cmb_DCOFFSETChanged(int index);
	
private:
	void initUI();
	void initConnections();
	void initBaseData();
	void initPara();
	void SetCommonValueDialogStateFont();

public:
	QScrollComboBox *m_pCmb_DCOFFSET;
	QScrollComboBox *m_pCmb_JudgeCondition;
	QLabel *m_pDCOFFSETLabel;
	QLabel *m_pJudgeConditionLabel;
	QLabel *m_pRepeatTimeLabel;
	QLabel *m_pTouLabel;
	QSttLineEdit *m_pRepeatTimeEdit;
	QSttLineEdit *m_pTouEdit;
	QSpacerItem *m_pVerticalSpacer;
	QFrame *m_pLine;
	QPushButton *m_pbn_Ok;
	QPushButton *m_pbn_Cancel;

	QStringList m_listJudgeConditions;
	QStringList m_listDcOffSets;

public:
	tmt_StateParas* m_pSateParas;	
	int m_nIsOK;
};

#endif // COMMONVALUEDIALOG_H
