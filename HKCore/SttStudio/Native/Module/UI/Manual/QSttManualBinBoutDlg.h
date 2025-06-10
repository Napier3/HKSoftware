#ifndef QINBINARYOUTDLG_H
#define QINBINARYOUTDLG_H

#include <QDialog>
#include "../Controls/SttLineEdit.h"
#include "../../SttTest/Common/tmt_manu_test.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"

namespace Ui {
class QSttManualBinBoutDlg;
}

class QSttManualBinBoutDlg : public QDialog
{
    Q_OBJECT

public:
	Ui::QSttManualBinBoutDlg *ui;
    explicit QSttManualBinBoutDlg(tmt_BinaryIn *pBinaryIn,tmt_BinaryOut *pBinaryOut,
		int	*pnBinLogic,float *pfTrigDelay,BOOL *pbAuto, QWidget *parent);
    ~QSttManualBinBoutDlg();
//	int m_nIsOK;

	
	tmt_BinaryIn *m_pBinaryIn;
	tmt_BinaryOut *m_pBinaryOut;
	int		*m_pnBinLogic;
	float *m_pfTrigDelay;
	BOOL *m_pbAuto;

public:
	void InitLanguage();
	void InitPara();
	void InitConnections();

	void slot_edit_changed(QSttLineEdit* pEditLine, long nType);

	void SetInBinaryOutSettingFont();
	void InitStyle();
	void slot_lne_delayedChanged();
	void DelayedSetVisible();

private slots:
	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
	void slot_ck_BinaryInStateChanged(int );

	void on_m_editDelayChanged();
	void on_m_editDelayed_editingFinished();

};

#endif // QINBINARYOUTDLG_H
