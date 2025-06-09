#ifndef STATEMONITORTAB_H
#define STATEMONITORTAB_H

#include <QGridLayout>
#include <QWidget>

class QStateMonitorTab : QWidget
{
Q_OBJECT
public:
	QStateMonitorTab(QWidget *parent = 0);
	virtual ~QStateMonitorTab();

public:
	void InitUI();
	
};

#endif // STATEMONITORTAB_H