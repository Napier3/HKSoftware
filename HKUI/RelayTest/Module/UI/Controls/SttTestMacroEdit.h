#ifndef STTTESTMACROEDIT_H
#define STTTESTMACROEDIT_H

#include <QDialog>
#include "../../../../Module/BaseClass/ExBaseObject.h"
#include "../Config/Frame/SttFrame_MacroParaView.h"

namespace Ui {
class QSttTestMacroEdit;
}

class QSttTestMacroEdit : public QDialog
{
    Q_OBJECT

public:
    explicit QSttTestMacroEdit(CExBaseObject *pObj,QWidget *parent = 0);
    virtual ~QSttTestMacroEdit();


	CExBaseObject *m_pSttTestData;
public slots:
	void slot_OKClick();
	void slot_CancelClick();

private:
    Ui::QSttTestMacroEdit *ui;
};

#endif // STTTESTMACROEDIT_H
