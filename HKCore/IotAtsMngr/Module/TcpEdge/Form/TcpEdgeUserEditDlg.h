#ifndef _TCPEDGEUSEREDITDLG_H_
#define _TCPEDGEUSEREDITDLG_H_

#include <QMenu>
#include <QVBoxLayout>
#include <Qsci/qsciscintilla.h>
#include "TcpEdgeFormUI.h"

namespace Ui {
	class CTcpEdgeUserEditDlg;
}

class CTcpEdgeUserEditDlg : public CTcpEdgeFormUI
{
	Q_OBJECT
private:
	Ui::CTcpEdgeUserEditDlg *ui;
	QMenu m_oMenu;
	QsciScintilla* m_pTextBox;

	void InitWriteUI();
	void InitReadUI();
	void InitScintilla();
	QString ResizePkg(QString strPkg);

public:
	explicit CTcpEdgeUserEditDlg(QWidget *parent = NULL);
	CTcpEdgeUserEditDlg(const QString& strPkg, const QString& strError);
	~CTcpEdgeUserEditDlg();

	QString text();
	bool ch();
	void InitFunctionBtns(CExBaseList* pDataset);

protected slots:
	void slot_CharAdded(int charadded);
	void slot_showMenu(const QPoint& pt);
	void slot_menuUndo(bool checked);
	void slot_menuRedo(bool checked);
	void slot_menuCopy(bool checked);
	void slot_menuPaste(bool checked);
	void slot_menuSelectAll(bool checked);
	void slot_menuClear(bool checked);
	void slot_menuTriggered();
};

#endif