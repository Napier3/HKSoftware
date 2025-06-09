#ifndef STTDEBUGLOGWIDGET_H
#define STTDEBUGLOGWIDGET_H

#include <QWidget>
#include "../../../Module/Log/LogPrint.h"

namespace Ui {
class sttdebuglogwidget;
}

class sttdebuglogwidget : public QWidget, public CLogBase
{
    Q_OBJECT

public:
    explicit sttdebuglogwidget(QWidget *parent = 0);
    ~sttdebuglogwidget();

    void SaveLogFile();
    CString m_strMacroID;

public:
    virtual void LogString(long nLevel, const CString &strMsg);
    virtual void LogString(long nLevel, const char *strMsg);

signals:
    void sig_LogString(QString strMsg);

public slots:
    void slot_LogString(QString strMsg);

private:
    Ui::sttdebuglogwidget *ui;
};

extern sttdebuglogwidget *g_pLogWidget;

#endif // STTDEBUGLOGWIDGET_H
