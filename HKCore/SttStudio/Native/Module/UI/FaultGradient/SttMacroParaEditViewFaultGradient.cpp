#include "SttMacroParaEditViewFaultGradient.h"
#include "CFaultGradientSetting.h"
#include "FaultGradientEstimateDlg.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include"../Module/XLangResource_Native.h"
#include "../../Module/XLanguage/XLanguageResource.h"
#include "../SttTestCntrFrameBase.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewFaultGradient::QSttMacroParaEditViewFaultGradient(QWidget *parent)
	:/* QWidget(parent)*/ui(new Ui::QSttMacroParaEditViewFaultGradient)
	
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	m_nLastFaultModeIndex = 0;
	m_nOutNormalError = (ui->btnGrpOutNormalError->buttons().count())/2;	
	m_pGooseParaWidget = NULL;
	m_pFT3OutParaWidget = NULL;
	InitLanuage();
	//初始化创建测试项
	SetData(CreateTestParas(GetMacroID())); 
	InitUI();
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();//创建软件资源类对象
	g_theTestCntrFrame->InitTestResource();//软件资源初始化

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

}

void QSttMacroParaEditViewFaultGradient::SetUIFont(QWidget* pWidget)
{
	g_pSttGlobalFont->resolve(QFont::AllPropertiesResolved);

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

	m_lstGradientType << _T("动作值") << _T("返回系数") << _T("最大灵敏角") ;
	ui->m_cbbType->addItems(m_lstGradientType);

	m_lstFaultMode << _T("A相短路") << _T("B相短路") << _T("C相短路") << _T("ABC相短路") << _T("AB相短路") << _T("BC相短路") << _T("CA相短路") 
					<< _T("AB相短路，C相电流") << _T("BC相短路，A相电流") << _T("CA相短路，B相电流") << _T("AB相短路，B相电流") 
					<< _T("BC相短路，C相电流") << _T("CA相短路，A相电流") /*<< _T("CA相短路，A相电流")*/ << _T("U/f") << _T("I2/I1");
	ui->m_cbbFaultMode->addItems(m_lstFaultMode);

	QStringList lstChangeValue;
	lstChangeValue << _T("短路电压") << _T("短路电流") << _T("阻抗角") << _T("短路阻抗") << _T("频率") 
					 << _T("正序电压") << _T("负序电压") << _T("零序电压（3U0）");

	m_mapChangValue[FG_FaultMode_Null] = lstChangeValue;
	QStringList lstChangeValue_UF;
	lstChangeValue_UF << _T("电压") << _T("频率");
	m_mapChangValue[FG_FaultMode_UF] = lstChangeValue_UF;
	QStringList lstChangeValue_I2;
	lstChangeValue_I2 << _T("I2");
	m_mapChangValue[FG_FaultMode_I2I1] = lstChangeValue_I2;

	QStringList lstChangeValue_AB_C;
	lstChangeValue_AB_C << _T("Uab") << _T("Ic") << _T("Φ(Uab-Ic)");
	m_mapChangValue[FG_FaultMode_AB_C] = lstChangeValue_AB_C;

	QStringList lstChangeValue_BC_A;
	lstChangeValue_BC_A << _T("Ubc") << _T("Ia") << _T("Φ(Ubc-Ia)");
	m_mapChangValue[FG_FaultMode_BC_A] = lstChangeValue_BC_A;

	QStringList lstChangeValue_CA_B;
	lstChangeValue_CA_B << _T("Uca") << _T("Ib") << _T("Φ(Uca-Ib)");
	m_mapChangValue[FG_FaultMode_CA_B] = lstChangeValue_CA_B;

	QStringList lstChangeValue_AB_B;
	lstChangeValue_AB_B << _T("Uab") << _T("Ib") << _T("Φ(Uab-Ib)");
	m_mapChangValue[FG_FaultMode_AB_B] = lstChangeValue_AB_B;

	QStringList lstChangeValue_BC_C;
	lstChangeValue_BC_C << _T("Ubc") << _T("Ic") << _T("Φ(Ubc-Ic)");
	m_mapChangValue[FG_FaultMode_BC_C] = lstChangeValue_BC_C;

	QStringList lstChangeValue_CA_A;
	lstChangeValue_CA_A << _T("Uca") << _T("Ia") << _T("Φ(Uca-Ia)");
	m_mapChangValue[FG_FaultMode_CA_A] = lstChangeValue_CA_A;

	ui->m_cbbChangeVaule->addItems(lstChangeValue);

	m_lstShortVm << _T("正序(U1)") << _T("负序(U2)") << _T("零序(3U0)");
	ui->m_cbbShortVm->addItems(m_lstShortVm);
}

void QSttMacroParaEditViewFaultGradient::InitUI()
{
	//初始化界面属性 和设置
	SetUIFont(ui->m_tabWidget);
	InitComboBox();

	SetStyleStateValue(ui->m_gpBin);
	SetStyleStateValue(ui->m_gpBoutNormal);
	SetStyleStateValue(ui->m_gpBoutError);
	((QSttTabWidget*)ui->m_tabWidget)->InitStyleSheet();
}

void QSttMacroParaEditViewFaultGradient::SetParas()
{
	ui->m_editInit->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fStart, 'f', 3));
	ui->m_editFinish->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fStop, 'f', 3));
	ui->m_editStep->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fStep, 'f', 3));
	ui->m_editFaultTime->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fFaultTime, 'f', 3));
	ui->m_cbbType->setCurrentIndex(m_pCurFGTest->m_oFaultGradientParas.m_nTestMode);

	ui->m_cbbFaultMode->setCurrentIndex(m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode);
	on_FaultMode_currentIndexChanged(m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode);
	ui->m_cbbChangeVaule->setCurrentIndex(m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue);
	on_ChangeValue_currentIndexChanged(-1);

	ui->m_cbbShortVm->setCurrentIndex(m_pCurFGTest->m_oFaultGradientParas.m_nShortVmType);
	ui->m_editShortVm->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fShortVm, 'f', 3));
	ui->m_editShortVa->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fShortVa, 'f', 3));
	ui->m_editAngle->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fAngle, 'f', 3));

	ui->m_editTimeBeforeChange->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fPrepareTime, 'f', 3));
	if(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime < 0.0001)
	{
		m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime = 0;
		ui->m_editTimeBeforeFail->setText("0");
		ui->m_editTimeBeforeFail->setEnabled(false);
	}
	else
	{
		ui->m_editTimeBeforeFail->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultTime,'f',3));
	}

	ui->m_editFaultBeforeVm->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDU, 'f', 3));
	ui->m_editFaultBeforeVa->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDI, 'f', 3));
	ui->m_editFaultBeforeAngle->setText(QString::number(m_pCurFGTest->m_oFaultGradientParas.m_fEDUaIaAngle, 'f', 3));

	SetStyleStateValue(ui->m_gpBin,-1,0);
	SetStyleStateValue(ui->m_gpBoutNormal,-1,1);
	SetStyleStateValue(ui->m_gpBoutError,-1,1);
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
		}
		else if(nChangIndex == 1)
		{
			SetUnit(nFaultIndex,nChangIndex,"A");
			m_nEditControlType = 2;
		}
		else if(nChangIndex == 2)
		{
			SetUnit(nFaultIndex,nChangIndex,"°");
			m_nEditControlType = 4;
		}
	}
	else if(nFaultIndex == FG_FaultMode_UF)
	{
		if(nChangIndex == FG_FM_Vaule_VM) 
		{
			SetUnit(nFaultIndex,nChangIndex,"V");
			m_nEditControlType = 3;
		}
		else if(nChangIndex == FG_FM_Vaule_HZ) 
		{
			SetUnit(nFaultIndex,nChangIndex,"HZ");
			m_nEditControlType = 5;
		}
	}
	else if(nFaultIndex == FG_FaultMode_I2I1)
	{
		SetUnit(nFaultIndex,nChangIndex,"A");
		m_nEditControlType = 2;
	}
	else
	{
		if(nChangIndex == FG_FM_Vaule_ShortVM || nChangIndex == FG_FM_Vaule_PlusVM 
			|| nChangIndex == FG_FM_Vaule_MinusVM ||nChangIndex == FG_FM_Vaule_ZeroVM) 
		{
			SetUnit(nFaultIndex,nChangIndex,"V");
			m_nEditControlType = 3;
		}
		if(nChangIndex == FG_FM_Vaule_ShortVA || nChangIndex == FG_FM_Vaule_ShortImpede) 
		{
			SetUnit(nFaultIndex,nChangIndex,"A");
			m_nEditControlType = 2;
		}
		if(nChangIndex == FG_FM_Vaule_ImpedeAngle) 
		{
			SetUnit(nFaultIndex,nChangIndex,"°");
			m_nEditControlType = 4;
		}
		if(nChangIndex == FG_FM_Vaule_Frequency) 
		{
			SetUnit(nFaultIndex,nChangIndex,"HZ");
			m_nEditControlType = 5;
		}
	}
	SetAllEditValueControl();
}

void QSttMacroParaEditViewFaultGradient::SetUnit(int nFaultMode,int nValueType,QString strUnit)
{
	QString strTemp = ui->m_labInit->text();
	int nPos = strTemp.indexOf("(");

	QString strLabInit = strTemp.left(nPos) + "(" + strUnit + ")";
	QString strLabFinish = ((QString)ui->m_labFinish->text()).left(nPos) + "(" + strUnit + ")";
	QString strLabStep = ((QString)ui->m_labStep->text()).left(nPos) + "(" + strUnit + ")";
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

//设置edit 值限制 1 时间  2 电流  3 电压  4 角度 5 HZ
float QSttMacroParaEditViewFaultGradient::SetEditValueControl(float fValue,int nFlag,QSttLineEdit* pLine)
{
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
	if(m_nEditControlType == 4)
	{
		if(nIndex == FG_TestMode_ActValue || nIndex == FG_TestMode_ReturnCoef)
		{
			ui->m_cbbType->setCurrentIndex(FG_TestMode_MaxAngle);
			return;
		}
	}
	if (m_pCurFGTest->m_oFaultGradientParas.m_nTestMode != nIndex)
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nTestMode = nIndex;
		//ToDo W
		m_bTmtParaChanged = TRUE;
	}
}

void QSttMacroParaEditViewFaultGradient::on_FaultMode_currentIndexChanged(int nIndex)
{
	if (m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode != nIndex)
	{
		m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode = nIndex;
	}

	if(m_nLastFaultModeIndex == nIndex) return;

	ui->m_cbbChangeVaule->clear();
	m_nLastFaultModeIndex = nIndex;
	if(nIndex > FG_FaultMode_CA)
	{
		ui->m_cbbChangeVaule->addItems(m_mapChangValue[nIndex]);
	}
	else
	{
		ui->m_cbbChangeVaule->addItems(m_mapChangValue[FG_FaultMode_Null]);
	}
}

void QSttMacroParaEditViewFaultGradient::on_ChangeValue_currentIndexChanged(int nIndex)
{
	if(ui->m_cbbChangeVaule->IsScrolling()) return;

	if (m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue != nIndex)
	{
		if(nIndex == -1)
		{
			nIndex = m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue;
		}
		m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue = nIndex;
		//设置单位  控件使用
		int nValIndex = ui->m_cbbFaultMode->currentIndex();
		SetLableTextUnit(nValIndex,nIndex);
		SetShortVaVmAngle(nValIndex,nIndex);

	}
	//ToDo
	m_bTmtParaChanged = TRUE;
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
	float fv = 0.000;
	GetEditFloatValue(ui->m_editInit,fv);
	float fNewValue = SetEditValueControl(fv,m_nEditControlType,ui->m_editInit);
	// 业务处理  暂无  直接赋值
	m_pCurFGTest->m_oFaultGradientParas.m_fStart = fNewValue;
}
//变化终值
void QSttMacroParaEditViewFaultGradient::on_EditFinish_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editFinish,fv);
	float fNewValue = SetEditValueControl(fv,m_nEditControlType,ui->m_editFinish);
	m_pCurFGTest->m_oFaultGradientParas.m_fStop = fNewValue;
}
//变化步长
void QSttMacroParaEditViewFaultGradient::on_EditStep_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editStep,fv);
	float fNewValue = SetEditValueControl(fv,m_nEditControlType,ui->m_editStep);
	m_pCurFGTest->m_oFaultGradientParas.m_fStep = fNewValue;
}
//故障时间
void QSttMacroParaEditViewFaultGradient::on_EditFaultTime_Finish()
{
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
}
//故障前电压
void QSttMacroParaEditViewFaultGradient::on_EditFaultBeforeVm_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editFaultBeforeVm,fv);
	float fNewValue = SetEditValueControl(fv,3,ui->m_editFaultBeforeVm);
	m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDU = fNewValue;
}
//故障前电流
void QSttMacroParaEditViewFaultGradient::on_EditFaultBeforeVa_Finish()
{
	float fv = 0.000;
	GetEditFloatValue(ui->m_editFaultBeforeVa,fv);
	float fNewValue =SetEditValueControl(fv,2,ui->m_editFaultBeforeVa);
	m_pCurFGTest->m_oFaultGradientParas.m_fPreFaultEDI = fNewValue;
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
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->InitStateMonitor(m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode, m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue, g_theTestCntrFrame->IsTestStarted());
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
	g_theTestCntrFrame->EnableManualTriggerButton(false);

}
void QSttMacroParaEditViewFaultGradient::OnViewTestStop()
{
	ui->m_tabWidget->setEnabled(1);
	//ToDo W
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
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
	}
	//ToDo
	/*if (m_oSequenceGradientChs.GetCount() == 0)
	{
		if (g_oSttTestResourceMngr.m_pTestResouce != NULL)
		{
			g_oSttTestResourceMngr.m_pTestResouce->AddGradientChs_All(m_oSequenceGradientChs);
		}
	}*/

	//ToDo
	//g_theTestCntrFrame->InitVectorWidget(m_pCurPara->m_uiVOL[0],m_pCurPara->m_uiCUR[0]);
	//g_theTestCntrFrame->InitPowerWidget(m_pCurPara->m_uiVOL[0],m_pCurPara->m_uiCUR[0]);
	//g_theTestCntrFrame->InitStateMonitor(true, NULL);
	//g_theTestCntrFrame->InitStateMonitor(m_pCurFGTest->m_oFaultGradientParas.m_nFaultMode, m_pCurFGTest->m_oFaultGradientParas.m_nChangeValue, g_theTestCntrFrame->IsTestStarted(), this);
	//g_theTestCntrFrame->ClearInfoWidget();

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