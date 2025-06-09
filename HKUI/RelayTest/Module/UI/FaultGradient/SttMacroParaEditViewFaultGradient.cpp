#include "SttMacroParaEditViewFaultGradient.h"
#include "CFaultGradientSetting.h"
#include "FaultGradientEstimateDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include"../../Module/XLangResource_Native.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include "../SttTestCntrFrameAPI.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewFaultGradient::QSttMacroParaEditViewFaultGradient(QWidget *parent)
	:/* QWidget(parent)*/ui(new Ui::QSttMacroParaEditViewFaultGradient)
	
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	m_nOutNormalError = (ui->btnGrpOutNormalError->buttons().count())/2;	
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;
	m_strUnit = "";
	m_nChannel = if_type;
	m_nType = amplitude_type;
	InitLanuage();
	//初始化创建测试项
	SetData(CreateTestParas(GetMacroID())); 
	InitUI();
	m_pOriginalSttTestResource = stt_GetSttTestResource();//创建软件资源类对象
	stt_Frame_InitTestResource();//软件资源初始化

	if (g_oSystemParas.m_nHasDigital)
	{
		InitFT3PubDataGroups();
		InitGoosePubDataGroups();
	}
	OpenTestTestMngrFile(m_strDefaultParaFile);
	SetDatas(0);
	
	InitConnections();
}

QSttMacroParaEditViewFaultGradient::~QSttMacroParaEditViewFaultGradient()
{

}

void QSttMacroParaEditViewFaultGradient::InitLanuage()
{
	xlang_SetLangStrToWidget(ui->m_labInit, "Gradient_Init", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_labFinish, "Gradient_Finish", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_labStep, "Gradient_Step", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_labTime, "Gradient_Time", XLang_Ctrls_QLabel);
	if (!ui->m_labTime->text().contains("(s):"))
	{
		ui->m_labTime->setText(ui->m_labTime->text() + "(s):");
	}//wangtao 20240726 
	xlang_SetLangStrToWidget(ui->m_labType, "Native_Type", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_labVar, "Gradient_FailModes", XLang_Ctrls_QLabel);
	if (!ui->m_labVar->text().contains(":"))
	{
		ui->m_labVar->setText(ui->m_labVar->text() + ":");
	}
	xlang_SetLangStrToWidget(ui->m_labVar_2, "Gradient_Change", XLang_Ctrls_QLabel);
	if (!ui->m_labVar_2->text().contains(":"))
	{
		ui->m_labVar_2->setText(ui->m_labVar_2->text() + ":");
	}
	xlang_SetLangStrToWidget(ui->m_labShortVm, "Native_ShortCircuitVs", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_labDirection, "Impedance_ShortCurr", XLang_Ctrls_QLabel);
	if (!ui->m_labDirection->text().contains(":"))
	{
		ui->m_labDirection->setText(ui->m_labDirection->text() + ":");
	}
	xlang_SetLangStrToWidget(ui->m_labDirection_2, "Gradient_ImpAngle", XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget(ui->m_labTimeBeforeChange, "Gradient_ChangeTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_labTimeBeforeFail, "Native_PreFaultTime", XLang_Ctrls_QLabel);
	if (!ui->m_labTimeBeforeFail->text().contains(":"))
	{
		ui->m_labTimeBeforeFail->setText(ui->m_labTimeBeforeFail->text() + ":");
	}
	xlang_SetLangStrToWidget(ui->m_labTimeBeforeChange_2, "Gradient_FailVol", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_labTimeBeforeFail_2, "Gradient_FailCur", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_labTimeBeforeFail_3, "Gradient_FailAngle", XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget(ui->m_gpChangeSet, "Gradient_RampParas", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(ui->m_gpVarSet, "Gradient_VarSet", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(ui->m_gpMannual, "Gradient_CommonParas", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(ui->m_gpBin, "Gradient_BinBout", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(ui->m_gpBoutNormal, "Gradient_BoutNormal", XLang_Ctrls_QGroupBox);
	xlang_SetLangStrToWidget(ui->m_gpBoutError, "Gradient_BoutFaultState", XLang_Ctrls_QGroupBox);

	xlang_SetLangStrToWidget(ui->m_btnEstimate, "State_Estimate", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnMoreOut, "Gradient_BoutSets", XLang_Ctrls_QPushButton);

	xlang_SetLangStrToWidget(ui->m_rbOr, "Native_LogicOr", XLang_Ctrls_QRadioButton);
	xlang_SetLangStrToWidget(ui->m_rbAnd, "Native_LogicAnd", XLang_Ctrls_QRadioButton);
}

void QSttMacroParaEditViewFaultGradient::SetUIFont(QWidget* pWidget)
{

#ifdef _PSX_QT_LINUX_//mod wangtao 20240827 只在Linux下调用，解决Windows下字体不一致问题
	g_pSttGlobalFont->resolve(QFont::AllPropertiesResolved);
#endif
	setFont(*g_pSttGlobalFont);

	if(pWidget == NULL) return;
	pWidget->setFont(*g_pSttGlobalFont);

	QWidget *pChildWig = NULL;
	foreach(QObject* pObj,pWidget->children())
	{
		if(pObj == NULL) continue;
		
		QLabel* pLab = NULL;
		QSttLineEdit* pEdit = NULL;
		QScrollComboBox* pCombox = NULL;
		QAbstractButton* pBt = NULL;

		pLab = dynamic_cast<QLabel*>(pObj);
		pEdit = dynamic_cast<QSttLineEdit*>(pObj);
		pCombox = dynamic_cast<QScrollComboBox*>(pObj);
		pBt = dynamic_cast<QAbstractButton*>(pObj);

		if(pLab)
		{
			pLab->setFont(*g_pSttGlobalFont);
		}
		else if(pEdit)
		{
			pEdit->setFont(*g_pSttGlobalFont);
			initMaxPositiveEdit(pEdit);
		}
		else if(pCombox)
		{
			pCombox->setFont(*g_pSttGlobalFont);
		}
		else if(pBt)
		{
			pBt->setFont(*g_pSttGlobalFont);
		}
		else
		{
			pChildWig = dynamic_cast<QWidget*>(pObj);
			if(pChildWig)
			{
				SetUIFont(pChildWig);
			}
		}
	}
}

void QSttMacroParaEditViewFaultGradient::SetStyleStateValue(QGroupBox* pGroup,int nState,int nVFlag)
{
	if(pGroup == NULL) return;
	foreach(QObject* pObj,pGroup->children())
	{
		if(pObj == NULL) continue;
		QSttCheckBox* pCheck = NULL;
		QWidget* pWdg = NULL;
		if(nState < 0 && nVFlag < 0)
		{
			pCheck = dynamic_cast<QSttCheckBox*>(pObj);
			if(pCheck)
			{
				pCheck->InitStyleSheet();
			}
		}
		else if(nState >= 0 && nVFlag < 0)
		{
			pWdg = dynamic_cast<QWidget*>(pObj);
			if(pWdg)
			{
				pWdg->setEnabled(nState);
			}
		}
		else if(nState < 0 && nVFlag >= 0)
		{
			pCheck = dynamic_cast<QSttCheckBox*>(pObj);
			if(pCheck)
			{
				QString strBtn = pCheck->objectName();
				int nIndex = strBtn.right(1).toInt();
				int nPos = 0;
				if(nVFlag == 0)
				{
					GlobalSetQcheckState_BinaryIn(pCheck,m_pCurFGTest->m_oFaultGradientParas.m_binIn,nIndex);
				}
				else if(nVFlag == 1)
				{
					if(nIndex >= m_nOutNormalError)
					{
						nPos = 1;
						nIndex -= m_nOutNormalError;
					}
					GlobalSetQcheckState_BinaryOut(pCheck,m_pCurFGTest->m_oFaultGradientParas.m_binOut[nPos],nIndex);
				}
			}
		}
	}
}

void QSttMacroParaEditViewFaultGradient::InitComboBox()
{
	ui->m_cbbType->clear();
	ui->m_cbbFaultMode->clear();
	ui->m_cbbChangeVaule->clear();
	ui->m_cbbShortVm->clear();

	m_lstGradientType << /*_T("动作值")*/g_sLangTxt_State_ActionValue << /*_T("返回系数")*/g_sLangTxt_Native_ReturnCoeff /*<< g_sLangTxt_Gradient_MaxAngle/*_T("最大灵敏角")*/ ;
	ui->m_cbbType->addItems(m_lstGradientType);

	m_lstFaultMode << /*_T("A相短路")*/g_sLangTxt_Native_PhaseAshort << /*_T("B相短路")*/g_sLangTxt_Native_PhaseBshort << /*_T("C相短路")*/g_sLangTxt_Native_PhaseCshort << /*_T("ABC相短路")*/g_sLangTxt_Native_PhaseABCshort
		<< /*_T("AB相短路")*/g_sLangTxt_Native_PhaseABshort << /*_T("BC相短路")*/g_sLangTxt_Native_PhaseBCshort << /*_T("CA相短路")*/g_sLangTxt_Native_PhaseCAshort << /*_T("AB相短路，C相电流")*/g_sLangTxt_Native_PhaseABshortCcur << /*_T("BC相短路，A相电流")*/g_sLangTxt_Native_PhaseBCshortAcur << /*_T("CA相短路，B相电流")*/g_sLangTxt_Native_PhaseCAshortBcur << /*_T("AB相短路，B相电流")*/g_sLangTxt_Native_PhaseABshortBcur 
		<< /*_T("BC相短路，C相电流")*/g_sLangTxt_Native_PhaseBCshortCcur << /*_T("CA相短路，A相电流")*/g_sLangTxt_Native_PhaseCAshortAcur /*<< _T("CA相短路，A相电流")*/ << _T("U/f") << _T("I2/I1");
	ui->m_cbbFaultMode->addItems(m_lstFaultMode);

	QStringList lstChangeValue;
	lstChangeValue << /*_T("短路电压")*/g_sLangTxt_Native_ShortCircuitV << /*_T("短路电流")*/g_sLangTxt_Native_ShortCircuit << /*_T("阻抗角")*/g_sLangTxt_Native_ImpedanceAngles << /*_T("短路阻抗")*/g_sLangTxt_Native_ShortZImp << /*_T("频率")*/g_sLangTxt_Native_Freq 
					 << /*_T("正序电压")*/g_sLangTxt_Native_PosVol << /*_T("负序电压")*/g_sLangTxt_Native_NegVol << /*_T("零序电压（3U0）")*/g_sLangTxt_Native_ZeroVol3U0;

	m_mapChangValue[FG_FaultMode_Null] = lstChangeValue;
	QStringList lstChangeValue_UF;
	lstChangeValue_UF << /*_T("电压")*/g_sLangTxt_Native_Voltage << /*_T("频率")*/g_sLangTxt_Native_Freq;
	m_mapChangValue[FG_FaultMode_UF] = lstChangeValue_UF;
	QStringList lstChangeValue_I2;
	lstChangeValue_I2 << _T("I2");
	m_mapChangValue[FG_FaultMode_I2I1] = lstChangeValue_I2;

	QStringList lstChangeValue_AB_C;
	lstChangeValue_AB_C << _T("Uab") << _T("Ic") << QString::fromLocal8Bit("Φ(Uab-Ic)");
	m_mapChangValue[FG_FaultMode_AB_C] = lstChangeValue_AB_C;

	QStringList lstChangeValue_BC_A;
	lstChangeValue_BC_A << _T("Ubc") << _T("Ia") << QString::fromLocal8Bit("Φ(Ubc-Ia)");
	m_mapChangValue[FG_FaultMode_BC_A] = lstChangeValue_BC_A;

	QStringList lstChangeValue_CA_B;
	lstChangeValue_CA_B << _T("Uca") << _T("Ib") << QString::fromLocal8Bit("Φ(Uca-Ib)");
	m_mapChangValue[FG_FaultMode_CA_B] = lstChangeValue_CA_B;

	QStringList lstChangeValue_AB_B;
	lstChangeValue_AB_B << _T("Uab") << _T("Ib") << QString::fromLocal8Bit("Φ(Uab-Ib)");
	m_mapChangValue[FG_FaultMode_AB_B] = lstChangeValue_AB_B;

	QStringList lstChangeValue_BC_C;
	lstChangeValue_BC_C << _T("Ubc") << _T("Ic") << QString::fromLocal8Bit("Φ(Ubc-Ic)");
	m_mapChangValue[FG_FaultMode_BC_C] = lstChangeValue_BC_C;

	QStringList lstChangeValue_CA_A;
	lstChangeValue_CA_A << _T("Uca") << _T("Ia") << QString::fromLocal8Bit("Φ(Uca-Ia)");
	m_mapChangValue[FG_FaultMode_CA_A] = lstChangeValue_CA_A;

	ui->m_cbbChangeVaule->addItems(lstChangeValue);

	m_lstShortVm <</* _T("正序(U1)")*/ g_sLangTxt_Native_PosVolU1<<g_sLangTxt_Native_NegVolU2/* _T("负序(U2)")*/ << /*_T("零序(3U0)")*/g_sLangTxt_Native_Zero3U0;
	ui->m_cbbShortVm->addItems(m_lstShortVm);

	ui->m_cbbShortVm->setMaximumHeight(ui->m_editInit->height());
	ui->m_cbbShortVm->setMinimumHeight(ui->m_editInit->height());
	ui->m_editShortVm->setMaximumHeight(ui->m_editInit->height());
	ui->m_editShortVm->setMinimumHeight(ui->m_editInit->height());

}

void QSttMacroParaEditViewFaultGradient::InitUI()
{

	//初始化界面属性 和设置
	SetUIFont(ui->m_tabWidget);
	InitComboBox();

	ui->m_tabWidget->setTabText(0, g_sLangTxt_Gradient_ParaSet);
	ui->m_tabWidget->setTabText(1, g_sLangTxt_Native_Bout);

	SetStyleStateValue(ui->m_gpBin);
	SetStyleStateValue(ui->m_gpBoutNormal);
	SetStyleStateValue(ui->m_gpBoutError);
	((QSttTabWidget*)ui->m_tabWidget)->InitStyleSheet();
}

void QSttMacroParaEditViewFaultGradient::SetParas()
{
	//20240808 gongyiping 添加定值关联
	//ui->m_editInit->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fStart, 'f', 3));
	((QSettingLineEdit*)ui->m_editInit)->UpdateStructText(CVariantDataAddress(&m_pCurFGTest->m_oFaultGradientParas.m_fStart), 3);
	//ui->m_editFinish->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fStop, 'f', 3));
	((QSettingLineEdit*)ui->m_editFinish)->UpdateStructText(CVariantDataAddress(&m_pCurFGTest->m_oFaultGradientParas.m_fStop), 3);
	//ui->m_editStep->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fStep, 'f', 3));
	((QSettingLineEdit*)ui->m_editStep)->UpdateStructText(CVariantDataAddress(&m_pCurFGTest->m_oFaultGradientParas.m_fStep), 3);
	//ui->m_editFaultTime->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fFaultTime, 'f', 3));
	((QSettingLineEdit*)ui->m_editFaultTime)->UpdateStructText(CVariantDataAddress(&m_pCurFGTest->m_oFaultGradientParas.m_fFaultTime), 3);
	ui->m_cbbType->setCurrentIndex(m_pCurFGTest->m_oFaultGradientParas.m_nTestMode);

	ui->m_cbbFaultMode->setCurrentIndex(m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode);

	ui->m_cbbShortVm->setCurrentIndex(m_pCurFGTest->m_oFaultGradientParas.m_nShortVmType);
	ui->m_editShortVm->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fShortVm, 'f', 3));
	ui->m_editShortVa->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fShortVa, 'f', 3));
	ui->m_editAngle->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fAngle, 'f', 3));

	ui->m_editTimeBeforeChange->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fPrepareTime, 'f', 3));
	if(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime < 0.0001)
	{
		m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime = 0;
		ui->m_editTimeBeforeFail->setText("0.000");
	}
	else
	{
		ui->m_editTimeBeforeFail->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime,'f',3));
	}

	ui->m_editFaultBeforeVm->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDU, 'f', 3));
	ui->m_editFaultBeforeVa->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDI, 'f', 3));
	ui->m_editFaultBeforeAngle->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fEDUaIaAngle, 'f', 3));

	if (m_pCurFGTest->m_oFaultGradientParas.m_nBinLogic == 1)
	{
		ui->m_rbAnd->setChecked(TRUE);
	}
	else
	{
		ui->m_rbOr->setChecked(TRUE);
	}

	SetStyleStateValue(ui->m_gpBin,-1,0);
	SetStyleStateValue(ui->m_gpBoutNormal,-1,1);
	SetStyleStateValue(ui->m_gpBoutError,-1,1);

	on_FaultMode_currentIndexChanged(m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode);
	ui->m_cbbChangeVaule->setCurrentIndex(m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue);
	SetLableTextUnit(m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode, m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue);
}

void QSttMacroParaEditViewFaultGradient::InitConnections()
{
	//commbox 连接
	connect(ui->m_cbbType,SIGNAL(currentIndexChanged(int)),this,SLOT(on_ReturnType_currentIndexChanged(int)));
	connect(ui->m_cbbFaultMode,SIGNAL(currentIndexChanged(int)),this,SLOT(on_FaultMode_currentIndexChanged(int)));
	connect(ui->m_cbbChangeVaule,SIGNAL(currentIndexChanged(int)),this,SLOT(on_ChangeValue_currentIndexChanged(int)));
	connect(ui->m_cbbShortVm,SIGNAL(currentIndexChanged(int)),this,SLOT(on_VMType_currentIndexChanged(int)));
	//开入 开出 
	connect(ui->m_rbAnd, SIGNAL(toggled(bool )), this, SLOT(on_AndStateChanged(bool)));
	connect(ui->btnGrpBin,SIGNAL(buttonClicked(QAbstractButton *)),this,SLOT(on_GrpBin_ButtonClick(QAbstractButton*)));
	connect(ui->btnGrpOutNormalError,SIGNAL(buttonClicked(QAbstractButton *)),this,SLOT(on_GrpOutNormalError_ButtonClick(QAbstractButton*)));
	connect(ui->m_btnEstimate,SIGNAL(clicked()),this,SLOT(on_Estimate_ButtonClick()));
	connect(ui->m_btnMoreOut,SIGNAL(clicked()),this,SLOT(on_MoreOut_ButtonClick()));
	//eidt 变量
	connect(ui->m_editInit,SIGNAL(editingFinished()),this,SLOT(on_EditInit_Finish()));
	connect(ui->m_editFinish,SIGNAL(editingFinished()),this,SLOT(on_EditFinish_Finish()));
	connect(ui->m_editStep,SIGNAL(editingFinished()),this,SLOT(on_EditStep_Finish()));
	connect(ui->m_editFaultTime,SIGNAL(editingFinished()),this,SLOT(on_EditFaultTime_Finish()));
	connect(ui->m_editShortVm,SIGNAL(editingFinished()),this,SLOT(on_EditShortVm_Finish()));
	connect(ui->m_editShortVa,SIGNAL(editingFinished()),this,SLOT(on_EditShortVa_Finish())); 
	connect(ui->m_editAngle,SIGNAL(editingFinished()),this,SLOT(on_EditAngle_Finish()));
	connect(ui->m_editTimeBeforeChange,SIGNAL(editingFinished()),this,SLOT(on_EditTimeBeforeChange_Finish()));
	connect(ui->m_editTimeBeforeFail,SIGNAL(editingFinished()),this,SLOT(on_EditTimeBeforeFail_Finish()));
	connect(ui->m_editFaultBeforeVm,SIGNAL(editingFinished()),this,SLOT(on_EditFaultBeforeVm_Finish()));
	connect(ui->m_editFaultBeforeVa,SIGNAL(editingFinished()),this,SLOT(on_EditFaultBeforeVa_Finish()));
	connect(ui->m_editFaultBeforeAngle,SIGNAL(editingFinished()),this,SLOT(on_EditFaultBeforeAngle_Finish()));
}

void QSttMacroParaEditViewFaultGradient::SetData(PTMT_PARAS_HEAD pCurr)
{
	ASSERT(m_pCur != NULL);
	m_pCurFGTest = (tmt_fault_gradient_test*)pCurr;
}

void QSttMacroParaEditViewFaultGradient::SetLableTextUnit(int nFaultIndex,int nChangIndex)
{
	if(nFaultIndex >= FG_FaultMode_AB_C && nFaultIndex <= FG_FaultMode_CA_A)
	{
		if(nChangIndex == 0) 
		{
			SetUnit(nFaultIndex,nChangIndex,"V");
			m_nEditControlType = 3;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 0;
		}
		else if(nChangIndex == 1)
		{
			SetUnit(nFaultIndex,nChangIndex,"A");
			m_nEditControlType = 2;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 1;
		}
		else if(nChangIndex == 2)
		{
			SetUnit(nFaultIndex, nChangIndex, QString::fromLocal8Bit("°"));
			m_nEditControlType = 4;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 2;
		}
	}
	else if(nFaultIndex == FG_FaultMode_UF)
	{
		if(nChangIndex == FG_FM_Vaule_VM) 
		{
			SetUnit(nFaultIndex,nChangIndex,"V");
			m_nEditControlType = 3;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 0;
		}
		else if(nChangIndex == FG_FM_Vaule_HZ) 
		{
			SetUnit(nFaultIndex,nChangIndex,"Hz");
			m_nEditControlType = 5;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 4;
		}
	}
	else if(nFaultIndex == FG_FaultMode_I2I1)
	{
		SetUnit(nFaultIndex,nChangIndex,"A");
		m_nEditControlType = 2;
		m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 1;
	}
	else
	{
		if(nChangIndex == FG_FM_Vaule_ShortVM || nChangIndex == FG_FM_Vaule_PlusVM 
			|| nChangIndex == FG_FM_Vaule_MinusVM ||nChangIndex == FG_FM_Vaule_ZeroVM) 
		{
			SetUnit(nFaultIndex,nChangIndex,"V");
			m_nEditControlType = 3;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 0;
		}
		if(nChangIndex == FG_FM_Vaule_ShortVA )
		{
			SetUnit(nFaultIndex,nChangIndex,"A");
			m_nEditControlType = 2;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 1;
		}
		if (nChangIndex == FG_FM_Vaule_ShortImpede)
		{
			SetUnit(nFaultIndex, nChangIndex, QString::fromLocal8Bit("Ω"));
			m_nEditControlType = 1;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 3;
		}
		if(nChangIndex == FG_FM_Vaule_ImpedeAngle) 
		{
			SetUnit(nFaultIndex,nChangIndex,QString::fromLocal8Bit("°"));
			m_nEditControlType = 4;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 2;
		}
		if(nChangIndex == FG_FM_Vaule_Frequency) 
		{
			SetUnit(nFaultIndex,nChangIndex,"Hz");
			m_nEditControlType = 5;
			m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 4;
		}
	}
	//add wangtao 20240818 更新右侧状态图的显示文本
	CString strTemp1 = ui->m_labInit->text();
	QRegExp re("\\(([^)]+)\\)");
	if (re.indexIn(strTemp1) != -1)
	{
		m_strUnit = re.cap(1);
	}
	SetStateMonitorYRange();

	SetAllEditValueControl();
}

void QSttMacroParaEditViewFaultGradient::GetStateMonitorYRange(float ftime, float fv, float fstart, float fend, float &up)
{
	float fNew = fv;
	if (ftime < EPSINON)
	{
		fNew = 0;
	}

    float fUnit;
	if (m_strUnit == "V")
	{
        fUnit = 57.735;
        fNew =max(fUnit, fNew);
	}
	else if (m_strUnit == "Hz")
	{
        fUnit = 50;
        fNew = max(fUnit, fNew);
	}
	up = getMaxFormThreeValue(fNew, fstart, fend);
	
}
void QSttMacroParaEditViewFaultGradient::SetStateMonitorYRange()
{
	float fup = 0;
	if (m_strUnit == "A")
	{
		GetStateMonitorYRange(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime, m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDI, ui->m_editInit->text().toFloat(), ui->m_editFinish->text().toFloat(), fup);
		emit sig_YRangeChanged(amplitude_type, ui->m_cbbChangeVaule->currentText() + "(" + m_strUnit + ")", fup, 0);
	}
	else if (m_strUnit == "V")
	{
		GetStateMonitorYRange(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime, m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDU, ui->m_editInit->text().toFloat(), ui->m_editFinish->text().toFloat(), fup);
		emit sig_YRangeChanged(amplitude_type, ui->m_cbbChangeVaule->currentText() + "(" + m_strUnit + ")", fup, 0);
	}
	else if (m_strUnit == CString("°"))
	{
		GetStateMonitorYRange(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime, 0, ui->m_editInit->text().toFloat(), ui->m_editFinish->text().toFloat(), fup);
		emit sig_YRangeChanged(phasor_type, ui->m_cbbChangeVaule->currentText() + "(" + m_strUnit + ")", fup, 0);
	}
	else
	{
		GetStateMonitorYRange(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime, 0, ui->m_editInit->text().toFloat(), ui->m_editFinish->text().toFloat(), fup);
		emit sig_YRangeChanged(amplitude_type, ui->m_cbbChangeVaule->currentText() + "(" + m_strUnit + ")", fup, 0);
	}
}
void QSttMacroParaEditViewFaultGradient::SetUnit(int nFaultMode,int nValueType,QString strUnit)
{
	QString strTemp1 = ui->m_labInit->text();
	int nPos1 = strTemp1.indexOf("(");

	QString strTemp2 = ui->m_labFinish->text();
	int nPos2 = strTemp2.indexOf("(");

	QString strTemp3 = ui->m_labStep->text();
	int nPos3 = strTemp3.indexOf("(");

	QString strLabInit = strTemp1.left(nPos1) + "(" + strUnit + "):";
	QString strLabFinish = /*((QString)ui->m_labFinish->text())*/strTemp2.left(nPos2) + "(" + strUnit + "):";
	QString strLabStep = /*((QString)ui->m_labStep->text())*/strTemp3.left(nPos3) + "(" + strUnit + "):";
	ui->m_labInit->setText(strLabInit);
	ui->m_labFinish->setText(strLabFinish);
	ui->m_labStep->setText(strLabStep);
}

void QSttMacroParaEditViewFaultGradient::GetEditFloatValue(QSttLineEdit* pLine,float& fValue)
{
	QString str2 = pLine->text();
	if (str2.right(1).contains("."))
	{
		str2.append("000");
	}
	fValue = str2.toFloat();
}

void QSttMacroParaEditViewFaultGradient::SetShortVaVmAngle(int nFaultIndex,int nChangIndex)
{
	if(nFaultIndex >=	FG_FaultMode_A && nFaultIndex <= FG_FaultMode_CA)
	{
		if(nChangIndex == FG_FM_Vaule_ShortVM || nChangIndex == FG_FM_Vaule_ShortImpede || 
			nChangIndex == FG_FM_Vaule_PlusVM || nChangIndex == FG_FM_Vaule_MinusVM || nChangIndex == FG_FM_Vaule_ZeroVM)
		{
			SetShortVaVmAngleEnable(0,0,1,1);
		}
		else if(nChangIndex == FG_FM_Vaule_ShortVA)  SetShortVaVmAngleEnable(1,1,0,1);
		else if(nChangIndex == FG_FM_Vaule_ImpedeAngle) SetShortVaVmAngleEnable(1,1,1,0);
		else if(nChangIndex == FG_FM_Vaule_Frequency) SetShortVaVmAngleEnable(1,1,1,1);

	}
	else if(nFaultIndex >= FG_FaultMode_AB_C && nFaultIndex <= FG_FaultMode_CA_A)
	{
		if(nChangIndex == 0) SetShortVaVmAngleEnable(0,0,1,1);
		if(nChangIndex == 1) SetShortVaVmAngleEnable(1,0,0,1);
		if(nChangIndex == 2) SetShortVaVmAngleEnable(1,0,1,0);
	}
	else if(nFaultIndex == FG_FaultMode_UF)
	{
		if(nChangIndex == FG_FM_Vaule_VM) SetShortVaVmAngleEnable(0,0,1,1);
		if(nChangIndex == FG_FM_Vaule_HZ) SetShortVaVmAngleEnable(1,0,1,1);
	}
	else if(nFaultIndex == FG_FaultMode_I2I1)
	{
		if(nChangIndex == FG_FM_Vaule_I2) SetShortVaVmAngleEnable(1,0,1,1);
	}
}

void QSttMacroParaEditViewFaultGradient::SetShortVaVmAngleEnable(int nShortVmFlag,int nShortVmTypeFlag,int nShortVaFlag,int nAngleFlag)
{
	ui->m_editShortVm->setEnabled(nShortVmFlag);
	ui->m_cbbShortVm->setEnabled(nShortVmTypeFlag);
	ui->m_editShortVa->setEnabled(nShortVaFlag);
	ui->m_editAngle->setEnabled(nAngleFlag);
}

//设置edit 值限制 1 电阻  2 电流  3 电压  4 角度 5 HZ
float QSttMacroParaEditViewFaultGradient::SetEditValueControl(float fValue,int nFlag,QSttLineEdit* pLine)
{
	//20240808 gongyiping 
	if (pLine->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)pLine)->IsSetting())
		{
			return fValue;
		}
	}

	float fMaxValue = 0.000,fMinValue = 0.000;
	switch(nFlag)
	{
	case 1:
		fMaxValue = 999.999;
		fMinValue = EPSINON;
		break;
	case 2:
		fMaxValue = g_oLocalSysPara.m_fAC_CurMax;
		fMinValue = 0.000;
		break;
	case 3:
		fMaxValue = g_oLocalSysPara.m_fAC_VolMax;
		fMinValue = 0.000;
		break;
	case 4:
		fMaxValue = 9999.000;
		fMinValue = 0.000;
		break;
	case 5:
		fMaxValue = 1500;
		fMinValue = 0.000;
	}

	if (fabs(fValue) > fMaxValue) 
	{
		fValue = fMaxValue;
	}
	else if (fabs(fValue) < fMinValue) 
	{
		fValue = fMinValue;
	}

	if(nFlag == 1)
	{
		if (fabs(fValue) > fMinValue && fabs(fValue) < 0.02)
		{
			fValue = 0.02;
		}
	}
	
	if(nFlag == 4)
	{
		float f1 = fValue - (int)fValue;
		int f2 = ((int)fValue)%360;
		fValue = f1+f2;
	}
	pLine->setText(QString::number(fValue,'f',3));
	return fValue;
}

void QSttMacroParaEditViewFaultGradient::SetAllEditValueControl()
{
	on_EditInit_Finish();
	on_EditFinish_Finish();
	on_EditStep_Finish();
	on_EditFaultTime_Finish();
	on_EditShortVm_Finish();
	on_EditShortVa_Finish();
	on_EditAngle_Finish();
	on_EditTimeBeforeChange_Finish();
	on_EditTimeBeforeFail_Finish();
	on_EditFaultBeforeVm_Finish();
	on_EditFaultBeforeVa_Finish();
	on_EditFaultBeforeAngle_Finish();
}

//////////////////
void QSttMacroParaEditViewFaultGradient::on_ReturnType_currentIndexChanged(int nIndex)
{
	if(ui->m_cbbType->IsScrolling())
	{
		return;
	}
	//if(m_nEditControlType == 4)//wangtao 20240902 需确认阻抗角是否需要选择动作值和返回系数
	//{
	//	if(nIndex == FG_TestMode_ActValue || nIndex == FG_TestMode_ReturnCoef)
	//	{
	//		ui->m_cbbType->setCurrentIndex(FG_TestMode_MaxAngle);
	//		return;
	//	}
	//}
	if (m_pCurFGTest->m_oFaultGradientParas.m_nTestMode != nIndex)
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nTestMode = nIndex;
		//ToDo W
		m_bTmtParaChanged = TRUE;
	}
	if (m_pCurFGTest->m_oFaultGradientParas.m_nTestMode == FG_TestMode_ReturnCoef)//返回系数
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 5;
	}
	else if (m_pCurFGTest->m_oFaultGradientParas.m_nTestMode == FG_TestMode_MaxAngle)//最大灵敏角
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nVarIndexType = 6;
	}
}

void QSttMacroParaEditViewFaultGradient::on_FaultMode_currentIndexChanged(int nIndex)
{
		m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode = nIndex;
	
	disconnect(ui->m_cbbChangeVaule, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ChangeValue_currentIndexChanged(int)));
	ui->m_cbbChangeVaule->clear();
	if(nIndex > FG_FaultMode_CA)
	{
		ui->m_cbbChangeVaule->addItems(m_mapChangValue[nIndex]);
	}
	else
	{
		ui->m_cbbChangeVaule->addItems(m_mapChangValue[FG_FaultMode_Null]);
	}
	connect(ui->m_cbbChangeVaule, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ChangeValue_currentIndexChanged(int)));

	//add wangtao 20240818 故障模式修改后，尽量保留当前变化量
	if (ui->m_cbbChangeVaule->count() > m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue)
	{
		ui->m_cbbChangeVaule->setCurrentIndex(m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue);
	}
	else
	{
		on_ChangeValue_currentIndexChanged(0);
	}
}

void QSttMacroParaEditViewFaultGradient::on_ChangeValue_currentIndexChanged(int nIndex)
{
	if(ui->m_cbbChangeVaule->IsScrolling()) return;

		m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue = nIndex;
		
		//设置单位  控件使用
		int nValIndex = ui->m_cbbFaultMode->currentIndex();
		SetLableTextUnit(nValIndex,nIndex);
		SetShortVaVmAngle(nValIndex,nIndex);

	m_bTmtParaChanged = TRUE;
	if (nIndex == FG_FM_Vaule_ImpedeAngle)
	{
		m_lstGradientType.clear();
		ui->m_cbbType->clear();
		m_lstGradientType << /*_T("动作值")*/g_sLangTxt_State_ActionValue << /*_T("返回系数")*/g_sLangTxt_Native_ReturnCoeff << g_sLangTxt_Gradient_MaxAngle/*_T("最大灵敏角")*/;
		ui->m_cbbType->addItems(m_lstGradientType);
	}
	else 
	{
		m_lstGradientType.clear();
		ui->m_cbbType->clear();
		m_lstGradientType << /*_T("动作值")*/g_sLangTxt_State_ActionValue << /*_T("返回系数")*/g_sLangTxt_Native_ReturnCoeff;
		ui->m_cbbType->addItems(m_lstGradientType);
	}

}

void QSttMacroParaEditViewFaultGradient::on_VMType_currentIndexChanged(int nIndex)
{
	if(ui->m_cbbChangeVaule->IsScrolling()) return;
	
	if (m_pCurFGTest->m_oFaultGradientParas.m_nShortVmType != nIndex)
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nShortVmType = nIndex;
	}
	//ToDo
}

void QSttMacroParaEditViewFaultGradient::on_GrpBin_ButtonClick(QAbstractButton * pCurrBtn)
{
	QString strBtn = pCurrBtn->objectName();
	int nIndex = strBtn.right(1).toInt();
	if (pCurrBtn->isChecked())
	{
		m_pCurFGTest->m_oFaultGradientParas.m_binIn[nIndex].nSelect = 1;
	}
	else
	{
		m_pCurFGTest->m_oFaultGradientParas.m_binIn[nIndex].nSelect = 0;
	}
}

void QSttMacroParaEditViewFaultGradient::on_GrpOutNormalError_ButtonClick(QAbstractButton * pCurrBtn)
{
	QString strBtn = pCurrBtn->objectName();
	int nIndex = strBtn.right(1).toInt();
	int nPos = 0;
	if(nIndex >= m_nOutNormalError)
	{
		nPos = 1;
		nIndex -= m_nOutNormalError;
	}
	if (pCurrBtn->isChecked())
	{
		m_pCurFGTest->m_oFaultGradientParas.m_binOut[nPos][nIndex].nState = 1;
	}
	else
	{
		m_pCurFGTest->m_oFaultGradientParas.m_binOut[nPos][nIndex].nState = 0;
	}
}

void QSttMacroParaEditViewFaultGradient::on_AndStateChanged(bool)
{
	if (ui->m_rbAnd->isChecked())
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nBinLogic = 1;
	}
	else
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nBinLogic = 0;
	}
}

void QSttMacroParaEditViewFaultGradient::on_MoreOut_ButtonClick()
{
	CFaultGradientSetting dlg(m_pCurFGTest,this);
	dlg.setWindowModality(Qt::WindowModal);
	dlg.setWindowTitle(g_sLangTxt_Gradient_BoutSet);
	int nRet = -1;
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	nRet = dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	nRet = dlg.exec();
#endif

	if(nRet == QDialog::Accepted)
	{
		for(int j = 0; j < 2;j++)
		{
			for(int i = 0;i < MAX_BINARYOUT_COUNT;i++)
			{
				m_pCurFGTest->m_oFaultGradientParas.m_binOut[j][i] = dlg.m_binOutTemp[j][i];
			}
		}
		SetStyleStateValue(ui->m_gpBoutNormal,-1,1);
		SetStyleStateValue(ui->m_gpBoutError,-1,1);
	}
}

void QSttMacroParaEditViewFaultGradient::on_Estimate_ButtonClick()
{
	CFaultGradientEstimateDlg dlg(m_pCurFGTest,this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
 #endif
}

//变化始值
void QSttMacroParaEditViewFaultGradient::on_EditInit_Finish()
{
	
	if (ui->m_editInit->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_editInit)->IsSetting())
		{
			return;
		}
	}

	float fv = 0.000;
	GetEditFloatValue(ui->m_editInit,fv);
	float fNewValue = SetEditValueControl(fv,m_nEditControlType,ui->m_editInit);
	// 业务处理  暂无  直接赋值
	m_pCurFGTest->m_oFaultGradientParas.m_fStart = fNewValue;

	//更新实时图Y坐标轴范围
	SetStateMonitorYRange();
}
//变化终值
void QSttMacroParaEditViewFaultGradient::on_EditFinish_Finish()
{
	
	if (ui->m_editFinish->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_editFinish)->IsSetting())
		{
			return;
		}
	}

	float fv = 0.000;
	GetEditFloatValue(ui->m_editFinish,fv);
	float fNewValue = SetEditValueControl(fv,m_nEditControlType,ui->m_editFinish);
	m_pCurFGTest->m_oFaultGradientParas.m_fStop = fNewValue;
	//更新实时图Y坐标轴范围
	SetStateMonitorYRange();
}
//变化步长
void QSttMacroParaEditViewFaultGradient::on_EditStep_Finish()
{
	
	if (ui->m_editStep->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_editStep)->IsSetting())
		{
			return;
		}
	}

	float fv = 0.000;
	GetEditFloatValue(ui->m_editStep,fv);
	float fNewValue = SetEditValueControl(fv,m_nEditControlType,ui->m_editStep);
	m_pCurFGTest->m_oFaultGradientParas.m_fStep = fNewValue;
}
//故障时间
void QSttMacroParaEditViewFaultGradient::on_EditFaultTime_Finish()
{
	
	if (ui->m_editFaultTime->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if (((QSettingLineEdit*)ui->m_editFaultTime)->IsSetting())
		{
			return;
		}
	}

	float fv = 0.000;
	GetEditFloatValue(ui->m_editFaultTime,fv);
	float fNewValue = SetEditValueControl(fv,1,ui->m_editFaultTime);
	m_pCurFGTest->m_oFaultGradientParas.m_fFaultTime = fNewValue;
}
//短路电压
void QSttMacroParaEditViewFaultGradient::on_EditShortVm_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editShortVm,fv);
	float fNewValue = SetEditValueControl(fv,3,ui->m_editShortVm);
	m_pCurFGTest->m_oFaultGradientParas.m_fShortVm = fNewValue;
}
//短路电流
void QSttMacroParaEditViewFaultGradient::on_EditShortVa_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editShortVa,fv);
	float fNewValue = SetEditValueControl(fv,2,ui->m_editShortVa);
	m_pCurFGTest->m_oFaultGradientParas.m_fShortVa = fNewValue;
}
//阻抗角
void QSttMacroParaEditViewFaultGradient::on_EditAngle_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editAngle,fv);
	float fNewValue = SetEditValueControl(fv,4,ui->m_editAngle);
	m_pCurFGTest->m_oFaultGradientParas.m_fAngle = fNewValue;
}
//变化前时间
void QSttMacroParaEditViewFaultGradient::on_EditTimeBeforeChange_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editTimeBeforeChange,fv);
	float fNewValue = SetEditValueControl(fv,1,ui->m_editTimeBeforeChange);
	m_pCurFGTest->m_oFaultGradientParas.m_fPrepareTime = fNewValue;
}
//故障前时间
void QSttMacroParaEditViewFaultGradient::on_EditTimeBeforeFail_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editTimeBeforeFail,fv);
	float fNewValue = SetEditValueControl(fv,1,ui->m_editTimeBeforeFail);
	m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime = fNewValue;
	//更新实时图Y坐标轴范围
	SetStateMonitorYRange();
}
//故障前电压
void QSttMacroParaEditViewFaultGradient::on_EditFaultBeforeVm_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editFaultBeforeVm,fv);
	float fNewValue = SetEditValueControl(fv,3,ui->m_editFaultBeforeVm);
	m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDU = fNewValue;
	//更新实时图Y坐标轴范围
	SetStateMonitorYRange();
}
//故障前电流
void QSttMacroParaEditViewFaultGradient::on_EditFaultBeforeVa_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editFaultBeforeVa,fv);
	float fNewValue =SetEditValueControl(fv,2,ui->m_editFaultBeforeVa);
	m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDI = fNewValue;
	//更新实时图Y坐标轴范围
	SetStateMonitorYRange();
}
//故障前相角
void QSttMacroParaEditViewFaultGradient::on_EditFaultBeforeAngle_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editFaultBeforeAngle,fv);
	float fNewValue = SetEditValueControl(fv,4,ui->m_editFaultBeforeAngle);
	m_pCurFGTest->m_oFaultGradientParas.m_fEDUaIaAngle = fNewValue;
}

///////////////////////////
void QSttMacroParaEditViewFaultGradient::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
								long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	tmt_faultGradientTest *pGradientParas = (tmt_faultGradientTest*)pParas;

	if(stt_xml_serialize_is_read(pMacroParas) || stt_xml_serialize_is_register(pMacroParas))
	{
		stt_xml_serialize(&pGradientParas->m_oFaultGradientParas, pMacroParas);	//文件的读写
	}
	else if (pParas->m_nSelected)
	{
		stt_xml_serialize(&pGradientParas->m_oFaultGradientParas, pMacroParas);	//测试参数下发
	}

	if (bHasGoosePub)
	{
		CIecCfgGoutDatas *pGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr()/*m_listGoosePub.at(0)*/;
		ASSERT(pGoutDatas);
		SerializeGoosePubs(pMacroParas,pGoutDatas);

		CIecCfgDatasSMV *pDatasSMV = m_listFT3Pub.at(0);
		ASSERT(pDatasSMV);
		SerializeFT3Pubs(pMacroParas,pDatasSMV);
	}
}

PTMT_PARAS_HEAD QSttMacroParaEditViewFaultGradient::CreateTestParas(const char * pszMacroID)
{
	PTMT_PARAS_HEAD pNewTest = new tmt_fault_gradient_test;
	strcpy(pNewTest->m_oRsltExprMngr.m_pszExprGroupID, _T("Common"));
	return pNewTest;
}

void QSttMacroParaEditViewFaultGradient::OnViewTestStart()
{
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	ui->m_tabWidget->setEnabled(0);
	//ToDo W
	stt_Frame_ClearInfoWidget();
	ConvertChannelAndType();
	stt_Frame_InitStateMonitor(m_nChannel, m_nType, stt_Frame_IsTestStarted(), this);//状态图暂无对应m_nChangeValue，先写死 wangtao 20240902
	stt_Frame_StartStateMonitor();
	stt_Frame_StartVectorWidget();
	stt_Frame_StartPowerWidget();
	stt_Frame_EnableManualTriggerButton(false);


}
void QSttMacroParaEditViewFaultGradient::OnViewTestStop()
{
	ui->m_tabWidget->setEnabled(1);
	//ToDo W
	stt_Frame_StopStateMonitor();
	stt_Frame_StopVectorWidget();
	stt_Frame_StopPowerWidget();
}

void QSttMacroParaEditViewFaultGradient::ShowReport(CDvmValues *pValues)
{
	//根据id获取值
	CDvmValue* pTripData = (CDvmValue*)pValues->FindByID("TripValue");
	CDvmValue* pReturnData = (CDvmValue*)pValues->FindByID("ReturnValue");
	CDvmValue* pCoefData = (CDvmValue*)pValues->FindByID("ReturnCoef");

	float fTripValue = 0, fReturnValue = 0, fReturnCoef = 0;

	if(pTripData != NULL)  fTripValue = GlobalSetResultValue(pTripData,3);
	
	if(pReturnData != NULL) fReturnValue = GlobalSetResultValue(pReturnData,3);
	
	if(pCoefData != NULL) fReturnCoef = GlobalSetResultValue(pCoefData,3);
}

void QSttMacroParaEditViewFaultGradient::GetDatas(CDataGroup *pParas)
{
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewFaultGradient::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		CSttDataGroupSerializeRead oRead(pParas);
		stt_xml_serialize(&m_pCurFGTest->m_oFaultGradientParas, &oRead);
		ReadModeDataSaveMaps(&oRead);	//add wangtao 20241010 保存模板中定值关联关系
	}

	
	if (m_oGradientChs.GetCount() == 0)
	{
		if (g_oSttTestResourceMngr.m_pTestResouce != NULL)
		{
			g_oSttTestResourceMngr.m_pTestResouce->AddGradientChs_All(m_oGradientChs);
		}
	}
	stt_Frame_InitVectorWidget(NULL, NULL);
	stt_Frame_InitPowerWidget(NULL, NULL);
	stt_Frame_InitStateMonitor(TRUE, NULL);
	stt_Frame_InitStateMonitor(m_nChannel, m_nType, stt_Frame_IsTestStarted(), this);
	stt_Frame_ClearInfoWidget();

	SetParas();

	UpdateGoutTab();
	UpdateFT3Tab();
}

void QSttMacroParaEditViewFaultGradient::UpdateTestResource(BOOL bCreateChMaps)
{
	//UpdateSequenceGradientChs();
	//InitParas(); //重新初始化递变参数
	SetParas();
	UpdateGoutTab();
	UpdateFT3Tab();
	UpdateBinBoutExTab();
	//updateLabName();
}

CString QSttMacroParaEditViewFaultGradient::GetDefaultParaFile()
{
	CString strFile = _P_GetConfigPath();
	strFile += FILE_FAULTGRADIENT; //文件名
	strFile += _T(".");
	strFile += POSTFIX_FAULTGRADIENT; //文件后缀
	return strFile;
}

bool QSttMacroParaEditViewFaultGradient::IsValidTestParasFile(const CString& strParasFile,bool bOpen)
{
	//文件后缀名判断是否正确
	if (strParasFile.IsEmpty() || ParseFilePostfix(strParasFile) != FILE_FAULTGRADIENT)  return false;
	
	if(bOpen && !IsFileExist(strParasFile))
	{
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////
//FT3 goose 数据更新
void QSttMacroParaEditViewFaultGradient::UpdateGoutTab(BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		InitGoosePubDataGroups();
		UpdateGoutTab_UI(g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr()/*m_listGoosePub.at(0)*/);
	}
	else
	{
		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewFaultGradient::UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas)
{
	//connect 连接没有实现  去掉 使用再增加
	if ((m_pGooseParaWidget == NULL) && (g_oSystemParas.m_nHasDigital)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC> 0))//数字输出且无goose界面
	{
		AddGooseParaWidget(pCfgGoutDatas);
	}
	else if ((m_pGooseParaWidget != NULL) && (!g_oSystemParas.m_nHasDigital))
	{
		RemoveGooseParaWidget();//更新后不需要goose界面
	}
	else if ((m_pGooseParaWidget != NULL) && (g_oSystemParas.m_nHasDigital))
	{
		m_pGooseParaWidget->initGoosePubTable(pCfgGoutDatas);
	}
	else if ((m_pGooseParaWidget != NULL)&&(g_oSttTestResourceMngr.m_nTotalFiberNum_LC == 0))//更新前有GOOSE界面,更新后LC口为0不需要
	{
// 		disconnect(m_pGooseParaWidget, SIGNAL(sig_GooseDataChanged()), this, SLOT(slot_GooseDataChanged()));
// 		disconnect(m_pGooseParaWidget, SIGNAL(sig_RepairDataChanged()), this, SLOT(slot_GooseDataChanged()));
// 		disconnect(m_pGooseParaWidget, SIGNAL(sig_GoutMapChanged()), this, SLOT(slot_GoutMapChanged()));

		RemoveGooseParaWidget();
	}
}

void QSttMacroParaEditViewFaultGradient::UpdateFT3Tab_UI(CIecCfgDatasSMV* pIecCfgDatasSMV)
{

	int nFT3Block = 0;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();
	while(pos)
	{
		CIecCfgDataBase* pIecCfgDataBase = (CIecCfgDataBase *)pIecCfgDatasSMV->GetNext(pos);
		if (pIecCfgDataBase->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA && pIecCfgDataBase->m_nUseFlag)
		{
			nFT3Block ++;
		}
	}

	//判断数字量输出类型以及FT3的界面  connnect  同上
	if ((m_pFT3OutParaWidget == NULL) && (g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0) && (nFT3Block > 0))
	{
		AddFT3OutParaWidget(pIecCfgDatasSMV);
	}
	else if ((m_pFT3OutParaWidget != NULL) && (!g_oSystemParas.IsDigitalOutputFT3()))
	{
		RemoveFT3OutParaWidget();
	}
	else if ((m_pFT3OutParaWidget != NULL) && (g_oSystemParas.IsDigitalOutputFT3())&&(g_oSttTestResourceMngr.m_nTotalFiberNum_STSend> 0))
	{
		if(nFT3Block > 0)
		{
// 			disconnect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		m_pFT3OutParaWidget->InitFT3Table(pIecCfgDatasSMV);
// 			connect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
		}
		else
		{
// 			disconnect(m_pFT3OutParaWidget, SIGNAL(sig_FT3DataChanged()), this, SLOT(slot_FT3DataChanged()));
			RemoveFT3OutParaWidget();
		}

		//m_pFT3OutParaWidget->InitFT3Table(pIecCfgDatasSMV);
	}
}

void QSttMacroParaEditViewFaultGradient::UpdateFT3Tab(BOOL bUpdateList)
{
	if (g_oSystemParas.m_nHasDigital)
	{
		InitFT3PubDataGroups();
		UpdateFT3Tab_UI(m_listFT3Pub.at(0));
	}
	else
	{
		RemoveFT3OutParaWidget();
	}
}

//goose 界面 添加 删除
void QSttMacroParaEditViewFaultGradient::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)  return;

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas, FALSE);
	int nInsertPos = ui->m_tabWidget->count();
	CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	ui->m_tabWidget->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QSttMacroParaEditViewFaultGradient::RemoveGooseParaWidget()
{
	if (m_pGooseParaWidget == NULL)  return;
	ui->m_tabWidget->removeTab(ui->m_tabWidget->indexOf(m_pGooseParaWidget));
	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QSttMacroParaEditViewFaultGradient::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		ui->m_tabWidget->setTabEnabled(ui->m_tabWidget->indexOf(m_pGooseParaWidget),b);
	}
}

bool QSttMacroParaEditViewFaultGradient::ExistGooseParaWidget()
{
	//获取ui界面中的goose界面，判断是否有该界面
	int nIndex = ui->m_tabWidget->indexOf(m_pGooseParaWidget);
	return (nIndex >= 0);
}

// FT3 界面添加 删除
void QSttMacroParaEditViewFaultGradient::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}
	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV, TRUE);
	int nInsertPos = ui->m_tabWidget->count();
	CString strTitle = _T("FT3发布");
	//在界面中插入FT3界面
	ui->m_tabWidget->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QSttMacroParaEditViewFaultGradient::RemoveFT3OutParaWidget()
{
	if (m_pFT3OutParaWidget == NULL)  return;
	
	ui->m_tabWidget->removeTab(ui->m_tabWidget->indexOf(m_pFT3OutParaWidget));
	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

void QSttMacroParaEditViewFaultGradient::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		ui->m_tabWidget->setTabEnabled(ui->m_tabWidget->indexOf(m_pGooseParaWidget),b);
	}
}

bool QSttMacroParaEditViewFaultGradient::ExistFT3OutParaWidget()
{
	int nIndex = ui->m_tabWidget->indexOf(m_pFT3OutParaWidget);
	return (nIndex >= 0);
}
void QSttMacroParaEditViewFaultGradient::ConvertChannelAndType()
{
	switch (m_nEditControlType)
	{
	case 1://阻抗
		m_nChannel = z_type;
		m_nType = amplitude_type;
		break;
	case 2://故障电流
		m_nChannel = if_type;
		m_nType = amplitude_type;
		break;
	case 3://故障电压
		m_nChannel = uf_type;
		m_nType = amplitude_type;
		break;
	case 4://阻抗角
		m_nChannel = z_type;
		m_nType = phasor_type;
		break;
	case 5://频率
		m_nChannel = if_type;
		m_nType = fre_type;
		break;
	}
}