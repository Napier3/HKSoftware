#include "QLongLineEdit.h"
#include"QCovDoubleValidator.h"

QLongLineEdit::QLongLineEdit(QWidget *parent)
	: QNumberLineEditBase(parent)
{
	m_strUnit = "";
	m_pValid = NULL;
}

QLongLineEdit::~QLongLineEdit()
{

}

void QLongLineEdit::InitCoverage(long nMinValue,long nMaxValue)
{
	if (m_pValid == NULL)
	{
		m_pValid = new QCovDoubleValidator(this);
	}

	m_pValid->setRange(nMinValue, nMaxValue,0);
	setValidator(m_pValid);  
}

void QLongLineEdit::SetValue(long nValue)
{
	QString strTmp;

	strTmp = (QString("%1").arg(nValue));

	if (!m_strUnit.isEmpty())
	{
		strTmp += m_strUnit;
	}

	setText(strTmp);
}

void QLongLineEdit::SetValue_Number(float fValue)
{
	long nValue = fValue;

	if ((fValue-nValue)>=0.5)
	{
		nValue++;
	}

	SetValue(nValue);
}

long QLongLineEdit::GetValue()
{
	QString strValue;
	strValue = text();

	if (!m_strUnit.isEmpty())
	{
		strValue.replace(m_strUnit,"");
	}

	long nValue = strValue.toLong();
	return nValue;
}

void QLongLineEdit::InitUnit(const QString &strUnit)
{
	m_strUnit = strUnit;
	connect(this, SIGNAL(editingFinished()), SLOT(slot_UpdateUnitReturnPressed()));
}

void QLongLineEdit::slot_UpdateUnitReturnPressed()
{
	if (!m_strUnit.isEmpty())
	{
		QString strValue;
		long nValue = GetValue();
		SetValue(nValue);
	}
}

// void QLongLineEdit::mousePressEvent(QMouseEvent *event)
//{
// 	//��������˾ʹ���clicked�ź�
// 	if (event->button() == Qt::LeftButton)
// 	{
// 		//����clicked�ź�
// 		emit clicked();
// 	}
// 
// 	//�����¼��������ദ��
// 	QLineEdit::mousePressEvent(event);
//}