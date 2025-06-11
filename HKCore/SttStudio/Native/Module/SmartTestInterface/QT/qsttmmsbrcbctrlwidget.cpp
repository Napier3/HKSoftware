#include "qsttmmsbrcbctrlwidget.h"
#include "ui_qsttmmsbrcbctrlwidget.h"
#include "../../../../Module/OSInterface/OSInterface.h"

QSttMmsBrcbCtrlWidget::QSttMmsBrcbCtrlWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttMmsBrcbCtrlWidget)
{
    ui->setupUi(this);
	CString strTitleText;
	strTitleText = _T("定值区号选择界面");
	setWindowTitle(strTitleText);
}

QSttMmsBrcbCtrlWidget::~QSttMmsBrcbCtrlWidget()
{
    delete ui;
}

void QSttMmsBrcbCtrlWidget::on_m_btnOK_clicked()
{
	accept();
}

void QSttMmsBrcbCtrlWidget::on_m_btnCancel_clicked()
{
	reject();
}
