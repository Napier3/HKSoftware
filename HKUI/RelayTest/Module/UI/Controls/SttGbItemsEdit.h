#ifndef SttGbItemsEDIT_H
#define SttGbItemsEDIT_H

#include <QDialog>
#include "../../../../Module/BaseClass/ExBaseObject.h"
#include "../Config/Frame/SttFrame_MacroParaView.h"
#include "../../SttCmd/GuideBook/SttItemBase.h"

namespace Ui {
class QSttGbItemsEdit;
}

class QSttGbItemsEdit : public QDialog
{
    Q_OBJECT

public:
    explicit QSttGbItemsEdit(CSttItemBase *pItems, CExBaseList *pParent,QWidget *parent = 0);
    virtual ~QSttGbItemsEdit();

	bool m_bEditMode;
	CSttItemBase *m_pSttItems;
	CExBaseList *m_pSttParent;

public:
	long CalAutoIndex(const CString& strID);
	void InitTitleLevel();
        void InitLanguage();
public slots:
	void slot_OKClick();
	void slot_CancelClick();
	void on_m_chkRptTitle_clicked();

private slots:
    void on_m_Btn_SelName_clicked();

private:
    Ui::QSttGbItemsEdit *ui;
};

#endif // SttGbItemsEDIT_H
