#include "SttMacroParaEditViewSwing.h"
#include "ui_SttMacroParaEditViewSwing.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SwingTestCommon.h"
#include "../SttTestCntrFrameBase.h"
#include "../SoftKeyboard/SoftKeyBoard.h"

extern QFont *g_pSttGlobalFont;
//extern QSttTestCntrFrameBase *g_theTestCntrFrame;
QSttMacroParaEditViewSwing::QSttMacroParaEditViewSwing(QWidget *parent) :
    ui(new Ui::QSttMacroParaEditViewSwing)
{
    //g_pCurrTestMacroUI_DataMaps = &m_oDvmDataMaps;//20240802 huangliang 在基类CSttMacroParaEditViewOriginal中以使用，删除此处代码
    ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

    m_pParasDlg = new QSwingTestParasDlg(this);
    m_pBinaryDlg = new QSwingTestBinarySignalDlg(this);
    m_pResultEvalDlg = new QSwingResultEvalDlg(this);
	m_pImpChart  = new QSwingImpChartWidget(this,true,true);
	
	m_pImpChart->hide();
	m_pImpChart->setParent(this);
	//m_pSysDiagramWidget = new QSwingSysDiagramWidget(this);
	m_pCurTest = new tmt_SwingTest;
	m_pResultEvalDlg->m_pCurTest = m_pCurTest;
	m_pParasDlg->m_pCurTest = m_pCurTest;
    m_pBinaryDlg->m_pCurTest = m_pCurTest;
	m_pImpChart->m_pCharacterDrawView->m_pCurTest = m_pCurTest;
	//m_pSysDiagramWidget->m_pCurTest = m_pCurTest;
	m_pCurrDataGroup = new CDataGroup;
	m_pParasDlg->m_pCurrDataGroup = m_pCurrDataGroup;
    m_pBinaryDlg->m_pCurrDataGroup = m_pCurrDataGroup;
	m_pResultEvalDlg->m_pCurrDataGroup = m_pCurrDataGroup;
	m_pGooseParaWidget = NULL;

    InitUI();
	InitLanuage();
	OpenTestTestMngrFile(m_strDefaultParaFile);
    SetDatas(NULL);
	UpdateParas();
	m_pResultEvalDlg->UpdateParas();
	m_pParasDlg->UpdateParas();
    m_pBinaryDlg->UpdateParas();
	m_pImpChart->SetImpDatas();
	//m_pSysDiagramWidget->SetDatas();

    connect(ui->m_cbRefault, SIGNAL(stateChanged(int)), this, SLOT(on_Refault_Check_StateChanged(int)));
    connect(ui->m_cbDzdt, SIGNAL(stateChanged(int)), this, SLOT(on_Dzdt_Check_StateChanged(int)));
    connect(ui->m_cbReciprocating, SIGNAL(stateChanged(int)), this, SLOT(on_Reciprocating_Check_StateChanged(int)));
    connect(m_pParasDlg, SIGNAL(sig_DataChanged()), this, SLOT(on_DataChanged()));
}

QSttMacroParaEditViewSwing::~QSttMacroParaEditViewSwing()
{
	if(NULL != m_pCurrDataGroup)
		delete m_pCurrDataGroup;

	if(NULL != m_pCurTest)
		delete m_pCurTest;

	if(NULL != m_pGooseParaWidget)
		delete m_pGooseParaWidget;

    delete ui;
}

void QSttMacroParaEditViewSwing::InitLanuage()
{
    xlang_SetLangStrToWidget(ui->m_labPAngleStart, g_sLangID_Swing_PowerAngleBegin, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labPAngleEnd, g_sLangID_Swing_PowerAngleEnd, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labSwingCycle, g_sLangID_Swing_SwingPeriod, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labSwingCount, g_sLangID_Swing_SwingCount, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labTripPoint, g_sLangID_Swing_TripPoint, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labTripSpeedUp, g_sLangID_Swing_TripSpeedUp, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labTripSpeedDown, g_sLangID_Swing_TripSpeedDown, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labFaultType, g_sLangID_Swing_FaultType, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labZ1, g_sLangID_Swing_Impedance, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labISet1, g_sLangID_Swing_SCurrent, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labFaultTime, g_sLangID_Swing_FaultTime, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labK0Mode, g_sLangID_Swing_K0CalMode, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labAmplitude, g_sLangID_Swing_Amplitude, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget(ui->m_labPhase, g_sLangID_Swing_Phase, XLang_Ctrls_QLabel);

    xlang_SetLangStrToWidget(ui->m_rbSpeedUp, g_sLangID_Swing_IncreaseSpeed, XLang_Ctrls_QRadioButton);
    xlang_SetLangStrToWidget(ui->m_rbSpeedDown, g_sLangID_Swing_Decelerate, XLang_Ctrls_QRadioButton);

    xlang_SetLangStrToWidget(ui->m_cbRefault, g_sLangID_Swing_FaultSwing, XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget(ui->m_cbReciprocating, g_sLangID_Swing_Reciprocating, XLang_Ctrls_QCheckBox);

	xlang_SetLangStrToWidget(ui->m_btnResultEval, "ResultEstimate", XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget(ui->m_btnBinary, "sOutputValue", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnTestParas, "sGeneralParameter", XLang_Ctrls_QPushButton);
}

void QSttMacroParaEditViewSwing::SetSwingFont()
{
	this->setFont(*g_pSttGlobalFont);
	ui->m_cbbFaultType->setFont(*g_pSttGlobalFont);
	ui->m_editPAngleEnd->setFont(*g_pSttGlobalFont);
	ui->m_editZ1->setFont(*g_pSttGlobalFont);
	ui->m_editISet1->setFont(*g_pSttGlobalFont);
	ui->m_editFaultTime->setFont(*g_pSttGlobalFont);
	ui->m_cbbK0Mode->setFont(*g_pSttGlobalFont);
	ui->m_editAmplitude->setFont(*g_pSttGlobalFont);
	ui->m_editPhase->setFont(*g_pSttGlobalFont);
	ui->m_editDzdt->setFont(*g_pSttGlobalFont);

	ui->m_cbDzdt->setFont(*g_pSttGlobalFont);
	ui->m_labDzdt->setFont(*g_pSttGlobalFont);
	ui->m_editDzdt->setFont(*g_pSttGlobalFont);
	ui->m_rbSpeedUp->setFont(*g_pSttGlobalFont);
	ui->m_rbSpeedDown->setFont(*g_pSttGlobalFont);
	ui->m_btnResultEval->setFont(*g_pSttGlobalFont);
	ui->m_btnBinary->setFont(*g_pSttGlobalFont);
	ui->m_btnTestParas->setFont(*g_pSttGlobalFont);
	ui->m_labPAngleStart->setFont(*g_pSttGlobalFont);
	ui->m_labPAngleEnd->setFont(*g_pSttGlobalFont);
	ui->m_labSwingCycle->setFont(*g_pSttGlobalFont);
	ui->m_labSwingCount->setFont(*g_pSttGlobalFont);
	ui->m_labTripPoint->setFont(*g_pSttGlobalFont);
	ui->m_labTripSpeedUp->setFont(*g_pSttGlobalFont);
	ui->m_labTripSpeedDown->setFont(*g_pSttGlobalFont);
	ui->m_labFaultType->setFont(*g_pSttGlobalFont);
	ui->m_labZ1->setFont(*g_pSttGlobalFont);
	ui->m_labISet1->setFont(*g_pSttGlobalFont);
	ui->m_labFaultTime->setFont(*g_pSttGlobalFont);
	ui->m_labK0Mode->setFont(*g_pSttGlobalFont);
	ui->m_labAmplitude->setFont(*g_pSttGlobalFont);
	ui->m_labPhase->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewSwing::InitUI()
{
    //this->setFont(*g_pSttGlobalFont);
	SetSwingFont();

	ui->m_tabWidget->setTabText(0, g_sLangTxt_Swing_OscParaSet);
	ui->m_tabWidget->setTabText(1, g_sLangTxt_Swing_ImpDiagram);
	ui->m_tabWidget->setTabText(2, g_sLangTxt_Swing_EquCirSystem);

    ui->m_cbbFaultType->clear();
	ui->m_cbbFaultType->addItem(g_sLangTxt_Native_GndA);
	ui->m_cbbFaultType->addItem(g_sLangTxt_Native_GndB);
	ui->m_cbbFaultType->addItem(g_sLangTxt_Native_GndC);
	ui->m_cbbFaultType->addItem(g_sLangTxt_Native_ShortAB);
	ui->m_cbbFaultType->addItem(g_sLangTxt_Native_ShortBC);
	ui->m_cbbFaultType->addItem(g_sLangTxt_Native_ShortCA);
	ui->m_cbbFaultType->addItem(g_sLangTxt_Native_ShortABC);


	m_pImpChart->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->m_cbbFaultType->setEnabled(false);
    ui->m_editPAngleEnd->setEnabled(false);
    ui->m_editZ1->setEnabled(false);
    ui->m_editISet1->setEnabled(false);
    ui->m_editFaultTime->setEnabled(false);
    ui->m_cbbK0Mode->setEnabled(false);
    ui->m_editAmplitude->setEnabled(false);
    ui->m_editPhase->setEnabled(false);
    ui->m_editDzdt->setEnabled(false);
	ui->m_tabWidget->setCurrentIndex(0);

    //20241118 wanmj 底层不支持
    ui->m_cbDzdt->setDisabled(true);
    ui->m_labDzdt->setDisabled(true);
    ui->m_editDzdt->setDisabled(true);

	UpdateGoutTab();

	return;
}


void QSttMacroParaEditViewSwing::UpdateParas()
{
    ui->m_editPAngleStart->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fPowerAngleBegin),PANGLESTART_MAX, PANGLESTART_MIN, 3));
    ui->m_editPAngleEnd->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fPowerAngleEnd),PANGLEEND_MAX, PANGLEEND_MIN, 3));
    ui->m_editSwingCycle->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fCycle),SWINGCYCLE_MAX, SWINGCYCLE_MIN, 3));
    ui->m_editSwingCount->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_nSwingCount),SWINGCOUNT_MAX, SWINGCOUNT_MIN, 3));
    ui->m_editEmEnRate->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fRate),EMENRATE_MAX, EMENRATE_MIN, 3));
    ui->m_cbbTripPoint->setCurrentIndex(m_pCurTest->m_oSwingParas.m_nTripPoint);
    ui->m_cbbTripSpeedUp->setCurrentIndex(m_pCurTest->m_oSwingParas.m_nTripSpeedUp - 2);
    ui->m_cbbTripSpeedDown->setCurrentIndex(m_pCurTest->m_oSwingParas.m_nTripSpeedDown - 3);
    ui->m_cbReciprocating->setChecked(m_pCurTest->m_oSwingParas.m_bReciprocating);
    ui->m_cbRefault->setChecked(m_pCurTest->m_oSwingParas.m_bTransFault);
    ui->m_cbDzdt->setChecked(m_pCurTest->m_oSwingParas.m_bDzdt);
    ui->m_rbSpeedUp->setChecked(m_pCurTest->m_oSwingParas.m_nAccelerate);
    ui->m_rbSpeedDown->setChecked(!m_pCurTest->m_oSwingParas.m_nAccelerate);
    ui->m_editDzdt->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fDzdt),AMPLITUDE_MAX, AMPLITUDE_MIN, 3));
    ui->m_cbbFaultType->setCurrentIndex(m_pCurTest->m_oSwingParas.m_nFaultType);
    ui->m_editZ1->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fImpedance),Z1_MAX, Z1_MIN, 3));
    ui->m_editISet1->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fSCurrent),ISET1_MAX, ISET1_MIN, 3));
    ui->m_editFaultTime->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fFaultTime),FAULTTIME_MAX, FAULTTIME_MIN, 3));
    ui->m_cbbK0Mode->setCurrentIndex(m_pCurTest->m_oSwingParas.m_nK0CalMode);
    ui->m_editAmplitude->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fK0Amp),AMPLITUDE_MAX, AMPLITUDE_MIN, 3));
    ui->m_editPhase->setText(SwingTestValueCheck(QString::number(m_pCurTest->m_oSwingParas.m_fK0Angle),PHASE_MAX, PHASE_MIN, 3));

    on_Refault_Check_StateChanged(ui->m_cbRefault->checkState());
    on_Dzdt_Check_StateChanged(ui->m_cbDzdt->checkState());
    on_Reciprocating_Check_StateChanged(ui->m_cbReciprocating->checkState());

    //20241118 wanmj 底层不支持
    ui->m_cbDzdt->setDisabled(true);
    ui->m_labDzdt->setDisabled(true);
    ui->m_editDzdt->setDisabled(true);

	return;
}

void QSttMacroParaEditViewSwing::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL && m_pCurTest != NULL)
	{
		CSttDataGroupSerializeRead oRead(pParas);
		stt_xml_serialize(&(m_pCurTest->m_oSwingParas), &oRead);
		ReadModeDataSaveMaps(&oRead);	//20240923 保存模板中定值关联关系
	}

	UpdateParas();

	m_pResultEvalDlg->SetDatas(pParas);
	m_pParasDlg->SetDatas(pParas);
    m_pBinaryDlg->SetDatas(pParas);
	m_pImpChart->SetImpDatas();
	//m_pSysDiagramWidget->SetDatas();

	GetDatas(m_pCurrDataGroup);

	g_theTestCntrFrame->InitStateMonitor();
    g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
    g_theTestCntrFrame->ClearInfoWidget();

	return;
}

void QSttMacroParaEditViewSwing::GetDatas(CDataGroup *pParas)
{
    m_pCurTest->m_oSwingParas.m_nAccelerate = ui->m_rbSpeedUp->isChecked();
    GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewSwing::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	tmt_SwingTest *pSwingTest = (tmt_SwingTest*)pParas;
	if(stt_xml_serialize_is_read(pMacroParas) || stt_xml_serialize_is_register(pMacroParas) || pParas->m_nSelected)
    {
        stt_xml_serialize(&(pSwingTest->m_oSwingParas), pMacroParas);
        ReadModeDataSaveMaps((CSttDataGroupSerializeRead*)pMacroParas);	//20240923 保存模板中定值关联关系
	}

	return;
}

void QSttMacroParaEditViewSwing::UpdateGoutTab(BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		InitGoosePubDataGroups();
		UpdateGoutTab_UI(m_listGoosePub.at(0));
	}
	else
	{
		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewSwing::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if ((m_pGooseParaWidget == NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		AddGooseParaWidget(pCfgGoutDatas);

		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
	}
	else if ((m_pGooseParaWidget != NULL)&&(!g_oSystemParas.m_nHasDigital))
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));

		RemoveGooseParaWidget();
	}
	else if ((m_pGooseParaWidget != NULL)&&(g_oSystemParas.m_nHasDigital))
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		m_pGooseParaWidget->initGoosePubTable(pCfgGoutDatas);
		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
	}
}

void QSttMacroParaEditViewSwing::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,FALSE);
	int nInsertPos = 3;

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	ui->m_tabWidget->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewSwing::RemoveGooseParaWidget()
{
	if(m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = ui->m_tabWidget->indexOf(m_pGooseParaWidget);
	ui->m_tabWidget->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QSttMacroParaEditViewSwing::UpdateTestResource(BOOL bCreateChMaps)
{
    UpdateGoutTab();
	return;
}

void QSttMacroParaEditViewSwing::UpdateSettingAttachUI()
{
    if(m_pResultEvalDlg == NULL)
        return;

    m_pResultEvalDlg->UpdateSettingText();
}

void QSttMacroParaEditViewSwing::startInit()
{
	ui->m_editPAngleStart->setDisabled(true);
    ui->m_editPAngleEnd->setDisabled(true);
    ui->m_editSwingCycle->setDisabled(true);
    ui->m_editSwingCount->setDisabled(true);
    ui->m_editEmEnRate->setDisabled(true);
    ui->m_cbbTripPoint->setDisabled(true);
    ui->m_cbbTripSpeedUp->setDisabled(true);
    ui->m_cbbTripSpeedDown->setDisabled(true);
    ui->m_cbReciprocating->setDisabled(true);
    ui->m_cbRefault->setDisabled(true);
    ui->m_cbDzdt->setDisabled(true);
    ui->m_rbSpeedUp->setDisabled(true);
    ui->m_rbSpeedDown->setDisabled(true);
    ui->m_editDzdt->setDisabled(true);
    ui->m_cbbFaultType->setDisabled(true);
    ui->m_editZ1->setDisabled(true);
    ui->m_editISet1->setDisabled(true);
    ui->m_editFaultTime->setDisabled(true);
    ui->m_cbbK0Mode->setDisabled(true);
    ui->m_editAmplitude->setDisabled(true);
    ui->m_editPhase->setDisabled(true);

	return;
}

void QSttMacroParaEditViewSwing::stopInit()
{
    ui->m_editPAngleStart->setDisabled(false);
    ui->m_editSwingCycle->setDisabled(false);
    ui->m_editSwingCount->setDisabled(false);
    ui->m_editEmEnRate->setDisabled(false);
    ui->m_cbbTripPoint->setDisabled(false);
    ui->m_cbbTripSpeedUp->setDisabled(false);
    ui->m_cbbTripSpeedDown->setDisabled(false);
    ui->m_cbReciprocating->setDisabled(false);
    ui->m_cbRefault->setDisabled(false);
    //ui->m_cbDzdt->setDisabled(false); //20241120 wanmj 设备不支持
    ui->m_rbSpeedUp->setDisabled(false);
    ui->m_rbSpeedDown->setDisabled(false);

    on_Refault_Check_StateChanged(ui->m_cbRefault->checkState());
    //on_Dzdt_Check_StateChanged(ui->m_cbDzdt->checkState());
    on_Reciprocating_Check_StateChanged(ui->m_cbReciprocating->checkState());

	return;
}

void QSttMacroParaEditViewSwing::OnViewTestStart()
{
    g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	startInit();
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();

	return;
}

void QSttMacroParaEditViewSwing::OnViewTestStop()
{
	stopInit();
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();

	return;
}

void QSttMacroParaEditViewSwing::ShowReport(CDvmValues *pValues)
{
	return;
}

void QSttMacroParaEditViewSwing::on_Refault_Check_StateChanged(int state)
{
    if(Qt::Checked == state)
    {
        ui->m_cbbFaultType->setEnabled(true);
        ui->m_editZ1->setEnabled(true);
        ui->m_editISet1->setEnabled(true);
        ui->m_editFaultTime->setEnabled(true);
        ui->m_cbbK0Mode->setEnabled(true);
        ui->m_editAmplitude->setEnabled(true);
        ui->m_editPhase->setEnabled(true);
    }
    else
    {
        ui->m_cbbFaultType->setEnabled(false);
        ui->m_editZ1->setEnabled(false);
        ui->m_editISet1->setEnabled(false);
        ui->m_editFaultTime->setEnabled(false);
        ui->m_cbbK0Mode->setEnabled(false);
        ui->m_editAmplitude->setEnabled(false);
        ui->m_editPhase->setEnabled(false);
    }
    m_pCurTest->m_oSwingParas.m_bTransFault = ui->m_cbRefault->isChecked();
}

void QSttMacroParaEditViewSwing::on_Dzdt_Check_StateChanged(int state)
{
    if(Qt::Checked == state)
    {
        ui->m_editSwingCycle->setEnabled(false);
        ui->m_editDzdt->setEnabled(true);
    }
    else
    {
        ui->m_editSwingCycle->setEnabled(true);
        ui->m_editDzdt->setEnabled(false);
    }
    m_pCurTest->m_oSwingParas.m_bDzdt = ui->m_cbDzdt->isChecked();
}

void QSttMacroParaEditViewSwing::on_Reciprocating_Check_StateChanged(int state)
{
    if(Qt::Checked == state)
    {
        ui->m_editPAngleEnd->setEnabled(true);
        ui->m_rbSpeedUp->setEnabled(false);
        ui->m_rbSpeedDown->setEnabled(false);
    }
    else
    {
        ui->m_editPAngleEnd->setEnabled(false);
        ui->m_rbSpeedUp->setEnabled(true);
        ui->m_rbSpeedDown->setEnabled(true);
    }
    m_pCurTest->m_oSwingParas.m_bReciprocating = ui->m_cbReciprocating->isChecked();
}


void QSttMacroParaEditViewSwing::on_m_btnResultEval_clicked()
{
	GetDatas(m_pCurrDataGroup);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(m_pResultEvalDlg, Keyboard::NUMBER);
	m_pResultEvalDlg->exec();
#else
	m_pResultEvalDlg->exec();
#endif
}

void QSttMacroParaEditViewSwing::on_m_btnTestParas_clicked()
{
	GetDatas(m_pCurrDataGroup);
    m_pParasDlg->UpdateParas();

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(m_pParasDlg, Keyboard::NUMBER);
	 m_pParasDlg->exec();
#else
	m_pParasDlg->exec();
#endif
   
}

//通用参数改变 阻抗图和系统图同步
void QSttMacroParaEditViewSwing::on_DataChanged()
{
	m_pImpChart->SetImpDatas();
	//m_pSysDiagramWidget->SetDatas();

	return;
}

void QSttMacroParaEditViewSwing::on_m_editPAngleStart_editingFinished()
{
    ui->m_editPAngleStart->setText(SwingTestValueCheck(ui->m_editPAngleStart->text(),PANGLESTART_MAX, PANGLESTART_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fPowerAngleBegin = ui->m_editPAngleStart->text().toFloat();
}

void QSttMacroParaEditViewSwing::on_m_editPAngleEnd_editingFinished()
{
	ui->m_editPAngleEnd->setText(SwingTestValueCheck(ui->m_editPAngleEnd->text(),PANGLEEND_MAX, PANGLEEND_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fPowerAngleEnd = ui->m_editPAngleEnd->text().toFloat();
}

void QSttMacroParaEditViewSwing::on_m_editSwingCycle_editingFinished()
{
	ui->m_editSwingCycle->setText(SwingTestValueCheck(ui->m_editSwingCycle->text(),SWINGCYCLE_MAX, SWINGCYCLE_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fCycle = ui->m_editSwingCycle->text().toFloat();
}

void QSttMacroParaEditViewSwing::on_m_editSwingCount_editingFinished()
{
	ui->m_editSwingCount->setText(SwingTestValueCheck(ui->m_editSwingCount->text(),SWINGCOUNT_MAX, SWINGCOUNT_MIN, 3));
    m_pCurTest->m_oSwingParas.m_nSwingCount = CString_To_long(ui->m_editSwingCount->text());
}

void QSttMacroParaEditViewSwing::on_m_editEmEnRate_editingFinished()
{
	ui->m_editEmEnRate->setText(SwingTestValueCheck(ui->m_editEmEnRate->text(),EMENRATE_MAX, EMENRATE_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fRate = ui->m_editEmEnRate->text().toFloat();

    GetDatas(m_pCurrDataGroup);
	SetDatas(m_pCurrDataGroup);
	m_pImpChart->SetImpDatas();
	//m_pSysDiagramWidget->SetDatas();

}

void QSttMacroParaEditViewSwing::on_m_editZ1_editingFinished()
{
	ui->m_editZ1->setText(SwingTestValueCheck(ui->m_editZ1->text(),Z1_MAX, Z1_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fImpedance = ui->m_editZ1->text().toFloat();
}

void QSttMacroParaEditViewSwing::on_m_editISet1_editingFinished()
{
	ui->m_editISet1->setText(SwingTestValueCheck(ui->m_editISet1->text(),ISET1_MAX, ISET1_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fSCurrent = ui->m_editISet1->text().toFloat();
}

void QSttMacroParaEditViewSwing::on_m_editFaultTime_editingFinished()
{
	ui->m_editFaultTime->setText(SwingTestValueCheck(ui->m_editFaultTime->text(),FAULTTIME_MAX, FAULTTIME_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fFaultTime = ui->m_editFaultTime->text().toFloat();
}

void QSttMacroParaEditViewSwing::on_m_editAmplitude_editingFinished()
{
	ui->m_editAmplitude->setText(SwingTestValueCheck(ui->m_editAmplitude->text(),AMPLITUDE_MAX, AMPLITUDE_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fK0Amp = ui->m_editAmplitude->text().toFloat();
}

void QSttMacroParaEditViewSwing::on_m_editPhase_editingFinished()
{
	ui->m_editPhase->setText(SwingTestValueCheck(ui->m_editPhase->text(),PHASE_MAX, PHASE_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fK0Angle = ui->m_editPhase->text().toFloat();
}

void QSttMacroParaEditViewSwing::on_m_editDzdt_editingFinished()
{
	ui->m_editDzdt->setText(SwingTestValueCheck(ui->m_editDzdt->text(),AMPLITUDE_MAX, AMPLITUDE_MIN, 3));
    m_pCurTest->m_oSwingParas.m_fDzdt = ui->m_editDzdt->text().toFloat();
}

void QSttMacroParaEditViewSwing::on_m_cbbK0Mode_currentIndexChanged(int index)
{
	static CString strAmplitude = ui->m_labAmplitude->text();
	static CString strPhase = ui->m_labPhase->text();

	if(index == 1)
	{

		ui->m_labAmplitude->setText("Kr: ");
		ui->m_labPhase->setText("Kx: ");
    }
    else if(index == 2)
    {

        ui->m_labAmplitude->setText("Z0: ");
        ui->m_labPhase->setText("Z1: ");
    }
	else
	{
		ui->m_labAmplitude->setText(strAmplitude);
		ui->m_labPhase->setText(strPhase);
	}

    m_pCurTest->m_oSwingParas.m_nK0CalMode = ui->m_cbbK0Mode->currentIndex();
}


void QSttMacroParaEditViewSwing::on_m_cbbFaultType_currentIndexChanged(int index)
{
    m_pCurTest->m_oSwingParas.m_nFaultType = ui->m_cbbFaultType->currentIndex();
}

void QSttMacroParaEditViewSwing::on_m_cbbTripPoint_currentIndexChanged(int index)
{
    m_pCurTest->m_oSwingParas.m_nTripPoint = ui->m_cbbTripPoint->currentIndex();
}


void QSttMacroParaEditViewSwing::on_m_btnBinary_clicked()
{
	GetDatas(m_pCurrDataGroup);
    m_pBinaryDlg->UpdateParas();
    m_pBinaryDlg->exec();
}
