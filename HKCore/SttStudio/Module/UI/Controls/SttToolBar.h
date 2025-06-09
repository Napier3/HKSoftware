#ifndef QSTTTOOLBAR_H
#define QSTTTOOLBAR_H

#include <QToolButton>
#include <QToolBar>
#include "../Config/Frame/SttFrame_XBar.h"
#include "SttToolButton.h"
#include "../../../../Module/DataMngr/DvmData.h"

class QSttToolBar : public QToolBar
{
	Q_OBJECT
public:
    QSttToolBar(CSttFrame_ToolBar *pToolBar,QWidget *parent=0);
	virtual ~QSttToolBar();

public:
	void InitToolButton();

	QList<QSttToolButton*> m_listToolBtn;
	QList<QToolBar*> m_listToolBar;

	virtual void UpdateEnableState(const CString &strState);

signals:
	void sig_ToolBarClicked(QString);
public:
    CSttFrame_ToolBar *m_pToolBar;
};


#endif // QSTTTOOLBUTTONBASE_H
