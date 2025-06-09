#include "GradientSetDlg.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../Module/UI/Controls/SttLineEdit.h"
#include "../../SttTestCntrFrameApi.h"
#include <QApplication>

GradientSetDlg::GradientSetDlg(QWidget *pParent)
:QDialog(pParent), ui(new Ui::GradientSetDlg)
{
	ui->setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);

	m_pParaTab = NULL;
	m_plblStepTime = NULL;
	m_pedtStepTime = NULL;
	m_pbtnLinear = NULL;
	m_pbtnStep = NULL;
	m_pbtnOK = NULL;
	m_pbtnCancel = NULL;
	m_pStatePara = NULL;
	m_pMainLayout = NULL;
	m_pStatePara = NULL;
	m_nIsOK = 0;
	
// 	QDesktopWidget *pDeskTop = QApplication::desktop();
// 	QRect rcScreen = pDeskTop->screenGeometry();
// 	m_nScreenWidth = rcScreen.width();
// 	m_nScreenHeight = rcScreen.height();

	initUI(); 
	initConnections();
	SetGradientParaFont();
}

GradientSetDlg::~GradientSetDlg()
{

}
void GradientSetDlg::SetGradientParaFont()
{
	m_pbtnCancel->setFont(*g_pSttGlobalFont);
	m_pbtnOK->setFont(*g_pSttGlobalFont);
	m_pbtnLinear->setFont(*g_pSttGlobalFont);
	m_pbtnStep->setFont(*g_pSttGlobalFont);
	m_pedtStepTime->setFont(*g_pSttGlobalFont);
	m_plblStepTime->setFont(*g_pSttGlobalFont);

}
void GradientSetDlg::initUI()
{
	m_pParaTab =  new GradientParaTab(this);
	
	AddRadioButton(&m_pbtnLinear,tr("线性变化"),16);
	AddRadioButton(&m_pbtnStep,tr("阶梯变化"),16);
	AddLabel(&m_plblStepTime,tr("步长时间(s)"),16);
	m_pedtStepTime = new QSttLineEdit(this);
	AddPushButton(&m_pbtnOK,tr("确定"),16);
	AddPushButton(&m_pbtnCancel,tr("取消"),16);

	resize(1010,600);
	this->setFixedWidth(1010/*stt_FrameTestCntrFrameWidth()*/);
	this->setFixedHeight(600/*stt_FrameTestCntrFrameHeight()*/);
//	setMaximumSize(1010, 600);
	
	xlang_SetLangStrToWidget(m_pbtnLinear, "State_LinearChange", XLang_Ctrls_QRadioButton);
	xlang_SetLangStrToWidget(m_pbtnStep, "State_StepChange", XLang_Ctrls_QRadioButton);
	xlang_SetLangStrToWidget(m_plblStepTime, "State_StepTime", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(m_pbtnOK, "sOK", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(m_pbtnCancel, "sCancel", XLang_Ctrls_QPushButton);
	


	if (m_pMainLayout == NULL)
	{
		QHBoxLayout *pHLay = new QHBoxLayout;
		pHLay->addWidget(m_pbtnLinear);
		pHLay->addWidget(m_pbtnStep);
		pHLay->addWidget(m_plblStepTime);
		pHLay->addWidget(m_pedtStepTime);
		pHLay->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding));
		pHLay->addWidget(m_pbtnOK);
		pHLay->addWidget(m_pbtnCancel);

		m_pParaTab->initUI();

		m_pMainLayout = new QVBoxLayout;
		m_pMainLayout->addWidget(m_pParaTab);
		m_pMainLayout->addLayout(pHLay);	

		setLayout(m_pMainLayout); 
	}

//	setWindowTitle(tr("递变设置"));

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"State_GradientSet");
	setWindowTitle(strTitle);

// 	QFont font = this->font();
// 	font.setPointSize(20);
// 	this->setFont(font);

// 	Qt::WindowFlags flags= this->windowFlags();
// 	setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);
}

void GradientSetDlg::AddPushButton(QPushButton** ppBtn,QString strName,int nFontSize)
{
	(*ppBtn) = new QPushButton(strName);
	(*ppBtn)->setFixedWidth(80);
	QFont font = (*ppBtn)->font();
	font.setPixelSize(nFontSize);
	(*ppBtn)->setFont(font);
}

void GradientSetDlg::AddRadioButton(QRadioButton** ppBtn,QString strName,int nFontSize)
{
	(*ppBtn) = new QRadioButton(strName);
	QFont font = (*ppBtn)->font();
	font.setPixelSize(nFontSize);
	(*ppBtn)->setFont(font);
}

void GradientSetDlg::AddLabel(QLabel** ppLabel,QString strName,int nFontSize)
{
	(*ppLabel) = new QLabel(strName);
	QFont font = (*ppLabel)->font();
	font.setPixelSize(nFontSize);
	(*ppLabel)->setFont(font);
}

void GradientSetDlg::setData(CSttTestResourceBase *pSttTestResource,tmt_StatePara* pStatePara)
{ 
	ASSERT(pSttTestResource != NULL && pStatePara != NULL);
	m_pStatePara = pStatePara;

    long maxCount = pSttTestResource->m_oVolChRsListRef.GetCount();
    long nCount2 = pSttTestResource->m_oCurChRsListRef.GetCount();

    if (nCount2 > maxCount)
    {
        maxCount = nCount2;
    }

// #ifdef _PSX_QT_LINUX_
// 	int height = maxCount*45+150; 
// 	resize( QSize( 1020, height ));
// #else
// 	int height = maxCount*60+200; 
// 	resize( QSize( 1120, height ));
// #endif

	copyTmpStatePara();

	m_pParaTab->setData(pSttTestResource,&m_tmpStatePara);
	
	if(m_pStatePara->m_nRampTimeGrad>1) 
	{
		setGradientType(GRADIENT_TYPE_Step);
	}
	else
	{
		setGradientType(GRADIENT_TYPE_Linear);
	}
}

void GradientSetDlg::copyTmpStatePara(bool b)
{
	if(b)
	{
		memcpy(&m_tmpStatePara,m_pStatePara,sizeof(tmt_StatePara));
	}
	else
	{
		memcpy(m_pStatePara,&m_tmpStatePara,sizeof(tmt_StatePara));
	}
}

void GradientSetDlg::updateGradientType(int nType)
{
	m_pParaTab->updateGradientType(nType);
}

void GradientSetDlg::initConnections()
{
	connect(m_pbtnLinear, SIGNAL(clicked()), this, SLOT(slot_GradientLinearClicked()));
	connect(m_pbtnStep, SIGNAL(clicked()), this, SLOT(slot_GradientStepClicked()));
	connect(m_pedtStepTime, SIGNAL(editingFinished()), this, SLOT(slot_StepTimeKeyBoard()));
	connect(m_pbtnOK, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pParaTab, SIGNAL(sig_TabPageChanged(int)), this, SLOT(slot_TabPageChanged(int)));
#ifdef _PSX_QT_LINUX_
	connect(m_pedtStepTime, SIGNAL(clicked()), this, SLOT(slot_StepTimeChanged()));
#endif

}

void GradientSetDlg::setGradientType(int nType)
{
	if (nType == GRADIENT_TYPE_Linear)
	{
		m_pbtnLinear->setChecked(true);
		m_pbtnStep->setChecked(false);

		m_pStatePara->m_nRampTimeGrad = 1;
		m_plblStepTime->hide();
		m_pedtStepTime->hide();
	}
	else if (nType == GRADIENT_TYPE_Step)
	{
		m_pbtnLinear->setChecked(false);
		m_pbtnStep->setChecked(true);

		if (m_pStatePara->m_nRampTimeGrad <= 1)
		{
			m_pStatePara->m_nRampTimeGrad = 2;
		}

		m_plblStepTime->show();
		m_pedtStepTime->show();
		m_pedtStepTime->setText(QString::number((float)m_pStatePara->m_nRampTimeGrad/1000,'f',3));
		m_pedtStepTime->setDisabled(false);
	}
}

void GradientSetDlg::slot_GradientLinearClicked()
{
	saveTmpData();
	setGradientType(GRADIENT_TYPE_Linear);
	m_pParaTab->InitLinearStepGradient();
	updateGradientType(GRADIENT_TYPE_Linear);
}

void GradientSetDlg::slot_GradientStepClicked()
{
	saveTmpData();
	setGradientType(GRADIENT_TYPE_Step);
	m_pParaTab->InitLinearStepGradient();
	updateGradientType(GRADIENT_TYPE_Step);
}

void GradientSetDlg::slot_StepTimeChanged()
{
//	disconnect(m_pedtStepTime,SIGNAL(editingFinished()),this,SLOT(slot_StepTimeChanged()));

	QString str = m_pedtStepTime->text();
    GetWidgetBoard_DigitData(4,str,m_pedtStepTime,stt_Frame_TestCtrlFrame());

// 	float fv = str.toFloat();
// 	fv = setLimit(0.001,999,fv);
// 	m_pedtStepTime->setText(QString::number(fv,'f',3));

//	connect(m_pedtStepTime,SIGNAL(editingFinished()),this,SLOT(slot_StepTimeChanged()));
}

void GradientSetDlg::slot_StepTimeKeyBoard()
{

	QString str = m_pedtStepTime->text();

	float fv = str.toFloat();
	fv = setLimit(0.001,999,fv);
	m_pedtStepTime->setText(QString::number(fv,'f',3));

}

void GradientSetDlg::saveTmpData()
{
	//保存参数
	m_pParaTab->saveData();

	//递变时间
	if (m_pbtnStep->isChecked())
	{
		QString str = m_pedtStepTime->text();
		float fv = str.toFloat();

		m_tmpStatePara.m_nRampTimeGrad = fv*1000;
	}
	else
	{
		m_tmpStatePara.m_nRampTimeGrad = 1;
	}
}

void GradientSetDlg::slot_OKClicked()
{
	ExitHideKeyboardWidget();
	saveTmpData();
	copyTmpStatePara(false);

	close();
	m_nIsOK = 1;
}

void GradientSetDlg::slot_CancelClicked()
{
	ExitHideKeyboardWidget();
	close();
	m_nIsOK = 2;
}

void GradientSetDlg::closeEvent(QCloseEvent *event)
{
	m_nIsOK = 2;
}
