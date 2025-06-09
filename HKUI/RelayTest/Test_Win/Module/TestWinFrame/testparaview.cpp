#include "testparaview.h"
#include<QSplitter>
#include<QLayout>

TestParaView::TestParaView(QWidget *parent):QWidget(parent)
{
	m_pMainPara = NULL;
	m_pMonitor = NULL;
	m_pTestParaViewSplitterH = NULL;

    initUI();
}

TestParaView::~TestParaView()
{
   
}

void TestParaView::initUI()
{
	m_pTestParaViewSplitterH = new QSplitter(Qt::Horizontal, this);
	m_pMainPara = new QMainPara(m_pTestParaViewSplitterH);
	m_pMonitor = new MonitorTab(m_pTestParaViewSplitterH);

	m_pTestParaViewSplitterH->setStretchFactor(0, 6);//5
	m_pTestParaViewSplitterH->setStretchFactor(1, 7);
    m_pTestParaViewSplitterH->setAutoFillBackground(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
    layout->addWidget(m_pTestParaViewSplitterH);
    setLayout(layout);
}



