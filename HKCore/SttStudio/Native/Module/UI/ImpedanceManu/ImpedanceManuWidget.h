#ifndef IMPEDANCEMANUWIDGET_H
#define IMPEDANCEMANUWIDGET_H

#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttTest/Common/tmt_result_def.h"
#include "../../SttTest/Common/Impedance/tmt_manuImped_test.h"
#include "../Module/SttTestBase/SttComplexp.h"

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

class QImpedanceManuWidget : public QWidget
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
	void FirstModeListChanged();
	void SecondModeListChanged();
	void OnRXValue();

	QIcon m_imgLock;
	QIcon m_imgUnlock;

	QGridLayout *m_pMainGridLayout;
	QPushButton *m_pBinarySet_PushButton;
	QPushButton *m_pEstimate_PushButton;
	QSttTabWidget *m_pImpedanceManuTab;
	

	QWidget *m_pParaSetting_Widget;//参数设置

public:
	QPushButton *m_pbn_Clear;
	QPushButton *m_pbn_Up;
	QPushButton *m_pbn_Down;
	QPushButton *m_pbn_Lock;
	QLabel *m_pFaultTypeLabel;//故障类型
	QLabel *m_pCalModeLabel;//阻抗类型
	QLabel *m_pImpedlabel;//阻抗输入选择
	QLabel *m_pZLabel;//|Z|
	QLabel *m_pRXLabel;//R,X
	QLabel *m_pDLLabel;//短路
	QLabel *m_pVarSelecLabel;//变量选择
	QLabel *m_PrepareTimeLabel;//常态时间
	QLabel *m_PreFaultTimeLabel;//故障前时间
	QLabel *m_pStepLabel;//变化步长
	QLabel *m_pStartLabel;//变化始值
	QLabel *m_pTimeLabel;//变化时间
	QLabel *m_pEndLabel;//变化终值
	QLabel *m_pTrigDelayLabel;//触发后延时
	QLabel *m_pChangeTypeLabel;//变化方式
	QLabel *m_pActTimeLabel;//动作时间
	QLabel *m_pFrequencyLabel;//频率
	QLabel *m_pZsLabel;
	QLabel *m_pCacuTypeLabel;//模式
	QLabel *m_pAmpLabel;//幅值
	QLabel *m_pAngleLabel;//相位
	QScrollComboBox *m_pCmb_CalMode;
	QScrollComboBox *m_pCmb_FaultType;
	QScrollComboBox *m_pCmb_FirstMode;//变量选择1
	QScrollComboBox *m_pCmb_SecondMode;//变量选择2
	QScrollComboBox *m_pCmb_CacuType;
	QScrollComboBox *m_pCmb_ChangeType;
	QRadioButton *m_pRad_Z;//Z
	QRadioButton *m_pRad_RX;//R,X
	QSttCheckBox *m_pAuto_CheckBox;//自动递变
	QSttCheckBox *m_pMutation_CheckBox;//突变量启动
	QSttLineEdit *m_pPhiEdit;
	QSttLineEdit *m_pZEdit;
	QSttLineEdit *m_pXEdit;
	QSttLineEdit *m_pREdit;
	QSttLineEdit *m_pShortIOrZsAmpEdit;//短路电流/短路电压/Zs幅值
	QSttLineEdit *m_pShortIOrZsAngleEdit;//Zs角度
	QSttLineEdit *m_PrepareTimeEdit;//常态时间
	QSttLineEdit *m_PreFaultTimeEdit;//故障前时间
	QSttLineEdit *m_pStepEdit;//变化步长
	QSttLineEdit *m_pStartEdit;//变化始值
	QSttLineEdit *m_pTimeEdit;//变化时间
	QSttLineEdit *m_pEndEdit;//变化终值
	QSttLineEdit *m_pFrequencyEdit;//频率
	QSttLineEdit *m_pTrigDelayEdit;//触发后延时
	QSttLineEdit *m_pActTimeEdit;//动作时间
	QSttLineEdit *m_pAmpEdit;
	QSttLineEdit *m_pAngleEdit;

	QGroupBox *m_pBoutGroupBox;
	QGridLayout *m_pBout_GridLayout;
	QSttCheckBox *m_pBout_CheckBox[4];

private:
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
	private slots:
		void slot_CmbErrorTypeIndexChanged(int);
		void slot_CmbCalModeIndexChanged(int);
		void slot_CmbCacuTypeIndexChanged(int);
		void slot_CmbFirstModeIndexChanged(int);  //变量选择1
		void slot_CmbSecondModeIndexChanged(int);//变量选择2
		void slot_CmbChangeTypeIndexChanged(int);
		void slot_RadioZPhiAndRX_StateChanged();
		void slot_lne_TextChanged(QSttLineEdit* pLineEdit);
		float slot_lne_Changed(QSttLineEdit* pLineEdit);
		void slot_lneZ_TextKeyBoard();
		void slot_lnePhi_TextKeyBoard();
		void slot_lneR_TextKeyBoard();
		void slot_lneX_TextKeyBoard();	
		void slot_lneDLZSAmp_TextKeyBoard(); //短路电流 \短路电压\ZS-AMP
		void slot_lneDLZSAngle_TextKeyBoard();//ZS-Angle
		//void slot_lneAmplitudeOrKr_TextChanged();//零系补偿
		void slot_lneAmplitudeOrKr_TextKeyBoard();
		//void slot_lnePhaseOrKx_TextChanged();//零系补偿
		void slot_lnePhaseOrKx_TextKeyBoard();
		//void slot_lnePrepareTime_TextChanged();//常态时间
		void slot_lnePrepareTime_TextKeyBoard();
		//void slot_PreFaultTime_TextChanged();//故障前时间
		void slot_PreFaultTime_TextKeyBoard();
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
