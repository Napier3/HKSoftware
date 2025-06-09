#include "gradientparatab.h"
#include "gradientparaset.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
//#include "../../SttTestCntrFrameBase.h"
#include "../../Controls/SttTabWidget.h"
#include "../../Module/XLangResource_Native.h"

GradientParaTab::GradientParaTab(QWidget *parent)
	: QWidget(parent)
{
	m_AmpParaWidget = NULL;
	m_FreqParaWidget = NULL;
	m_pVBoxLayout = NULL;

	m_tabWidget = new QSttTabWidget(this);
	connect(m_tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slot_TabPageChanged(int)));

	initUI();
	
}

GradientParaTab::~GradientParaTab()
{
}

void GradientParaTab::initUI()
{
	int num = m_tabWidget->count();
	if (m_pVBoxLayout != NULL)
	{
		delete m_pVBoxLayout;
		m_pVBoxLayout = NULL;
	}

	if (m_AmpParaWidget != NULL)
	{
		delete m_AmpParaWidget;
		m_AmpParaWidget = NULL;
	}

	if (m_FreqParaWidget != NULL)
	{
		delete m_FreqParaWidget;
		m_FreqParaWidget = NULL;
	}
	
	m_tabWidget->clear();

	m_AmpParaWidget = new GradientParaSet();
	m_AmpParaWidget->m_nGradientObj = GRADIENT_AMP;
//	m_tabWidget->addTab(m_AmpParaWidget,tr("幅值递变"));

    CString strTitle;
	xlang_GetLangStrByFile(strTitle,"State_AmpGradient");
	m_tabWidget->addTab(m_AmpParaWidget,strTitle);

	m_FreqParaWidget = new GradientParaSet();
	m_FreqParaWidget->m_nGradientObj = GRADIENT_FRE;
//	m_tabWidget->addTab(m_FreqParaWidget,tr("频率递变"));

	xlang_GetLangStrByFile(strTitle,"State_FreqGradient");
	m_tabWidget->addTab(m_FreqParaWidget,strTitle);

// 	QFont font = m_tabWidget->font();
// 	font.setPointSize(20);
// 	m_tabWidget->setFont(font);

	m_tabWidget->setFont(*g_pSttGlobalFont);

	m_pVBoxLayout = new QVBoxLayout(this);
	m_pVBoxLayout->addWidget(m_tabWidget);
	m_pVBoxLayout->setMargin(0);
	m_pVBoxLayout->setSpacing(0);
	setLayout(m_pVBoxLayout);	
}

GradientParaSet* GradientParaTab::getAmpParaSet()
{
	return m_AmpParaWidget;
}

GradientParaSet* GradientParaTab::getFreqParaSet()
{
	return m_FreqParaWidget;
}

void GradientParaTab::setData(CSttTestResourceBase *pSttTestResource,tmt_StatePara* pStatePara)
{ 
	ASSERT(pSttTestResource != NULL && pStatePara != NULL);
	if (m_AmpParaWidget)
	{
		m_AmpParaWidget->setPropertyOfParaSet(pSttTestResource,pStatePara,GRADIENT_AMP);
		m_AmpParaWidget->setMaxMinVal();
	}

	if (m_FreqParaWidget)
	{
		m_FreqParaWidget->setPropertyOfParaSet(pSttTestResource,pStatePara,GRADIENT_FRE);
		m_FreqParaWidget->setMaxMinVal();
	}
}

void GradientParaTab::saveData()
{
	if (m_AmpParaWidget)
	{
		m_AmpParaWidget->saveData();
	}

	if (m_FreqParaWidget)
	{
		m_FreqParaWidget->saveData();
	}
}

void GradientParaTab::updateGradientType(int nType)
{
	if (m_AmpParaWidget)
	{
		m_AmpParaWidget->updateGradientType(nType);
	}

	if(m_FreqParaWidget)
	{
		m_FreqParaWidget->updateGradientType(nType);
	}
}

void GradientParaTab::InitLinearStepGradient()
{
	if (m_AmpParaWidget)
	{
		m_AmpParaWidget->InitLinearStepGradient();
	}

	if(m_FreqParaWidget)
	{
		m_FreqParaWidget->InitLinearStepGradient();
	}
}

void GradientParaTab::slot_TabPageChanged(int index)
{
	QString strName = m_tabWidget->tabText(index);
	if (!strName.isEmpty())
	{
		//if (strName.contains(tr("幅值")))
		if (strName.contains(g_sLangTxt_Native_Amplitude)) //幅值 lcq 3.14
		{
			emit sig_TabPageChanged(0);
		}
		//else if (strName.contains(tr("频率")))g_sLangTxt_Native_Freq
        else if (strName.contains(g_sLangTxt_Native_Freq))//频率 lcq 3.14
		{
			emit sig_TabPageChanged(1);
		}
	}
/*
	GradientParaSet *pWidget = (GradientParaSet*)m_tabWidget->currentWidget();
	if (pWidget != NULL)
	{
		pWidget->initData();
	}	
*/
}
