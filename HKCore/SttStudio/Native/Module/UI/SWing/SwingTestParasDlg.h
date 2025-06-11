#ifndef QSWINGTESTPARASDLG_H
#define QSWINGTESTPARASDLG_H

#include <QDialog>
#include "../../UI/Interface/SttMacroParaEditViewOriginal.h"
#include "../../SttTest/Common/Swing/tmt_swing_test.h"

#define PREFAULTTIME_MIN 0
#define PREFAULTTIME_MAX 999999
#define IMPSYS_MIN 0
#define IMPSYS_MAX 999999
#define IMPSYSPH_MIN 0
#define IMPSYSPH_MAX 360
#define IMPTF_MIN 0
#define IMPTF_MAX 999999
#define IMPTFPH_MIN 0
#define IMPTFPH_MAX 360
#define IMPTS_MIN 0
#define IMPTS_MAX 999999

namespace Ui {
class QSwingTestParasDlg;
}

class QSwingTestParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSwingTestParasDlg(QWidget *parent = 0);
    ~QSwingTestParasDlg();
    void InitUI();
	void UpdateParas();
	void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);
	virtual void InitLanuage();
public:
	CDataGroup *m_pCurrDataGroup;
	tmt_SwingTest *m_pCurTest;

private slots:
    void on_m_btnOk_clicked();
    void on_m_btnCancel_clicked();

    void on_m_editPreFaultTime_editingFinished();

    void on_m_editImpSys_editingFinished();

    void on_m_editImpSysPh_editingFinished();

    void on_m_editImpTf_editingFinished();

    void on_m_editImpTfPh_editingFinished();

    void on_m_editImpTs_editingFinished();

private:
    Ui::QSwingTestParasDlg *ui;

signals:
	void sig_DataChanged();
};

#endif // QSWINGTESTPARASDLG_H
