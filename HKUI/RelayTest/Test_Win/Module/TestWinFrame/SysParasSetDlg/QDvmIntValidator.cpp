#include "QDvmIntValidator.h"
#include "QDvmDataLineEdit.h"
QDvmIntValidator::QDvmIntValidator(QObject *parent)
	: QIntValidator(parent)
{

}

QDvmIntValidator::~QDvmIntValidator()
{

}

QValidator::State QDvmIntValidator::validate( QString &input, int &pos ) const
{
	if (input.isEmpty())
	{
		return QValidator::Intermediate;
	}

	bool OK = false;
	double val = input.toDouble(&OK);

	if (!OK)
	{
		return QValidator::Invalid;
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

void QDvmIntValidator::SetParentValue( int dValue ) const
{
	if (parent() == NULL)
	{
		return;
	}

	QDvmDataLineEdit *pLineEdit = (QDvmDataLineEdit*)parent();
	pLineEdit->SetValue(dValue);
}
