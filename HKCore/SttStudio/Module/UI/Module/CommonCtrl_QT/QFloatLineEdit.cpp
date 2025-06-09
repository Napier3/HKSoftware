#include "QFloatLineEdit.h"
#include"QCovDoubleValidator.h"
#include "../../../../../Module/OSInterface/OSInterface.h"
#include "../../../../../Module/API/StringApi.h"

QFloatLineEdit::QFloatLineEdit(QWidget *parent)
	: QNumberLineEditBase(parent)
{
	m_fValue = 0;
	m_fMinValue = 0.00f;
	m_fMaxValue = 1000000.0f;
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
		m_pValid->setRange(fMinValue, fMaxValue,nDecimals);
		m_nDecimals = nDecimals;
		setValidator(m_pValid);  
	}
	else
	{
		m_pValid->setRange(fMinValue, fMaxValue,nDecimals);
		m_nDecimals = nDecimals;
		setValidator(m_pValid);  
	}
}

void QFloatLineEdit::InitCoverage_EditFinished(float fMinValue,float fMaxValue,int nDecimals)
{
	m_fMinValue = fMinValue;
	m_fMaxValue = fMaxValue;
	m_nDecimals = nDecimals;
	connect(this, SIGNAL(editingFinished()), SLOT(slot_MinMaxValueLimit()));
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

void QFloatLineEdit::SetValue_Number(float fValue)
{
	SetValue(fValue);
}

void QFloatLineEdit::SetValue(float *pfValue)
{
	disconnect(this, SIGNAL(editingFinished()), this,SLOT(slot_UpateFloatValue()));
	m_pfValue = pfValue;
	SetValue(*m_pfValue);
	connect(this, SIGNAL(editingFinished()), SLOT(slot_UpateFloatValue()));
}

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

CString QFloatLineEdit::GetValue_String()
{
	CString strValue;
	strValue = text();

	if (!m_strUnit.isEmpty())
	{
		strValue.Replace(m_strUnit,_T(""));
	}

	return strValue;
}

long QFloatLineEdit::GetValue_Long()
{
	CString strValue;
	strValue = text();
	return CString_To_long(strValue);
}

void QFloatLineEdit::InitUnit(const QString &strUnit)
{
	m_strUnit = strUnit;
	connect(this, SIGNAL(editingFinished()), SLOT(slot_UpdateUnitReturnPressed()));
}

void QFloatLineEdit::slot_UpdateUnitReturnPressed()
{
	if (!m_strUnit.isEmpty())
	{
		disconnect(this, SIGNAL(editingFinished()),this, SLOT(slot_UpdateUnitReturnPressed()));
		float fValue = GetValue();
		SetValue(fValue);
		connect(this, SIGNAL(editingFinished()), SLOT(slot_UpdateUnitReturnPressed()));
	}
}

void QFloatLineEdit::slot_MinMaxValueLimit()
{
	QString strValue;
	float fValue = GetValue();

	if (fValue<m_fMinValue)
	{
		fValue = m_fMinValue;
	}

	if (fValue>m_fMaxValue)
	{
		fValue = m_fMaxValue;
	}

	disconnect(this, SIGNAL(editingFinished()),this ,SLOT(slot_MinMaxValueLimit()));
	SetValue(fValue);
	connect(this, SIGNAL(editingFinished()), SLOT(slot_MinMaxValueLimit()));
}

void QFloatLineEdit::slot_UpateFloatValue()
{
	if (m_pfValue != NULL)
	{
		*m_pfValue = GetValue();
	}
}

// void QFloatLineEdit::mousePressEvent(QMouseEvent *event)
//{
// 	//如果单击了就触发clicked信号
//	if (event->button() == Qt::LeftButton)
//	{
// 		//触发clicked信号
// 		emit clicked();
// 	}
// 
// 	//将该事件传给父类处理
// 	QLineEdit::mousePressEvent(event);
//}