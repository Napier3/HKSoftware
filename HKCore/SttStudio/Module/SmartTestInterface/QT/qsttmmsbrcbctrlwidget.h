#ifndef QSTTMMSBRCBCTRLWIDGET_H
#define QSTTMMSBRCBCTRLWIDGET_H

#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"

#include <QDialog>

namespace Ui {
class QSttMmsBrcbCtrlWidget;
}

class QSttMmsBrcbCtrlWidget : public QDialog
{
    Q_OBJECT

public:
    explicit QSttMmsBrcbCtrlWidget(QWidget *parent = 0);
    ~QSttMmsBrcbCtrlWidget();

	MMS_BRCB_CTRL_CONFIG m_oBrcbCtrl;

private slots:
        void on_m_btnOK_clicked();

        void on_m_btnCancel_clicked();

private:
    Ui::QSttMmsBrcbCtrlWidget *ui;
};

#endif // QSTTMMSBRCBCTRLWIDGET_H
