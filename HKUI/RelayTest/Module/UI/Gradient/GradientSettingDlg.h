#ifndef GRADIENTSETTINGDLG_H
#define GRADIENTSETTINGDLG_H

#include <QDialog>
#include "../Controls/SttLineEdit.h"
#include "../../SttTest/Common/tmt_gradient_test.h"
#define NUM_ZERO 0  //LCQ
#define NUM_ONE  1   //lCQ

namespace Ui {
class QGradientSettingDlg;
}

class QGradientSettingDlg : public QDialog
{
	Q_OBJECT

public:
	Ui::QGradientSettingDlg *ui;

	explicit QGradientSettingDlg(tmt_GradientParasEx *pGradientParas, QWidget *parent);
	~QGradientSettingDlg();

	tmt_GradientParasEx *m_pGradientParas;
	int  m_nIsOK;

public:
	void InitLanguage();
	void InitPara();
	void InitConnections();

	void slot_edit_changed(QSttLineEdit* pEditLine, long nType);

	void SetGradientSettingFont();
	void InitStyle();

private slots:
	//void on_m_editTimeBeforeChangeChanged();
	//void on_m_editTimeBeforeFailChanged();
	//void on_m_editCurBeforeChangeChanged();
	//void on_m_editPhaseChanged();

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();

	//void on_m_editTimeBeforeChange_clicked();
	//void on_m_editTimeBeforeFail_clicked();
	//void on_m_editCurBeforeChange_clicked();
	//void on_m_editPhase_clicked();
	void slot_ck_BinaryInStateChanged(int );
};

extern CFont *g_pSttGlobalFont;  

#endif // GRADIENTSETTINGDLG_H
