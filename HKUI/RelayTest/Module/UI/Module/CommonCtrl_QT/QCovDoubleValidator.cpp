#include "QCovDoubleValidator.h"
#include <QDoubleValidator>
#include "QFloatLineEdit.h"

QNumberLineEditBase::QNumberLineEditBase(QWidget *parent)
: QSttLineEdit(parent)
{
}

QNumberLineEditBase::~QNumberLineEditBase()
{

}

void QNumberLineEditBase::SetValue_Number(float fValue)
{

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QCovDoubleValidator::QCovDoubleValidator(QObject *parent)
	: QDoubleValidator(parent)
{
}

QCovDoubleValidator::~QCovDoubleValidator()
{

}

QValidator::State QCovDoubleValidator::validate(QString & input, int & pos) const
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

void QCovDoubleValidator::SetParentValue(double dValue) const
{
	if (parent() == NULL)
	{
		return;
	}

	QNumberLineEditBase *pLineEdit = (QNumberLineEditBase*)parent();
	pLineEdit->SetValue_Number(dValue);
}
