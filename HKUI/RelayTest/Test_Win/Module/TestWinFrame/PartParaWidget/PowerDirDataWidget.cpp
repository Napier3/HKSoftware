#include "PowerDirDataWidget.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

PowerDirDataWidget::PowerDirDataWidget(QWidget *parent)
	: QWidget(parent)
{
	InitUI();
}

PowerDirDataWidget::~PowerDirDataWidget()
{

}

void PowerDirDataWidget::InitUI()
{
	strListTestPhase.clear();
	strListFaultPhase.clear();

	m_MainLayout = new QHBoxLayout;
	m_leftLayout = new QGridLayout;
	m_rightLayout = new QGridLayout;

	QFont ft("Microsoft YaHei", 10);

	strListTestPhase<</*tr("A相")*/g_sLangTxt_Aphase<</*tr("B相")*/g_sLangTxt_Bphase<</*tr("C相")*/g_sLangTxt_Cphase<</*tr("零序")*/g_sLangTxt_Native_ZeroSeq<</*tr("负序")*/g_sLangTxt_Native_NegativeSeq;
	label_TestPhase = new QLabel();
	label_TestPhase->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_TestPhase->setFont(ft);
	label_TestPhase->setText(/*QObject::tr("测试相:")*/g_sLangTxt_State_Testphase+":");
	m_leftLayout->addWidget(label_TestPhase,0,0);
	m_CmbTestPhase = new QComboBox;
	m_CmbTestPhase->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_CmbTestPhase->addItems(strListTestPhase);
	m_CmbTestPhase->setFont(ft);
	m_leftLayout->addWidget(m_CmbTestPhase,0,1);

	strListFaultPhase<</*tr("A相")*/g_sLangTxt_Aphase<</*tr("B相")*/g_sLangTxt_Bphase<</*tr("C相")*/g_sLangTxt_Cphase<</*tr("AB相")*/g_sLangTxt_ABphase<</*tr("BC相")*/g_sLangTxt_BCphase<</*tr("CA相")*/g_sLangTxt_CAphase<</*tr("ABC三相")*/g_sLangTxt_Native_ABCTP<</*tr("零序")*/g_sLangTxt_Native_ZeroSeq<</*tr("负序")*/g_sLangTxt_Native_NegativeSeq;
	label_FaultPhase = new QLabel();
	label_FaultPhase->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_FaultPhase->setFont(ft);
	label_FaultPhase->setText(/*QObject::tr("故障相:")*/g_sLangTxt_CharLib_FaultPhase+":");
	m_leftLayout->addWidget(label_FaultPhase,1,0);
	m_CmbFaultPhase = new QComboBox();
	m_CmbFaultPhase->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_CmbFaultPhase->addItems(strListFaultPhase);
	m_CmbFaultPhase->setFont(ft);
	m_leftLayout->addWidget(m_CmbFaultPhase,1,1);

	label_SCVoltage = new QLabel();
	label_SCVoltage->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_SCVoltage->setFont(ft);
	label_SCVoltage->setText(/*QObject::tr("故障电压(V):")*/g_sLangTxt_Native_Faultcurrent+":");
	m_leftLayout->addWidget(label_SCVoltage,2,0);
	m_LineSCVoltage = new QLineEdit();
	m_LineSCVoltage->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineSCVoltage->setFont(ft);
	m_leftLayout->addWidget(m_LineSCVoltage,2,1);

	label_SCCurrent = new QLabel();
	label_SCCurrent->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_SCCurrent->setFont(ft);
	label_SCCurrent->setText(/*QObject::tr("故障电流(A):")*/g_sLangTxt_Native_FaultCurrValue+"(A):");
	m_leftLayout->addWidget(label_SCCurrent,3,0);
	m_LineSCCurrent = new QLineEdit();
	m_LineSCCurrent->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineSCCurrent->setFont(ft);
	m_leftLayout->addWidget(m_LineSCCurrent,3,1);

	label_Freq = new QLabel();
	label_Freq->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_Freq->setFont(ft);
	label_Freq->setText(/*QObject::tr("频率(Hz):")*/g_sLangTxt_Frequency);
	m_leftLayout->addWidget(label_Freq,4,0);
	m_LineFreq = new QLineEdit();
	m_LineFreq->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineFreq->setFont(ft);
	m_LineFreq->setDisabled(true);
	m_leftLayout->addWidget(m_LineFreq,4,1);

	label_Start = new QLabel();
	label_Start->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_Start->setFont(ft);
	label_Start->setText(/*QObject::tr("变化始值(°):")*/g_sLangTxt_Gradient_Init+"(°):");
	m_rightLayout->addWidget(label_Start,0,0);
	m_LineStart = new QLineEdit();
	m_LineStart->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineStart->setFont(ft);
	m_rightLayout->addWidget(m_LineStart,0,1);

	label_Stop = new QLabel();
	label_Stop->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_Stop->setFont(ft);
	label_Stop->setText(/*QObject::tr("变化终值(°):")*/g_sLangTxt_Gradient_Finish+"(°):");
	m_rightLayout->addWidget(label_Stop,1,0);
	m_LineStop = new QLineEdit();
	m_LineStop->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineStop->setFont(ft);
	m_rightLayout->addWidget(m_LineStop,1,1);

	label_Step = new QLabel();
	label_Step->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_Step->setFont(ft);
	label_Step->setText(/*QObject::tr("变化步长(°):")*/g_sLangTxt_Gradient_Step+"(°):");
	m_rightLayout->addWidget(label_Step,2,0);
	m_LineStep = new QLineEdit();
	m_LineStep->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineStep->setFont(ft);
	m_rightLayout->addWidget(m_LineStep,2,1);

	label_StepTime = new QLabel();
	label_StepTime->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_StepTime->setFont(ft);
	label_StepTime->setText(/*QObject::tr("故障时间(s):")*/g_sLangTxt_Gradient_Time+"(s):");
	m_rightLayout->addWidget(label_StepTime,3,0);
	m_LineStepTime = new QLineEdit();
	m_LineStepTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineStepTime->setFont(ft);
	m_rightLayout->addWidget(m_LineStepTime,3,1);

	pSpacer1 = new QSpacerItem(30,20,QSizePolicy::Maximum,QSizePolicy::Maximum);
	pSpacer2 = new QSpacerItem(30,20,QSizePolicy::Maximum,QSizePolicy::Maximum);
	pSpacer3 = new QSpacerItem(30,20,QSizePolicy::Maximum,QSizePolicy::Maximum);

	m_MainLayout->addSpacerItem(pSpacer1);
	m_MainLayout->addLayout(m_leftLayout);
	m_MainLayout->addSpacerItem(pSpacer2);
	m_MainLayout->addLayout(m_rightLayout);
	m_MainLayout->addSpacerItem(pSpacer3);

	setLayout(m_MainLayout);

	connect(m_CmbTestPhase,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TestPhaseCurrentIndexChanged(int)));
	connect(m_CmbFaultPhase,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_FaultPhaseCurrentIndexChanged(int)));
	connect(m_LineSCVoltage,SIGNAL(editingFinished()),this,SLOT(slot_SCVoltage_editingFinished()));
	connect(m_LineSCCurrent,SIGNAL(editingFinished()),this,SLOT(slot_SCCurrent_editingFinished()));

	connect(m_LineStart,SIGNAL(editingFinished()),this,SLOT(slot_Start_editingFinished()));
	connect(m_LineStop,SIGNAL(editingFinished()),this,SLOT(slot_Stop_editingFinished()));
	connect(m_LineStep,SIGNAL(editingFinished()),this,SLOT(slot_Step_editingFinished()));
	connect(m_LineStepTime,SIGNAL(editingFinished()),this,SLOT(slot_StepTime_editingFinished()));
}

void PowerDirDataWidget::setData( PTMT_PARAS_HEAD pCurr )
{
	ASSERT(pCurr != NULL);
	m_PowerDirTest = (tmt_PowerDirectionTest*)pCurr;
	m_PowerDirParas = &m_PowerDirTest->m_oTmtParas;
	m_PowerDirResults = &m_PowerDirTest->m_oTmtResults;

	InitData();
}

void PowerDirDataWidget::InitData()
{
	disconnect(m_CmbTestPhase,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TestPhaseCurrentIndexChanged(int)));
	disconnect(m_CmbFaultPhase,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_FaultPhaseCurrentIndexChanged(int)));

	m_CmbTestPhase->setCurrentIndex(m_PowerDirParas->m_nTestPhase);
	SetFaultPhaseIndex(m_PowerDirParas->m_nTestPhase);
	m_LineSCVoltage->setText(m_PowerDirParas->m_pszSCVoltage);
	m_LineSCCurrent->setText(m_PowerDirParas->m_pszSCCurrent);

	m_LineStart->setText(m_PowerDirParas->m_pszStart);
	m_LineStop->setText(m_PowerDirParas->m_pszStop);
	m_LineStep->setText(QString::number( m_PowerDirParas->m_fStep, 'f', 3));
	m_LineStepTime->setText(m_PowerDirParas->m_pszStepTime);
	m_LineFreq->setText(QString::number(g_oSystemParas.m_fFNom, 'f', 3));

	m_LineSCVoltage->setCursorPosition(0);
	m_LineSCCurrent->setCursorPosition(0);
	m_LineStart->setCursorPosition(0);
	m_LineStop->setCursorPosition(0);
	m_LineStep->setCursorPosition(0);
	m_LineStepTime->setCursorPosition(0);
	m_LineFreq->setCursorPosition(0);

	connect(m_CmbTestPhase,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_TestPhaseCurrentIndexChanged(int)));
	connect(m_CmbFaultPhase,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_FaultPhaseCurrentIndexChanged(int)));
}
void PowerDirDataWidget::slot_cmb_TestPhaseCurrentIndexChanged( int )
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	int nIndex = m_CmbTestPhase->currentIndex();
	SetFaultPhaseIndex(nIndex);

	m_PowerDirParas->m_nTestPhase = nIndex;
	emit sig_TestPhaseChanged();
}

void PowerDirDataWidget::slot_cmb_FaultPhaseCurrentIndexChanged( int )
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	int nIndex = m_CmbFaultPhase->currentIndex();
	GetFaultPhaseNumber(nIndex);
	
	emit sig_FaultPhaseChanged();
}
void PowerDirDataWidget::slot_SCVoltage_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	float fmax;

	switch (m_PowerDirParas->m_nTestPhase)
	{
	case POWER_DIR_FAULT_PHASE_A:
	case POWER_DIR_FAULT_PHASE_B:
	case POWER_DIR_FAULT_PHASE_C:
	case POWER_DIR_FAULT_PHASE_ZERO:
	case POWER_DIR_FAULT_PHASE_NEG:
		fmax = g_oLocalSysPara.m_fAC_VolMax;
		break;
	case POWER_DIR_FAULT_PHASE_AB:
	case POWER_DIR_FAULT_PHASE_BC:
	case POWER_DIR_FAULT_PHASE_CA:
	case POWER_DIR_FAULT_PHASE_ABC:
		fmax = g_oLocalSysPara.m_fAC_VolMax*sqrt(3.0);
		break;
	}

	QString strExpr = m_LineSCVoltage->text();
	bool bOK = false;
	double lfv;
	float fv;
	bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
	fv = lfv;

	if (!bOK)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
		m_LineSCVoltage->setText(m_PowerDirParas->m_pszSCVoltage);
	}
	else
	{
		if (fv != setLimit(0,fmax,fv))
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("超出范围")*/g_sLangTxt_Native_OutOfRange.GetString());
			m_LineSCVoltage->setText(m_PowerDirParas->m_pszSCVoltage);
		}
		else
		{
			m_PowerDirParas->m_fSCVoltage = fv;
			CString strTemp = strExpr;
			CString_to_char(strTemp,m_PowerDirParas->m_pszSCVoltage);
			m_LineSCVoltage->setText(m_PowerDirParas->m_pszSCVoltage);
		}
	}
	m_LineSCVoltage->setCursorPosition(0);
	
	emit updateData();
}

void PowerDirDataWidget::slot_SCCurrent_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	float fmax;

	fmax = g_oLocalSysPara.m_fAC_CurMax;

	QString strExpr = m_LineSCCurrent->text();
	bool bOK = false;
	double lfv;
	float fv;
	bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
	fv = lfv;

	if (!bOK)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
		m_LineSCCurrent->setText(m_PowerDirParas->m_pszSCCurrent);
	}
	else
	{
		if (fv != setLimit(0,fmax,fv))
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("超出范围")*/g_sLangTxt_Native_OutOfRange.GetString());
			m_LineSCCurrent->setText(m_PowerDirParas->m_pszSCCurrent);
		}
		else
		{
			m_PowerDirParas->m_fSCCurrent = fv;
			CString strTemp = strExpr;
			CString_to_char(strTemp,m_PowerDirParas->m_pszSCCurrent);
			m_LineSCCurrent->setText(m_PowerDirParas->m_pszSCCurrent);
		}
	}
	m_LineSCCurrent->setCursorPosition(0);

	emit updateData();
}

void PowerDirDataWidget::slot_Start_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	QString strExpr = m_LineStart->text();
	bool bOK = false;
	double lfv;
	float fv;
	bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
	fv = lfv;

	if (!bOK)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
		m_LineStart->setText(m_PowerDirParas->m_pszStart);
	}
	else
	{
		if (fv > 360 || fv < -360)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式超出范围")*/g_sLangTxt_Native_ExprOutOfRange.GetString());
		}
		fv = setAngleLimitEx(fv);
		m_PowerDirParas->m_fStart = fv;
		CString strTemp = strExpr;
		CString_to_char(strTemp,m_PowerDirParas->m_pszStart);
		m_LineStart->setText(m_PowerDirParas->m_pszStart);
	}
	m_LineStart->setCursorPosition(0);
	
	emit updateData();
}

void PowerDirDataWidget::slot_Stop_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	QString strExpr = m_LineStop->text();
	bool bOK = false;
	double lfv;
	float fv;
	bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
	fv = lfv;

	if (!bOK)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
		m_LineStop->setText(m_PowerDirParas->m_pszStop);
	}
	else
	{
		if (fv > 360 || fv < -360)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式超出范围")*/g_sLangTxt_Native_ExprOutOfRange.GetString());
		}
		fv = setAngleLimitEx(fv);
		m_PowerDirParas->m_fStop = fv;
		CString strTemp = strExpr;
		CString_to_char(strTemp,m_PowerDirParas->m_pszStop);
		m_LineStop->setText(m_PowerDirParas->m_pszStop);
	}
	m_LineStop->setCursorPosition(0);
	
	emit updateData();
}

void PowerDirDataWidget::slot_Step_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	float fv = m_LineStep->text().toFloat();
        //20230607 suyang  设置步长时间最大值为10000, 防止输入步长时间太大，setAngleLimit计算超过360
	if(fv >10000)
	{
		fv = 10000;
	}

	fv = setAngleLimit(fv);

	m_PowerDirParas->m_fStep = fv;

	m_LineStep->setText(QString::number(fv,'f',3));

	m_LineStep->setCursorPosition(0);
	
	emit updateData();
}

void PowerDirDataWidget::slot_StepTime_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	QString strExpr = m_LineStepTime->text();
	bool bOK = false;
	double lfv;
	float fv;
	bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
	fv = lfv;

	if (!bOK)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
		m_LineStepTime->setText(m_PowerDirParas->m_pszStepTime);
	}
	else
	{
		if (fv != setLimit(0,999.999,fv))
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("超出范围")*/g_sLangTxt_Native_OutOfRange.GetString());
			m_LineStepTime->setText(m_PowerDirParas->m_pszStepTime);
		}
		else
		{
			m_PowerDirParas->m_fStepTime = fv;
			CString strTemp = strExpr;
			CString_to_char(strTemp,m_PowerDirParas->m_pszStepTime);
			m_LineStepTime->setText(m_PowerDirParas->m_pszStepTime);
		}
	}
	m_LineStepTime->setCursorPosition(0);
	emit updateData();
}
void PowerDirDataWidget::SetFaultPhaseIndex( int nIndex )
{
	//g_theSttXTestMngrBaseApp->SetModifyPara();
	strListFaultPhase.clear();
	int nCurrSelect = 0;
	if (nIndex == POWER_DIR_TEST_PHASE_A)
	{
		strListFaultPhase<<tr("AN")<<tr("AB")<<tr("CA")<<tr("ABC");
		switch (m_PowerDirParas->m_nFaultPhase)
		{
		case POWER_DIR_FAULT_PHASE_AB:
			nCurrSelect = 1;
			break;
		case POWER_DIR_FAULT_PHASE_CA:
			nCurrSelect = 2;
			break;
		case POWER_DIR_FAULT_PHASE_ABC:
			nCurrSelect = 3;
			break;
		default:
			{
				m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_A;
				nCurrSelect = 0;
			}
		}
	}
	else if (nIndex == POWER_DIR_TEST_PHASE_B)
	{
		strListFaultPhase<<tr("BN")<<tr("AB")<<tr("BC")<<tr("ABC");
		switch (m_PowerDirParas->m_nFaultPhase)
		{
		case POWER_DIR_FAULT_PHASE_AB:
			nCurrSelect = 1;
			break;
		case POWER_DIR_FAULT_PHASE_BC:
			nCurrSelect = 2;
			break;
		case POWER_DIR_FAULT_PHASE_ABC:
			nCurrSelect = 3;
			break;
		default:
			{
				m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_B;
				nCurrSelect = 0;
			}
			
		}
	}
	else if (nIndex == POWER_DIR_TEST_PHASE_C)
	{
		strListFaultPhase<<tr("CN")<<tr("BC")<<tr("CA")<<tr("ABC");
		switch (m_PowerDirParas->m_nFaultPhase)
		{
		case POWER_DIR_FAULT_PHASE_BC:
			nCurrSelect = 1;
			break;
		case POWER_DIR_FAULT_PHASE_CA:
			nCurrSelect = 2;
			break;
		case POWER_DIR_FAULT_PHASE_ABC:
			nCurrSelect = 3;
			break;
		default:
			{
				m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_C;
				nCurrSelect = 0;
			}
		}
	}
	else if (nIndex == POWER_DIR_TEST_PHASE_ZERO)
	{
		strListFaultPhase<<tr("Zero-Seq")<<tr("AN")<<tr("BN")<<tr("CN");
		switch (m_PowerDirParas->m_nFaultPhase)
		{
		case POWER_DIR_FAULT_PHASE_A:
			nCurrSelect = 1;
			break;
		case POWER_DIR_FAULT_PHASE_B:
			nCurrSelect = 2;
			break;
		case POWER_DIR_FAULT_PHASE_C:
			nCurrSelect = 3;
			break;
		default:
			{
				m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_ZERO;
				nCurrSelect = 0;
			}
		}
	}
	else if (nIndex == POWER_DIR_TEST_PHASE_NEG)
	{
		strListFaultPhase<<tr("Neg-Seq")<<tr("AN")<<tr("BN")<<tr("CN")<<tr("AB")<<tr("BC")<<tr("CA");
		switch (m_PowerDirParas->m_nFaultPhase)
		{
		case POWER_DIR_FAULT_PHASE_A:
			nCurrSelect = 1;
			break;
		case POWER_DIR_FAULT_PHASE_B:
			nCurrSelect = 2;
			break;
		case POWER_DIR_FAULT_PHASE_C:
			nCurrSelect = 3;
			break;
		case POWER_DIR_FAULT_PHASE_AB:
			nCurrSelect = 4;
			break;
		case POWER_DIR_FAULT_PHASE_BC:
			nCurrSelect = 5;
			break;
		case POWER_DIR_FAULT_PHASE_CA:
			nCurrSelect = 6;
			break;
		default:
			{
				m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_NEG;
				nCurrSelect = 0;
			}
		}
	}
	disconnect(m_CmbFaultPhase,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_FaultPhaseCurrentIndexChanged(int)));
	m_CmbFaultPhase->clear();
	m_CmbFaultPhase->addItems(strListFaultPhase);
	m_CmbFaultPhase->setCurrentIndex(nCurrSelect);
	connect(m_CmbFaultPhase,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cmb_FaultPhaseCurrentIndexChanged(int)));
}

void PowerDirDataWidget::GetFaultPhaseNumber( int nIndex )
{
	if (m_CmbTestPhase->currentIndex() == POWER_DIR_TEST_PHASE_A)
	{
		if (nIndex == 0)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_A;
		}
		else if (nIndex == 1)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_AB;
		}
		else if (nIndex == 2)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_CA;
		}
		else if (nIndex == 3)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_ABC;
		}
		else
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_A;
		}
	}
	else if (m_CmbTestPhase->currentIndex() == POWER_DIR_TEST_PHASE_B)
	{
		if (nIndex == 0)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_B;
		}
		else if (nIndex == 1)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_AB;
		}
		else if (nIndex == 2)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_BC;
		}
		else if (nIndex == 3)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_ABC;
		}
		else
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_B;
		}
	}
	else if (m_CmbTestPhase->currentIndex() == POWER_DIR_TEST_PHASE_C)
	{
		if (nIndex == 0)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_C;
		}
		else if (nIndex == 1)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_BC;
		}
		else if (nIndex == 2)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_CA;
		}
		else if (nIndex == 3)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_ABC;
		}
		else
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_C;
		}
	}
	else if (m_CmbTestPhase->currentIndex() == POWER_DIR_TEST_PHASE_ZERO)
	{
		if (nIndex == 0)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_ZERO;
		}
		else if (nIndex == 1)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_A;
		}
		else if (nIndex == 2)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_B;
		}
		else if (nIndex == 3)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_C;
		}
		else
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_ZERO;
		}
	}
	else if (m_CmbTestPhase->currentIndex() == POWER_DIR_TEST_PHASE_NEG)
	{
		if (nIndex == 0)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_NEG;
		}
		else if (nIndex == 1)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_A;
		}
		else if (nIndex == 2)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_B;
		}
		else if (nIndex == 3)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_C;
		}
		else if (nIndex == 4)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_AB;
		}
		else if (nIndex == 5)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_BC;
		}
		else if (nIndex == 6)
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_CA;
		}
		else
		{
			m_PowerDirParas->m_nFaultPhase = POWER_DIR_FAULT_PHASE_NEG;
		}
	}
}

void PowerDirDataWidget::startInit()
{
	m_CmbTestPhase->setDisabled(true);
	m_CmbFaultPhase->setDisabled(true);
	m_LineSCVoltage->setDisabled(true);
	m_LineSCCurrent->setDisabled(true);
	m_LineStart->setDisabled(true);
	m_LineStop->setDisabled(true);
	m_LineStep->setDisabled(true);
	m_LineStepTime->setDisabled(true);
}

void PowerDirDataWidget::stopInit()
{
	m_CmbTestPhase->setDisabled(false);
	m_CmbFaultPhase->setDisabled(false);
	m_LineSCVoltage->setDisabled(false);
	m_LineSCCurrent->setDisabled(false);
	m_LineStart->setDisabled(false);
	m_LineStop->setDisabled(false);
	m_LineStep->setDisabled(false);
	m_LineStepTime->setDisabled(false);
}




