#ifndef QFLOATLINEEDIT_H
#define QFLOATLINEEDIT_H

#include <QMouseEvent>
#include "QCovDoubleValidator.h"

class QFloatLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	QFloatLineEdit(QWidget *parent);
	~QFloatLineEdit();
	void InitCoverage(float fMinValue,float fMaxValue,int nDecimals = 3);//参数3为有效位数,默认为3位
//	void InitUnit(const QString &strUnit);

	void SetValue(float fValue);
//	void SetValue(float *pfValue);
	float GetValue();
// 	long GetValue_Long();
// 	virtual void SetValue_Number(float fValue);
private:
	QCovDoubleValidator *m_pValid;
	float m_fValue;
	float *m_pfValue;
	long m_nDecimals;
	QString m_strUnit;

// protected slots:
// 	void slot_UpdateUnitReturnPressed();
// 	void slot_UpateFloatValue();
	
};

#endif // QFLOATLINEEDIT_H
