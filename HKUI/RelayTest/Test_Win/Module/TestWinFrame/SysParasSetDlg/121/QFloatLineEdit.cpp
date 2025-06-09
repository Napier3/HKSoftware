#include "QFloatLineEdit.h"
#include"QCovDoubleValidator.h"

QFloatLineEdit::QFloatLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	m_fValue = 0;
	m_nDecimals = 3;
}

QFloatLineEdit::~QFloatLineEdit()
{

}

void QFloatLineEdit::InitCoverage(float fMinValue,float fMaxValue,int nDecimals)
{
	QCovDoubleValidator *pValid = new QCovDoubleValidator(this);
	pValid->setRange(fMinValue, fMaxValue,nDecimals);
	m_nDecimals = nDecimals;
	setValidator(pValid);  
}

void QFloatLineEdit::SetValue(float fValue)
{
	if (m_nDecimals>0)
	{
		setText(QString::number(fValue,'f',m_nDecimals));
	} 
	else
	{
		setText(QString("%1").arg(fValue));
	}
}

float QFloatLineEdit::GetValue()
{
	QString strValue;
	strValue = text();
	float fValue = strValue.toFloat();
	return fValue;
}
