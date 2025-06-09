#ifndef QDVMDATALINEEDIT_H
#define QDVMDATALINEEDIT_H

#include <QLineEdit>
#include "..\..\..\..\..\Module\DataMngr\DvmData.h"

class QDvmDataLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	QDvmDataLineEdit(QWidget *parent);
	~QDvmDataLineEdit();
	void InitCoverage(float fMinValue,float fMaxValue,int nDecimals = 3);//参数3为有效位数,默认为3位

	void setData(CDvmData *pData);
	void SetValue(float fValue);
	void SetValue(int nValue);

private:
	CDvmData *m_pData;
};

#endif // QDVMDATALINEEDIT_H
