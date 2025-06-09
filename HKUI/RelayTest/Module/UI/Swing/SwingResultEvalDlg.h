#ifndef QSWINGRESULTEVALDLG_H
#define QSWINGRESULTEVALDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include "../../UI/Interface/SttMacroParaEditViewOriginal.h"
#include "../../SttTest/Common/Swing/tmt_swing_test.h"

#define SETTINGVAL_MIN 0
#define SETTINGVAL_MAX 999.999
#define TTRIPRELERR_MIN 0
#define TTRIPRELERR_MAX 100
#define TTRIPABSERR_MIN 0
#define TTRIPABSERR_MAX 200

namespace Ui {
class QSwingResultEvalDlg;
}

class QSwingResultEvalDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSwingResultEvalDlg(QWidget *parent = 0);
    ~QSwingResultEvalDlg();
    void InitUI();
	void UpdateParas();
    void SetDatas(CDataGroup *pParas);
    void GetDatas(CDataGroup *pParas);

public:
	CDataGroup *m_pCurrDataGroup;
    QTableWidgetItem *m_editSettingValue;
    QComboBox *m_pComboBox;
    QSettingItem *m_editRelErr;
    QSettingItem *m_editAbsErr;
    QSettingItem *m_editAbsErrNeg;
	tmt_SwingTest *m_pCurTest;

private slots:
    void on_m_btnOk_clicked();
    void on_m_btnCancel_clicked();
    void on_m_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::QSwingResultEvalDlg *ui;
};

#endif // QSWINGRESULTEVALDLG_H
