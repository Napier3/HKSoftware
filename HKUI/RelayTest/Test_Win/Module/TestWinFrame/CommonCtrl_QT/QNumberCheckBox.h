#ifndef QNUMBERCHECKBOX_H
#define QNUMBERCHECKBOX_H

#include <QCheckBox>

class QNumberCheckBox : public QCheckBox
{
	Q_OBJECT

public:
	QNumberCheckBox(QWidget *parent = NULL);
	QNumberCheckBox(const QString &text,QWidget *parent = NULL);
	~QNumberCheckBox();

	void SetValue(int nValue);
	int GetValue();

private:
	void InitStyleSheet();


protected slots:
	
};

#endif // QNUMBERCHECKBOX_H
