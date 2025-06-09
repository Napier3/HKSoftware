#ifndef ACTIONTIMEADDMULTDLG_H
#define ACTIONTIMEADDMULTDLG_H

#include <QDialog>
#include <QRadioButton>

#include "ActionTimeBinarySignalDlg.h"
#include "ActionTimeResultEvalDlg.h"
#include <QRadioButton>
#include "SttMultiMacroActionTimeParasDefine.h"

namespace Ui {
	class QActionTimeAddMultDlg;
}

class QActionTimeAddMultDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QActionTimeAddMultDlg(QWidget *parent = 0);
	~QActionTimeAddMultDlg();
	void InitUI();
    void InitConnect();
	void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);

private:
    void SetValueToPage(CDvmData *pData);
    void GetPageToValue(CDvmData *pData);
    void CheckAllPresence();

private:
	Ui::QActionTimeAddMultDlg *ui;
	QCheckBox *m_cbLN;  //单相接地短路
    QLineEdit *m_editLNVol;
	QRadioButton *m_rbLNFaultVolShort;  //短路电压
	QRadioButton *m_rbLNFaultVolZero;  //零序电压
    QCheckBox *m_cbLNAN;  //单相AN
    QCheckBox *m_cbLNBN;  //单相BN
    QCheckBox *m_cbLNCN;  //单相CN

	QCheckBox *m_cbLL;  //相间短路
    QLineEdit *m_editLLVol;
	QRadioButton *m_rbLLFaultVolShort;  //短路电压
    QRadioButton *m_rbLLFaultVolNeg;  //负序电压
    QCheckBox *m_cbLLAB;  //相间AB
    QCheckBox *m_cbLLBC;  //相间BC
    QCheckBox *m_cbLLCA;  //相间CA

	QCheckBox *m_cbThreePhase;  //三相短路
	QCheckBox *m_cbI0;  //零序电流
    QCheckBox *m_cbI2;  //负序电流
	QCheckBox *m_cbThreeParallel;  //三相电流并联

    QLineEdit *m_editThreePhaseVol;  //三相短路故障电压
    QLineEdit *m_editI0Vol;     //零序电流故障电压
    QLineEdit *m_editI2Vol;      //负序电流故障电压

    int m_nInputWidgetWidth;     //20240802 wanmj lineEdit和comboBox固定宽度

public:
    CDataGroup *m_pCurrDataGroup;

private slots:
    void on_m_btnOk_clicked();
    void on_m_btnCancel_clicked();
    void on_LN_Check_StateChanged(int state);
    void on_LL_Check_StateChanged(int state);
    void on_ThreePhase_Check_StateChanged(int state);
    void on_I0_Check_StateChanged(int state);
    void on_I2_Check_StateChanged(int state);
    void on_TestCheck_StateChanged();
    void on_m_editSettingTime_editingFinished();
    void on_m_editFaultCurrent_editingFinished();
    void on_m_editFaultAngle_editingFinished();
    void on_m_editLNVol_editingFinished();
    void on_m_editLLVol_editingFinished();
    void on_m_editThreePhaseVol_editingFinished();
    void on_m_editI0Vol_editingFinished();
    void on_m_editI2Vol_editingFinished();
    void on_m_editRelErr_editingFinished();
    void on_m_editAbsErrPos_editingFinished();
    void on_m_editAbsErrNeg_editingFinished();
};

#endif //ACTIONTIMEWIDGET_H
