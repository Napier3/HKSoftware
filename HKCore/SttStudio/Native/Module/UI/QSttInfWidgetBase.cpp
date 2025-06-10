#include "QSttInfWidgetBase.h"

QSttInfWidgetBase::QSttInfWidgetBase(QWidget *parent)
	: QWidget(parent)
{
	
}

QSttInfWidgetBase::~QSttInfWidgetBase()
{

}

void QSttInfWidgetBase::InitSttInfWidget(QWidget *pInfWidget)
{
	m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->setContentsMargins(0, 0, 0, 0);
	m_pMainLayout->addWidget(pInfWidget);
	setLayout(m_pMainLayout);
}
