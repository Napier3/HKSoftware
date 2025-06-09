#ifndef CharEditWidget_Syn_H
#define CharEditWidget_Syn_H

#include <QWidget>
#include <QLabel>
#include "ui_CharEditWidget_Syn.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"

#include "CharEditWidgetBase.h"

class QCharEditWidget_Syn : public QWidget, public QCharEditWidgetBase
{
	Q_OBJECT

public:
	QCharEditWidget_Syn(QWidget *parent = 0);
	~QCharEditWidget_Syn();

        void InitLanguage();

signals:

protected slots:


private:
	Ui::QCharEditWidget_Syn ui;
	

public:

};

#endif // CharEditWidget_Syn_H
