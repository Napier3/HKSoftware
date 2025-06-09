#include "qmainpara.h"

QMainPara::QMainPara(QWidget *parent): QWidget(parent)
{
	m_templateWidget = NULL;
	m_pMainParaSplitterV = NULL;
	initUI();
}

QMainPara::~QMainPara()
{

}

void QMainPara::initUI()
{
	setObjectName(QString::fromUtf8("QMainPara"));
	resize(502, 412);

	QFont font;
	font.setPointSize(9);
	setFont(font);

	QGridLayout *gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

	QWidget *centerWidget = new QWidget(this);
	centerWidget->setObjectName(QString::fromUtf8("centerWidget"));
	gridLayout->addWidget(centerWidget, 0, 0, 1, 1);

	m_pMainParaSplitterV = new QSplitter(Qt::Vertical, this);
	m_tabWidget = new QTabWidget(m_pMainParaSplitterV);
	m_tabWidget->setTabPosition(QTabWidget::North);

	QVBoxLayout* pLay = new QVBoxLayout;
	pLay->addWidget(m_pMainParaSplitterV);
	pLay->setMargin(0);
	pLay->setSpacing(0);
	centerWidget->setLayout(pLay);
}
