#ifndef QHARMPARATABLE_H
#define QHARMPARATABLE_H

#include <QWidget>
#include <QHBoxLayout>

#include "QHarmTable.h"

class QHarmParaTable : public QWidget
{
	Q_OBJECT

public:
    QHarmParaTable(QWidget *parent = 0);
	virtual ~QHarmParaTable();

	void InitUI();
public:
	QHarmTable *m_pUChannel;
	QHarmTable *m_pIChannel;
	
	QHBoxLayout *m_pHBoxLayout_Main;
};

#endif // QHARMPARATAB_H
