#include "monitortab.h"

MonitorTab::MonitorTab(QWidget *parent) : QWidget(parent)
{
	m_infoWidget = NULL;
	m_plotWidget = NULL;
    initUI();
	initData();
}

MonitorTab::~MonitorTab()
{
    
}

void MonitorTab::initUI()
{
	setObjectName(QString::fromUtf8("MonitorTab"));
	resize(279, 593);

	QFont font;
	font.setPointSize(9);
	setFont(font);

	QGridLayout *gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

	m_tabWidget = new QTabWidget(this);
	m_tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

	m_plotWidget = new QTimeResponseWidget(this);
	m_plotWidget->setObjectName(QString::fromUtf8("QTimeResponseWidget"));
	m_tabWidget->addTab(m_plotWidget,tr("测试过程监视图"));

	m_vectorWidget = new VectorWidget(this);
	m_vectorWidget->setObjectName(QString::fromUtf8("VectorWidget"));
	m_tabWidget->addTab(m_vectorWidget,tr("矢量图"));

// 	m_powerWidget = new PowerWidget(this);
// 	m_powerWidget->setObjectName(QString::fromUtf8("PowerWidget"));
// 	m_tabWidget->addTab(m_powerWidget, tr("功率表"));

	m_seqWidget = new SeqWidget(this);
	m_seqWidget->setObjectName(QString::fromUtf8("SeqWidget"));
	m_tabWidget->addTab(m_seqWidget, tr("序分量"));

	m_lineVoltWidget = new LineVoltWidget(this);
	m_lineVoltWidget->setObjectName(QString::fromUtf8("LineVoltWidget"));
	m_tabWidget->addTab(m_lineVoltWidget, tr("线电压"));

	m_infoWidget = new InfoWidget(this);
	m_infoWidget->setObjectName(QString::fromUtf8("InfoWidget"));
	m_tabWidget->addTab(m_infoWidget, tr("信息图"));

	//2023-3-9chenling
 	m_powerdiagramWidget= new PowerDiagramWidget(this);
 	m_powerdiagramWidget->setObjectName(QString::fromUtf8("PowerDiagramWidget"));
 	m_tabWidget->addTab(m_powerdiagramWidget,tr("功率图"));

	gridLayout->addWidget(m_tabWidget, 0, 0, 1, 1);

	QMetaObject::connectSlotsByName(this);
}

void MonitorTab::initData()
{

}

