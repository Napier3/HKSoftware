#ifndef QSTTITEMBUTTON_H
#define QSTTITEMBUTTON_H

#include <QPushButton>
#include <QFont>

#include "../Config/Frame/SttFrame_Item.h"

class QSttItemButton : public QPushButton
{
    Q_OBJECT

public:
    QSttItemButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
    ~QSttItemButton();

	virtual void UpdateEnableState(const CString &strState);
    CSttFrame_Item *m_pItem;
signals:
    void sig_clicked(QString);

public slots:
    void slot_Click();
};

#endif // QSTTITEMBUTTON_H
