#ifndef QDVMDOUBLEVALIDATOR_H
#define QDVMDOUBLEVALIDATOR_H

#include <QDoubleValidator>

class QDvmDoubleValidator : public QDoubleValidator
{
	Q_OBJECT

public:
	QDvmDoubleValidator(QObject *parent);
	~QDvmDoubleValidator();

	virtual QValidator::State validate(QString &input, int &pos) const;

	void SetParentValue(double dValue) const;

private:
	
};

#endif // QDVMDOUBLEVALIDATOR_H
