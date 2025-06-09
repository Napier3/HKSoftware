#ifndef QSTTTOOLBUTTON_H
#define QSTTTOOLBUTTON_H

#include <QToolButton>
#include <QObject>
#include <QFont>

#include "SttToolButtonBase.h"


class QSttToolButton : public QSttToolButtonBase
{
    Q_OBJECT

public:
    QSttToolButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
    ~QSttToolButton();

	virtual void UpdateEnableState(const CString &strState);

signals:
    void sig_clicked(QString);

public slots:
    void slot_Click();
};

#endif // QTOOLBARBUTTON_H
