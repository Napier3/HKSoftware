#ifndef GradientSetDlg_H_
#define GradientSetDlg_H_

#include "ui_GradientSetDlg.h"
#include "gradientparatab.h"
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
#include "../../Module/SttTest/Common/tmt_state_test.h"
#include "../../Module/UI/Controls/SttLineEdit.h"

namespace Ui {
	class GradientSetDlg;
}

class GradientSetDlg : public QDialog
{
	Q_OBJECT

public:
	Ui::GradientSetDlg *ui;

	explicit GradientSetDlg(QWidget *pParent = 0);
	~GradientSetDlg();

private:
	GradientParaTab* m_pParaTab;
	
	QLabel *m_plblStepTime;
	QSttLineEdit *m_pedtStepTime;

	QRadioButton *m_pbtnLinear;
	QRadioButton *m_pbtnStep;

	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;
	
	QVBoxLayout *m_pMainLayout;

	void AddPushButton(QPushButton** ppBtn,QString strName,int nFontSize);
	void AddRadioButton(QRadioButton** ppBtn,QString strName,int nFontSize);
	void AddLabel(QLabel** ppLabel,QString strName,int nFontSize);

private:
	void initUI();
	void initConnections();
	void SetGradientParaFont();

signals:
	void sig_OkClicked();
	void sig_CancelClicked();

public slots:
	void slot_GradientLinearClicked();
	void slot_GradientStepClicked();
	void slot_StepTimeChanged();
	void slot_StepTimeKeyBoard();
	void slot_OKClicked();
	void slot_CancelClicked();

public:
	int m_nScreenWidth,m_nScreenHeight;

	int  m_nIsOK;
	tmt_StatePara* m_pStatePara;
	void setData(CSttTestResourceBase *pSttTestResource,tmt_StatePara* pStatePara);

	tmt_StatePara m_tmpStatePara;
	void copyTmpStatePara(bool b=true);

	void saveTmpData();

	void updateGradientType(int nType);
	void setGradientType(int nType);

	void closeEvent(QCloseEvent *event);
};

#endif