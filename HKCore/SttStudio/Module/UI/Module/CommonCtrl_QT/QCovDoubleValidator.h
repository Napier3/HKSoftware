#ifndef QCovDoubleValidator_H
#define QCovDoubleValidator_H

#include <QDoubleValidator>
#include <QLineEdit>
#include "../../Controls/SttLineEdit.h"

class QNumberLineEditBase : public QSttLineEdit
{
public:
	QNumberLineEditBase(QWidget *parent);
	~QNumberLineEditBase();
	virtual void SetValue_Number(float fValue); 
};

class QCovDoubleValidator : public QDoubleValidator
{
	Q_OBJECT

public:
	QCovDoubleValidator(QObject *parent);
	~QCovDoubleValidator();	
	virtual QValidator::State validate(QString &input, int &pos) const;

	void SetParentValue(double dValue) const;
private:
};

#endif // QCovDoubleValidator_H
