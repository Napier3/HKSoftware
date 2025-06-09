#include "QDvmDoubleValidator.h"
#include "QDvmDataLineEdit.h"

QDvmDoubleValidator::QDvmDoubleValidator(QObject *parent)
	: QDoubleValidator(parent)
{

}

QDvmDoubleValidator::~QDvmDoubleValidator()
{

}

QValidator::State QDvmDoubleValidator::validate( QString &input, int &pos ) const
{
	if (input.isEmpty())
	{
		return QValidator::Intermediate;
	}
	if(input == "-")
	{
		return QValidator::Intermediate;
	}

	bool OK = false;
	double val = input.toDouble(&OK);

	if (!OK)
	{
		return QValidator::Invalid;
	}

	int dotPos = input.indexOf(".");

	if (dotPos > 0)
	{
		if (input.right(input.length() - dotPos - 1).length() > decimals())
		{
			return QValidator::Invalid;
		}
	}

	if (val<bottom())
	{
		SetParentValue(bottom());
		return QValidator::Invalid;
	}

	if (val>top())
	{
		SetParentValue(top());
		return QValidator::Invalid;
	}

	return QValidator::Acceptable;
}

void QDvmDoubleValidator::SetParentValue( double dValue ) const
{
	if (parent() == NULL)
	{
		return;
	}

	QDvmDataLineEdit *pLineEdit = (QDvmDataLineEdit*)parent();
	pLineEdit->SetValue((float)dValue);
}
