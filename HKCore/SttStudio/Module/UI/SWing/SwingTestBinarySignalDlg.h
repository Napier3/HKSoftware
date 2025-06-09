#ifndef QSWINGTESTBINARYSIGNALDLG_H
#define QSWINGTESTBINARYSIGNALDLG_H

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
class QSwingTestBinarySignalDlg;
}

class QSwingTestBinarySignalDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSwingTestBinarySignalDlg(QWidget *parent = 0);
    ~QSwingTestBinarySignalDlg();
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

private:
    Ui::QSwingTestBinarySignalDlg *ui;

signals:
	void sig_DataChanged();
};

#endif // QSWINGTESTBINARYSIGNALDLG_H
