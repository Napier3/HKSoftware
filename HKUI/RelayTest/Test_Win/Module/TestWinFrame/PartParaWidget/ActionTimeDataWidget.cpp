#include "ActionTimeDataWidget.h"
#include "../ReportView/XLangResource_PowerTestWin.h"


ActionTimeDataWidget::ActionTimeDataWidget(QWidget *parent,bool bRefValueType)
	: QWidget(parent)
{
	m_bRefValueType = bRefValueType;
	InitUI();
}

ActionTimeDataWidget::~ActionTimeDataWidget()
{

}

void ActionTimeDataWidget::InitUI()
{
	QFont ft("Microsoft YaHei", 10);

	m_MainLayout = new QHBoxLayout;
	
	groupBoxBefore = new QGroupBox(/*tr("故障前状态")*/g_sLangTxt_Native_PreFaultSt);
	groupBoxBefore->setFont(ft);
	groupBoxAfter = new QGroupBox(/*tr("故障状态")*/g_sLangTxt_Native_FaultSt);
	groupBoxAfter->setFont(ft);

	QGridLayout *leftLayout = new QGridLayout;

	label_PreFaultVol = new QLabel;
	label_PreFaultVol->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_PreFaultVol->setFont(ft);
	label_PreFaultVol->setText(/*QObject::tr("电压(V):")*/g_sLangTxt_Native_Voltage+"(V):");
	leftLayout->addWidget(label_PreFaultVol,0,0);
	m_LinePreFaultVol = new QLineEdit;
	m_LinePreFaultVol->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LinePreFaultVol->setFont(ft);
	leftLayout->addWidget(m_LinePreFaultVol,0,1);

	label_PreFaultCur = new QLabel;
	label_PreFaultCur->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_PreFaultCur->setFont(ft);
	label_PreFaultCur->setText(/*QObject::tr("电流(A):")*/g_sLangTxt_Native_Current+"(A):");
	leftLayout->addWidget(label_PreFaultCur,1,0);
	m_LinePreFaultCur = new QLineEdit;
	m_LinePreFaultCur->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LinePreFaultCur->setFont(ft);
	leftLayout->addWidget(m_LinePreFaultCur,1,1);

	label_PreFaultAngle = new QLabel;
	label_PreFaultAngle->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_PreFaultAngle->setFont(ft);
	label_PreFaultAngle->setText(/*QObject::tr("相位差(°):")*/g_sLangTxt_Gradient_Phase+"(°):");
	leftLayout->addWidget(label_PreFaultAngle,2,0);
	m_LinePreFaultAngle = new QLineEdit;
	m_LinePreFaultAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LinePreFaultAngle->setFont(ft);
	leftLayout->addWidget(m_LinePreFaultAngle,2,1);

	label_Freq = new QLabel;
	label_Freq->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_Freq->setFont(ft);
	label_Freq->setText(/*QObject::tr("频率:")*/g_sLangTxt_Native_Freq+":");
	leftLayout->addWidget(label_Freq,3,0);
	m_LineFreq = new QLineEdit;
	m_LineFreq->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineFreq->setFont(ft);
	leftLayout->addWidget(m_LineFreq,3,1);
	
	groupBoxBefore->setLayout(leftLayout);

	QGridLayout *rightLayout = new QGridLayout;

	label_FaultVol = new QLabel;
	label_FaultVol->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_FaultVol->setFont(ft);
	label_FaultVol->setText(/*QObject::tr("短路电压(V):")*/g_sLangTxt_State_ShortU);
	rightLayout->addWidget(label_FaultVol,0,0);
	m_LineFaultVol = new QLineEdit;
	m_LineFaultVol->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineFaultVol->setFont(ft);
	rightLayout->addWidget(m_LineFaultVol,0,1);
	m_CmbFaultVolType = new QComboBox;
	m_CmbFaultVolType->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	strListFaultVol<</*tr("短路电压")*/g_sLangTxt_Native_ShortCircuitV<</*tr("负序(U2)")*/(g_sLangTxt_Native_NegativeSeq+"(U2)")<</*tr("零序(3U0)")*/(g_sLangTxt_Native_ZeroSeq+"(3U0)");
	m_CmbFaultVolType->addItems(strListFaultVol);
	m_CmbFaultVolType->setFont(ft);
	rightLayout->addWidget(m_CmbFaultVolType,0,2);

	label_FaultCur = new QLabel;
	label_FaultCur->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_FaultCur->setFont(ft);
	if (m_bRefValueType)
	{
		label_FaultCur->setText(/*QObject::tr("电流(A):")*/g_sLangTxt_Native_Current+"(A):");
	}
	else
	{
		label_FaultCur->setText(/*QObject::tr("电流(I*):")*/g_sLangTxt_Native_Current+"(I*):");
	}
	rightLayout->addWidget(label_FaultCur,1,0);
	m_LineFaultCur = new QLineEdit;
	m_LineFaultCur->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineFaultCur->setFont(ft);
	rightLayout->addWidget(m_LineFaultCur,1,1);

	label_FaultVolType = new QLabel;
	label_FaultVolType->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_FaultVolType->setFont(ft);
	label_FaultVolType->setText(/*QObject::tr("故障类型:")*/g_sLangTxt_State_FaultType);
	rightLayout->addWidget(label_FaultVolType,2,0);
	m_CmbFaultType = new QComboBox;
	m_CmbFaultType->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	strListFaultVolType<</*tr("A相接地")*/g_sLangTxt_Native_GndA<</*tr("B相接地")*/g_sLangTxt_Native_GndB<</*tr("C相接地")*/g_sLangTxt_Native_GndC<</*tr("AB短路")*/g_sLangTxt_Native_ShortAB<</*tr("BC短路")*/g_sLangTxt_Native_ShortBC<</*tr("CA短路")*/g_sLangTxt_Native_ShortCA<</*tr("ABC短路")*/g_sLangTxt_Native_ABCSC<<tr("3I0")<<tr("I2")<<tr("Ia+Ib+Ic")<<tr("Ua,Ia");
	m_CmbFaultType->addItems(strListFaultVolType);
	m_CmbFaultType->setFont(ft);
	rightLayout->addWidget(m_CmbFaultType,2,1);

// 	label_RefValueType = new QLabel;
// 	label_RefValueType->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
// 	label_RefValueType->setFont(ft);
// 	label_RefValueType->setText(QObject::tr("基准值:"));
// 	rightLayout->addWidget(label_RefValueType,3,0);
// 	m_CmbRefValueType = new QComboBox;
// 	m_CmbRefValueType->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
// 	strListRefValueType<<tr("In")<<tr("Iset1")<<tr("Iset2")<<tr("Iset3")<<tr("In*Ip");
// 	m_CmbRefValueType->addItems(strListRefValueType);
// 	m_CmbRefValueType->setFixedHeight(nHeight);
// 	m_CmbRefValueType->setFont(ft);
// 	m_CmbRefValueType->setDisabled(m_bRefValueType);
// 	rightLayout->addWidget(m_CmbRefValueType,3,1);

	label_FaultAngle = new QLabel;
	label_FaultAngle->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_FaultAngle->setFont(ft);
	label_FaultAngle->setText(/*QObject::tr("相位差(°):")*/g_sLangTxt_Gradient_Phase+"(°):");
	rightLayout->addWidget(label_FaultAngle,3,0);
	m_LineFaultAngle = new QLineEdit;
	m_LineFaultAngle->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineFaultAngle->setFont(ft);
	rightLayout->addWidget(m_LineFaultAngle,3,1);

	label_SettingFaultTime = new QLabel;
	label_SettingFaultTime->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
	label_SettingFaultTime->setFont(ft);
	label_SettingFaultTime->setText(/*QObject::tr("动作时间定值(s):")*/g_sLangTxt_Native_OpTimeSet+"(s):");
	rightLayout->addWidget(label_SettingFaultTime,4,0);
	m_LineSettingFaultTime = new QLineEdit;
	m_LineSettingFaultTime->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
	m_LineSettingFaultTime->setFont(ft);
	rightLayout->addWidget(m_LineSettingFaultTime,4,1);

	groupBoxAfter->setLayout(rightLayout);
	
	pSpacer1 = new QSpacerItem(30,20,QSizePolicy::Maximum,QSizePolicy::Maximum);
	pSpacer2 = new QSpacerItem(30,20,QSizePolicy::Maximum,QSizePolicy::Maximum);
	pSpacer3 = new QSpacerItem(30,20,QSizePolicy::Maximum,QSizePolicy::Maximum);

	m_MainLayout->addSpacerItem(pSpacer1);
	m_MainLayout->addWidget(groupBoxBefore);
	m_MainLayout->addSpacerItem(pSpacer2);
	m_MainLayout->addWidget(groupBoxAfter);
	m_MainLayout->addSpacerItem(pSpacer3);

	setLayout(m_MainLayout);

	connect(m_LinePreFaultVol,SIGNAL(editingFinished()),this,SLOT(slot_PreFaultVol_editingFinished()));
	connect(m_LinePreFaultCur,SIGNAL(editingFinished()),this,SLOT(slot_PreFaultCur_editingFinished()));
	connect(m_LinePreFaultAngle,SIGNAL(editingFinished()),this,SLOT(slot_PreFaultAngle_editingFinished()));
	connect(m_LineFaultVol,SIGNAL(editingFinished()),this,SLOT(slot_FaultVol_editingFinished()));
	connect(m_LineFaultCur,SIGNAL(editingFinished()),this,SLOT(slot_FaultCur_editingFinished()));
	connect(m_LineFaultAngle,SIGNAL(editingFinished()),this,SLOT(slot_FaultAngle_editingFinished()));
	connect(m_LineSettingFaultTime,SIGNAL(editingFinished()),this,SLOT(slot_SettingFaultTime_editingFinished()));

	connect(m_CmbFaultVolType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultVolTypeCurrentIndexChanged(int)));
	connect(m_CmbFaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTypeCurrentIndexChanged(int)));
}

void ActionTimeDataWidget::setData( PTMT_PARAS_HEAD pCurr )
{
	ASSERT(pCurr);
	m_ActionTimeTest = (tmt_CurrInverseTimeTest*)pCurr;
	m_ActionTimeParas = &m_ActionTimeTest->m_oActionTimeParas;
	m_ActionTimeResults = &m_ActionTimeTest->m_oActionTimeResults;

	InitData();
}

void ActionTimeDataWidget::InitData()
{
	disconnect(m_CmbFaultVolType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultVolTypeCurrentIndexChanged(int)));
	disconnect(m_CmbFaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTypeCurrentIndexChanged(int)));

	m_LinePreFaultVol->setText(QString::number(m_ActionTimeParas->m_fPreFaultVol, 'f', 3));
	m_LinePreFaultCur->setText(QString::number(m_ActionTimeParas->m_fPreFaultCur, 'f', 3));

	if (m_bRefValueType)
	{
		m_LinePreFaultAngle->setText(m_ActionTimeParas->m_pszPreFaultAngle);
	}
	else
	{
		m_LinePreFaultAngle->setText(QString::number(m_ActionTimeParas->m_fPreFaultAngle, 'f', 3));
	}
	
	m_LineFreq->setText(QString::number(g_oSystemParas.m_fFNom, 'f', 3));
	m_LineFreq->setDisabled(true);

	if (m_bRefValueType)
	{
		m_LineFaultVol->setText(m_ActionTimeParas->m_pszFaultVol);
	}
	else
	{
		m_LineFaultVol->setText(QString::number(m_ActionTimeParas->m_fFaultVol, 'f', 3));
	}

	if (m_bRefValueType)
	{
		m_LineFaultCur->setText(m_ActionTimeParas->m_pszFaultCur);
	}
	else
	{
		m_LineFaultCur->setText(QString::number(m_ActionTimeParas->m_fFaultCur, 'f', 3));
	}

	m_CmbFaultType->setCurrentIndex(m_ActionTimeParas->m_nFaultType);
	SetFaultData(m_ActionTimeParas->m_nFaultType);

	if (m_bRefValueType)
	{
		m_LineFaultAngle->setText(m_ActionTimeParas->m_pszFaultAngle);
		m_LineSettingFaultTime->setText(m_ActionTimeParas->m_pszSettingFaultTime);
	}
	else
	{
		m_LineFaultAngle->setText(QString::number(m_ActionTimeParas->m_fFaultAngle, 'f', 3));
		m_LineSettingFaultTime->setText(QString::number(m_ActionTimeParas->m_fSettingFaultTime, 'f', 3));
	}

	m_LinePreFaultVol->setCursorPosition(0);
	m_LinePreFaultCur->setCursorPosition(0);
	m_LinePreFaultAngle->setCursorPosition(0);
	m_LineFreq->setCursorPosition(0);
	m_LineFaultVol->setCursorPosition(0);
	m_LineFaultCur->setCursorPosition(0);
	m_LineFreq->setCursorPosition(0);
	m_LineFaultAngle->setCursorPosition(0);
	m_LineSettingFaultTime->setCursorPosition(0);

	connect(m_CmbFaultVolType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultVolTypeCurrentIndexChanged(int)));
	connect(m_CmbFaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTypeCurrentIndexChanged(int)));
}

void ActionTimeDataWidget::slot_FaultVolTypeCurrentIndexChanged( int nIndex)
{
	disconnect(m_CmbFaultVolType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultVolTypeCurrentIndexChanged(int)));
	disconnect(m_CmbFaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTypeCurrentIndexChanged(int)));

	g_theSttXTestMngrBaseApp->SetModifyPara();
 	int faulttypeIndex = m_CmbFaultType->currentIndex();
 	
  	if (faulttypeIndex <= 2)
  	{
  		if (nIndex == 1)
  		{
  			nIndex = 3;
  		}
  	}
  	else if (faulttypeIndex <= 5)
  	{
		if (nIndex == 1)
		{
			nIndex = 2;
		}
  	}

	m_ActionTimeParas->m_nFaultVolType = nIndex;

	//m_CmbFaultVolType->setCurrentIndex(nIndex);

	if (nIndex ==0)
	{
		label_FaultVol->setText(/*tr("短路电压:")*/g_sLangTxt_Native_ShortCircuitV+":");
	}
// 	else if (nIndex ==1)
// 	{
// 		label_FaultVol->setText(tr("正序(U1)"));
// 	}
	else if (nIndex ==2)
	{
		label_FaultVol->setText(/*tr("负序(U2):")*/g_sLangTxt_Native_NegativeSeq+"(U2):");
	}
	else if (nIndex ==3)
	{
		label_FaultVol->setText(/*tr("零序(3U0):")*/g_sLangTxt_Native_ZeroSeq+"(3U0):");
	}
	connect(m_CmbFaultVolType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultVolTypeCurrentIndexChanged(int)));
	connect(m_CmbFaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTypeCurrentIndexChanged(int)));
}


void ActionTimeDataWidget::slot_FaultTypeCurrentIndexChanged( int nIndex)
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	disconnect(m_CmbFaultVolType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultVolTypeCurrentIndexChanged(int)));
	disconnect(m_CmbFaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTypeCurrentIndexChanged(int)));

	int nCurrSelect = SetFaultData(nIndex);

	m_ActionTimeParas->m_nFaultType = nIndex;

	connect(m_CmbFaultVolType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultVolTypeCurrentIndexChanged(int)));
	connect(m_CmbFaultType,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_FaultTypeCurrentIndexChanged(int)));

	emit sig_FaultTypeChange();
}
int ActionTimeDataWidget::SetFaultData(int nData)
{
	strListFaultVol.clear();

	int nCurrSelect;
	switch(nData)
	{
	case 0:
	case 1:
	case 2:
		{
			strListFaultVol<</*tr("短路电压")*/g_sLangTxt_Native_ShortCircuitV<</*tr("零序(3U0)")*/(g_sLangTxt_Native_ZeroSeq+"(3U0)");
			m_CmbFaultVolType->setDisabled(false);
			m_LinePreFaultVol->setDisabled(false);
			m_LinePreFaultAngle->setDisabled(false);
			m_LineFaultVol->setDisabled(false);
			m_LineFaultAngle->setDisabled(false);

			if (m_ActionTimeParas->m_nFaultVolType != 3)
			{
				label_FaultVol->setText(/*tr("短路电压:")*/g_sLangTxt_Native_ShortCircuitV+":");
				m_ActionTimeParas->m_nFaultVolType = 0;
				nCurrSelect = 0;
			}
			else
			{
				nCurrSelect = 1;
				label_FaultVol->setText(/*tr("零序(3U0):")*/g_sLangTxt_Native_ZeroSeq+"(3U0):");
			}
		}break;
	case 3:
	case 4:
	case 5:
		{
			strListFaultVol<</*tr("短路电压")*/g_sLangTxt_Native_ShortCircuitV<</*tr("负序(U2)")*/(g_sLangTxt_Native_NegativeSeq+"(U2)");
			m_CmbFaultVolType->setDisabled(false);
			m_LinePreFaultVol->setDisabled(false);
			m_LinePreFaultAngle->setDisabled(false);
			m_LineFaultVol->setDisabled(false);
			m_LineFaultAngle->setDisabled(false);
			if (m_ActionTimeParas->m_nFaultVolType != 2)
			{
				label_FaultVol->setText(/*tr("短路电压:")*/g_sLangTxt_Native_ShortCircuitV+":");
				m_ActionTimeParas->m_nFaultVolType = 0;
				nCurrSelect = 0;
			}
			else
			{
				nCurrSelect = 1;
				label_FaultVol->setText(/*tr("负序(U2):")*/g_sLangTxt_Native_NegativeSeq+"(U2):");
			}
		}break;
	case 6:
	case 7:
	case 8:
	case 10:
		{
			strListFaultVol<</*tr("短路电压")*/g_sLangTxt_Native_ShortCircuitV;
			m_CmbFaultVolType->setDisabled(true);
			m_LinePreFaultVol->setDisabled(false);
			m_LinePreFaultAngle->setDisabled(false);
			m_LineFaultVol->setDisabled(false);
			m_LineFaultAngle->setDisabled(false);
			m_ActionTimeParas->m_nFaultVolType = 0;
			nCurrSelect = 0;
			label_FaultVol->setText(/*tr("短路电压:")*/g_sLangTxt_Native_ShortCircuitV+":");
		}break;
	case 9:
		{
			strListFaultVol<</*tr("短路电压")*/g_sLangTxt_Native_ShortCircuitV;
			m_CmbFaultVolType->setDisabled(true);
			m_LinePreFaultVol->setDisabled(true);
			m_LinePreFaultAngle->setDisabled(true);
			m_LineFaultVol->setDisabled(true);
			m_LineFaultAngle->setDisabled(true);
			m_ActionTimeParas->m_nFaultVolType = 0;
			nCurrSelect = 0;
			label_FaultVol->setText(/*tr("短路电压:")*/g_sLangTxt_Native_ShortCircuitV+":");
		}break;
	}

	m_CmbFaultVolType->clear();
	m_CmbFaultVolType->addItems(strListFaultVol);
	m_CmbFaultVolType->setCurrentIndex(nCurrSelect);

	return nCurrSelect;
}
void ActionTimeDataWidget::slot_PreFaultVol_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	float fv = m_LinePreFaultVol->text().toFloat();
	float fmax = g_oLocalSysPara.m_fAC_VolMax;//不知道电压最大值是多少,先写999.999
	fv = setLimit(0,fmax,fv);

	m_ActionTimeParas->m_fPreFaultVol = fv;

	m_LinePreFaultVol->setText(QString::number(fv,'f',3));

	m_LinePreFaultVol->setCursorPosition(0);
}

void ActionTimeDataWidget::slot_PreFaultCur_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	float fv = m_LinePreFaultCur->text().toFloat();
	float fmax;
	if (m_CmbFaultType->currentIndex() == 9)
	{
		fmax = g_oLocalSysPara.m_fAC_CurMax *3;
	}
	else
	{
		fmax = g_oLocalSysPara.m_fAC_CurMax;
	}
	fv = setLimit(0,fmax,fv);

	m_ActionTimeParas->m_fPreFaultCur = fv;

	m_LinePreFaultCur->setText(QString::number(fv,'f',3));

	m_LinePreFaultCur->setCursorPosition(0);
}

void ActionTimeDataWidget::slot_PreFaultAngle_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	if (m_bRefValueType)
	{
		QString strExpr = m_LinePreFaultAngle->text();
		bool bOK = false;
		double lfv;
		float fv;
		bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
		fv = lfv;

		if (!bOK)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
			m_LinePreFaultAngle->setText(m_ActionTimeParas->m_pszPreFaultAngle);
		}
		else
		{
			if (fv > 360 || fv < -360)
			{
				CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式超出范围")*/g_sLangTxt_Native_ExprOutOfRange.GetString());
			}
			fv = setAngleLimitEx(fv);
			m_ActionTimeParas->m_fPreFaultAngle = fv;
			CString strTemp = strExpr;
			CString_to_char(strTemp,m_ActionTimeParas->m_pszPreFaultAngle);

			if(isFloat(m_ActionTimeParas->m_pszPreFaultAngle))
			{
				m_LinePreFaultAngle->setText(QString::number(fv,'f',1));
			}
			else
			{
				m_LinePreFaultAngle->setText(m_ActionTimeParas->m_pszPreFaultAngle);
			}
			//m_LinePreFaultAngle->setText(m_ActionTimeParas->m_pszPreFaultAngle);
			//m_LinePreFaultAngle->setText(QString::number(fv,'f',1));
		}

	}
	else
	{
		float fv = m_LinePreFaultAngle->text().toFloat();

		fv = setAngleLimitEx(fv);

		m_ActionTimeParas->m_fPreFaultAngle = fv;

		m_LinePreFaultAngle->setText(QString::number(fv,'f',3));
	}

	m_LinePreFaultCur->setCursorPosition(0);
}

void ActionTimeDataWidget::slot_FaultVol_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	float fmax;			

	fmax = 130/*g_oLocalSysPara.m_fAC_VolMax*/;

	if (m_bRefValueType)
	{
		QString strExpr = m_LineFaultVol->text();
		bool bOK = false;
		double lfv;
		float fv;
		bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
		fv = lfv;

		if (!bOK)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
			m_LineFaultVol->setText(m_ActionTimeParas->m_pszFaultVol);
		}
		else
		{
			if (fv != setLimit(0,fmax,fv))
			{
				CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("超出范围")*/g_sLangTxt_Native_OutOfRange.GetString());
				m_LineFaultVol->setText(m_ActionTimeParas->m_pszFaultVol);
			}
			else
			{
				m_ActionTimeParas->m_fFaultVol = fv;
				CString strTemp = strExpr;
				CString_to_char(strTemp,m_ActionTimeParas->m_pszFaultVol);

				if(isFloat(m_ActionTimeParas->m_pszFaultVol))
				{
					m_LineFaultVol->setText(QString::number(fv,'f',3));
				}
				else
				{
					m_LineFaultVol->setText(m_ActionTimeParas->m_pszFaultVol);
				}
				//m_LineFaultVol->setText(m_ActionTimeParas->m_pszFaultVol);
				//m_LineFaultVol->setText(QString::number(fv,'f',3));
			}
		}
	}
	else
	{
		float fv = m_LineFaultVol->text().toFloat();

		fv = setLimit(0,fmax,fv);

		m_ActionTimeParas->m_fFaultVol = fv;

		m_LineFaultVol->setText(QString::number(fv,'f',3));
	}
	
	m_LineFaultVol->setCursorPosition(0);
}

void ActionTimeDataWidget::slot_FaultCur_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	float fmax;
	if (m_CmbFaultType->currentIndex() == 9)
	{
		fmax = g_oLocalSysPara.m_fAC_CurMax * 3;
	}
	else
	{
		fmax = g_oLocalSysPara.m_fAC_CurMax;
	}

	if (m_bRefValueType)
	{
		QString strExpr = m_LineFaultCur->text();
		bool bOK = false;
		double lfv;
		float fv;
		bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
		fv = lfv;

		if (!bOK)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
			m_LineFaultCur->setText(m_ActionTimeParas->m_pszFaultCur);
		}
		else
		{
			if (fv != setLimit(0,fmax,fv))
			{
				CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("超出范围")*/g_sLangTxt_Native_OutOfRange.GetString());
				m_LineFaultCur->setText(m_ActionTimeParas->m_pszFaultCur);
			}
			else
			{
				m_ActionTimeParas->m_fFaultCur = fv;
				CString strTemp = strExpr;
				CString_to_char(strTemp,m_ActionTimeParas->m_pszFaultCur);

				if(isFloat(m_ActionTimeParas->m_pszFaultCur))
				{
					m_LineFaultCur->setText(QString::number(fv,'f',3));
				}
				else
				{
					m_LineFaultCur->setText(m_ActionTimeParas->m_pszFaultCur);
				}
				//m_LineFaultCur->setText(m_ActionTimeParas->m_pszFaultCur);
				//m_LineFaultCur->setText(QString::number(fv,'f',3));
			}
		}
	}
	else
	{
		float fv = m_LineFaultCur->text().toFloat();

		fv = setLimit(0,fmax,fv);

		m_ActionTimeParas->m_fFaultCur = fv;

		m_LineFaultCur->setText(QString::number(fv,'f',3));
	}

	m_LineFaultCur->setCursorPosition(0);
	
	emit sig_FaultCurChange();
}

void ActionTimeDataWidget::slot_FaultAngle_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	if (m_bRefValueType)
	{
		QString strExpr = m_LineFaultAngle->text();
		bool bOK = false;
		double lfv;
		float fv;
		bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
		fv = lfv;

		if (!bOK)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
			m_LineFaultAngle->setText(m_ActionTimeParas->m_pszFaultAngle);
		}
		else
		{
			if (fv > 360 || fv < -360)
			{
				CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式超出范围")*/g_sLangTxt_Native_ExprOutOfRange.GetString());
			}

			fv = setAngleLimitEx(fv);
			m_ActionTimeParas->m_fFaultAngle = fv;
			CString strTemp = strExpr;
			CString_to_char(strTemp,m_ActionTimeParas->m_pszFaultAngle);

			if(isFloat(m_ActionTimeParas->m_pszFaultAngle))
			{
				m_LineFaultAngle->setText(QString::number(fv,'f',1));
			}
			else
			{
				m_LineFaultAngle->setText(m_ActionTimeParas->m_pszFaultAngle);
			}
			//m_LineFaultAngle->setText(m_ActionTimeParas->m_pszFaultAngle);
			//m_LineFaultAngle->setText(QString::number(fv,'f',1));
		}
	}
	else
	{
		float fv = m_LineFaultAngle->text().toFloat();

		fv = setAngleLimitEx(fv);

		m_ActionTimeParas->m_fFaultAngle = fv;

		m_LineFaultAngle->setText(QString::number(fv,'f',3));
	}

	m_LineFaultAngle->setCursorPosition(0);
}

void ActionTimeDataWidget::slot_SettingFaultTime_editingFinished()
{
	g_theSttXTestMngrBaseApp->SetModifyPara();
	if (m_bRefValueType)
	{
		QString strExpr = m_LineSettingFaultTime->text();
		bool bOK = false;
		double lfv;
		float fv;
		bOK = g_oTmtTestRsltExprImp.CalParaExpression(strExpr,lfv);
		fv = lfv;

		if (!bOK)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR,/*_T("表达式输入错误")*/g_sLangTxt_Native_ExprInputErr.GetString());
			m_LineSettingFaultTime->setText(m_ActionTimeParas->m_pszSettingFaultTime);
		}
		else
		{
			fv = setLimit(0,999.999,fv);
			m_ActionTimeParas->m_fSettingFaultTime = fv;
			CString strTemp = strExpr;
			CString_to_char(strTemp,m_ActionTimeParas->m_pszSettingFaultTime);

			if(isFloat(m_ActionTimeParas->m_pszSettingFaultTime))
			{
				m_LineSettingFaultTime->setText(QString::number(fv,'f',3));
			}
			else
			{
				m_LineSettingFaultTime->setText(m_ActionTimeParas->m_pszSettingFaultTime);
			}
			//m_LineSettingFaultTime->setText(m_ActionTimeParas->m_pszSettingFaultTime);
			//m_LineSettingFaultTime->setText(QString::number(fv,'f',3));
		}
	}
	else
	{
		float fv = m_LineSettingFaultTime->text().toFloat();

		fv = setLimit(0,999.999,fv);

		m_ActionTimeParas->m_fSettingFaultTime = fv;
		m_LineSettingFaultTime->setText(QString::number(fv,'f',3));
	}

	m_LineSettingFaultTime->setCursorPosition(0);

	emit sig_SettingFaultTimeChanged();
}

BOOL ActionTimeDataWidget::isFloat(char* pszExpr)
{
	BOOL bIsFloat = TRUE;
	long nSignalCount = 0;           
	long nDotCount = 0;              
	long nLen = strlen(pszExpr);
	long nIndex = 0;

	for(nIndex=0; nIndex < nLen; ++nIndex)
	{
		if(!((pszExpr[nIndex] >= '0') && (pszExpr[nIndex] <= '9')))
		{
			if(pszExpr[0] == '-')
			{
				nSignalCount++;
			}
			else if (pszExpr[nIndex] == '.')
			{
				nDotCount++;
			}
			else
			{
				bIsFloat = FALSE;
			}			
		}
	}

	if (nSignalCount > 1 || nDotCount > 1 )
	{
		bIsFloat = FALSE;
	}

	return bIsFloat;
}

void ActionTimeDataWidget::UpdateActTime()
{
	m_LineFaultCur->setText(QString::number(m_ActionTimeParas->m_fFaultCur, 'f', 3));
	m_LineSettingFaultTime->setText(QString::number(m_ActionTimeParas->m_fSettingFaultTime, 'f', 3));
}

void ActionTimeDataWidget::startInit()
{
	m_LinePreFaultVol->setDisabled(true);
	m_LinePreFaultCur->setDisabled(true);
	m_LinePreFaultAngle->setDisabled(true);
	m_LineFaultVol->setDisabled(true);
	m_CmbFaultVolType->setDisabled(true);
	m_LineFaultCur->setDisabled(true);
	m_CmbFaultType->setDisabled(true);
	m_LineFaultAngle->setDisabled(true);
	m_LineSettingFaultTime->setDisabled(true);
}

void ActionTimeDataWidget::stopInit()
{
	m_LinePreFaultCur->setDisabled(false);
	m_LineFaultCur->setDisabled(false);
	m_CmbFaultType->setDisabled(false);
	m_LineSettingFaultTime->setDisabled(false);

	int nIndex = m_CmbFaultType->currentIndex();

	if (nIndex == 6 ||nIndex == 7 || nIndex == 8 ||nIndex == 9||nIndex == 10)
	{
		m_CmbFaultVolType->setDisabled(true);		
	}
	else 
	{
		m_CmbFaultVolType->setDisabled(false);
	}
	if (nIndex == 9)
	{
		m_LinePreFaultVol->setDisabled(true);
		m_LinePreFaultAngle->setDisabled(true);
		m_LineFaultVol->setDisabled(true);
		m_LineFaultAngle->setDisabled(true);
	}
	else 
	{
		m_LinePreFaultVol->setDisabled(false);
		m_LinePreFaultAngle->setDisabled(false);
		m_LineFaultVol->setDisabled(false);
		m_LineFaultAngle->setDisabled(false);
	}
}
