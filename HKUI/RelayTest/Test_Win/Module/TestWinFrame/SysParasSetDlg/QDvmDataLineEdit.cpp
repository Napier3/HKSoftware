#include "QDvmDataLineEdit.h"
#include "QDvmIntValidator.h"
#include "QDvmDoubleValidator.h"

QDvmDataLineEdit::QDvmDataLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	m_pData = NULL;
}

QDvmDataLineEdit::~QDvmDataLineEdit()
{
	
}

void QDvmDataLineEdit::setData( CDvmData *pData )
{
	ASSERT(pData);
	m_pData = pData;

	setText(m_pData->m_strValue);
}

void QDvmDataLineEdit::InitCoverage( float fMinValue,float fMaxValue,int nDecimals /*= 3*/ )
{
	if (m_pData->m_strDataType == _T("int"))
	{
		QDvmIntValidator *pValid = new QDvmIntValidator(this);
		pValid->setRange(fMinValue,fMaxValue);
		setValidator(pValid);
	}
	else if (m_pData->m_strDataType == _T("float"))
	{
		QDvmDoubleValidator *pValid = new QDvmDoubleValidator(this);
		pValid->setRange(fMinValue,fMaxValue,nDecimals);
		setValidator(pValid);
	}
	else{}
}

void QDvmDataLineEdit::SetValue( float fValue )
{
	setText(QString("%1").arg(fValue));
}

void QDvmDataLineEdit::SetValue( int nValue )
{
	setText(QString("%1").arg(nValue));
}
