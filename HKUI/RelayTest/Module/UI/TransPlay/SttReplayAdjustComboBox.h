#ifndef _CSttReplayAdjustComboBox_H_
#define _CSttReplayAdjustComboBox_H_

#include<QComboBox>
#include "../Module/ScrollCtrl/ScrollComboBox.h"

class CSttReplayAdjustComboBox : public QComboBox
{
public:
	CSttReplayAdjustComboBox(QWidget *parent = 0);

	void adjustItemWidth();
};

#endif