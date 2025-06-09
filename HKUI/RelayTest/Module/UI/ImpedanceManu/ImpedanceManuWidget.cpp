#include "stdafx.h"
#include "ImpedanceManuWidget.h"
#include <QDialog>
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SttMacroParaEditViewImpedanceManu.h"
#include "../SttTestCntrFrameBase.h"
#include "../../Module/XLangResource_Native.h"

QImpedanceManuWidget::QImpedanceManuWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::QImpedanceManuWidget)
{
	ui->setupUi(this);

}

QImpedanceManuWidget::~QImpedanceManuWidget()
{
	 delete ui;
}

void QImpedanceManuWidget::InitUI()
{
	ui->m_pImpedanceManuTab->setTabText(0, /*"功能参数"*/g_sLangTxt_Impedance_FunParas); 
	ui->m_pShortIOrZsAngleEdit->setVisible(false);//不显示

	ui->m_pLock_PushButton->setDisabled(true);

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

	ui->m_pLock_PushButton->setIcon(m_imgUnlock);
	ui->m_pLock_PushButton->setIconSize(QSize(ui->m_pbn_Up->height(), ui->m_pbn_Up->height()));
	//ui->m_pLock_PushButton->setFixedWidth(ui->m_pbn_Up->width());
	ui->m_pLock_PushButton->setText(/*""*/g_sLangTxt_Manual_Lock);

	ui->m_pDLLabel->setText(g_sLangTxt_Impedance_ShortCurr);
	ui->groupBoxCoe->setTitle(g_sLangTxt_State_ZeroCoeff);
	ui->groupBoxCommon->setTitle(g_sLangTxt_Impedance_Variable);
	ui->m_PrepareTimeLabel->setText(g_sLangTxt_Impedance_NormalTime);
	ui->m_PreFaultTimeLabel->setText(g_sLangTxt_Impedance_FailTime);
	ui->m_pStartLabel->setText(g_sLangTxt_Impedance_ChangeStart);
	ui->m_pEndLabel->setText(g_sLangTxt_Impedance_ChangeEnd);
	ui->m_pStepLabel->setText(g_sLangTxt_Impedance_ChangStep);
}

void QImpedanceManuWidget::InitConnect()
{
	connect(ui->m_pZEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneZ_TextKeyBoard()));
	connect(ui->m_pPhiEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePhi_TextKeyBoard()));
	connect(ui->m_pREdit,SIGNAL(editingFinished()),this,SLOT(slot_lneR_TextKeyBoard()));
	connect(ui->m_pXEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneX_TextKeyBoard()));
	connect(ui->m_pShortIOrZsAmpEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneDLZSAmp_TextKeyBoard()));
	connect(ui->m_pShortIOrZsAngleEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneDLZSAngle_TextKeyBoard()));
	connect(ui->m_PrepareTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePrepareTime_TextKeyBoard()));
	connect(ui->m_PreFaultTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_PreFaultTime_TextKeyBoard()));
	connect(ui->m_pStepEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneStep_TextKeyBoard()));
	connect(ui->m_pStartEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneStart_TextKeyBoard()));
	connect(ui->m_pTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneTime_TextKeyBoard()));
	connect(ui->m_pEndEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneEnd_TextKeyBoard()));
	connect(ui->m_pTrigDelayEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneTrigDelay_TextKeyBoard()));
	//connect(m_pActTimeEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneActTime_TextKeyBoard()));
	connect(ui->m_pAmpEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneAmplitudeOrKr_TextKeyBoard()));
	connect(ui->m_pAngleEdit,SIGNAL(editingFinished()),this,SLOT(slot_lnePhaseOrKx_TextKeyBoard()));

	//connect(m_pbn_Clear, SIGNAL(clicked ()), this, SLOT(slot_pbn_ClearClicked()));
	connect(ui->m_pbn_Up, SIGNAL(clicked ()), this, SLOT(slot_pbn_UpClicked()));
	connect(ui->m_pbn_Down, SIGNAL(clicked ()), this, SLOT(slot_pbn_DownClicked()));
	//connect(ui->m_pLock_PushButton, SIGNAL(clicked ()), this, SLOT(slot_pbn_LockClicked()));

#ifdef _PSX_QT_LINUX_
    connect(ui->m_pZEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pZEdit)));
    connect(ui->m_pPhiEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pPhiEdit)));
    connect(ui->m_pREdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pREdit)));
    connect(ui->m_pXEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pXEdit)));
    connect(ui->m_pShortIOrZsAmpEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pShortIOrZsAmpEdit)));
    connect(ui->m_pShortIOrZsAngleEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pShortIOrZsAngleEdit)));
    connect(ui->m_PrepareTimeEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_PrepareTimeEdit)));
    connect(ui->m_PreFaultTimeEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_PreFaultTimeEdit)));
    connect(ui->m_pStepEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pStepEdit)));
    connect(ui->m_pStartEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pStartEdit)));
    connect(ui->m_pTimeEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pTimeEdit)));
    connect(ui->m_pEndEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pEndEdit)));
    connect(ui->m_pTrigDelayEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pTrigDelayEdit)));
	//connect(m_pActTimeEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pActTimeEdit)));
    connect(ui->m_pAmpEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pAmpEdit)));
    connect(ui->m_pAngleEdit,SIGNAL(clicked()),this,SLOT(slot_lne_TextChanged(m_pAngleEdit)));

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
	//递变参数
	InitGradientData();
	slot_lneStart_TextKeyBoard();
	slot_lneEnd_TextKeyBoard();
	slot_lneStep_TextKeyBoard();

	GlobalSetQcheckState_BinaryOut(ui->m_pBout_CheckBox0,m_pManualImpedParas->m_binOut,0);	
	GlobalSetQcheckState_BinaryOut(ui->m_pBout_CheckBox1,m_pManualImpedParas->m_binOut,1);
	GlobalSetQcheckState_BinaryOut(ui->m_pBout_CheckBox2,m_pManualImpedParas->m_binOut,2);
	GlobalSetQcheckState_BinaryOut(ui->m_pBout_CheckBox3,m_pManualImpedParas->m_binOut,3);

	Global_CheckBinSelect(m_pManualImpedParas->m_binIn,g_nBinCount, m_pManualImpedParas->m_nBinLogic);
}
void QImpedanceManuWidget::InitGradientData()
{
	if (m_pManualImpedParas->m_nSecondMode== phasor_type)
	{
		//20240802 gongyiping 
		//ui->m_pStartEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStart, 'f',1));
		((QSettingLineEdit*)ui->m_pStartEdit)->UpdateStructText(CVariantDataAddress(&m_pManualImpedParas->m_manuImpedGradient.fStart), 1);
		//ui->m_pEndEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fEnd, 'f',1));
		((QSettingLineEdit*)ui->m_pEndEdit)->UpdateStructText(CVariantDataAddress(&m_pManualImpedParas->m_manuImpedGradient.fEnd), 1);
		//ui->m_pStepEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStep, 'f',1));
		((QSettingLineEdit*)ui->m_pStepEdit)->UpdateStructText(CVariantDataAddress(&m_pManualImpedParas->m_manuImpedGradient.fStep), 1);		
	}
	else
	{
		//ui->m_pStartEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStart, 'f',3));
		((QSettingLineEdit*)ui->m_pStartEdit)->UpdateStructText(CVariantDataAddress(&m_pManualImpedParas->m_manuImpedGradient.fStart), 3);
		//ui->m_pEndEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fEnd, 'f',3));
		((QSettingLineEdit*)ui->m_pEndEdit)->UpdateStructText(CVariantDataAddress(&m_pManualImpedParas->m_manuImpedGradient.fEnd), 3);
		//ui->m_pStepEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStep, 'f',3));
		((QSettingLineEdit*)ui->m_pStepEdit)->UpdateStructText(CVariantDataAddress(&m_pManualImpedParas->m_manuImpedGradient.fStep), 3);
	}

	//ui->m_pTimeEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStepTime, 'f',3));
	((QSettingLineEdit*)ui->m_pTimeEdit)->UpdateStructText(CVariantDataAddress(&m_pManualImpedParas->m_manuImpedGradient.fStepTime), 3);

	ui->m_pCmb_SecondMode->setCurrentIndex(m_pManualImpedParas->m_nSecondMode);

}



void QImpedanceManuWidget::StartInit()
{
	m_bControlLock = false;
	m_pManualImpedParas->m_bLockChanged = m_bControlLock;
	
	bool bAuto = m_pManualImpedParas->m_bAuto;

	ui->m_pbn_Up->setDisabled(bAuto);
	ui->m_pbn_Down->setDisabled(bAuto);
	ui->m_pLock_PushButton->setDisabled(bAuto);

	ui->m_pBoutGroupBox->setDisabled(bAuto);
	ui->m_pBinarySet_PushButton->setDisabled(bAuto);
	ui->m_pEstimate_PushButton->setDisabled(bAuto);

	GlobalSetQcheckEnable_Binary(ui->m_pBout_CheckBox0,0,g_nBoutCount,!m_pManualImpedParas->m_bAuto);
	GlobalSetQcheckEnable_Binary(ui->m_pBout_CheckBox1,1,g_nBoutCount,!m_pManualImpedParas->m_bAuto);
	GlobalSetQcheckEnable_Binary(ui->m_pBout_CheckBox2,2,g_nBoutCount,!m_pManualImpedParas->m_bAuto);
	GlobalSetQcheckEnable_Binary(ui->m_pBout_CheckBox3,3,g_nBoutCount,!m_pManualImpedParas->m_bAuto);

	//ui->m_pTimeEdit->setDisabled(true);
	//ui->m_pStartEdit->setDisabled(true);
	//ui->m_pEndEdit->setDisabled(true);
	//ui->m_PrepareTimeEdit->setDisabled(true);
	//ui->m_PreFaultTimeEdit->setDisabled(true);
	////ui->m_pPhiEdit->setDisabled(true);
	////ui->m_pZEdit->setDisabled(true);
	////ui->m_pXEdit->setDisabled(true);
	////ui->m_pREdit->setDisabled(true);
	//ui->m_pShortIOrZsAmpEdit->setDisabled(true);
	//ui->m_pShortIOrZsAngleEdit->setDisabled(true);
	//ui->m_pTrigDelayEdit->setDisabled(true);
	//ui->m_pAmpEdit->setDisabled(true);
	//ui->m_pAngleEdit->setDisabled(true);

	//ui->m_pCmb_CalMode->setDisabled(true);
	//ui->m_pCmb_FaultType->setDisabled(true);
	//ui->m_pCmb_FirstMode->setDisabled(true);
	//ui->m_pCmb_SecondMode->setDisabled(true);
	//ui->m_pCmb_CacuType->setDisabled(true);
	//ui->m_pCmb_ChangeType->setDisabled(true);

	ui->m_pAuto_CheckBox->setDisabled(true);
}

void QImpedanceManuWidget::StopInit()
{
	m_bControlLock = true;
	m_pManualImpedParas->m_bLockChanged = false;
	ui->m_pLock_PushButton->setIcon(m_imgUnlock);
	ui->m_pLock_PushButton->setDisabled(true);
	ui->m_pbn_Up->setDisabled(m_pManualImpedParas->m_bAuto);
	ui->m_pbn_Down->setDisabled(m_pManualImpedParas->m_bAuto);

	ui->m_pStepEdit->setDisabled(false);
	ui->m_pTimeEdit->setDisabled(!m_pManualImpedParas->m_bAuto);
	ui->m_pStartEdit->setDisabled(!m_pManualImpedParas->m_bAuto);
	ui->m_pEndEdit->setDisabled(!m_pManualImpedParas->m_bAuto);
	//ui->m_PrepareTimeEdit->setDisabled(false);
	//ui->m_PreFaultTimeEdit->setDisabled(false);
	////ui->m_pPhiEdit->setDisabled(false);
	////ui->m_pZEdit->setDisabled(false);
	////ui->m_pXEdit->setDisabled(false);
	////ui->m_pREdit->setDisabled(false);
	//ui->m_pShortIOrZsAmpEdit->setDisabled(false);
	//ui->m_pShortIOrZsAngleEdit->setDisabled(false);
	//ui->m_pTrigDelayEdit->setDisabled(false);
	//ui->m_pAmpEdit->setDisabled(false);
	//ui->m_pAngleEdit->setDisabled(false);

	//ui->m_pCmb_CalMode->setDisabled(false);
	//ui->m_pCmb_FaultType->setDisabled(false);
	//ui->m_pCmb_FirstMode->setDisabled(false);
	//ui->m_pCmb_SecondMode->setDisabled(false);
	//ui->m_pCmb_CacuType->setDisabled(false);
	//ui->m_pCmb_ChangeType->setDisabled(false);

	ui->m_pAuto_CheckBox->setDisabled(false);

	ui->m_pBoutGroupBox->setDisabled(false);
	ui->m_pBinarySet_PushButton->setDisabled(false);
	ui->m_pEstimate_PushButton->setDisabled(false);

	m_pManualImpedParas->m_bLockChanged = false;
	GlobalSetQcheckEnable_Binary(ui->m_pBout_CheckBox0,0,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(ui->m_pBout_CheckBox1,1,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(ui->m_pBout_CheckBox2,2,g_nBoutCount,true);
	GlobalSetQcheckEnable_Binary(ui->m_pBout_CheckBox3,3,g_nBoutCount,true);
}

//初始化单位
void QImpedanceManuWidget::initstrUnit()
{
		strUnit[0]="A";
		strUnit[1]="V";
		strUnit[2]="Ω";
		strUnit[3]="Hz";
		strUnit[4]="°";
		strUnit[5]="s";
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
	m_CalModList << /*"定电流"*/g_sLangTxt_Impedance_ConstantCur << /*"定电压"*/g_sLangTxt_Impedance_ConstantVol << g_sLangTxt_Impedance_FixedSystem/*"固定系统侧阻抗"*/;

	//变量选择1
	m_FirstModeList<< "Z" << "R" << "X" << /*"短路电流"*/g_sLangTxt_Native_ShortCircuit;
	//变量选择2
	m_SecondModeList << /*"幅值"*/g_sLangTxt_Native_Amplitude << /*"相位"*/g_sLangTxt_Native_Phase;

	//零序补偿系数的模式
	//m_CalTypeList << "Ko" << "Kr,Kx" << "Z0/Z1";
	m_CalTypeList << _T("|K0|,Phi(K0)") << _T("RERL,XEXL") << _T("|Z0/Z1|,Phi(Z0/Z1)");

	//变化方式
	m_ChangeTypeList << /*"始-终"*/g_sLangTxt_Manual_S_E << /*"始-终-始"*/g_sLangTxt_Manual_S_E_S;

	ui->m_pCmb_FaultType->clear();
	ui->m_pCmb_FirstMode->clear();
	ui->m_pCmb_SecondMode->clear();
	ui->m_pCmb_CalMode->clear();
	ui->m_pCmb_CacuType->clear();
	ui->m_pCmb_ChangeType->clear();
	
	ui->m_pCmb_FaultType->addItems(m_errorTypeList);
	ui->m_pCmb_FirstMode->addItems(m_FirstModeList);
	ui->m_pCmb_SecondMode->addItems(m_SecondModeList);
	ui->m_pCmb_CalMode->addItems(m_CalModList);
	ui->m_pCmb_CacuType->addItems(m_CalTypeList);
	ui->m_pCmb_ChangeType->addItems(m_ChangeTypeList);
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
	ui->m_pCmb_FaultType->setCurrentIndex(m_pManualImpedParas->m_nFaultType);
	ui->m_pCmb_CalMode->setCurrentIndex(m_pManualImpedParas->m_nCalMode);
	ui->m_pCmb_CacuType->setCurrentIndex(m_pManualImpedParas->m_nOffsetsMode);

	if (m_bZPhi)
	{
		ui->m_pRad_Z->setChecked(true);
		ui->m_pRad_RX->setChecked(false);
	}
	else
	{
		ui->m_pRad_Z->setChecked(false);
		ui->m_pRad_RX->setChecked(true);
	}

	ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent,'f',3));//短路电流
	//ui->m_pAmpEdit->setText(QString::number(m_pManualImpedParas->m_fAmplitudeOrKr,'f',3));
	((QSettingLineEdit*)ui->m_pAmpEdit)->UpdateStructText(CVariantDataAddress(&m_pManualImpedParas->m_fAmplitudeOrKr), 3);
	//ui->m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
	((QSettingLineEdit*)ui->m_pAngleEdit)->UpdateStructText(CVariantDataAddress(&m_pManualImpedParas->m_fPhaseOrKx), 3);
	ui->m_pZEdit->setText(QString::number( m_pManualImpedParas->m_fZAmp,'f',3));
	ui->m_pPhiEdit->setText(QString::number(m_pManualImpedParas->m_fZAngle,'f',3));
	ui->m_pREdit->setText(QString::number(m_pManualImpedParas-> m_fR,'f',3));
	ui->m_pXEdit->setText(QString::number(m_pManualImpedParas->m_fX,'f',3));
	ui->m_PrepareTimeEdit->setText(QString::number(m_pManualImpedParas->m_fPrepareTime,'f',3));
	ui->m_PreFaultTimeEdit->setText(QString::number(m_pManualImpedParas->m_fPreFaultTime,'f',3));
	ui->m_pStepEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStep,'f',3));
	ui->m_pStartEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStart,'f',3));
	ui->m_pTimeEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStepTime,'f',3));
	ui->m_pEndEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fEnd,'f',3));
	ui->m_pTrigDelayEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fTrigDelay,'f',3));
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
	if(ui->m_pCmb_FaultType->IsScrolling())
	{
		return;
	}

	m_pManualImpedParas->m_nFaultType = index;
}

void QImpedanceManuWidget::slot_RadioZPhiAndRX_StateChanged( )
{
	if (ui->m_pRad_Z->isChecked())
	{
		 m_pManualImpedParas->m_nImped = 0;
		m_bZPhi = true;	
		m_bRX = false;
		ui->m_pRad_RX->setChecked(false);
		ui->m_pZLabel->setEnabled(true);
		ui->m_pZEdit->setEnabled(true);
		ui->m_pPhiEdit->setEnabled(true);

		ui->m_pRXLabel->setEnabled(false);
		ui->m_pREdit->setEnabled(false);
		ui->m_pXEdit->setEnabled(false);

		FirstModeListChanged();
		SecondModeListChanged();
	}
	else
	{
		 m_pManualImpedParas->m_nImped = 1;
		m_bZPhi = false;	
		m_bRX = true;
		ui->m_pRad_RX->setChecked(true);
		ui->m_pZLabel->setEnabled(false);
		ui->m_pZEdit->setEnabled(false);
		ui->m_pPhiEdit->setEnabled(false);

		ui->m_pRXLabel->setEnabled(true);
		ui->m_pREdit->setEnabled(true);
		ui->m_pXEdit->setEnabled(true);
		FirstModeListChanged();
		SecondModeListChanged();

	}
	g_oSttTestResourceMngr.m_oRtDataMngr.SetAutoMode(m_pManualImpedParas->m_bAuto);
}

void QImpedanceManuWidget::slot_Chb_AutoStateChanged(int index)
{
	if (ui->m_pAuto_CheckBox->isChecked())
	{
		m_pManualImpedParas->m_bAuto=1;
		ui->m_pMutation_CheckBox->setEnabled(true);
		ui->m_pTimeEdit->setEnabled(true);
		ui->m_pStartEdit->setEnabled(true);
		ui->m_pEndEdit->setEnabled(true);
		ui->m_pCmb_ChangeType->setEnabled(true);
		ui->m_pbn_Up->setEnabled(false);
		ui->m_pbn_Down->setEnabled(false);
	}
	else
	{
		m_pManualImpedParas->m_bAuto =0;
		m_pManualImpedParas->m_bMutation =0;
		ui->m_pMutation_CheckBox->setChecked(false);
		ui->m_pMutation_CheckBox->setEnabled(false);
		//变换时间、终值、始值置灰
		ui->m_pTimeEdit->setEnabled(false);
		ui->m_pStartEdit->setEnabled(false);
		ui->m_pEndEdit->setEnabled(false);
		ui->m_pCmb_ChangeType->setEnabled(false);
		ui->m_pbn_Up->setEnabled(true);
		ui->m_pbn_Down->setEnabled(true);
	}
        g_oSttTestResourceMngr.m_oRtDataMngr.SetAutoMode(m_pManualImpedParas->m_bAuto);

}

void QImpedanceManuWidget::slot_Chb_MutationStateChanged(int index)
{
	if (ui->m_pMutation_CheckBox->isChecked())
	{
		m_pManualImpedParas->m_bMutation=1;
		ui->m_PrepareTimeEdit->setEnabled(true);
		ui->m_PreFaultTimeEdit->setEnabled(true);
	}
	else
	{
		m_pManualImpedParas->m_bMutation=0;
		ui->m_PrepareTimeEdit->setEnabled(false);
		ui->m_PreFaultTimeEdit->setEnabled(false);
	}
}



void QImpedanceManuWidget::slot_lneZ_TextKeyBoard()
{
	//20240802 gongyiping 
	if (ui->m_pZEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pZEdit)->IsSetting())
		{
			return;
		}
	}

	m_pManualImpedParas->m_fZAmp = slot_lne_Changed(ui->m_pZEdit);
	ui->m_pZEdit->setText(QString::number( m_pManualImpedParas->m_fZAmp,'f',3));
	OnRXValue();
}

void QImpedanceManuWidget::slot_lnePhi_TextKeyBoard()
{
	//20240802 gongyiping 
	if (ui->m_pPhiEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pPhiEdit)->IsSetting())
		{
			return;
		}
	}

	m_pManualImpedParas->m_fZAngle = slot_lne_Changed(ui->m_pPhiEdit);
	while (m_pManualImpedParas->m_fZAngle<0)
	{
		m_pManualImpedParas->m_fZAngle += 360;
	}
	while (m_pManualImpedParas->m_fZAngle>360)
	{
		m_pManualImpedParas->m_fZAngle -= 360;
	}
	ui->m_pPhiEdit->setText(QString::number(m_pManualImpedParas->m_fZAngle,'f',3));
	OnRXValue();
}

void QImpedanceManuWidget::slot_lneR_TextKeyBoard()
{
	m_pManualImpedParas->m_fR = slot_lne_Changed(ui->m_pREdit);
	ui->m_pREdit->setText(QString::number(m_pManualImpedParas->m_fR,'f',3));
	OnRXValue();
}


void QImpedanceManuWidget::slot_lneX_TextKeyBoard()
{
	m_pManualImpedParas->m_fX = slot_lne_Changed(ui->m_pXEdit);
	ui->m_pXEdit->setText(QString::number(m_pManualImpedParas->m_fX,'f',3));
	OnRXValue();
}

//阻抗类型
void QImpedanceManuWidget::slot_CmbCalModeIndexChanged( int index)
{
	if(ui->m_pCmb_CalMode->IsScrolling())
	{
		return;
	}

	m_pManualImpedParas->m_nCalMode = index;

	switch(index)
	{
	case 0:
		{
			ui->m_pDLLabel->setText(/*tr("短路电流（A）")*/g_sLangTxt_Impedance_ShortCurr);
			ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent,'f',3));//短路电流
			ui->m_pShortIOrZsAngleEdit->setVisible(false);//不显示

			FirstModeListChanged();
		}
		break;
	case 1:
		{
			ui->m_pDLLabel->setText(/*tr("短路电压（V）")*/g_sLangTxt_Impedance_ShortVol);
			ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCVoltage,'f',3));//短路电压
			ui->m_pShortIOrZsAngleEdit->setVisible(false);//不显示

			FirstModeListChanged();
		}
		break;
	case 2:
		{
			ui->m_pDLLabel->setText(tr("Zs:"));
			ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSZSAmp,'f',3));
			ui->m_pShortIOrZsAngleEdit->setText(QString::number(m_pManualImpedParas->m_fSZSAngle,'f',3));
			ui->m_pShortIOrZsAngleEdit->setVisible(true);//显示

			FirstModeListChanged();
		}
		break;
	default:
		break;
	}
	UpdateData();
}
void QImpedanceManuWidget::FirstModeListChanged()
{
	m_FirstModeList.clear();
	if (m_pManualImpedParas->m_nCalMode==0 )//定电流
	{
		if (m_pManualImpedParas->m_nImped==0)//z 
	{
			m_FirstModeList<< "Z" << /*"短路电流"*/g_sLangTxt_Native_ShortCircuit;
	}
	else
	{
			m_FirstModeList<< "R"  << "X" << /*"短路电流"*/g_sLangTxt_Native_ShortCircuit;
		}
		
	} 
	else if (m_pManualImpedParas->m_nCalMode==1 )//定电压
	{
		if (m_pManualImpedParas->m_nImped==0)//z 
		{
			m_FirstModeList<< "Z" << /*"短路电压"*/g_sLangTxt_Native_ShortCircuitV;
		}
		else
	{
			m_FirstModeList<< "R"  << "X" << /*"短路电压"*/g_sLangTxt_Native_ShortCircuitV;
		}
	}
	else
	{
		if (m_pManualImpedParas->m_nImped==0)//z 
		{
			m_FirstModeList<< "Z" ;
		}
		else
	{
		m_FirstModeList<< "R" << "X" ;
	}
	}
	
	
	ui->m_pCmb_FirstMode->clear();
	ui->m_pCmb_FirstMode->addItems(m_FirstModeList);

	ui->m_pCmb_FirstMode->setCurrentIndex(0);
	slot_CmbFirstModeIndexChanged(0);
}

void QImpedanceManuWidget::SecondModeListChanged()
{
	int index = m_pManualImpedParas->m_nSecondMode;
	m_SecondModeList.clear();

	if (m_pManualImpedParas->m_nImped==0)//z
	{
		
		if (m_pManualImpedParas->m_nFirstMode == IMPED_MANUL_GRADIENTVHAMMMEL_SCCURRT 
			|| m_pManualImpedParas->m_nFirstMode == IMPED_MANUL_GRADIENTVHAMMMEL_SCVOLT)
	{
			m_SecondModeList << /*"幅值"*/g_sLangTxt_Native_Amplitude;

		}
		else
		{
			m_SecondModeList << /*"幅值"*/g_sLangTxt_Native_Amplitude <</*"相位"*/g_sLangTxt_Native_Phase;
		}
	} 
	else if (m_pManualImpedParas->m_nImped==1)
	{
		m_SecondModeList<< /*"幅值"*/g_sLangTxt_Native_Amplitude ;
	}
	
	ui->m_pCmb_SecondMode->clear();
	ui->m_pCmb_SecondMode->addItems(m_SecondModeList);
	m_pManualImpedParas->m_nSecondMode = 0;

	ui->m_pCmb_SecondMode->setCurrentIndex(m_pManualImpedParas->m_nSecondMode);
}


void QImpedanceManuWidget::slot_lneDLZSAmp_TextKeyBoard()
{
	if (m_pManualImpedParas->m_nCalMode==0)//定电流
	{
		m_pManualImpedParas->m_fSCCurrent = slot_lne_Changed(ui->m_pShortIOrZsAmpEdit);
		m_pManualImpedParas->m_fSCCurrent = setLimit(0,g_oLocalSysPara.m_fAC_CurMax,m_pManualImpedParas->m_fSCCurrent);
		ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent,'f',3));
	} 
	else if (m_pManualImpedParas->m_nCalMode==1)//定电压
	{
		m_pManualImpedParas->m_fSCVoltage = slot_lne_Changed(ui->m_pShortIOrZsAmpEdit);
		m_pManualImpedParas->m_fSCVoltage = setLimit(0,g_oLocalSysPara.m_fAC_VolMax,m_pManualImpedParas->m_fSCVoltage);
		ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCVoltage,'f',3));
	}
	else//系统侧阻抗
	{
		m_pManualImpedParas->m_fSZSAmp = slot_lne_Changed(ui->m_pShortIOrZsAmpEdit);
		ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSZSAmp,'f',3));
	}
}

void QImpedanceManuWidget::slot_lneDLZSAngle_TextKeyBoard()
{
	m_pManualImpedParas->m_fSZSAngle = slot_lne_Changed(ui->m_pShortIOrZsAngleEdit);
	ui->m_pShortIOrZsAngleEdit->setText(QString::number(m_pManualImpedParas->m_fSZSAngle,'f',3));
}

void QImpedanceManuWidget::slot_CmbCacuTypeIndexChanged( int index)//零序补偿
{
	if(ui->m_pCmb_CacuType->IsScrolling())
	{
		return;
	}

	m_pManualImpedParas->m_nOffsetsMode = index;
	switch(index)
	{
	case 0:
		{
			xlang_SetLangStrToWidget(ui->m_pAmpLabel, "State_Amp", XLang_Ctrls_QLabel);
			xlang_SetLangStrToWidget(ui->m_pAngleLabel, "State_Angle", XLang_Ctrls_QLabel);
			ui->m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
		}
		break;
	case 1:
		{
			ui->m_pAmpLabel->setText(tr("Kr:"));
			ui->m_pAngleLabel->setText(tr("Kx:"));
			ui->m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
		}
		break;
	case 2:
		{
			xlang_SetLangStrToWidget(ui->m_pAmpLabel, "State_Amp", XLang_Ctrls_QLabel);
			xlang_SetLangStrToWidget(ui->m_pAngleLabel, "State_Angle", XLang_Ctrls_QLabel);
			ui->m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
		}
		break;
	default:
		break;
	}
}

void QImpedanceManuWidget::slot_lneAmplitudeOrKr_TextKeyBoard()
{

	m_pManualImpedParas->m_fAmplitudeOrKr = slot_lne_Changed(ui->m_pAmpEdit);
	ui->m_pAmpEdit->setText(QString::number(m_pManualImpedParas->m_fAmplitudeOrKr,'f',3));
	
}


void QImpedanceManuWidget::slot_lnePhaseOrKx_TextKeyBoard()
{
	m_pManualImpedParas->m_fPhaseOrKx = slot_lne_Changed(ui->m_pAngleEdit);
	//判断零序补偿模式
	if(m_pManualImpedParas->m_nOffsetsMode == 1)
	{
		ui->m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
		
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
		ui->m_pAngleEdit->setText(QString::number(m_pManualImpedParas->m_fPhaseOrKx,'f',3));
	}
}

void QImpedanceManuWidget::slot_lnePrepareTime_TextKeyBoard()
{
	m_pManualImpedParas->m_fPrepareTime = slot_lne_Changed(ui->m_PrepareTimeEdit);
	ui->m_PrepareTimeEdit->setText(QString::number(m_pManualImpedParas->m_fPrepareTime,'f',3));
}

void QImpedanceManuWidget::slot_PreFaultTime_TextKeyBoard()
{
	m_pManualImpedParas->m_fPreFaultTime = slot_lne_Changed(ui->m_PreFaultTimeEdit);
	ui->m_PreFaultTimeEdit->setText(QString::number(m_pManualImpedParas->m_fPreFaultTime,'f',3));
}

void QImpedanceManuWidget::slot_lneStep_TextKeyBoard()
{
	/*m_pManualImpedParas->m_manuImpedGradient.fStep = slot_lne_Changed(ui->m_pStepEdit);
	ui->m_pStepEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStep,'f',3));	*/

	//20240802 gongyiping 
	if (ui->m_pStepEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pStepEdit)->IsSetting())
		{
			return;
		}
	}

	float fv = ui->m_pStepEdit->text().toFloat();
	if (qAbs(fv)<=EPSINON)
	{
		fv = 0.001;
	}

	QString strvar = ui->m_pCmb_FirstMode->currentText();
	//int index = m_pChGradientType_ComboBox->currentIndex();
	float fAcVMax = g_oLocalSysPara.m_fAC_VolMax;
	float fAcIMax = g_oLocalSysPara.m_fAC_CurMax;
	float fDcVMax = g_oLocalSysPara.m_fDC_VolMax;
	float fDcIMax = g_oLocalSysPara.m_fDC_CurMax;


	if (strvar.contains(g_sLangTxt_Native_ShortVolt))
	{
		if (fv>fAcVMax)
		{
			fv = fAcVMax;
		}

		if (fv<0)
		{
			fv = 0.001;
		}
	}
	else if (strvar.contains(g_sLangTxt_Native_ShortCircuit))
	{
		if (fv>fAcIMax)
		{
			fv = fAcIMax;
		}

		if (fv<0)
		{
			fv = 0.001;
		}
	}


	m_pManualImpedParas->m_manuImpedGradient.fStep = fv;
	ui->m_pStepEdit->setText(QString::number(fv,'f',3));
}

void QImpedanceManuWidget::slot_lneTime_TextKeyBoard()
{
	//20240802 gongyiping 
	if (ui->m_pTimeEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_pTimeEdit)->IsSetting())
		{
			return;
		}
	}

	m_pManualImpedParas->m_manuImpedGradient.fStepTime = slot_lne_Changed(ui->m_pTimeEdit);
	ui->m_pTimeEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStepTime,'f',3));
}


void QImpedanceManuWidget::slot_lneStart_TextKeyBoard()
{
	m_pManualImpedParas->m_manuImpedGradient.fStart = slot_lne_Changed(ui->m_pStartEdit);
	ui->m_pStartEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fStart,'f',3));

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
	m_pManualImpedParas->m_manuImpedGradient.fEnd = slot_lne_Changed(ui->m_pEndEdit);
	ui->m_pEndEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fEnd,'f',3));

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
	m_pManualImpedParas->m_manuImpedGradient.fTrigDelay = slot_lne_Changed(ui->m_pTrigDelayEdit);
	ui->m_pTrigDelayEdit->setText(QString::number(m_pManualImpedParas->m_manuImpedGradient.fTrigDelay,'f',3));
}

void QImpedanceManuWidget::slot_lneActTime_TextKeyBoard()
{
	//m_oManualImpedTest.m_oManuImpedResult.m_fActValue  = slot_lne_Changed(ui->m_pActTimeEdit);
	//ui->m_pActTimeEdit->setText(QString::number(m_oManualImpedTest.m_oManuImpedResult.m_fActValue ,'f',3));
}

void QImpedanceManuWidget::slot_CmbFirstModeIndexChanged(int index)
{
	if(ui->m_pCmb_FirstMode->IsScrolling())
	{
		return;
	}
	if (ui->m_pCmb_FirstMode->currentText() == "Z")
	{
		m_pManualImpedParas->m_nFirstMode = IMPED_MANUL_GRADIENTVHAMMMEL_Z;
	}
	else if (ui->m_pCmb_FirstMode->currentText() == "R")
	{
		m_pManualImpedParas->m_nFirstMode = IMPED_MANUL_GRADIENTVHAMMMEL_R;
	}
	else if(ui->m_pCmb_FirstMode->currentText() == "X")
	{
		m_pManualImpedParas->m_nFirstMode = IMPED_MANUL_GRADIENTVHAMMMEL_X;
	}
	QString strStep,strStart,strEnd;
	strStep=/*"变化步长（"*/g_sLangTxt_Gradient_Step;
	strStart=/*"变化始值（"*/g_sLangTxt_Gradient_Init;
	strEnd=/*"变化终值（"*/g_sLangTxt_Gradient_Finish;

	//获取combox
	if(ui->m_pCmb_FirstMode->currentText() ==/*"短路电流"*/g_sLangTxt_Native_ShortCircuit)//除变化时间外，其他三个值变换单位为A
	{
		m_pManualImpedParas->m_nFirstMode = IMPED_MANUL_GRADIENTVHAMMMEL_SCCURRT;
		ui->m_pStepLabel->setText(strStep + "(" + strUnit[0] + "):");
		ui->m_pStartLabel->setText(strStart + "(" + strUnit[0] + "):");
		ui->m_pEndLabel->setText(strEnd + "(" + strUnit[0] + "):");
		
	} 
	else if (ui->m_pCmb_FirstMode->currentText()==/*"短路电压"*/g_sLangTxt_Native_ShortCircuitV)//除变化时间外，其他三个值变换单位为V
	{
		m_pManualImpedParas->m_nFirstMode = IMPED_MANUL_GRADIENTVHAMMMEL_SCVOLT;
		ui->m_pStepLabel->setText(strStep + "(" + strUnit[1] + "):");
		ui->m_pStartLabel->setText(strStart + "(" + strUnit[1] + "):");
		ui->m_pEndLabel->setText(strEnd + "(" + strUnit[1] + "):");
	

	}
	else//除变化时间外，其他三个值变换单位为Ω
	{
		if (m_pManualImpedParas->m_nSecondMode==0)//幅值
		{
			ui->m_pStepLabel->setText(g_sLangTxt_Impedance_ChangStep);	
			ui->m_pStartLabel->setText(g_sLangTxt_Impedance_ChangeStart);	
			ui->m_pEndLabel->setText(g_sLangTxt_Impedance_ChangeEnd);	
		}
		else
		{
			ui->m_pStepLabel->setText(strStep+QString::fromLocal8Bit("(°):"));	
			ui->m_pStartLabel->setText(strStart+QString::fromLocal8Bit("(°):"));	
			ui->m_pEndLabel->setText(strEnd+QString::fromLocal8Bit("(°):"));	
		}
		
	}
	SecondModeListChanged();
}
void QImpedanceManuWidget::slot_CmbSecondModeIndexChanged(int index)
{
	if(ui->m_pCmb_SecondMode->IsScrolling())
	{
		return;
	}
	m_pManualImpedParas->m_nSecondMode = index;

	QString strStep,strStart,strEnd;
	strStep=/*"变化步长（"*/g_sLangTxt_Gradient_Step;
	strStart=/*"变化始值（"*/g_sLangTxt_Gradient_Init;
	strEnd=/*"变化终值（"*/g_sLangTxt_Gradient_Finish;
	//获取combox
	if (m_pManualImpedParas->m_nSecondMode==0 )//除变化时间外，其他三个值变换幅值单位为Ω
	{
		ui->m_pStepLabel->setText(g_sLangTxt_Impedance_ChangStep);	
		ui->m_pStartLabel->setText(g_sLangTxt_Impedance_ChangeStart);	
		ui->m_pEndLabel->setText(g_sLangTxt_Impedance_ChangeEnd);	
		if (ui->m_pCmb_FirstMode->currentText() ==/*"短路电流"*/g_sLangTxt_Native_ShortCircuit)
	{
			ui->m_pStepLabel->setText(strStep + "(" + strUnit[0] + "):");
			ui->m_pStartLabel->setText(strStart + "(" + strUnit[0] + "):");
			ui->m_pEndLabel->setText(strEnd + "(" + strUnit[0] + "):");
	}
		if (ui->m_pCmb_FirstMode->currentText() ==/*"短路电压"*/g_sLangTxt_Native_ShortCircuitV)
	{
			ui->m_pStepLabel->setText(strStep + "(" + strUnit[1] + "):");
			ui->m_pStartLabel->setText(strStart + "(" + strUnit[1] + "):");
			ui->m_pEndLabel->setText(strEnd + "(" + strUnit[1] + "):");
	}
	} 
	else if (m_pManualImpedParas->m_nSecondMode==1 )//除变化时间外，其他三个值变换相位单位为°
	{
		ui->m_pStepLabel->setText(strStep+QString::fromLocal8Bit("(°):"));	
		ui->m_pStartLabel->setText(strStart+QString::fromLocal8Bit("(°):"));	
		ui->m_pEndLabel->setText(strEnd+QString::fromLocal8Bit("(°):"));	
	}
	
	UpdateData();
}
void QImpedanceManuWidget::slot_CmbChangeTypeIndexChanged(int index)
{
	if(ui->m_pCmb_SecondMode->IsScrolling())
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

	ui->m_pZEdit->setText(QString::number(m_pManualImpedParas->m_fZAmp,'f',3));
	ui->m_pPhiEdit->setText(QString::number(m_pManualImpedParas->m_fZAngle,'f',3));
	ui->m_pREdit->setText(QString::number(m_pManualImpedParas->m_fR,'f',3));
	ui->m_pXEdit->setText(QString::number(m_pManualImpedParas->m_fX,'f',3));
}

void QImpedanceManuWidget::slot_pbn_ClearClicked()
{
	/*m_oManualImpedTest.m_oManuImpedResult.m_fActValue =0.000;
	ui->m_pActTimeEdit->setText(QString::number(m_oManualImpedTest.m_oManuImpedResult.m_fActValue,'f',3));*/
}

void QImpedanceManuWidget::slot_pbn_UpClicked()
{
	switch (m_pManualImpedParas->m_nFirstMode)
	{
	case IMPED_MANUL_GRADIENTVHAMMMEL_Z:
		if (m_pManualImpedParas->m_nSecondMode == 0)
		{
			m_pManualImpedParas->m_fZAmp = slot_lne_Changed(ui->m_pZEdit);
			m_pManualImpedParas->m_fZAmp += m_pManualImpedParas->m_manuImpedGradient.fStep;
		if (m_pManualImpedParas->m_fZAmp<0)
		{
				m_pManualImpedParas->m_fZAmp = 0;
		}
		OnRXValue();
		}
		else if (m_pManualImpedParas->m_nSecondMode == 1)//z-phi
	{
			m_pManualImpedParas->m_fZAngle = slot_lne_Changed(ui->m_pPhiEdit);
			m_pManualImpedParas->m_fZAngle += m_pManualImpedParas->m_manuImpedGradient.fStep;
		OnRXValue();
	}
		break;
	case IMPED_MANUL_GRADIENTVHAMMMEL_R:
		m_pManualImpedParas->m_fR = slot_lne_Changed(ui->m_pREdit);
		m_pManualImpedParas->m_fR += m_pManualImpedParas->m_manuImpedGradient.fStep;
		OnRXValue();
		break;
	case IMPED_MANUL_GRADIENTVHAMMMEL_X:
		m_pManualImpedParas->m_fX = slot_lne_Changed(ui->m_pXEdit);
		m_pManualImpedParas->m_fX += m_pManualImpedParas->m_manuImpedGradient.fStep;
		OnRXValue();
		break;
	case IMPED_MANUL_GRADIENTVHAMMMEL_SCCURRT:
		m_pManualImpedParas->m_fSCCurrent = slot_lne_Changed(ui->m_pShortIOrZsAmpEdit);
		m_pManualImpedParas->m_fSCCurrent += m_pManualImpedParas->m_manuImpedGradient.fStep;
		m_pManualImpedParas->m_fSCCurrent = setLimit(0, g_oLocalSysPara.m_fAC_CurMax, m_pManualImpedParas->m_fSCCurrent);
		ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent, 'f', 3));
		break;
	case IMPED_MANUL_GRADIENTVHAMMMEL_SCVOLT:
		m_pManualImpedParas->m_fSCVoltage = slot_lne_Changed(ui->m_pShortIOrZsAmpEdit);
		m_pManualImpedParas->m_fSCVoltage += m_pManualImpedParas->m_manuImpedGradient.fStep;
		m_pManualImpedParas->m_fSCVoltage = setLimit(0, g_oLocalSysPara.m_fAC_VolMax, m_pManualImpedParas->m_fSCVoltage);
		ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCVoltage, 'f', 3));	
		break;

	}

}

void QImpedanceManuWidget::slot_pbn_DownClicked()
{
	switch (m_pManualImpedParas->m_nFirstMode)
	{
	case IMPED_MANUL_GRADIENTVHAMMMEL_Z:
		if (m_pManualImpedParas->m_nSecondMode == 0)
		{
			m_pManualImpedParas->m_fZAmp = slot_lne_Changed(ui->m_pZEdit);
			m_pManualImpedParas->m_fZAmp -= m_pManualImpedParas->m_manuImpedGradient.fStep;
		if (m_pManualImpedParas->m_fZAmp<0)
		{
				m_pManualImpedParas->m_fZAmp = 0;
		}
		OnRXValue();
		}
		else if (m_pManualImpedParas->m_nSecondMode == 1)//z-phi
	{
			m_pManualImpedParas->m_fZAngle = slot_lne_Changed(ui->m_pPhiEdit);
			m_pManualImpedParas->m_fZAngle -= m_pManualImpedParas->m_manuImpedGradient.fStep;
		OnRXValue();
	}
		break;
	case IMPED_MANUL_GRADIENTVHAMMMEL_R:
		m_pManualImpedParas->m_fR = slot_lne_Changed(ui->m_pREdit);
		m_pManualImpedParas->m_fR -= m_pManualImpedParas->m_manuImpedGradient.fStep;
		OnRXValue();
		break;
	case IMPED_MANUL_GRADIENTVHAMMMEL_X:
		m_pManualImpedParas->m_fX = slot_lne_Changed(ui->m_pXEdit);
		m_pManualImpedParas->m_fX -= m_pManualImpedParas->m_manuImpedGradient.fStep;
		OnRXValue();
		break;
	case IMPED_MANUL_GRADIENTVHAMMMEL_SCCURRT:
		m_pManualImpedParas->m_fSCCurrent = slot_lne_Changed(ui->m_pShortIOrZsAmpEdit);
		m_pManualImpedParas->m_fSCCurrent -= m_pManualImpedParas->m_manuImpedGradient.fStep;
		m_pManualImpedParas->m_fSCCurrent = setLimit(0, g_oLocalSysPara.m_fAC_CurMax, m_pManualImpedParas->m_fSCCurrent);
		ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCCurrent, 'f', 3));
		break;
	case IMPED_MANUL_GRADIENTVHAMMMEL_SCVOLT:
		m_pManualImpedParas->m_fSCVoltage = slot_lne_Changed(ui->m_pShortIOrZsAmpEdit);
		m_pManualImpedParas->m_fSCVoltage -= m_pManualImpedParas->m_manuImpedGradient.fStep;
		m_pManualImpedParas->m_fSCVoltage = setLimit(0, g_oLocalSysPara.m_fAC_VolMax, m_pManualImpedParas->m_fSCVoltage);
		ui->m_pShortIOrZsAmpEdit->setText(QString::number(m_pManualImpedParas->m_fSCVoltage, 'f', 3));	
		break;

	}

}

void QImpedanceManuWidget::slot_pbn_LockClicked()
{
	if (m_pManualImpedParas->m_bLockChanged)
	{
		m_bControlLock = true;
		m_pManualImpedParas->m_bLockChanged = false;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_Lock", XLang_Ctrls_QPushButton);
		ui->m_pLock_PushButton->setIcon(m_imgUnlock);
	}
	else
	{
		m_bControlLock = false;
		m_pManualImpedParas->m_bLockChanged = true;
		//xlang_SetLangStrToWidget(m_pBtnLock, "Manual_UnLock", XLang_Ctrls_QPushButton);
		ui->m_pLock_PushButton->setIcon(m_imgLock);
	}
	m_pManualImpedParas->m_bBinStop = TRUE;
}

void QImpedanceManuWidget::slot_ck_Out1StateChanged()
{
	if (ui->m_pBout_CheckBox0->checkState() == Qt::Checked)
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
	if (ui->m_pBout_CheckBox1->checkState() == Qt::Checked)
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
	if (ui->m_pBout_CheckBox2->checkState() == Qt::Checked)
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
	if (ui->m_pBout_CheckBox3->checkState() == Qt::Checked)
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

float QImpedanceManuWidget::slot_lne_Changed(QLineEdit* pLineEdit)
{
	//20240802 gongyiping 
	if (pLineEdit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)pLineEdit)->IsSetting())
		{
			float fv = ((QSettingLineEdit*)pLineEdit)->GetValue().toFloat();
			return fv;
		}
	}

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

	BOOL bVisibleBottomCtrlsGoose = (g_pImpedanceManuTest->m_pGooseParaWidget == ui->m_pImpedanceManuTab->currentWidget());
	BOOL bVisibleBottomCtrlsFT3 = (g_pImpedanceManuTest->m_pFT3OutParaWidget == ui->m_pImpedanceManuTab->currentWidget());
	BOOL bVisibleBottomCtrls=!(bVisibleBottomCtrlsGoose || bVisibleBottomCtrlsFT3);

	ui->m_pBoutGroupBox->setVisible(bVisibleBottomCtrls);
	ui->m_pLock_PushButton->setVisible(bVisibleBottomCtrls);
	ui->m_pbn_Up->setVisible(bVisibleBottomCtrls);
	ui->m_pbn_Down->setVisible(bVisibleBottomCtrls);
	ui->m_pBinarySet_PushButton->setVisible(bVisibleBottomCtrls);
	ui->m_pEstimate_PushButton->setVisible(bVisibleBottomCtrls);
}
