#include "QFloatLineEdit.h"
#include"QCovDoubleValidator.h"
#include "../../../../../Module/OSInterface/OSInterface.h"
#include "../../../../../Module/API/StringApi.h"

QFloatLineEdit::QFloatLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	m_fValue = 0;
	m_nDecimals = 3;
	m_strUnit = "";
	m_pfValue = NULL;
	m_pValid = NULL;
}

QFloatLineEdit::~QFloatLineEdit()
{

}

void QFloatLineEdit::InitCoverage(float fMinValue,float fMaxValue,int nDecimals)
{
	if (m_pValid == NULL)
	{
		m_pValid = new QCovDoubleValidator(this);
		setValidator(m_pValid);  
	}

	m_pValid->setRange(fMinValue, fMaxValue,nDecimals);
	m_nDecimals = nDecimals;
}

void QFloatLineEdit::SetValue(float fValue)
{
	QString strTmp;

	if (m_nDecimals>0)
	{
		strTmp = QString::number(fValue,'f',m_nDecimals);
	} 
	else
	{
		strTmp = (QString("%1").arg(fValue));
	}

	if (!m_strUnit.isEmpty())
	{
		strTmp += m_strUnit;
	}

	if (m_pfValue != NULL)
	{
		*m_pfValue = fValue;
	}

	setText(strTmp);
}

// void QFloatLineEdit::SetValue_Number(float fValue)
// {
// 	SetValue(fValue);
// }
// 
// void QFloatLineEdit::SetValue(float *pfValue)
// {
// 	disconnect(this, SIGNAL(editingFinished()), this,SLOT(slot_UpateFloatValue()));
// 	m_pfValue = pfValue;
// 	SetValue(*m_pfValue);
// 	connect(this, SIGNAL(editingFinished()), SLOT(slot_UpateFloatValue()));
// }

float QFloatLineEdit::GetValue()
{
	QString strValue;
	strValue = text();

	if (!m_strUnit.isEmpty())
	{
		strValue.replace(m_strUnit,"");
	}

	float fValue = strValue.toFloat();
	return fValue;
}

// long QFloatLineEdit::GetValue_Long()
// {
// 	CString strValue;
// 	strValue = text();
// 	return CString_To_long(strValue);
// }

// void QFloatLineEdit::InitUnit(const QString &strUnit)
// {
// 	m_strUnit = strUnit;
// 	connect(this, SIGNAL(editingFinished()), SLOT(slot_UpdateUnitReturnPressed()));
// }

// void QFloatLineEdit::slot_UpdateUnitReturnPressed()
// {
// 	if (!m_strUnit.isEmpty())
// 	{
// 		QString strValue;
// 		float fValue = GetValue();
// 		SetValue(fValue);
// 	}
// }
// 
// void QFloatLineEdit::slot_UpateFloatValue()
// {
// 	if (m_pfValue != NULL)
// 	{
// 		*m_pfValue = GetValue();
// 	}
// }
