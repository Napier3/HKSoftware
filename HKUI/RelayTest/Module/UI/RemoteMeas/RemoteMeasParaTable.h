#ifndef QREMOTEMEASPARATABLE_H
#define QREMOTEMEASPARATABLE_H

#include <QWidget>
#include <QHBoxLayout>

#include "RemoteMeasParaset.h"
#include "QRemoteMeasTable.h"

class QRemoteMeasParaTable : public QWidget
{
	Q_OBJECT

public:
    QRemoteMeasParaTable(QWidget *parent = 0);
	virtual ~QRemoteMeasParaTable();

	void InitUI();
public:
	RemoteMeasParaSet* m_pUIParaWidget;		//电压电流设置
	QTabWidget* m_pTabWidget;

};

#endif // QREMOTEMEASPARATABLE_H
