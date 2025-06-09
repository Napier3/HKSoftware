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
	void InitCoverage(float fMinValue,float fMaxValue,int nDecimals = 3);//����3Ϊ��Чλ��,Ĭ��Ϊ3λ
	void InitCoverage_EditFinished(float fMinValue,float fMaxValue,int nDecimals = 3);//�༭������,���б�ȴ���
	void InitUnit(const QString &strUnit);

	void SetValue(float fValue);
	void SetValue(float *pfValue);
	float GetValue();
	long GetValue_Long();
	CString GetValue_String();
	virtual void SetValue_Number(float fValue);

// 	void SetEditFinished()//20220309 sf ������Ҫ
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
