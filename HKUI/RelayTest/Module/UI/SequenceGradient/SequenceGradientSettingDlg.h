#ifndef GRADIENTSETTINGDLG_H
#define GRADIENTSETTINGDLG_H

#include <QDialog>
#include "../Controls/SttLineEdit.h"
#include "../../SttTest/Common/Sequence/tmt_sequence_gradient_test.h"
#include "../../../../Module/OSInterface/OSInterface.h"
#define NUM_ZERO 0  //LCQ
#define NUM_ONE  1   //lCQ

namespace Ui {
	class QSequenceGradientSettingDlg;
}

class QSequenceGradientSettingDlg : public QDialog
{
	Q_OBJECT

public:
	Ui::QSequenceGradientSettingDlg *ui;

	explicit QSequenceGradientSettingDlg(tmt_GradientParasEx *pSequenceGradient, QWidget *parent);
	~QSequenceGradientSettingDlg();

	tmt_GradientParasEx *m_pSequenceGradientParas;
	int m_nIsOK;

public:
	void InitLanguage();
	void InitPara();
	void InitConnections();
	void SetSequenceGradientSettingFont();
	void InitStyle();
private slots:
	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
	void slot_ck_BinaryInStateChanged(int );
};

extern CFont *g_pSttGlobalFont;  

#endif // GRADIENTSETTINGDLG_H

