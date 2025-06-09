#ifndef _TCPEDGECTRL_TEXTBOX_H
#define _TCPEDGECTRL_TEXTBOX_H

#include <QTextEdit>
#include <QMenu>

class CTcpEdgeCtrl_TextBox : public QTextEdit
{
	Q_OBJECT
private:
	QMenu m_oMenu;
	bool m_bStop;
	QAction* m_pClearAction;
	QAction* m_pStopAction;
	QAction* m_pContinueAction;

public:
	CTcpEdgeCtrl_TextBox(QWidget *parent = 0);
	virtual ~CTcpEdgeCtrl_TextBox();

	virtual QString LogString(long nLevel, const char *strMsg);
	virtual QString LogString(long nLevel, const QString &strMsg);
	virtual void UsePkgAction(bool bUse = true);

protected slots:
	void slot_showMenu(const QPoint& pt);
	void slot_menuCopy(bool checked);
	void slot_menuSelectAll(bool checked);
	void slot_menuClear(bool checked);
	void slot_menuStop(bool checked);
	void slot_menuContinue(bool checked);
};

#endif