#ifndef _CAdjustComboBox_H_
#define _CAdjustComboBox_H_

#include<QComboBox>

class CAdjustComboBox : public QComboBox
{
public:
	CAdjustComboBox(QWidget *parent = 0);

	void adjustItemWidth();
	long GetIndexByString(QString strText);
};

#endif