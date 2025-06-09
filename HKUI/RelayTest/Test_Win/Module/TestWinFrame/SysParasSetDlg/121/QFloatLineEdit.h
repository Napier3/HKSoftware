#ifndef QFLOATLINEEDIT_H
#define QFLOATLINEEDIT_H

#include <QLineEdit>

class QFloatLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	QFloatLineEdit(QWidget *parent);
	~QFloatLineEdit();
	void InitCoverage(float fMinValue,float fMaxValue,int nDecimals = 3);//参数3为有效位数,默认为3位

	void SetValue(float fValue);
	float GetValue();

private:
	float m_fValue;
	long m_nDecimals;
	
};

#endif // QFLOATLINEEDIT_H
