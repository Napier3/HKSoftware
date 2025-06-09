#include "CharEditWidget_None.h"

QCharEditWidget_None::QCharEditWidget_None(QWidget* pParent) : QWidget(pParent)
{
	m_pCharEditWidget = this;

	m_pText = new QLabel(this); 
	m_pText->setText(_T("none characteristic"));
	m_pText->show();
}

QCharEditWidget_None::~QCharEditWidget_None()
{
	
}
