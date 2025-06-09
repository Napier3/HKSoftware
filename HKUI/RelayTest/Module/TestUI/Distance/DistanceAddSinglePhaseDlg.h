#ifndef DISTANCEADDSINGLEPHASEDLG_H
#define DISTANCEADDSINGLEPHASEDLG_H

#include "DistanceAddMultBase.h"
namespace Ui {
class QDistanceAddSinglePhaseDlg;
}

class QDistanceAddSinglePhaseDlg : public QDistanceAddMultBase
{
    Q_OBJECT

public:
    explicit QDistanceAddSinglePhaseDlg(QWidget *parent = 0);
    ~QDistanceAddSinglePhaseDlg();

	void SetPageFont(CFont oPageFont);//20240806 luozibing 测试使用

private slots:
	void slot_ZoneTypeCurrentIndexChanged(int index);
    void on_m_checkAN_clicked(bool checked);
    void on_m_checkBN_stateChanged(int arg1);
    void on_m_checkCN_stateChanged(int arg1);
    void on_m_checkForward_stateChanged(int arg1);
    void on_m_checkReverse_stateChanged(int arg1);
    void on_m_checkRate_105_clicked(bool checked);
    void on_m_checkRate_095_stateChanged(int arg1);
    void on_m_checkRate_070_stateChanged(int arg1);
    void on_m_checkRate_100_clicked(bool checked);
    void on_m_cmbK0Mode_currentIndexChanged(int index);
	void on_m_btnSave_clicked();
	void on_m_btnclose_clicked();

	//void on_m_txtPlus_editingFinished();
	//void on_m_txtMinus_editingFinished();
	//void on_m_txtRel1_editingFinished();
	void on_m_cmb_currentIndexChanged(int index);

	//void on_m_txtZSetting_editingFinished();
	void on_m_txtZAng_editingFinished();
	//void on_m_txtR_editingFinished();
	//void on_m_txtX_editingFinished();
	void on_m_txtTSetting_editingFinished();
	void on_m_txtRel1_editingFinished();
	void on_m_txtPlus_editingFinished();
	void on_m_txtMinus_editingFinished();
	void on_m_txtFaultCurrent_editingFinished();
	void on_m_txtRate_100_editingFinished();
    void on_m_txtKlKr_editingFinished();
    void on_m_txtAngKx_editingFinished();

private:
    Ui::QDistanceAddSinglePhaseDlg *ui;

	virtual void SetValueToPage(CDvmData *pData);
	virtual void GetPageToValue(CDvmData *pData);
	virtual void InitUI();
	virtual void InitLanuage();

	void SetModeText(int nIndex);
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

	void SetValueToPage__Zone1(CDvmData *pData);//设置对应区段参数在页面
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

	virtual void MinCheckLeastOne();
	void UpdateBtnEnable(BOOL bEnable);//选择区段改变，部分控件使能状态改变
	virtual void InitPageShowByParas();//设置特性曲线相关数据后更新界面下拉框显示数据

	void UpadatePageByZoneType();//区段选择改变后更新界面显示
	void UpadateValueToPage(CDvmData *pData);

	void SetZRXValueByZAng(int nZoneValue);
};

#endif // DISTANCEADDSINGLEPHASEDLG_H
