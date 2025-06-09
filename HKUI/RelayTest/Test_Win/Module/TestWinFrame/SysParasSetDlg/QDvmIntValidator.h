#ifndef QDVMINTVALIDATOR_H
#define QDVMINTVALIDATOR_H

#include <QIntValidator>

class QDvmIntValidator : public QIntValidator
{
	Q_OBJECT

public:
	QDvmIntValidator(QObject *parent);
	~QDvmIntValidator();
	virtual QValidator::State validate(QString &input, int &pos) const;

	void SetParentValue(int dValue) const;

private:
	
};

#endif // QDVMINTVALIDATOR_H
