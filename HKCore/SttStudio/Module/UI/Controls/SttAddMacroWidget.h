#ifndef STTADDMACROWIDGET_H
#define STTADDMACROWIDGET_H

#include <QDialog>
#include <QFont>
#include "../../../../Module/BaseClass/QT/ExBaseListTreeCtrl.h"
#include "../Config/Frame/SttFrame_MacroParaView.h"
#include "../Config/MacroTestUI/SttMacroTestUI_TestMacroUIRef.h"
#include "../Config/MacroTestUI/SttMacroTestUI_TestMacroUIMngr.h"

namespace Ui {
class QSttAddMacroWidget;
}

class QSttAddMacroWidget : public QDialog, public CExBaseListTreeOptrInterface
{
    Q_OBJECT

public:
    explicit QSttAddMacroWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttAddMacroWidget();

	void Use_Name_ID(BOOL bUse);  //lijunqing 2022-6-24  lijunqing
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj);

    CExBaseListTreeCtrl *m_pTreeCtrl;
	CSttMacroTestUI_TestMacroUIRef *m_pCurrUIRef;
	CSttMacroTestUI_TestMacroUIMngr *m_pTestMacroUIMngr;
    QFont m_font;

	CExBaseList *m_pCurrentSelGbItem;  //选择功能时，当前选中的父项目节点
	CString m_strItemsName, m_strItemsID;
	BOOL m_bUseNameID;

    void EnableOK();
	BOOL CanAddMacro();
	void InitLanguage();
	long CalAutoIndex(const CString& strID);

public slots:
	void slot_OKClick();
	void slot_CancelClick();


signals:
	void sig_TreeItemSelect(CSttMacroTestUI_TestMacroUIRef *, const CString &, const CString &);
private slots:
    void on_m_edtItemsName_textChanged(const QString &arg1);

    void on_m_edtItemsID_textChanged(const QString &arg1);

private:
    Ui::QSttAddMacroWidget *ui;
};

#endif // STTADDMACROWIDGET_H
