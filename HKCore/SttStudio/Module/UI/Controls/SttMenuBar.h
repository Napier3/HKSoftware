#ifndef QSTTMENUBAR_H
#define QSTTMENUBAR_H

#include <QMenuBar>
#include <QMenu>
#include "../Config/Frame/SttFrame_Menus.h"
#include "SttAction.h"

class QSttMenuBar : public QMenuBar
{
	Q_OBJECT
public:
    QSttMenuBar(CSttFrame_Menus *pMenus,QWidget *parent=0);
	virtual ~QSttMenuBar();
public:
	void InitAction();

	QList<QMenu*> m_listMenu;
	QList<QSttAction*> m_listAct;

signals:
	void sig_MenuClicked(QString);
public:
    CSttFrame_Menus *m_pMenus;
};


#endif
