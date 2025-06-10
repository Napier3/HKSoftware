#include "stdafx.h"
#include "ImpedanceManuWidget.h"

#include "../Module/CommonMethod/commonMethod.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SttMacroParaEditViewImpedanceManu.h"
#include "../SttTestCntrFrameBase.h"
#include "../Module/XLangResource_Native.h"

QImpedanceManuWidget::QImpedanceManuWidget(QWidget *pParent): QWidget(pParent)
{
	m_pBout_CheckBox[0] = NULL;
	m_pBout_CheckBox[1] = NULL;
	m_pBout_CheckBox[2] = NULL;
	m_pBout_CheckBox[3] = NULL;

}

QImpedanceManuWidget::~QImpedanceManuWidget()
{

}

void QImpedanceManuWidget::InitUI()
{
	m_pMainGridLayout = new QGridLayout(this);
	m_pImpedanceManuTab = new QSttTabWidget(this);
	m_pMainGridLayout->addWidget(m_pImpedanceManuTab, 0, 0, 1, 10);

	m_pParaSetting_Widget = new QWidget();
	m_pParaSetting_Widget->setObjectName(QString::fromUtf8("ParaSettingWidget"));

	m_pImpedanceManuTab->addTab(m_pParaSetting_Widget,"功能参数");
	
	//参数设置界面UI
	QGridLayout *gridLayout = new QGridLayout(m_pParaSetting_Widget);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(11, 11, 11, 11);

	m_pFaultTypeLabel = new QLabel(tr("故障类型:"),this);//故障类型Label
	gridLayout->addWidget(m_pFaultTypeLabel, 1, 0, 1, 1);
	m_pCmb_FaultType = new QScrollComboBox(this);//故障类型
	gridLayout->addWidget(m_pCmb_FaultType, 1, 1, 1, 2);

	m_pCalModeLabel = new QLabel(tr("测试类型:"),this);//测试类型Label  空2
	gridLayout->addWidget(m_pCalModeLabel, 1, 5, 1, 1);
	m_pCmb_CalMode = new QScrollComboBox(this);//测试类型
	gridLayout->addWidget(m_pCmb_CalMode, 1, 6, 1, 2);

	m_pImpedlabel = new QLabel(tr("阻抗输入选择:"),this);//阻抗输入选择Label
	gridLayout->addWidget(m_pImpedlabel, 2, 0, 1, 1);
	m_pRad_Z = new QRadioButton(tr("Z"),this);//Z,Phi  RadioButton
	gridLayout->addWidget(m_pRad_Z, 2, 1, 1, 1);
	m_pRad_RX = new QRadioButton(tr("R,X"),this);//R,X  RadioButton
	gridLayout->addWidget(m_pRad_RX, 2, 2, 1, 1);

	m_pZLabel = new QLabel(QString::fromLocal8Bit("|Z|（Ω），Phi（°）"),this);
	gridLayout->addWidget(m_pZLabel, 3, 0, 1, 1);
	m_pZEdit = new QSttLineEdit(this);
	m_pZEdit->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(m_pZEdit, 3, 1, 1, 1);//Z
	m_pPhiEdit = new QSttLineEdit(this);
	m_pPhiEdit->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(m_pPhiEdit, 3, 2, 1, 1);//Phi

	m_pRXLabel = new QLabel(QString::fromLocal8Bit("R,X（Ω）"),this);
	gridLayout->addWidget(m_pRXLabel, 4, 0, 1, 1);
	m_pREdit = new QSttLineEdit(this);//R
	m_pREdit->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(m_pREdit, 4, 1, 1, 1);
	m_pXEdit = new QSttLineEdit(this);//X
	m_pXEdit->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(m_pXEdit, 4, 2, 1, 1);

	m_pDLLabel = new QLabel(tr("短路电流（A）"),this);//短路电流Label
	gridLayout->addWidget(m_pDLLabel, 5, 0, 1, 1);
	m_pShortIOrZsAmpEdit = new QSttLineEdit(this);
	m_pShortIOrZsAmpEdit->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(m_pShortIOrZsAmpEdit, 5, 1, 1, 1);
	m_pShortIOrZsAngleEdit = new QSttLineEdit(this);	
	m_pShortIOrZsAngleEdit->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(m_pShortIOrZsAngleEdit, 5, 2, 1, 1);
	m_pShortIOrZsAngleEdit->setVisible(false);//不显示

	//m_pFrequencyLabel = new QLabel(tr("频率（Hz）"),this);//频率Label
	//gridLayout->addWidget(m_pFrequencyLabel, 6, 0, 1, 1);
	//m_pFrequencyEdit = new QSttLineEdit(this);
	//m_pFrequencyEdit->setAlignment(Qt::AlignCenter);
	//gridLayout->addWidget(m_pFrequencyEdit, 6, 1, 1, 1);

	m_pTrigDelayLabel = new QLabel(tr("触发后延时（s）"),this);//触发后延时Label
	gridLayout->addWidget(m_pTrigDelayLabel, 6, 0, 1, 1);	
	m_pTrigDelayEdit = new QSttLineEdit(this);
	m_pTrigDelayEdit->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(m_pTrigDelayEdit, 6, 1, 1, 1);

	QSttGroupBox* groupBoxCommon = new QSttGroupBox(tr("递变"),this);
	QGridLayout* gridLayoutCommon = new QGridLayout(groupBoxCommon);
	gridLayoutCommon->setSpacing(6);
	gridLayoutCommon->setContentsMargins(11, 11, 11, 11);

	m_pVarSelecLabel = new QLabel(tr("变量选择"),this);//变量选择Label
	gridLayoutCommon->addWidget(m_pVarSelecLabel, 1, 0, 1, 1);
	m_pCmb_FirstMode = new QScrollComboBox(this);//变量选择1
	gridLayoutCommon->addWidget(m_pCmb_FirstMode, 1, 1, 1, 1);
	m_pCmb_SecondMode = new QScrollComboBox(this);//变量选择2
	gridLayoutCommon->addWidget(m_pCmb_SecondMode, 1, 2, 1, 1);

	m_pTimeLabel = new QLabel(tr("变化时间（s）"),this);//变化时间Label
	gridLayoutCommon->addWidget(m_pTimeLabel, 1, 4, 1, 1);	
	m_pTimeEdit = new QSttLineEdit(this);
	m_pTimeEdit->setAlignment(Qt::AlignCenter);
	gridLayoutCommon->addWidget(m_pTimeEdit, 1, 5, 1, 1);

	m_pStartLabel = new QLabel(tr("变化始值（Ω）"),this);//变化始值Label
	gridLayoutCommon->addWidget(m_pStartLabel, 2, 0, 1, 1);	
	m_pStartEdit = new QSttLineEdit(this);
	m_pStartEdit->setAlignment(Qt::AlignCenter);
	gridLayoutCommon->addWidget(m_pStartEdit,2, 1, 1, 1);

	m_pEndLabel = new QLabel(tr("变化终值（Ω）"),this);//变化终值Label
	gridLayoutCommon->addWidget(m_pEndLabel, 2, 2, 1, 1);	
	m_pEndEdit = new QSttLineEdit(this);
	m_pEndEdit->setAlignment(Qt::AlignCenter);
	gridLayoutCommon->addWidget(m_pEndEdit, 2, 3, 1, 1);

	m_pStepLabel = new QLabel(tr("变化步长（Ω）"),this);//变化步长Label
	gridLayoutCommon->addWidget(m_pStepLabel, 2, 4, 1, 1);	
	m_pStepEdit = new QSttLineEdit(this);
	m_pStepEdit->setAlignment(Qt::AlignCenter);
	gridLayoutCommon->addWidget(m_pStepEdit, 2, 5, 1, 1);

	m_PrepareTimeLabel = new QLabel(tr("常态时间（s）"),this);//常态时间Label
	gridLayoutCommon->addWidget(m_PrepareTimeLabel, 3, 0, 1, 1);	
	m_PrepareTimeEdit = new QSttLineEdit(this);
	m_PrepareTimeEdit->setAlignment(Qt::AlignCenter);
	gridLayoutCommon->addWidget(m_PrepareTimeEdit, 3, 1, 1, 1);

	m_PreFaultTimeLabel = new QLabel(tr("故障前时间（s）"),this);//故障前时间Label
	gridLayoutCommon->addWidget(m_PreFaultTimeLabel, 3, 2, 1, 1);	
	m_PreFaultTimeEdit = new QSttLineEdit(this);
	m_PreFaultTimeEdit->setAlignment(Qt::AlignCenter);
	gridLayoutCommon->addWidget(m_PreFaultTimeEdit, 3, 3, 1, 1);

	m_pChangeTypeLabel = new QLabel(g_sLangTxt_Manual_ChangeType,this);//变化方式Label
	gridLayoutCommon->addWidget(m_pChangeTypeLabel, 3, 4, 1, 1);	
	m_pCmb_ChangeType = new QScrollComboBox(this);
	gridLayoutCommon->addWidget(m_pCmb_ChangeType, 3, 5, 1, 1);

	QSttGroupBox* groupBox = new QSttGroupBox(tr("零序补偿系数"),this);
	QGridLayout* gridLayoutSub = new QGridLayout(groupBox);
	gridLayoutSub->setSpacing(6);
	gridLayoutSub->setContentsMargins(11, 11, 11, 11);

	m_pCacuTypeLabel = new QLabel(tr("模式:"),groupBox);
	gridLayoutSub->addWidget(m_pCacuTypeLabel, 0, 0, 1, 1);
	m_pCmb_CacuType = new QScrollComboBox(groupBox);
	gridLayoutSub->addWidget(m_pCmb_CacuType, 0, 1, 1, 1);
	m_pAmpLabel = new QLabel(tr("幅值:"),groupBox);
	gridLayoutSub->addWidget(m_pAmpLabel, 0, 2, 1, 1);
	m_pAmpEdit = new QSttLineEdit(groupBox);
	m_pAmpEdit->setAlignment(Qt::AlignCenter);
	gridLayoutSub->addWidget(m_pAmpEdit, 0, 3, 1, 1);
	m_pAngleLabel = new QLabel(tr("相角:"),groupBox);
	gridLayoutSub->addWidget(m_pAngleLabel, 1, 2, 1, 1);
	m_pAngleEdit = new QSttLineEdit(groupBox);
	m_pAngleEdit->setAlignment(Qt::AlignCenter);
	gridLayoutSub->addWidget(m_pAngleEdit, 1, 3, 1, 1);

	gridLayout->addWidget(groupBox, 2, 5, 4, 3);

	m_pAuto_CheckBox = new QSttCheckBox(tr("自动递变"),this);//自动递变Label
	gridLayout->addWidget(m_pAuto_CheckBox, 6, 7, 1, 1);	

	m_pMutation_CheckBox = new QSttCheckBox(tr("突变量启动"),this);//突变量启动Label
	gridLayout->addWidget(m_pMutation_CheckBox, 7, 7, 1, 1);	

	//m_pbn_Clear = new QPushButton(tr("清除结果"),this);//清除结果Label
	//gridLayoutCommon->addWidget(m_pbn_Clear, 2, 6, 1, 2);	

	//m_pActTimeLabel = new QLabel(tr("动作时间"),this);//动作时间Label
	//gridLayoutCommon->addWidget(m_pActTimeLabel, 3, 4, 1, 2);	
	//m_pActTimeEdit = new QSttLineEdit(this);
	//m_pActTimeEdit->setAlignment(Qt::AlignCenter);
	//gridLayoutCommon->addWidget(m_pActTimeEdit, 3, 6, 1, 2);

	m_pbn_Up = new QPushButton(tr("+"),this);//up
	m_pMainGridLayout->addWidget(m_pbn_Up, 1, 1, 1, 1);	
	m_pbn_Down = new QPushButton(tr("-"),this);//down
	m_pMainGridLayout->addWidget(m_pbn_Down, 1,2, 1, 1);	

	m_pbn_Lock = new QPushButton(g_sLangTxt_Manual_Lock,this);//lock
	m_pMainGridLayout->addWidget(m_pbn_Lock, 1, 0, 1, 1);	

	gridLayout->addWidget(groupBoxCommon, 8, 0, 3, 7);

	//strText = _T("开出量");
	m_pBoutGroupBox = new QGroupBox(g_sLangTxt_Native_Bout,this);
	m_pBoutGroupBox->setFixedWidth(150);

	m_pBout_GridLayout = new QGridLayout(m_pBoutGroupBox);
	m_pBout_CheckBox[0] = new QSttCheckBox(tr("1"),m_pBoutGroupBox);
	//m_pBout_CheckBox[0]->setFixedWidth(80);
	m_pBout_GridLayout->addWidget(m_pBout_CheckBox[0], 0, 0, 1, 1);

	m_pBout_CheckBox[1] = new QSttCheckBox(tr("2"),m_pBoutGroupBox);
	//m_pBout_CheckBox[1]->setFixedWidth(80);
	m_pBout_GridLayout->addWidget(m_pBout_CheckBox[1], 0, 1, 1, 1);

	m_pBout_CheckBox[2] = new QSttCheckBox(tr("3"),m_pBoutGroupBox);
	//m_pBout_CheckBox[2]->setFixedWidth(80);
	m_pBout_GridLayout->addWidget(m_pBout_CheckBox[2], 1, 0, 1, 1);

	m_pBout_CheckBox[3] = new QSttCheckBox(tr("4"),m_pBoutGroupBox);
	//m_pBout_CheckBox[3]->setFixedWidth(80);
	m_pBout_GridLayout->addWidget(m_pBout_CheckBox[3], 1, 1, 1, 1);

	m_pBinarySet_PushButton = new QPushButton(g_sLangTxt_Native_Switch,this);


    gridLayout->addWidget(m_pBoutGroupBox, 10, 7, 1, 1);
	m_pMainGridLayout->addWidget(m_pBinarySet_PushButton, 1, 6, 1, 2);

	m_pEstimate_PushButton =new QPushButton(g_sLangTxt_State_Estimate,this);
	m_pEstimate_PushButton->setFixedWidth(150);
	m_pMainGridLayout->addWidget(m_pEstimate_PushButton, 1, 8, 1, 2);

	m_pbn_Lock->setDisabled(true);

#ifdef _PSX_QT_WINDOWS_
	CString strImagePath = _P_GetResourcePath();
	m_imgLock.addFile(strImagePath + "Lock.png");
	m_imgUnlock.addFile(strImagePath + "Unlock.png");
#else
	CString strImagePath ;
	strImagePath = ":/ctrls/images/Lock.png";
	m_imgLock.addFile(strImagePath);
	strImagePath = ":/ctrls/images/Unlock.png";
	m_imgUnlock.addFile(strImagePath);
#endif

	m_pbn_Lock->setIcon(m_imgUnlock);
	m_pbn_Lock->setIconSize(QSize(m_pbn_Up->height(), m_pbn_Up->height()));
	m_pbn_Lock->setFixedWidth(m_pbn_Up->width());
	m_pbn_Lock->setText("");

}

void QImpedanceManuWidget::InitConnect()
{
	connect(m_pImpedanceManuTab, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
	connect(m_pCmb_FaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbErrorTypeIndexChanged(int)));//故障类型
	connect(m_pCmb_CalMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbCalModeIndexChanged(int)));//阻抗类型
	connect(m_pCmb_CacuType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbCacuTypeIndexChanged(int)));//零系补偿模式ko
	connect(m_pCmb_FirstMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbFirstModeIndexChanged(int)));
	connect(m_pCmb_SecondMode,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbSecondModeIndexChanged(int)));
	connect(m_pCmb_ChangeType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CmbChangeTypeIndexChanged(int)));

	//阻抗输入选择
	connect(m_pRad_Z, SIGNAL(toggled(bool )), this, SLOT(slot_RadioZPhiAndRX_StateChanged()));
	connect(m_pRad_RX, SIGNAL(toggled(bool )), this, SLOT(slot_RadioZPhiAndRX_StateChanged()));

	connect(m_pAuto_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_Chb_AutoStateChanged(int)));
	connect(m_pMutation_CheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_Chb_MutationStateChanged(int)));

	connect(m_pZEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneZ_TextKeyBoard()));
	connect(m_pPhiEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePhi_TextKeyBoard()));
	connect(m_pREdit,SIGNAL(editingFinished()),this,SLOT(slot_lneR_TextKeyBoard()));
	connect(m_pXEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneX_TextKeyBoard()));
	connect(m_pShortIOrZsAmpEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneDLZSAmp_TextKeyBoard()));
	connect(m_pShortIOrZsAngleEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneDLZSAngle_TextKeyBoard()));
	connect(m_PrepareTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePrepareTime_TextKeyBoard()));
	connect(m_PreFaultTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_PreFaultTime_TextKeyBoard()));
	connect(m_pStepEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneStep_TextKeyBoard()));
	connect(m_pStartEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneStart_TextKeyBoard()));
	connect(m_pTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneTime_TextKeyBoard()));
	connect(m_pEndEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneEnd_TextKeyBoard()));
	connect(m_pTrigDelayEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneTrigDelay_TextKeyBoard()));
	//connect(m_pActTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneActTime_TextKeyBoard()));
	connect(m_pAmpEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneAmplitudeOrKr_TextKeyBoard()));
	connect(m_pAngleEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePhaseOrKx_TextKeyBoard()));

	//connect(m_pbn_Clear, SIGNAL(clicked ()), this, SLOT(slot_pbn_ClearClicked()));
	connect(m_pbn_Up, SIGNAL(clicked ()), this, SLOT(slot_pbn_UpClicked()));
	connect(m_pbn_Down, SIGNAL(clicked ()), this, SLOT(slot_pbn_DownClicked()));
	connect(m_pbn_Lock, SIGNAL(clicked ()), this, SLOT(slot_pbn_LockClicked()));

#ifdef _PSX_QT_LINUX_
	connect(m_pZEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pZEdit)));
	connect(m_pPhiEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pPhiEdit)));
	connect(m_pREdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pREdit)));
	connect(m_pXEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pXEdit)));
	connect(m_pShortIOrZsAmpEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pShortIOrZsAmpEdit)));
	connect(m_pShortIOrZsAngleEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pShortIOrZsAngleEdit)));
	connect(m_PrepareTimeEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_PrepareTimeEdit)));
	connect(m_PreFaultTimeEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_PreFaultTimeEdit)));
	connect(m_pStepEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pStepEdit)));
	connect(m_pStartEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pStartEdit)));
	connect(m_pTimeEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pTimeEdit)));
	connect(m_pEndEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pEndEdit)));
	connect(m_pTrigDelayEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pTrigDelayEdit)));
	connect(m_pActTimeEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pActTimeEdit)));
	connect(m_pAmpEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pAmpEdit)));
	connect(m_pAngleEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pAngleEdit)));

#endif
}

void QImpedanceManuWidget::SetData(CSttTestResourceBase *pSttTestResource,tmt_ManualImpedParas* pManualImpedParas,CEventResult* pEvent)
{
	m_pTestResource = pSttTestResource;
	m_pManualImpedParas = pManualImpedParas;
	m_pEvent = pEvent;

	initPara();
	initstrUnit();
	initBaseData();
	initData();

	UpdateData();
}

void QImpedanceManuWidget::UpdateData()
{
	if(m_pManualImpedParas == NULL || m_pTestResource == NULL)
	{
		return;
	}

	g_theTestCntrFrame->SetVectorGradient(m_pManualImpedParas->m_bAuto);

}

void QImpedanceManuWidget::StartInit()
{
	m_bControlLock = false;
	m_pManualImpedParas->m_bLockChanged = m_bControlLock;
	
	bool bAuto = m_pManualImpedParas->m_bAuto;

	m_pbn_Up->setDisabled(bAuto);
	m_pbn_Down->setDisabled(bAuto);
	m_pbn_Lock->setDisabled(bAuto);

	m_pStepEdit->setDisabled(bAuto);
	m_pBoutGroupBox->setDisabled(bAuto);
	m_pBinarySet_PushButton->setDisabled(bAuto);
	m_pEstimate_PushButton->setDisabled(bAuto);

	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[0],0,g_nBoutCount,!m_pManualImpedParas->m_bAuto);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[1],1,g_nBoutCount,!m_pManualImpedParas->m_bAuto);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[2],2,g_nBoutCount,!m_pManualImpedParas->m_bAuto);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[3],3,g_nBoutCount,!m_pManualImpedParas->m_bAuto);

	m_pTimeEdit->setDisabled(true);
	m_pStartEdit->setDisabled(true);
	m_pEndEdit->setDisabled(true);
	m_PrepareTimeEdit->setDisabled(true);
	m_PreFaultTimeEdit->setDisabled(true);
	m_pPhiEdit->setDisabled(true);
	m_pZEdit->setDisabled(true);
	m_pXEdit->setDisabled(true);
	m_pREdit->setDisabled(true);
	m_pShortIOrZsAmpEdit->setDisabled(true);
	m_pShortIOrZsAngleEdit->setDisabled(true);
	m_pTrigDelayEdit->setDisabled(true);
	m_pAmpEdit->setDisabled(true);
	m_pAngleEdit->setDisabled(true);

	m_pCmb_CalMode->setDisabled(true);
	m_pCmb_FaultType->setDisabled(true);
	m_pCmb_FirstMode->setDisabled(true);
	m_pCmb_SecondMode->setDisabled(true);
	m_pCmb_CacuType->setDisabled(true);
	m_pCmb_ChangeType->setDisabled(true);

	m_pAuto_CheckBox->setDisabled(true);
}

void QImpedanceManuWidget::StopInit()
{
	m_bControlLock = true;
	m_pManualImpedParas->m_bLockChanged = false;
	m_pbn_Lock->setIcon(m_imgUnlock);
	m_pbn_Lock->setDisabled(true);
	m_pbn_Up->setDisabled(m_pManualImpedParas->m_bAuto);
	m_pbn_Down->setDisabled(m_pManualImpedParas->m_bAuto);

	m_pTimeEdit->setDisabled(!m_pManualImpedParas->m_bAuto);
	m_pStartEdit->setDisabled(!m_pManualImpedParas->m_bAuto);
	m_pEndEdit->setDisabled(!m_pManualImpedParas->m_bAuto);
	m_PrepareTimeEdit->setDisabled(false);
	m_PreFaultTimeEdit->setDisabled(false);
	m_pPhiEdit->setDisabled(false);
	m_pZEdit->setDisabled(false);
	m_pXEdit->setDisabled(false);
	m_pREdit->setDisabled(false);
	m_pShortIOrZsAmpEdit->setDisabled(false);
	m_pShortIOrZsAngleEdit->setDisabled(false);
	m_pTrigDelayEdit->setDisabled(false);
	m_pAmpEdit->setDisabled(false);
	m_pAngleEdit->setDisabled(false);

	m_pCmb_CalMode->setDisabled(false);
	m_pCmb_FaultType->setDisabled(false);
	m_pCmb_FirstMode->setDisabled(false);
	m_pCmb_SecondMode->setDisabled(false);
	m_pCmb_CacuType->setDisabled(false);
	m_pCmb_ChangeType->setDisabled(false);

	m_pAuto_CheckBox->setDisabled(false);

	m_pBoutGroupBox->setDisabled(false);
	m_pBinarySet_PushButton->setDisabled(false);
	m_pEstimate_PushButton->setDisabled(false);

	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[0],0,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[1],1,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[2],2,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(m_pBout_CheckBox[3],3,g_nBoutCount,true);
}

//初始化单位
void QImpedanceManuWidget::initstrUnit()
{
		strUnit[0]="A";
		strUnit[1]="V";
		strUnit[2]="Ω";
		strUnit[3]="Hz";
		strUnit[4]="°";
		strUnit[5]="S";
}
void QImpedanceManuWidget::initBaseData()
{
	m_errorTypeList.clear();
	m_FirstModeList.clear();
	m_SecondModeList.clear();
	m_CalModList.clear();
	m_CalTypeList.clear();
	m_ChangeTypeList.clear();

	//故障类型
    CString strGndA,strGndB,strGndC,strShortAB,strShortBC,strShortCA,strGndShortAB,strGndShortBC,strGndShortCA,
		strShortABC;
//	m_errorTypeList << tr("A相接地")<< tr("B相接地")<< tr("C相接地")<< tr("AB短路")<< tr("BC短路")<< tr("CA短路")\
//		<< tr("AB接地短路")<< tr("BC接地短路")<< tr("CA接地短路")<< tr("三相短路"));
	
	xlang_GetLangStrByFile(strGndA, "Native_GndA");
	xlang_GetLangStrByFile(strGndB, "Native_GndB");
	xlang_GetLangStrByFile(strGndC, "Native_GndC");
	xlang_GetLangStrByFile(strShortAB, "Native_ShortAB");
	xlang_GetLangStrByFile(strShortBC, "Native_ShortBC");
	xlang_GetLangStrByFile(strShortCA, "Native_ShortCA");
	xlang_GetLangStrByFile(strGndShortAB, "Native_GndShortAB");
	xlang_GetLangStrByFile(strGndShortBC, "Native_GndShortBC");
	xlang_GetLangStrByFile(strGndShortCA, "Native_GndShortCA");
	xlang_GetLangStrByFile(strShortABC, "Native_ShortABC");

	m_errorTypeList << strGndA<< strGndB<< strGndC<< strShortAB<< strShortBC<< strShortCA\
		<< strGndShortAB<< strGndShortBC<< strGndShortCA<< strShortABC;

	//阻抗类型
	m_CalModList << "定电流" << "定电压" << "固定系统侧阻抗";

	//变量选择1
	m_FirstModeList<< "Z" << "R" << "X" << "短路电流";
	//变量选择2
	m_SecondModeList << "幅值" << "相位";

	//零序补偿系数的模式
	m_CalTypeList << "Ko" << "Kr,Kx" << "Z0/Z1";

	//变化方式
	m_ChangeTypeList << "始-终" << "始-终-始";

	m_pCmb_FaultType->clear();
	m_pCmb_FirstMode->clear();
	m_pCmb_SecondMode->clear();
	m_pCmb_CalMode->clear();
	m_pCmb_CacuType->clear();
	m_pCmb_ChangeType->clear();
	
	m_pCmb_FaultType->addItems(m_errorTypeList);
	m_pCmb_FirstMode->addItems(m_FirstModeList);
	m_pCmb_SecondMode->addItems(m_SecondModeList);
	m_pCmb_CalMode->addItems(m_CalModList);
	m_pCmb_CacuType->addItems(m_CalTypeList);
	m_pCmb_ChangeType->addItems(m_ChangeTypeList);
}

void QImpedanceManuWidget::initPara()
{
	//m_nRadio = m_pManualImpedParas->m_nImped;//输入阻抗选择0-z 1-rx
	if ( m_pManualImpedParas->m_nImped)
	{
		m_bZPhi = false;
		m_bRX = true;
	}
	else
	{
		m_bZPhi = true;
		m_bRX = false;	
	}

	m_bLockChanged=m_pManualImpedParas->m_bLockChanged;

}

void QImpedanceManuWidget::initData()
{
	m_pCmb_FaultType->setCurrentIndex(m_pManualImpedParas->m_nFaultType);
	m_pCmb_CalMode->setCurrentIndex(m_pManualImpedParas->m_nCalMode);
	m_pCmb_CacuType->setCurrentIndex(m_pManualImpedParas->m_nOffsetsMode);

	if (m_bZPhi)
	{
		m_pRad_Z->setChecked(true);
		m_pRad_RX->setChecked(false);
	}
	else
	{
		m_pRad_Z->setChecked(false);
		m_pRad_RX->setChecked(true);
	}

	m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent,'f',3));//短路电流
	m_pAmpEdit->setText(QString::number(m_pManualImpedParas->m_fAmplitudeOrKr,'f',3));
	m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
	m_pZEdit->setText(QString::number( m_pManualImpedParas->m_fZAmp,'f',3));
	m_pPhiEdit->setText(QString::number(m_pManualImpedParas->m_fZAngle,'f',3));
	m_pREdit->setText(QString::number(m_pManualImpedParas-> m_fR,'f',3));
	m_pXEdit->setText(QString::number(m_pManualImpedParas->m_fX,'f',3));
	m_PrepareTimeEdit->setText(QString::number(m_pManualImpedParas->m_fPrepareTime,'f',3));
	m_PreFaultTimeEdit->setText(QString::number(m_pManualImpedParas->m_fPreFaultTime,'f',3));
	m_pStepEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStep,'f',3));
	m_pStartEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStart,'f',3));
	m_pTimeEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStepTime,'f',3));
	m_pEndEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fEnd,'f',3));
	m_pTrigDelayEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fTrigDelay,'f',3));
	//m_pActTimeEdit->setText(QString::number(m_oManualImpedTest.m_oManuImpedResult.m_fActValue,'f',3));

	OnRXValue();
	slot_RadioZPhiAndRX_StateChanged();
	slot_CmbCalModeIndexChanged(m_pManualImpedParas->m_nCalMode);
	slot_CmbCacuTypeIndexChanged(m_pManualImpedParas->m_nOffsetsMode);
	slot_Chb_AutoStateChanged(0);
	slot_Chb_MutationStateChanged(0);
	
}


void QImpedanceManuWidget::slot_CmbErrorTypeIndexChanged(int index)
{
	if(m_pCmb_FaultType->IsScrolling())
	{
		return;
	}

	m_pManualImpedParas->m_nFaultType = index;
}

void QImpedanceManuWidget::slot_RadioZPhiAndRX_StateChanged( )
{
	if (m_pRad_Z->isChecked())
	{
		 m_pManualImpedParas->m_nImped = 0;
		m_bZPhi = true;	
		m_bRX = false;
		m_pRad_RX->setChecked(false);
		m_pZLabel->setEnabled(true);
		m_pZEdit->setEnabled(true);
		m_pPhiEdit->setEnabled(true);

		m_pRXLabel->setEnabled(false);
		m_pREdit->setEnabled(false);
		m_pXEdit->setEnabled(false);

		FirstModeListChanged();
		SecondModeListChanged();
	}
	else
	{
		 m_pManualImpedParas->m_nImped = 1;
		m_bZPhi = false;	
		m_bRX = true;
		m_pRad_RX->setChecked(true);
		m_pZLabel->setEnabled(false);
		m_pZEdit->setEnabled(false);
		m_pPhiEdit->setEnabled(false);

		m_pRXLabel->setEnabled(true);
		m_pREdit->setEnabled(true);
		m_pXEdit->setEnabled(true);
		FirstModeListChanged();
		SecondModeListChanged();

	}
	g_oSttTestResourceMngr.m_oRtDataMngr.SetAutoMode(m_pManualImpedParas->m_bAuto);
}

void QImpedanceManuWidget::slot_Chb_AutoStateChanged(int index)
{
	if (m_pAuto_CheckBox->isChecked())
	{
		m_pManualImpedParas->m_bAuto=1;
		m_pMutation_CheckBox->setEnabled(true);
		m_pTimeEdit->setEnabled(true);
		m_pStartEdit->setEnabled(true);
		m_pEndEdit->setEnabled(true);
		m_pbn_Up->setEnabled(false);
		m_pbn_Down->setEnabled(false);
	}
	else
	{
		m_pManualImpedParas->m_bAuto =0;
		m_pManualImpedParas->m_bMutation =0;
		m_pMutation_CheckBox->setChecked(false);
		m_pMutation_CheckBox->setEnabled(false);
		//变换时间、终值、始值置灰
		m_pTimeEdit->setEnabled(false);
		m_pStartEdit->setEnabled(false);
		m_pEndEdit->setEnabled(false);
		m_pbn_Up->setEnabled(true);
		m_pbn_Down->setEnabled(true);
	}

}

void QImpedanceManuWidget::slot_Chb_MutationStateChanged(int index)
{
	if (m_pMutation_CheckBox->isChecked())
	{
		m_pManualImpedParas->m_bMutation=1;
		m_PrepareTimeEdit->setEnabled(true);
		m_PreFaultTimeEdit->setEnabled(true);
	}
	else
	{
		m_pManualImpedParas->m_bMutation=0;
		m_PrepareTimeEdit->setEnabled(false);
		m_PreFaultTimeEdit->setEnabled(false);
	}
}



void QImpedanceManuWidget::slot_lneZ_TextKeyBoard()
{
	m_pManualImpedParas->m_fZAmp = slot_lne_Changed(m_pZEdit);
	m_pZEdit->setText(QString::number( m_pManualImpedParas->m_fZAmp,'f',3));
	OnRXValue();
}

void QImpedanceManuWidget::slot_lnePhi_TextKeyBoard()
{
	m_pManualImpedParas->m_fZAngle = slot_lne_Changed(m_pPhiEdit);
	while (m_pManualImpedParas->m_fZAngle<0)
	{
		m_pManualImpedParas->m_fZAngle += 360;
	}
	while (m_pManualImpedParas->m_fZAngle>360)
	{
		m_pManualImpedParas->m_fZAngle -= 360;
	}
	m_pPhiEdit->setText(QString::number(m_pManualImpedParas->m_fZAngle,'f',3));
	OnRXValue();
}

void QImpedanceManuWidget::slot_lneR_TextKeyBoard()
{
	m_pManualImpedParas->m_fR = slot_lne_Changed(m_pREdit);
	m_pREdit->setText(QString::number(m_pManualImpedParas->m_fR,'f',3));
	OnRXValue();
}


void QImpedanceManuWidget::slot_lneX_TextKeyBoard()
{
	m_pManualImpedParas->m_fX = slot_lne_Changed(m_pXEdit);
	m_pXEdit->setText(QString::number(m_pManualImpedParas->m_fX,'f',3));
	OnRXValue();
}

//阻抗类型
void QImpedanceManuWidget::slot_CmbCalModeIndexChanged( int index)
{
	if(m_pCmb_CalMode->IsScrolling())
	{
		return;
	}

	m_pManualImpedParas->m_nCalMode = index;

	switch(index)
	{
	case 0:
		{
			m_pDLLabel->setText(tr("短路电流（A）"));
			m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent,'f',3));//短路电流
			m_pShortIOrZsAngleEdit->setVisible(false);//不显示

			//FirstModeListChanged();
		}
		break;
	case 1:
		{
			m_pDLLabel->setText(tr("短路电压（V）"));
			m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSZSAmp,'f',3));//短路电压
			m_pShortIOrZsAngleEdit->setVisible(false);//不显示

			//FirstModeListChanged();
		}
		break;
	case 2:
		{
			m_pDLLabel->setText(tr("Zs"));
			m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSZSAmp,'f',3));
			m_pShortIOrZsAngleEdit->setText(QString::number(m_pManualImpedParas->m_fSZSAngle,'f',3));
			m_pShortIOrZsAngleEdit->setVisible(true);//显示

			//FirstModeListChanged();
		}
		break;
	default:
		break;
	}
}
void QImpedanceManuWidget::FirstModeListChanged()
{
	int index = m_pManualImpedParas->m_nFirstMode;
	m_FirstModeList.clear();
	/*if (m_pManualImpedParas->m_nCalMode==0)
	{
		m_FirstModeList<< "Z" << "R" << "X" << "短路电流";
	} 
	else if (m_pManualImpedParas->m_nCalMode==1)
	{
		m_FirstModeList<< "Z" << "R" << "X" << "短路电压";
	}
	else
	{
		m_FirstModeList<< "Z" << "R" << "X";
		if(index==3)
		{
			index--;
		}
	}*/
	if (m_pManualImpedParas->m_nImped==0)//z
	{
		m_FirstModeList<< "Z";
	} 
	if (m_pManualImpedParas->m_nImped==1)
	{
		m_FirstModeList<< "R" << "X" ;
	}
	
	
	m_pCmb_FirstMode->clear();
	m_pCmb_FirstMode->addItems(m_FirstModeList);
	m_pManualImpedParas->m_nFirstMode = 0;

	m_pCmb_FirstMode->setCurrentIndex(m_pManualImpedParas->m_nFirstMode);
}

void QImpedanceManuWidget::SecondModeListChanged()
{
	int index = m_pManualImpedParas->m_nSecondMode;
	m_SecondModeList.clear();

	if (m_pManualImpedParas->m_nImped==0)//z
	{
		m_SecondModeList<< "幅值"<<"相位";
	} 
	if (m_pManualImpedParas->m_nImped==1)
	{
		m_SecondModeList<< "幅值" ;
	}
	
	m_pCmb_SecondMode->clear();
	m_pCmb_SecondMode->addItems(m_SecondModeList);
	m_pManualImpedParas->m_nSecondMode = 0;

	m_pCmb_SecondMode->setCurrentIndex(m_pManualImpedParas->m_nSecondMode);
}


void QImpedanceManuWidget::slot_lneDLZSAmp_TextKeyBoard()
{
	if (m_pManualImpedParas->m_nCalMode==0)//定电流
	{
		m_pManualImpedParas->m_fSCCurrent = slot_lne_Changed(m_pShortIOrZsAmpEdit);
		m_pManualImpedParas->m_fSCCurrent = setLimit(0,g_oLocalSysPara.m_fAC_CurMax,m_pManualImpedParas->m_fSCCurrent);
		m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent,'f',3));
	} 
	else if (m_pManualImpedParas->m_nCalMode==1)//定电压
	{
		m_pManualImpedParas->m_fSCVoltage = slot_lne_Changed(m_pShortIOrZsAmpEdit);
		m_pManualImpedParas->m_fSCVoltage = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,m_pManualImpedParas->m_fSCVoltage);
		m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCVoltage,'f',3));
	}
	else//系统侧阻抗
	{
		m_pManualImpedParas->m_fSZSAmp = slot_lne_Changed(m_pShortIOrZsAmpEdit);
		m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSZSAmp,'f',3));
	}
}

void QImpedanceManuWidget::slot_lneDLZSAngle_TextKeyBoard()
{
	m_pManualImpedParas->m_fSZSAngle = slot_lne_Changed(m_pShortIOrZsAngleEdit);
	m_pShortIOrZsAngleEdit->setText(QString::number(m_pManualImpedParas->m_fSZSAngle,'f',3));
}

void QImpedanceManuWidget::slot_CmbCacuTypeIndexChanged( int index)//零序补偿
{
	if(m_pCmb_CacuType->IsScrolling())
	{
		return;
	}

	m_pManualImpedParas->m_nOffsetsMode = index;
	switch(index)
	{
	case 0:
		{
			xlang_SetLangStrToWidget(m_pAmpLabel, "State_Amp", XLang_Ctrls_QLabel);
			xlang_SetLangStrToWidget(m_pAngleLabel, "State_Angle", XLang_Ctrls_QLabel);
			m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
		}
		break;
	case 1:
		{
			m_pAmpLabel->setText(tr("Kr"));
			m_pAngleLabel->setText(tr("Kx"));
			m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
		}
		break;
	case 2:
		{
			xlang_SetLangStrToWidget(m_pAmpLabel, "State_Amp", XLang_Ctrls_QLabel);
			xlang_SetLangStrToWidget(m_pAngleLabel, "State_Angle", XLang_Ctrls_QLabel);
			m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
		}
		break;
	default:
		break;
	}
}

void QImpedanceManuWidget::slot_lneAmplitudeOrKr_TextKeyBoard()
{
	m_pManualImpedParas->m_fAmplitudeOrKr = slot_lne_Changed(m_pAmpEdit);
	m_pAmpEdit->setText(QString::number(m_pManualImpedParas->m_fAmplitudeOrKr,'f',3));
}


void QImpedanceManuWidget::slot_lnePhaseOrKx_TextKeyBoard()
{
	m_pManualImpedParas->m_fPhaseOrKx = slot_lne_Changed(m_pAngleEdit);
	//判断零序补偿模式
	if(m_pManualImpedParas->m_nOffsetsMode == 1)
	{
		m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
	}
	else
	{
		while(m_pManualImpedParas->m_fPhaseOrKx<0)
		{
			m_pManualImpedParas->m_fPhaseOrKx += 360;
		}
		while(m_pManualImpedParas->m_fPhaseOrKx>360)
		{
			m_pManualImpedParas->m_fPhaseOrKx -= 360;
		}
		m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
	}
}

void QImpedanceManuWidget::slot_lnePrepareTime_TextKeyBoard()
{
	m_pManualImpedParas->m_fPrepareTime = slot_lne_Changed(m_PrepareTimeEdit);
	m_PrepareTimeEdit->setText(QString::number(m_pManualImpedParas->m_fPrepareTime,'f',3));
}

void QImpedanceManuWidget::slot_PreFaultTime_TextKeyBoard()
{
	m_pManualImpedParas->m_fPreFaultTime = slot_lne_Changed(m_PreFaultTimeEdit);
	m_PreFaultTimeEdit->setText(QString::number(m_pManualImpedParas->m_fPreFaultTime,'f',3));
}

void QImpedanceManuWidget::slot_lneStep_TextKeyBoard()
{
	m_pManualImpedParas->m_manuImpedGradient.fStep = slot_lne_Changed(m_pStepEdit);
	m_pStepEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStep,'f',3));	

}

void QImpedanceManuWidget::slot_lneTime_TextKeyBoard()
{
	m_pManualImpedParas->m_manuImpedGradient.fStepTime = slot_lne_Changed(m_pTimeEdit);
	m_pTimeEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStepTime,'f',3));
}


void QImpedanceManuWidget::slot_lneStart_TextKeyBoard()
{
	m_pManualImpedParas->m_manuImpedGradient.fStart = slot_lne_Changed(m_pStartEdit);
	m_pStartEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStart,'f',3));

	if(m_pManualImpedParas->m_nCalMode==1)
	{
		g_theTestCntrFrame->UpdateVectorRange(m_pManualImpedParas->m_manuImpedGradient.fStart,
			m_pManualImpedParas->m_manuImpedGradient.fEnd, 0, 0);
	}
	if(m_pManualImpedParas->m_nCalMode==0) 
	{
		g_theTestCntrFrame->UpdateVectorRange(0, 0, m_pManualImpedParas->m_manuImpedGradient.fStart,
			m_pManualImpedParas->m_manuImpedGradient.fEnd);
	}
}


void QImpedanceManuWidget::slot_lneEnd_TextKeyBoard()
{
	m_pManualImpedParas->m_manuImpedGradient.fEnd = slot_lne_Changed(m_pEndEdit);
	m_pEndEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fEnd,'f',3));

	if(m_pManualImpedParas->m_nCalMode==1)
	{
		g_theTestCntrFrame->UpdateVectorRange(m_pManualImpedParas->m_manuImpedGradient.fStart,
			m_pManualImpedParas->m_manuImpedGradient.fEnd, 0, 0);
	}
	if(m_pManualImpedParas->m_nCalMode==0) 
	{
		g_theTestCntrFrame->UpdateVectorRange(0, 0, m_pManualImpedParas->m_manuImpedGradient.fStart,
			m_pManualImpedParas->m_manuImpedGradient.fEnd);
	}
}

void QImpedanceManuWidget::slot_lneTrigDelay_TextKeyBoard()
{
	m_pManualImpedParas->m_manuImpedGradient.fTrigDelay = slot_lne_Changed(m_pTrigDelayEdit);
	m_pTrigDelayEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fTrigDelay,'f',3));
}

void QImpedanceManuWidget::slot_lneActTime_TextKeyBoard()
{
	m_oManualImpedTest.m_oManuImpedResult.m_fActValue  = slot_lne_Changed(m_pActTimeEdit);
	m_pActTimeEdit->setText(QString::number(m_oManualImpedTest.m_oManuImpedResult.m_fActValue ,'f',3));
}

void QImpedanceManuWidget::slot_CmbFirstModeIndexChanged(int index)
{
	if(m_pCmb_FirstMode->IsScrolling())
	{
		return;
	}

	m_pManualImpedParas->m_nFirstMode = index;
	QString strStep,strStart,strEnd;
	strStep="变化步长（";
	strStart="变化始值（";
	strEnd="变化终值（";
	//获取combox
	if (m_pManualImpedParas->m_nFirstMode==3 && m_pManualImpedParas->m_nCalMode==0)//除变化时间外，其他三个值变换单位为A
	{
		m_pStepLabel->setText(strStep+strUnit[0]+"）");	
		m_pStartLabel->setText(strStart+strUnit[0]+"）");	
		m_pEndLabel->setText(strEnd+strUnit[0]+"）");	
	} 
	else if (m_pManualImpedParas->m_nFirstMode==3 && m_pManualImpedParas->m_nCalMode==1)//除变化时间外，其他三个值变换单位为V
	{
		m_pStepLabel->setText(strStep+strUnit[1]+"）");	
		m_pStartLabel->setText(strStart+strUnit[1]+"）");	
		m_pEndLabel->setText(strEnd+strUnit[1]+"）");	
	}
	else//除变化时间外，其他三个值变换单位为Ω
	{
		if (m_pManualImpedParas->m_nSecondMode==0)
		{
			m_pStepLabel->setText(strStep+strUnit[2]+"）");	
			m_pStartLabel->setText(strStart+strUnit[2]+"）");	
			m_pEndLabel->setText(strEnd+strUnit[2]+"）");	
		}
		else
		{
			m_pStepLabel->setText(strStep+strUnit[4]+"）");	
			m_pStartLabel->setText(strStart+strUnit[4]+"）");	
			m_pEndLabel->setText(strEnd+strUnit[4]+"）");	
		}
		
	}
}
void QImpedanceManuWidget::slot_CmbSecondModeIndexChanged(int index)
{
	if(m_pCmb_SecondMode->IsScrolling())
	{
		return;
	}
	m_pManualImpedParas->m_nSecondMode = index;

	QString strStep,strStart,strEnd;
	strStep="变化步长（";
	strStart="变化始值（";
	strEnd="变化终值（";

	//获取combox
	if (m_pManualImpedParas->m_nSecondMode==0 && m_pManualImpedParas->m_nFirstMode !=3)//除变化时间外，其他三个值变换幅值单位为Ω
	{
		m_pStepLabel->setText(strStep+strUnit[2]+"）");	
		m_pStartLabel->setText(strStart+strUnit[2]+"）");	
		m_pEndLabel->setText(strEnd+strUnit[2]+"）");	
	} 
	else if (m_pManualImpedParas->m_nSecondMode==1 && m_pManualImpedParas->m_nFirstMode !=3)//除变化时间外，其他三个值变换相位单位为°
	{
		m_pStepLabel->setText(strStep+strUnit[4]+"）");	
		m_pStartLabel->setText(strStart+strUnit[4]+"）");	
		m_pEndLabel->setText(strEnd+strUnit[4]+"）");	
	}
}
void QImpedanceManuWidget::slot_CmbChangeTypeIndexChanged(int index)
{
	if(m_pCmb_SecondMode->IsScrolling())
	{
		return;
	}
	m_pManualImpedParas->m_manuImpedGradient.nMode = index;

}

void QImpedanceManuWidget::OnRXValue()
{
	if( m_pManualImpedParas->m_nImped==0)
	{	
		if( m_pManualImpedParas->m_fZAmp<0.0)m_pManualImpedParas->m_fZAmp=0.0;
		if(m_pManualImpedParas->m_fZAngle<-180.0)m_pManualImpedParas->m_fZAngle+=360.0;
		if(m_pManualImpedParas->m_fZAngle>360.0)m_pManualImpedParas->m_fZAngle-=360.0;
		m_pManualImpedParas->m_fX= m_pManualImpedParas->m_fZAmp*sin(m_pManualImpedParas->m_fZAngle*3.14159/180.0);
		m_pManualImpedParas->m_fR= m_pManualImpedParas->m_fZAmp*cos(m_pManualImpedParas->m_fZAngle*3.14159/180.0);
	}
	else
	{
		 m_pManualImpedParas->m_fZAmp=hypot(m_pManualImpedParas->m_fX,m_pManualImpedParas->m_fR);
		if(fabs(m_pManualImpedParas->m_fR)>0.0001)m_pManualImpedParas->m_fZAngle=atan2(m_pManualImpedParas->m_fX,m_pManualImpedParas->m_fR)*180.0/3.14159;
		else m_pManualImpedParas->m_fZAngle=0.0;
	}

	m_pZEdit->setText(QString::number(m_pManualImpedParas->m_fZAmp,'f',3));
	m_pPhiEdit->setText(QString::number(m_pManualImpedParas->m_fZAngle,'f',3));
	m_pREdit->setText(QString::number(m_pManualImpedParas->m_fR,'f',3));
	m_pXEdit->setText(QString::number(m_pManualImpedParas->m_fX,'f',3));
}

void QImpedanceManuWidget::slot_pbn_ClearClicked()
{
	m_oManualImpedTest.m_oManuImpedResult.m_fActValue =0.000;
	m_pActTimeEdit->setText(QString::number(m_oManualImpedTest.m_oManuImpedResult.m_fActValue,'f',3));
}

void QImpedanceManuWidget::slot_pbn_UpClicked()
{
	if (m_pManualImpedParas->m_nImped == 0 && m_pManualImpedParas->m_nSecondMode==0)//Z
	{
		m_pManualImpedParas->m_fZAmp =slot_lne_Changed(m_pZEdit);
	m_pManualImpedParas->m_fZAmp+=0.5;
	if (m_pManualImpedParas->m_fZAmp<0 || bflag ==true)
	{
		if (!bflag)
		{
			bflag =true;
			fValue = m_pManualImpedParas->m_fZAmp;
			m_pManualImpedParas->m_fZAmp = qAbs(fValue);
		}
		else
		{
			fValue+=0.5;
			m_pManualImpedParas->m_fZAmp = qAbs(fValue);
		}	
	}
	else
	{
		bflag =false;
	}
		OnRXValue();
	} 
	else if (m_pManualImpedParas->m_nImped == 0 && m_pManualImpedParas->m_nSecondMode==1)//z-phi
	{
		m_pManualImpedParas->m_fZAngle =slot_lne_Changed(m_pPhiEdit);
		m_pManualImpedParas->m_fZAngle+=0.5;
		OnRXValue();
	}
	else if (m_pManualImpedParas->m_nFirstMode == 0 && m_pManualImpedParas->m_nImped==1)//R
	{
		m_pManualImpedParas->m_fR =slot_lne_Changed(m_pREdit);
		m_pManualImpedParas->m_fR+=0.5;
		OnRXValue();
	}
	else if (m_pManualImpedParas->m_nFirstMode == 1 && m_pManualImpedParas->m_nImped==1)//X
	{
		m_pManualImpedParas->m_fX =slot_lne_Changed(m_pXEdit);
		m_pManualImpedParas->m_fX+=0.5;
		OnRXValue();

	}
	//else if (m_pManualImpedParas->m_nFirstMode == 3 && m_pManualImpedParas->m_nCalMode ==0)//电流
	//{
	//	m_pManualImpedParas->m_fSCCurrent =slot_lne_Changed(m_pShortIOrZsAmpEdit);
	//	m_pManualImpedParas->m_fSCCurrent+=0.5;
	//	m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent,'f',3));
	//}
	//else if (m_pManualImpedParas->m_nFirstMode == 3 && m_pManualImpedParas->m_nCalMode ==1)//电压
	//{
	//	m_pManualImpedParas->m_fSCVoltage =slot_lne_Changed(m_pShortIOrZsAmpEdit);
	//	m_pManualImpedParas->m_fSCVoltage+=0.5;
	//	m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCVoltage,'f',3));
	//}

}

void QImpedanceManuWidget::slot_pbn_DownClicked()
{
	if (m_pManualImpedParas->m_nImped == 0 && m_pManualImpedParas->m_nSecondMode==0)//Z
	{
		m_pManualImpedParas->m_fZAmp =slot_lne_Changed(m_pZEdit);
	m_pManualImpedParas->m_fZAmp-=0.5;
	if (m_pManualImpedParas->m_fZAmp<0 || bflag ==true)
	{
		if (!bflag)
		{
			bflag =true;
			fValue = m_pManualImpedParas->m_fZAmp;
			m_pManualImpedParas->m_fZAmp = qAbs(fValue);
		}
		else
		{
			fValue-=0.5;
			m_pManualImpedParas->m_fZAmp = qAbs(fValue);
		}	
	}
	else
	{
		bflag =false;
	}
		OnRXValue();
	} 
	else if (m_pManualImpedParas->m_nImped == 0 && m_pManualImpedParas->m_nSecondMode==1)//z-phi
	{
		m_pManualImpedParas->m_fZAngle =slot_lne_Changed(m_pPhiEdit);
		m_pManualImpedParas->m_fZAngle+=0.5;
		OnRXValue();
	}
	else if (m_pManualImpedParas->m_nFirstMode == 0 && m_pManualImpedParas->m_nImped==1)//R
	{
		m_pManualImpedParas->m_fR =slot_lne_Changed(m_pREdit);
		m_pManualImpedParas->m_fR-=0.5;
		OnRXValue();
	}
	else if (m_pManualImpedParas->m_nFirstMode == 1 && m_pManualImpedParas->m_nImped==1)//X
	{
		m_pManualImpedParas->m_fX =slot_lne_Changed(m_pXEdit);
		m_pManualImpedParas->m_fX-=0.5;
		OnRXValue();
	}
	//else if (m_pManualImpedParas->m_nFirstMode == 3 && m_pManualImpedParas->m_nCalMode ==0)//电流
	//{
	//	m_pManualImpedParas->m_fSCCurrent =slot_lne_Changed(m_pShortIOrZsAmpEdit);
	//	m_pManualImpedParas->m_fSCCurrent-=0.5;
	//	m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent,'f',3));
	//}
	//else if (m_pManualImpedParas->m_nFirstMode == 3 && m_pManualImpedParas->m_nCalMode ==1)//电压
	//{
	//	m_pManualImpedParas->m_fSCVoltage =slot_lne_Changed(m_pShortIOrZsAmpEdit);
	//	m_pManualImpedParas->m_fSCVoltage-=0.5;
	//	m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCVoltage,'f',3));
	//}
}

void QImpedanceManuWidget::slot_pbn_LockClicked()
{
	if (m_pManualImpedParas->m_bLockChanged)
	{
		m_bControlLock = true;
		m_pManualImpedParas->m_bLockChanged = false;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_Lock", XLang_Ctrls_QPushButton);
		m_pbn_Lock->setIcon(m_imgUnlock);
	}
	else
	{
		m_bControlLock = false;
		m_pManualImpedParas->m_bLockChanged = true;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_UnLock", XLang_Ctrls_QPushButton);
		m_pbn_Lock->setIcon(m_imgLock);
	}

}

void QImpedanceManuWidget::slot_ck_Out1StateChanged()
{
	if (m_pBout_CheckBox[0]->checkState() == Qt::Checked)
	{
		m_pManualImpedParas->m_binOut[0].nState = 1;
	}
	else
	{
		m_pManualImpedParas->m_binOut[0].nState = 0;
	}
}

void QImpedanceManuWidget::slot_ck_Out2StateChanged()
{
	if (m_pBout_CheckBox[1]->checkState() == Qt::Checked)
	{
		m_pManualImpedParas->m_binOut[1].nState = 1;
	}
	else
	{
		m_pManualImpedParas->m_binOut[1].nState = 0;
	}
}

void QImpedanceManuWidget::slot_ck_Out3StateChanged()
{
	if (m_pBout_CheckBox[2]->checkState() == Qt::Checked)
	{
		m_pManualImpedParas->m_binOut[2].nState = 1;
	}
	else
	{
		m_pManualImpedParas->m_binOut[2].nState = 0;
	}
}

void QImpedanceManuWidget::slot_ck_Out4StateChanged()
{
	if (m_pBout_CheckBox[3]->checkState() == Qt::Checked)
	{
		m_pManualImpedParas->m_binOut[3].nState = 1;
	}
	else
	{
		m_pManualImpedParas->m_binOut[3].nState = 0;
	}
}

void QImpedanceManuWidget::slot_lne_TextChanged(QSttLineEdit* pLineEdit)
{
	QString strValue = pLineEdit->text();
	GetWidgetBoard_DigitData(4,strValue,pLineEdit,g_theTestCntrFrame);
}

float QImpedanceManuWidget::slot_lne_Changed(QSttLineEdit* pLineEdit)
{
	QString strValue = pLineEdit->text();
	float fv = strValue.toFloat();
	fv = setLimit(0,9999.999,fv);
	return fv;
}

void QImpedanceManuWidget::slot_currentChangedTabWidget(int nCurrIndex)
{
	if (g_pImpedanceManuTest == NULL)
	{
		return;
	}

	BOOL bVisibleBottomCtrlsGoose = (g_pImpedanceManuTest->m_pGooseParaWidget == m_pImpedanceManuTab->currentWidget());
	BOOL bVisibleBottomCtrlsFT3 = (g_pImpedanceManuTest->m_pFT3OutParaWidget == m_pImpedanceManuTab->currentWidget());
	BOOL bVisibleBottomCtrls=!(bVisibleBottomCtrlsGoose || bVisibleBottomCtrlsFT3);

	m_pBoutGroupBox->setVisible(bVisibleBottomCtrls);
	m_pbn_Lock->setVisible(bVisibleBottomCtrls);
	m_pbn_Up->setVisible(bVisibleBottomCtrls);
	m_pbn_Down->setVisible(bVisibleBottomCtrls);
	m_pBinarySet_PushButton->setVisible(bVisibleBottomCtrls);
	m_pEstimate_PushButton->setVisible(bVisibleBottomCtrls);
}
