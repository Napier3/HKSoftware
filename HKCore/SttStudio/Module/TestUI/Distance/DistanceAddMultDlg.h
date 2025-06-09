#ifndef DISTANCEADDMULTDLG_H
#define DISTANCEADDMULTDLG_H

#include <QDialog>
#include "../../UI/SttTestCntrFrameBase.h"
#include "./DistanceResultEstimateDlg.h"
#include "./SttMultiMacroDistanceParasDefine.h"
namespace Ui {
class QDistanceAddMultDlg;
}
#define TIPS_DISPLAY_TIME	3000
class QDistanceAddMultDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceAddMultDlg(QWidget *parent = 0);
    ~QDistanceAddMultDlg();

private slots:

    void on_m_btnSave_clicked();
    void on_m_btnClose_clicked();

    void on_m_txtZSetingLN1_editingFinished();
    void on_m_txtZSetingLN2_editingFinished();
    void on_m_txtZSetingLN3_editingFinished();
    void on_m_txtZSetingLN4_editingFinished();

    void on_m_txtZSetingLL1_editingFinished();
    void on_m_txtZSetingLL2_editingFinished();
    void on_m_txtZSetingLL3_editingFinished();
    void on_m_txtZSetingLL4_editingFinished();

    void on_m_txtTSetingLN1_editingFinished();
    void on_m_txtTSetingLN2_editingFinished();
    void on_m_txtTSetingLN3_editingFinished();
    void on_m_txtTSetingLN4_editingFinished();

    void on_m_txtTSetingLL1_editingFinished();
    void on_m_txtTSetingLL2_editingFinished();
    void on_m_txtTSetingLL3_editingFinished();
    void on_m_txtTSetingLL4_editingFinished();

	void on_m_txtPreFaultTime_editingFinished();
	void on_m_txtFaultTime_editingFinished();
	void on_m_txtFaultAngle_editingFinished();
	void on_m_txtFaultCur_editingFinished();

	void on_m_txtRate_100_editingFinished();
	void on_m_cmbK0Mode_currentIndexChanged(int index);
	void on_m_txtK0_editingFinished();
	void on_m_txtPhi_editingFinished();

	void on_m_checkLNZone1_clicked(bool checked);
    void on_m_checkLNZone2_stateChanged(int arg1);
    void on_m_checkLNZone3_stateChanged(int arg1);
    void on_m_checkLNZone4_stateChanged(int arg1);
    void on_m_checkLLZone1_stateChanged(int arg1);
    void on_m_checkLLZone2_stateChanged(int arg1);
    void on_m_checkLLZone3_stateChanged(int arg1);
    void on_m_checkLLZone4_stateChanged(int arg1);

    void on_m_checkFaultTypeA_N1_clicked(bool checked);
    void on_m_checkFaultTypeB_N1_stateChanged(int arg1);
    void on_m_checkFaultTypeC_N1_stateChanged(int arg1);
    void on_m_checkFaultTypeABC_N1_stateChanged(int arg1);

    void on_m_checkFaultTypeA_N2_clicked(bool checked);
    void on_m_checkFaultTypeB_N2_stateChanged(int arg1);
    void on_m_checkFaultTypeC_N2_stateChanged(int arg1);
    void on_m_checkFaultTypeABC_N2_stateChanged(int arg1);

    void on_m_checkFaultTypeA_N3_clicked(bool checked);
    void on_m_checkFaultTypeB_N3_stateChanged(int arg1);
    void on_m_checkFaultTypeC_N3_stateChanged(int arg1);
    void on_m_checkFaultTypeABC_N3_stateChanged(int arg1);

    void on_m_checkFaultTypeA_N4_clicked(bool checked);
    void on_m_checkFaultTypeB_N4_stateChanged(int arg1);
    void on_m_checkFaultTypeC_N4_stateChanged(int arg1);
    void on_m_checkFaultTypeABC_N4_stateChanged(int arg1);

    void on_m_checkFaultTypeA_L1_clicked(bool checked);
    void on_m_checkFaultTypeB_L1_stateChanged(int arg1);
    void on_m_checkFaultTypeC_L1_stateChanged(int arg1);
    void on_m_checkFaultTypeABC_L1_stateChanged(int arg1);

    void on_m_checkFaultTypeA_L2_clicked(bool checked);
    void on_m_checkFaultTypeB_L2_stateChanged(int arg1);
    void on_m_checkFaultTypeC_L2_stateChanged(int arg1);
    void on_m_checkFaultTypeABC_L2_stateChanged(int arg1);

    void on_m_checkFaultTypeA_L3_clicked(bool checked);
    void on_m_checkFaultTypeB_L3_stateChanged(int arg1);
    void on_m_checkFaultTypeC_L3_stateChanged(int arg1);
    void on_m_checkFaultTypeABC_L3_stateChanged(int arg1);

    void on_m_checkFaultTypeA_L4_clicked(bool checked);
    void on_m_checkFaultTypeB_L4_stateChanged(int arg1);
    void on_m_checkFaultTypeC_L4_stateChanged(int arg1);
    void on_m_checkFaultTypeABC_L4_stateChanged(int arg1);

    void on_m_checkRate_105_clicked(bool checked);
    void on_m_checkRate_095_stateChanged(int arg1);
    void on_m_checkRate_070_stateChanged(int arg1);
	void on_m_checkRate_100_stateChanged(int arg1);

	void on_m_btnResEvaluat_clicked();
	void on_m_cmb_RSC_currentIndexChanged(int index);

	void on_m_txtZAngLN1_editingFinished();
	void on_m_txtZAngLN2_editingFinished();
	void on_m_txtZAngLN3_editingFinished();
	void on_m_txtZAngLN4_editingFinished();
	void on_m_txtZAngLL1_editingFinished();
	void on_m_txtZAngLL2_editingFinished();
	void on_m_txtZAngLL3_editingFinished();
	void on_m_txtZAngLL4_editingFinished();

private:
    Ui::QDistanceAddMultDlg *m_pAddMult_UI;

	CDataGroup* m_pDistanceparas;//距离保护参数数据
	int m_nTipsTime;//页面提示计时ID

	void SetValueToPage(CDvmData *pData);
	void GetPageToValue(CDvmData *pData);
	void InitUI();
	void InitFont();

	CString CheckDataMinMax(CString strValue,CString strID,float nMax,float nMin,int nAfterPoint);
	CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
	void SetModeText(int nIndex);

	void CheckFaultTypeN1();
	void CheckFaultTypeN2();
	void CheckFaultTypeN3();
	void CheckFaultTypeN4();
	void CheckFaultTypeL1();
	void CheckFaultTypeL2();
	void CheckFaultTypeL3();
	void CheckFaultTypeL4();
	void SetApplyTips(CString strTips);
	void timerEvent(QTimerEvent* ev);

	void setLNZone1(bool bState);
	void setLNZone2(bool bState);
	void setLNZone3(bool bState);
	void setLNZone4(bool bState);
	void setLLZone1(bool bState);
	void setLLZone2(bool bState);
	void setLLZone3(bool bState);
	void setLLZone4(bool bState);
	bool CheckSectionState();

    bool CheckSelMultipleState();
public:
	CDataGroup* OpenDisTanceParasFile(const CString& strParasFile);
	void GetDatas(CDataGroup *pParas);
	void SetDatas(CDataGroup *pParas);

};

#endif // DISTANCEADDMULTDLG_H
