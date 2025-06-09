#ifndef DISTANCEADDMULTDLG_H
#define DISTANCEADDMULTDLG_H

#include "DistanceAddMultBase.h"
namespace Ui {
class QDistanceAddMultDlg;
}
class QDistanceAddMultDlg : public QDistanceAddMultBase
{
    Q_OBJECT

public:
    explicit QDistanceAddMultDlg(QWidget *parent = 0);
    virtual ~QDistanceAddMultDlg();

private slots:

    void on_m_btnSave_clicked();
    void on_m_btnClose_clicked();

    void on_m_txtZSetingLN1_editingFinished();
    void on_m_txtZSetingLN2_editingFinished();
    void on_m_txtZSetingLN3_editingFinished();
    void on_m_txtZSetingLN4_editingFinished();
	void on_m_txtZSetingLN5_editingFinished();

    void on_m_txtZSetingLL1_editingFinished();
    void on_m_txtZSetingLL2_editingFinished();
    void on_m_txtZSetingLL3_editingFinished();
    void on_m_txtZSetingLL4_editingFinished();
	void on_m_txtZSetingLL5_editingFinished();

    void on_m_txtTSetingLN1_editingFinished();
    void on_m_txtTSetingLN2_editingFinished();
    void on_m_txtTSetingLN3_editingFinished();
    void on_m_txtTSetingLN4_editingFinished();
	void on_m_txtTSetingLN5_editingFinished();

    void on_m_txtTSetingLL1_editingFinished();
    void on_m_txtTSetingLL2_editingFinished();
    void on_m_txtTSetingLL3_editingFinished();
    void on_m_txtTSetingLL4_editingFinished();
	void on_m_txtTSetingLL5_editingFinished();

	void on_m_txtFaultCur_editingFinished();
	void on_m_txtRate_100_editingFinished();
	void on_m_cmbK0Mode_currentIndexChanged(int index);
	void on_m_txtK0_editingFinished();
	void on_m_txtPhi_editingFinished();

	void on_m_checkLNZone1_clicked(bool checked);
	void on_m_checkLNZone2_clicked(bool checked);
	void on_m_checkLNZone3_clicked(bool checked);
	void on_m_checkLNZone4_clicked(bool checked);
	void on_m_checkLNZone5_clicked(bool checked);

	void on_m_checkLLZone1_clicked(bool checked);
	void on_m_checkLLZone2_clicked(bool checked);
	void on_m_checkLLZone3_clicked(bool checked);
	void on_m_checkLLZone4_clicked(bool checked);
	void on_m_checkLLZone5_clicked(bool checked);

    void on_m_checkFaultTypeA_N1_clicked(bool checked);
    void on_m_checkFaultTypeB_N1_stateChanged(int arg1);
    void on_m_checkFaultTypeC_N1_stateChanged(int arg1);

    void on_m_checkFaultTypeA_N2_clicked(bool checked);
    void on_m_checkFaultTypeB_N2_stateChanged(int arg1);
    void on_m_checkFaultTypeC_N2_stateChanged(int arg1);

    void on_m_checkFaultTypeA_N3_clicked(bool checked);
    void on_m_checkFaultTypeB_N3_stateChanged(int arg1);
    void on_m_checkFaultTypeC_N3_stateChanged(int arg1);

    void on_m_checkFaultTypeA_N4_clicked(bool checked);
    void on_m_checkFaultTypeB_N4_stateChanged(int arg1);
    void on_m_checkFaultTypeC_N4_stateChanged(int arg1);

	void on_m_checkFaultTypeA_N5_clicked(bool checked);
	void on_m_checkFaultTypeB_N5_stateChanged(int arg1);
	void on_m_checkFaultTypeC_N5_stateChanged(int arg1);

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

	void on_m_checkFaultTypeA_L5_clicked(bool checked);
	void on_m_checkFaultTypeB_L5_stateChanged(int arg1);
	void on_m_checkFaultTypeC_L5_stateChanged(int arg1);
	void on_m_checkFaultTypeABC_L5_stateChanged(int arg1);

    void on_m_checkRate_105_clicked(bool checked);
    void on_m_checkRate_095_stateChanged(int arg1);
    void on_m_checkRate_070_stateChanged(int arg1);
	void on_m_checkRate_100_stateChanged(int arg1);

	//void on_m_btnResEvaluat_clicked();

	void on_m_txtZAngLN1_editingFinished();
	void on_m_txtZAngLN2_editingFinished();
	void on_m_txtZAngLN3_editingFinished();
	void on_m_txtZAngLN4_editingFinished();
	void on_m_txtZAngLN5_editingFinished();

	void on_m_txtZAngLL1_editingFinished();
	void on_m_txtZAngLL2_editingFinished();
	void on_m_txtZAngLL3_editingFinished();
	void on_m_txtZAngLL4_editingFinished();
	void on_m_txtZAngLL5_editingFinished();

private:
    Ui::QDistanceAddMultDlg *m_pAddMult_UI;
protected:
	virtual void SetValueToPage(CDvmData *pData);
	virtual void GetPageToValue(CDvmData *pData);
 	virtual void InitUI();
	virtual void InitLanuage();
	void InitFont();

 	void SetModeText(int nIndex);

	void CheckFaultTypeN1(bool bShoeTips = true);
	void CheckFaultTypeN2(bool bShoeTips = true);
	void CheckFaultTypeN3(bool bShoeTips = true);
	void CheckFaultTypeN4(bool bShoeTips = true);
	void CheckFaultTypeN5(bool bShoeTips = true);

	void CheckFaultTypeL1(bool bShoeTips = true);
	void CheckFaultTypeL2(bool bShoeTips = true);
	void CheckFaultTypeL3(bool bShoeTips = true);
	void CheckFaultTypeL4(bool bShoeTips = true);
	void CheckFaultTypeL5(bool bShoeTips = true);

	void SetApplyTips(CString strTips);
	void timerEvent(QTimerEvent* ev);

	void setLNZone1(bool bState);
	void setLNZone2(bool bState);
	void setLNZone3(bool bState);
	void setLNZone4(bool bState);
	void setLNZone5(bool bState);

	void setLLZone1(bool bState);
	void setLLZone2(bool bState);
	void setLLZone3(bool bState);
	void setLLZone4(bool bState);
	void setLLZone5(bool bState);
	bool CheckSectionState(bool bShoeTips = true);

    bool CheckSelMultipleState(bool bShoeTips = true);

	virtual void CheckAllPresence();
	virtual void MinCheckLeastOne();
	void GetResultEstimateDatas(CDataGroup *pParas);
	//20240923 luozibing 隐藏显示对应区段信息
	void HideFaulType_ABC();
	void ShowZonesByCharIndex();//根据曲线相关信息显示界面
	virtual void UpdateAddMultPageShow(int nZone, bool bLN);//根据曲线区段(参数1) 是否为LN类型(参数2) 更新界面显示
	void UpdateAddMultPageShow_Zone1(bool bLN,bool bshow);
	void UpdateAddMultPageShow_Zone2(bool bLN, bool bshow);
	void UpdateAddMultPageShow_Zone3(bool bLN, bool bshow);
	void UpdateAddMultPageShow_Zone4(bool bLN, bool bshow);
	void UpdateAddMultPageShow_Zone5(bool bLN, bool bshow);
	virtual void SetAllZTSetingEnabled(bool bEnable);//设置所有阻抗定值 时间定值使能
	virtual void SetAllZAngEnabled(bool bEnable);//设置所有角阻抗使能
public:
	void GetDatas(CDataGroup *pParas);
	virtual void SetPageFont(CFont oPageFont);

};

#endif // DISTANCEADDMULTDLG_H
