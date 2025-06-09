#include "paratab.h"
#include "QBasicTestParaSet.h"
#include "../Module/TestWinFrame/ReportView/XLangResource_PowerTestWin.h"

ParaTab::ParaTab(QWidget *parent)
	: QWidget(parent)
{
	m_AnaParaWidget = NULL;
	m_DigParaWidget = NULL;
	m_LowSParaWidget = NULL;
	m_pVBoxLayout = NULL;

	m_tabWidget = new QTabWidget(this);
	connect(m_tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slot_TabPageChanged(int)));

	initUI();
}

ParaTab::~ParaTab()
{
}

void ParaTab::initUI()
{
	int num = m_tabWidget->count();
	if (m_pVBoxLayout != NULL)
	{
		delete m_pVBoxLayout;
		m_pVBoxLayout = NULL;
	}

	if (m_AnaParaWidget != NULL)
	{
		delete m_AnaParaWidget;
		m_AnaParaWidget = NULL;
	}
	if (m_DigParaWidget != NULL)
	{
		delete m_DigParaWidget;
		m_DigParaWidget = NULL;
	}
	if (m_LowSParaWidget != NULL)
	{
		delete m_LowSParaWidget;
		m_LowSParaWidget = NULL;
	}
	m_tabWidget->clear();

	m_AnaParaWidget = new QBasicTestParaSet();
	m_tabWidget->addTab(m_AnaParaWidget,/*tr("模拟")*/g_sLangTxt_ChMaps_Analog);
	
	m_DigParaWidget = new QBasicTestParaSet();
	m_tabWidget->addTab(m_DigParaWidget,/*tr("数字")*/g_sLangTxt_ChMaps_Digital);
	
	m_LowSParaWidget = new QBasicTestParaSet();
	m_tabWidget->addTab(m_LowSParaWidget,/*tr("小信号")*/g_sLangTxt_Native_smallsignal);

	m_pVBoxLayout = new QVBoxLayout(this);
	m_pVBoxLayout->addWidget(m_tabWidget);
	m_pVBoxLayout->setMargin(0);
	m_pVBoxLayout->setSpacing(0);
	setLayout(m_pVBoxLayout);	
}

void ParaTab::setEnabled()
{
	if (m_tabWidget)
	{
		m_tabWidget->setTabEnabled(0,g_oSystemParas.m_nHasAnalog);
		m_tabWidget->setTabEnabled(1,g_oSystemParas.m_nHasDigital);
		m_tabWidget->setTabEnabled(2,g_oSystemParas.m_nHasWeek);
	}
}

QParaSetBase* ParaTab::getActiveParaSet()
{
	if (m_tabWidget == NULL)
	{
		return NULL;
	}

	return (QParaSetBase*)m_tabWidget->currentWidget();
}

QParaSetBase* ParaTab::getAnaParaSet(){
	return m_AnaParaWidget;
}

QParaSetBase* ParaTab::getDigParaSet(){
	return m_DigParaWidget;
}

QParaSetBase* ParaTab::getLowSParaSet()
{
	return m_LowSParaWidget;
}

void ParaTab::slot_TabPageChanged(int index)
{
	QString strName = m_tabWidget->tabText(index);
	if (!strName.isEmpty())
	{
		if (strName.contains(/*tr("模拟")*/g_sLangTxt_ChMaps_Analog))
		{
			emit sig_TabPageChanged(P_Analog);
		}
		else if (strName.contains(/*tr("数字")*/g_sLangTxt_ChMaps_Digital))
		{
			emit sig_TabPageChanged(P_Digit);
		}
		else if (strName.contains(/*tr("小信号")*/g_sLangTxt_Native_smallsignal))
		{
			emit sig_TabPageChanged(P_LowSignal);
		}
	}

	QParaSetBase *pWidget = (QParaSetBase*)m_tabWidget->currentWidget();
	if (pWidget != NULL)
	{
		pWidget->initData();
	}	
}