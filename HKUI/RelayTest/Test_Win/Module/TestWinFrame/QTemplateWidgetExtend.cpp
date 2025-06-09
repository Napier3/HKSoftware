#include "QTemplateWidgetExtend.h"
#include <QVBoxLayout>
#include <QTextCodec>
#include "QItemTableBase.h"

QTemplateWidgetExtend::QTemplateWidgetExtend()
{
	initUI();
}

QTemplateWidgetExtend::~QTemplateWidgetExtend()
{

}

void QTemplateWidgetExtend::initUI()
{
	setObjectName(QString::fromUtf8("QTemplateWidget"));
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

	m_pSplitterV = new QSplitter(Qt::Vertical, this);
//	m_pSplitterV->setStretchFactor(0,10);
//	m_pSplitterV->setStretchFactor(1,10);
	m_pSplitterV->setAutoFillBackground(true);

	QVBoxLayout* pLay = new QVBoxLayout;
	pLay->addWidget(m_pSplitterV);
	pLay->setMargin(0);
	pLay->setSpacing(0);
	centerWidget->setLayout(pLay);
}