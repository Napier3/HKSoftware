#ifndef QFLOATLINEEDIT_H
#define QFLOATLINEEDIT_H

#include <QMouseEvent>
#include "QCovDoubleValidator.h"
#include "../../../../../Module/OSInterface/OSInterface.h"

class QFloatLineEdit : public QNumberLineEditBase
{
	Q_OBJECT

public:
	QFloatLineEdit(QWidget *parent = NULL);
	~QFloatLineEdit();
	void InitCoverage(float fMinValue,float fMaxValue,int nDecimals = 3);//参数3为有效位数,默认为3位
	void InitCoverage_EditFinished(float fMinValue,float fMaxValue,int nDecimals = 3);//编辑结束后,进行变比处理
	void InitUnit(const QString &strUnit);

	void SetValue(float fValue);
	void SetValue(float *pfValue);
	float GetValue();
	long GetValue_Long();
	CString GetValue_String();
	virtual void SetValue_Number(float fValue);

// 	void SetEditFinished()//20220309 sf 键盘需要
// 	{
// 		emit editingFinished();
// 	}
private:
	float m_fValue;
	float *m_pfValue;
	float m_fMinValue;
	float m_fMaxValue;
	long m_nDecimals;
	QString m_strUnit;
	QCovDoubleValidator *m_pValid;

protected slots:
	void slot_UpdateUnitReturnPressed();
	void slot_MinMaxValueLimit();
	void slot_UpateFloatValue();

protected:
//	virtual void mousePressEvent(QMouseEvent *event);

signals:
//	void clicked();

	
};

#endif // QFLOATLINEEDIT_H
