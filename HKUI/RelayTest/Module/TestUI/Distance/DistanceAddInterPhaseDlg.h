#ifndef DISTANCEADDINTERPHASEDLG_H
#define DISTANCEADDINTERPHASEDLG_H

#include "DistanceAddMultBase.h"
namespace Ui {
class QDistanceAddInterPhaseDlg;
}

class QDistanceAddInterPhaseDlg : public QDistanceAddMultBase
{
    Q_OBJECT

public:
    explicit QDistanceAddInterPhaseDlg(QWidget *parent = 0);
    ~QDistanceAddInterPhaseDlg();
private slots:
	void slot_ZoneTypeCurrentIndexChanged(int index);
    void on_m_checkAB_clicked(bool checked);
    void on_m_checkBC_stateChanged(int arg1);
    void on_m_checkCA_stateChanged(int arg1);
    void on_m_checkForward_clicked(bool checked);
    void on_m_checkReverse_stateChanged(int arg1);
    void on_m_checkRate_105_clicked(bool checked);
    void on_m_checkRate_095_stateChanged(int arg1);
    void on_m_checkRate_070_stateChanged(int arg1);
    void on_m_checkRate_101_clicked(bool checked);
	void on_m_btnSave_clicked();
	void on_m_btnclose_clicked();

	//void on_m_txtZSetting_editingFinished();
	void on_m_txtZAng_editingFinished();
	//void on_m_txtR_editingFinished();
	//void on_m_txtX_editingFinished();
	void on_m_txtTSetting_editingFinished();
	void on_m_txtRel_editingFinished();
	void on_m_txtPlus_3_editingFinished();
	void on_m_txtMinus_3_editingFinished();

	void on_m_txtFaultCurrent_editingFinished();
    void on_m_txtRate_101_editingFinished();

	void on_m_cmb_currentIndexChanged(int index);

private:
    Ui::QDistanceAddInterPhaseDlg *ui;

	virtual void SetValueToPage(CDvmData *pData);
	virtual void GetPageToValue(CDvmData *pData);
	virtual void InitUI();
	virtual void InitLanuage();
	
	void CheckFaultTypeState(BOOL bShow = TRUE);
	void CheckFaultDirectionState(BOOL bShow = TRUE);
	void CheckRateState(BOOL bShow = TRUE);
	void SetApplyTips(CString strTips);
	void timerEvent(QTimerEvent* ev);
	virtual void CheckAllPresence();

	void CheckAllPresence_Zone1();
	void CheckAllPresence_Zone2();
	void CheckAllPresence_Zone3();
	void CheckAllPresence_Zone4();
	void CheckAllPresence_Zone5();
	void CheckAllPresence_Zone6();

	void GetPageToValue_Zone1(CDvmData *pData);
	void GetPageToValue_Zone2(CDvmData *pData);
	void GetPageToValue_Zone3(CDvmData *pData);
	void GetPageToValue_Zone4(CDvmData *pData);
	void GetPageToValue_Zone5(CDvmData *pData);
	void GetPageToValue_Zone6(CDvmData *pData);
	void GetPageToValue_ZoneALL(CDvmData *pData);
	void GetPageToInitValue_Zone1(CDvmData *pData);
	void GetPageToInitValue_Zone2(CDvmData *pData);
	void GetPageToInitValue_Zone3(CDvmData *pData);
	void GetPageToInitValue_Zone4(CDvmData *pData);
	void GetPageToInitValue_Zone5(CDvmData *pData);
	void GetPageToInitValue_Zone6(CDvmData *pData);
	void ConnectAll_SigSlot();
	void DisConnectAll_SigSlot();

	virtual void MinCheckLeastOne();

	void SetValueToPage__Zone1(CDvmData *pData);
	void SetValueToPage__Zone2(CDvmData *pData);
	void SetValueToPage__Zone3(CDvmData *pData);
	void SetValueToPage__Zone4(CDvmData *pData);
	void SetValueToPage__Zone5(CDvmData *pData);
	void SetValueToPage__Zone6(CDvmData *pData);

	void UpadateValueToPage_Zone1(CDvmData *pData);//区段选择对应参数设置在界面上
	void UpadateValueToPage_Zone2(CDvmData *pData);
	void UpadateValueToPage_Zone3(CDvmData *pData);
	void UpadateValueToPage_Zone4(CDvmData *pData);
	void UpadateValueToPage_Zone5(CDvmData *pData);
	void UpadateValueToPage_Zone6(CDvmData *pData);

	void UpdateBtnEnable(BOOL bEnable);
	virtual void InitPageShowByParas();//设置特性曲线相关数据后更新界面下拉框显示数据

	void UpadatePageByZoneType();
	void UpadateValueToPage(CDvmData *pData);

	void SetZRXValueByZAng(int nZoneValue);
};

#endif // DISTANCEADDINTERPHASEDLG_H
