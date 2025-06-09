#ifndef IMPEDANCEMANUWIDGET_H
#define IMPEDANCEMANUWIDGET_H

#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttTest/Common/tmt_result_def.h"
#include "../../SttTest/Common/Impedance/tmt_manuImped_test.h"
#include "../../Module/SttTestBase/SttComplexp.h"

#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QGroupBox>
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Controls/SttTabWidget.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttLineEdit.h"
#include "../Controls/SttGroupBox.h"
#include "../Controls/SettingCtrls/QSettingLineEdit.h"
#include "ui_ImpedanceManuWidget.h"

#define IMPED_MANUL_GRADIENTVHAMMMEL_Z						 0//Z
#define IMPED_MANUL_GRADIENTVHAMMMEL_R						 1//R
#define IMPED_MANUL_GRADIENTVHAMMMEL_X					 	 2//X
#define IMPED_MANUL_GRADIENTVHAMMMEL_SCCURRT				 3//短路电流
#define IMPED_MANUL_GRADIENTVHAMMMEL_SCVOLT					 4//短路电压

namespace Ui {
	class QImpedanceManuWidget;
}

class QImpedanceManuWidget  : public QWidget
{
	Q_OBJECT

public:
    QImpedanceManuWidget(QWidget *pParent);
    virtual ~QImpedanceManuWidget();
	void InitUI();
	void InitConnect();
	void initBaseData();
	void initData();
	void initstrUnit();
	void initPara();
	void InitGradientData();
	void FirstModeListChanged();
	void SecondModeListChanged();
	void OnRXValue();

	QIcon m_imgLock;
	QIcon m_imgUnlock;

public:
	Ui::QImpedanceManuWidget *ui;

	QStringList m_errorTypeList;//故障类型列表
	QStringList m_CalTypeList;
	QStringList m_CalModList;
	QStringList m_FirstModeList;//变量选择 
	QStringList m_SecondModeList; //变量选择 幅值、相位
	QStringList m_ChangeTypeList;//变化方式

	bool m_bZPhi;
	bool m_bRX;
	int m_bLockChanged;
	float m_fActTime;
	float fValue;
	bool bflag;

	Complex m_fVa;
	Complex m_fVb;
	Complex m_fVc;
	Complex m_fIa;
	Complex m_fIb;
	Complex m_fIc;

	QString strUnit[10];
	bool m_bControlLock; //锁


public:
	CSttTestResourceBase* m_pTestResource;
	tmt_ManualImpedParas *m_pManualImpedParas;
	tmt_ManualImpedTest m_oManualImpedTest;
	CEventResult* m_pEvent;

public:
	void SetData(CSttTestResourceBase *pSttTestResource,tmt_ManualImpedParas* pManualImpedParas,CEventResult* pEvent);
	void UpdateData();

	void StartInit();
	void StopInit();
public slots:
	void slot_CmbErrorTypeIndexChanged(int);
	void slot_CmbCalModeIndexChanged(int);
	void slot_CmbCacuTypeIndexChanged(int);
	void slot_CmbFirstModeIndexChanged(int);  //变量选择1
	void slot_CmbSecondModeIndexChanged(int);//变量选择2
	void slot_CmbChangeTypeIndexChanged(int);
	void slot_RadioZPhiAndRX_StateChanged();
	void slot_lne_TextChanged(QSttLineEdit* pLineEdit);
	float slot_lne_Changed(QLineEdit* pLineEdit);
	void slot_lneZ_TextKeyBoard();
	void slot_lnePhi_TextKeyBoard();
	void slot_lneR_TextKeyBoard();
	void slot_lneX_TextKeyBoard();	
	void slot_lneDLZSAmp_TextKeyBoard(); //短路电流 \短路电压\ZS-AMP
	void slot_lneDLZSAngle_TextKeyBoard();//ZS-Angle
	void slot_lneAmplitudeOrKr_TextKeyBoard();//零系补偿
	void slot_lnePhaseOrKx_TextKeyBoard();//零系补偿
	void slot_lnePrepareTime_TextKeyBoard();//常态时间
	void slot_PreFaultTime_TextKeyBoard();//故障前时间
	void slot_lneStep_TextKeyBoard();//变化步长及时间
	void slot_lneTime_TextKeyBoard();
	void slot_lneStart_TextKeyBoard();//变化始值及终值
	void slot_lneEnd_TextKeyBoard();
	void slot_lneTrigDelay_TextKeyBoard();//触发后延时
	void slot_lneActTime_TextKeyBoard();//动作时间
	void slot_Chb_AutoStateChanged(int);//自动递变
	void slot_Chb_MutationStateChanged(int);//突变量启动
	void slot_pbn_ClearClicked();
	void slot_pbn_UpClicked();
	void slot_pbn_DownClicked();
	void slot_pbn_LockClicked();

	void slot_ck_Out1StateChanged();
	void slot_ck_Out2StateChanged();
	void slot_ck_Out3StateChanged();
	void slot_ck_Out4StateChanged();
signals:

protected slots:
	void slot_currentChangedTabWidget(int nCurrIndex);

};

#endif // IMPEDANCEMANUWIDGET_H
