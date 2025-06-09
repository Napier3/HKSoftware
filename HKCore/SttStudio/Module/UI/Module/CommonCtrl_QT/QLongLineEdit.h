#ifndef QLONGLINEEDIT_H
#define QLONGLINEEDIT_H

#include "QCovDoubleValidator.h"
#include <QMouseEvent>

class QLongLineEdit : public QNumberLineEditBase
{
	Q_OBJECT

public:
	QLongLineEdit(QWidget *parent = NULL);
	~QLongLineEdit();
	void InitCoverage(long nMinValue,long nMaxValue);//
	void InitUnit(const QString &strUnit);

	void SetValue(long nValue);
	virtual void SetValue_Number(float fValue);

	long GetValue();

// 	void SetEditFinished()//20220309 sf ¼üÅÌÐèÒª
// 	{
// 		emit editingFinished();
// 	}

private:
	QString m_strUnit;
	QCovDoubleValidator *m_pValid;

protected slots:
	void slot_UpdateUnitReturnPressed();

protected:
//	virtual void mousePressEvent(QMouseEvent *event);

signals:
//	void clicked();
	
};

#endif // QLONGLINEEDIT_H
