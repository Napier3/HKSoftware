#include "QChMapsQuickWidget.h"

QChMapsQuickWidget::QChMapsQuickWidget(CSttChMaps *pChMaps, QWidget *parent)
: QWidget(parent)
{
	m_pSttChMaps = new CSttChMaps;
	m_pSttChMaps = pChMaps;
	initUI();
}

QChMapsQuickWidget::~QChMapsQuickWidget()
{

}

void QChMapsQuickWidget::initUI()
{
	m_pTabWidget = new QTabWidget(this);
	//添加模拟量电压电流表
	QWidget* pWidget = new QWidget(m_pTabWidget);
	m_pTabWidget->addTab(pWidget, "模拟量电压/电流");

    m_pVoltAnalogQuickGrid = new CChMapsAnalogQuickGrid(AnalogMoudle_U, pWidget);
	m_pVoltAnalogQuickGrid->InitGrid(AnalogMoudle_U, m_pSttChMaps);

	m_pCurAnalogQuickGrid = new CChMapsAnalogQuickGrid(AnalogMoudle_I, pWidget);
	m_pCurAnalogQuickGrid->InitGrid(AnalogMoudle_I, m_pSttChMaps);

	m_pLayout = new QGridLayout(pWidget);
 	m_pLayout->addWidget(m_pVoltAnalogQuickGrid, 0, 0);
 	m_pLayout->addWidget(m_pCurAnalogQuickGrid, 0, 1);
	pWidget->setLayout(m_pLayout);

	//如果有弱信号插件，则插入弱信号tab页
 	if (g_oSttTestResourceMngr.m_oWeak_Tags.GetCount() > 0)
 	{
		QWidget* pWeakWidget = new QWidget(m_pTabWidget);
		m_pTabWidget->addTab(pWeakWidget, "弱信号");
		m_pCurWeakQuickGrid = new CChMapsWeakQuickGrid(pWeakWidget);
		m_pCurWeakQuickGrid->InitGrid(m_pSttChMaps);
		QVBoxLayout *m_pWeakLayout = new QVBoxLayout(pWeakWidget);
		m_pWeakLayout->addWidget(m_pCurWeakQuickGrid);
		pWeakWidget->setLayout(m_pWeakLayout);

	}

	m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->addWidget(m_pTabWidget);
	setLayout(m_pMainLayout);
}
