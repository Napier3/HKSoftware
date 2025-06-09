#include "QSttMacroParaEditViewCBOperate.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

#include "../SttTestCntrFrameAPI.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResource_Sync.h"
#include "../../TestUI/QSttMultiMacroParaEditViewBase.h"


QSttMacroParaEditViewCBOperate::QSttMacroParaEditViewCBOperate(QWidget *parent):
 ui(new Ui::QSttMacroParaEditViewCBOperate)
{

    ui->setupUi(this);
	m_pGooseParaWidget = NULL;

	//先初始化Resource才能设置最大最小值
    m_pOriginalSttTestResource = stt_GetSttTestResource();
	stt_Frame_InitTestResource();

	m_oCBOperateParas = &m_oCBOperateTest.m_oCBOperateParas;
	
	OpenTestTestMngrFile(m_strDefaultParaFile);

	stt_Frame_UpdateToolButtons();

	InitUI();
	InitFont();
	InitConnections();
	Initdates();
	SetDatas(NULL);
	slot_ConversionFault();
}

QSttMacroParaEditViewCBOperate::~QSttMacroParaEditViewCBOperate()
{

}

void QSttMacroParaEditViewCBOperate::InitUI()
{
    ui->m_pLabFaultType->setText(/*_T("故障类型")*/g_sLangTxt_State_FaultType);
    m_ItemsList << /*"A相接地" */g_sLangTxt_Native_GndA<</* "B相接地"*/g_sLangTxt_Native_GndB << g_sLangTxt_Native_GndC/*"C相接地" */<< /*"AB短路" */g_sLangTxt_Native_ShortAB<< g_sLangTxt_Native_ShortBC/*"BC短路"*/ <</* "CA短路"*/g_sLangTxt_Native_ShortCA <</* "AB相接地短路"*/ g_sLangTxt_Native_GndShortAB
		<< /*"BC相接地短路"*/g_sLangTxt_Native_GndShortBC << /*"CA相接地短路"*/g_sLangTxt_Native_GndShortCA <</* "ABC短路"*/g_sLangTxt_Native_ShortABC << /*"单相阻抗"*/g_sLangTxt_State_SinglephaseImpedance;
    ui->m_pCmbFaultType->setMaxVisibleItems(m_ItemsList.count());
    ui->m_pCmbFaultType->addItems(m_ItemsList);
    ui->m_pLabZ->setText(g_sLangTxt_DistanceSearch_Z + ":");
    ui->m_pLabImpedanceAngle->setText(/*_T("阻抗角(°)")*/g_sLangTxt_Gradient_ImpAngle);
    ui->m_pLabCurLoad->setText(/*_T("负荷电流(A)")*/g_sLangTxt_LoadI);
    ui->m_pLabPowerAngleLoad->setText(/*_T("负荷功角(°)")*/g_sLangTxt_State_LoadAngle);
    ui->m_pLabCurShortCircuit->setText(/*_T("短路电流")*/g_sLangTxt_Impedance_ShortCurr/* + ":"*/);
    ui->m_pLabVolShortCircuit->setText(/*_T("短路电压")*/g_sLangTxt_Native_ShortCircuitVs);
    ui->m_pLabFaultDirection->setText(/*_T("故障方向")*/g_sLangTxt_Gradient_FailDirect + ":");
    ui->m_pCmbFaultDirection->addItem(/*"反向"*/g_sLangTxt_CBOperate_Reverse);
    ui->m_pCmbFaultDirection->addItem(/*"正向"*/g_sLangTxt_CBOperate_Positive);
    ui->m_pLabFaultQuality->setText(/*_T("故障性质")*/g_sLangTxt_Native_NatureMalf + ":");
    ui->m_pCmbFaultQuality->addItem(/*"瞬时"*/g_sLangTxt_CBOperate_Instan);
    ui->m_pCmbFaultQuality->addItem(/*"永久"*/g_sLangTxt_CBOperate_Perpetual);
    ui->m_pLabLarFaultTime->setText(/*_T("最大故障时间(s)")*/g_sLangTxt_CBOperate_MaxFaultTime + ":");
    ui->m_pLabFaultTrigTime->setText(/*_T("故障触发时刻")*/g_sLangTxt_CBOperate_FaultMoment + ":");
    ui->m_pLabHour->setText(/*_T("时")*/g_sLangTxt_CBOperate_Hour);
    ui->m_pLabMinute->setText(/*_T("分")*/g_sLangTxt_CBOperate_Minute);
    ui->m_pLabSecond->setText(/*_T("秒")*/g_sLangTxt_CBOperate_Second);
    ui->m_pLabRZ->setText(g_sLangTxt_DistanceSearch_Z + ":");
    ui->m_pLabImpedanceWay->setText(/*_T("阻抗表示方式：")*/g_sLangTxt_CBOperate_ImpRepre);
    ui->m_pChkAmpAngle->setText(_T("Z-Phi"));
    ui->m_pChkRX->setText(_T("R-X"));
    ui->m_pChkAmpAngle->setChecked(true);
    ui->m_pLabConversionTime->setText(/*_T("转换时间(s)")*/g_sLangTxt_CBOperate_ConversionTime+ ":");
    ui->m_pLabRFaultType->setText(/*_T("故障类型")*/g_sLangTxt_State_FaultType);
    ui->m_pCmbRFaultType->addItems(m_ItemsList);
    ui->m_pCmbRFaultType->setMaxVisibleItems(m_ItemsList.count());
    ui->m_pLabRCurShortCircuit->setText(/*_T("短路电流(A)")*/g_sLangTxt_Impedance_ShortCurr /*+ ":"*/);
    ui->m_pLabRZ->setText(g_sLangTxt_DistanceSearch_Z + ":");
    ui->m_pLabRVolShortCircuit->setText(/*_T("短路电压(V)")*/g_sLangTxt_Native_ShortCircuitVs);
    ui->m_pLabRImpedanceAngle->setText(/*_T("阻抗角(°)")*/g_sLangTxt_Gradient_ImpAngle);
    ui->m_pLabRFaultDirection->setText(/*_T("故障方向")*/g_sLangTxt_Gradient_FailDirect + ":");
    ui->m_pCmbRFaultDirection->addItem(/*"反向"*/g_sLangTxt_CBOperate_Reverse);
    ui->m_pCmbRFaultDirection->addItem(/*"正向"*/g_sLangTxt_CBOperate_Positive);
    ui->m_pBtnResultAssess->setText(/*_T("结果评估")*/g_sLangTxt_StateEstimate_ResultEstimate);
    ui->m_pBtnCommonParas->setText(/*_T("通用参数")*/g_sLangTxt_GeneralParameter);

	slot_ConversionFault();
	int nMode = m_oCBOperateParas->m_nFaultTrigMode;
	if (nMode == 3)
	{
		ui->m_pEditHour->setEnabled(true);
		ui->m_pEditMinute->setEnabled(true);
		ui->m_pEditSecond->setEnabled(true);
	}
	else
	{
    ui->m_pEditHour->setEnabled(false);
    ui->m_pEditMinute->setEnabled(false);
    ui->m_pEditSecond->setEnabled(false);
	}

	int nCalMode = m_oCBOperateParas->m_nCalMode;
	if (nCalMode == 0)
	{
    ui->m_pEditCurShortCircuit->setEnabled(true);
    ui->m_pEditVolShortCircuit->setEnabled(false);
		ui->m_pEditRCurShortCircuit->setEnabled(true);
		ui->m_pEditRVolShortCircuit->setEnabled(false);
	}
	if (nCalMode == 1)
	{
		ui->m_pEditCurShortCircuit->setEnabled(false);
		ui->m_pEditVolShortCircuit->setEnabled(true);
		ui->m_pEditRCurShortCircuit->setEnabled(false);
		ui->m_pEditRVolShortCircuit->setEnabled(true);
	}
	if (nCalMode == 2)
	{
		ui->m_pEditCurShortCircuit->setEnabled(false);
		ui->m_pEditVolShortCircuit->setEnabled(false);
    ui->m_pEditRCurShortCircuit->setEnabled(false);
    ui->m_pEditRVolShortCircuit->setEnabled(false);
	}
	if (!ui->m_pChkConversionFault->isChecked())
	{
		ui->m_pEditRCurShortCircuit->setEnabled(false);
		ui->m_pEditRVolShortCircuit->setEnabled(false);
	}
}

void QSttMacroParaEditViewCBOperate::InitFont()
{
	ui->tabWidget->setTabText(0,g_sLangTxt_Gradient_ParaSet);

	ui->m_pChkConversionFault->setText(g_sLangTxt_CBOperate_ConversionFail);
	
    ui->m_pLabFaultType->setFont(*g_pSttGlobalFont);
    ui->m_pLabCurShortCircuit->setFont(*g_pSttGlobalFont);
    ui->m_pLabZ->setFont(*g_pSttGlobalFont);
    ui->m_pLabVolShortCircuit->setFont(*g_pSttGlobalFont);
    ui->m_pLabImpedanceAngle->setFont(*g_pSttGlobalFont);
    ui->m_pLabFaultDirection->setFont(*g_pSttGlobalFont);
    ui->m_pLabCurLoad->setFont(*g_pSttGlobalFont);
    ui->m_pLabFaultQuality->setFont(*g_pSttGlobalFont);
    ui->m_pLabPowerAngleLoad->setFont(*g_pSttGlobalFont);
    ui->m_pLabLarFaultTime->setFont(*g_pSttGlobalFont);
    ui->m_pLabFaultTrigTime->setFont(*g_pSttGlobalFont);
    ui->m_pLabImpedanceWay->setFont(*g_pSttGlobalFont);
    ui->m_pLabConversionTime->setFont(*g_pSttGlobalFont);
    ui->m_pLabHour->setFont(*g_pSttGlobalFont);
    ui->m_pLabMinute->setFont(*g_pSttGlobalFont);
    ui->m_pLabSecond->setFont(*g_pSttGlobalFont);

    ui->m_pChkAmpAngle->setFont(*g_pSttGlobalFont);
    ui->m_pChkRX->setFont(*g_pSttGlobalFont);
    ui->m_pChkConversionFault->setFont(*g_pSttGlobalFont);
    ui->m_pCmbFaultType->setFont(*g_pSttGlobalFont);
    ui->m_pCmbFaultDirection->setFont(*g_pSttGlobalFont);
    ui->m_pCmbFaultQuality->setFont(*g_pSttGlobalFont);

    ui->m_pEditCurShortCircuit->setFont(*g_pSttGlobalFont);
    ui->m_pEditZ->setFont(*g_pSttGlobalFont);
    ui->m_pEditVolShortCircuit->setFont(*g_pSttGlobalFont);
    ui->m_pEditImpedanceAngle->setFont(*g_pSttGlobalFont);
    ui->m_pEditCurLoad->setFont(*g_pSttGlobalFont);
    ui->m_pEditPowerAngleLoad->setFont(*g_pSttGlobalFont);
    ui->m_pEditLarFaultTime->setFont(*g_pSttGlobalFont);
    ui->m_pEditConversionTime->setFont(*g_pSttGlobalFont);
    ui->m_pEditHour->setFont(*g_pSttGlobalFont);
    ui->m_pEditMinute->setFont(*g_pSttGlobalFont);
    ui->m_pEditSecond->setFont(*g_pSttGlobalFont);

    ui->m_pLabRFaultType->setFont(*g_pSttGlobalFont);
    ui->m_pLabRCurShortCircuit->setFont(*g_pSttGlobalFont);
    ui->m_pLabRZ->setFont(*g_pSttGlobalFont);
    ui->m_pLabRVolShortCircuit->setFont(*g_pSttGlobalFont);
    ui->m_pLabRImpedanceAngle->setFont(*g_pSttGlobalFont);
    ui->m_pLabRFaultDirection->setFont(*g_pSttGlobalFont);
    ui->m_pCmbRFaultType->setFont(*g_pSttGlobalFont);
    ui->m_pCmbRFaultDirection->setFont(*g_pSttGlobalFont);
    ui->m_pEditRCurShortCircuit->setFont(*g_pSttGlobalFont);
    ui->m_pEditRZ->setFont(*g_pSttGlobalFont);
    ui->m_pEditRVolShortCircuit->setFont(*g_pSttGlobalFont);
    ui->m_pEditRImpedanceAngle->setFont(*g_pSttGlobalFont);

    ui->m_pBtnResultAssess->setFont(*g_pSttGlobalFont);
    ui->m_pBtnCommonParas->setFont(*g_pSttGlobalFont);
}

void QSttMacroParaEditViewCBOperate::InitConnections()
{
    connect(ui->m_pBtnResultAssess, SIGNAL(clicked()), this, SLOT(slot_ResultAssess()));
    connect(ui->m_pBtnCommonParas, SIGNAL(clicked()), this, SLOT(slot_CommonParas()));
    connect(ui->m_pChkConversionFault, SIGNAL(clicked()), this, SLOT(slot_ConversionFault()));
    connect(ui->m_pChkAmpAngle,SIGNAL(toggled(bool)),this,SLOT(slot_ImpedanceChanged(bool)));


    connect(ui->m_pCmbFaultType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbFaultType(int)));
    connect(ui->m_pEditZ, SIGNAL(editingFinished()), this, SLOT(slot_EditZ()));
    connect(ui->m_pEditImpedanceAngle, SIGNAL(editingFinished()), this, SLOT(slot_EditImpedanceAngle()));
    connect(ui->m_pEditCurLoad, SIGNAL(editingFinished()), this, SLOT(slot_EditCurLoad()));
    connect(ui->m_pEditPowerAngleLoad, SIGNAL(editingFinished()), this, SLOT(slot_EditPowerAngleLoad()));
    connect(ui->m_pEditCurShortCircuit, SIGNAL(editingFinished()), this, SLOT(slot_EditCurShortCircuit()));
    connect(ui->m_pEditVolShortCircuit, SIGNAL(editingFinished()), this, SLOT(slot_EditVolShortCircuit()));
    connect(ui->m_pCmbFaultDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbFaultDirection(int)));
    connect(ui->m_pCmbFaultQuality, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbFaultQuality(int)));
    connect(ui->m_pEditLarFaultTime, SIGNAL(editingFinished()), this, SLOT(slot_EditLarFaultTime()));
    connect(ui->m_pEditHour, SIGNAL(editingFinished()), this, SLOT(slot_EditHour()));
    connect(ui->m_pEditMinute, SIGNAL(editingFinished()), this, SLOT(slot_EditMinute()));
    connect(ui->m_pEditSecond, SIGNAL(editingFinished()), this, SLOT(slot_EditSecond()));
    //connect(ui->m_pChkConversionFault, SIGNAL(clicked()), this, SLOT(slot_ChkConversionFault()));
    connect(ui->m_pCmbRFaultType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbRFaultType(int)));
    connect(ui->m_pEditConversionTime, SIGNAL(editingFinished()), this, SLOT(slot_EditConversionTime()));
    connect(ui->m_pEditRZ, SIGNAL(editingFinished()), this, SLOT(slot_EditRZ()));
    connect(ui->m_pEditRImpedanceAngle, SIGNAL(editingFinished()), this, SLOT(slot_EditRImpedanceAngle()));
    connect(ui->m_pEditRCurShortCircuit, SIGNAL(editingFinished()), this, SLOT(slot_EditRCurShortCircuit()));
    connect(ui->m_pEditRVolShortCircuit, SIGNAL(editingFinished()), this, SLOT(slot_EditRVolShortCircuit()));
    connect(ui->m_pCmbRFaultDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbRFaultDirection(int)));
}

void QSttMacroParaEditViewCBOperate::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
														   long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	tmt_CBOperateTest *pTmtCBOperateTest = (tmt_CBOperateTest *)pParas;

	stt_xml_serialize(&pTmtCBOperateTest->m_oCBOperateParas,pMacroParas);

}


void QSttMacroParaEditViewCBOperate::UpdateTestResource(BOOL bCreateChMaps)
{
	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewCBOperate::UpdateGoutTab(BOOL bUpdateList /*= FALSE*/)
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

void QSttMacroParaEditViewCBOperate::slot_ResultAssess()
{
	CBOperateResultAssessGrid dlg(m_oCBOperateParas,this);
	dlg.setWindowTitle(/*"结果评估"*/g_sLangTxt_StateEstimate_ResultEstimate);
	dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();

#else
	dlg.exec();
#endif

}

void QSttMacroParaEditViewCBOperate::slot_CommonParas()
{
	CBOperateCommonParasDlg dlg(m_oCBOperateParas,this);
	dlg.setWindowTitle(/*"通用参数"*/g_sLangTxt_Gradient_CommonParas);
	dlg.setWindowModality(Qt::WindowModal);

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif

    int nMode = dlg.m_pCmbFaultTrigMode->currentIndex();
    if (nMode == 3)
    {
        ui->m_pEditHour->setEnabled(true);
        ui->m_pEditMinute->setEnabled(true);
        ui->m_pEditSecond->setEnabled(true);
    }
    else
    {
        ui->m_pEditHour->setEnabled(false);
        ui->m_pEditMinute->setEnabled(false);
        ui->m_pEditSecond->setEnabled(false);
    }

    int nCalMode = dlg.m_pCmbCalMode->currentIndex();
    if (nCalMode == 0)
    {
        ui->m_pEditCurShortCircuit->setEnabled(true);
        ui->m_pEditVolShortCircuit->setEnabled(false);
        ui->m_pEditRCurShortCircuit->setEnabled(true);
        ui->m_pEditRVolShortCircuit->setEnabled(false);
    }
    if (nCalMode == 1)
    {
        ui->m_pEditCurShortCircuit->setEnabled(false);
        ui->m_pEditVolShortCircuit->setEnabled(true);
        ui->m_pEditRCurShortCircuit->setEnabled(false);
        ui->m_pEditRVolShortCircuit->setEnabled(true);
    }
    if (nCalMode == 2)
    {
        ui->m_pEditCurShortCircuit->setEnabled(false);
        ui->m_pEditVolShortCircuit->setEnabled(false);
        ui->m_pEditRCurShortCircuit->setEnabled(false);
        ui->m_pEditRVolShortCircuit->setEnabled(false);
    }
    if(!ui->m_pChkConversionFault->isChecked())
    {
        ui->m_pEditRCurShortCircuit->setEnabled(false);
        ui->m_pEditRVolShortCircuit->setEnabled(false);
    }
}

void QSttMacroParaEditViewCBOperate::slot_ConversionFault()
{
    bool isChecked = ui->m_pChkConversionFault->isChecked();

	m_oCBOperateParas->m_bTransFault = isChecked;

    ui->m_pCmbRFaultType->setEnabled(isChecked);
    ui->m_pCmbRFaultDirection->setEnabled(isChecked);
    ui->m_pEditRCurShortCircuit->setEnabled(isChecked);
    ui->m_pEditRZ->setEnabled(isChecked);
    ui->m_pEditRVolShortCircuit->setEnabled(isChecked);
    ui->m_pEditRImpedanceAngle->setEnabled(isChecked);
    ui->m_pEditConversionTime->setEnabled(isChecked);

	if (isChecked)
	{
        if (m_oCBOperateParas->m_nCalMode == 0)
		{
            ui->m_pEditCurShortCircuit->setEnabled(true);
            ui->m_pEditVolShortCircuit->setEnabled(false);
            ui->m_pEditRCurShortCircuit->setEnabled(true);
            ui->m_pEditRVolShortCircuit->setEnabled(false);
		}
        if (m_oCBOperateParas->m_nCalMode == 1)
		{
            ui->m_pEditCurShortCircuit->setEnabled(false);
            ui->m_pEditVolShortCircuit->setEnabled(true);
            ui->m_pEditRCurShortCircuit->setEnabled(false);
            ui->m_pEditRVolShortCircuit->setEnabled(true);
		}
        if (m_oCBOperateParas->m_nCalMode == 2)
		{
            ui->m_pEditCurShortCircuit->setEnabled(false);
            ui->m_pEditVolShortCircuit->setEnabled(false);
            ui->m_pEditRCurShortCircuit->setEnabled(false);
            ui->m_pEditRVolShortCircuit->setEnabled(false);
		}
	}
}

void QSttMacroParaEditViewCBOperate::Initdates()
{
	ui->m_pEditImpedanceAngle->UpdateStructText(CVariantDataAddress(&m_oCBOperateParas->m_fImpAngle[0]), 3);
	ui->m_pEditZ->UpdateStructText(CVariantDataAddress(&m_oCBOperateParas->m_fImpedance[0]), 3);
	//ui->m_pEditImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
    //ui->m_pEditZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
    ui->m_pEditCurShortCircuit->setText(QString::number(m_oCBOperateParas->m_fSCCurrent[0], 'f', 3));
    ui->m_pEditVolShortCircuit->setText(QString::number(m_oCBOperateParas->m_fSCVoltage[0], 'f', 3));
    ui->m_pCmbFaultDirection->setCurrentIndex(m_oCBOperateParas->m_nFaultDir[0]);
    ui->m_pCmbFaultQuality->setCurrentIndex(m_oCBOperateParas->m_nFaultProperty);
	//ui->m_pEditLarFaultTime->setText(QString::number(m_oCBOperateParas->m_fMaxFaultTime, 'f', 3));
	ui->m_pEditLarFaultTime->UpdateStructText(CVariantDataAddress(&m_oCBOperateParas->m_fMaxFaultTime), 3);
    ui->m_pEditCurLoad->setText(QString::number(m_oCBOperateParas->m_fIfh, 'f', 3));
    ui->m_pEditPowerAngleLoad->setText(QString::number(m_oCBOperateParas->m_fPowerAngle, 'f', 3));

    ui->m_pChkConversionFault->setChecked(m_oCBOperateParas->m_bTransFault);
    ui->m_pCmbFaultType->setCurrentIndex(m_oCBOperateParas->m_nFaultType[0]);//2024-7-10 wuxinyi 补充故障类型更新参数
    ui->m_pCmbRFaultType->setCurrentIndex(m_oCBOperateParas->m_nFaultType[1]);
    ui->m_pEditConversionTime->setText(QString::number(m_oCBOperateParas->m_fTransTime, 'f', 3));
	ui->m_pEditRImpedanceAngle->UpdateStructText(CVariantDataAddress(&m_oCBOperateParas->m_fImpAngle[1]), 3);
	ui->m_pEditRZ->UpdateStructText(CVariantDataAddress(&m_oCBOperateParas->m_fImpedance[1]), 3);
    //ui->m_pEditRZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
    //ui->m_pEditRImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
    ui->m_pEditRCurShortCircuit->setText(QString::number(m_oCBOperateParas->m_fSCCurrent[1], 'f', 3));
    ui->m_pEditRVolShortCircuit->setText(QString::number(m_oCBOperateParas->m_fSCVoltage[0], 'f', 3));
    ui->m_pCmbRFaultDirection->setCurrentIndex(m_oCBOperateParas->m_nFaultDir[1]);
	ui->m_pEditHour->setText(QString::number(m_oCBOperateParas->m_tGps.nHour));
	ui->m_pEditMinute->setText(QString::number(m_oCBOperateParas->m_tGps.nMinutes));
	ui->m_pEditSecond->setText(QString::number(m_oCBOperateParas->m_tGps.nSeconds));
}

void QSttMacroParaEditViewCBOperate::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewCBOperate::SetDatas(CDataGroup *pDataset)
{
	if (pDataset != NULL)
	{
		CSttDataGroupSerializeRead oRead(pDataset);
		stt_xml_serialize(m_oCBOperateParas, &oRead);
		ReadModeDataSaveMaps(&oRead);	//20240913 huangliang 保存模板中定值关联关系
	}
    stt_Frame_InitVectorWidget(NULL,NULL);
    stt_Frame_InitPowerWidget(NULL,NULL);
    stt_Frame_InitStateMonitor();
    stt_Frame_ClearInfoWidget();

	//2024-7-10 wuxinyi 整组试验参数改变不更新
	Initdates();

	UpdateBinBoutExTab();
	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewCBOperate::slot_CmbFaultType(int nIndex)
{
	m_oCBOperateParas->m_nFaultType[0] = nIndex;

}

void QSttMacroParaEditViewCBOperate::slot_EditZ()
{
    if (ui->m_pEditZ->inherits(STT_SETTING_LINEEDIT_ClassID/*QSettingEdit*/))
    {
        if(((QSettingLineEdit*)ui->m_pEditZ)->IsSetting())
        {
            return ;
        }
    }

    float fv = ui->m_pEditZ->text().toFloat();
    fv = setLimit(0,999.999,fv);
    ui->m_pEditZ->setText(QString::number(fv, 'f', 3));
    m_oCBOperateParas->m_fImpedance[0] = fv;
    return;
}

void QSttMacroParaEditViewCBOperate::slot_EditImpedanceAngle()
{
    if (ui->m_pEditImpedanceAngle->inherits(STT_SETTING_LINEEDIT_ClassID/*QSettingEdit*/))
    {
        if(((QSettingLineEdit*)ui->m_pEditImpedanceAngle)->IsSetting())
        {
            return ;
        }
    }

    float fv = ui->m_pEditImpedanceAngle->text().toFloat();
	fv = setLimit(-360.000,360.000,fv);
    ui->m_pEditImpedanceAngle->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fImpAngle[0] = fv;
    return;
}

void QSttMacroParaEditViewCBOperate::slot_EditCurLoad()
{
    if (ui->m_pEditCurLoad->inherits(STT_SETTING_LINEEDIT_ClassID/*QSettingEdit*/))
    {
        if(((QSettingLineEdit*)ui->m_pEditCurLoad)->IsSetting())
        {
            return ;
        }
    }

    float fv = ui->m_pEditCurLoad->text().toFloat();
	fv = setLimit(0,20.000,fv);
    ui->m_pEditCurLoad->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fIfh = fv;
    return;
}

void QSttMacroParaEditViewCBOperate::slot_EditPowerAngleLoad()
{
    if (ui->m_pEditPowerAngleLoad->inherits(STT_SETTING_LINEEDIT_ClassID/*QSettingEdit*/))
    {
        if(((QSettingLineEdit*)ui->m_pEditPowerAngleLoad)->IsSetting())
        {
            return ;
        }
    }

    float fv = ui->m_pEditPowerAngleLoad->text().toFloat();
	fv = setLimit(-360.0,360.0,fv);
    ui->m_pEditPowerAngleLoad->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fPowerAngle = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditCurShortCircuit()
{
    float fv =ui-> m_pEditCurShortCircuit->text().toFloat();
	fv = setLimit(0,20.0,fv);
    ui->m_pEditCurShortCircuit->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fSCCurrent[0] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditVolShortCircuit()
{
    float fv = ui->m_pEditVolShortCircuit->text().toFloat();
	fv = setLimit(0,130.000,fv);
    ui->m_pEditVolShortCircuit->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fSCVoltage[0] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_CmbFaultDirection(int nIndex)
{
	m_oCBOperateParas->m_nFaultDir[0] = nIndex;
}

void QSttMacroParaEditViewCBOperate::slot_CmbFaultQuality(int nIndex)
{
	m_oCBOperateParas->m_nFaultProperty = nIndex;
}

void QSttMacroParaEditViewCBOperate::slot_EditLarFaultTime()
{
    float fv = ui->m_pEditLarFaultTime->text().toFloat();
	fv = setLimit(0,999.999,fv);
    ui->m_pEditLarFaultTime->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fMaxFaultTime = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditHour()
{
    int fv = ui->m_pEditHour->text().toInt();
	fv = setLimit(0,999,fv);
    ui->m_pEditHour->setText(QString::number(fv));
	m_oCBOperateParas->m_tGps.nHour = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditMinute()
{
    int fv = ui->m_pEditMinute->text().toInt();
	fv = setLimit(0,999,fv);
    ui->m_pEditMinute->setText(QString::number(fv));
	m_oCBOperateParas->m_tGps.nMinutes = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditSecond()
{
    int fv = ui->m_pEditSecond->text().toInt();
	fv = setLimit(0,999,fv);
    ui->m_pEditSecond->setText(QString::number(fv));
	m_oCBOperateParas->m_tGps.nSeconds = fv;
}

//void QSttMacroParaEditViewCBOperate::slot_ChkConversionFault()
//{
//    m_oCBOperateParas->m_bTransFault = ui->m_pChkConversionFault->isChecked();
//}

void QSttMacroParaEditViewCBOperate::slot_CmbRFaultType(int nIndex)
{
	m_oCBOperateParas->m_nFaultType[1] = nIndex;
}

void QSttMacroParaEditViewCBOperate::slot_EditConversionTime()
{
    float fv = ui->m_pEditConversionTime->text().toFloat();
	fv = setLimit(0,1000.000,fv);
    ui->m_pEditConversionTime->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fTransTime = fv;
}

void QSttMacroParaEditViewCBOperate::slot_EditRZ()
{
    if (ui->m_pEditRZ->inherits(STT_SETTING_LINEEDIT_ClassID/*QSettingEdit*/))
    {
        if(((QSettingLineEdit*)ui->m_pEditRZ)->IsSetting())
        {
            return ;
        }
    }

    float fv = ui->m_pEditRZ->text().toFloat();
	fv = setLimit(0,999.999,fv);
    ui->m_pEditRZ->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fImpedance[1] = fv;
    return ;
}

void QSttMacroParaEditViewCBOperate::slot_EditRImpedanceAngle()
{
    if (ui->m_pEditRImpedanceAngle->inherits(STT_SETTING_LINEEDIT_ClassID/*QSettingEdit*/))
    {
        if(((QSettingLineEdit*)ui->m_pEditRImpedanceAngle)->IsSetting())
        {
            return ;
        }
    }

    float fv = ui->m_pEditRImpedanceAngle->text().toFloat();
	fv = setLimit(-360.000,360.000,fv);
    ui->m_pEditRImpedanceAngle->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fImpAngle[1] = fv;
    return ;
}

void QSttMacroParaEditViewCBOperate::slot_EditRCurShortCircuit()
{
    if (ui->m_pEditRCurShortCircuit->inherits(STT_SETTING_LINEEDIT_ClassID/*QSettingEdit*/))
    {
        if(((QSettingLineEdit*)ui->m_pEditRCurShortCircuit)->IsSetting())
        {
            return ;
        }
    }

    float fv = ui->m_pEditRCurShortCircuit->text().toFloat();
	fv = setLimit(0,20.000,fv);
    ui->m_pEditRCurShortCircuit->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fSCCurrent[1] = fv;
    return ;
}

void QSttMacroParaEditViewCBOperate::slot_EditRVolShortCircuit()
{
    float fv = ui->m_pEditRVolShortCircuit->text().toFloat();
	fv = setLimit(0,130.000,fv);
    ui->m_pEditRVolShortCircuit->setText(QString::number(fv, 'f', 3)); // 显示三位小数
	m_oCBOperateParas->m_fSCVoltage[1] = fv;
}

void QSttMacroParaEditViewCBOperate::slot_CmbRFaultDirection(int nIndex)
{
	m_oCBOperateParas->m_nFaultDir[1] = nIndex;
}


void QSttMacroParaEditViewCBOperate::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if ((m_pGooseParaWidget == NULL) && (g_oSystemParas.m_nHasDigital) && (g_oSttTestResourceMngr.m_nTotalFiberNum_LC > 0))//更新前无GOOSE界面,更新后需要GOOSE界面
	{
		AddGooseParaWidget(pCfgGoutDatas);

		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()), Qt::DirectConnection);
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
	}
	else if ((m_pGooseParaWidget != NULL) && (!g_oSystemParas.m_nHasDigital))//更新前有GOOSE界面,更新后不需要
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		RemoveGooseParaWidget();
	}
	else if ((m_pGooseParaWidget != NULL) && (g_oSystemParas.m_nHasDigital))
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
		m_pGooseParaWidget->initGoosePubTable(pCfgGoutDatas);
		connect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()), Qt::DirectConnection);
		connect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		connect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));
	}
	else if ((m_pGooseParaWidget != NULL) && (g_oSttTestResourceMngr.m_nTotalFiberNum_LC == 0))//更新前有GOOSE界面,更新后LC口为0不需要
	{
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
		disconnect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		RemoveGooseParaWidget();
	}

}

void QSttMacroParaEditViewCBOperate::RemoveGooseParaWidget()
{
	if (m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = ui->tabWidget->indexOf(m_pGooseParaWidget);
	ui->tabWidget->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QSttMacroParaEditViewCBOperate::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas, TRUE);

	CString strTitle;
	xlang_GetLangStrByFile(strTitle, "Native_GooseDataSet");
	ui->tabWidget->addTab(m_pGooseParaWidget, strTitle);
}

void QSttMacroParaEditViewCBOperate::OnViewTestStart()
{
	startInit();
	stt_Frame_ClearInfoWidget();
	stt_Frame_StartPowerWidget();
	stt_Frame_StartVectorWidget();
    stt_Frame_StartStateMonitor();

	if (m_oCBOperateParas->m_nFaultTrigMode == 1)
	{
		stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger, true, true);
	}
	else
	{
		stt_Frame_Ats_UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger, false, true);
	}
}

void QSttMacroParaEditViewCBOperate::OnViewTestStop()
{
	stopInit();
	stt_Frame_StopPowerWidget();
	stt_Frame_StopVectorWidget();
    stt_Frame_StopStateMonitor();

}

void QSttMacroParaEditViewCBOperate::startInit()
{
    ui->m_pCmbFaultType->setEnabled(false);
    ui->m_pEditZ->setEnabled(false);
    ui->m_pEditImpedanceAngle->setEnabled(false);
    ui->m_pEditCurLoad->setEnabled(false);
    ui->m_pEditPowerAngleLoad->setEnabled(false);
    ui->m_pEditCurShortCircuit->setEnabled(false);
    ui->m_pEditVolShortCircuit->setEnabled(false);
    ui->m_pCmbFaultDirection->setEnabled(false);
    ui->m_pCmbFaultQuality->setEnabled(false);
    ui->m_pEditLarFaultTime->setEnabled(false);
    ui->m_pEditConversionTime->setEnabled(false);
    ui->m_pEditHour->setEnabled(false);
    ui->m_pEditMinute->setEnabled(false);
    ui->m_pEditSecond->setEnabled(false);
    ui->m_pBtnResultAssess->setEnabled(false);
    ui->m_pBtnCommonParas->setEnabled(false);
    ui->m_pCmbRFaultType->setEnabled(false);
    ui->m_pCmbRFaultDirection->setEnabled(false);
    ui->m_pEditRCurShortCircuit->setEnabled(false);
    ui->m_pEditRZ->setEnabled(false);
    ui->m_pEditRVolShortCircuit->setEnabled(false);
    ui->m_pEditRImpedanceAngle->setEnabled(false);
    ui->m_pChkConversionFault->setEnabled(false);
    ui->m_pChkRX->setEnabled(false);
    ui->m_pChkAmpAngle->setEnabled(false);
}

void QSttMacroParaEditViewCBOperate::stopInit()
{

    ui->m_pCmbFaultType->setEnabled(true);
    ui->m_pEditZ->setEnabled(true);
    ui->m_pEditImpedanceAngle->setEnabled(true);
    ui->m_pEditCurLoad->setEnabled(true);
    ui->m_pEditPowerAngleLoad->setEnabled(true);
    //ui->m_pEditCurShortCircuit->setEnabled(true);
    //ui->m_pEditVolShortCircuit->setEnabled(false);
    ui->m_pCmbFaultDirection->setEnabled(true);
    ui->m_pCmbFaultQuality->setEnabled(true);
    ui->m_pEditLarFaultTime->setEnabled(true);
    //ui->m_pEditHour->setEnabled(false);
    //ui->m_pEditMinute->setEnabled(false);
    //ui->m_pEditSecond->setEnabled(false);
    ui->m_pBtnResultAssess->setEnabled(true);
    ui->m_pBtnCommonParas->setEnabled(true);
    ui->m_pChkConversionFault->setEnabled(true);
    ui->m_pChkRX->setEnabled(true);
    ui->m_pChkAmpAngle->setEnabled(true);

	slot_ConversionFault();
	int nMode = m_oCBOperateParas->m_nFaultTrigMode;
	if (nMode == 3)
	{
		ui->m_pEditHour->setEnabled(true);
		ui->m_pEditMinute->setEnabled(true);
		ui->m_pEditSecond->setEnabled(true);
	}
	else
	{
		ui->m_pEditHour->setEnabled(false);
		ui->m_pEditMinute->setEnabled(false);
		ui->m_pEditSecond->setEnabled(false);
	}

	int nCalMode = m_oCBOperateParas->m_nCalMode;
	if (nCalMode == 0)
	{
		ui->m_pEditCurShortCircuit->setEnabled(true);
		ui->m_pEditVolShortCircuit->setEnabled(false);
		ui->m_pEditRCurShortCircuit->setEnabled(true);
		ui->m_pEditRVolShortCircuit->setEnabled(false);
	}
	if (nCalMode == 1)
	{
		ui->m_pEditCurShortCircuit->setEnabled(false);
		ui->m_pEditVolShortCircuit->setEnabled(true);
		ui->m_pEditRCurShortCircuit->setEnabled(false);
		ui->m_pEditRVolShortCircuit->setEnabled(true);
	}
	if (nCalMode == 2)
	{
		ui->m_pEditCurShortCircuit->setEnabled(false);
		ui->m_pEditVolShortCircuit->setEnabled(false);
		ui->m_pEditRCurShortCircuit->setEnabled(false);
		ui->m_pEditRVolShortCircuit->setEnabled(false);
	}
	if (!ui->m_pChkConversionFault->isChecked())
	{
		ui->m_pEditRCurShortCircuit->setEnabled(false);
    ui->m_pEditRVolShortCircuit->setEnabled(false);
	}
}

void QSttMacroParaEditViewCBOperate::slot_ImpedanceChanged( bool bIsrBtnAmpAngleChecked)
{
    QString strEdit1;
    QString strEdit2;

	if (bIsrBtnAmpAngleChecked)
	{

		ui->m_pLabZ->setText(QString::fromLocal8Bit("|Z|(Ω):"));
		ui->m_pLabImpedanceAngle->setText(/*"阻抗角(°)"*/g_sLangTxt_Gradient_ImpAngle);
		ui->m_pLabRZ->setText(QString::fromLocal8Bit("|Z|(Ω):"));
		ui->m_pLabRImpedanceAngle->setText(/*"阻抗角(°)"*/g_sLangTxt_Gradient_ImpAngle);
		//ui->m_pEditZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
		//ui->m_pEditImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
		//ui->m_pEditRZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
		//ui->m_pEditRImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));

        strEdit1 = GetImpedanceByXY("Amp",ui->m_pEditZ->text(),ui->m_pEditImpedanceAngle->text());
        strEdit2 = GetImpedanceByXY("Angle",ui->m_pEditZ->text(),ui->m_pEditImpedanceAngle->text());
        ui->m_pEditZ->setText(strEdit1);
        ui->m_pEditImpedanceAngle->setText(strEdit2);

        strEdit1 = GetImpedanceByXY("Amp",ui->m_pEditRZ->text(),ui->m_pEditRImpedanceAngle->text());
        strEdit2 = GetImpedanceByXY("Angle",ui->m_pEditRZ->text(),ui->m_pEditRImpedanceAngle->text());
        ui->m_pEditRZ->setText(strEdit1);
        ui->m_pEditRImpedanceAngle->setText(strEdit2);
	}	
	else
	{
        strEdit1 = GetXYByImpedance("X",ui->m_pEditZ->text(),ui->m_pEditImpedanceAngle->text());
        strEdit2 = GetXYByImpedance("Y",ui->m_pEditZ->text(),ui->m_pEditImpedanceAngle->text());
        ui->m_pEditZ->setText(strEdit1);
        ui->m_pEditImpedanceAngle->setText(strEdit2);

        strEdit1 = GetXYByImpedance("X",ui->m_pEditRZ->text(),ui->m_pEditRImpedanceAngle->text());
        strEdit2 = GetXYByImpedance("Y",ui->m_pEditRZ->text(),ui->m_pEditRImpedanceAngle->text());
        ui->m_pEditRZ->setText(strEdit1);
        ui->m_pEditRImpedanceAngle->setText(strEdit2);

        ui->m_pLabZ->setText(QString::fromLocal8Bit("R(Ω):"));
        ui->m_pLabImpedanceAngle->setText(QString::fromLocal8Bit("X(Ω):"));
        ui->m_pLabRZ->setText(QString::fromLocal8Bit("R(Ω):"));
        ui->m_pLabRImpedanceAngle->setText(QString::fromLocal8Bit("X(Ω):"));
        //ui->m_pEditZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
        //ui->m_pEditImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));
        //ui->m_pEditRZ->setText(QString::number(m_oCBOperateParas->m_fImpedance[0], 'f', 3));
        //ui->m_pEditRImpedanceAngle->setText(QString::number(m_oCBOperateParas->m_fImpAngle[0], 'f', 3));

	}
}

CString QSttMacroParaEditViewCBOperate::GetXYByImpedance(QString strXY,QString strAmp,QString strAngle)
{
	double  dCoordsValue ;

	if(strXY.compare("X") == 0)
	{
		dCoordsValue = strAmp.toDouble() * cos(strAngle.toDouble() * _PI / 180);
	}
	else
	{
		dCoordsValue = strAmp.toDouble() * sin(strAngle.toDouble() * _PI / 180);
	}
	return QString::number(dCoordsValue, 'f', 3);
}

CString QSttMacroParaEditViewCBOperate::GetImpedanceByXY(QString strAmpAngle,CString strAmp,CString strAngle)
{
	double  dImpedanceValue ;

	if(strAmpAngle.compare("Amp") == 0)
	{
		dImpedanceValue = sqrt(strAmp.toDouble() * strAmp.toDouble()+strAngle.toDouble() * strAngle.toDouble());
		return QString::number(dImpedanceValue, 'f', 3);
	}
	else
	{
		dImpedanceValue = atan2(strAngle.toDouble(),strAmp.toDouble()) * 180 / _PI;
		return QString::number(dImpedanceValue, 'f', 3);
	}
}
